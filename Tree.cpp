//// TREE.CPP

#include "Tree.h"

#define PARENT(node) (node)->parent
#define LEFT(node) (node)->left
#define RIGHT(node) (node)->right
#define ROOT(tree)  (tree)->root

void tree_Ctor(Tree* tr)
{
    assert(tr);

    tr->tree_guard_begin = GUARD;
    tr->tree_guard_end = GUARD;

    ROOT(tr) = NULL;

    tr->ver_num = 0;

    trmake_hash(tr);
}

void tree_Dtor(Tree* tr)
{
    assert(tr);

    tree_clear(tr);

    tr->TreeHash_struct = HASHPOIS;

    tr->tree_guard_begin = GUARDPOIS;
    tr->tree_guard_end = GUARDPOIS;
}

void node_Ctor(Node* node)
{
    assert(node);

    node->node_guard_begin = GUARD;
    node->node_guard_end = GUARD;

    PARENT(node) = NULL;
    LEFT(node) = NULL;
    RIGHT(node)= NULL;

    node->info = 0;
}

void node_Dtor(Node* node)
{
    assert(node);

    node->node_guard_begin = GUARDPOIS;
    node->node_guard_end = GUARDPOIS;

    PARENT(node) = NULL;
    LEFT(node) = NULL;
    RIGHT(node)= NULL;

    node->info = NAN;
}

void trmake_hash(Tree* tr)
{
    assert(tr);

    tr->TreeHash_struct = HASHDEFAULT;
    tr->TreeHash_struct = hash (tr, sizeof (*tr));
}

Node* create_node(tree_type val)
{
    Node* new_node = (Node*) calloc(1, sizeof(*new_node));
    node_Ctor(new_node);
    new_node->info = val;

    return new_node;
}

#define INSERT(pos) \
                if(nd->pos)\
                {\
                    nd->pos->info = val;\
                    return nd->pos;\
                }\
                Node* new_node = (Node*) calloc(1, sizeof(*new_node));\
                node_Ctor(new_node);\
                new_node->info = val;\
                PARENT(new_node) = nd;\
                nd->pos = new_node;\
                tr->ver_num++;\
                trmake_hash(tr);

Node* tree_insert_left(Tree* tr, Node* nd, tree_type val)
{
    assert(tr && nd);
    INSERT(left);
    return new_node;
}

Node* tree_insert_right(Tree* tr, Node* nd, tree_type val)
{
    assert(tr && nd);
    INSERT(right);
    return new_node;
}

int tree_erase(Tree* tr, Node* nd)
{
    assert(tr && nd);

    tree_cut(tr, nd);
    trmake_hash(tr);

    return 0;
}

Tree* tree_clear(Tree* tr)
{
    assert(tr);

    tree_cut(tr, ROOT(tr));

    ROOT(tr) = NULL;

    tr->ver_num = 0;

    trmake_hash(tr);

    return tr;
}

int tree_cut(Tree* tr, Node* nd)
{
    if (!nd)
    {
        return 0;
    }

    tree_cut(tr, LEFT(nd));
    tree_cut(tr, RIGHT(nd));

    if (PARENT(nd))
    {
        if (LEFT(PARENT(nd)) == nd)
        {
            LEFT(PARENT(nd)) = NULL;
        }

        if (RIGHT(PARENT(nd)) == nd)
        {
            RIGHT(PARENT(nd)) = NULL;
        }
    }

    node_Dtor(nd);
    free(nd);

    (tr->ver_num)--;
    return 0;
}

void tree_print(Tree* tr)
{
    assert(tr);
    node_print(ROOT(tr));
}

void node_print(Node* nd)
{
    if (!nd)
    {
        return;
    }
    printf("{%lg", nd->info);
    node_print(LEFT(nd));
    node_print(LEFT(nd));
    printf("}");
}

Tree* tree_read(const char READNAME[])
{

}

#define DO_REAL_HASH  \
    int StructHash_buf = tr->TreeHash_struct;\
    tr->TreeHash_struct = HASHDEFAULT;\
    int RealHash_buf = hash (tr, sizeof (*tr));
#define RE_STORE tr->TreeHash_struct = StructHash_buf;\

int tree_is_OK(Tree* tr)
{
    assert(tr);
    int error = TRERROK;

    DO_REAL_HASH;
    if ((tr->tree_guard_begin != GUARD) || (tr->tree_guard_end != GUARD) ||  RealHash_buf != StructHash_buf)
    {
        return TRERSTRUCT;
    }
    RE_STORE;

    unsigned int count = 0;

    node_is_OK(ROOT(tr), &count);

    if (tr->ver_num > count)
    {
        return TRERLEN;
    }

    return error;
}


