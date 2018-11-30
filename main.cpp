#include "D:\TX\TXlib.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "PtrList.h"
#include "Tree.h"

const char dot[300] = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\" -Tbmp ";

const char LISTDUMP[10] = "list";
const char TREEDUMP[10] = "tree";

void ptr_list_test(const char*);

int main()
{
    txSetConsoleAttr (0xf0);

    Tree tr;
    tree_Ctor(&tr);

    Node* root = create_node(456);

    tr.root = root;
    trmake_hash(&tr);
    tr.ver_num++;

    tree_insert_left(&tr, root, 65);
    tree_insert_right(&tr, root, 873);


    tree_erase(&tr, root->left);

    tree_insert_left(&tr, root, 767);

    tree_insert_left(&tr, root->left, 54);

    tree_insert_right(&tr, root, 666);

    tree_print(&tr);
    tree_dump(dot, TREEDUMP, &tr);

    tree_Dtor(&tr);
    return 0;
}

void ptr_list_test(const char DUMPNAME[])
{
    MyPtrList list;
    plist_Ctor(&list);

    plist_push_back(&list, 12);

    PtrListElem* k = plist_push_front(&list, 144);
    plist_insert(&list, k, 156);

    PtrListElem* del = plist_push_back(&list, 2222);
    plist_push_back(&list, 3333);
    plist_push_back(&list, 45454);
    plist_push_front(&list, 890);
    plist_erase(&list, del);
    for (int i = 0; i < 20; i++) plist_insert(&list, k, i*i + 2);

    plist_dump(dot, DUMPNAME, &list);

    plist_Dtor(&list);
}
