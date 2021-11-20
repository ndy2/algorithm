#ifndef TREEINFO_H__
#define TREEINFO_H__

typedef struct _treeInfo{
    unsigned int rootId;
    int leafCnt;
    unsigned int * leafIds;
    int height;
}treeInfo;

extern void print_treeInfo(treeInfo ti, char * title);

#endif /* TREEINFO_H__*/
