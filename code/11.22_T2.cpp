#include<bits/stdc++.h>
#define MAXN 10050
using namespace std;
string a;
bool is_visit[500];
int num[MAXN];
struct huffman_node{
    int num;   //num为element出现的次数
    char element;
    huffman_node *leftson;
    huffman_node *rightson;
    huffman_node(){
        num=0;
    }
    huffman_node(int a,int b){
        this->num=a;
        this->element=(char)b;
    }
    huffman_node(huffman_node *l,huffman_node *r){
        this->leftson=l;
        this->rightson=r;
        this->num=l->num+r->num;
        element='0';
    }
};
int qwq;
class Compare_Node_Pointer
{
public:
    /* Node::priority 大的优先 */
    bool operator () (huffman_node* &a, huffman_node* &b) const
    {
        return a->num>b->num;
    }
};
priority_queue<huffman_node*,std::vector<huffman_node*>,Compare_Node_Pointer> q;
template<class T>
class Huffman{
    public:
        Huffman();
        ~Huffman(){

        }
        inline void build_tree();
        inline void dfs(huffman_node *current);
        
    huffman_node *root;
    int size;
};
template<class T>
Huffman<T>::Huffman(){
    size=0;
    root=NULL;
}
int cnt;
template<class T>
void Huffman<T>::build_tree(){
    for(int i=0;i<a.length();i++) num[(int)a[i]]++;
    for(int i=0;i<=255;i++){
        if(num[i]!=0){ huffman_node *node=new huffman_node(num[i],i);q.push(node);}
    }
    while(q.size()!=1){
        huffman_node *left=q.top();q.pop();
        huffman_node *right=q.top();q.pop();
        huffman_node *fa=new huffman_node(left,right);
        q.push(fa);
        if(q.size()==1) break;
    } 
    this->root=q.top();
}
string ans[50];
string str;
void dfs(huffman_node *now)
{
    if(now->element!='0'){
        ans[now->element-'a']=str;
        return;
    }
    str.push_back('0');
    dfs(now->leftson);
    str[str.size()-1]='1';
    dfs(now->rightson);
    str=str.substr(0,str.size()-1);
}
int main(){
    cin>>a;
    Huffman<char> h;
    h.build_tree();
    dfs(h.root);
    //h.dfs(h.root);
    for(int i=0;i<6;i++) cout<<(char)(i+'a')<<" "<<ans[i]<<endl;

    system("pause");
}
/*

aaaaaabbcccdddeeeefffffffff


expect output:
b 000
c 001
a 01
d 100
e 101
f 11
*/