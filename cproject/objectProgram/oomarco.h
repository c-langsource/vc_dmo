#ifndef  OO_H
#define OO_H

#define NEW(type)\
({\
    type * ob = (type*) malloc(sizeof(type));\
    type##Construct(ob);\
    ob;\
})


#define DELETE(type,ob)\
({\
   type##Destructor(ob);\
   free(ob);\
})


#endif // ! OO_H
