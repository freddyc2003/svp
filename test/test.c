#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Command to run './runme' with the known lattice
    const char* command = "./runme [1.0 0.0 0.0] [0.0 1.0 0.0] [0.0 0.0 1.0]";

    // Execute the command
    int status = system(command);
    if (status != 0) {
        printf("Error running the command\n");
        return 1;
    }

    // Read the result from 'result.txt'
    double result;
    FILE* file = fopen("result.txt", "r");
    if (file == NULL) {
        printf("Error opening 'result.txt'");
        return 1;
    }

    if (fscanf(file, "%lf", &result) != 1) {
        printf("Error reading value from 'result.txt'\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    // Check if the result is equal to 1.0
    if (result == 1.0) {
        printf("Passed. Result is equal to 1.0\n");
    } else {
        printf("Failed. Result is not equal to 1.0\n");
    }

    return 0;
}
