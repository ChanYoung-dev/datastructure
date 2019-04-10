#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
typedef char Element;
Element data[MAX_STACK_SIZE];
int top; // 스택이 현재 가리키는 부분
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
//스택을 쌓고 그대로 추출해준다.(push를 한 후 pop)
void push_pop(char expr[])
{
    int i=0; //문자열의 현재 index
    char ch,prev; // ch는 글자를 저장할 변수형,prev는 스택에서 추출한 글자를 저장할 변수형
    init_stack(); //스택 초기화
    while(expr[i]!='\0'){ // 문자열의 끝부분 '/0'을 도착하기전까지 반복
        ch=expr[i++]; //문자열의 i-1번째 문자를 ch에 입력
        push(ch);  //스택에 ch를 삽입
    }
    // 스택이 비워질때까지 pop을 해주고 출력해준다.
    while(is_empty()!=1){ //스택이 비워질때까지 반복한다.
        prev=pop();  //스택을 pop해주고 prev변수에 삽입
        printf("%c",prev); //추출한 스택내용을 출력
    }
}
int main()
{

    char str[80];               // 문자열을 저장할 배열 선언
    printf("문자열을 입력해주세요:");
    scanf("%s",str); //문자열을 입력받는다.
    push_pop(str); //push를 하고 난뒤 pop해주는 함수 실행
    return 0;

}

