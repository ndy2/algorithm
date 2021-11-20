#ifndef TRANSCRIPT_MODEL_H__
#define TRANSCRIPT_MODEL_H__

#include "../entity/reg.h"
#include <stdbool.h>

typedef struct _reg_info{
    /* course에서 얻을 수 있는 정보들*/
    char course_id[20];
    char name[20];
    char major[20];
    short credit;

    /* clazz에서 얻을 수 있는 정보들*/
    int year;
    short semester;
    char prof[20];

    /* reg에서 얻을 수 있는 정보들*/
    float score;
    unsigned int reg_id;
}regInfo;


typedef struct _semester_register_info{
    int year;
    short semester;
    int count;
    float score_sum;
    short credit_sum; 
    regInfo * infos;
}semRegInfo;


typedef struct model1{
    int size;
    int num_reg;
    float score_sum;
    short credit_sum; 
    semRegInfo * data;
}model1;


extern char* toStringRegInfo(regInfo ri);

extern regInfo create_regInfo(unsigned int reg_id, char * course_id, int year, short semester,char *prof, float score);
extern void setCourseInfos(regInfo * ri ,char * name, char * major, short credit);

#endif /* TRANSCRIPT_MODEL_H__*/
