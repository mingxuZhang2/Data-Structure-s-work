#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
#define MAX 1000
char *change(char data[]);
bool compare(char a, char b);
int priority(char a);
int priority(char a){
    if (a == '(') return 0;
    else if (a == '+' || a == '-') return 1;
    else return 2;
}
bool compare(char a, char b){
    return priority(a)>priority(b);
}
void show(char data[],int length){
    for (int i=0;i<length;i++){
        printf("%c",data[i]);
    }
}
char *change(char data[])
{
    int length=strlen(data);
    char *hou=(char *)malloc(length * sizeof(char));
    stack<char> s;
    int index = 0; 
    for (int i=0;i<length;i++)
    {
        if (data[i] >= 'a' && data[i] <= 'z'){
            hou[index] = data[i];
            index++;
        }
        else if (data[i] == ')')
        {
            // 不断的弹出栈元素并输出直到遇到左括号结束
            while (!s.empty() && s.top() != '(')
            {
                hou[index] = s.top();
                index++;
                s.pop();
            }
            s.pop(); 
        }else if(data[i]=='('){
            s.push(data[i]);
        }
        else{
            while (!s.empty() && !compare(data[i], s.top()))
            {
                hou[index] = s.top();
                index++;
                s.pop();
            }
            s.push(data[i]);
        }
    }
    while (!s.empty())
    {
        hou[index] = s.top();
        index++;
        s.pop();
    }
    show(hou,index);
    return hou;
}
int main(int argc, char const *argv[])
{
    // 样例 2*(9+6/3-5)+4
    // 结果 2963/+5-*4+
    char s[MAX] = "a+b+c*(d+e)";
    char *result;
    result = change(s);
    system("pause");
    return 0;
}
