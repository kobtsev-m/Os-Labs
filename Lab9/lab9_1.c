#include <unistd.h>
#include <stdio.h>

#define SUCCESS_STATUS (0)
#define WRONG_ARGUMENTS_NUMBER_ERROR (1)
#define FORK_ERROR (2)
#define WAIT_ERROR (3)
#define EXECVP_ERROR (4)

#define FORK_ERROR_VALUE (-1)
#define WAIT_ERROR_VALUE (-1)
#define CHILD_FORK_RESULT_VALUE (0)

#define REQUIRED_ARGUMENTS_NUMBER (2)


int executeCommand(char *commandName, char *argv[]) {
    pid_t forkRes = fork();
    if (forkRes == FORK_ERROR_VALUE) {
        perror("Error on fork");
        return FORK_ERROR;
    }
    if (forkRes == CHILD_FORK_RESULT_VALUE) {
        execvp(commandName, argv);
        perror("Error on execvp");
        return EXECVP_ERROR;
    }
    return SUCCESS_STATUS;
}

int main(int argc, char *argv[]) {

    if (argc != REQUIRED_ARGUMENTS_NUMBER) {
        fprintf(stderr, "Wrong arguments number\n");
        return WRONG_ARGUMENTS_NUMBER_ERROR;
    }

    char *commandName = "cat";
    char *fileName = argv[1];
    char *commandArgv[] = {commandName, fileName, NULL};

    printf("Output of specified file:\n");

    int executeCommandRes = executeCommand(commandName, commandArgv);
    if (executeCommandRes != SUCCESS_STATUS) {
        return executeCommandRes;
    }

    return SUCCESS_STATUS;
}
