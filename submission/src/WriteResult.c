#include <stdio.h>
#include <stdlib.h>

void WriteResult(double result) {
    FILE *resultFile = fopen("result.txt", "w");

    if (resultFile == NULL) {
        perror("Error opening the text file");
    }

    fprintf(resultFile, "%.15f", result);

    fclose(resultFile);
}
