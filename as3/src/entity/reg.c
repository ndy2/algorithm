#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_ID -1
#include "reg.h"

char * toStringReg(reg r){
    char * out = (char*)malloc(sizeof(char) * 50);
    sprintf(out,"%d, %d, %d, %f\n", r.id, r.student_id, r.clazz_id, r.credit);
    return out;
}

reg create_reg(unsigned int student_id, unsigned int clazz_id, float credit){
    reg ret;
    ret.id = DEFAULT_ID;
    ret.student_id = student_id;
    ret.clazz_id = clazz_id;
    ret.credit = credit;
    return ret;
}

reg create_dummyReg(){
    return create_reg(-1,-1,-1.0);
}