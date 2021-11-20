#ifndef DELETE_H__
#define DELETE_H__

#include "..\model\credential.h"
#include "viewTemplate.h"

#include <stdio.h>

extern viewTemplate delete_oneRequestView();
extern viewTemplate delete_oneCompleteView(bool deleted);
extern viewTemplate delete_allRequestView(authentication a);

#endif /* DELETE_H__*/
