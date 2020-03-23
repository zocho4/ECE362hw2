
/*
This is to test making a pipe with my own executables.
The code for the pipe part is a logical progression beyond newProcess.c
First a pipe is created, then the process is forked. 
The child will write to the pipe so it closes stdout and dup(pipe[1])
The parent will read from the pipe so it closes stdin and dup(pipe[0])
This is essentially what TX will do!
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //needed for pipe()
#include <fcntl.h> //needed for open() and creat()
#include <sys/wait.h> //needed for wait()

int main(void) {
    printf("This is the original process, pid=%d\n", (int)getpid());


    //make a pipe and check that it worked
    int testPipe[2];
    if ( pipe(testPipe)<0 ) {
        write(STDERR_FILENO, "Pipe error.\n", 12);
        exit(1);
    }
    printf("testPipe[0]=%d, testPipe[1]=%d\n", testPipe[0], testPipe[1]);


    //fork the process and check that it worked
    int rc = fork();
    if (rc<0) {
        write(STDERR_FILENO, "Fork failed.\n", 13);
        exit(1);
    }

    ////CHILD////
    else if (rc==0) {
        printf("This is the child process, pid=%d, child of %d\n", (int)getpid(), (int)getppid());
        printf("testPipe[0]=%d, testPipe[1]=%d\n", testPipe[0], testPipe[1]);

        //close stdout and replace it with writing end of the pipe
        close(STDOUT_FILENO);
        int pipeWriteCopy = dup(testPipe[1]);
        //close the reading end of the pipe
        close(testPipe[0]);

        //printf will now print to the pipe! have to use stderr to check
        fprintf(stderr, "child closed stdout\npipe writing end [1] copied to %d\n", pipeWriteCopy);
        execlp("./firstProg", "./firstProg", (char*)0);
        fprintf(stderr, "This shouldn't print.\n");
    }

    ////PARENT////
    else {
        printf("This is the parent, pid=%d, parent of %d.\n", (int)getpid(), rc);
        wait(NULL);
        printf("The parent is done waiting.\n");
        printf("testPipe[0]=%d, testPipe[1]=%d\n", testPipe[0], testPipe[1]);

        //close stdin and replace it with the reading end of the pipe
        close(STDIN_FILENO);
        int pipeReadCopy = dup(testPipe[0]);
        //close writing end of the pipe
        close(testPipe[1]);
        printf("Parent closed stdin\npipe reading end [0] copied to fd %d\n", pipeReadCopy);

        execlp("./secondProg", ".secondProg", (char*)0);
        printf("This shouldn't print.\n");
    }

    exit(0);
}
