#pragma once
#include "stdafx.h"
#include <fstream>
#include "In.h"
#include "Parm.h"
#include "Error.h"
#include "LT.h"
#include "IT.h"


namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;
	};

	static const LOG INITLOG{ L"", NULL };
	LOG getlog(wchar_t logfile[]);
	void WriteLine(LOG log, char* c, ...); // запись строки в протокол
	void WriteLine(LOG log, wchar_t* c, ...); // запись строки в протокол
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::ININ in);
	void WriteError(LOG log, Error::ERRORS error);
	void WriteLexTable(LOG log, LT::LexTable& lextable);
	void WriteIdTable(LOG log, IT::IdTable& idtable);
	


	void Close(LOG log);
};

