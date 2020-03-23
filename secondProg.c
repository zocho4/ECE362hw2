/*
This is to test making a pipe.
This is the second program that will get input from stdin
which is actually the piped output of the first program.
It will send output to regular stdout (or output file).
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char charBuf[2];
    int nBytesRead = read(STDIN_FILENO, charBuf, 2);
    charBuf[0] = charBuf[0] + 1;
    //charBuf[1] = '\0';
    int nBytesWritten = write(STDOUT_FILENO, charBuf, 2);
    return 0;
}
