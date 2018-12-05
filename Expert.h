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
Node* expert_new_item(Tree*, Node*, int POS);
Node* expert_new_branch(Tree*, Node*);
int expert_get_definition(Tree*);
int expert_get_comparison(Tree*);
int expert_info_cmp(tree_type, tree_type);
int expert_print_way(Node*, const char*, int mode);                         // includes input nd info

#endif // EXPERT_H_INCLUDED
