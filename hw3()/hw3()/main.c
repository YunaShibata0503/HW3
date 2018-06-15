//
//  main.c
//  hw3()
//
//  Created by MacUser on 2018/06/13.
//  Copyright © 2018年 MacUser. All rights reserved.
//


#include <stdio.h>
#include <string.h>
#include <ctype.h>

int i,j;
double number[100];
char line[100],token[100];

void tokenize(char line[]);
double evaluate(char token[],double number[], int index);


int main() {
    double answer;
    printf(">");
    gets(line);
    printf("%s",line);//ok
    
    tokenize(line);
    
    answer=evaluate(token,number,0);
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
void readopen(char line[],int *index, int *i){
    token[*i]='(';
    *i+=1;
    *index+=1;
}
void readclose(char line[],int *index, int *i){
    token[*i]=')';
    *i+=1;
    *index+=1;
}

void tokenize(char line[]){
    int index=0;
    i=0;
    
    
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
        else if(line[index]=='('){
            readopen(line,&index,&i);
        }
        else if(line[index]==')'){
            readclose(line,&index,&i);
        }
        else{
            printf("Invalid character found:%c\n",line[index]);
            //wanna exit but into loop
        }
        
    }
}

// ()内の計算
double evaluateparen(char token[],int index,double number[]){
    double ans=1;
    int index1=2;
    int index2=index;
    int flag=0;//乗除計算の始まりのindex保存に利用
    int l=0;// '('から')'までの長さを保存
    if(token[1]=='*'||token[1]=='/') ans=number[0];
    printf("\nindex=%d\n",index);
    //乗除計算、一つの数字number[index1]にまとめる
    while(token[index]!=')'){
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
        l++;
    }
    
    //足し算引き算
    index=index2+1;
    ans=0;
    while(token[index]!=')'){
        if(token[index]=='n'){
            if(token[index-1]=='+'||token[index-1]=='('){
                ans+=number[index];
            }
            else if(token[index-1]=='-'){
                ans-=number[index];
            }
        }
        index+=1;
    }
    // '('の位置に()内の結果保存
    token[index2]='n';
    number[index2]=ans;
    
    // '('の隣から')'より後の値を移していく
    for(j=index2+1;j<10;j++){
        token[j]=token[j+l];
        number[j]=number[j+l];
    }
    
    return ans;
}

// ()の計算順序を決めてevaluateparen()に送る
double orderparen(char token[],int index,double number[]){
    double ans=1;
    int flag=0;
    int index2=index;
    while(token[index2]!=')'){
        index2+=1;
        if(token[index2]=='('){
            flag+=1;
            index=index2;
            ans=orderparen(token,index,number);
        }
    }
    if(flag==0){
        ans=evaluateparen(token,index,number);
    }
    return ans;
}

//全体の計算
double evaluate(char token[],double number[],int index){

    double ans=1.0;
    while(index<strlen(line)){
        if(token[index]=='('){
            ans=orderparen(token,index,number);
        }
        index+=1;
    }
    
    int index1=2;
    int flag=0;
    if(token[1]=='*'||token[1]=='/') ans=number[0];
    else ans=1;
    
    //乗除計算、一つの数字number[index1]にまとめる
    index=1;
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
        if(token[index]=='n'){
            if(token[index-1]=='+'){
                ans+=number[index];
            }
            else if(token[index-1]=='-'){
                ans-=number[index];
            }
        }
        index+=1;
    }
    return ans;
    
}



