#include "credential.h"


credential create_credential(bool valid){
    credential c;
    c.valid = valid;
    return c;
}

authentication create_authentication(credential c, student s){
    authentication a;
    a.c = c;
    a.user = s;
    return a;
}
