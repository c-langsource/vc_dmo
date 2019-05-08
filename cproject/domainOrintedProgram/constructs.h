#ifndef __CONSTRUCT__H__
#define __CONSTRUCT__H__

#include <stdlib.h>
#include <memory.h>

//## 运行在编译期
//#是文本替换，代码运行期间

static void * myallocfun(int size) {
	void * o = NULL;
	do {
		o = malloc(size);
	} while (o == NULL);
	memset(o, 0, size);
	return o;
}

#define myalloc(type)\
	    myallocfun(sizeof(type))

#ifdef _WIN32

#define NEW(type,...)\
		type##Construct((type*)myalloc(type),##__VA_ARGS__)

#elif _WIN64
#define NEW(type,...)\
	type##Construct((type*)myalloc(type),##__VA_ARGS__)

#elif __linux__
#define NEW(type,...)\
({\
	type * o = myallocfun(sizeof(type));\
	type##Construct(o,##__VA_ARGS__);、
	o; \
	})

#elif __unix__
#define NEW(type,...)\
({\
	type * o = myallocfun(sizeof(type));\
	type##Construct(o,##__VA_ARGS__);\
	o;\
})	

#endif

#define VIRTUAL_DELETE(ptr)\
	if (ptr!=0){\
	    ptr->destruct(ptr);\
	}\
	free(ptr);\
	ptr = 0;



 

#endif




