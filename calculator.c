// Evaluate function is yet to work on


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPR_LENGTH 100

struct Operation
{
    int operand;
    char operator;
    struct Operation *prev;
    struct Operation *next;
};

void input(char *, int);
struct Operation *create_operation(int operand);
struct Operation *append_operation(struct Operation *, int, char);
int evaluate(int, char, int);
int add(int, int);
int subtract(int, int);
int multiply(int, int);
int divide(int, int);
int extract_operand(char *, int *);

int main()
{
    char expression[MAX_EXPR_LENGTH];
    char operator;
    int index, operand, result, expression_length;

    while (1)
    {
        input(expression, MAX_EXPR_LENGTH);
        expression_length = strlen(expression);

        // If no input then ask for input again
        if (expression_length == 0)
            continue;

        // EXIT command
        if (strncmp(expression, "EXIT", expression_length) == 0 || strncmp(expression, "exit", expression_length) == 0)
            break;

        // Convert expression from string to linked list
        index = 0;
        struct Operation *head, *tail;
        operand = extract_operand(expression, &index);
        head = create_operation(operand);
        tail = head;
        while (expression[index])
        {
            operator = expression[index];
            index++;
            operand = extract_operand(expression, &index);
            tail = append_operation(tail, operand, operator);
        }
        evaluate(head);
        result = head->operand;
        printf("%d\n", result);
    }
    return 0;
}

void input(char *string, int length)
{
    // INPUT
    printf(">> ");
    fgets(string, length, stdin);

    length = strlen(string);

    // Remove the '\n' character from input string
    string[length - 1] = '\0';
}

struct Operation *create_operation(int operand)
{
    struct Operation *node = (struct Operation *)malloc(sizeof(struct Operation));
    node->operand = operand;
    node->operator= '\0';
    node->prev = NULL;
    node->next = NULL;
    return node;
}

struct Operation *append_operation(struct Operation *tail, int operand, char operator)
{
    struct Operation *node = (struct Operation *) malloc(sizeof(struct Operation));
    node->operand = operand;
    node->operator = operator;
    node->prev = tail;
    node->next = NULL;
    tail->next = node;
    tail = node;
    return tail;
}

int evaluate(struct Operation *head)
{
    switch (operator)
    {
    case '+':
        return add(operand1, operand2);
    case '-':
        return subtract(operand1, operand2);
    case '*':
        return multiply(operand1, operand2);
    case '/':
        return divide(operand1, operand2);
    default:
        return 0;
    }
}

int add(int operand1, int operand2)
{
    return operand1 + operand2;
}

int subtract(int operand1, int operand2)
{
    return operand1 - operand2;
}

int multiply(int operand1, int operand2)
{
    return operand1 * operand2;
}

int divide(int operand1, int operand2)
{
    return operand1 / operand2;
}

int extract_operand(char *string, int *index)
{
    int operand = 0;
    while (isdigit(string[*index]))
    {
        operand = operand * 10 + (string[*index] - '0');
        (*index)++;
    }
    return operand;
}
