#include <stdio.h>
#include <stdlib.h>

#include "..\src\service\clazzService.h"

clazzRepo repo;
clazzService service;

//Before Each
void prepare_ServiceWith_twoClazz(){
    //given
    repo.t = create_clazzTree(60);

    service.repo = repo;

    clazz sw_kim = create_clazz(2016,1,"SWE1234","김교수");
    clazz sw_lee = create_clazz(2012,2,"SWE8888","이교수");
    insertOne_clazzService(&service, sw_kim);
    insertOne_clazzService(&service, sw_lee);
}
void prepare_ServiceWith_noClazz(){
    //given
    repo.t = create_clazzTree(60);
    service.repo = repo;
}
void prepare_ServiceWith_defaultRepo(){
    //given
    service = defaultClazzService(2010,2021);
}



/**
 * 정상 CRUD Logic Test
**/
void findByIdTest(){
    printf("\n=======findByIdTest=======\n");
    //given
    prepare_ServiceWith_twoClazz();
    //when

    //then
    clazz sw_kim = findById_clazzService(service,0);
    clazz sw_lee = findById_clazzService(service,1);

    printf("%s",toStringClazz(sw_kim));         //assertThat.isEqualTo(dy);
    printf("%s",toStringClazz(sw_lee));       //assertThat.isEqualTo(suzy);
}

void deleteByIdTest(){
    printf("\n=======deleteByIdTest=======\n");
    //given
    prepare_ServiceWith_twoClazz();

    //when
    //delete 김교수 강의 two times
    bool res_firstDelete = deleteById_clazzService(&service, 0);
    bool res_secondDelete = deleteById_clazzService(&service, 0);

    //then
    printf("total amount after deletion = %d\n", count_clazzService(service));    //assertThat.isEqualTo(1);    
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
    prepare_ServiceWith_noClazz();

    //when
    clazz found = findById_clazzService(service,0);

    //then
    printf("%s",toStringClazz(found)); //assertThat(found.name).isEqualTo("noClazz");
}

void deleteTest_with_emptyRepo(){
    printf("\n=======deleteTest_with_emptyRepo=======\n");
    //given
    prepare_ServiceWith_noClazz();

    //when
    bool res = deleteById_clazzService(&service, 0);

    //then
    printf("total amount = %d\n", count_clazzService(service));    //assertThat.isEqualTo(0);    
    printf("res= %s\n", res ? "true" : "false");            //assertThat.isFalse();
}

void deleteTwoClazzAndPrintTest(){
    printf("\n=======deleteTwoClazzAndPrintTest=======\n");
    //given
    prepare_ServiceWith_defaultRepo();
    
    printf("before deletion\n");
    printf("size : %d\n", count_clazzService(service));
    //when
    deleteById_clazzService(&service,0);
    
    deleteById_clazzService(&service,3);
    
    //then
    printf("after deletion\n");
    printf("size : %d\n", count_clazzService(service));
}


/**
 * printTree Test
* */

void printTest_with_defaultRepo(){
    printf("\n=======printTest_with_defaultRepo=======\n");
    //given
    prepare_ServiceWith_defaultRepo();
    int repoSize = (2021-2010)*2*8;
    //when

    //then -> repoSize size  의 대략 70퍼센트 정도의 과목이 생성되어있다면 성공
    for(int i = 0 ; i < repoSize ; i++){
        printf("%d :  %s",i, toStringClazz(findById_clazzService(service,i)));
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
    prepare_ServiceWith_defaultRepo();
    int size = count_clazzService(service);

    //when
    clazz math_park = create_clazz(2012,2,"MTH7777","박교수");
    unsigned int res = insertOne_clazzService(&service, math_park);

    //then
    printf(res==size?"true":"false");            //assertThat(res).isEqaulTo(size);
}

 /**
 * Id generation policy Test
* */
void idGenerationPolicyTest(){
    printf("\n=======idGenerationPolicyTest=======\n");
    //given
    prepare_ServiceWith_defaultRepo();
    
    //when
    deleteById_clazzService(&service,0);
    deleteById_clazzService(&service,3);

    clazz math_park = create_clazz(2012,1,"MTH7777","박교수");
    clazz ged_choi = create_clazz(2012,2,"CED1234","최교수");

    insertOne_clazzService(&service,math_park);
    insertOne_clazzService(&service,ged_choi);

    //then
    clazz id_0 = findById_clazzService(service, 0);
    clazz id_3 = findById_clazzService(service, 3);

    printf("%s",toStringClazz(id_0));     //assertThat(id_0).isEqualTo(logitech);
    printf("%s",toStringClazz(id_3));     //assertThat(id_3).isEqualTo(yangkees);
}

void printClazzDto(clazzDto dto){
    printf("size : %d\n", dto.size);
    for(int i = 0 ; i < dto.size; i++){
        printf("%s", toStringClazz(dto.data[i]));
    }
}

/**
 * clazz Dto Test - 
* */
void clazzDtoTest(){
    //given
    prepare_ServiceWith_defaultRepo();

    //when
    clazzDto dto = findAllClazzWhereYearAndSemesterGiven_clazzRepo(service.repo,2016,1);

    //then -> expected out put is as below
    printClazzDto(dto);
    // size : 6
    // 71, 2016, 1, ZOO1234, 이교수
    // 67, 2016, 1, ARC1234, 김교수
    // 66, 2016, 1, MTH1234, 이교수
    // 69, 2016, 1, BOT9876, 김교수
    // 68, 2016, 1, PHY2345, 김교수
    // 70, 2016, 1, ZOO7777, 김교수
}

void clazzApiTest(){
    //given
    prepare_ServiceWith_defaultRepo();

    //when
    clazzApi api = findAllGroupByYearandSemester_clazzService(&service);

    //then
    printf("2010 spring clazz");
    printClazzDto(api.data[0]);
    printf("2021 fall clazz");
    printClazzDto(api.data[21]);
}

int main(){
    /**
     * 정상 CRUD Logic Test
    **/
    // findByIdTest();
    // deleteByIdTest();
    // deleteTwoClazzAndPrintTest();

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
     * clazz Dto, Api Test - 
    * */
    // clazzDtoTest();
    clazzApiTest();
}