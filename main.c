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
int check_matching(char filename[])
{
    int i,j = 0, prev;
    char ch;
    char string[100];
    FILE *fp = fopen(filename, "r");
    for (i = 0; (i < (sizeof(string)-1) &&((ch = fgetc(fp)) != EOF) && (ch != '\n')); i++) {
            ch = fgetc(fp);
            if(ch==39)
                while(ch!=39);
            else
                string[i] = ch;


    }
    string[i] = '\0';
    fclose(fp);
    printf("string?%s",string);
    init_stack();
    while (string[j] != '\0') {
        ch = string[j++];
        if (ch == '[' || ch == '(' || ch == '{')
            push(ch);
        else if (ch == ']' || ch == ')' || ch == '}') {
            if (is_empty())
                return 2;    // 조건 2 위반
            prev = pop();
            if ((ch == ']' && prev != '[')
                || (ch == ')' && prev != '(')
                || (ch == '}' && prev != '{')) {
                return 3;    // 조건 3 위반
            }
        }

    }
    if (is_empty() == 0) return 1;        // 조건 1 위반
    return 0;                // 괄호 정상
}

int main()
{



    int errCode, i;


    errCode = check_matching("asdf.txt");
    if (errCode == 0)
        printf(" 정상 ");
    else
        printf(" 오류:  (조건%d 위반)\n", errCode);



    return 0;
}


