#include "D:\TX\TXlib.h"
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

    return 0;
}
