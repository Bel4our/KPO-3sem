#include <iostream>
#include "Error.h"
#include "Parm.h"
#include "In.h"
#include <locale>
#include <cwchar>
#include <tchar.h>
#include <Windows.h>
#include "Log.h"
#include "Out.h"

using namespace std;

int _tmain(int argc, const _TCHAR* argv[])
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);

    cout << "---- тест Parm::getparm ----" << endl << endl;
    Parm::PARM parm;
    Log::LOG log = Log::INITLOG;

    try {
        parm = Parm::getparm(argc, argv);
        wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << endl << endl;
        log = Log::getlog(parm.log);
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
    }
    catch (Error::ERRORS e) {
        cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
    }

    cout << "---- тест In::getin ----" << endl << endl;
    try {
        parm = Parm::getparm(argc, argv);
        In::ININ in = In::getin(parm.in, parm.out);
        cout << in.text << endl;
        cout << "Всего символов: " << in.size << endl;
        cout << "Всего строк: " << in.lines << endl;
        cout << "Пропущено: " << in.ignor << endl;
        Log::WriteIn(log, in);
    }
    catch (Error::ERRORS e) {
        cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
        cout << "Строка " << e.inext.line << " позиция " << e.inext.col << endl << endl;
        log = Log::getlog(parm.log);
        Log::WriteError(log, e);
        log = Log::getlog(parm.out);
        Log::WriteError(log, e);

    }

    system("pause");
    return 0;

}