#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define HEADER_N64 0x40123780
#define HEADER_V64 0x37804012
#define HEADER_Z64 0x80371240
#define ERROR_WRONG_USAGE -1
#define ERROR_INPUT_FILE_NOT_FOUND -2
#define ERROR_INPUT_FILE_TOO_BIG -3
#define ERROR_IDENTICAL_FORMAT -4
#define ERROR_UNSUPPORTED_OUTPUT_FORMAT -5
#define ERROR_UNSUPPORTED_INPUT_FORMAT -6
#define ERROR_WRITE_OUTPUT -7
#define MAXIMUM_FILE_SIZE 134217728

void wordSwap(unsigned char* inputROM, long inputLength) {
  for(int i=0; i<inputLength; i+= 2) {
  	unsigned char byteA = inputROM[i + 0];
  	unsigned char byteB = inputROM[i + 1];
  	
  	inputROM[i + 0] = byteB;
  	inputROM[i + 1] = byteA;
  }
}

void dWordSwap(unsigned char* inputROM, long inputLength) {
  for(int i=0; i<inputLength; i+= 4) {
    unsigned char byteA = inputROM[i + 0];
    unsigned char byteB = inputROM[i + 1];
    unsigned char byteC = inputROM[i + 2];
    unsigned char byteD = inputROM[i + 3];
    
    inputROM[i + 0] = byteD;
    inputROM[i + 1] = byteC;
    inputROM[i + 2] = byteB;
    inputROM[i + 3] = byteA;
  }
}

int hasExtension(const char* outputFile, const char* extension) {
  char upperCaseExt[5];
  memcpy(upperCaseExt, extension, 4);
  upperCaseExt[1] = toupper(upperCaseExt[1]);
  upperCaseExt[4] = 0x00;

  return strlen(outputFile) > 4 && ((!strcmp(outputFile + strlen(outputFile) - 4, extension)) || 
                                    (!strcmp(outputFile + strlen(outputFile) - 4, upperCaseExt)));
}

int main(int argc, const char *argv[]) {
  if(argc != 3) {
    printf("Usage: n64convert input.v64 output.z64\n");
    return ERROR_WRONG_USAGE;
  }
  
  const char* inputFile = argv[1];
  const char* outputFile = argv[2];

  FILE* fi = fopen(inputFile, "r");
  if(!fi) {
    printf("Input file does not exist!\n");
    return ERROR_INPUT_FILE_NOT_FOUND;
  }

  fseek(fi, 0L, SEEK_END);
  long inputLength = ftell(fi);
  fseek(fi, 0L, SEEK_SET);

  if(inputLength > MAXIMUM_FILE_SIZE) {
    printf("Input file is too big (128 MB exceeded)!\n");
    return ERROR_INPUT_FILE_TOO_BIG;
  }

  unsigned char* inputROM = (unsigned char*)malloc(inputLength);
  fread(inputROM, inputLength, sizeof(char), fi);
  fclose(fi);

  unsigned int header = (inputROM[0] << 24) | (inputROM[1] << 16) | (inputROM[2] << 8) | inputROM[3];
  printf("Header: 0x%08x\n", header);

  if(header == HEADER_V64) { // inputFile = v64
  	printf("Detected input format: V64\n");
    if(hasExtension(outputFile, ".z64")) {
      printf("Output format: Z64\n");
      wordSwap(inputROM, inputLength);
    }
    else if(hasExtension(outputFile, ".n64")) {
      printf("Output format: N64\n");
      wordSwap(inputROM, inputLength);
      dWordSwap(inputROM, inputLength);
    }
    else if(hasExtension(outputFile, ".v64")){
      printf("Output format cannot be the same as input format!\n");
      return ERROR_IDENTICAL_FORMAT;
    }
    else {
      printf("Unsupported output format! Use either .n64, .v64 or .z64!\n");
      return ERROR_UNSUPPORTED_OUTPUT_FORMAT;
    }
  }
  else if(header == HEADER_Z64) { // inputFile = z64
    printf("Detected input format: Z64\n");
    if(hasExtension(outputFile, ".v64")) {
      printf("Output format: V64\n");
      wordSwap(inputROM, inputLength);
    }
    else if(hasExtension(outputFile, ".n64")) {
      printf("Output format: N64\n");
      dWordSwap(inputROM, inputLength);
    }
    else if(hasExtension(outputFile, ".z64")){
      printf("Output format cannot be the same as input format!\n");
      return ERROR_IDENTICAL_FORMAT;
    }
    else {
      printf("Unsupported output format! Use either .n64, .v64 or .z64!\n");
      return ERROR_UNSUPPORTED_OUTPUT_FORMAT;
    }
  }
  else if(header == HEADER_N64) { // inputFile = n64
    printf("Detected input format: N64\n");
    if(hasExtension(outputFile, ".v64")) {
      printf("Output format: V64\n");
      dWordSwap(inputROM, inputLength);
      wordSwap(inputROM, inputLength);
    }
    else if(hasExtension(outputFile, ".z64")) {
      printf("Output format: Z64\n");
      dWordSwap(inputROM, inputLength);
    }
    else if(hasExtension(outputFile, ".n64")){
      printf("Output format cannot be the same as input format!\n");
      return ERROR_IDENTICAL_FORMAT;
    }
    else {
      printf("Unsupported output format! Use either .n64, .v64 or .z64!\n");
      return ERROR_UNSUPPORTED_OUTPUT_FORMAT;
    }
  }
  else {
    printf("Unsupported input format!\n");
    return ERROR_UNSUPPORTED_INPUT_FORMAT;
  }

  FILE* fo = fopen(outputFile, "w");
  if(!fo) {
    printf("Can't create output file!\n");
    return ERROR_WRITE_OUTPUT;
  }

  fwrite(inputROM, inputLength, 1, fo);
  fclose(fo);

  printf("File converted successfully!\n");
  return 0;
  
}
