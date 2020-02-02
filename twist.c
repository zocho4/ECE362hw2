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
    char *inputFile = NULL; //this will point to dynamic char array
    int fdIN = STDIN_FILENO;
    char *outputFile = NULL; //same deal for output file
    int fdOUT = STDOUT_FILENO;
    int currentArg = 1; //for tracking which argv we are checking
    int blockSize = 10;

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
                exit(-1);
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
                exit(-1);
            }
            strcpy(outputFile, argv[currentArg+1]);
            printf("The output file name is: %s\n", outputFile);
            ++currentArg; ++currentArg;
        }
	else if (strcmp(argv[currentArg], "-b") == 0) {
            printf("The block size is %s as a string.\n", argv[currentArg+1]);
            blockSize = atoi(argv[currentArg+1]);
            if (blockSize<1) {
                write(STDERR_FILENO, "Not a valid block size.\n", 24);
                blockSize = 10;
            }
            printf("The block size is %d as an integer.\n", blockSize);
            ++currentArg; ++currentArg;
        }
	else { // default case
            printf("Not a valid command line argument!\n");
            //skip to checking the next argv
            ++currentArg;
        }

    } //close while loop for parsing argv

    //if IO files were specified then open them
    if (inputFile != NULL) {
        fdIN = open();
    }
    if (outputFile != NULL) {
        fdOUT = open();
    }
    //check value of all arguments
    printf("Input file name is: %s\n", inputFile);
    printf("Output file name is: %s\n", outputFile);
    printf("Block size is: %d\n", blockSize);

    return(0);
}


/*
twist checklist
( ) parse command line args
( ) move parsing into a function


*/
