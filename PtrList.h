// PTRLIST . H

#ifndef PTRLIST_H_INCLUDED
#define PTRLIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "stack.h"

#define GUARD 69490
#define GUARDPOIS -1
#define HASHPOIS -1
#define HASHDEFAULT 0
#define LERROK 0
#define LERREMOVE 1
#define LERDATA 2
#define LERINFO 3
#define LERPOS 4
#define LERSTRUCT 5
#define LERLEN 6

#ifndef $
#define $(x) std::cout<<"~"<<#x " = "<<x<<"\n";
#endif

typedef double list_type;
typedef struct MyPtrList MyPtrList;
typedef unsigned int out_ptr;

struct PtrListElem
{
    int list_elem_guard_begin = GUARDPOIS;

    PtrListElem* prev = NULL;

    list_type info = NAN;

    PtrListElem* next = NULL;

    int list_elem_guard_end = GUARDPOIS;
};

struct MyPtrList
{
    int plist_guard_begin = GUARDPOIS;

    unsigned int pList_len = 0;

    PtrListElem* head = NULL;
    PtrListElem* tail = NULL;

    int pListHash_struct = HASHDEFAULT;

    int plist_guard_end = GUARDPOIS;
};

void ptr_list_test(const char* dot);

void plist_Ctor(MyPtrList* list);
void plist_Dtor(MyPtrList* list);

void plist_elem_Ctor(PtrListElem* elem);
void plist_elem_Dtor(PtrListElem* elem);
PtrListElem* plist_elem_create(list_type val);

void plist_make_hash(MyPtrList* list);

PtrListElem* plist_push_back(MyPtrList* list, list_type val);
PtrListElem* plist_push_front(MyPtrList* list, list_type val);

PtrListElem* plist_insert(MyPtrList* list, PtrListElem* elem, list_type val);                 // behind input element
int plist_pop_back(MyPtrList* list);
int plist_pop_front(MyPtrList*list);

int plist_erase(MyPtrList* list, PtrListElem* elem);
int plist_clear(MyPtrList* list);

int plist_is_OK(MyPtrList* list);
int plist_elem_is_OK(PtrListElem* elem);

int plist_dump(const char dot[], const char DUMPNAME[], MyPtrList* list);
char* plist_elem_dump(PtrListElem* elem);
int plist_draw(const char dot[], const char DUMPNAME[], MyPtrList* list);

#endif // PTRLIST_H_INCLUDED
