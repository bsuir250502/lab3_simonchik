#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string_size 100

typedef struct inform {
    char name_of_appliance[string_size];
    char specification[string_size];
    struct inform *next;
} ring;

char *my_gets(char *str, size_t strin_size)
{
    fgets(str, strin_size, stdin);
    str[strlen(str) - 1] = '\0';
    return str;
}

ring *input_of_inform(ring * pointer)
{
    printf("Enter name of appliance: ");
    my_gets(pointer->name_of_appliance, string_size);
    printf("Enter information about %s: ", pointer->name_of_appliance);
    my_gets(pointer->specification, string_size);
    return pointer;
}

ring *memory_allocation(ring * pointer)
{
    if (!(pointer = (ring *) calloc(1, sizeof(ring)))) {
        printf("ERROR!!!There is no free memory!");
        return NULL;
    } else
        return pointer;
}

void review(ring * pointer)
{
    ring *n_pointer;
    n_pointer = pointer->next;
    do {
        puts(n_pointer->name_of_appliance);
        n_pointer = n_pointer->next;
    }
    while (n_pointer != pointer->next);
}

ring *create_ring(ring * pointer)
{
    pointer = memory_allocation(pointer);
    pointer = input_of_inform(pointer);
    pointer->next = pointer;
    return pointer;
}

ring *add_element_to_ring(ring * pointer)
{
    char str[string_size];
    ring *n_pointer = NULL;
    do {
        if (!pointer) {
            pointer = create_ring(pointer);
        } else {
            n_pointer = memory_allocation(n_pointer);
            n_pointer = input_of_inform(n_pointer);
            n_pointer->next = pointer->next;
            pointer->next = n_pointer;
            pointer = n_pointer;
        }
        printf("To enter still appliance press '+' else, press any key: ");
    }
    while (strcmp(my_gets(str, string_size), "+") == 0);
    return pointer;
}

ring *revers_of_ring(ring * pointer)
{
    ring *previous, *current, *the_next;
    previous = pointer;
    current = previous->next;
    the_next = current->next;
    do {
        current->next = previous;
        previous = current;
        current = the_next;
        the_next = the_next->next;
    }
    while (previous != pointer);
    pointer = current;
    return pointer;
}

void checkHelp(void)
{
    printf
        ("================================================================================\n"
         "MANUAL:\n"
         "Enter the name of appliance and specification,\n"
         "to add another appliance, press '+'.\n"
         "===============================================================================\n"
         "The program will be direct and inverse list of appliances.\n"
         "===============================================================================\n");
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if (!strcmp(argv[1], "-h"))
            checkHelp();
    }
    ring *pointer = NULL;
    pointer = add_element_to_ring(pointer);
    printf("\nThe list of appliances:\n");
    review(pointer);
    pointer = revers_of_ring(pointer);
    printf("\nReverse a list of appliances:\n");
    review(pointer);
    return 0;
}
