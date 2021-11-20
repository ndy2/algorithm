#ifndef COURSEREPOSITORY_H__
#define COURSEREPOSITORY_H__

#include "..\rb_tree\course_rbTree.h"

struct courseRepository{
    tree_course t;
};

typedef struct courseRepository courseRepo;

/*public*/
extern courseRepo create_courseRepo(int size);
extern void printTree_courseRepo(courseRepo repo);
extern void print_treeInfo_courseRepo(courseRepo repo,char * title);


extern unsigned int insertOne_courseRepo(courseRepo * repo, course course);
extern course findById_courseRepo(courseRepo repo, unsigned int id);
extern bool deleteById_courseRepo(courseRepo * repo, unsigned int id);
extern int count_courseRepo(courseRepo repo);

extern course findByCourseId_courseRepo(courseRepo repo, char * course_id);

extern void updateTreeInfo_courseRepo(courseRepo * repo);

#endif /* COURSEREPOSITORY_H__*/
