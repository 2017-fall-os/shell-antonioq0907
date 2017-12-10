#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include "token.h"
#include "shell.h"

#define MAX_COMMAND_SIZE 512

char *prompt = "$ \0";

int main(int argc, char** argv, char** envp) {
    char *shellInput = (char *)malloc( sizeof(char) * ( MAX_COMMAND_SIZE ) );
    char **path = backgroundPath(envp);

    while (1) { //Wait for input or shell termination
        printf("%s", prompt);
        int valid = readInput(shellInput, MAX_COMMAND_SIZE);
        if (compareString(shellInput, "exit\0") == 0 || compareString(shellInput, "EXIT\0") == 0|| valid == 0) { // EXIT COMMAND
            break;
        } else if (shellInput[0] == '\0') { //COMMAND EMPTY. WAIT FOR INPUT
            continue;
        }

        char **dir = tokenize(shellInput, ' ');
        if(changeDir(dir)){
            continue;
        }
        
        char **backgroundTokenized = tokenize(shellInput, '&');
        int numberOfBackgroundTasks = numberOfTokens(backgroundTokenized);
        if(backgroundTask(shellInput,numberOfBackgroundTasks,backgroundTokenized,envp,path)){
            continue;
        }
        if (valid < 0) {
            break;
        }
    }
    free(shellInput);
    freeArray(path);
    return 0;

}

/*Executes commands*/
void execute(char *command, char **envp, char **path) {
    // Check for pipes
    char **tokenizedPipe = tokenize(command, '|');
    char **tokenizedCommand = tokenize(command, ' ');
    int numberOfPipes = numberOfTokens(tokenizedPipe);
    int duplicate0 = dup(0);
    int duplicate1 = dup(1);
    int fileDes[2];
    int pipeIndex, val, waitArg,pathValue;
    if (contains(command, '|') == 1 && totalWords(command, '|') > 0) { // PIPES FOUND
        for (pipeIndex = 0; pipeIndex< numberOfPipes - 1; pipeIndex++) {
            val = pipe(fileDes);
            pid_t pid = fork();
            if (pid < 0 || val != 0) {
                printf("PIPE FAILED \n");
                return;
            } else if (pid == 0) {
                close(1);
                val = dup(fileDes[1]);
                close(fileDes[1]);
                close(fileDes[0]);

                execute(tokenizedPipe[pipeIndex], envp, path);
                return;
            } else {
                wait(&waitArg);
                if (WEXITSTATUS(waitArg) != 0) {
                    printf("\nError Code: %d\n", WEXITSTATUS(waitArg));
                }
                close(0);
                val = dup(fileDes[0]);
                close(fileDes[0]);
                close(fileDes[1]);
            }
        }   
        execute(tokenizedPipe[pipeIndex], envp, path);
        
        dup2(duplicate0, 0);
        dup2(duplicate1, 1);
        freeArray(tokenizedPipe);
        return;
    } else {        //NO PIPES FOUND
        freeArray(tokenizedPipe);
        pathValue = pathExecute(tokenizedCommand, envp, path);
        if (pathValue != 0) {
            printf("Command not found \n");
        }
        freeArray(tokenizedCommand);
        return;
    }
}

int pathExecute(char **tokenizedCommand, char **envp, char **path) {
    int pathValue = execve(tokenizedCommand[0], tokenizedCommand, envp);
    char * string;
    for (int i = 0; pathValue != 0 && path[i] != (char *)0; i++) {
        string = concatenate(path[i], tokenizedCommand[0]);
        pathValue = execve(string, tokenizedCommand, envp);
        free(string);
    }
    return pathValue;
}

char** backgroundPath(char** envp) {
    char **path;
    int actualTokens;
    int tokenLen;
    for (int i = 0; envp[i] != (char*)0; i++) {
        char ** envElement = tokenize(envp[i], '=');

        if (compareString("PATH\0", envElement[0]) == 0) {
            path = tokenize(envElement[1], ':');
        }

        if (compareString("PS1\0", envElement[0]) == 0) {
            actualTokens = numberOfTokens(envElement);
            if (actualTokens == 1) {
                prompt = "\0";
            } else {
                tokenLen = stringLength(envElement[1]);

                int i = 0;
                prompt = (char *)malloc(sizeof(char) * (tokenLen + 1));
                for (i = 0; i < tokenLen; i++) {
                    prompt[i] = envElement[1][i];
                }
                prompt[i] = '\0';
            }   
        }
        freeArray(envElement);
    }
    return path;
}

int backgroundTask( char *shellInput,int numberOfBackgroundTasks,char **backgroundTokenized,char** envp,char **path ){
    if (contains(shellInput, '&') == 1) {
        for (int i = 0; i < numberOfBackgroundTasks; i++) {
            int rc = fork();
            if (rc < 0) {
                printf("Process could not be created!\n");
                freeArray(backgroundTokenized);
                break;
            } else if (rc == 0) {
                execute(backgroundTokenized[i], envp, path);
                return 0;
            }
        }

        freeArray(backgroundTokenized);
        return 1;
    } else {    
        freeArray(backgroundTokenized);
        int rc = fork();
        if (rc < 0) {
            printf("Process not created! \n");
            return 1 ;
        } else if (rc == 0) {
            execute(shellInput, envp, path);
            return 0;
        } else {
            int waitArg;
            wait(&waitArg);
            if (WEXITSTATUS(waitArg) != 0) {
            printf("Error Code: %d\n", WEXITSTATUS(waitArg));
            }
        }
    }
}

/*Method change directory */
int changeDir(char ** dir){
    if (compareString(dir[0], "cd\0") == 0) {
        int ret = chdir(dir[1]);
        if(ret != 0) {
            printf("Couldn't change directory\n");
        }
        freeArray(dir);
        return 1;
    }
    freeArray(dir);
    return 0;
}

/*Reads input from the console */
int readInput(char *string, int limit) {
    char c = getchar();
    int count = 0;

    while (c >= 32 && count < limit - 1) {
        string[count] = c;
        count++;

        c = getchar();
    }

    string[count] = '\0';  

    if (c == -1 && count > 0) {
        return count * -1;
    } 
    else if (c == -1 && count == 0) {
        return 0;
    }

return 1;
}
