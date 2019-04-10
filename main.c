#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef char Element;
Element data[MAX_STACK_SIZE];
int top;

void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}
void init_stack(){top=-1;}
int is_empty(){return top==-1;}
int is_full(){return top==MAX_STACK_SIZE-1;}
int size(){return top+1;}

void push(Element e)
{
    if(is_full())
        error("스택 포화 에러");
    data[++top]=e;
}
Element pop(){
    if(is_empty())
        error("스택 공백 에러");
    return data[top--];
}
Element peek()
{
    if(is_empty())
        error("스택 공백 에러");
    return data[top];
}
/*
void insert(char str[]){

    printf("문자열을 입력해주세요:");
    scanf("%s",&str);
    printf("%s",&str);

}*/

void check_matching(char expr[])
{
    int i=0;
    char ch,prev;

    init_stack();
    while(expr[i]!='\0'){
        ch=expr[i++];
        push(ch);

    }
    while(is_empty()!=1){
        prev=pop();
        printf("%c",prev);

    }



}
int main()
{

    char str[80];

    printf("문자열을 입력해주세요:");
    scanf("%s",str);


    check_matching(str);


    return 0;

}


