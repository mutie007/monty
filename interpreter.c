#include "monty.h"

/**
 * get_op_func - matches an opcode string to its handler function
 * @opcode: the opcode string
 *
 * Return: pointer to the matching function, or NULL if not found
 */
void (*get_op_func(char *opcode))(stack_t **stack, unsigned int line_number)
{
	instruction_t instructions[] = {
		{"push", push_stack},
		{"pall", pall_stack},
		{"pint", pint_stack},
		{"pop", pop_stack},
		{"swap", swap_stack},
		{"add", add_stack},
		{NULL, NULL}
	};
	int i;

	for (i = 0; instructions[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
			return (instructions[i].f);
	}
	return (NULL);
}

/**
 * run_file - reads a Monty bytecode file and executes it line by line
 * @fp: pointer to the opened bytecode file
 */
void run_file(FILE *fp)
{
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;
	stack_t *stack = NULL;
	char *opcode;
	void (*op_func)(stack_t **stack, unsigned int line_number);

	while (getline(&line, &len, fp) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");
		current_arg = strtok(NULL, " \t\n");

		if (opcode == NULL || opcode[0] == '#')
			continue;

		op_func = get_op_func(opcode);
		if (op_func == NULL)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n",
				line_number, opcode);
			free(line);
			free_stack(stack);
			exit(EXIT_FAILURE);
		}
		op_func(&stack, line_number);
	}

	free(line);
	free_stack(stack);
}