#define IFRETURN(cond) if (cond) return (cond);

int node_is_OK(Node* nd, unsigned int* num)
{
    if (!nd)
    {
        return TRERROK;
    }

    int lerror = node_is_OK(LEFT(nd), num);
    int rerror = node_is_OK(RIGHT(nd), num);

    IFRETURN(lerror);
    IFRETURN(rerror);

    if ((nd->node_guard_begin != GUARD) || (nd->node_guard_end != GUARD))
    {
        return TRERDATA;
    }

    if (!isfinite(nd->info))
    {
        return TRERINFO;
    }

    (*num)++;
    return TRERROK;
}

#define CASE_TREE_OK(ERROR,MESSAGE)\
            case ERROR:\
            printf("   " MESSAGE "\n");\
            break;
#define TO_GRAPHVIZ(gv_name, DUMPNAME) strdup(DUMPNAME); strcat(gv_name, ".gv")
#define TO_BMP(bmp_name, DUMPNAME) strdup(DUMPNAME); strcat(bmp_name, ".bmp")
#define CONCAT_DOT(arg)    strcat(dotty, arg)

int tree_dump(const char dot[], const char DUMPNAME[], Tree* tr)
{
    assert(tr);

    printf("~In File: %s\n~In Line: %d\n", __FILE__, __LINE__);
    printf("~Tree [0x%X]\n~{\n   Vertex number = %u\n   Root = [0x%X]\n", (out_ptr) tr, tr->ver_num, (out_ptr) ROOT(tr));
    printf("   Struct_guard_begin  = %s\n", ((tr->tree_guard_begin) == GUARD) ? "GUARD": "ERROR");
    printf("   Struct_guard_end    = %s\n",   ((tr->tree_guard_end) == GUARD) ? "GUARD": "ERROR");

    DO_REAL_HASH;
    printf("   In memory Struct_Hash = %i\n", StructHash_buf);
    printf("        Real Struct_Hash = %i\n", RealHash_buf);
    RE_STORE;
    printf("   INFO: \n");\
    switch(tree_is_OK(tr))
    {
        CASE_TREE_OK(TRERROK,    "Tree is OK");
        CASE_TREE_OK(TRERDATA,   "Data memory in the tree was damaged");
        CASE_TREE_OK(TRERINFO,   "Tree values are not suitable");
        CASE_TREE_OK(TRERLEN,    "Tree length is not suitable");
        CASE_TREE_OK(TRERPOS,    "Links between tree elements are damaged");
        CASE_TREE_OK(TRERSTRUCT, "Structure of the tree is damaged");
    default:
        printf("   Tree verification failed\n");
        return 1;
    }

    printf("~}\n\n");

    char* gv_name = TO_GRAPHVIZ(gv_name, DUMPNAME);  // make grathviz file name
    char* bmp_name = TO_BMP(bmp_name, DUMPNAME);     // make bmp file name


    FILE* dumptxt = fopen(gv_name, "w");
    if (!dumptxt) return 1;

    fprintf(dumptxt, "digraph ge\n{\n ");

    node_dump(dumptxt, ROOT(tr));

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

#define NONE_ND(pos) strcat(dump_str, "pos%i[shape = none, label = \"\"];\n %i:<pos> -> "#pos"%i[style = \"\"];\n");
#define WRITE_ARG file, dump_str, nd, PARENT(nd), nd->info, nd, LEFT(nd), RIGHT(nd)
#define CASE_EDGE(val, body) case (val):\
                                    body;\
                                    break
#define CHILDSUMIF(cond, increm) if (cond)\
                                {\
                                    child += (increm);\
                                }


int node_dump(FILE* file, Node* nd)
{
    if(!nd)
    {
        return 0;
    }

    char dump_str[150] = "%i [shape = record, label = \" {%p | %lg | %p | {<l> %p | <r> %p }} \"];\n";

    int child = 0;
    CHILDSUMIF(LEFT(nd), 1);
    CHILDSUMIF(RIGHT(nd),2);

    switch(child)
    {
        CASE_EDGE(1, NONE_ND(r); fprintf(WRITE_ARG, nd, nd, nd));
        CASE_EDGE(2, NONE_ND(l); fprintf(WRITE_ARG, nd, nd, nd));
        CASE_EDGE(3, strcat(dump_str, "%i:<l> -> %i;\n %i:<r> -> %i;\n");
                    fprintf(WRITE_ARG, nd, LEFT(nd), nd, RIGHT(nd)));
    default:
        fprintf(WRITE_ARG);
    }

    node_dump(file, LEFT(nd));
    node_dump(file, RIGHT(nd));

    return 0;
}