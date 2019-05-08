#ifndef __BASEO__H__
#define __BASEO__H__
#include <string.h>
#include <stdlib.h>

#ifdef  _WIN32
#define NEW(type,...)\
type##Construct(malloc(sizeof(type)),##__VA_ARGS__)

#elif __linux__ ||  __unix__
#define NEW(type,args...)\
({\
     type * o = (type*) malloc(sizeof(type));\
     memset((void*)o,0,sizeof(type));\
     o;\
})
#endif

#define VIRTUAL_DELETE(ptr) \
   if (ptr!=NULL)\
   {\
       ptr->destruct(ptr);\
       ptr=0;\
   }

#endif
