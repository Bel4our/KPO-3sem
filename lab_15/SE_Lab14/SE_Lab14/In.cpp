#include "Error.h";
#include "In.h";
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>

using namespace In;
using namespace std;

ININ In::getin(wchar_t infile[], wchar_t outfile[])
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ININ in;
	wifstream file(infile);
	if (!file.is_open())
	{
		ERROR_THROW(110);
	}

	in.size = 0;
	in.lines = 1;
	in.ignor = 0;
	in.text = new unsigned char[IN_MAX_LEN_TEXT];


	const int code_table[] = IN_CODE_TABLE;
	for (int i = 0; i < 256; i++)
	{
		in.code[i] = code_table[i];
	}

	wchar_t buf;
	int index = 0;

	while (file.get(buf) && index < IN_MAX_LEN_TEXT - 1)
	{
		if (buf == L'\n')
		{
			in.text[index] = '|';
			index++;
			in.lines++;
		}else
		if (in.code[static_cast<unsigned int>(buf)] == ININ::F)
		{
			ERROR_THROW_IN(111, in.lines, index);
		}
		else if (in.code[static_cast<unsigned int>(buf)] == ININ::I)
		{
			in.ignor++;
		}
		else if (in.code[static_cast<unsigned int>(buf)] == ININ::T)
		{
			in.text[index] = static_cast<unsigned char>(buf);
			index++;
		}
		else
		{
			in.text[index] = in.code[static_cast<unsigned int>(buf)];
			index++;
		}
	}

	in.text[index] = '\0';
	in.size = index;
	file.close();

	ofstream outfilet(outfile);
	outfilet << in.text;
	outfilet.close();

	return in;
}
