#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    // But to use execve, we need a NULL
    // after that, so we WOULD add one
    // BUT we're going to skip "us"
    // (argv[0], our executable) So we
    // allocate the same size.
    char** newargv = (char**)malloc(
        sizeof(char*) * argc);

    // we "copy it down" by one
    for (int ix = 1; ix < argc; ix++) {
        newargv[ix - 1]
            = (char*)argv[ix];
    }
    newargv[argc - 1] = NULL;

    int child_pid = fork();
    if (child_pid == 0) {
        // assumes that the first param
        // is a absolute path to the
        // executable
        execve(
            newargv[0], newargv, NULL);

        printf("Exec failed\n");
        _exit(1);
    }

    printf("%s pid is %d. forked %d. "
           "Parent exiting\n",
        argv[0], getpid(), child_pid);
    return 0;
}
