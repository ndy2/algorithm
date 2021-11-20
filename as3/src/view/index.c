#include "index.h"

#include <stdio.h>
#include <stdlib.h>

viewTemplate indexView(authentication a, model2 model){
    viewTemplate view;
    if(a.c.valid){
        setView(&view,"index", 0,5);

        printf("%s 관리 페이지 %u\n",a.user.name,a.user.student_id);
        printf("┌────────────────────┐\n");
        printf("│1.성적확인서 조회   │\n");
        printf("│2.학기별성적조회    │\n");
        printf("│3.전체삭제          │\n");
        printf("│4.강의 ID별 삭제    │\n");
        printf("│5.로그 아웃         │\n");
        printf("└────────────────────┘\n");
        printf("[total student count : %d, total GPA : %.2f]\n",model.studentCnt,model.totalGpa);
    }else{
        setView(&view,"index", 0,2);
        printf("Welcome to Coffee University GLS!!\n");
        printf("┌────────────────────┐\n");
        printf("│1.Id                │\n");
        printf("│2.Exit              │\n");
        printf("└────────────────────┘\n");
    }
    return view;
}