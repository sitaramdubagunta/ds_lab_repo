
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char arr[MAX];
    int top;
} Stack;

void init(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int isFull(Stack* s) {
    return s->top == MAX - 1;
}

void push(Stack* s, char c) {
    if (!isFull(s)) {
        s->arr[++s->top] = c;
    }
}

char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->arr[s->top--];
    }
    return '\0';
}

int isPalindrome(char str[]) {
    Stack s;
    init(&s);

    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (isalnum(str[i])) {
            push(&s, tolower(str[i]));
        }
    }

    for (int i = 0; i < len; i++) {
        if (isalnum(str[i])) {
            if (tolower(str[i]) != pop(&s)) {
                return 0;
            }
        }
    }
    return 1; }
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int areParenthesesBalanced(char expr[]) {
    Stack s;
    init(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        if (ch == '(' || ch == '{' || ch == '[') {
            push(&s, ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(&s)) return 0;
            char topChar = pop(&s);
            if (!isMatchingPair(topChar, ch)) return 0;
        }
    }
    return isEmpty(&s);
}


int main() {
    char input[MAX];

    printf("Enter a string to check palindrome: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (isPalindrome(input)) {
        printf("The string is a palindrome.\n");
    } else {
        printf("The string is NOT a palindrome.\n");
    }

    printf("\nEnter an expression to check parentheses matching: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (areParenthesesBalanced(input)) {
        printf("Parentheses are balanced.\n");
    } else {
        printf("Parentheses are NOT balanced.\n");
    }

    return 0;
}
