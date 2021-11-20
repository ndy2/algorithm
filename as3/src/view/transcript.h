#ifndef TRANSCRIPT_H__
#define TRANSCRIPT_H__

#include "viewTemplate.h"
#include "../model/models.h"

#include <stdio.h>

typedef struct _form1 form1;

extern viewTemplate transcript_allView(authentication a);
extern viewTemplate transcript_semesterRequestView();
extern viewTemplate transcript_semesterView(authentication a, model1 *model);
extern viewTemplate transcript_entireView(authentication a, model1* model);

#endif /* TRANSCRIPT_H__*/
