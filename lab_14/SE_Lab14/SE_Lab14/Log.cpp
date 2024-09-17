#define _CRT_SECURE_NO_WARNINGS
#include "Log.h"
#include <iostream>
#include <fstream>
#include "Error.h"
#include <cstdarg>
#include <ctime>

using namespace Log;
using namespace std;
using namespace Parm;
using namespace In;

LOG Log::getlog(wchar_t logfile[])
{
    LOG log;
    ofstream* file = new ofstream(logfile);
    if (!file->is_open())
    {
        delete file;
        ERROR_THROW(112);
    }
    wcscpy_s(log.logfile, logfile);
    log.stream = file;
    return log;
}

void Log::WriteLine(LOG log, char* c, ...)
{
    char** p = &c; 
    int j = 0;
    while (p[j] != "") { 
        *log.stream << p[j];
        j++;
    }
}


void Log::WriteLine(LOG log, wchar_t* c, ...)
{
    wchar_t** p = &c;
    char buf[50];
    int j = 0;
    while (p[j] != L"") {
        wcstombs(buf, p[j++], 50);
        *log.stream << buf;
    }
}

void Log::WriteLog(LOG log)
{
    time_t rantime;
    struct tm timeinfo;
    char buffer[80];
    time(&rantime);
    localtime_s(&timeinfo, &rantime);

    strftime(buffer, sizeof(buffer), "%d.%m.%Y %I:%M:%S", &timeinfo);
    (*log.stream) << "---Протокол---" << buffer << " ---" << endl;
}

void Log::WriteParm(LOG log, PARM parm)
{
    char buf[80];
    wcstombs(buf, parm.in, sizeof(buf));
    (*log.stream) << buf << endl;
    wcstombs(buf, parm.out, sizeof(buf));
    (*log.stream) << buf << endl;
    wcstombs(buf, parm.log, sizeof(buf));
    (*log.stream) << buf << endl;
}

void Log::WriteIn(LOG log, ININ in)
{
    (*log.stream) << "Количество символов: " << in.size << endl
        << "Пропущено: " << in.ignor << endl
        << "Количество строк: " << in.lines << endl;
}

void Log::WriteError(LOG log, Error::ERRORS er)
{
    if (log.stream) { // если открыт поток для записи
        *log.stream << "Ошибка " << er.id << ": " << er.message; // выводим сообщение об ошибке
        if (er.inext.line != -1) { // если имеется информации о месте ошибке, то выводим и эту информацию
            *log.stream << ", строка " << er.inext.line << ", позиция " << er.inext.col << '\n';
        }
        else {
            *log.stream << '\n';
        }
    }
    else { // если поток не открыт, то выводим информацию в консоль
        cout << "Ошибка " << er.id << ": " << er.message << '\n';
        cout << "Строка " << er.inext.line << ", позиция " << er.inext.col << '\n';
    }
   
}

void Log::Close(LOG log)
{
    if (log.stream->is_open())
    {
        log.stream->close();
        delete log.stream;
    }
}