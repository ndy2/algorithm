#ifndef STUDENTREPOSITORY_H__
#define STUDENTREPOSITORY_H__

#include "..\rb_tree\student_rbTree.h"

struct studentRepository{
    tree_student t;
};

typedef struct studentRepository studentRepo;

/*public*/
extern void printTree_studentRepo(studentRepo repo);
extern void print_treeInfo_studentRepo(studentRepo repo,char * title);

extern unsigned int insertOne_studentRepo(studentRepo * repo, student student);
extern student findById_studentRepo(studentRepo repo, unsigned int id);
extern bool deleteById_studentRepo(studentRepo * repo, unsigned int id);
extern int count_studentRepo(studentRepo repo);
extern student findByStudentId_repo(studentRepo repo, unsigned int student_id);

extern student * findAll_studentRepo(studentRepo repo);

extern void updateTreeInfo_studentRepo(studentRepo * repo);

#endif /* STUDENTREPOSITORY_H__*/
