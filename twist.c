/*
Zoe Schmertzler
ilanaz@pdx.edu
ECE362 HW2 Prog1
1/31/20

This is the main function for twist.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

//////////Prototypes//////////
//void parseArgs();


int main(int argc, char *argv[]) {

    //declare all the variables for holding command line arguments
    char *inputFile = NULL; //this will point to string in dynamic array if not stdin
    int fdIN = STDIN_FILENO;
    char *outputFile = NULL; //this will point to string if not stdout
    int fdOUT = STDOUT_FILENO;
    int currentArg = 1; //for tracking which argv we are checking
    int blockSize = 10; //to be modified by

    //check and parse the command line arguments
    printf("argc is %d\n", argc);
    //better to use a while because we aren't exactly iterating through each argv
    while (currentArg < argc) {
        printf("argv[%d] is %s\n", currentArg, argv[currentArg]);
        //check for each flag case
        if (strcmp(argv[currentArg], "-i") == 0) {
            //malloc space for the input file name
            if ( (inputFile = (char*)malloc(sizeof(argv[currentArg+1]))) == NULL ) {
                write(STDERR_FILENO, "Could not allocate memory for input file name.\n", 47);
                exit(1);
            }
            strcpy(inputFile, argv[currentArg+1]);
            printf("The input file name is: %s\n", inputFile);
            //increment currentArg to check next flag
            ++currentArg; ++currentArg;
        }
	else if (strcmp(argv[currentArg], "-o") == 0) {
            //same deal for output file
            if ( (outputFile = (char*)malloc(sizeof(argv[currentArg+1]))) == NULL ) {
                write(STDERR_FILENO, "Could not allocate memory for output filename.\n", 48);
                exit(1);
            }
            strcpy(outputFile, argv[currentArg+1]);
            printf("The output file name is: %s\n", outputFile);
            ++currentArg; ++currentArg;
        }
	else if (strcmp(argv[currentArg], "-b") == 0) {
            printf("The block size is %s as a string.\n", argv[currentArg+1]);
            blockSize = atoi(argv[currentArg+1]);
            if (blockSize<1 | blockSize>1024) {
                write(STDERR_FILENO, "Not a valid block size.\n", 24);
                blockSize = 10;
            }
            printf("The block size is %d as an integer.\n", blockSize);
            ++currentArg; ++currentArg;
        }
	else { // default case
            printf("%s:\n", argv[currentArg]);
            write(STDERR_FILENO, "Not a valid argument.\n", 22);
            //skip to checking the next argv
            ++currentArg;
        }

    } //close while loop for parsing argv

    //if IO files were specified then open them
    if (inputFile != NULL) {
        //open input file for read only with read permissions for everyone
        fdIN = open(inputFile, O_RDONLY, S_IRUSR|S_IRGRP|S_IROTH);
        if (fdIN < 0) { //if open error then print and exit
            write(STDERR_FILENO, "Unable to open input file.\n", 27);
            exit(1);
        }
    }
    if (outputFile != NULL) {
        //open output file for write only with write permissions for everyone
        //we want this file to be empty every time and crated if none exists
        fdOUT = open(outputFile, O_WRONLY|O_CREAT|O_TRUNC, S_IWUSR|S_IWGRP|S_IWOTH);
        if  (fdOUT < 0) { //if open error then print and exit
            write(STDERR_FILENO, "Unable to open output file.\n", 28);
            exit(1);
        }
    }
    //check value of all arguments
    printf("Input file name is: %s\n", inputFile);
    printf("fdIN is: %d\n", fdIN);
    printf("Output file name is: %s\n", outputFile);
    printf("fdOUT is: %d\n", fdOUT);
    printf("Block size is: %d\n", blockSize);


    //free all allocated memory
    free(inputFile);
    free(outputFile);

    exit(0);
}


/*
twist checklist
( ) parse command line args
( ) move parsing into a function


*/
