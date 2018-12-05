// PTRLIST . CPP

#include "PtrList.h"

void ptr_list_present(const char dot[])
{
    const char LISTDUMP[10] = "list";

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

    plist_dump(dot, LISTDUMP, &list);

    plist_Dtor(&list);
}


//************************************
/// Constructs MyPtrList object and initialize it.
///
/// \param [in] MyPtrList* l - pointer to MyPtrList object
///
///
/// \return void
///
//************************************

void plist_Ctor(MyPtrList* l)
{
    assert(l);

    l->plist_guard_begin = GUARD;
    l->plist_guard_end = GUARD;

    l->head = NULL;
    l->tail = NULL;

    l->pList_len = 0;

    plmake_hash(l);
}

//************************************
/// Deletes MyPtrList structure and its data.
///
/// \param [in] MyPtrList* l - pointer to MyPtrList object
///
///
/// \return void
///
//************************************

void plist_Dtor(MyPtrList* l)
{
    assert(l);

    plist_clear(l);

    l->pListHash_struct = HASHPOIS;

    l->plist_guard_begin = GUARDPOIS;
    l->plist_guard_end = GUARDPOIS;
}

//************************************
/// Constructs PtrListElem object and initialize it.
///
/// \param [in] PtrListElem* l - pointer to PtrListElem object
///
///
/// \return void
///
//************************************

void plist_elem_Ctor(PtrListElem* le)
{
    assert(le);

    le->lelem_guard_begin = GUARD;
    le->lelem_guard_end = GUARD;

    le->prev = NULL;
    le->next = NULL;

    le->info = 0;
}

//************************************
/// Deletes PtrListElem structure.
///
/// \param [in] PtrListElem* l - pointer to PtrListElem object
///
///
/// \return void
///
//************************************

void plist_elem_Dtor(PtrListElem* le)
{
    assert(le);

    le->lelem_guard_begin = GUARDPOIS;
    le->lelem_guard_end = GUARDPOIS;

    le->prev = NULL;
    le->next = NULL;

    le->info = NAN;
}

//************************************
/// Hashes the list.
///
/// \param [in] MyPtrList* l - pointer to MyPtrList object
///
/// \return changes ListHash_struct in list.
///
//************************************

void plmake_hash(MyPtrList* l)
{
    assert(l);

    l->pListHash_struct = HASHDEFAULT;
    l->pListHash_struct = hash (l, sizeof (*l));
}

#define INSERT(head_or_tail,next_or_prev_for_1_arg,not_2_arg) \
            PtrListElem* new_item = (PtrListElem*) calloc(1, sizeof(*new_item));\
            plist_elem_Ctor(new_item);\
            new_item->info = val;\
            \
            if(!(l->head_or_tail))\
            {\
                l->head = new_item;\
                l->tail = new_item;\
            }\
            else\
            {\
                l->head_or_tail->next_or_prev_for_1_arg = new_item;\
                new_item->not_2_arg = l->head_or_tail;\
                l->head_or_tail = new_item;\
            }\
            \
            (l->pList_len)++;\
            plmake_hash(l)

PtrListElem* plist_push_back(MyPtrList* l, list_type val)
{
    assert(l);
    INSERT(tail, next, prev);
    return new_item;
}

PtrListElem* plist_push_front(MyPtrList* l, list_type val)
{
    assert(l);
    INSERT(head, prev, next);
    return new_item;
}

//************************************
/// Inserts element in list after the certain element
///
/// \param [in] MyPtrList* l - pointer to MyPtrList object
/// \param [in] PtrListElem* le - pointer to the element to insert after
/// \param [in] list_type val - value to insert
///
/// \return pointer to PtrListElem object which include val
///
//************************************

