#include <stdio.h>
#include <string.h>

#define MAXLEN (int)1e3
#define STACKSIZE (int)1e3

#define PLUS (int)1<<30
#define MINUS (int)(1<<30)-1
#define MUL (int)(1<<30)-2
#define DIV (int)(1<<30)-3
#define OPEN (int)(1<<30)-4
#define CLOSE (int)(1<<30)-5

char isNumber(char c) { return c >= '0' && c <= '9'; };
char isMulDiv(int c) { return c == MUL || c == DIV; };
char isOperator(int c) { return c == MUL || c == DIV || c == MINUS || c == PLUS; }

double calc(char* exp)
{
    int len = strlen(exp);

    double stack[STACKSIZE];
    int top = -1;

    for (int i = 0; i < len; i++)
    {
        if (exp[i] == '"') continue;

        if (isNumber(exp[i]))
        {
            int n_number = 0;
            double p_number = 0;

            int j = i;
            char meetPoint = 0;

            while (j < len && ((exp[j] >= '0' && exp[j] <= '9') || exp[j] == '.'))
            {
                if (exp[j] == '.')
                {
                    meetPoint = 1;
                    j++;
                    continue;
                }
                if (meetPoint==0)
                {
                    n_number *= 10;
                    n_number += (exp[j] - '0');
                    j++;
                }
                else
                {
                    p_number *= 10;
                    p_number += (exp[j] - '0');
                    j++;
                }
            }
            i = j - 1;

            while (p_number > 1) p_number /= 10;
            double now = n_number + p_number;

            char MulDiv = 0;
            if (top>=0) MulDiv = isMulDiv(stack[top]);

            if (MulDiv)
            {
                if (stack[top] == MUL)
                {
                    stack[top-1] = stack[top - 1] * now;
                }
                else stack[top - 1] = stack[top - 1] / now;
                top--;
            }
            else stack[++top] = now;

        }
        else if (exp[i] == '(') stack[++top] = OPEN;
        else if (exp[i] == ')')
        {
            double tmpstack[STACKSIZE];
            int tmptop = -1;

            while (stack[top] != OPEN)
            {
                tmpstack[++tmptop] = stack[top];
                top--;
            }
            top--;


            double result = 0;
            int oper = 1;
            while (tmptop >= 0)
            {
                if (tmpstack[tmptop] == PLUS || tmpstack[tmptop] == MINUS )
                {
                    if (tmpstack[tmptop] == PLUS) oper = 1;
                    else oper = -1;
                }
                else result += (oper)*(tmpstack[tmptop]);
                tmptop--;
            }

            if (top >= 0 && isMulDiv(stack[top]))
            {
                if (stack[top] == MUL) stack[top - 1] = stack[top - 1] * result;
                else stack[top - 1] = stack[top - 1] / result;
                top--;
            }
            else stack[++top] = result;
        }
        else if (
                exp[i] == '+' || exp[i] == '-' ||
                exp[i] == '*' || exp[i] == '/')
        {
            if (exp[i] == '+') stack[++top] = PLUS;
            else if (exp[i] == '-') stack[++top] = MINUS;
            else if (exp[i] == '*') stack[++top] = MUL;
            else stack[++top] = DIV;
        }
        else
        {
            printf("이상한 입력이 있습니다.");
            return -1;
        };
    }

    double tmpstack[STACKSIZE];
    int tmptop = -1;

    while (top>=0 )
    {
        tmpstack[++tmptop] = stack[top];
        top--;
    }

    double result = 0;
    int oper = 1;
    while (tmptop >= 0)
    {
        if (tmpstack[tmptop] == PLUS || tmpstack[tmptop] == MINUS )
        {
            if (tmpstack[tmptop] == PLUS) oper = 1;
            else oper = -1;
        }
        else result += (oper)*(tmpstack[tmptop]);
        tmptop--;
    }
    return result;

}

void ESpace(char *ap_st)
{
    char *p = ap_st;
    while(*ap_st !=0){
        if(*ap_st != ' '){
            if(p!= ap_st) *p = *ap_st;
            p++;
        }
        ap_st++;
    }
    *p = 0;
}

int main(int argc, char* argv[])
{
    char exp[MAXLEN];
    memset(exp, 0, sizeof(exp));

    if (argc == 1)
    {
        printf("%d",PLUS);
        printf("식을 입력하세요\n");
        printf(">> ");
        scanf("%s", exp);
    }
    else if (argc == 2) strcpy(exp, argv[1]);
    else
    {
        printf("하나의 식만 입력해 주세요\n");
        return -1;
    }

    ESpace(exp);
    printf("Result = %lf\n", calc(exp));
}