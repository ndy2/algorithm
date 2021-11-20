#ifndef REG_RBTREE_H__
#define REG_RBTREE_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "..\entity\reg.h"
#include "treeInfo.h"

#define reg reg

typedef struct _node_reg{
    reg data;
    char color;
    struct _node_reg * parent;
    struct _node_reg * left;
    struct _node_reg * right;
}node_reg;

typedef struct _tree_reg{
    int size;
    node_reg * root;
    node_reg * nil;
    bool * exist;

    treeInfo ti;
}tree_reg;

/**
 * print
 * */
void printTree_regTree(node_reg * tree);

/**
* constructor
**/
extern tree_reg create_regTree(int m);

/**
* insert
**/
extern bool insertOne_regTree(tree_reg *in, reg val);

/**
* select
**/
extern reg findById_regTree(tree_reg t, int id);
extern int count_regTree(tree_reg in);
extern regApi findAll_wherestudentIdIsGiven_regTree(tree_reg t, unsigned int student_id);

/**
* delete
**/
extern bool deleteById_regTree(tree_reg *in, int id);


/**
 *  treeInfo
 * */
extern void setTreeName_regTree(tree_reg * t, char * treeName);
extern void updateTreeInfo_regTree(tree_reg * t);
extern void print_treeInfo_regTree(tree_reg t, char * title);


#endif /* REG_RBTREE_H__*/
