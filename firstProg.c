/*
This is to test making a pipe.
This is the first program that will get input from stdin (or a filename).
It will send output to stdout but that will actually get piped to the second program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char charBuf[2];

    //can also try this with an input file
//    int fdIN = open("testInputFile", O_RDONLY, S_IRUSR|S_IRGRP|S_IROTH);
    int nBytesRead = read(STDIN_FILENO, charBuf, 2);
    charBuf[0] = charBuf[0] + 1;
    //charBuf[1] = '\0';
    int nBytesWritten = write(STDOUT_FILENO, charBuf, 2);
    return 0;
}

