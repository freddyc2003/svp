#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ParseArguments(int argc, char **argv, double **basis, int n) {
    // Stores index of the current element we are considering in the a vector
    int c = 0;

    // Stores index of the current vector in the basis we're considering
    int v = 0;

    // For each argument passed into the program
    for (int i = 1; i < argc; i++) {
        // The specific argument
        char *arg = argv[i];
        // Pointer used for string to double conversion
        char *eptr;
        // Double value passed by string to double conversion
        double result;

        if (c == 0) {
            if (arg[0] != '[') {
                // We are expecting an opening bracket
                printf("Invalid input\n");
                return 1;
            } else {
                // Was an opening bracket so increment pointer past the bracket
                arg++;
            }
        }

        // Convert the argument to a double
        result = strtod(arg, &eptr);

        // If nothing to read pointer won't have moved
        if (eptr == arg) {
            printf("Invalid input\n");
            return 1;
        }

        // Store passed value in the basis array
        basis[v][c] = result;

        // If is the last expected element of the vector
        if (c == (n - 1)) {
            // We expect it to contain a closing bracket if not error
            if (*eptr != ']') {
                printf("Invalid input\n");
                return 1;
            } else {
                // Closing bracket occured, now move the pointer passed it
                eptr++;

                // Move onto next vector and back to the first element
                v += 1;
                c = 0;
            }
        } else {
            // Wasn't last element of vector so move onto the next
            c += 1;
        }

        // If the pointer returned from strtod isn't the empty character
        if (*eptr != '\0') {
            printf("Invalid input\n");
            return 1;
        }
    }

    return 0;
}
