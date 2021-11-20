#include <stdio.h>
#include <stdlib.h>

#include "..\src\service\appService.h"

appService app;

void runApp(){
    //given
    initApp(&app);

    // 학생 정보 출력
    for(int i = 0 ; i < 120 ; i++){
        printf("%d %s",i,toStringStudent(findById_studentService(app.stduent_service,i)));
    }

    //when
    run(&app);
}

// student generation check

void initTest(){
    //given
    initApp(&app);
    studentService service = app.stduent_service;
    
    //when
    for(int i = 0 ; i < 60 ; i++){
        printf("%s",toStringStudent(findById_studentService(service,i)));
    }

    //then
    // valid 30개 확인
}


int main(){
    // initTest();
    runApp();
}