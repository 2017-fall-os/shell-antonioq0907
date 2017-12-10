#ifndef MYSHELL_H_INCLUDED
#define MYSHELL_H_INCLUDED

/*Executes commands*/
void execute(char *command, char **envp, char **path);


int pathExecute(char **tokenizedCommand, char **envp, char **path);

char** backgroundPath(char** envp);

int backgroundTask( char *shellInput,int numberOfBackgroundTasks,char **backgroundTokenized,char** envp,char **path );

/*Method change directory */
int changeDir(char ** dir);

/*Reads input from the console */
int readInput(char *string, int limit);


#endif // BTREE_H_INCLUDED
 
