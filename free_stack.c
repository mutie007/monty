#include "monty.h"

/**
 * free_stack - frees every node of a stack_t doubly linked list
 * @stack: pointer to the head (top) of the stack
 */
void free_stack(stack_t *stack)
{
	stack_t *tmp;

	while (stack != NULL)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}
