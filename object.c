#include "object.h"

#include <stdlib.h>
#include <assert.h>

/* В месте этого объявления содержимое структуры увязывается с ранее
 * объявленным Object. При этом, содержимое доступно только в object.c */
struct Object_ClosedRealization {
	int (*method)(ObjectContext *c, int a);
	void (*release)(ObjectContext *c);
	ObjectContext *context;
};

/* Для данной структуры выравнивание не нужно, но для более сложных может
 * понадобиться */
static int align(int size) {
	return (size + sizeof(void *) - 1) / sizeof(void *) * sizeof(void *);
}

extern Object* objectCreate(ObjectContext **c, int contextSize,
							int method(ObjectContext *c, int a),
							void release(ObjectContext *c))
{
	Object *o;
	assert((NULL != method) && (0 <= contextSize) && ((NULL != *c) || (0 == contextSize)));
	/* Выделим память сразу для основной структуры и для контекста. Подобная
	 * экономия места и времени может быть полезной на микрокотроллерах, но в
	 * таких случаях нельзя забывать о выравнивании, что особенн важно для ARM */
	o = (Object *)malloc(align(sizeof(Object)) + contextSize);
	if (NULL != o) {
		o->method = method;
		o->release = release;
		o->context = (ObjectContext *)(align(sizeof(Object)) + (long unsigned)o);
		if (NULL != *c) {
			*c = o->context;
		}
	} else {
		*c = NULL;
	}
	return o;
}

extern int objectMethod(Object *o, int a) {
	return o->method(o->context, a);
}

extern void objectRelease(Object **o) {
	/* Удобно сделать возможность вызова освобождения для *o == NULL, приближая
	 * таким образом её поведение к стандартной free() */
	if ((NULL != *o) && (NULL != (*o)->release)) {
		(*o)->release((*o)->context);
		free(*o);
	}
	/* И чтобы было неповадно использовать освобождённый указатель, занулить его*/
	*o = NULL;
}
