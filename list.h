// C enumerables library 

#ifndef ENUMS_LIST_H
#define ENUMS_LIST_H

#include <stdio.h>
#include <stdlib.h>   

#define en_list_int unsigned int

// A list of generic objects
typedef struct {
	size_t count;
	en_list_int* iarray;
} list;

// Create new list instance. The instance should be freed after use
list* list_Create()
{

	list* l = (list*)malloc(sizeof(list));

	if (l) {
		l->count = 0;
		l->iarray = (unsigned int*)NULL; 
	}
	return l;
}

// Add the object to the list
int list_Add(list* l, const void* obj)
{

	en_list_int* iarray = (en_list_int*)l->iarray;

	if (!iarray)
		iarray = (en_list_int*)malloc(sizeof(void*));
	else {

		int new_size = (l->count + 1) * sizeof(void*);
		void* ra_array = realloc(iarray, new_size);
		iarray = (en_list_int*)ra_array;
	}

	if (iarray) {

		iarray[l->count++] = (en_list_int)(obj);
	}

	l->iarray = iarray;

	return 1;
}

// Get item pointer under zero-based index in the list
void* list_ItemAt(const list* l, const int i)
{
	//list li = (*l);
	return (void*)(l->iarray[i]);
}

// Remove the object from the list by its pointer
int list_Remove(list* l, const void* obj)
{

	char removed = 0;
	int initialCount = l->count;

	if (l->iarray) {

		for (size_t i = 0; i < (removed ? initialCount : l->count); i++)
		{
			if (removed) {
				// realign the order of pointers 
				l->iarray[i - 1] = l->iarray[i];
			}
			else
				if (l->iarray[i] == (en_list_int)obj) {

					l->iarray[i] = (unsigned int)NULL;
					l->count--;
					// resize iarray accordingly
					removed = 1;
				}
		}
	}

	if (removed) {

		int new_size = (l->count) * sizeof(void*);

		en_list_int* iarray = (en_list_int*)l->iarray;
		void* ra_array = realloc(iarray, new_size);
		iarray = (en_list_int*)ra_array;

		l->iarray = iarray;

		return 1;
	}

	return 0;
}

// Dispose the list object instance
void list_Free(list* l) {

	free(l);
}

int train_list() {

	list* l = list_Create();

	int num0 = 64;
	list_Add(l, &num0);

	int num1 = 128;
	list_Add(l, &num1);

	int num2 = 256;
	list_Add(l, &num2);

	int num3 = 512;
	list_Add(l, &num3);

	int* num_p = (int*)list_ItemAt(l, 3);

	printf("train_list ItemAt: %i\n", *num_p);

	return 0;
}
#endif 