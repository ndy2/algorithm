#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "clazzService.h"
#include "../util/dataSource.h"

/*courseService -> clazzRepo 
 *generate and save methods*/


void setCourseService(clazzService * service, courseService course_service){
    service ->couser_service = course_service;
}


void initClazzRepo(clazzService * service, int fromYear, int toYear){
    courseApi api = get_all_available_courseDto();
    service->repo = create_clazzRepo((toYear-fromYear+1) * 2 * api.size);

    for(int year = fromYear ; year<= toYear ; year++){
        for(short semester = 1; semester <=2 ; semester ++){        
            for(int i = 0 ; i < api.size ; i++){
                int p = rand()%10;
                if(p>=3){
                    char * course_id = api.data[i].course_id;
                    char * prof = p%2?"김교수":"이교수";
                    clazz c= create_clazz(year,semester,course_id,prof);
                    
                    insertOne_clazzService(service,c);
                }              
            }
        }
    }    
}


clazzService defaultClazzService(int fromYear, int toYear){
    clazzService service;
    setCourseService(&service,defaultCourseService());
    initClazzRepo(&service, fromYear, toYear);
    return service;
}



/*clazzRepo only*/
void printTree_clazzService(clazzService service){
    printTree_clazzRepo(service.repo);
}


unsigned int insertOne_clazzService(clazzService * service, clazz one){
    return insertOne_clazzRepo(&service->repo,one);
}

clazz findById_clazzService(clazzService service, unsigned int id){
    return findById_clazzRepo(service.repo,id);
}

bool deleteById_clazzService(clazzService * service, unsigned int id){
    return deleteById_clazzRepo(&service->repo,id);
}

int count_clazzService(clazzService service){
    return count_clazzRepo(service.repo);
}

int getApiIdx(int year, short semester){
    return (year-2010) * 2 +(semester-1);
}

/*api*/
clazzApi findAllGroupByYearandSemester_clazzService(clazzService * service){
    clazzApi api;
    api.data = (clazzDto*)malloc(sizeof(clazzDto)*(2021-2010+1)*2);
    
    for(int year = 2010; year <=2021; year++){
        for(short semester = 1; semester <=2; semester++){
            clazzDto dto = findAllClazzWhereYearAndSemesterGiven_clazzRepo(service->repo,year, semester);
            api.data[getApiIdx(year,semester)] = dto;
        }
    }
    return api;
}
