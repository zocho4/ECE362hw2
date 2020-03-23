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
void flushBuf(char *buffer, int bufSize);
void reverseBytes(char *readBuf, char *writeBuf, int blockSize);

////////////////////MAIN////////////////////
int main(int argc, char *argv[]) {

    //declare all the variables for holding command line arguments
    char *inputFile = NULL; //this will point to string in dynamic array if not stdin
    int fdIN = STDIN_FILENO;
    char *outputFile = NULL; //this will point to string if not stdout
    int fdOUT = STDOUT_FILENO;
    int currentArg = 1; //for tracking which argv we are checking
    int blockSize = 10; //default will be modified from input args

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
        fdIN = open(inputFile, O_RDONLY/*, S_IRUSR|S_IRGRP|S_IROTH*/);
        if (fdIN < 0) { //if open error then print and exit
            write(STDERR_FILENO, "Unable to open input file.\n", 27);
            exit(1);
        }
    }
    if (outputFile != NULL) {
        //open output file for write only with write permissions for everyone
        //user also needs read permissions so I can check the result later
        //we want this file to be empty every time and created if none exists
        fdOUT = open(outputFile, O_WRONLY|O_CREAT|O_TRUNC/*, S_IWUSR|S_IWGRP|S_IWOTH|S_IRUSR*/);
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

    //declare variables for tracking number of bytes read/written
    ssize_t nBytesRead = 0;
    ssize_t nBytesWritten = 0;

    //malloc space for the buffers used to read and write
    char *readBuf = (char*)malloc(blockSize*sizeof(char));
    char *writeBuf = (char*)malloc(blockSize*sizeof(char));

    //test out the reverseByte function
    flushBuf(readBuf, blockSize);
    flushBuf(writeBuf, blockSize);
    printf("readBuf after flushing is -%s-\n", readBuf);
    printf("writeBuf after flushing is -%s-\n", writeBuf);
    readBuf[0] = 'a';
    readBuf[1] = 'b';
    reverseBytes(readBuf, writeBuf, blockSize);
    printf("readBuf after reverse is -%s-\n", readBuf);
    printf("writeBuf after reverse is -%s-\n", writeBuf);

/*
    //read in twice, copy over and write out twice
    nBytesRead = read(fdIN, (void*)readBuf, blockSize);
    printf("We wanted to read %d byte(s) and read %ld byte(s)\n", blockSize, nBytesRead);
    reverseBytes(readBuf, writeBuf, blockSize);
    flushBuf(readBuf, blockSize);
    //printf("Byte(s) read then written are:\n");
    nBytesWritten = write(fdOUT, (void*)writeBuf, blockSize);
    flushBuf(writeBuf, blockSize);
    //printf("\n");
    printf("We wanted to write %d bytes and wrote %ld byte(s)\n", blockSize, nBytesWritten);

    nBytesRead = read(fdIN, (void*)readBuf, blockSize);
    printf("We wanted to read %d byte(s) and read %ld byte(s)\n", blockSize, nBytesRead);
    reverseBytes(readBuf, writeBuf, blockSize);
    flushBuf(readBuf, blockSize);
    printf("readBuf after flushing is -%s-.\n", readBuf);
    //printf("Byte(s) read then written are:\n");
    nBytesWritten = write(fdOUT, (void*)writeBuf, blockSize);
    flushBuf(writeBuf, blockSize);
    printf("writeBuf after flushing is -%s-\n", writeBuf);
    //printf("\n");
    printf("We wanted to write %d bytes and wrote %ld byte(s)\n", blockSize, nBytesWritten);
*/
/*
    while ( ( nBytesRead = read(fdIN, (void*)readBuf, blockSize) ) > 0 ) {

    }
*/

    //(close files) and free all allocated memory
    free(inputFile);
    free(outputFile);
    free(readBuf);
    free(writeBuf);
    //close();
    //close();

    exit(0);
}
////////////////////END MAIN////////////////////



////////Functions////////
/*
Inputs: pointer to dynamic char array
Outputs: none
This function clears the contents of a read/write buffer. This way nothing
is left over from a previous read and nothing unexpected gets written.
*/
void flushBuf(char *buffer, int bufSize) {
    for (int i=0; i<bufSize; ++i) {
        buffer[i] = '\0';
    }
    return;
}

/*
Inputs: readBuf (bytes read), writeBuf (bytes written) and blockSize (size of both)
Outputs: none
This is the function that does the actual twisting. It copies readBuf into
writeBuf in reverse order.
*/
void reverseBytes(char *readBuf, char *writeBuf, int blockSize) {
    for (int i=0; i<blockSize; ++i) {
        printf("BEFORE: writeBuf[%d] = -%c-\n", i, writeBuf[i]);
        writeBuf[i] = readBuf[blockSize-i];
        printf("AFTER: writeBuf[%d] = -%c-\n", i, writeBuf[i]);
    }
    return;
}
