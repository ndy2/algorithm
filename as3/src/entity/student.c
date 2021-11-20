#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_ID -1
#include "student.h"

char * toStringStudent(student stdu){
    char * out = (char*)malloc(sizeof(char) * 50);
    sprintf(out,"%u, %u, %s, %s\n", stdu.id,stdu.student_id,stdu.name,stdu.major);
    return out;
}

student create_student(unsigned int student_id, char * name, char * major){
    student ret;
    ret.id = DEFAULT_ID;
    ret.student_id = student_id;
    sprintf(ret.name,"%s",name);
    sprintf(ret.major,"%s",major);
    return ret;
}

student create_dummyStudent(){
    return create_student(-1,"덤학생","덤학생");
}