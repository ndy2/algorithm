#include <stdio.h>
#include <stdlib.h>

#include "..\src\service\studentService.h"

studentRepo repo;
studentService service;

//Before Each
void prepare_ServiceWith_twoStudent(){
    //given
    repo.t = create_studentTree(60);

    service.repo = repo;

    student dy = create_student(2016000000,"남득윤","수학");
    student suzy = create_student(2012000000,"배수지","건축학");
    insertOne_studentService(&service, dy);
    insertOne_studentService(&service, suzy);
}
void prepare_ServiceWith_noStudent(){
    //given
    repo.t = create_studentTree(60);
    service.repo = repo;
}
void prepare_ServiceWith_fullRepo(){
    //given
    int size= 5;
    repo.t = create_studentTree(size);
    service.repo = repo;
    
    student * students = create_student_randomArray(service,size);
    for(int i = 0 ; i < size; i++){
        insertOne_studentService(&service,students[i]);
    }
}

/**
 * 램덤 생성
**/
void RandomGenearionTest(){
    //given

    //when
    int size = 10;
    student * random_students = (student*)malloc(sizeof(student)*size);
    random_students = create_student_randomArray(service,size);

    //then
    //service service에 삽입 하지 않았기 때문에 id는 전부 dummy value들임
    for(int i = 0 ; i < size; i++){
        printf("%s", toStringStudent(random_students[i]));
    }
}

/**
 * 정상 CRUD Logic Test
**/
void findByIdTest(){
    printf("\n=======findByIdTest=======\n");
    //given
    prepare_ServiceWith_twoStudent();
    //when

    //then
    student found_dy = findById_studentService(service,0);
    student found_suzi = findById_studentService(service,1);

    printf("%s",toStringStudent(found_dy));         //assertThat.isEqualTo(dy);
    printf("%s",toStringStudent(found_suzi));       //assertThat.isEqualTo(suzy);
}

void findAllTest_withTwoStudent(){
    printf("\n=======findAllTest_withTwoStudent=======\n");
    //given
    prepare_ServiceWith_twoStudent();
    //when
    int size = count_studentService(service);
    student * all = findAll_studentService(service);

    //then

    for(int i = 0 ; i <size; i++){
        printf("%s",toStringStudent(all[i]));
    }
}

void findAllTest_withFullStudent(){
    printf("\n=======findAllTest_withFullStudent=======\n");
    //given
    prepare_ServiceWith_fullRepo();
    //when
    int size = count_studentService(service);
    student * all = findAll_studentService(service);

    //then

    for(int i = 0 ; i <size; i++){
        printf("%s",toStringStudent(all[i]));
    }
}

void deleteByIdTest(){
    printf("\n=======deleteByIdTest=======\n");
    //given
    prepare_ServiceWith_twoStudent();

    //when
    //delete 남득윤 two times
    bool res_firstDelete = deleteById_studentService(&service, 0);
    bool res_secondDelete = deleteById_studentService(&service, 0);

    //then
    printf("total amount after deletion = %d\n", count_studentService(service));    //assertThat.isEqualTo(1);    
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
    prepare_ServiceWith_noStudent();

    //when
    student found = findById_studentService(service,0);

    //then
    printf("%s",toStringStudent(found)); //assertThat(found.name).isEqualTo("noStudent");
}

void deleteTest_with_emptyRepo(){
    printf("\n=======deleteTest_with_emptyRepo=======\n");
    //given
    prepare_ServiceWith_noStudent();

    //when
    bool res = deleteById_studentService(&service, 0);

    //then
    printf("total amount = %d\n", count_studentService(service));    //assertThat.isEqualTo(0);    
    printf("res= %s\n", res ? "true" : "false");            //assertThat.isFalse();
}

void deleteTwoStudentAndPrintTest(){
    printf("\n=======deleteTwoStudentAndPrintTest=======\n");
    //given
    prepare_ServiceWith_fullRepo();
    
    printf("before deletion\n");
    printTree_studentService(service);

    //when
    deleteById_studentService(&service,0);
    deleteById_studentService(&service,3);

    //then
    printf("after deletion\n");
    printTree_studentService(service);
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
    printTree_studentService(service);
    }

/**
 * 예외 검증
 * full Repo일때 삽입 Test
 *      -> full -> return false!
* */
void insertOneTest_with_fullRepo(){
    printf("\n=======insertOneTest_with_fullRepo=======\n");
    //given
    prepare_ServiceWith_fullRepo();

    //when
    student suzy = create_student(2012000000,"배수지","건축학");
    unsigned int res = insertOne_studentService(&service, suzy);
    //then
    printf("res= %u\n", res);            //assertThat(res).isEqaulTo(4294967295);
}


void idGenerationPolicyTest(){
    printf("\n=======idGenerationPolicyTest=======\n");
    //given
    prepare_ServiceWith_fullRepo();
    
    //when
    deleteById_studentService(&service,0);
    deleteById_studentService(&service,3);

    student logitech = create_student(2016333333,"로지텍","건축학");
    student yangkees = create_student(2012001234,"양키즈","건축학");

    insertOne_studentService(&service,logitech);
    insertOne_studentService(&service,yangkees);

    //then
    student id_0 = findById_studentService(service, 0);
    student id_3 = findById_studentService(service, 3);

    printf("%s",toStringStudent(id_0));     //assertThat(id_0).isEqualTo(logitech);
    printf("%s",toStringStudent(id_3));     //assertThat(id_3).isEqualTo(yangkees);
}

int main(){
    /**
     * 램덤 생성
    **/
    RandomGenearionTest();
    
    /**
     * 정상 CRUD Logic Test
    **/
    findByIdTest();
    findAllTest_withTwoStudent();
    findAllTest_withFullStudent();
    deleteByIdTest();
    deleteTwoStudentAndPrintTest();

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
     * 예외 검증
     * full Repo일때 삽입 Test
    * */
    insertOneTest_with_fullRepo();

    /**
     * Id generation policy Test
    * */
    idGenerationPolicyTest();


}