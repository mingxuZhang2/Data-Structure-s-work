#include<bits/stdc++.h>
using namespace std;
int dep=0;
int n,a,b,root_num;
char c,root_val;
char common[100050];
int cc[220][220];
int reflect[100];
string final_expression;
template<class T>
struct BinaryTreeNode{
    T element;
    int deep;
    int index;
    BinaryTreeNode<T> *leftson;
    BinaryTreeNode<T> *rightson;
    BinaryTreeNode(){
    }
    BinaryTreeNode(T val){
        this->element=val;deep=0;
        leftson=rightson=NULL;
    }
    BinaryTreeNode(BinaryTreeNode<T> *a,BinaryTreeNode<T> *b,T value){
        this->leftson=a;
        this->rightson=b;
        this->element=value;
    }
    BinaryTreeNode(int index,T val,BinaryTreeNode *left,BinaryTreeNode *right,int deep){
        this->element=val;this->index=index;
        leftson=left;rightson=right;
        this->deep=deep;
        //cout<<"now "<<index<<" "<<val<<endl;
    }
};
template<class T>
class Tree{
    public:
        Tree(int x){
            Root=NULL;
        }
        Tree(int index,T value){
            Root=new BinaryTreeNode<T>[1000];
            Root->leftson=NULL,Root->rightson=NULL,num=0;
            Root->deep=0;Root->index=index;Root->element=value;
        }
        inline void build();
        ~Tree(){

        }
        inline void calc(BinaryTreeNode<T> *now);
        inline void dfs(BinaryTreeNode<T> *now,int now_index,int fa_index,T value);
        inline void search_for_deep(BinaryTreeNode<T> *now);
        BinaryTreeNode<T> *Root;
        int num;
};
template<class T>
void Tree<T>::build(){
    stack<BinaryTreeNode<T>*> mystack; 
    for(int i=0;i<final_expression.length();i++){
        if(final_expression[i]!='+'&&final_expression[i]!='*'&&final_expression[i]!='/'&&final_expression[i]!='-'){
            BinaryTreeNode<T> *now=new BinaryTreeNode<T>(final_expression[i]);
            mystack.push(now);
        }
        else{
            BinaryTreeNode<T> *right=mystack.top();mystack.pop();
            BinaryTreeNode<T> *left=mystack.top();mystack.pop();
            BinaryTreeNode<T> *fa=new BinaryTreeNode<T>(left,right,final_expression[i]);
            mystack.push(fa);
        }
    }
    this->Root=mystack.top();
}
struct No{
    int index;
    int deep;
    char value;
}ss[1000];
template<class T>
void give_index(BinaryTreeNode<T> *now){
    dep++;
    now->index=dep;
    cout<<"the element is "<<now->element<<" "<<now->index<<" "<<now->deep<<endl;
    cc[(int)(now->element)][now->index]=now->deep;
}
template<class T>
void Tree<T>::calc(BinaryTreeNode<T> *now){
    cout<<now->deep<<" "<<now->index<<" "<<now->element<<endl;
    dep=max(now->deep,Root->deep);
    if(now->leftson!=NULL) num++,calc(now->leftson);else return ;
    if(now->rightson!=NULL) num++,calc(now->rightson);else return ;
}
int length=0;
template<class T>
inline void visit(BinaryTreeNode<T> *tree){
    cout<<tree->element<<" ";
    common[++length]=tree->element;
    ss[++length].value=tree->element;
    ss[length].deep=tree->deep;
}
template<class T>
void pre_dfs(BinaryTreeNode<T> *Root){
    if(Root!=NULL){
        give_index(Root);
        pre_dfs(Root->leftson);
        pre_dfs(Root->rightson);
    }
}
template<class T>
void Tree<T>::dfs(BinaryTreeNode<T> *now,int now_index,int fa_index,T value){
    if(now->index==fa_index){
        BinaryTreeNode<T> *new_Node=new BinaryTreeNode<T>(now_index,value,NULL,NULL,now->deep+1);
        cout<<"I find my dad "<<fa_index<<" "<<now->element<<endl;
        if(now->leftson==NULL) now->leftson=new_Node;
        else now->rightson=new_Node;
        return ;
    }
    if(now->leftson!=NULL) dfs(now->leftson,now_index,fa_index,value);
    if(now->rightson!=NULL) dfs(now->rightson,now_index,fa_index,value);
}
template<class T>
void mid_dfs(BinaryTreeNode<T> *Root){
    if(Root!=NULL){
        mid_dfs(Root->leftson);
        visit(Root);
        mid_dfs(Root->rightson);
    }
}
template<class T>
void final_dfs(BinaryTreeNode<T> *Root){
    if(Root!=NULL){
        final_dfs(Root->leftson);
        final_dfs(Root->rightson);
        visit(Root);
    }
}
int priority(char a){
    if (a=='(') return 0;
    else if(a =='+'||a =='-') return 1;
    else return 2;
}
bool compare(char a, char b){
    return priority(a)>priority(b);
}
inline void change(string s){
    char now;
    stack<char> op;
    string temp;
    for(int i=0;i<s.length();i++){
        now=(char)s[i];
        if(now>='a'&&now<='z'){
            temp=now;
            final_expression.append(temp);
        }
        else if(now=='(') op.push(now);
        else if(now==')'){
            while(op.top()!='('&&!op.empty()){
                temp=op.top();
                final_expression.append(temp);
                op.pop();
            }
            op.pop();
        }
        else{
            while(!op.empty()&&!compare(now,op.top())){
                temp=now;
                final_expression.append(temp);
                op.pop();
            }
            op.push(now);
        }
        cout<<final_expression<<endl;
    }
    while(!op.empty()){
        temp=op.top();
        cout<<temp<<endl;
        final_expression.append(temp);
        op.pop();
    }
}
template<class T>
void Tree<T>::search_for_deep(BinaryTreeNode<T> *now){
    if(now->leftson==NULL||now->rightson==NULL) return ;
    now->leftson->deep=now->deep+1;
    now->rightson->deep=now->deep+1;
    if(now->leftson!=NULL) search_for_deep(now->leftson);
    if(now->rightson!=NULL) search_for_deep(now->rightson);
}
template<class T>
void bfs(BinaryTreeNode<T> *now){
    queue<BinaryTreeNode<T>*> q;
    q.push(now);
    while(q.size()!=0){
        give_index(now);
        if(now->leftson) q.push(now->leftson);
        if(now->rightson) q.push(now->rightson);
        q.pop();
        now=q.front();
    }
}
string s;
Tree<char> tr(0);
inline void print(){
    for(int i=length;i>=1;i--){ 
        cout<<setw(ss[i].deep*5)<<ss[i].value<<endl;
        }
    cout<<endl;
}
int main(){  
    cin>>s;
    change(s);
    cout<<final_expression<<endl;
    tr.build();
    tr.Root->deep=0;
    tr.search_for_deep(tr.Root);
    mid_dfs(tr.Root);
    //cout<<"the index "<<tr.Root->index<<" "<<tr.Root->leftson->index<<" "<<tr.Root->leftson->leftson->index<<endl;
    cout<<tr.Root->deep<<" "<<tr.Root->leftson->deep<<" "<<tr.Root->leftson->leftson->deep<<endl;
    cout<<"qwqwqwq"<<endl;
    bfs(tr.Root);
    print();
    system("pause");
    return 0;
}/*
a+b+c*(d+e)
*/