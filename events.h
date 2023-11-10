/* Base template
*/

#ifndef EVENTS_H
#define EVENTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

#include "list.h" 

typedef struct {
	list* subs_handlers;
} _event_container;

_event_container* eveco_Create()
{

	_event_container* eveco = (_event_container*)malloc(sizeof(_event_container));

	if (eveco)
	{

		memset(eveco, 0, sizeof(_event_container));
		eveco->subs_handlers = list_Create();
	}

	return eveco;
}

static void eveco_Invoke(_event_container* event_c)
{
	list* handlers = (list*)event_c->subs_handlers;

	for (size_t i = 0; i < handlers->count; i++)
	{
		void (*handler)() = (void(*)())(list_ItemAt(handlers, i));

		(*handler)();
	}
}

static void eveco_InvokeArg(_event_container* event_c, void* arg)
{

	list* handlers = (list*)event_c->subs_handlers;

	for (size_t i = 0; i < handlers->count; i++)
	{
		void* handler_ptr = list_ItemAt(handlers, i);
		void (*handler)(void*) = (void(*)(void*))(handler_ptr);

		(*handler)(arg);
	}
}

static void eveco_InvokeArgs2(_event_container* event_c, void* arg1, void* arg2)
{

	list* handlers = (list*)event_c->subs_handlers;

	for (size_t i = 0; i < handlers->count; i++)
	{
		void* handler_ptr = list_ItemAt(handlers, i);
		void (*handler)(void*, void*) = (void(*)(void*, void*))(handler_ptr);

		(*handler)(arg1, arg2);
	}
}

static void eveco_Subscribe(_event_container* event_c, void* method)
{

	list* handlers = event_c->subs_handlers;

	list_Add(handlers, method);
}

// unsubscribe?

static void eveco_Free(_event_container* event_c) {

	list_Free(event_c->subs_handlers);

	free(event_c);
}

#endif  