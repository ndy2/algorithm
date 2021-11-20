#ifndef CLAZZ_RBTREE_H__
#define CLAZZ_RBTREE_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "..\entity\clazz.h"
#include "treeInfo.h"

#define clazz clazz

typedef struct _node_clazz{
    clazz data;
    char color;
    struct _node_clazz * parent;
    struct _node_clazz * left;
    struct _node_clazz * right;
}node_clazz;

typedef struct _tree_clazz{
    int size;
    node_clazz * root;
    node_clazz * nil;
    bool * exist;

    treeInfo ti;
}tree_clazz;

/**
 * print
 * */
void printTree_clazzTree(node_clazz * tree);

/**
* constructor
**/
extern tree_clazz create_clazzTree(int m);

/**
* insert
**/
extern bool insertOne_clazzTree(tree_clazz *in, clazz val);

/**
* select
**/
extern clazz findById_clazzTree(tree_clazz t, int id);
extern int count_clazzTree(tree_clazz in);
extern clazzDto findAllClazzWhereYearAndSemesterGiven_clazzTree(tree_clazz t,int year, short semester);

/**
* delete
**/
extern bool deleteById_clazzTree(tree_clazz *in, int id);


/**
 *  treeInfo
 * */
extern void setTreeName_clazzTree(tree_clazz * t, char * treeName);
extern void updateTreeInfo_clazzTree(tree_clazz * t);
extern void print_treeInfo_clazzTree(tree_clazz t, char * title);


#endif /* CLAZZ_RBTREE_H__*/
