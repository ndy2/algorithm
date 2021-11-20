#ifndef REG_H__
#define REG_H__

struct _register{
    unsigned int id;
    unsigned int student_id;
    unsigned int clazz_id;
    float credit;
};
typedef struct _register reg;

extern char * toStringReg(reg c);
extern reg create_reg(unsigned int student_id, unsigned int clazz_id, float credit);
extern reg create_dummyReg();



typedef struct _register_Api{
    int size;
    reg* data;
}regApi;


#endif /* REG_H__*/
