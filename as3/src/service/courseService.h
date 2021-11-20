#ifndef COURSESERVICE_H__
#define COURSESERVICE_H__

#include "..\repository\courseRepository.h"

struct courseService{
    courseRepo repo;
};
typedef struct courseService courseService;

/*public*/
extern courseService defaultCourseService();

extern void printTree_courseService(courseService service);
extern course * get_all_availableCourse();

extern unsigned int insertOne_courseService(courseService * service, course one);
extern course findById_courseService(courseService service, unsigned int id);
extern bool deleteById_courseService(courseService * service, unsigned int id);
extern int count_courseService(courseService service);

extern course findByCourseId_courseService(courseService service, char * course_id);

/*treeInfo*/
extern void print_treeInfo_courseService(courseService service);

#endif /* COURSESERVICE_H__*/
