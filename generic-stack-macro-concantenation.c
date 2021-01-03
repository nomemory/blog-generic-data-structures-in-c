#include <stdio.h>
#include <stdlib.h>

#define STACK_DECLARE(type)                                     \
typedef struct stack_##type##_s {                               \
    type data;                                                  \
    struct stack_##type##_s *next;                              \
} stack_##type;                                                 \
void stack_##type##_push(stack_##type **stack, type data);      \
type stack_##type##_pop(stack_##type **stack);                  \

#define STACK_DEFINE(type)                                      \
void stack_##type##_push(stack_##type **stack, type data) {     \
    stack_##type *new_node = malloc(sizeof(*new_node));         \
    if (NULL == new_node) {                                     \
        fputs("Couldn't allocate memoryn", stderr);             \
        abort();                                                \
    }                                                           \
    new_node->data = data;                                      \
    new_node->next = *stack;                                    \
    *stack = new_node;                                          \
}                                                               \
type stack_##type##_pop(stack_##type **stack) {                 \
    if (NULL == stack || NULL == *stack){                       \
        fputs("Stack underflow", stderr);                       \
        abort();                                                \
    }                                                           \
    stack_##type *top = *stack;                                 \
    type value = top->data;                                     \
    *stack = top->next;                                         \
    free(top);                                                  \
    return value;                                               \
}                                                               \

#define STACK_TYPE(type)                    \
    stack_##type                            \

#define STACK_DATA(stack)                   \
    (stack)->data                           \

#define STACK_PUSH(type, stack, data)       \
    stack_##type##_push(stack, data)        \

#define STACK_POP(type, stack)              \
    stack_##type##_pop(stack)               \


// If you want to work with a stack that holds integers you should
// use those macros. They will expand and the associated functions will be
// generated .
//

STACK_DECLARE(int)
STACK_DEFINE(int)
STACK_DECLARE(double)
STACK_DEFINE(double)

int main(int argc, char** argv) {
    int i;

    //New stack . Alaways assign NULL
    STACK_TYPE(int) *st = NULL;
    STACK_TYPE(double) *st2 = NULL;

    for (i = 0; i < 100; ++i) {
        printf("PUSH: %d\n", i);
        STACK_PUSH(int, &st, i);
        STACK_PUSH(double, &st2, i);
    }

    while (i--> 0) {
        printf("POP: %d %2.2f\n", STACK_POP(int, &st), STACK_POP(double, &st2));
    }
    return (0);
}
