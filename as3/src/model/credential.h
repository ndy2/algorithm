#ifndef CREDENTIAL_H__
#define CREDENTIAL_H__


#include <stdbool.h>
#include "../entity/student.h"

struct _credential{
    bool valid;
};
typedef struct _credential credential;

struct _authentication{
    credential c;
    student user;
};
typedef struct _authentication authentication;

extern credential create_credential(bool valid);
extern authentication create_authentication(credential c, student s);


#endif /* CREDENTIAL_H__*/
