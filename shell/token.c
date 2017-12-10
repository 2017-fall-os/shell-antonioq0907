#include <stdio.h>
#include <stdlib.h> 
#include "token.h"

/**Method takes an string and a delimiter. String is separated in tokens, accordingly witht the delimiter**/
char ** tokenize(char *string, char delim) {
    int arrayLength = 0;     // The length of the array(includes each element plus the null terminator)
    arrayLength = totalWords(string,delim);
    return createTokenArr(string, delim, arrayLength);
}

/*Method creates an array of tokens*/
char ** createTokenArr(char *string, char delim, int arrayLength){
    char **tokensArr = (char **)malloc(sizeof(char *) * (arrayLength + 1));
    int tokenIndex = 0;
    int tokenNum = 0; // Number of tokens done
    int tokenStartIndex = -1;
    int tokenLength = 0;
    char *token;
    for (int i = 0; tokenNum < arrayLength; i++) {
        if (string[i] != delim && tokenStartIndex == -1) {      // Find a token and store token initial location
            tokenStartIndex = i;
        } 
        else if ((string[i] == delim || string[i] == '\0') && tokenStartIndex != -1) {  
            tokenLength = i - tokenStartIndex;
            token = (char *)malloc(sizeof(char) * (tokenLength + 1)); 
            
            for (int j = tokenStartIndex, tokenIndex = 0; j < i; j++, tokenIndex++) { // Copy chars to the token
                token[tokenIndex] = string[j];
            }
            
            tokenNum++; 
            tokensArr[tokenIndex] = token;
            tokenIndex++;
            tokenStartIndex = -1;
            token[tokenLength] = '\0';
            } 
        else if (string[i] == '\0') { // Error handling
            break;
        }
    }
    
    tokensArr[arrayLength] = (char *)0;
    return tokensArr;
}

/** Method count the total amount of words, not the total amount of tokens**/
int totalWords(char *string, char delim) {
    int arrayLength = 0;       // The length of the array(includes each element plus the null terminator)
    int isToken = 0;                // Helps to check current element

    // Count number of tokens in the string
    for (int i = 0; ; i++) {
        if (string[i] == '\0') { //Check for the end of the string
            if (isToken) { 
                arrayLength += 1;
            }
            break;
            }

        if (!isToken && string[i] != delim) {
            isToken = 1;
        } else if (isToken && string[i] == delim) {
            arrayLength += 1;
            isToken = 0;
        }
    }

    return arrayLength;
}

/** Method counts the total amount of tokens **/
int numberOfTokens(char **tokenArr) {
    for (int i = 0;;i++) {
        if (tokenArr[i] == (char *)0) {
        return i;
        }
    }
}

/** frees up all memory associated with a token array **/
void freeArray(char **arr) {
    for (int i = 0;;i++) {
        if (arr[i] == (char *)0) {
            free(arr);
            break;
        }
        free(arr[i]);
    }
}

/*Compares strings a and b 
 *returns 0 is a == b, 
 *returns 1 if a is alphabetically first or if terminates first,
 *return -1 if b is alphabetically first or if terminates first.
 **/
char compareString(char *a, char *b) {
    for (int i = 0;;i++) {
        char aTemp = (char) a[i];
        char bTemp = (char) b[i];

        if (aTemp == '\0' && bTemp== '\0') {
            return 0;
        } else if (aTemp == '\0') { // a terminates first
            return 1;
        } else if (bTemp == '\0') { // b terminates first
            return -1;
        } else if (aTemp < bTemp) {
            return 1;
        } else if (bTemp < aTemp) {
            return -1;
        }
    }
}

/*Finds the lenght of the string(Token) with length validations for commands
 *not equal to 0, not empty and not larger than 32 length*/
int stringLength(char *string) {
    for (int i = 0;;i++) {
        if (string[i] == 0 || string[i] == '\0' || string[i] == -1 || string[i] < 32) {
        return i;
        }
    }
}

/*Checks if a string contains the token desired*/
int contains(char *string, char token) {
    for (int i = 0; string[i] != '\0';i++) {
        if (string[i] == token) {
            return 1;
        }
    }
    return 0;
}

/*Concatenates string a and b*/
char* concatenate(char *a, char *b) {
    int sizeA = stringLength(a);
    int sizeB = stringLength(b);
    char *concatenateStr = (char *)malloc(sizeof(char) * (sizeA + sizeB + 1 + 1)); 
    int concatIndex;
    
    for (concatIndex = 0; concatIndex< sizeA; concatIndex++) {
        concatenateStr[concatIndex] = a[concatIndex];
    }

    concatenateStr[concatIndex] = '/';
    concatIndex++;

    for (int j = 0; j < sizeB; j++, concatIndex++) {
        concatenateStr[concatIndex] = b[j];
    }
    concatenateStr[concatIndex] = 0;

    return concatenateStr;
}
