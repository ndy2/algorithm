#include "viewTemplate.h"

#include <stdio.h>
#include <stdlib.h>
void setView(viewTemplate * view, char * name, int numLines, int cntOptions){
    view->name = name;
    view->numLines = numLines;
    view->cntOptions = cntOptions;
    view->contnent = (char**)malloc(sizeof(char*)*(numLines));
}


void addContent(viewTemplate * view, int lineNum, char *line){
    view->contnent[lineNum] = line;
}

void renderView(viewTemplate view){
    for(int l = 0 ; l <view.numLines ; l++){
        printf("%s\n",view.contnent[l]);
    }
    printf("\n");
}
