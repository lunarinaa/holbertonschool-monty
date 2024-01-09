#include "monty.h"


/**
 * checkFile - checks aviability of file & given argument
 * @ac: arguments' count
 * @av: arguments' array
 */
void checkFile(int ac, char **av)
{
	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		freeStack();
		exit(EXIT_FAILURE); }

	glob.fd = fopen(av[1], "r");
	if (!glob.fd)
	{
		fprintf(stderr, "Error: Can't open file %s\n", av[1]);
		freeStack();
		exit(EXIT_FAILURE); }

}


/**
 * checkLine - reads and parses the line
 * Return: getline's read status
 */
int checkLine(void)
{
	size_t max = 0;
	int r = 0;

	r = getline(&glob.buffer, &max, glob.fd);
	if (r != -1)
		glob.token = strtok(glob.buffer, " \t\n");
	return (r);
}


/**
 * checkOp - checks given function's aviability
 * @str: function name
 * @line_number: function accured in file
 * Return: function adress in success, exits in failure
 */
void (*checkOp(char *str, unsigned int line_number))(stack_t **, unsigned int)
{
	int i = 0;
	instruction_t ops[] = {
		{"push", push},
		{"pall", pall},
		{NULL, NULL}
	};

		for (i = 0; strcmp(ops[i].opcode, str) != 0; i++)
		{
			if (ops[i + 1].opcode == NULL && ops[i].opcode != str)
			{
				fprintf(stderr, "L%u: unknown instruction %s\n", line_number, str);
				freeStack();
				exit(EXIT_FAILURE);
			}
		}
	return (ops[i].f);
}


/**
 * freeStack - frees stack & closes file descriptor
 */
void freeStack(void)
{
	stack_t *temp = NULL;

	while (glob.top)
	{
		temp = glob.top;
		glob.top = glob.top->next;
		free(temp);
	}
	free(glob.top);
	free(glob.buffer);
	fclose(glob.fd);
}


/**
 * isDigit - check string is full of digits or not
 * @number: string
 * Return: if string is not digit return -1
 */
int isDigit(char *number)
{
	int i = 0;

	if (number)
	{
		if (number[i] == '-')
			++i;
		for (; number[i] != '\0'; i++)
		{
			if ((isdigit(number[i])) == 0)
				return (-1); }
		return (0);
	}
	return (-1);
}
