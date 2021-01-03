#include <stdio.h>
#include <stdlib.h>

typedef struct stack_s {
    void *data; // Can reference "anything"
    struct stack_s *next; // The stack is built as a linked list
} stack;

void stack_push(stack **head, void *data);
void *stack_pop(stack **head);

void stack_push(stack **head, void *data) {
    stack *new_node = malloc(sizeof(*new_node));
    if (NULL == new_node) {
        fputs("Couldn't allocate memoryn", stderr);
        abort();
    }
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

void *stack_pop(stack **head) {
    stack *top;
    void *value;
    if (NULL == head || NULL == *head) {
        fputs("Stack underflow\n", stderr);
        abort();
    }
    top = *head;
    value = top->data;
    *head = top->next;
    free(top);
    return value;
}

int main() {
    stack *s = NULL;
    int i, *tmp;

    /* Add values from [1..100] into the stack */
    printf("Pushing: \n");

    for (i = 0; i < 100; ++i) {
        tmp = malloc(sizeof (*tmp));
        if (NULL == tmp) {
            fputs("Couldn't allocate memory\n", stderr);
            abort();
        }
        *tmp = i;
        printf("%d ", *tmp);
        stack_push(&s, tmp);
    }

    // Remove all elements of the stack

    printf("\nPopping: n");
    while(i-->0){
        tmp = stack_pop(&s);
        printf("%d ", *tmp);
        free(tmp);
    }

    return (0);
}
