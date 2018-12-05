#include "D:\TX\TXlib.h"
#include "C:\Program Files (x86)\eSpeak\docs\speak_lib.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "PtrList.h"
#include "Tree.h"
#include "Expert.h"

const char dot[300] = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\gvedit.exe\" -Tbmp ";

const char* SAVENAME = "expert.txt";

int main()
{
    txSetConsoleAttr (0xf0);

    Akinator(dot, SAVENAME);

    //ptr_list_test(dot);

    return 0;
}
