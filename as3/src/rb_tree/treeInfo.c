#include "treeInfo.h"
#include <stdio.h>

void print_treeInfo(treeInfo ti, char * title){
    printf("==================\n");
    printf("%s information \n",title);
    printf("root id : %d\n",ti.rootId);
    printf("tree height : %d\n", ti.height);
    printf("leaves count : %d\n", ti.leafCnt);
    printf("leaf ids : \n");
    for(int i = 0 ; i < ti.leafCnt; i++){
        printf("%d ",ti.leafIds[i]);
        if((i+1)%10==0) printf("\n");
    }
    printf("\n==================\n");
}