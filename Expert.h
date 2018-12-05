// EXPERT.H

#ifndef EXPERT_H_INCLUDED
#define EXPERT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <locale>
#include "Tree.h"

#define TRUE 1
#define FALSE 2
#define EXIT 3
#define DEFINE 4
#define COMPARE 5
#define DRAW 6

int Akinator(const char dot[], const char* SAVENAME);
int expert_get_answer();
int expert_cheer();

Node* expert_new_item(Tree* tree, Node* node, int POS);
Node* expert_new_branch(Tree* tree, Node* node);

int expert_get_definition(Tree* tree);
int expert_get_comparison(Tree* tree);

int expert_info_cmp(tree_type value1, tree_type value2);
int expert_print_way(Node* node, const char* separate, int mode);                         // includes input nd info

#endif // EXPERT_H_INCLUDED
