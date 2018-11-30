// TREE.H

#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <direct.h>
#include "stack.h"


#define GUARD 7933
#define GUARDPOIS -1
#define HASHPOIS -1
#define HASHDEFAULT 0
#define TRERROK 0
#define TRERREMOVE 1
#define TRERDATA 2
#define TRERINFO 3
#define TRERPOS 4
#define TRERSTRUCT 5
#define TRERLEN 6

#ifndef $
#define $(x) std::cout<<"~"<<#x " = "<<x<<"\n";
#endif

typedef double tree_type;
typedef unsigned int out_ptr;

struct Node
{
    int node_guard_begin = GUARDPOIS;

    Node* parent = NULL;

    tree_type info = NAN;

    Node* left = NULL;
    Node* right = NULL;

    int node_guard_end = GUARDPOIS;
};

struct Tree
{
    int tree_guard_begin = GUARDPOIS;

    unsigned int ver_num = 0;

    Node* root = NULL;

    int TreeHash_struct = HASHDEFAULT;

    int tree_guard_end = GUARDPOIS;
};

void tree_Ctor(Tree*);
void tree_Dtor(Tree*);
void node_Ctor(Node*);
void node_Dtor(Node*);
void trmake_hash(Tree*);
Node* create_node(tree_type);
Node* tree_insert_left(Tree*, Node*, tree_type);
Node* tree_insert_right(Tree*, Node*, tree_type);
Tree* tree_clear(Tree*);
int tree_cut(Tree*, Node*);
int tree_erase(Tree*, Node*);
int tree_is_OK(Tree*);
int node_is_OK(Node*, unsigned int*);
int tree_dump(const char*, const char*, Tree*);
int node_dump(FILE*, Node*);
void tree_print(Tree*);
void node_print(Node*);
Tree* tree_read(const char READNAME[]);


#endif // TREE_H_INCLUDED
