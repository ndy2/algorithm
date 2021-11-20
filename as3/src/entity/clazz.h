#ifndef CLAZZ_H__
#define CLAZZ_H__

struct clazz{
    unsigned int id;
    int year;
    short semester;
    char course_id[20];
    char prof[20];
};
typedef struct clazz clazz;

extern char * toStringClazz(clazz c);
extern clazz create_clazz(int year, short semester, char * course_id, char * prof);
extern clazz create_dummyClazz();


struct _clazzDto{
    int size;
    clazz * data;
};
typedef struct _clazzDto clazzDto;

struct _clazzApi{
    clazzDto * data;
};
typedef struct _clazzApi clazzApi;


#endif /* CLAZZ_H__*/
