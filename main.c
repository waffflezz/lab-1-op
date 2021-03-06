#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define MAX_RANDOM_NUMBER 50
#define MAX_INPUT_ARRAY_LEN 11

//15 OP
void sequence_border(const int array[], int array_len, int *start, int *end);
void print_sequence(int array[], int start, int end);
int input_int_check(char value_array[]);
int input_int();

int main(void) {
    int *array = NULL;
    int array_len;
    int start, end;

    //update seed for random function
    srand(time(NULL));

    while (1) {
        puts("1. Enter array len and fill it with random numbers");
        puts("2. Find maximum non-decreasing sequence");
        puts("3. Print array");
        puts("4. Exit");

        int menu_input = input_int();
        switch (menu_input) {
            case 1:
                puts("Enter array len:");
                array_len = input_int();
                if (array_len == -1) {
                    fputs("You enter incorrect value!\n", stderr);
                    break;
                }

                if (array != NULL)
                    free(array);

                array = malloc(array_len * sizeof(int));

                for (int i = 0; i < array_len; ++i) {
                    array[i] = rand() % MAX_RANDOM_NUMBER * (int)pow(-1,
                                                                     rand());
                }
                break;
            case 2:
                if (array != NULL) {
                    sequence_border(array, array_len, &start, &end);

                    printf("Maximum non-decreasing sequence:\n");
                    print_sequence(array, start, end);
                } else {
                    fputs("First, specify the length of the array and "
                          "fill it with numbers\n", stderr);
                }
                break;
            case 3:
                if (array != NULL) {
                    int max_numbers_print = 100;

                    puts("Numbers in massive:");
                    if (array_len < max_numbers_print) {
                        for (int i = 0; i < array_len; ++i) {
                            printf("%d ", array[i]);
                        }
                        puts("");
                    } else {
                        for (int i = 0; i < max_numbers_print; ++i) {
                            printf("%d ", array[i]);
                        }
                        puts("...");
                    }
                } else {
                    fputs("First, specify the length of the array and fill "
                          "it with numbers\n", stderr);
                }
                break;
            case 4:
                free(array);
                return 0;
            default:
                fputs("Not in menu\n", stderr);
                break;
        }
    }
}

int input_int() {
    char str_array_len[MAX_INPUT_ARRAY_LEN];
    fgets(str_array_len, MAX_INPUT_ARRAY_LEN, stdin);
    fflush(stdin);
    if (!(input_int_check(str_array_len))
        || strlen(str_array_len) == 1) {
        return -1;
    }

    return strtol(str_array_len, NULL, 10);
}

void sequence_border(const int array[], int array_len, int *start, int *end) {
    int start_ptr = 0, end_ptr = 0;
    int next_start_ptr = 0, next_end_ptr, diff;

    for (int i = 1; i < array_len; ++i) {
        if (array[i] >= array[i - 1]) {
            next_end_ptr = i;
            diff = next_end_ptr - next_start_ptr + 1;
            if (end_ptr - start_ptr + 1 <= diff) {
                start_ptr = next_start_ptr;
                end_ptr = next_end_ptr;
            }
        } else {
            next_start_ptr = i;
        }
    }

    *start = start_ptr;
    *end = end_ptr;
}

void print_sequence(int array[], int start, int end) {
    for (int i = start; i <= end; ++i) {
        printf("%d ", array[i]);
    }
    puts("");
}

int input_int_check(char value_array[]) {
    for (int i = 0; i < strlen(value_array) - 1; ++i) {
        if ((value_array[i] < '0') || (value_array[i] > '9')) {
            return 0;
        }
    }
    return 1;
}
