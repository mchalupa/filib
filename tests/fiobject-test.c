#include <err.h>
#include <stdio.h>
#include "../src/fiobject/filib-fiobject.h"

CLASS(MyClass, FiObject)
{
	CLASS_EXTENDS(FiObject);

	int a;
};

CLASS(MyClass2, MyClass)
{
	CLASS_EXTENDS(MyClass);

	int b;
};

CLASS(MyClass3, MyClass2)
{
	CLASS_EXTENDS(MyClass2);

	int c;
};

CLASS_INIT(MyClass)
{
	printf("MyClass init\n");
	self->a = 1;
}

CLASS_INIT(MyClass2)
{
	printf("MyClass2 init\n");
	self->b = 2;
}

CLASS_INIT(MyClass3)
{
	printf("MyClass3 init\n");
	self->c = 3;
}

CLASS_DESTROY(MyClass)
{
	printf("MyClass destroy\n");
	self->a = 0;
}

CLASS_DESTROY(MyClass2)
{
	printf("MyClass2 destroy\n");
	self->b = 0;
}

CLASS_DESTROY(MyClass3)
{
	printf("MyClass3 destroy\n");
	self->c = 0;
}


int main(void)
{
	MyClass3 obj;
	fiobject_init(MyClass3, &obj);

	if (obj.c != 3 || obj.parent.b != 2 || obj.parent.parent.a != 1)
		errx(-1, "Initialization failed");

	/* or this way */
	FiObject *ptr = (FiObject *) &obj;
	if (((MyClass *) ptr)->a != 1 || ((MyClass2 *) ptr)->b != 2
		|| ((MyClass3 *) ptr)->c != 3)
		errx(-1, "Initialization failed");

	printf ("MyClass::a = %d, MyClass2::b = %d, MyClass3::c = %d\n",
		((MyClass *) ptr)->a, ((MyClass2 *) ptr)->b,
		((MyClass3 *) ptr)->c);

	if (! COBJECT_IS (MyClass3, ptr))
		errx(-1, "COBJECT_IS failed");

	if (COBJECT_IS (MyClass2, ptr))
		errx(-1, "COBJECT_IS parent failed");

	if (COBJECT_IS (FiObject, ptr))
		errx(-1, "COBJECT_IS FiObject failed");

	if (! fiobject_instanceof (MyClass3, ptr))
		errx(-1, "Instance of the same class failed");

	if (! fiobject_instanceof (MyClass2, ptr))
		errx(-1, "Instance of the parent class failed");

	if (! fiobject_instanceof (MyClass, ptr))
		errx(-1, "Instance of the parent.parent class failed");

	if (! fiobject_instanceof (FiObject, ptr))
		errx(-1, "Instance of the  FiObject failed");

	MyClass3 *obj2 = (MyClass3 *) fiobject_new(MyClass3);
	if (!obj2)
		err(1, "fiobject_new");

	ptr = (FiObject *) obj2;
	printf ("MyClass::a = %d, MyClass2::b = %d, MyClass3::c = %d\n",
		((MyClass *) ptr)->a, ((MyClass2 *) ptr)->b,
		((MyClass3 *) ptr)->c);

	fiobject_destroy(&obj);

	if (obj.c != 0 || obj.parent.b != 0 || obj.parent.parent.a != 0)
		errx(-1, "Destruction failed");

	fiobject_destroy(ptr);

	return 0;
}
