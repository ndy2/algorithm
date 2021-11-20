#include <stdio.h>
#include "dataSource.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int n = 74;
char *names[74] = { "남득윤", "배수지","고칼슘","저지방", 
"장문영", "남궁소훈", "배광식", "장준기", "문현아", "심재정", "제갈은정", "탁승훈", "신윤수", "설진아",
"노샘", "황보달", "신나라우람", "풍한결", "강나길", "안나라우람", "양나길", "신한결", "심빛가람", "장한결",
"송봄", "조나빛", "심나리", "사공은비", "신햇빛", "유한울", "송구름", "노새벽", "노구슬", "박라움",
"장웅", "배호", "전혁", "안철", "제갈광", "안광", "풍광", "제갈훈", "허철", "봉혁",
"봉설", "사공성", "고상", "전상", "박현", "송란", "허진", "고성", "정란", "오리",
"고경택", "임덕수", "임요한", "정오성", "장현승", "이경택", "성동건", "남궁경택", "사공경모", "정재섭",
"황재인", "남경님", "박유리", "신미란", "정재인", "이지해", "강이경", "예미래", "사공혜림", "최자경"};

int m = 6;
char *majors[6] = { "수학과","솦","건축학과","물리학과","식물학과","동물학과" };

int c = 12;
char *courseIds[12] = { "MTH1234", "SWE7777","PHY1234","PHY2345","ARC1234","BOT9876","ZOO7777","ZOO1234","ZOO4321","MTH4321",
                        "sWE1234","PHY4321"};

char *courseNames[12] = { "해석학", "인공지능개론","우주물리학","일반물리학","건축학개론","식물학과","동물학개론","양돈학","가금학","응용수학",
                          "자료구조","전자물리학"};

short credits[12] =  {3,3,3,3,3,3,3,3,3,3,
                      3,2};

char * get_random_student_name(){
    int i = rand() % n;
    return names[i];
}

char * get_random_major(){
    int i = rand() % m;
    return majors[i];
}



/* course Api */

char * naiveDictionary(char * key){
    char * val;
    if(!strcmp(key,"수학과")){
        return "MTH";
    }else if(!strcmp(key,"솦")){
        return "SWE";
    }else if(!strcmp(key,"건축학과")){
        return "ARC";
    }else if(!strcmp(key,"물리학과")){
        return "PHY";
    }else if(!strcmp(key,"식물학과")){
        return "BOT";
    }else if(!strcmp(key,"동물학과")){
        return "ZOO";
    }else{
        return "NULL";
    }
}

bool isAbbreviationMatch(char * major, char *courseId){
    char * slice = (char*)malloc(sizeof(char)*3);
    sprintf(slice,"%c%c%c",courseId[0],courseId[1],courseId[2]);
    return !strcmp(naiveDictionary(major),slice);
}

courseDto create_courseDto(char * major, char * courseId, char * name, short credit){
    courseDto c;
    sprintf(c.major,"%s",major);
    sprintf(c.course_id,"%s",courseId);
    sprintf(c.name,"%s",name);
    c.credit = credit;
    return c;
}

courseApi get_all_available_courseDto(){
    
    courseApi api;
    courseDto * list = (courseDto*)malloc(sizeof(courseDto)*c);
    int li = 0;
    for(int mi = 0 ; mi < m ; mi++){
        char * major = majors[mi];
        for(int ci =0 ; ci<c; ci++ ){
            if(isAbbreviationMatch(major, courseIds[ci])){
                list[li] = create_courseDto(major,courseIds[ci],courseNames[ci],credits[ci]);
                li++;
            }
        }
    }
    api.data = list;
    api.size = c;
    return api;
}