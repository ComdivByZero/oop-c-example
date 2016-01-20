/** Сборка: gcc/clang/tcc *.c -o object */
#include <stdio.h>

#include "object-add.h"
#include "object-mult.h"

extern int main(void) {
	Object *a[4];
	int i, j;

	/* создадим комбинацию из 2-х реализаций с 2-мя контекстами */
	a[0] = objectMultCreate(1);
	a[1] = objectAddCreate(1);
	a[2] = objectAddCreate(2);
	a[3] = objectMultCreate(2);

	for (i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
		printf("%d) ", i);
		
		/* вызов одной и той же функции-метода с одинаковым параметром для 
		 * разных указателей-объектов */
		j = objectMethod(a[i], 3);
		printf(" = %d\n", j	);
	}
	for (i = 0; i < sizeof(a) / sizeof(a[0]); ++i) {
		objectRelease(a + i);
	}
	return 0;
}
