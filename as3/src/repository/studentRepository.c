#include <stdio.h>
#include "studentRepository.h"

void printTree_studentRepo(studentRepo repo){
    printTree_studentTree(repo.t.root);
}

void print_treeInfo_studentRepo(studentRepo repo,char * title){
    print_treeInfo_studentTree(repo.t,title);
}

/*private*/
unsigned int generateId_student(studentRepo * repo){
    unsigned int id=-1;
    for(int i = 0 ; i <repo->t.size; i++){
        if(!repo->t.exist[i]){
            id=i;
            break;
        }
    }
    return id;
}

/*private - student id generate policy */
unsigned int get_student_id(int fromYear, int toYear, int id){

    int h = rand()% 6;
    int year = h<3?2021:
               h<4?2020:
               h<5?2019:2018;

    return year*1000000+id;
}

/*public*/
unsigned int insertOne_studentRepo(studentRepo * repo, student student){
     
    //Repo has the role to generate id!
    student.id= generateId_student(repo);
    
    if(student.id!=-1){
        if(student.student_id==-1){
            student.student_id = get_student_id(2018,2021,student.id);
        } 
        insertOne_studentTree(&repo->t, student);
    }
    
    return student.id;
 }

student findById_studentRepo(studentRepo  repo, unsigned int id){
    return findById_studentTree(repo.t,id);
}

bool deleteById_studentRepo(studentRepo * repo, unsigned int id){
    return deleteById_studentTree(&repo->t,id);
}

int count_studentRepo(studentRepo repo){
    return count_studentTree(repo.t);
}


student findByStudentId_repo(studentRepo repo, unsigned int student_id){
    return findByStudentId_tree(repo.t, student_id);
}


student * findAll_studentRepo(studentRepo repo){
    return findAll_studentTree(repo.t);
}


void updateTreeInfo_studentRepo(studentRepo * repo){
    updateTreeInfo_studentTree(&repo->t);
}
