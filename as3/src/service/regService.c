#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "regService.h"
#include "../util/utils.h"
#include "../model/models.h"


/*studentService, clazzService -> clazzRepo 
 *generate and save methods*/
void setStudentService(regService * service, studentService student_service){
    service->student_service=student_service;
}

void setClazzService(regService * service, clazzService clazz_service){
    service->clazz_service=clazz_service;
}

void shuffle_clazz(clazz *array, size_t n)
{   
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          clazz t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

float get_random_credit(){
    return ((float)(rand()%10))/2;
}

void initRegService(regService * service){
    // Student Service와 Clazz Service를 이용해서
    // 이용가능한 학생 및 수업 정보 조회
    int numStudent = count_studentService(service->student_service);
    int numClazz = count_clazzService(service->clazz_service);

    student * all_student = findAll_studentService(service->student_service);
    clazzApi api = findAllGroupByYearandSemester_clazzService(&service->clazz_service);

    //조회 데이터로 random하게 register 정보 생성 후 저장
    for(int s = 0; s <numStudent; s++){
        int student_id_primary_key = all_student[s].id;
        int student_id = all_student[s].student_id;
        
        int y = (student_id-2010*1000000)/1000000 + 2010;
        for(int idx = 0 ; idx<24; idx++){
            int num_lectures = api.data[idx].size;
            
            clazz* lectures = api.data[idx].data;
            shuffle_clazz(lectures,num_lectures);
            
            int h = rand()%38;
            int target_amount = h<1?3:
                                h<3?4:
                                h<6?5:
                                h<21?6:7;


            int num_take_clazz = target_amount<=num_lectures?target_amount:num_lectures;
            for(int t = 0 ; t <num_take_clazz ; t++){
                insertOne_regService(service,create_reg(student_id_primary_key,lectures[t].id,get_random_credit()));
            }
        }
    }
    
}

regService defaultRegService(studentService student_service){
    regService service;
    service.repo = create_regRepo(10000);
    setClazzService(&service,defaultClazzService(2018,2021));
    setStudentService(&service,student_service);
    initRegService(&service);
    return service;
}

/*regRepo only*/
void printTree_regService(regService service){
    printTree_regRepo(service.repo);
}

unsigned int insertOne_regService(regService * service, reg one){
    return insertOne_regRepo(&service->repo,one);
}

reg findById_regService(regService service, unsigned int id){
    return findById_regRepo(service.repo,id);
}

bool deleteById_regService(regService * service, unsigned int id){
    return deleteById_regRepo(&service->repo,id);
}

int count_regService(regService service){
    return count_regRepo(service.repo);
}

// 아래 method의 도우미
regApi findAll_wherestudentIdIsGiven_regService(regService service, int student_id){
    return findAll_wherestudentIdIsGiven_regRepo(service.repo,student_id);
}

/* 학기별 성적 조회 */
// Method의 책임 :
// year, semester를 통해 주어진 학생의 수강 정보 조회 및 정리 후 model에 담아 제공 
// (reg, clazz, course) Class의 협력
// step1. find all reg for given student
// step2. loop clazz and find the info of the clazz and list of course_id
// step3. loop clazz and find all course where course_id is given
// model 1 생성 
model1 singleSemester_model1_query(regService service,student s, int year, short semester){
    model1 model;
    
    //step 1!
    regApi rapi = findAll_wherestudentIdIsGiven_regService(service, s.id);

    //요청한 학기만 찾으면 됨
    model.size = 1;
    model.data = (semRegInfo *)malloc(sizeof(semRegInfo)*1);
    model.credit_sum = 0;
    model.score_sum = 0.0;
    semRegInfo sri;
    sri.year = year;
    sri.semester= semester;
    //step 2
    int regSize = rapi.size;
    regInfo * temp = (regInfo *) malloc(sizeof(regInfo)*regSize);
    
    int idx =0;
    for(int r = 0 ; r < regSize; r++){
        clazz c = findById_clazzService(service.clazz_service, rapi.data[r].clazz_id);
        if(c.year==year && c.semester==semester){
            temp[idx] = create_regInfo(rapi.data[r].id,c.course_id,year,semester,c.prof,rapi.data[r].credit);
            idx++;
        }
    }

    //이제 총 return할 reg의 개수가 결정됨
    // 실제 반환 객체 생성후 temp에서 옴김 temp는 free해줌
    int cnt = idx;
    sri.count = cnt;
    regInfo * ri = (regInfo *) malloc(sizeof(regInfo)*cnt);
    for(int i = 0 ; i < cnt ; i++){
        ri[i] = temp[i];
    }
    free(temp);
    
    //step 3
    //정리한 regInfo를 이용해서 clazz와 course의 외래키인 course_id를 이용해서
    //조회 후 정보 채워 넣기 (course_name, course_major, course_credit)
    sri.credit_sum = 0;
    sri.score_sum = 0.0;
    for(int i = 0 ; i < cnt ; i++){
        course c = findByCourseId_courseService(service.clazz_service.couser_service, ri[i].course_id);
        short credit = c.credit;
        sri.credit_sum += credit;
        sri.score_sum += credit * ri[i].score;
        model.credit_sum +=credit;
        model.score_sum += credit * ri[i].score;

        setCourseInfos(&ri[i],c.name,c.major,credit);
    }
    sri.infos = ri;

    //model에 담기
    model.data[0] = sri;
    model.num_reg = cnt;

    return model;
}


/* 학생의 전체 reg 조회*/
// 전체 regInfo를 정리 한 이후에 정렬 하는것이 좋겠지만
// 최적화는 생략하고... 위의 함수를 재활용하겠습니다.
model1 entireSemester_model1_query(regService service,student stu){
    model1 out;
    out.credit_sum = 0;
    out.score_sum = 0.0;
    
    int year = stu.student_id/1000000;
    short semester = 1;

    int numSemester = (2021-year+1)*2;
    out.size =numSemester;
    out.data = (semRegInfo*)malloc(sizeof(semRegInfo)*numSemester);

    for(int y = year ; y<=2021; y++){
        for(int s = semester ; s<=2; s++){
            model1 model_for_specific_semester = singleSemester_model1_query(service,stu,y,s);

            int idx= 2*(y-year) + (s-1);
            out.data[idx] = model_for_specific_semester.data[0];
            out.num_reg += model_for_specific_semester.num_reg;

            out.credit_sum+=model_for_specific_semester.credit_sum;
            out.score_sum+=model_for_specific_semester.score_sum;
        }
    }

    return out;
}

/*강의 ID별 삭제*/
//년도,학기별로 먼저 조회후 courseId에 대해서는 단순 loop를 하는 것으로 구현하였습니다.
//return : 삭제여부
bool delete_regByCourseId(regService service,student stu, char * courseId, int year, short semester){
    bool found = false;
    model1 model = singleSemester_model1_query(service,stu,year,semester);
    semRegInfo sri = model.data[0];
    regInfo ri;
    int num_reg = model.num_reg;
    
    for(int i = 0 ; i < num_reg ; i++){
        char * foundCourseId = sri.infos[i].course_id;
        if(isEqualString(courseId,foundCourseId)){
            ri = sri.infos[i];
            found = true;
            break;
        }
    }
    if(!found){
        return false;
    }
    unsigned int foundRegId = ri.reg_id;

    //무조건 true 여야합니다.
    return deleteById_regService(&service, foundRegId);
}

/* stu와 관련된 모든 reg정보 삭제 */
// 학생의 전체 reg 조회 method를 재활용하여 구현하였습니다.
void deleteAllRegs_relatedToStudent(regService service,student s){
    model1 model = entireSemester_model1_query(service, s);

    int num_semester = model.size;
    for(int i = 0 ; i < num_semester ; i++){
        semRegInfo sri = model.data[i];
        for(int r = 0 ;r < sri.count; r++){
            regInfo ri = sri.infos[r];
            deleteById_regService(&service, ri.reg_id);
        }
    }
}

// 모든 학생의 gpa를 조사하여 단순 평균을 내립니다.
// 역시 reg와 clazz, course service의 협력으로 최적화 할 수 있습니다.
void setModelTwoTotalGPA(model2 * model,regService service, student * students, int size){
    float totalGpa = 0 ;
    for(int i = 0 ; i < size ; i++){
        student s = students[i];
        
        model1 model_one = entireSemester_model1_query(service, s);
        totalGpa += model_one.score_sum/model_one.credit_sum;
    }
    model->totalGpa = totalGpa/size;
} 