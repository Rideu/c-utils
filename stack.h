// C helper library 

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h> 


typedef struct stack_entry {

	void* obj;
	struct stack_entry* next_ptr;
	struct stack_entry* prev_ptr;
} stack_entry;

// A last-in first-out stack
typedef struct {

	stack_entry* first_ptr; // current, top stack_entry
	stack_entry* last_ptr; // last, bottom stack_entry
} stack;

stack* stack_Create()
{

	stack* s = (stack*)malloc(sizeof(stack));
	s->first_ptr = NULL;
	s->last_ptr = NULL;
	return s;
}

int push(stack* s, void* obj)
{

	stack_entry* new_l = (stack_entry*)malloc(sizeof(stack_entry));

	new_l->prev_ptr = 0;
	new_l->next_ptr = 0;
	new_l->obj = obj;

	if (new_l)
	{

		if (s->last_ptr)
		{ // stack has some entry
			stack_entry* l = s->last_ptr;

			l->prev_ptr = new_l;
			new_l->next_ptr = l;

			s->last_ptr = new_l; // set new last obj
		}
		else
		{ // stack is empty
			s->last_ptr = new_l;
			s->first_ptr = new_l;
		}
	}
	else
	{
		return 0x2;
	}

	return 0;
}

void* pop(stack* s)
{
	if (s->first_ptr)
	{
		stack_entry* f = s->first_ptr;


		if (s->first_ptr == s->last_ptr)
		{
			s->last_ptr = 0x0;
		}

		s->first_ptr = f->prev_ptr; // swap to the prev before current;

		if (s->first_ptr)
			s->first_ptr->next_ptr = 0x0; // there's no next entry 


		void* val = f->obj;

		free(f); // disp current

		return val;
	}

	return 0; // return 0x0 (stack is empty)
}

#endif 