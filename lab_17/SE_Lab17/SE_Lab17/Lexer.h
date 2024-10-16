#pragma once
#include "LT.h"
#include "IT.h"

namespace Lexer
{
    void Run(LT::LexTable& lextable, IT::IdTable& idtable, In::ININ in);
}