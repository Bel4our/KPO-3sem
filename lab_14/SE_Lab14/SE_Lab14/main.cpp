#include <iostream>
#include "Error.h"
#include "Parm.h"
#include "In.h"
#include <locale>
#include <cwchar>
#include <tchar.h>
#include <Windows.h>
#include "Log.h"

using namespace std;

int _tmain(int argc, const _TCHAR* argv[])
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    cout << "---- тест Parm::getparm ----" << endl << endl;
    Parm::PARM parm;
    try {
        parm = Parm::getparm(argc, argv);
        wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << endl << endl;
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
    }
    catch (Error::ERRORS e) {
        cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
        cout << "Строка " << e.inext.line << " позиция " << e.inext.col << endl << endl;
    }
    Log::LOG log = Log::INITLOG;
    try {
        parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log);
        Log::WriteLine(log, (char*)"Тест: ", (char*)"без ошибок \n", "");
        Log::WriteLine(log, (wchar_t*)L"Тест: ", (wchar_t*)L"без ошибок \n", L"");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::ININ in = In::getin(parm.in, parm.out);
        Log::WriteIn(log, in);
        Log::Close(log);
    }
    catch (Error::ERRORS e) {
        Log::WriteError(log, e);
    };
    system("pause");
    return 0;

}