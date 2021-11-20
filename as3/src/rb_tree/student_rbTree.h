#ifndef STUDENT_RBTREE_H__
#define STUDENT_RBTREE_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "..\entity\student.h"
#include "treeInfo.h"

typedef struct _node_student{
    student data;
    char color;
    struct _node_student * parent;
    struct _node_student * left;
    struct _node_student * right;
}node_student;

typedef struct _tree_student{
    int size;
    node_student * root;
    node_student * nil;
    bool * exist;

    treeInfo ti;
}tree_student;

/**
 * print
 * */
void printTree_studentTree(node_student * tree);

/**
* constructor
**/
extern tree_student create_studentTree(int m);

/**
* insert
**/
extern bool insertOne_studentTree(tree_student *in, student val);

/**
* select
**/
extern student findById_studentTree(tree_student t, int id);
extern int count_studentTree(tree_student in);
extern student findByStudentId_tree(tree_student t, unsigned int student_id);
extern student * findAll_studentTree(tree_student t);

/**
* delete
**/
extern bool deleteById_studentTree(tree_student *in, int id);

/**
 *  treeInfo
 * */
extern void setTreeName_studentTree(tree_student * t, char * treeName);
extern void updateTreeInfo_studentTree(tree_student * t);
extern void print_treeInfo_studentTree(tree_student t, char * title);

#endif /* STUDENT_RBTREE_H__*/
