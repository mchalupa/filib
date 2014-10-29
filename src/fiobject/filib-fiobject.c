/*
 * filib-fiobject.c - Lightweight objects for C programming language
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

#include <stdlib.h>

#include "filib-fiobject.h"

inline void
__fiobject_init(FiObject *c, struct FiObject_type *type)
{
	c->__type = &__type__FiObject;
	c->__real_type = type;
	c->refcount = -1;

	type->init(c);
}

inline void
__fiobject_destroy(FiObject *c)
{
	c->__real_type->destroy(c);

	/* if the object was created by __fiobject_new, then free allocated
	 * memory */
	if (c->refcount != -1)
		free(c);
}

FiObject *
__fiobject_new(size_t size, struct FiObject_type *type)
{
	FiObject *obj = malloc(size);
	if (!obj)
		return NULL;

	__fiobject_init(obj, type);
	obj->refcount = 1;

	return obj;
}

inline int
__fiobject_instanceof(struct FiObject_type *type1, struct FiObject_type *type2)
{
	struct FiObject_type *tmp = type1;

	while (tmp) {
		if (tmp == type2)
			return 1;

		tmp = tmp->parent;
	}

	return 0;
}
