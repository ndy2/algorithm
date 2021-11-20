#ifndef CLAZZSERVICE_H__
#define CLAZZSERVICE_H__

#include "..\repository\clazzRepository.h"
#include "courseService.h"

struct _clazzService{
    clazzRepo repo;
    courseService couser_service;
};
typedef struct _clazzService clazzService;

/*public*/
extern clazzService defaultClazzService(int fromYear, int toYear);
extern void setCourseService(clazzService * service, courseService course_service);
extern void initClazzRepo_usingCourseService(clazzService * service, int fromYear, int toYear);
extern void printTree_clazzService(clazzService service);
extern unsigned int insertOne_clazzService(clazzService * service, clazz one);
extern clazz findById_clazzService(clazzService service, unsigned int id);
extern bool deleteById_clazzService(clazzService * service, unsigned int id);
extern int count_clazzService(clazzService service);


/*api*/
extern int getApiIdx(int year, short semester);
extern clazzApi findAllGroupByYearandSemester_clazzService(clazzService * service);

#endif /* CLAZZSERVICE_H__*/
