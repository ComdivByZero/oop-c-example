#if !defined(OBJECT_H)
#define OBJECT_H

/* С указателем на Object будет взаимодействовать клиент интерфейса */
typedef struct Object_ClosedRealization Object;
/* ObjectContext нужен реализации интерфейса для передачи контекста объекта в 
 * его методы; переменную этого типа можно воспринимать как аналог this во 
 * многих ООП — языках*/
typedef struct Object_ContextRealization ObjectContext;

/* Функция objectCreate нужна, как и тип ObjectContext, только при реализации 
 * интерфейса, клиентский код не должен вызывать его напрямую */
extern Object* objectCreate(ObjectContext **context, int contextSize, 
							int method(ObjectContext *c, int a),
							void release(ObjectContext *c));

/* Функции objectMethod и objectRelease будут использованы клиентским кодом */
extern int objectMethod(Object *o, int a);
extern void objectRelease(Object **o);

#endif
