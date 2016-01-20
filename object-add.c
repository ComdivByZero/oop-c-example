#include "object-add.h"

#include <stdio.h>

struct Object_ContextRealization {
	int add;
};

static int method(ObjectContext *c, int a) {
	printf("%d + %d", a, c->add);
	return a + c->add;
}

static void release(ObjectContext *c) {
	printf("object-add(%d) released\n", c->add);
}

extern Object* objectAddCreate(int add) {
	Object *o;
	ObjectContext *c;
	o = objectCreate(&c, sizeof(ObjectContext), method, release);
	if (NULL != o) {
		c->add = add;
	}
	return o;
}
