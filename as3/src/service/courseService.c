#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "courseService.h"
#include "..\util\dataSource.h"

void printTree_courseService(courseService service){
    printTree_courseRepo(service.repo);
}

courseService defaultCourseService(){
    
    courseApi api = get_all_available_courseDto();
    int size = api.size;

    courseService service;
    service.repo = create_courseRepo(size);
    
    course * courses = get_all_availableCourse();
    
    for(int i = 0 ; i < size; i++){
        course c =  create_course(api.data[i].course_id,api.data[i].name,api.data[i].major,api.data[i].credit);
        insertOne_courseService(&service,c);
    }

    updateTreeInfo_courseRepo(&service.repo);
    return service;
}

course * get_all_availableCourse(){
    courseApi api = get_all_available_courseDto();
    course * data = (course*)malloc(sizeof(course)*api.size);
    for(int i = 0 ; i < api.size; i++){
        data[i] = create_course(api.data[i].course_id,api.data[i].name,api.data[i].major,api.data[i].credit);
    }
    return data;
}

unsigned int insertOne_courseService(courseService * service, course one){
    return insertOne_courseRepo(&service->repo,one);
}

course findById_courseService(courseService service, unsigned int id){
    return findById_courseRepo(service.repo,id);
}

bool deleteById_courseService(courseService * service, unsigned int id){
    bool ret =  deleteById_courseRepo(&service->repo,id);
    updateTreeInfo_courseRepo(&service->repo);
    return ret;
}

int count_courseService(courseService service){
    return count_courseRepo(service.repo);
}

course findByCourseId_courseService(courseService service, char * course_id){
    return findByCourseId_courseRepo(service.repo, course_id);
}

//treeInfo print method
void print_treeInfo_courseService(courseService service){
    print_treeInfo_courseRepo(service.repo,"과목 트리");
}