PtrListElem* plist_insert(MyPtrList* l, PtrListElem* le, list_type val)
{
    assert(l && le && (le->next || le == l->tail));

    PtrListElem* new_item = (PtrListElem*) calloc(1, sizeof(*new_item));
    plist_elem_Ctor(new_item);
    new_item->info = val;

    if(le == l->tail)
    {
        return plist_push_back(l, val);
    }
    else
    {
        le->next->prev = new_item;
        new_item->prev = le;
        new_item->next = le->next;
        le->next = new_item;
    }

    (l->pList_len)++;
    plmake_hash(l);
    return new_item;
}

#undef INSERT

#define REMOVE(head_or_tail,next_or_prev_for_1_arg,not_2_arg)\
            if(!(l->head_or_tail))\
            {\
                return LERREMOVE;\
            }\
            \
            PtrListElem* del = l->head_or_tail;\
            l->head_or_tail = l->head_or_tail->next_or_prev_for_1_arg;\
            if(l->head_or_tail) \
            {\
                l->head_or_tail->not_2_arg = NULL;\
            }\
            else\
            {\
                l->head = NULL;\
                l->tail = NULL;\
            }\
            \
            plist_elem_Dtor(del);\
            free(del);\
            \
            (l->pList_len)--;\
            plmake_hash(l)

int plist_pop_back(MyPtrList* l)
{
    assert(l);
    REMOVE(tail, prev, next);
    return 0;
}

int plist_pop_front(MyPtrList* l)
{
    assert(l);
    REMOVE(head, next, prev);
    return 0;
}

int plist_erase(MyPtrList* l, PtrListElem* le)
{
    assert(l && le && (le->next || le == l->tail) && (le->prev || le == l->head));

    if(le == l->head)
    {
        return plist_pop_front(l);
    }
    if(le == l->tail)
    {
        return plist_pop_back(l);
    }

    PtrListElem* del = le;
    le->next->prev = le->prev;
    le->prev->next = le->next;

    plist_elem_Dtor(del);
    free(del);
    (l->pList_len)--;

    plmake_hash(l);
    return 0;
}

#undef REMOVE

#define CUR_HEAD PtrListElem* cur = l->head

int plist_clear(MyPtrList* l)
{
    assert(l);

    CUR_HEAD;
    while(cur)
    {
        PtrListElem* del = cur;
        cur = cur->next;
        plist_elem_Dtor(del);
        free(del);
    }

    l->pList_len = 0;

    l->head = NULL;
    l->tail = NULL;

    plmake_hash(l);

    return 0;
}

#define PREV(cur) cur->prev
#define NEXT(cur) cur->next
#define DO_REAL_HASH  \
    int StructHash_buf = l->pListHash_struct;\
    l->pListHash_struct = HASHDEFAULT;\
    int RealHash_buf = hash (l, sizeof (*l));
#define RE_STORE l->pListHash_struct = StructHash_buf;\

int plist_is_OK(MyPtrList* l)
{
    assert(l);
    int error = LERROK;

    DO_REAL_HASH;
    if ((l->plist_guard_begin != GUARD) || (l->plist_guard_end != GUARD) ||  RealHash_buf != StructHash_buf)
    {
        return LERSTRUCT;
    }
    RE_STORE;

    unsigned int count = 0;

    CUR_HEAD;
    while(cur)
    {
        if (error = plelem_is_OK(cur))
        {
            return error;
        }

        if (PREV(cur) && (NEXT(PREV(cur)) != cur) || NEXT(cur) && (PREV(NEXT(cur))!= cur))
        {
            return LERPOS;
        }

        if(count > l->pList_len)
        {
            return LERLEN;
        }

        cur = cur->next;
        count ++;
    }

    if (l->pList_len > count)
    {
        return LERLEN;
    }

    return error;
}




int plelem_is_OK(PtrListElem* le)
{
    assert(le);

    if ((le->lelem_guard_begin != GUARD) || (le->lelem_guard_end != GUARD))
    {
        return LERDATA;
    }

    if (!isfinite(le->info))
    {
        return LERINFO;
    }

    return LERROK;
}

#define CASE_LIST_OK(ERROR,MESSAGE)\
            case ERROR:\
            printf("   " MESSAGE "\n");\
            break;
