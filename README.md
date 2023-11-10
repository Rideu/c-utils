  
---
# c-utils

C utils library.


### list.h
A dynamic array of generic objects (pointers).

Basic usage:

```c
   
int main(void)
{
	list* l = list_Create();

	int num0 = 64;
	list_Add(l, &num0);

	int num1 = 128;
	list_Add(l, &num1);

	int num2 = 256;
	list_Add(l, &num2);

	int num3 = 512;
	list_Add(l, &num3);

	list_Remove(l, &num1);

	int* num_p = (int*)list_ItemAt(l, 1); // 256
}
```


### stack.h

A last-in first-out stack.

Basic usage:

```c
  
int main(void)
{ 
	stack* s = stack_Create();

	int a = 2;
	int b = 4;

	push(s, &a);
	push(s, &b);

	int* itemA = (int*)pop(s);
	int* itemB = (int*)pop(s);
}
``` 


### events.h

A basic event source that invokes the subscribed methods.

Basic usage:

```c
 
_event_container* onMessage;
 
void func(int* a, int* b)
{ 
	int sum = *a + *b;

	printf("%i", sum); 
}

int main(void)
{ 
	onMessage = eveco_Create();

	eveco_Subscribe(onMessage, func);

	int a = 1;
	int b = 2;

	eveco_InvokeArgs2(onMessage, &a, &b);
}
``` 


### utils.h

Additional utils.

Example:

```c
  
int main(void)
{ 
	char* chars = "chars";
	char* fchar = "r";

	int ios = string_IndexOf(chars, fchar); // 3
}
``` 

