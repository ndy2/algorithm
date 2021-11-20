#include "appService.h"
#include "..\view\views.h"
#include "..\util\utils.h"

#include <stdio.h>

#define NILID 987654321

model1 glb_model_one;
model2 glb_model_two;

bool glb_delete_success;

viewTemplate dispatcher(char * path,authentication *a, model1 model_one, model2 model_two){
    //controller
    if(isEqualString(path,"/")){        
        return indexView(*a, model_two);
    }else if(isEqualString(path, "/login")){
        return loginView(*a);
    }else if(isEqualString(path, "/transcript-entire")){
        return transcript_entireView(*a,&model_one);
    }else if(isEqualString(path, "/transcript-request")){
        return transcript_semesterRequestView();
    }else if(isEqualString(path, "/transcript-semester")){
        return transcript_semesterView(*a,&model_one);
    }else if(isEqualString(path, "/delete-one-request")){
        return delete_oneRequestView();
    }else if(isEqualString(path, "/delete-one")){
        return delete_oneCompleteView(glb_delete_success);
    }else if(isEqualString(path, "/delete-all-request")){
        return delete_allRequestView(*a);
    }else{
        return indexView(*a,model_two);
    }
}

authentication authenticate(studentService service,unsigned int in){
    student found = findByStudentId(service,in);
    bool isValid = (found.id!=NILID);
    return create_authentication(create_credential(true), found);
}

bool isValidIn(unsigned int in, int cntOptions){
    return in>0&&in<=cntOptions;
}

void updateState(appService * app, int in){
    char * path = app->path;
    authentication a = app->a;

    if(isEqualString(path,"/")){
        if(!a.c.valid){
            if(in == 1){
                app->path = "/login";
            }else if(in ==2){
                exit(0);
            }
        }else{
            switch (in)
            {
            case 1:
                {
                    glb_model_one = entireSemester_model1_query(app->regService,a.user);
                    app->path = "/transcript-entire";
                    break;
                }
            case 2:
                app->path = "/transcript-request";
                break;
            case 3:
                app->path = "/delete-all-request";
                break;
            case 4:
                app->path = "/delete-one-request";
                break;
            //logout : reset authentication
            case 5:{
                student s;
                app->a.c.valid = false;
                break;
                }
            default:
                break;
            }
        }
    //뒤로 가기
    }else if(isEqualString(path,"/delete-all-request")){
        if(in==1){
            /*계정, reg전부 삭제*/
            deleteById_studentService(&app->stduent_service,a.user.id);
            deleteAllRegs_relatedToStudent(&app->regService,a.user);
            
            /* 변경된 tree 정보 출력*/
            print_treeInfo_studentService(app->stduent_service);
            print_treeInfo_regService(app->regService);

            /*계정정보 초기화 후 index로 이동*/
            app->a.c.valid = false;
            app->path = "/";

        }else if(in==2){
            app->path = "/";
        }
    }
    else {
        if(in==1){
            app->path = "/";
        }
    }
}

void setAuthentication(appService * app, authentication a){
    app->a=a;
}

void redirectTo(appService * app, char * path){
    app->path=path;
}
void initApp(appService * app){
    app->path="/";
    student s;
    app->a=create_authentication(create_credential(false), s);
    app->stduent_service =  defaultStudentService(100,120);
    app->regService =  defaultRegService(app->stduent_service);

    // initialization info print
    print_allStudent(app->stduent_service);
    print_treeInfo_studentService(app->stduent_service);
    print_treeInfo_regService(app->regService);
    print_treeInfo_clazzService(app->regService.clazz_service);
    print_treeInfo_courseService(app->regService.clazz_service.course_service);
}

void updateModelTwo(appService * app){
    setModelTwoStudentCnt(&glb_model_two,app->stduent_service);
    student * all = findAll_studentService(app->stduent_service);
    setModelTwoTotalGPA(&glb_model_two,app->regService,all,glb_model_two.studentCnt);
}

void run(appService * app){
    while(true){
        //view resolver
        char * path = app->path;
        authentication a = app->a;
        viewTemplate view = dispatcher(path,&a,glb_model_one, glb_model_two);
        
        renderView(view);

        if(isEqualString(path,"/transcript-request")){
            /*postMapping("/transcript-semester")*/
            int year_in,year;
            short semester;
            scanf(" %d", &year_in);
            year = year_in;
            scanf(" %d", &semester);
            if(a.user.student_id/1000000 <=year && year <=2021 && (semester ==1 || semester==2)){
                glb_model_one = singleSemester_model1_query(app->regService,a.user,year,semester);

                redirectTo(app,"/transcript-semester");
            }
        }
        else if(isEqualString(path,"/delete-one-request")){
            /*postMapping("/delete-one") */
            char courseId[7];
            int year_in,year;
            short semester;
            scanf("%s",courseId);
            scanf(" %d", &year_in);
            year = year_in;
            scanf(" %d", &semester);
            glb_delete_success = delete_regByCourseId(&app->regService,a.user,courseId,year,semester);
            if(glb_delete_success){
                print_treeInfo_regService(app->regService);
            }
            redirectTo(app,"/delete-one");
        }
        else if(isEqualString(path,"/login")){
            /*postMapping("/login") */
            unsigned int in;
            scanf(" %u", &in);
            authentication a = authenticate(app->stduent_service,in);
            if(a.c.valid){
                setAuthentication(app,a);
                redirectTo(app,"/");        
            }
        }
        else {
            /*postMapping("/index")*/
            /*postMapping for other pages -> 뒤로가기*/
            int option;
            scanf(" %d", &option);
            if(isValidIn(option, view.cntOptions)){
                updateState(app,option);
            }
        }

        updateModelTwo(app);
    }
}
