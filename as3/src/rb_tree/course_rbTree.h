#ifndef COURSE_RBTREE_H__
#define COURSE_RBTREE_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "..\entity\course.h"
#include "treeInfo.h"


struct node_course{
    course data;
    char color;
    struct node_course * parent;
    struct node_course * left;
    struct node_course * right;
};
typedef struct node_course node_course;

struct tree_course{
    int size;
    node_course * root;
    node_course * nil;
    bool * exist;

    treeInfo ti;
};
typedef struct tree_course tree_course;


/**
 * print
 * */
void printTree_courseTree(node_course * tree);

/**
* constructor
**/
extern tree_course create_courseTree(int m);

/**
* insert
**/
extern bool insertOne_courseTree(tree_course *in, course val);

/**
* select
**/
extern course findById_courseTree(tree_course t, int id);
extern int count_courseTree(tree_course in);
extern course findByCourseId_courseTree(tree_course t,char * course_id);

/**
* delete
**/
extern bool deleteById_courseTree(tree_course *in, int id);


/**
 *  treeInfo
 * */
extern void setTreeName_courseTree(tree_course * t, char * treeName);
extern void updateTreeInfo_courseTree(tree_course * t);
extern void print_treeInfo_courseTree(tree_course t, char * title);


#endif /* COURSE_RBTREE_H__*/
