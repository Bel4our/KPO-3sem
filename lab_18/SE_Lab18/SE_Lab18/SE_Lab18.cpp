#include "stdafx.h"
#include "iostream"
#include"Error.h"
#include"In.h"
#include"Log.h"
#include"Parm.h"
#include"Out.h"
#include"FST.h"
#include"Lexer.h"
#include"LT.h"
#include"MFST.h"
#include<cwchar>
#include<time.h>

using namespace std;
int _tmain(int argc, const _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	Parm::PARM parm = Parm::getparm(argc, argv);
	Log::LOG log = Log::INITLOG;
	Out::OUT out = Out::INIOUT;
	try
	{
		parm = Parm::getparm(argc, argv);
		In::ININ in = In::getin(parm.in);
		LT::LexTable lextab = LT::Create(LT_MAXSIZE - 1);
		IT::IdTable idtab = IT::Create(TI_MAXSIZE - 1);
		log = Log::getlog(parm.log);
		out = Out::getout(parm.out);
		Lexer::Run(lextab, idtab, in);
		log = Log::getlog(parm.log);
		Log::WriteLexTable(log, lextab);
		Log::WriteIdTable(log, idtab);

	
		MFST_TRACE_START
			MFST::Mfst mfst(lextab, GRB::getGreibach());			//автомат

		mfst.start();											// старт синтаксического анализа

		mfst.savededucation();									// сохранить правила вывода

		mfst.printrules();

		out = Out::getout(parm.out);
		Out::WriteToFile(out, in);
		Log::Close(log);
		Out::CloseFile(out);
	}
	catch (Error::ERRORS e)
	{
		cout << "Ошибка" << e.id << ':' << e.message << endl << endl;
		if (e.inext.line)
			Log::WriteError(log, e);
		Out::WriteToError(out, e);
		//Log::Close(log);
		//Out::CloseFile(out);
	}

	return 0;
};