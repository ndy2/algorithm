#include "../src/view/viewTemplate.h"

#include <stdio.h>

viewTemplate view;

void initView(){
    //given
    setView(&view,"index",5,2);
}

void viewRenderingTest(){
    //given
    initView();

    //when
    addContent(&view,0, "hello view");
    addContent(&view,1, "Its second Line");

    char line2[20];
    sprintf(line2, "formatting test! %d",3);
    addContent(&view,2, line2);

    char line3[20];
    sprintf(line3, "formatting test! %s","득윤");
    addContent(&view,3, line3);

    char line4[20];
    sprintf(line4, "formatting test! %s","하삼동");
    addContent(&view,4, line4);

    //then
    renderView(view);
}


int main(){
    viewRenderingTest();
}