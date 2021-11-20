#include <stdio.h>
#include <stdlib.h>

#include "..\src\service\courseService.h"

courseRepo repo;
courseService service;

//Before Each
void prepare_ServiceWith_threeCourse(){
    //given
    repo = create_courseRepo(60);
    service.repo = repo;

    course algorithm = create_course("SWE2016","알고리즘 개론","솦",3);
    course java = create_course("SWE2023","자바프로그래밍 실습","솦",2);
    course appMath = create_course("MTH3023","응용수학","수학과",3);

    insertOne_courseService(&service, algorithm);
    insertOne_courseService(&service, java);
    insertOne_courseService(&service, appMath);
}

void prepare_ServiceWith_noCourse(){
    //given
    repo = create_courseRepo(60);
    service.repo = repo;
}

void prepare_ServiceWith_fullRepo(){
    //given
    service = defaultCourseService();
}



/**
 * 정상 CRUD Logic Test
**/
void findByIdTest(){
    printf("\n=======findByIdTest=======\n");
    //given
    prepare_ServiceWith_noCourse();
    course algorithm = create_course("SWE2016","알고리즘 개론","솦",3);
    course java = create_course("SWE2023","자바프로그래밍 실습","솦",2);
    course appMath = create_course("MTH3023","응용수학","수학과",3);

    //when
    unsigned int id0 = insertOne_courseService(&service, algorithm);
    unsigned int id1 = insertOne_courseService(&service, java);
    unsigned int id2 = insertOne_courseService(&service, appMath);
    
    course found_algorithm = findById_courseService(service,id0);
    course found_appMath = findById_courseService(service,id1);

    //then
    printf("service size = %d\n",count_courseService(service));       //assertThat.isEqaulTo(3);
    printf("%s",toStringCourse(found_algorithm));     //assertThat(algorithm).isEqualTo(found_algorithm);   -> 현재 구현에서 id는 다름
    printf("%s",toStringCourse(found_appMath));       //assertThat(appMath).isEqualTo(found_appMath);       -> 현재 구현에서 id는 다름
}

void deleteByIdTest(){
    printf("\n=======deleteByIdTest=======\n");
    //given
    prepare_ServiceWith_threeCourse();

    //when
    //delete 자바 프로그래밍 two times
    bool res_firstDelete = deleteById_courseService(&service, 1);
    bool res_secondDelete = deleteById_courseService(&service, 1);

    //then
    printf("total amount after deletion = %d\n", count_courseService(service));    //assertThat.isEqualTo(2);    
    printf("res_firstDelete= %s\n", res_firstDelete ? "true" : "false");            //assertThat.isTrue();
    printf("res_secondDelete= %s\n", res_secondDelete ? "true" : "false");          //assertThat.isFalse();
}

 /**
 * 예외 검증
 * empty Repo일때 CRUD Test
 * */
void findByIdTest_with_emptyRepo(){
    printf("\n=======findByIdTest_with_emptyRepo=======\n");

    //given
    prepare_ServiceWith_noCourse();

    //when
    course found = findById_courseService(service,0);

    //then
    printf("%s",toStringCourse(found)); //assertThat(found.name).isEqualTo("dummyCourse");
}

void deleteTest_with_emptyRepo(){
    printf("\n=======deleteTest_with_emptyRepo=======\n");
    //given
    prepare_ServiceWith_noCourse();

    //when
    bool res = deleteById_courseService(&service, 0);

    //then
    printf("total amount = %d\n", count_courseService(service));    //assertThat.isEqualTo(0);    
    printf("res= %s\n", res ? "true" : "false");            //assertThat.isFalse();
}

void deleteTwoCoursesAndPrintTest(){
    printf("\n=======deleteTwoCoursesAndPrintTest=======\n");
    //given
    prepare_ServiceWith_fullRepo();
    
    printf("before deletion\n");
    printTree_courseService(service);

    //when
    deleteById_courseService(&service,0);
    deleteById_courseService(&service,3);
    
    //then
    printf("after deletion\n");
    printTree_courseService(service);
}


/**
 * printTree Test
* */

void printTest_with_fullRepo(){
    printf("\n=======printTest_with_fullRepo=======\n");
    //given
    prepare_ServiceWith_fullRepo();

    //when
    //then
    printTree_courseService(service);
    }

/**
 * Default Repo일때 삽입 Test
 *      -> 전체 course수 +1!
 *         전체 course수 x3으로 default size생성하기 때문
* */
void insertOneTest_with_defaultRepo(){
    printf("\n=======insertOneTest_with_defaultRepo=======\n");
    //given
    prepare_ServiceWith_fullRepo();

    //when
    course os = create_course("SWE3004","운영체제","솦",3);
    unsigned int res = insertOne_courseService(&service, os);
    //then
    printf("res= %u\n", res);            //assertThat(res).isEqaulTo(전체 course수 +1) 
}


void idGenerationPolicyTest(){
    printf("\n=======idGenerationPolicyTest=======\n");
    //given
    prepare_ServiceWith_fullRepo();
    
    //when
    deleteById_courseService(&service,0);
    deleteById_courseService(&service,3);

    course analects = create_course("GEDC010","성균논어","철학과",2);
    course leadership = create_course("GEDR013","이론리더십","시스템경영공학부",2);

    insertOne_courseService(&service,analects);
    insertOne_courseService(&service,leadership);

    //then
    course id_0 = findById_courseService(service, 0);
    course id_3 = findById_courseService(service, 3);

    printf("%s",toStringCourse(id_0));     //assertThat(id_0).isEqualTo(analects);
    printf("%s",toStringCourse(id_3));     //assertThat(id_3).isEqualTo(leadership);
}

int main(){
    /**
     * 정상 CRUD Logic Test
    **/
    findByIdTest();
    deleteByIdTest();
    deleteTwoCoursesAndPrintTest();

     /**
     * 출력 Test
    * */
    printTest_with_fullRepo();


    /**
     * 예외 검증
     * empty Repo일때 CRUD Test
     * */
    findByIdTest_with_emptyRepo();
    deleteTest_with_emptyRepo();

    /**
     * 삽입
     * default Repo일때 삽입 Test
    * */
    insertOneTest_with_defaultRepo();

    /**
     * Id generation policy Test
    * */
    idGenerationPolicyTest();


}