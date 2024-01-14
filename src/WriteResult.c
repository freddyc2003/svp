#include <stdio.h>
#include <stdlib.h>

void WriteResult(double result) {
    // Try to open or create a file 'result.txt' in write mode
    FILE *resultFile = fopen("result.txt", "w");

    // Check if the file was successfully opened/created
    if (resultFile == NULL) {
        perror("Error opening the text file");
    }

    // Write the 'result' to 'resultFile', formatted to 15 decimal places
    fprintf(resultFile, "%.15f", result);

    // Close the file to free resources and flush any buffered output
    fclose(resultFile);
}
