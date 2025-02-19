#include <stdio.h>
#include <stdlib.h>

#include "file_reader.h"

char *readShaderFile(const char *filePath) {
    FILE *file = fopen(filePath, "rb");
    if (!file) {
        printf("Failed to open file: %s\n", filePath);
        return NULL;
    }
  
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
  
    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        printf("Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
  
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';  // Null-terminate the string
  
    fclose(file);
    return buffer;
  }
  