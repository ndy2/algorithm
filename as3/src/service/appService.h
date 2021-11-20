#ifndef APPSERVICE_H__
#define APPSERVICE_H__

#include "studentService.h"
#include "regService.h"
#include "..\model\models.h"

struct _appService{
    //client
    authentication a;
    char * path;

    //server
    studentService stduent_service;
    regService regService;

};

typedef struct _appService appService;

extern void initApp(appService * app);
extern void run(appService * app);

#endif /* APPSERVICE_H__*/
