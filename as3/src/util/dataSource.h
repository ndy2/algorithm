#ifndef DATASOURCE_H__
#define DATASOURCE_H__

extern char * get_random_student_name();
extern char * get_random_major();


/* course Api */
struct _courseDto{
    char course_id[20];
    char name[20];
    char major[20];
    short credit;
};
typedef struct _courseDto courseDto;


struct _courseApi{
    courseDto * data;
    int size;
};
typedef struct _courseApi courseApi;

extern courseApi get_all_available_courseDto();


#endif /* DATASOURCE_H__*/