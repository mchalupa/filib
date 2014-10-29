/*
 * filib-fiobject.h - Lightweight objects for C programming language
 *
 * Copyright (C) 2014 Marek Chalupa <mchqwerty@gmail.com>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose. It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#ifndef __FILIB_OBJECT__
#define __FILIB_OBJECT__

#include "filib-util.h"

struct FiObject_type;

typedef struct _FiObject {
	struct FiObject_type *__type;
	struct FiObject_type *__real_type;

	/* for inner object logic
	 * if the object was created dynamically (fiobject_new) then it holds
	 * number of references (atm always 1). If it was not created that way,
	 * then it is set to -1 */
	int refcount;
} FiObject;

struct FiObject_type {
	struct FiObject_type *parent;

	void (*init)(FiObject *self);
	void (*destroy)(FiObject *self);
};

/* PRIVATE, you should not need these */
struct FiObject_type __type__FiObject = {
	NULL, NULL, NULL
};

void __fiobject_init(FiObject *c, struct FiObject_type *type);
void __fiobject_destroy(FiObject *c);
FiObject *__fiobject_new(size_t size, struct FiObject_type *type);
int __fiobject_instanceof(struct FiObject_type *type1, struct FiObject_type *type2);
/* PRIVATE end */


#define CLASS(class, extends)						\
	static void __init__##class(FiObject *self);			\
	static void __destroy__##class(FiObject *self);			\
	struct FiObject_type __type__##class =				\
		{&__type__##extends,					\
		__init__##class, __destroy__##class };			\
	typedef struct __##class class;					\
	struct __##class


#define CLASS_INIT(class)						\
	static void __init__user__##class(class *self);			\
	static void __init__##class(FiObject *self) {			\
	((class *) self)->__type = &__type__##class;			\
	if (__type__##class.parent->init )				\
		__type__##class.parent->init(self); 			\
	__init__user__##class((class *) self);}				\
	static void __init__user__##class(class *self)

#define CLASS_DESTROY(class)						\
	static void __destroy__user__##class(class *self);		\
	static void __destroy__##class(FiObject *self) {			\
		__destroy__user__##class((class *) self);		\
		if (__type__##class.parent->destroy )			\
			__type__##class.parent->destroy(self);}		\
	static void __destroy__user__##class(class *self)

#define CLASS_EXTENDS(extends)						\
	extends parent;							\
	struct FiObject_type *__type

#define fiobject_init(class, obj)					\
	__fiobject_init(((FiObject *) (obj)), &__type__##class)

#define fiobject_destroy(obj)						\
	__fiobject_destroy((FiObject *) obj)

#define fiobject_new(class)						\
	((class *) (__fiobject_new(sizeof(class), &__type__##class)))

#define COBJECT_IS(class, obj)						\
	(obj->__real_type == &__type__##class)

#define fiobject_instanceof(class, obj)					\
	__fiobject_instanceof(obj->__real_type, &__type__##class)

#endif /* __FILIB_OBJECT__ */
