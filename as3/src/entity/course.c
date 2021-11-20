#include "course.h"
#include "../util/dataSource.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_ID -1
char * toStringCourse(course c){
    char * out = (char*)malloc(sizeof(char) * 50);
    sprintf(out,"%u, %s, %s, %s, %hd\n", c.id,c.course_id,c.name,c.major,c.credit);
    return out;
}

course create_course(char* course_id, char * name, char * major, short credit){
    course ret;
    ret.id = DEFAULT_ID;
    sprintf(ret.course_id,"%s",course_id);
    sprintf(ret.name,"%s",name);
    sprintf(ret.major,"%s",major);
    ret.credit=credit;
    return ret;
}

