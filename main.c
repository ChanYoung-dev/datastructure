#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100      // 스택 요소 저장을 위한 배열의 크기
typedef double Element;           // 스택 요소의 자료형 정의


Element data[MAX_STACK_SIZE];   // 실제 스택요소의 배열
int top;                        // 실제 스택의 top

void error(char str[])          // 오류 상황 처리를 위한 함수
{
    printf("%s\n", str);
    exit(1);
}

void init_stack() { top = -1; }
int is_empty() { return top == -1; }
int is_full() { return top == MAX_STACK_SIZE - 1; }
int size() { return top + 1; }

void push(Element e)
{
    if (is_full())
        error("스택 포화 에러");
    data[++top] = e;
}
Element pop() {
    if (is_empty())
        error("스택 공백 에러");
    return data[top--];
}
Element peek()
{
    if (is_empty())
        error("스택 공백 에러");
    return data[top];
}

double calc_postfix(char expr[])
{
    char c;
    int i=0;
    double val,val1,val2;

    init_stack();
    while(expr[i]!='\0'){
        c=expr[i++];
        if(c>='0'&&c<='9'){
            val = c -'0';
            push(val);
        }
        else if(c=='+' || c=='-'|| c=='*'|| c=='/'){
            val2=pop();
            val1=pop();
            switch(c){
                case '+': push(val1+val2);break;
                case '-': push(val1-val2);break;
                case '*': push(val1*val2);break;
                case '/': push(val1/val2);break;
            }
        }
    }
    return pop();
}

void main()
{
    char expr[2][80]={"8 2 / 3- 3 2 * +", "1 2 / 4 * 1 4 / *"};

    printf("수식: %s = %lf\n",expr[0],calc_postfix(expr[0]));
    printf("수식: %s = %lf\n",expr[1],calc_postfix(expr[1]));
}

