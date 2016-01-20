#include "object-mult.h"

#include <stdio.h>
 
/* Тело структуры опять объявлена внутри Си-файла, поэтому её содержимое 
 * скрыто от стороннего кода */ 
struct Object_ContextRealization {
	int mult;
};

/* Методы должны быть объявлены как static, чтобы не мешаться в общей области 
 * видимости. Связываются они всё равно через указатели */
static int method(ObjectContext *c, int a) {
	printf("%d * %d", a, c->mult);
	return a * c->mult;
}

static void release(ObjectContext *c) {
	printf("object-mult(%d) released\n", c->mult);
}

/* в ООП терминах функция objectMultCreate наиболее близка к фабрике типов, но 
 * не конструктору */
extern Object* objectMultCreate(int mult) {
	Object *o;
	ObjectContext *c;
	o = objectCreate(&c, sizeof(ObjectContext), method, release);
	if (NULL != o) {
		c->mult = mult;
	}
	return o;
}
