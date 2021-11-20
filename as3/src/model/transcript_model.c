#include "transcript_model.h"
#include <stdio.h>
#include <stdlib.h>


char* toStringRegInfo(regInfo ri){
    char * out = (char*)malloc(sizeof(char) * 100);
    sprintf(out,"%s, %s, %s, %d %d %d %s %.2f\n",ri.course_id,ri.name,ri.major,ri.credit, ri.year,ri.semester,ri.prof,ri.score);
    return out;
}

/* construct regInfo */
// reg, clazz에서 얻을 수 있는 정보를 이용해 regInfo 생성
regInfo create_regInfo(unsigned int reg_id, char * course_id, int year, short semester,char *prof, float score){
    regInfo  ri;
    ri.reg_id = reg_id;

    sprintf(ri.course_id,"%s",course_id);
    sprintf(ri.prof,"%s",prof);

    ri.year = year;
    ri.semester = semester;
    ri.score = score;
    return ri;
}

/* set course infos */
//course 까지 가야 얻을 수 있는 정보를 setting
void setCourseInfos(regInfo * ri ,char * name, char * major, short credit){
    sprintf(ri->name,"%s",name);
    sprintf(ri->major,"%s",major);
    ri->credit = credit;
}
