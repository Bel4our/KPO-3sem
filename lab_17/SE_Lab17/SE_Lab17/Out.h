#pragma once
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>
#include <ctime>
#include <stdarg.h>
#include "In.h"
#include "Error.h"
#include "Log.h"
#include "Parm.h"

namespace Out {
    struct OUT {
        wchar_t outfile[PARM_MAX_SIZE];
        std::ofstream* stream;
    };

    static const OUT INIOUT{ L"", NULL };
    OUT getout(wchar_t outfile[]);
    void WriteToFile(OUT out, In::ININ in);
    void WriteToError(OUT out, Error::ERRORS error);
    void CloseFile(OUT out);
}
