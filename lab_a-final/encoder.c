#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    int encryptType = 0; //+ or -
    int seqIndex = 0; //numbers to be added or substracted
    int debugFlag = 0; //debug mode
    char newChar; //encoded char
    char c;
    char* sequence;
    FILE* input = stdin;
    FILE* output = stdout;

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i],"+D") == 0) //turn debug mode on
            debugFlag = 1;
        else if(strcmp(argv[i],"-D") == 0) //turn debug mode off
            debugFlag = 0;
        if(debugFlag == 1 && strcmp(argv[i],"+D") != 0){ //debug mode is on (+in order to not print the '+D')
            fputs(argv[i], stderr);
            fprintf(stderr, "\n");
            fflush(stderr);
        }
    }

    for(int i = 1; i < argc; i++){ //check if + or - and point to first number in the sequence
        if(strncmp(argv[i],"+e", 2) == 0) {
            encryptType = 1;
            sequence = argv[i] + 2;
        }
        else if(strncmp(argv[i],"-e", 2) == 0){
            encryptType = -1;
            sequence = argv[i] + 2;
        }

        if(strncmp(argv[i],"-i", 2) == 0) { //read input from a specified input file
            input = fopen(argv[i] + 2, "r");
            if(input == NULL) {
                fprintf(stderr, "Failed opening the file\n");
                exit(0);
            }
        }
    
        if(strncmp(argv[i],"-o", 2) == 0) { //get input from user and write encoded string to a specified output file
            output = fopen(argv[i] + 2, "w");
            if(output == NULL) {
                fprintf(stderr, "Failed opening the file\n");
                exit(0);
            }
        }
    }
    c = fgetc(input);
    while(c != EOF){
        //How to encode was taken from presentation in course 'introduction to computer science'
        if((c >= 'A') && (c <= 'Z')){
            if(encryptType == 1) {
                newChar = c - 'A';
                newChar = (newChar + (sequence[seqIndex] - '0')) % 26;
                newChar = newChar + 'A';
                if(newChar < 'A')
                    newChar = newChar + 26;
            }
            else if(encryptType == -1) {
                newChar = c - 'A';
                newChar = (newChar - (sequence[seqIndex] - '0')) % 26;
                newChar = newChar + 'A';
                if(newChar < 'A')
                    newChar = newChar + 26;
            }
        }
        else if((c >= 'a') && (c <= 'z')){
            if(encryptType == 1) {
                newChar = c - 'a';
                newChar = (newChar + (sequence[seqIndex] - '0')) % 26;
                newChar = newChar + 'a';
                if(newChar < 'a')
                    newChar = newChar + 26;
            }
            else if(encryptType == -1) {
                newChar = c - 'a';
                newChar = (newChar - (sequence[seqIndex] - '0')) % 26;
                newChar = newChar + 'a';
                if(newChar < 'a')
                    newChar = newChar + 26;
            } 
        }
        else if((c >= '0') && (c <= '9')){
            if(encryptType == 1) {
                newChar = c - '0';
                newChar = (newChar + (sequence[seqIndex] - '0')) % 10;
                newChar = newChar + '0';
                if(newChar < '0')
                    newChar = newChar + 10;
            }
            else if(encryptType == -1) {
                newChar = c - '0';
                newChar = (newChar - (sequence[seqIndex] - '0')) % 10;
                newChar = newChar + '0';
                if(newChar < '0')
                    newChar = newChar + 10;
            }
        }
        else //char that isn't a letter or a number
            newChar = c; 

        seqIndex++;
        if(sequence[seqIndex] == '\0') //in order to make it a cyclic manner
            seqIndex = 0;
        fputc(newChar, output);
        newChar = '\n';
        c = fgetc(input);
    }

    //close file
    if(output != stdout)
        fclose(output);
    if(input != stdin)
        fclose(input);

    printf("\n");
    return 0;
}
