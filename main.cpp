#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stack>
#include <string.h>

struct node{
    char* data;
    struct node *parent;
    struct node *left;
    struct node *right;
};
struct node* newNode(char* data)
{
    // Allocate memory for new node
    struct node* node = (struct node*)malloc(sizeof(struct node));

    // Assign data to this node
    node->data = data;

    // Initialize left and right children as NULL
    node->left = NULL;
    node->right = NULL;
    return(node);
}

int precedence(char operand){
    switch (operand){
        case '+': case '-':
            return 1;
        case '*': case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

std::string infixToPostfix(std::string expression){
    std::string posfixExp = "";
    std::stack<char> aStack;
    for(unsigned i=0;i<expression.length();i++){
        char ch = expression[i];
        std::string fullnumber = "";
        switch (expression[i]){
            //If Number
            case '0': case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
                //Get full number
                fullnumber = "";
                fullnumber += expression[i++];
                while(expression[i]=='1'||expression[i]=='2'||expression[i]=='3'||expression[i]=='4'||expression[i]=='5'||expression[i]=='6'||expression[i]=='7'||expression[i]=='8'||expression[i]=='9'||expression[i]=='0'||expression[i]=='.'){
                    fullnumber+=expression[i++];
                }
                i--;
                fullnumber+=' ';
                posfixExp.append(fullnumber);
                break;
            //parentheses
            case '(':
                aStack.push(ch);
                break;
            case ')':
                while(aStack.top()!='('){
                    posfixExp += aStack.top();;
                    posfixExp+=' ';
                    aStack.pop();
                }
                aStack.pop();
                break;
            //Operation cases
            case '+': case '-': case '*': case '/': case '^':
                while(!aStack.empty()&&aStack.top()!='('&&precedence(ch)<=precedence(aStack.top())){
                    posfixExp+=aStack.top();
                    posfixExp+=' ';
                    aStack.pop();
                }
                aStack.push(ch);
                break;
            case ' ': default:
                continue;
        }
    }
    while (!aStack.empty()){
        posfixExp+=aStack.top();
        aStack.pop();
    }
    return posfixExp;
}


int main() {
    std::string expression = "555+66*7.2-(3/2^(9/16))";
    std::string posfix = infixToPostfix(expression);

    printf("Infix: %s\nPosfix: %s\n",expression.c_str(),posfix.c_str());

    return 0;
}