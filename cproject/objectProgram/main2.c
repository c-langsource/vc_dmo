#include "baseo.h"
#include <stdio.h>


struct _Animal;
typedef struct _Animal Animal;


struct _Animal {
	int age;
	int weight;

	void(*eat)(Animal*this, const char *food);
	void(*destruct)(Animal*this);

};


void AnimalEat(Animal*this, const char *food);
void  AnimalDestruct(Animal*this);

Animal* AnimalConstruct(Animal * this, int age, int weight) {
	this->age = age;
	this->weight = weight;
	this->eat = AnimalEat;
	this->destruct = AnimalDestruct;
	return this;
}


void AnimalEat(Animal*this, const char *food)
{
	printf("animal eat %s \n", food);
}

void  AnimalDestruct(Animal*this) {
	printf("animal 释放了。。。。 \n");

}

struct _Dog;
typedef struct _Dog Dog;
struct _Dog {
	Animal base;
	char name[30];
};
void DogEat(Dog*this, const char *name);
void DogDestruct(Dog* this);

Dog * DogConstruct(Dog *this, int age, int weight) {
	this->base.age = age;
	this->base.weight = weight;
	this->base.eat = DogEat;
	this->base.destruct = DogDestruct;
	return this;
}
void DogDestruct(Dog* this)
{
	//release self


	//release partnet
	AnimalDestruct((Animal*)this);
	printf("Dog 释放函数 \n");
}
void DogEat(Dog*this, const char *name)
{
	printf("Dog eat %s \n", name);
}

int main(int argc, char const *argv[]) {
	Animal *a = NEW(Animal, 10, 20);
	a->eat(a, "milk");
   // a->destruct(a);

	// Dog *dog = NEW(Dog,10,50);

	// a = (Animal*)dog;

	// a->eat(a,"dog food");

   //  a->destruct(a);
	VIRTUAL_DELETE(a);
	getchar();
	return 0;
}
