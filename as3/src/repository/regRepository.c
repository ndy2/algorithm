#include <stdio.h>
#include "regRepository.h"

void printTree_regRepo(regRepo repo){
    printTree_regTree(repo.t.root);
}

void print_treeInfo_regRepo(regRepo repo,char * title){
    print_treeInfo_regTree(repo.t,title);
}

/*private*/
unsigned int generateId_reg(regRepo * repo){
    unsigned int id=-1;
    for(int i = 0 ; i <repo->t.size; i++){
        if(!repo->t.exist[i]){
            id=i;
            break;
        }
    }
    return id;
}

/*public*/

regRepo create_regRepo(int size){
    regRepo repo;
    repo.t=create_regTree(size);
    return repo;
}

unsigned int insertOne_regRepo(regRepo * repo, reg one){
     
    //Repo has the role to generate id!
    one.id= generateId_reg(repo);
    
    if(one.id!=-1){
        insertOne_regTree(&repo->t, one);
    }
    return one.id;
 }

reg findById_regRepo(regRepo  repo, unsigned int id){
    return findById_regTree(repo.t,id);
}

bool deleteById_regRepo(regRepo * repo, unsigned int id){
    return deleteById_regTree(&repo->t,id);
}

int count_regRepo(regRepo repo){
    return count_regTree(repo.t);
}

regApi findAll_wherestudentIdIsGiven_regRepo(regRepo repo, unsigned int student_id){
    return findAll_wherestudentIdIsGiven_regTree(repo.t,student_id);
}

void updateTreeInfo_regRepo(regRepo * repo){
    updateTreeInfo_regTree(&repo->t);
}
