#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define MAX_EXPR_LENGTH 100

struct Operation
{
    int operand;
    char operator;
    struct Operation *next;
};

void input(char *, int);
int extract_operand(char *, int *);
struct Operation *parse_expression(char *);
struct Operation *create_operation_node(int, char);
struct Operation *append_operation_node(struct Operation *, int, char);
void delete_operation_nextnode(struct Operation *node);
int evaluate(struct Operation *);

int main()
{
    char string[MAX_EXPR_LENGTH];
    int string_length, result;
    struct Operation *expression;

    while (true)
    {
        input(string, MAX_EXPR_LENGTH);
        string_length = strlen(string);

        // If no input then ask for input again
        if (string_length == 0)
            continue;

        // EXIT command
        if (strncmp(string, "EXIT", string_length) == 0)
            break;

        expression = parse_expression(string);
        result = evaluate(expression);
        expression = NULL;
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

struct Operation *parse_expression(char *string)
{
    char operator;
    int operand, index;
    struct Operation *head, *tail;
    index = 0;
    operand = extract_operand(string, &index);
    head = create_operation_node(operand, '\0');
    tail = head;
    while (string[index])
    {
        operator = string[index];
        index++;
        operand = extract_operand(string, &index);
        tail = append_operation_node(tail, operand, operator);
    }
    tail = NULL;
    return head;
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

void delete_operation_nextnode(struct Operation *node)
{
    struct Operation *temp;
    temp = node->next;
    node->next = node->next->next;
    free(temp);
}

int evaluate(struct Operation *head)
{
    struct Operation *node;
    int evaluated, precedence, result;
    precedence = 1;
    while (head->next != NULL)
    {
        node = head;
        while (node->next != NULL)
        {
            evaluated = false;
            switch (precedence)
            {
            case 1:
                switch (node->next->operator)
                {
                case '^':
                    node->operand = pow(node->operand, node->next->operand);
                    evaluated = true;
                    break;
                }
                break;
            case 2:
                switch (node->next->operator)
                {
                case '*':
                    node->operand = node->operand * node->next->operand;
                    evaluated = true;
                    break;
                case '/':
                    node->operand = node->operand / node->next->operand;
                    evaluated = true;
                    break;
                }
                break;
            case 3:
                switch (node->next->operator)
                {
                case '+':
                    node->operand = node->operand + node->next->operand;
                    evaluated = true;
                    break;
                case '-':
                    node->operand = node->operand - node->next->operand;
                    evaluated = true;
                    break;
                }
                break;
            }
            if (evaluated)
                delete_operation_nextnode(node);
            else
                node = node->next;
        }
        precedence++;
    }
    result = head->operand;
    free(head);
    return result;
}