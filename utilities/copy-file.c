#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *readFile, *writeFile;
    char readFilePath[100] = "katalog/zdjecie.png";
    char writeFilePath[100] = "katalog-sync/zdjecie-kopia.png";
    char buffer;

    readFile = fopen(readFilePath, "r");

    if (readFile == NULL)
    {
        printf("File opening failed for %s", readFilePath);
        exit(0);
    }

    writeFile = fopen(writeFilePath, "w+");
    if (writeFile == NULL)
    {
        printf("File opening failed for %s", writeFilePath);
        exit(0);
    }

    buffer = fgetc(readFile);
    while (buffer != EOF)
    {
        fputc(buffer, writeFile);
        buffer = fgetc(readFile);
    }

    printf("Copying completed");
    fclose(readFile);
    fclose(writeFile);
    return 0;
}