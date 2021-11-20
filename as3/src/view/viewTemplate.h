#ifndef VIEWTEMPLATE_H__
#define VIEWTEMPLATE_H__

struct _viewTemplate{
    int numLines;
    int cntOptions;
    char **contnent;
    char * name;
};

typedef struct _viewTemplate viewTemplate;

extern void setView(viewTemplate * view,char * name, int numLines, int cntOptions);
extern void addContent(viewTemplate * view,int lineNum, char *line);
extern void renderView(viewTemplate view);

#endif /* VIEWTEMPLATE_H__*/