#define TO_GRAPHVIZ(gv_name, DUMPNAME) strdup(DUMPNAME); strcat(gv_name, ".gv")
#define TO_BMP(bmp_name, DUMPNAME) strdup(DUMPNAME); strcat(bmp_name, ".bmp")
#define CONCAT_DOT(arg)    strcat(dotty, arg)

int plist_dump(const char dot[], const char DUMPNAME[], MyPtrList* l)
{
    assert(l);

    printf("~In File: %s\n~In Line: %d\n", __FILE__, __LINE__);
    printf("~List [0x%X]\n~{\n   Length = %u\n   Head = [0x%X]\n   Tail = [0x%X]\n", (out_ptr) l, l->pList_len, (out_ptr) l->head, (out_ptr) l->tail);
    printf("   Struct_guard_begin  = %s\n", ((l->plist_guard_begin) == GUARD) ? "GUARD": "ERROR");
    printf("   Struct_guard_end  = %s\n",   ((l->plist_guard_end) == GUARD) ? "GUARD": "ERROR");

    DO_REAL_HASH;
    printf("   In memory Struct_Hash = %i\n", StructHash_buf);
    printf("        Real Struct_Hash = %i\n", RealHash_buf);
    RE_STORE;
    printf("   INFO: \n");\
    switch(plist_is_OK(l))
    {
        CASE_LIST_OK(LERROK,    "List is OK");
        CASE_LIST_OK(LERDATA,   "Data memory in the list was damaged");
        CASE_LIST_OK(LERINFO,   "List values are not suitable");
        CASE_LIST_OK(LERLEN,    "List length is not suitable");
        CASE_LIST_OK(LERPOS,    "Links between list elements are damaged");
        CASE_LIST_OK(LERSTRUCT, "Structure of the list is damaged");
    default:
        printf("   List verification failed\n");
    }

    printf("~}\n\n");

    char* gv_name = TO_GRAPHVIZ(gv_name, DUMPNAME);  // make grathviz file name
    char* bmp_name = TO_BMP(bmp_name, DUMPNAME);     // make bmp file name

    FILE* dumptxt = fopen(gv_name, "w");
    if (!dumptxt) return 1;

    fprintf(dumptxt, "digraph ge\n{ rankdir = LR;\n");

    CUR_HEAD;
    for(int i = 0; (i < l->pList_len) && cur; i++ , cur = cur->next)
    {
        char* dump_elem_str = plelem_dump(cur);
        fprintf(dumptxt, dump_elem_str);
        free(dump_elem_str);
    }

    fprintf(dumptxt, "}");
    fclose(dumptxt);

    char* dotty = (char*) calloc(200, sizeof(*dotty));
    dotty = strcpy(dotty, dot);                         // make
    CONCAT_DOT(gv_name);                                // dot
    CONCAT_DOT(" -o ");                                 // compile
    CONCAT_DOT(bmp_name);                               // command

    system(dotty);                                  //compile graphviz
    system(bmp_name);                               //open bmp

    free(gv_name);
    free(bmp_name);
    free(dotty);

    return 0;
}

char* plelem_dump(PtrListElem* le)
{
    assert(le);
    char* dump = (char*) calloc(800, sizeof(*dump));
    char dump_str[700] = "%i [shape = none, label = <<TABLE BORDER = \"0\" CELLBORDER = \"1\" CELLSPACING = \"0\" CELLPADDING = \"4\">\
                                        <TR>\
                                        <TD  COLSPAN = \"2\"> %lg </TD>\
                                        </TR>\
                                        <TR>\
                                        <TD  COLSPAN = \"2\"> %p </TD>\
                                        </TR>\
                                        <TR>\
                                        <TD>%p</TD>\
                                        <TD>%p</TD>\
                                        </TR>\
                                        </TABLE>>];\n";
    if(le->prev)
    {
        strcat(dump_str, "%i -> %i;\n");
    }
    sprintf(dump, dump_str, le, le->info, le, le->prev, le->next, le->prev, le);
    return dump;
}
