//
//  main.c
//  hw3
//
//  Created by MacUser on 2018/06/11.
//  Copyright © 2018年 MacUser. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int i,j,answer;
char line[100],token[100],number[100];

void tokenize(char line[]);
int evaluate(char token[]);


int main() {
    printf(">");

    gets(line);
    tokenize(line);
    answer=evaluate(token);
    printf("answer=%d",answer);
    
    return 0;
}

void readnumber(char line[]);
void readPlus(char line[]);
void readMinus(char line[]);
void readMulti(char line[]);
void readDivi(char line[]);



void tokenize(char line[]){
    int index=0;
    while(index<strlen(line)){
        if(isdigit(line[index])!=0){
            readnumber(line);//index couldnt come back
            index+=1;
        }
        else if(strcmp(&line[index],"+")==0){
            readPlus(line);
        }
        else if(strcmp(&line[index],"-")==0){
            readMinus(line);
        }
        else if(strcmp(&line[index],"*")==0){
            readMulti(line);
        }
        else if(strcmp(&line[index],"/")==0){
            readDivi(line);
        }
        else{
            printf("Invalid character found:%c",line[index]);
            exit(1);
        }
    }
}
