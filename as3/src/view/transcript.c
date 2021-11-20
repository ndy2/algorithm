#include "transcript.h"

#include <stdio.h>
#include <stdlib.h>


viewTemplate transcript_allView(authentication a){
    viewTemplate view;
    setView(&view,"transcript", 2,1);
    addContent(&view,0, "성적 확인서 출력하기 (전체)");
    addContent(&view,1, "-- 1. 뒤로가기");

    return view;
}


viewTemplate transcript_semesterRequestView(){
    viewTemplate view;
    setView(&view,"transcript-request", 2,0);
    
    addContent(&view,0, "성적을 확인하고 싶은 연도, 학기를 입력하세요");
    addContent(&view,1, "입력 형태 : yyyy n (n: 1 or 2)");

    return view;
}

char * regInfo_toRow(regInfo ri){
    char * out = (char*)malloc(sizeof(char) * 150);
    sprintf(out,"|%s %-18s %-14s %-14s %-5.2f  %-2d  |",ri.course_id,ri.name,ri.prof,ri.major,ri.score,ri.credit);
    return out;
}

viewTemplate transcript_semesterView(authentication a, model1* model){
    viewTemplate view;
    semRegInfo sri = model->data[0];
    int num_sugang = sri.count;
    setView(&view,"transcript-semester", 3+num_sugang+3,1);
    regInfo_toRow(model->data[0].infos[0]);

    addContent(&view,0, "┌───────────────────학기별 성적 조회──────────────────────┐");
    char * line = (char*)malloc(sizeof(char)*30);
    regInfo_toRow(model->data[0].infos[0]);

    sprintf(line,"│%d년도 %d학기                            수강 과목 수 : %d│",sri.year, sri.semester, num_sugang);
    addContent(&view,1, line);
    addContent(&view,2, "│과목코드 과목명      교수명      학과          성적   학점│");

    for(int r = 0; r <num_sugang; r++){
        addContent(&view,r+3, regInfo_toRow(model->data[0].infos[r]));
    }
    addContent(&view,num_sugang +3, "└──────────────────────────────────────────────────────────┘");
    
    char * line2 = (char*)malloc(sizeof(char)*30);
    sprintf(line2,"-- GPA : %.2f",model->score_sum/model->credit_sum);
    addContent(&view,num_sugang +4, line2);
    addContent(&view,num_sugang +5, "-- 1. 뒤로가기");

    return view;
}


viewTemplate transcript_entireView(authentication a, model1* model){

    printf("┌──────────────────── 성적 증명서 ──────────────────────┐\n");
    printf("│                         이름 : %s, 학번 : %u│\n",a.user.name,a.user.student_id);
    printf("├──────────────────────────────────────────────────────├\n");

    for(int i = 0 ; i <model->size; i++){
        semRegInfo sri = model->data[i];
        printf("│%d년도 %d학기                          수강 과목 수 : %d│\n",sri.year, sri.semester,sri.count);
        printf("├────────────────────────────────────────────────────────┤\n");
        printf("│과목코드 과목명      교수명      학과          성적   학점│\n");
        for(int r= 0 ;r < sri.count; r++){
            printf("%s\n",regInfo_toRow(sri.infos[r]));
        }

        printf("│                                         평균 평점 : %.2f│\n", sri.score_sum/sri.credit_sum);
        if(i==model->size-1){
                printf("└──────────────────────────────────────────────────────────┘\n");
        }else{
            printf("├────────────────────────────────────────────────────────┤\n");
        }
    }
    printf("               수강 학점 : %d/%d    전체 GPA : %.2f\n",model->credit_sum,140, model->score_sum/model->credit_sum);

    viewTemplate view;
    setView(&view,"transcript-entire", 1,1);
    
    addContent(&view,0,"--1.뒤로가기 ");
    return view;
}
