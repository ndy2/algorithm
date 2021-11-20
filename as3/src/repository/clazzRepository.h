#ifndef CLAZZREPOSITORY_H__
#define CLAZZREPOSITORY_H__

#include "..\rb_tree\clazz_rbTree.h"

struct clazzRepository{
    tree_clazz t;
};

typedef struct clazzRepository clazzRepo;

/*public*/

extern clazzRepo create_clazzRepo(int size);
extern void printTree_clazzRepo(clazzRepo repo);
extern unsigned int insertOne_clazzRepo(clazzRepo * repo, clazz one);
extern clazz findById_clazzRepo(clazzRepo repo, unsigned int id);
extern bool deleteById_clazzRepo(clazzRepo * repo, unsigned int id);
extern int count_clazzRepo(clazzRepo repo);

extern clazzDto findAllClazzWhereYearAndSemesterGiven_clazzRepo(clazzRepo repo, int year, short semester);

#endif /* CLAZZREPOSITORY_H__*/
