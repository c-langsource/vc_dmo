#include "constructs.h"
#include <stdio.h>
struct _Animial;
typedef struct _Animial Animial;

struct _Animial {
	int age;
	int weight;
	void(*eat)(Animial* this, const char * food);//就是虚函数，因为如果不是实现虚函数，直接type_method(this)就可以实现了
	void(*destruct)(Animial* this);//虚函数
};

//父类有一个没有实现就是抽象类，所有都没有实现 就是接口

void Animal_Eat(Animial* this, const char * food);
void AnimalDestruct(Animial* this);

Animial* AnimialConstruct(Animial* this, int age, int weight) {
	this->age = age;
	this->weight = weight;
	this->eat = Animal_Eat;
	this->destruct = AnimalDestruct;
	return this;
}


void Animal_Eat(Animial* this, const char * food) {

	printf("animal eat %s \n", food);
}

void AnimalDestruct(Animial* this) {
	printf("animal destory...  \n");
}


struct _Dog;
typedef struct _Dog Dog;

#define NAME_SIZE_LIMIT 30

//父类和子类的内存是，在一起的，释放上面，删除方面 行为是一致性的，只需要删除一次
struct _Dog {
	Animial base;
    char name[NAME_SIZE_LIMIT];
	void(*eat)(Dog* this, const char *food);
	void(*destruct)(Dog* this);
};

// 构造函数 也是一个过场函数，它可以控制过过场以内的资源生命周期，但是整个过场的控制，有系统控制
void DogEat(Dog* this, const char *food);
void DogDestruct(Dog* this);

Dog * DogConstruct(Dog *this,int age,int weight,const char *name) {
	AnimialConstruct((Animial*)this,age,weight);
	this->base.age = age;
	this->base.weight = weight;
	this->eat = DogEat;
	this->base.eat = DogEat;
	this->destruct = DogDestruct;
	return  this;

}


void DogEat(Dog* this, const char *food) {
	printf("dog is eating %s \n",food);
}

//不要在 析构函数里面，释放自己内存，因为 析构是 过程中的一个过场函数
void DogDestruct(Dog* this) {
	printf("dog this->name:%s  destroy \n",this->name);
}



//编译器做了拟合的作用，让你感觉是这样的

int main(int argc, const char *argvs[]) {
	Animial * a = NEW(Animial, 18, 65);
	a->eat(a, " milk");
	VIRTUAL_DELETE(a);
	a =(Animial *) NEW(Dog, 10, 20, "wenweiping");

	a->eat(a,"dog bone");

	VIRTUAL_DELETE(a);


	getchar();
	return 0;
}













