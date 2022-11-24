#include<bits/stdc++.h>
using namespace std;
int dep;
int n,a,b,root_num;
int el[100];
char c,root_val;
template<class T>
struct BinaryTreeNode{
    T element;
    int deep;
    int index;
    BinaryTreeNode<T> *leftson;
    BinaryTreeNode<T> *rightson;
    BinaryTreeNode(){
        deep=0;
        leftson=rightson=NULL;
    }
    BinaryTreeNode(T val){
        this->element=val;deep=0;
        leftson=rightson=NULL;
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
        Tree(){

        }
        Tree(int index,T value){
            Root=new BinaryTreeNode<T>[1000];
            Root->leftson=NULL,Root->rightson=NULL,num=0;
            Root->deep=0;Root->index=index;Root->element=value;
        }
        ~Tree(){

        }
        inline void swap_tree(BinaryTreeNode<T> *now);
        inline void calc(BinaryTreeNode<T> *now);
        inline void dfs(BinaryTreeNode<T> *now,int now_index,int fa_index,T value);
        BinaryTreeNode<T> *Root;
        int num;
};
template<class T>
void Tree<T>::calc(BinaryTreeNode<T> *now){
    cout<<now->deep<<" "<<now->index<<" "<<now->element<<endl;
    dep=max(now->deep,Root->deep);
    if(now->leftson!=NULL) num++,calc(now->leftson);
    else return ;
    if(now->rightson!=NULL) num++,calc(now->rightson);
    else return ;
}
template<class T>
void pre_dfs(BinaryTreeNode<T> *Root){
    if(Root!=NULL){
        visit(Root);
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
template<class T>
inline void visit(BinaryTreeNode<T> *now){
    return ;
}
template<class T>
void give_index(BinaryTreeNode<T> *now){
    el[now->deep]++;
    cout<<"the element is "<<now->element<<" "<<now->index<<" "<<now->deep<<endl;
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
template<class T>
void Tree<T>::swap_tree(BinaryTreeNode<T> *now){
    BinaryTreeNode<T> *temp;
    temp=now->leftson;
    now->leftson=now->rightson;
    now->rightson=temp;
    if(now->leftson) swap_tree(now->leftson);
    if(now->rightson) swap_tree(now->rightson);
}
int main(){  
    cin>>n;
    cin>>root_num>>root_val;
    Tree<char> tree(root_num,root_val);
    for(int i=1;i<=n;i++){
        cin>>a>>b>>c;
        tree.dfs(tree.Root,a,b,c);
    }
    tree.calc(tree.Root);
    cout<<tree.num+1<<endl;   //首节点（根）
    cout<<"The element  The  index  The deep "<<endl;
    bfs(tree.Root);
    int maxn=0;
    for(int i=0;i<=dep;i++){
        maxn=max(maxn,el[i]);
    }
    cout<<"The maximun of element is :"<<maxn<<endl;
    tree.swap_tree(tree.Root);
    bfs(tree.Root);
    system("pause");
    return 0;
}/*
6
1 a
2 1 b
3 1 c
4 2 d
5 2 e
6 3 f
7 3 g
*/
