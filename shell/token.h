#ifndef MYTOC_H_INCLUDED
#define MYTOC_H_INCLUDED

/*Token generator that "return(s)allocated strings containing each token from the input string"*/
char ** tokenize(char *str, char delim);

/*Method creates an array of tokens*/
char ** createTokenArr(char *string, char delim, int pointerArrLength);

/** Method counts the total amount of tokens **/
int numberOfTokens(char **tokenArr);

/** Method count the total amount of words, not the total amount of tokens**/
int totalWords(char *str, char delim);

/** frees up all memory associated with a token arry **/
void freeArray(char **arr);

/*Compares strings a and b 
 *returns 0 is a == b, 
 *returns 1 if a is alphabetically first or if terminates first,
 *return -1 if b is alphabetically first or if terminates first.
 **/
char compareString(char *a, char *b);

/*Finds the lenght of the string(Token) with lenght validations for commands
 *not equal to 0, not emprym and not larger than 32 length*/
int stringLength(char *string);

/*Checks if a string contains the token desired*/
int contains(char *string, char token);

/*Concatenates string a and b*/
char* concatenate(char *a, char *b);

#endif // BTREE_H_INCLUDED
