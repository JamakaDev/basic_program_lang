#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>

char* get_file_contents(char* filePath){
  
  FILE* filePtr = fopen(filePath, "r");
  
  if (filePtr) {

    long  fileLen = 0;
    char* fileBuf = NULL;

    fseek(filePtr, 0, SEEK_END);
    fileLen = ftell(filePtr);
    fseek(filePtr, 0, SEEK_SET);

    fileBuf = calloc(fileLen, fileLen);

    if (fileBuf)
      fread(fileBuf, 1, fileLen, filePtr);

    fclose(filePtr);

    return fileBuf;

  }

  printf("Error opening file: %s\n", filePath);

}