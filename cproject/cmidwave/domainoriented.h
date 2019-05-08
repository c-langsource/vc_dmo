#ifndef __DOMAIN_ORIENTED_H
#define __DOMAIN_ORIENTED_H

#include <stdlib.h>
#include <string.h>


#ifdef _WIN32 || _WIN64

static void* myalloc(int size) {
	void * o = NULL;
	do {
		o = malloc(size);
	} while (o!=NULL);
	memset(o, 0, size);
	return o;
}



#define NEW(type,...)\
	type##Construct((type*)myalloc(sizeof(type)),##__VA_ARGS__)

#elif __linux__ || __unix__
#define NEW(type,...)\
({\
	void * o = myalloc(sizeof(type));\
	type##Construct((type*)o,##__VA_ARGS__);\
	o;\
})
#endif

#define VIRTUAL_DELETE(ptr)\
{\
if (ptr!=0){\
	ptr->destruct(ptr);\
	free(ptr);\
	ptr = 0;\
		}\
}

#endif