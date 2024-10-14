#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ADD_OR_OVERWRITE_ENV_VAR 1
#define ADD_BUT_DO_NOT_OVERWRITE_VAR 0

extern char** environ;

void printenv(const char* label)
{
    printf("********* %s:\n", label);

    // use this to enumerate all env
    // vars.
    char** next_var = environ;
    while (*next_var != NULL) {
        printf("    %s\n", *next_var);
        next_var++;
    }
}

void add_env_var()
{
    char buf[100];
    sprintf(buf, "NEWVAR_%d", getpid());
    setenv(buf, "hello", ADD_OR_OVERWRITE_ENV_VAR);
}

// OLD, not portable, never do this.
// int main(int argc, char* argv[],
// char* envp[])

int main(int argc, char* argv[])
{
    add_env_var();

    // notice, "NEWVAR" now in the
    // environment. TEST_ME *may* be.
    printenv("PARENT after adding "
             "NEWVAR_<pid>");

    if (getenv("TEST_ME") == NULL) {
        printf("********* TEST_ME not "
               "found; ADDED '=HELLO'\n");
        setenv("TEST_ME", "hello", ADD_BUT_DO_NOT_OVERWRITE_VAR);
    } else {
        printf("********* TEST_ME "
               "found; removed\n");
        unsetenv("TEST_ME");
    }

    fflush(stdout);
    if (fork() == 0) {
        add_env_var();
        printenv("CHILD after NEWVAR_<pid>");
        exit(0);
    }

    wait(NULL);
    printenv("PARENT AFTER CHILD EXITS");
    return 0;
}
