#include "FST.h"
#include <tchar.h>
#include <locale.h>
#include <iostream>

int _tmain(int argc, TCHAR* argv[])
{
    setlocale(LC_ALL, "rus");

    char str1[] = "b; r; a(c); e;";
    char str2[] = "b;  r; a(p);  e;";
    char str3[] = "b;r;a(p);a(c);e;";
    char str4[] = "b; r; a(p);e;";
    char str5[] = "b; r; a(c);a(c);a(p);e;";
    char str6[] = "b; r; a(c);e;";
    char str7[] = "b;     r;a(p);    e;";
    char str8[] = "b; r; a(c);f;";
    char str9[] = "b: r; a(c);a(c);";

    char* chains[] = { str1, str2, str3, str4, str5, str6, str7, str8, str9 };

    for (int i = 0; i < sizeof(chains) / sizeof(char*); i++)
    {

        //begin;(□)*return;(□)*(abs(calc+pr);) ⁺ □ * end;

        FST::FST fst(chains[i], 15,
            FST::NODE(1, FST::RELATION('b', 1)), // 0 состояние
            FST::NODE(1, FST::RELATION(';', 2)), // 1 состояние
            FST::NODE(3, FST::RELATION(' ', 2), FST::RELATION(' ', 3), FST::RELATION('r', 4)), // 2 состояние
            FST::NODE(1, FST::RELATION('r', 4)), // 3 состояние
            FST::NODE(1, FST::RELATION(';', 5)), // 4 состояние
            FST::NODE(3, FST::RELATION(' ', 5), FST::RELATION(' ', 6), FST::RELATION('a', 7)), // 5 состояние
            FST::NODE(1, FST::RELATION('a', 7)), // 6 состояние
            FST::NODE(1, FST::RELATION('(', 8)), // 7 состояние
            FST::NODE(2, FST::RELATION('c', 9), FST::RELATION('p', 9)), // 8 состояние
            FST::NODE(1, FST::RELATION(')', 10)), // 9 состояние
            FST::NODE(1, FST::RELATION(';', 11)), // 10 состояние
            FST::NODE(4, FST::RELATION('a', 7), FST::RELATION('e', 13), FST::RELATION(' ', 11), FST::RELATION(' ', 12)), // 11 состояние
            FST::NODE(1, FST::RELATION('e', 13)), // 12 состояние
            FST::NODE(1, FST::RELATION(';', 14)), // 13 состояние
            FST::NODE()                           // 14 состояние(конечное)
        );

        if (FST::execute(fst))
            std::cout << "Цепочка " << fst.string << " распознана" << std::endl;
        else std::cout << "Цепочка " << fst.string << " не распознана" << std::endl;
    };
    

    system("pause");
    return 0;
}
