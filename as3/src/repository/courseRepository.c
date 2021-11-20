#include <stdio.h>
#include "courseRepository.h"

void printTree_courseRepo(courseRepo repo){
    printTree_courseTree(repo.t.root);
}

/*private*/
unsigned int generateId_course(courseRepo * repo){
    unsigned int id=-1;
    for(int i = 0 ; i <repo->t.size; i++){
        if(!repo->t.exist[i]){
            id=i;
            return id;
        }
    }
    return id;
}

courseRepo create_courseRepo(int size){
    courseRepo repo;
    repo.t=create_courseTree(size);
    return repo;
}

/*public*/
unsigned int insertOne_courseRepo(courseRepo * repo, course course){
     
    //Repo has the role to generate id!
    course.id= generateId_course(repo);
    
    if(course.id!=-1){
        insertOne_courseTree(&repo->t, course);
    }
    return course.id;
 }

course findById_courseRepo(courseRepo  repo, unsigned int id){
    return findById_courseTree(repo.t,id);
}

bool deleteById_courseRepo(courseRepo * repo, unsigned int id){
    return deleteById_courseTree(&repo->t,id);
}

int count_courseRepo(courseRepo repo){
    return count_courseTree(repo.t);
}

course findByCourseId_courseRepo(courseRepo repo, char * course_id){
    return findByCourseId_courseTree(repo.t,course_id);
}