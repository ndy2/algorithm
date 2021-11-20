#include <stdio.h>
#include "clazzRepository.h"

void printTree_clazzRepo(clazzRepo repo){
    printTree_clazzTree(repo.t.root);
}

void print_treeInfo_clazzRepo(clazzRepo repo,char * title){
    print_treeInfo_clazzTree(repo.t,title);
}

/*private*/
unsigned int generateId_clazz(clazzRepo * repo){
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
clazzRepo create_clazzRepo(int size){
    clazzRepo repo;
    repo.t=create_clazzTree(size);
    return repo;
}

unsigned int insertOne_clazzRepo(clazzRepo * repo, clazz one){
     
    //Repo has the role to generate id!
    one.id= generateId_clazz(repo);
    
    if(one.id!=-1){
        insertOne_clazzTree(&repo->t, one);
    }
    return one.id;
 }

clazz findById_clazzRepo(clazzRepo  repo, unsigned int id){
    return findById_clazzTree(repo.t,id);
}

bool deleteById_clazzRepo(clazzRepo * repo, unsigned int id){
    return deleteById_clazzTree(&repo->t,id);
}

int count_clazzRepo(clazzRepo repo){
    return count_clazzTree(repo.t);
}

/*select where*/
clazzDto findAllClazzWhereYearAndSemesterGiven_clazzRepo(clazzRepo repo, int year, short semester){
    return findAllClazzWhereYearAndSemesterGiven_clazzTree(repo.t, year, semester);
}

void updateTreeInfo_clazzRepo(clazzRepo * repo){
    updateTreeInfo_clazzTree(&repo->t);
}
