
#if 0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS 1

typedef struct _Animal  Animal;


//C89 C99 C11 c的官方标准  ,GNU  MS 特殊化的标准
//和这个是GNU的标准

#ifdef _WIN32
#define NEW11(type,...)\
     type##Construct(malloc(sizeof(type)),__VA_ARGS__);
#ifdef _WIN64
   //define something for Windows (64-bit only)
#else
   //define something for Windows (32-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
	 // iOS Simulator
#elif TARGET_OS_IPHONE
	// iOS device
#elif TARGET_OS_MAC
	// Other kinds of Mac OS
#else
#   error "Unknown Apple platform"
#endif
#elif __ANDROID__
	// android
#elif __linux__
#define NEW(type,...)\
	({\
		  type * o = (type*) malloc(sizeof(type));\
		  type##Construct(o,__VA_ARGS__);\
		  o;\
		})
#elif __unix__ // all unices not caught above
	#define NEW(type,...)\
	({\
		  type * o = (type*) malloc(sizeof(type));\
		  type##Construct(o,__VA_ARGS__);\
		  o;\
		})
#elif defined(_POSIX_VERSION)
	// POSIX
#else
#   error "Unknown compiler"
#endif





  

#define DELETE(type,ob)\
({\
        type##Destruct(ob);\
        free(ob);\
})

void inputExpressSentence(void* a,void* b ){
	
	
	
}


typedef struct _AnimalAnimal {
	//members
	int age;
	char name[30];
	int weight;

	//functions 有虚函数指针变量 就一定要有 析构函数！！！！
	void(*talk)(Animal * ani, const char *message);
	void(*destrcut)(Animal * ani);
}Animal;



void Animal_Talk_Impl(Animal * ani,const  char *message) {
	printf("name:%s ,say:%s \n",ani->name,message);
}

void AnimalDestruct(Animal *ani);

void * AnimalConstruct(Animal *ani,const char *name,int age,int weight) {
	ani->age = 0;
	ani->weight = 0;
	strcpy_s(ani->name,30, name);
	ani->talk = Animal_Talk_Impl;
	ani->destrcut = AnimalDestruct;

	return ani;
}

void AnimalDestruct(Animal *ani) {
	if (ani != NULL) {
		printf("释放了该：%s \n", ani->name);
		free(ani);
	}
	ani = NULL;
}

void AnimalSetAge(Animal * ani,int age) {
	ani->age = age;

}
void AnimalSetWeight(Animal * ani,int weight) {
	ani->weight = weight;
}




typedef struct _Dog Dog;
typedef struct _Dog {
	Animal base;
	char name[0];//这种方式一般都是定义在堆上面，一起释放嘛
}Dog;


int  DogConstruct(Dog * dog,int age,int weight) {
	AnimalConstruct((Animal*)dog,"dog:",age,weight);
}

void DogSetName(Dog* dog,const char *name) {


}

int mainxxxx(int argc,const char *argvs[]) {

	Animal *a = NEW11(Animal,"wenweiping",100,200);

	a->talk(a, "hello world....");
	a->destrcut(a);
	getchar();

	return  0;
}






#endif