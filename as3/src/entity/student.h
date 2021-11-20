#ifndef STUDENT_H__
#define STUDENT_H__

struct student{
    unsigned int id;
    unsigned int student_id;
    char name[20];
    char major[20];
};
typedef struct student student;

extern char * toStringStudent(student stdu);
extern student create_student(unsigned int student_id, char * name, char * major);
extern student create_dummyStudent();

#endif /* STUDENT_H__*/
