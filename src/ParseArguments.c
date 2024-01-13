#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ParseArguments(int argc, char **argv, double **basis, int n) {
    int c = 0;
    int v = 0;

    for (int i = 1; i < argc; i++) {
        char *arg = argv[i];
        char *eptr;
        double result;

        printf("%s \n", arg);

        if (c == 0) {
            printf("c=0, arg[0]=%c \n", arg[0]);

            if (arg[0] != '[') {
                // should be an opening bracket
                printf("Invalid input\n");
                return 1;
            } else {
                arg++;
                printf("arg=%s \n", arg);
            }
        }

        result = strtod(arg, &eptr);

        printf("result=%lf \n", result);
        printf("eptr=%s \n", eptr);

        if (eptr == arg) {
            printf("Invalid input\n");
            return 1;
        }

        basis[v][c] = result;

        if (c == (n - 1)) {
            if (*eptr != ']') {
                // should be a closing bracket...
                printf("Invalid input\n");
                return 1;
            } else {
                eptr++;
                v += 1;
                c = 0;
            }
        } else {
            c += 1;
        }
        if (*eptr != '\0') {
            printf("Invalid input\n");
            return 1;
        }
    }

    return 0;
}

// int vector = 0;
// int c = 0;

// for (int i = 1; i < argc; i++)
// {
//     char *argument = argv[i];

//     // printf("Argument %d (before): %s\n", i, argument);

//     int k = 0;

//     for (int j = 0; argument[j] != '\0'; j++)
//     {
//         if (argument[j] != '[' && argument[j] != ']')
//         {
//             argument[k] = argument[j];
//             k++;
//         }
//     }

//     argument[k] = '\0';

//     // printf("Argument %d (after): %s\n", i, argument);

//     double result = strtod(argument, NULL);

//     // printf("Converted value: %lf\n", result);

//     basis[vector][c] = result;

//     c += 1;

//     // printf("basis[%d][%d] \n", vector, c);

//     if (c == n)
//     {
//         vector += 1;
//         c = 0;
//     }
// }

// return basis;
// }
