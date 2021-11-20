#ifndef REGSERVICE_H__
#define REGSERVICE_H__

#include "..\repository\regRepository.h"
#include "studentService.h"
#include "clazzService.h"
#include "..\model\models.h"

struct _regService{
    regRepo repo;

    studentService student_service;
    clazzService clazz_service;
};
typedef struct _regService regService;

/*public*/
extern regService defaultRegService(studentService student_service);

extern void printTree_regService(regService service);
extern unsigned int insertOne_regService(regService * service, reg one);
extern reg findById_regService(regService service, unsigned int id);
extern bool deleteById_regService(regService * service, unsigned int id);
extern int count_regService(regService service);

extern model1 singleSemester_model1_query(regService service,student s, int year, short semester);
extern model1 entireSemester_model1_query(regService service,student stu);
extern bool delete_regByCourseId(regService service,student stu, char * courseId, int year, short semester);
extern void deleteAllRegs_relatedToStudent(regService service,student s);

extern void setModelTwoTotalGPA(model2 * model,regService service, student * students, int size);



#endif /* REGSERVICE_H__*/
