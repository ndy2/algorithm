#include <stdio.h>
#include <stdlib.h>

#include "..\src\service\regService.h"

regRepo repo;
regService service;

//Before Each
void prepare_ServiceWith_twoReg(){
    //given
    repo.t = create_regTree(60);

    service.repo = repo;

    reg B0 = create_reg(1,2,3.0);
    reg AP = create_reg(1,2,4.5);
    
    insertOne_regService(&service, B0);
    insertOne_regService(&service, AP);
}
void prepare_ServiceWith_noReg(){
    //given
    repo.t = create_regTree(60);
    service.repo = repo;
}
void prepare_defaultRegService(){
    //given
    service = defaultRegService();
}

/**
 * Api integration test
 * */
void apiInitilizationTest(){
    //given
    prepare_defaultRegService();

    //then - 2000 개 정도 등록되면 성공
    int size = count_regService(service);
    printf("all register count = %d\n", size);
}


/**
 * 정상 CRUD Logic Test
**/
void findByIdTest(){
    printf("\n=======findByIdTest=======\n");
    //given
    prepare_ServiceWith_twoReg();
    //when

    //then
    reg B0 = findById_regService(service,0);
    reg AP = findById_regService(service,1);

    printf("%s",toStringReg(B0));         //assertThat.isEqualTo(B0);
    printf("%s",toStringReg(AP));       //assertThat.isEqualTo(AP);
}

void deleteByIdTest(){
    printf("\n=======deleteByIdTest=======\n");
    //given
    prepare_ServiceWith_twoReg();

    //when
    //delete 김교수 강의 two times
    bool res_firstDelete = deleteById_regService(&service, 0);
    bool res_secondDelete = deleteById_regService(&service, 0);

    //then
    printf("total amount after deletion = %d\n", count_regService(service));    //assertThat.isEqualTo(1);    
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
    prepare_ServiceWith_noReg();

    //when
    reg found = findById_regService(service,0);

    //then
    printf("%s",toStringReg(found)); //assertThat(found.name).isEqualTo("noReg");
}

void deleteTest_with_emptyRepo(){
    printf("\n=======deleteTest_with_emptyRepo=======\n");
    //given
    prepare_ServiceWith_noReg();

    //when
    bool res = deleteById_regService(&service, 0);

    //then
    printf("total amount = %d\n", count_regService(service));    //assertThat.isEqualTo(0);    
    printf("res= %s\n", res ? "true" : "false");            //assertThat.isFalse();
}

void deleteTwoRegAndPrintTest(){
    printf("\n=======deleteTwoRegAndPrintTest=======\n");
    //given
    prepare_defaultRegService();
    
    printf("before deletion\n");
    printf("size : %d\n", count_regService(service));
    //when
    deleteById_regService(&service,0);
    
    deleteById_regService(&service,3);
    
    //then
    printf("after deletion\n");
    printf("size : %d\n", count_regService(service));
}


/**
 * printTree Test
* */

void printTest_with_defaultRepo(){
    printf("\n=======printTest_with_defaultRepo=======\n");
    //given
    prepare_defaultRegService();
    int repoSize = (2021-2010)*2*8;
    //when

    //then -> repoSize size  의 대략 70퍼센트 정도의 과목이 생성되어있다면 성공
    for(int i = 0 ; i < repoSize ; i++){
        printf("%d :  %s",i, toStringReg(findById_regService(service,i)));
    }
    }

/**
 * 예외 검증
 * full Repo일때 삽입 Test
 *      -> full -> return false!
* */
void insertOneTest_with_defaultRepo(){
    printf("\n=======insertOneTest_with_defaultRepo=======\n");
    //given
    prepare_defaultRegService();
    int size = count_regService(service);

    //when
    reg BP = create_reg(1,7,3.5);
    unsigned int res = insertOne_regService(&service, BP);

    //then
    printf(res==size?"true":"false");            //assertThat(res).isEqaulTo(size);
}


void idGenerationPolicyTest(){
    printf("\n=======idGenerationPolicyTest=======\n");
    //given
    prepare_defaultRegService();
    
    //when
    deleteById_regService(&service,0);
    deleteById_regService(&service,3);
    
    reg B0 = create_reg(1,7,3.0);
    reg BP = create_reg(1,8,3.5);

    insertOne_regService(&service,B0);
    insertOne_regService(&service,BP);

    //then
    reg id_0 = findById_regService(service, 0);
    reg id_3 = findById_regService(service, 3);

    printf("%s",toStringReg(id_0));     //assertThat(id_0).isEqualTo(logitech);
    printf("%s",toStringReg(id_3));     //assertThat(id_3).isEqualTo(yangkees);
}

void singleSemester_model1_query_test(){
    //given
    prepare_defaultRegService();
    
    //억지로 student 객체 생성 후 test
    student dy = create_student(2016310703,"남득윤","수학과");
    dy.id=30;

    //when
    model1 model = singleSemester_model1_query(service,dy,2018,2);

    //then
    int numSemester = model.size;
    for(int i = 0 ; i < numSemester; i++){
       semRegInfo ith_semester_regInfos =  model.data[i];

       int num_register = ith_semester_regInfos.count;
       for(int r = 0 ; r < num_register; r++){
           regInfo ri = ith_semester_regInfos.infos[r];
           printf("%s",toStringRegInfo(ri));
       }
    }
    
}

int main(){
    /**
     * 정상 CRUD Logic Test
    **/
    // findByIdTest();
    // deleteByIdTest();
    // deleteTwoRegAndPrintTest();

     /**
     * 출력 Test
    * */
    // printTest_with_defaultRepo();


    /**
     * 예외 검증
     * empty Repo일때 CRUD Test
     * */
    // findByIdTest_with_emptyRepo();
    // deleteTest_with_emptyRepo();

    /**
     * defaultRepo 삽입 Test
    * */
    // insertOneTest_with_defaultRepo();

    /**
     * Id generation policy Test
    * */
    // idGenerationPolicyTest();

    /**
     * Api를 활용한 초기화 Test
     * 
     **/
    // apiInitilizationTest();


    /**
     * reg -> clazz -> course query test
     **/
    singleSemester_model1_query_test();
}