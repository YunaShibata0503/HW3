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

int i,j;
double number[100];
char line[100],token[100];

void tokenize(char line[]);
double evaluate(char token[],double number[]);


int main() {
    double answer;
    printf(">");
    gets(line);
    printf("%s",line);//ok
    
    tokenize(line);
    for(j=0;j<4;j++){
        printf("\n%c %lf",token[j],number[j]);
    }
    
    answer=evaluate(token,number);
    printf("\nanswer=%lf",answer);
    
    return 0;
}

void readnumber(char line[],int *index,int *i){
    double keta=1;
    int flag=0;
    double num=0;
    
    while(((isdigit(line[*index])!=0)||(line[*index]=='.'))&&(*index<strlen(line))){
       if(line[*index]=='.'){
            flag=1;
        }
        else{
            num=num*10.0+line[*index]-48.0;
            if(flag==1){
                keta*=0.1;
            }
        }
        *index+=1;
        
    }
    token[*i]='n';
    number[*i]=num*keta;
    *i+=1;
    
    
}

void readPlus(char line[],int *index, int *i){
    token[*i]='+';
    *i+=1;
    *index+=1;
}

void readMinus(char line[],int *index, int *i){
    token[*i]='-';
    *i+=1;
    *index+=1;
}

void readMulti(char line[],int *index, int *i){
    token[*i]='*';
    *i+=1;
    *index+=1;
}

void readDivi(char line[],int *index, int *i){
    token[*i]='/';
    *i+=1;
    *index+=1;
}



void tokenize(char line[]){
    int index=0;
    i=0;
    int l=strlen(line);
    
    while(index<strlen(line)){
        
        if(isdigit(line[index])!=0){
            readnumber(line,&index,&i);
        }
        else if(line[index]=='.'){
            readnumber(line,&index,&i);
        }
        else if(line[index]=='+'){
            readPlus(line,&index,&i);
        }
        else if(line[index]=='-'){
            readMinus(line,&index,&i);
        }
        else if(line[index]=='*'){
            readMulti(line,&index,&i);
        }
        else if(line[index]=='/'){
            readDivi(line,&index,&i);
        }
        else{
            printf("Invalid character found:%c\n",line[index]);
            //wanna exit
        }
        
    }
}

double evaluate(char token[],double number[]){
    double ans=1;
    int index=2,index1=2;
    int flag=0;
    
    if(token[1]=='*'||token[1]=='/') ans=number[0];
    
    //乗除計算、一つの数字number[index1]にまとめる
    while(index<strlen(line)){
        if(token[index]=='n'){
            if(token[index-1]=='*'){
                flag+=1;
                if(flag==1)index1=index-2;
                if(ans==1)ans=number[index1];
                ans*=number[index];
                number[index1]=ans;
            }
            else if(token[index-1]=='/'){
                flag+=1;
                if(flag==1)index1=index-2;
                if(ans==1)ans=number[index1];
                ans/=number[index];
                number[index1]=ans;
            }
            
            else{
                ans=1;
                flag=0;
            }
            
        }
        index+=1;
    }
    
    //足し算引き算
    index=1;
    ans=number[0];
    while(index<strlen(line)){
        if(token[index-1]=='+'){
            ans+=number[index];
        }
        else if(token[index-1]=='-'){
            ans-=number[index];
        }
        index+=1;
    }
    return ans;
    
}



