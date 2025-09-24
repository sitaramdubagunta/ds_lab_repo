
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node {
    int data;
    char op;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
}

void pushInt(Stack* s, int value) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = value;
    temp->next = s->top;
    s->top = temp;
}

int popInt(Stack* s) {
    if (s->top == NULL) {
        printf("Stack Underflow\n");
        return -1;
    }
    Node* temp = s->top;
    int val = temp->data;
    s->top = temp->next;
    free(temp);
    return val;
}


void pushOp(Stack* s, char op) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->op = op;
    temp->next = s->top;
    s->top = temp;
}

char popOp(Stack* s) {
    if (s->top == NULL) {
        return '\0';
    }
    Node* temp = s->top;
    char op = temp->op;
    s->top = temp->next;
    free(temp);
    return op;
}


char peekOp(Stack* s) {
    if (s->top == NULL)
        return '\0';
    return s->top->op;
}

int isEmpty(Stack* s) {
    return s->top == NULL;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0, k = 0;
    char ch;

    while ((ch = infix[i++]) != '\0') {
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            postfix[k++] = ch;
        }
        else if (ch == '(') {
            pushOp(&s, ch);
        }
        else if (ch == ')') {
            while (!isEmpty(&s) && peekOp(&s) != '(') {
                postfix[k++] = popOp(&s);
            }
            if (!isEmpty(&s) && peekOp(&s) == '(')
                popOp(&s);
            else {
                printf("Invalid expression: Mismatched parentheses\n");
                exit(1);
            }
        }
        else if (isOperator(ch)) {
            while (!isEmpty(&s) && precedence(peekOp(&s)) >= precedence(ch) && peekOp(&s) != '(') {
                postfix[k++] = popOp(&s);
            }
            pushOp(&s, ch);
        }
        else {
            printf("Invalid character in expression: %c\n", ch);
            exit(1);
        }
    }


    while (!isEmpty(&s)) {
        if (peekOp(&s) == '(') {
            printf("Invalid expression: Mismatched parentheses\n");
            exit(1);
        }
        postfix[k++] = popOp(&s);
    }
    postfix[k] = '\0';
}


int evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);
    int i = 0;
    char ch;
    while ((ch = postfix[i++]) != '\0') {
        if (isspace(ch)) continue;

        if (isdigit(ch)) {

            pushInt(&s, ch - '0');
        }
        else if (isOperator(ch)) {
            int val2 = popInt(&s);
            int val1 = popInt(&s);
            int res = 0;

            switch (ch) {
                case '+': res = val1 + val2; break;
                case '-': res = val1 - val2; break;
                case '*': res = val1 * val2; break;
                case '/':
                    if (val2 == 0) {
                        printf("Error: Division by zero\n");
                        exit(1);
                    }
                    res = val1 / val2;
                    break;
                case '^': {
                    res = 1;
                    for (int j=0; j<val2; j++)
                        res *= val1;
                    break;
                }
                default:
                    printf("Unknown operator: %c\n", ch);
                    exit(1);
            }
            pushInt(&s, res);
        }
        else {
            printf("Invalid character in postfix expression: %c\n", ch);
            exit(1);
        }
    }
    return popInt(&s);
}


int main() {
    char infix[100], postfix[100];

    printf("Enter an infix expression (operands as single letters or digits): ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0;

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    int canEvaluate = 1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalpha(postfix[i])) {
            canEvaluate = 0;
            break;
        }
    }

    if (canEvaluate) {
        int result = evaluatePostfix(postfix);
        printf("Evaluated result: %d\n", result);
    } else {
        printf("Postfix expression contains variables; evaluation skipped.\n");
    }

    return 0;
}
