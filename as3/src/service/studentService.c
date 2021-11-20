#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "studentService.h"
#include "..\util\dataSource.h"


studentService defaultStudentService(int numStudent, int numFull){
    studentService service;
    studentRepo repo;
    
    repo.t = create_studentTree(numFull);
    service.repo = repo;

    student * students = create_student_randomArray(service,numStudent);
    for(int i = 0 ; i < numStudent; i++){
        insertOne_studentService(&service,students[i]);
    }
    insertOne_studentService(&service,create_student(2016310703,"남득윤","수학과"));

    updateTreeInfo_studentRepo(&service.repo);
    return service;
}


void printTree_studentService(studentService service){
    printTree_studentRepo(service.repo);
}


void print_treeInfo_studentService(studentService service){
    print_treeInfo_studentRepo(service.repo,"학생 트리");
}



student create_student_random(){
    return create_student(-1, get_random_student_name(), get_random_major());
}

student* create_student_randomArray(studentService service, int size){
    

    student* ret = (student*)malloc(sizeof(student) * size);

    for(int i = 0 ; i <size ; i++){
        ret[i] = create_student_random();
    }

    return ret;
}

unsigned int insertOne_studentService(studentService * service, student one){
    return insertOne_studentRepo(&service->repo,one);
}

student findById_studentService(studentService service, unsigned int id){
    return findById_studentRepo(service.repo,id);
}

bool deleteById_studentService(studentService * service, unsigned int id){
    bool ret =  deleteById_studentRepo(&service->repo,id);
    updateTreeInfo_studentRepo(&service->repo);
    return ret;
}

int count_studentService(studentService service){
    return count_studentRepo(service.repo);
}

student findByStudentId(studentService service, unsigned int student_id){
    return findByStudentId_repo(service.repo, student_id);
}

student * findAll_studentService(studentService service){
    return findAll_studentRepo(service.repo);
}

void setModelTwoStudentCnt(model2 * model,studentService service){
    model->studentCnt = count_studentService(service);
}

void print_allStudent(studentService service){
    int count = count_studentService(service);
    student * all = findAll_studentService(service);

    printf("[index, 학번, 이름, 전공]\n");
    for(int i = 0 ; i < count ; i++){
        printf("[%d %d %s %s]\n",all[i].id, all[i].student_id, all[i].name, all[i].major);
    }
}