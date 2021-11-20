#include "transcript.h"

#include <stdio.h>
#include <stdlib.h>


/*GetMapping("/delete-one")*/
viewTemplate delete_oneRequestView(){
    viewTemplate view;
    setView(&view,"delete-one", 0,0);
    printf("삭제할 과목의 학수번호와 수강년도, 학기를 입력하세요\n");
    printf("입력 형태 : COURSEID YYYY N (N: 1 or 2)\n");

    return view;
}

viewTemplate delete_oneCompleteView(bool deleted){
    viewTemplate view;
    setView(&view,"delete-one", 0,1);
    
    if(deleted){
        printf("삭제 되었습니다!\n");
    }else{
        printf("잘못된 요청입니다. 학수번호, 수강년도, 학기를 확인하세요.\n");
    }
    printf("--1.뒤로가기\n");

    return view;
}

viewTemplate delete_allRequestView(authentication a){
    viewTemplate view;
    setView(&view,"delete-entire", 0,2);
    
    printf("%s님과 관련된 모든 정보를 삭제합니다.\n",a.user.name);
    printf("정말 지우시겠습니까?\n");

    printf("삭제 대상 - 계정, 수강 정보\n");
    printf("\n");
    
    printf("--1.삭제\n");
    printf("--2.뒤로가기\n");

    return view;
}