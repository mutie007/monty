# Monty

Monty is a scripting language, compiled into Monty ByteCodes, using the Monty compiler `monty`. This project implements a Monty bytecode interpreter in C.

## Usage

monty file.m

Where file.m is the path to a file containing Monty bytecode instructions.

## Data structure

The stack is implemented as a doubly linked list, where the top of the stack is the head of the list.

## Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o monty

## Opcodes implemented

* push int - pushes an element onto the stack
* pall - prints all values on the stack, from top to bottom
