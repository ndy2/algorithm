#include <stdio.h>
#include <stdlib.h>

#include "service\appService.h"

appService app;

void runApp(){
    initApp(&app);
    run(&app);
}

int main(){
    runApp();
}