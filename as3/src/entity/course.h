#ifndef COURSE_H__
#define COURSE_H__

struct _course{
    unsigned int id;
    char course_id[20];
    char name[20];
    char major[20];
    short credit;
};
typedef struct _course course;

extern char * toStringCourse(course c);
extern course create_course(char* course_id, char * name, char * major, short credit);


#endif /* COURSE_H__*/
