#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_ID -1
#include "clazz.h"

char * toStringClazz(clazz c){
    char * out = (char*)malloc(sizeof(char) * 50);
    sprintf(out,"%d, %d, %d, %s, %s\n", c.id, c.year, c.semester, c.course_id, c.prof);
    return out;
}

clazz create_clazz(int year, short semester, char * course_id, char * prof){
    clazz ret;
    ret.id = DEFAULT_ID;
    ret.year=year;
    ret.semester=semester;
    sprintf(ret.course_id,"%s",course_id);
    sprintf(ret.prof,"%s",prof);
    return ret;
}

clazz create_dummyClazz(){
    return create_clazz(-1,-1,"DUM1234","덤교수");
}