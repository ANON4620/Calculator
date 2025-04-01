// Evaluate function is yet to work on

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_EXPR_LENGTH 100

struct Operation
{
    int operand;
    char operator;
    struct Operation *next;
};

void input(char *, int);
struct Operation *create_operation_node(int, char);
struct Operation *append_operation_node(struct Operation *, int, char);
int evaluate(struct Operation *);
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

    while (true)
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
        head = create_operation_node(operand, '\0');
        tail = head;
        while (expression[index])
        {
            operator= expression[index];
            index++;
            operand = extract_operand(expression, &index);
            tail = append_operation_node(tail, operand, operator);
        }

        result = evaluate(head);
        head = NULL;
        tail = NULL;
        printf("%d\n", result);
    }
    return 0;
}

void input(char *string, int length)
{
    printf(">> ");
    fgets(string, length, stdin);

    length = strlen(string);

    // Remove the '\n' character from input string
    string[length - 1] = '\0';
}

struct Operation *create_operation_node(int operand, char operator)
{
    struct Operation *node = (struct Operation *)malloc(sizeof(struct Operation));
    node->operand = operand;
    node->operator= operator;
    node->next = NULL;
    return node;
}

struct Operation *append_operation_node(struct Operation *tail, int operand, char operator)
{
    struct Operation *node = create_operation_node(operand, operator);
    tail->next = node;
    tail = node;
    return tail;
}

int evaluate(struct Operation *head)
{
    struct Operation *node, *temp;
    node = head;
    while (node->next != NULL)
    {
        int evaluated = false;
        switch (node->next->operator)
        {
        case '*':
            node->operand = multiply(node->operand, node->next->operand);
            evaluated = true;
            break;
        case '/':
            node->operand = divide(node->operand, node->next->operand);
            evaluated = true;
            break;
        }
        if (evaluated)
        {
            temp = node->next;
            node->next = node->next->next;
            free(temp);
        }
        else
            node = node->next;
    }
    node = head;
    while (node->next != NULL)
    {
        int evaluated = false;
        switch (node->next->operator)
        {
        case '+':
            node->operand = add(node->operand, node->next->operand);
            evaluated = true;
            break;
        case '-':
            node->operand = subtract(node->operand, node->next->operand);
            evaluated = true;
            break;
        }
        if (evaluated)
        {
            temp = node->next;
            node->next = node->next->next;
            free(temp);
        }
        else
            node = node->next;
    }
    int result = node->operand;
    free(node);
    return result;
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
