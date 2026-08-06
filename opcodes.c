#include "monty.h"

/**
 * is_number - checks whether a string represents a valid integer
 * @str: the string to check
 *
 * Return: 1 if str is a valid integer, 0 otherwise
 */
int is_number(char *str)
{
	int i = 0;
	int has_digit = 0;

	if (str == NULL || str[0] == '\0')
		return (0);

	if (str[0] == '-' || str[0] == '+')
		i = 1;

	for (; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		has_digit = 1;
	}
	return (has_digit);
}

/**
 * push_stack - pushes an element onto the top of the stack
 * @stack: pointer to the top of the stack
 * @line_number: line number in the bytecode file
 */
void push_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *new_node;

	if (!is_number(current_arg))
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	new_node->n = atoi(current_arg);
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
		(*stack)->prev = new_node;
	*stack = new_node;
}

/**
 * pall_stack - prints all the values on the stack, top to bottom
 * @stack: pointer to the top of the stack
 * @line_number: line number in the bytecode file (unused)
 */
void pall_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;

	(void)line_number;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

/**
 * pint_stack - prints the value at the top of the stack
 * @stack: pointer to the top of the stack
 * @line_number: line number in the bytecode file
 */
void pint_stack(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}

/**
 * pop_stack - removes the top element of the stack
 * @stack: pointer to the top of the stack
 * @line_number: line number in the bytecode file
 */
void pop_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	tmp = *stack;
	*stack = (*stack)->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}

/**
 * swap_stack - swaps the top two elements of the stack
 * @stack: pointer to the top of the stack
 * @line_number: line number in the bytecode file
 */
void swap_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *first;
	stack_t *second;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first = *stack;
	second = first->next;

	first->next = second->next;
	if (second->next != NULL)
		second->next->prev = first;

	second->prev = NULL;
	second->next = first;
	first->prev = second;

	*stack = second;
}

/**
 * add_stack - adds the top two elements of the stack
 * @stack: pointer to the top of the stack
 * @line_number: line number in the bytecode file
 */
void add_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *top;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	top = *stack;
	top->next->n = top->next->n + top->n;

	*stack = top->next;
	(*stack)->prev = NULL;
	free(top);
}
