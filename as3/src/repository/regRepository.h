#ifndef REGREPOSITORY_H__
#define REGREPOSITORY_H__

#include "..\rb_tree\reg_rbTree.h"

struct regRepository{
    tree_reg t;
};

typedef struct regRepository regRepo;

/*public*/

extern regRepo create_regRepo(int size);
extern void printTree_regRepo(regRepo repo);
extern unsigned int insertOne_regRepo(regRepo * repo, reg one);
extern reg findById_regRepo(regRepo repo, unsigned int id);
extern bool deleteById_regRepo(regRepo * repo, unsigned int id);
extern int count_regRepo(regRepo repo);


extern regApi findAll_wherestudentIdIsGiven_regRepo(regRepo repo, unsigned int student_id);

#endif /* REGREPOSITORY_H__*/
