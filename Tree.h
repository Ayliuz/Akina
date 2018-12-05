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

#define L 1
#define R 0
#define NOPARENT -1
#define GUARD 7933
#define GUARDPOIS -1
#define HASHPOIS -1
#define HASHDEFAULT 0
#define TRERROK 0
#define TRERREMOVE 1
#define TRERDATA 2
#define TRERPOS 4
#define TRERSTRUCT 5
#define TRERLEN 6

#ifndef $
#define $(x) std::cout<<"~"<<#x " = "<<x<<"\n";
#endif

#define PARENT(node) (node)->parent
#define LEFT(node) (node)->left
#define RIGHT(node) (node)->right
#define ROOT(tree)  (tree)->root

typedef char* tree_type;
typedef unsigned int out_ptr;

const size_t STRLEN = 100;

struct Node
{
    int node_guard_begin = GUARDPOIS;

    Node* parent = NULL;

    tree_type info = NULL;

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

void tree_present(const char dot[]);

void tree_Ctor(Tree*);
void tree_Dtor(Tree*);

void node_Ctor(Node*);
void node_Dtor(Node*);

void tree_make_hash(Tree*);

Node* tree_set_root(Tree*, Node*);
Node* node_create(tree_type);

Node* tree_insert_left(Tree*, Node*, tree_type);
Node* tree_insert_right(Tree*, Node*, tree_type);

Node* node_find(Node*, tree_type, int (*)(tree_type,tree_type));
int node_define(Node*);

Node* tree_find_common(Node*, Node*, int*);
size_t node_get_height(Node*);

Tree* tree_clear(Tree*);
int tree_cut(Tree*, Node*);
int tree_erase(Tree*, Node*);

int tree_is_OK(Tree*);
int node_is_OK(Node*, unsigned int*);

int tree_dump(const char*, const char*, Tree*);
int node_dump(FILE*, Node*);
int tree_draw(const char dot[], const char DUMPNAME[], Tree*);

void tree_print(Tree*, const char*);
void node_print(Node*, FILE*);

Tree* tree_read(const char*);
Node* node_read(FILE*, Tree*, int*);
Node* get_node(FILE*, int*);
char* get_str(FILE*, int*);
char* remove_shift(char*, int);

#endif // TREE_H_INCLUDED
