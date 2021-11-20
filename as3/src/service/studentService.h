#ifndef STUDENTSERVICE_H__
#define STUDENTSERVICE_H__

#include "..\repository\studentRepository.h"
#include "..\model\total_info_model.h"

struct _studentService{
    studentRepo repo;
};
typedef struct _studentService studentService;

/*public*/
extern studentService defaultStudentService(int numStudent, int numFull);
extern void printTree_studentService(studentService service);
extern void print_treeInfo_studentService(studentService service);

extern student* create_student_randomArray(studentService service, int size);
extern unsigned int insertOne_studentService(studentService * service, student one);
extern student findById_studentService(studentService service, unsigned int id);
extern bool deleteById_studentService(studentService * service, unsigned int id);
extern int count_studentService(studentService service);
extern student findByStudentId(studentService service, unsigned int student_id);

extern student * findAll_studentService(studentService service);
extern void setModelTwoStudentCnt( model2 * model,studentService service);

extern void print_allStudent(studentService service);


#endif /* STUDENTSERVICE_H__*/
