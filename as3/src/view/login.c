#include "index.h"

#include <stdio.h>

viewTemplate loginView(authentication a){

    viewTemplate view;
    
    setView(&view,"login", 2,0);
    addContent(&view,0, "-------------------");
    addContent(&view,1, "-type your id :");
    
    return view;
}