#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // isdigit(), isalpha() 사용
#include <string.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

// 스택 초기화
void initStack(Stack *s) {
    s->top = -1;
}

// 스택이 비었는지 확인
int isEmpty(Stack *s) {
    return s->top == -1;
}

// 스택에 요소 추가
void push(Stack *s, int value) {
    s->data[++(s->top)] = value;
}

// 스택에서 요소 제거
int pop(Stack *s) {
    if (isEmpty(s)) return '\0';
    return s->data[(s->top)--];
}

// 스택 최상단 요소 반환
int peek(Stack *s) {
    if (isEmpty(s)) return '\0';
    return s->data[s->top];
}

// 연산자 우선순위 설정
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;  // 여는 괄호는 우선순위 비교 대상 아님
}

int evaluatePostfix(char *postfix) {
    Stack s;
    initStack(&s);
    
    for(int i=0; postfix[i]!='\0'; i++) {
        char ch = postfix[i];
        
        if(isdigit(ch)) {
            push(&s, ch-'0');
        }else {
            int b = pop(&s);
            int a = pop(&s);
            int result;
            
            switch (ch){
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                default:
                    printf("error...\n");
                    exit(1);
            }
            push(&s, result);
        }
    }
    return pop(&s);
}

// 중위표기식을 후위표기식으로 변환
int infixToPostfix(char *infix, char *postfix) {
    Stack s;
    initStack(&s);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        // 1. 피연산자 (알파벳 또는 숫자)
        if (isalpha(ch) || isdigit(ch)) {
            postfix[j++] = ch;
        }
        // 2. 여는 괄호 '('
        else if (ch == '(') {
            push(&s, ch);
        }
        // 3. 닫는 괄호 ')'
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);  // 여는 괄호 '(' 전까지 pop
            }
            pop(&s);  // 여는 괄호 '(' 제거
        }
        // 4. 연산자
        else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);  // 우선순위가 높은 연산자들을 pop
            }
            push(&s, ch);  // 현재 연산자 push
        }
    }

    // 스택에 남은 연산자를 후위표기식에 추가
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';

    return evaluatePostfix(postfix);
}

int main() {
    char infix[MAX];
    char postfix[MAX];
    int result;
    printf("중위표기식을 입력하세요: ");
    scanf("%s", infix);
    result = infixToPostfix(infix, postfix);
    printf("후위표기식 : %s\n", postfix);
    printf("후위표기식 계산 결과 : %d\n", result);
    return 0;
}