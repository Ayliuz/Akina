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
    int lelem_guard_begin = GUARDPOIS;

    PtrListElem* prev = NULL;

    list_type info = NAN;

    PtrListElem* next = NULL;

    int lelem_guard_end = GUARDPOIS;
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

void plist_Ctor(MyPtrList*);
void plist_Dtor(MyPtrList*);
void plist_elem_Ctor(PtrListElem*);
void plist_elem_Dtor(PtrListElem*);
void plmake_hash(MyPtrList*);
PtrListElem* plist_push_back(MyPtrList*, list_type);
PtrListElem* plist_push_front(MyPtrList*, list_type);
PtrListElem* plist_insert(MyPtrList*, PtrListElem*, list_type);
int plist_pop_back(MyPtrList*);
int plist_pop_front(MyPtrList*);
int plist_erase(MyPtrList*, PtrListElem*);
int plist_clear(MyPtrList*);
int plist_is_OK(MyPtrList*);
int plelem_is_OK(PtrListElem*);
int plist_dump(const char*, const char*, MyPtrList*);
char* plelem_dump(PtrListElem*);

#endif // PTRLIST_H_INCLUDED
