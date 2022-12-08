#include<bits/stdc++.h>
using namespace std;
template<class T,class K>
struct Node{
    T element,value;
    K index;
    Node<T,K> *leftson;Node<T,K> *rightson;  //左儿子 右儿子
    Node<T,K> *fa;    //指向当前节点的父节点
    bool color;    // 0代表黑色 1代表红色（节点/边）
    bool leftedge_color;//左孩子的颜色
    bool rightedge_color;//右孩子的颜色
    Node(T val,K index,Node *l,Node *r){
        this->element=val;this->index=index;
        leftson=l;rightson=r;
        color=0;
        leftedge_color=rightedge_color=0;
    }   
    Node(T val,K index){
        this->value=val;this->index=index;color=1;
        this->leftson=NULL;this->rightson=NULL;this->fa=NULL;
    }
    Node(){
        element=0,index=0,leftson=rightson=NULL;color=0;
    }
};
template<class T,class K>
class Binary_search_tree{
    public:
    Binary_search_tree(T val,K index,Node<T,K> *l,Node<T,K> *r);
    Binary_search_tree(int l);
    ~Binary_search_tree(){

    }
    inline void insert(T val,K index);
    //inline void insert(K index,T element);
    inline void erase(K index);
    inline T find(K index);
    inline void output(Node<T,K> *now);
    inline void splay_LL(Node<T,K> *now);//LL是指插入到了某节点左儿子的左节点
    inline void splay_LR(Node<T,K> *now);//RL是指插入到了某节点左儿子的右节点
    inline void splay_RL(Node<T,K> *now);//RL是指插入到了某节点右儿子的左节点
    inline void splay_RR(Node<T,K> *now);//RL是指插入到了某节点右儿子的右节点
    inline void check(Node<T,K> *now);
    inline void dyeing_LL(Node<T,K> *now);
    inline void dyeing_LR(Node<T,K> *now);
    inline void dyeing_RR(Node<T,K> *now);
    inline void dyeing_RL(Node<T,K> *now);
    inline void bfs(Node<T,K> *now); //层次遍历输出每一个节点的<T,K>值
    inline void ascend(Node <T,K> *now); //按照升序输出所有的数对<T,K>，要求时间复杂度为线性级别
    Node<T,K> *root;
    int size;
};
template<class T,class K>
void Binary_search_tree<T,K>::bfs(Node<T,K> *now){
    queue<Node<T,K>*> q;
    q.push(now);
    int dep=5000;
    while(q.size()!=0){
        cout<<now->index<<" "<<now->color<<endl;
        if(now->leftson) q.push(now->leftson);
        if(now->rightson) q.push(now->rightson);
        q.pop();
        now=q.front();
    }
}
template<class T,class K>
void Binary_search_tree<T,K>::output(Node<T,K> *now){
    cout<<now->index<<" ";
    return ;
}
template<class T,class K>
void Binary_search_tree<T,K>::ascend(Node<T,K> *now){
    if(now->leftson!=NULL) ascend(now->leftson);
    output(now);
    if(now->rightson!=NULL) ascend(now->rightson);
}
template<class T,class K>
void Binary_search_tree<T,K>::erase(K index){
    int son=0;
    Node<T,K> *current=root; //current是被删节点
    while(1){  //找到索引为index的节点
        if(current->index==index) break;
        if(current->leftson==NULL&&current->rightson==NULL) break;
        if(current->index<index) current=current->rightson;
        if(current->index>index) current=current->leftson;
    }
    Node<T,K> *fa=current->fa;//待删除节点的父节点
    if(current->rightson!=NULL) son++;if(current->leftson!=NULL) son++;//计算节点的孩子数目便于后续判断
    if(current==root){cout<<"The index is illeagl!"<<endl;return ;}
    if(son==0&&current->color==1){  //情况一 被删节点无子节点 且被删节点为红色
        if(fa->leftson==current) fa->leftson=NULL,fa->leftedge_color=0;
        else fa->rightson=NULL,fa->rightedge_color=0;
    }
    if(son==0&&current->color==0){//情况二 被删节点无子节点 且颜色为黑色
        Node<T,K> *brother=NULL;
        if(fa->leftson==current) brother=fa->rightson;if(fa->rightson==current) brother=fa->leftson;
        Node<T,K> *brother_son=NULL;
        if(brother->leftson->color==1) brother_son=brother->leftson;
        if(brother->rightson->color==1) brother_son=brother->rightson;
        if(brother->color==0&&fa->leftson==brother&&brother->leftson==brother_son&&brother_son->color==1){
            //brother为黑色节点 brother有一个与其方向相同的红色节点 此处是LL形
            Node<T,K> *gu=fa->fa;
            if(gu->leftson==fa){
                Node<T,K> *temp1=brother->rightson;
                gu->leftson=brother;brother->rightson=fa;
                fa->rightson=NULL;fa->leftson=temp1;
                brother_son->color=0;brother->leftedge_color=0;
            }
            if(gu->rightson==fa){
                Node<T,K> *temp1=brother->rightson;
                gu->rightson=brother;brother->rightson=fa;
                fa->rightson=NULL;fa->leftson=temp1;
                brother_son->color=0;brother->leftedge_color=0;                    
            }
        }
        if(brother->color==0&&fa->rightson==brother&&brother->rightson==brother_son&&brother_son->color==1){
            //brother为黑色节点 brother有一个与其方向相同的红色节点 此处为RR形
            Node<T,K> *gu=fa->fa;
            Node<T,K> *temp1=brother->leftson;
            if(gu->leftson==fa){
                gu->leftson=brother;brother->leftson=fa;
                fa->leftson=NULL;fa->rightson=temp1;
                brother_son->color=0;brother->rightedge_color=0;
            }
            if(gu->rightson==fa){
                gu->rightson=brother;brother->leftson=fa;
                fa->leftson=NULL;fa->rightson=temp1;
                brother_son->color=0;brother->rightedge_color=0;                
            }
        }
        if(brother->color==0&&(fa->rightson==brother&&brother->leftson==brother_son)&&brother_son->color==1){
            //brother为黑色 且brother有一个与其方向不一致的红色子结点brother_son 此时对应为RL形
            
        }
        if(brother->color==0&&(fa->leftson==brother&&brother->rightson==brother_son)&&brother_son->color==1){
            //brother为黑色 且brother有一个与其方向不一致的红色子结点brother_son 此时对应为LR形
        }
        if(brother->color==0&&brother->leftson->color==0&&brother->rightson->color==0){
            //brother为黑色 且brother无红色子结点
        }
        if(brother->color==1){
            //此时brother为红色 则father必为黑色。
        }
    }
    if(son==1&&current->color==1){//情况三 有一个子节点且颜色为红色
        return ; //这种情况不存在 不符合红黑树性质
    }
    if(son==1&&current->color==0){//情况四 有一个子节点且颜色为黑色
        Node<T,K> *son;
        son=(current->leftson==NULL)?(current->rightson):current->leftson;
        if(fa->leftson==current){
            fa->leftson=son;son->color=0;fa->leftedge_color=0;
        }
        if(fa->rightson==current){
            fa->rightson=son;son->color=0;fa->rightedge_color=0;
        }
    }
    if(son==2&&current->color==1){//情况五&六 有两个子节点且颜色为红色或黑色
        Node<T,K> *successor=current->rightson; //先寻找到待删除节点的前驱/后继节点（在这里寻找后继节点）
        while(successor!=NULL) successor=successor->leftson;
        erase(successor->index);
        if(fa->leftson==current) fa->leftson=successor;
        else fa->rightson=successor;
        
    }
}
template<class T,class K>
void Binary_search_tree<T,K>::dyeing_LL(Node<T,K> *now){
    Node<T,K> *pu=now->fa;Node<T,K> *gu=pu->fa;
    Node<T,K> *fa=gu->fa; 
    if(fa==NULL){
        gu->color=1;
        gu->rightson->color=0;pu->color=0;
        gu->rightedge_color=0;gu->leftedge_color=0;
    } 
    else if(fa->rightson==gu){
        fa->rightedge_color=1;gu->color=1;
        gu->rightson->color=0;pu->color=0;
        gu->rightedge_color=0;gu->leftedge_color=0;
    }
    else if(fa->leftson==gu){
        fa->leftedge_color=1;gu->color=1;
        gu->rightson->color=0;pu->color=0;
        gu->rightedge_color=0;gu->leftedge_color=0;
    }
}
template<class T,class K>
void Binary_search_tree<T,K>::dyeing_LR(Node<T,K> *now){
    Node<T,K> *pu=now->fa;Node<T,K> *gu=pu->fa;
    Node<T,K> *fa=gu->fa;
    if(gu==root){

    }
    if(fa->rightson==gu){
        fa->rightedge_color=1;gu->color=1;
        gu->rightson->color=0;pu->color=0;
        gu->rightedge_color=0;gu->leftedge_color=0;
    }   
    if(fa->leftson==gu){
        fa->leftedge_color=1;gu->color=1;
        gu->rightson->color=0;pu->color=0;
        gu->rightedge_color=0;gu->leftedge_color=0;
    }
}
template<class T,class K>
void Binary_search_tree<T,K>::dyeing_RR(Node<T,K> *now){
    Node<T,K> *pu=now->fa;Node<T,K> *gu=pu->fa;
    Node<T,K> *fa=gu->fa;
    if(fa->rightson==gu){
        fa->rightedge_color=1;gu->color=1;
        gu->leftedge_color=0;gu->rightedge_color=0;
        gu->leftson->color=0;pu->nodecolor=0;
    }
    if(fa->leftson==gu){
        fa->leftedge_color=1;gu->nodecolor=1;
        gu->leftedge_color=0;gu->rightedge_color=0;
        gu->leftson->nodecolor=0;pu->nodecolor=0;
    }
}
template<class T,class K>
void Binary_search_tree<T,K>::dyeing_RL(Node<T,K> *now){
    Node<T,K> *pu=now->fa;Node<T,K> *gu=pu->fa;
    Node<T,K> *fa=gu->fa;
    if(fa->rightson==gu){
        fa->rightedge_color=1;gu->nodecolor=1;
        gu->leftedge_color=0;gu->rightedge_color=0;
        gu->leftson->nodecolor=0;pu->nodecolor=0;
    }
    if(fa->leftson==gu){
        fa->leftedge_color=1;gu->nodecolor=1;
        gu->leftedge_color=0;gu->rightedge_color=0;
        gu->leftson->nodecolor=0;pu->nodecolor=0;
    }
}
template<class T,class K>
Binary_search_tree<T,K>::Binary_search_tree(T val,K index,Node<T,K> *l,Node<T,K> *r){
    root=new Node<T,K>(val,index,l,r);
    size=0;
}
/*template<class T,class K>
void Binary_search_tree<T,K>::splay_LL(Node<T,K> *now){
    Node<T,K> *pu=now->fa;Node<T,K> *gu=pu->fa;
    Node<T,K> *fa=gu->fa;
    Node<T,K> *temp1=pu->rightson;Node<T,K> *temp2=gu->rightson;
    if(fa==NULL){
        pu->leftson=now;pu->rightson=gu;
        gu->leftson=temp1;gu->rightson=temp2;
    }
    else if(fa->leftson==gu){
        fa->leftson=pu;
        pu->leftson=now;pu->rightson=gu;
        gu->leftson=temp1;gu->rightson=temp2;
    }
    else if(fa->rightson==gu){
        fa->rightson=pu;
        pu->leftson=now;pu->rightson=gu;
        gu->leftson=temp1;gu->rightson=temp2;        
    }
    pu->nodecolor=0;now->nodecolor=1;gu->nodecolor=1;
    pu->leftedge_color=1;pu->rightedge_color=1;
    gu->rightedge_color=1;gu->leftedge_color=0;
}
template<class T,class K>
void Binary_search_tree<T,K>::splay_LR(Node<T,K> *now){
    Node<T,K> *pu=now->fa;Node<T,K> *gu=pu->fa;
    Node<T,K> *fa=gu->fa;
    Node<T,K> *temp1=pu->leftson;Node<T,K> *temp2=gu->rightson;
    Node<T,K> *temp3=now->leftson;Node<T,K> *temp4=now->rightson;
    if(fa==NULL){
        if(gu==root) root=now;
        now->leftson=pu;now->rightson=gu;
        pu->leftson=temp1;pu->rightson=temp3;
        gu->leftson=temp4;gu->rightson=temp2;   
        pu->fa=now;gu->fa=now;
        if(temp4!=NULL) temp4->fa=gu;if(temp2!=NULL) temp2->fa=gu;
        if(temp1!=NULL) temp1->fa=pu;if(temp1!=NULL) temp1->fa=pu;  
    }
    else if(fa->leftson==gu){
        fa->leftson=now;
        now->leftson=pu;now->rightson=gu;
        pu->leftson=temp1;pu->rightson=temp3;
        gu->leftson=temp4;gu->rightson=temp2;
        pu->fa=now;gu->fa=now;
        temp4->fa=gu;temp2->fa=gu;
        temp1->fa=pu;temp1->fa=pu;  
    }
    else if(fa->rightson==gu){
        fa->rightson=now;
        now->leftson=pu;now->rightson=gu;
        pu->leftson=temp1;pu->rightson=temp3;
        gu->leftson=temp4;gu->rightson=temp2;
        pu->fa=now;gu->fa=now;
        temp4->fa=gu;temp2->fa=gu;
        temp1->fa=pu;temp1->fa=pu;  
    }
    now->nodecolor=0;pu->nodecolor=1;gu->nodecolor=1;
    now->leftedge_color=1,now->rightedge_color=1;
    gu->leftedge_color=1,gu->rightedge_color=0;
    pu->leftedge_color=0;pu->rightedge_color=0;
}
template<class T,class K>
void Binary_search_tree<T,K>::splay_RR(Node<T,K> *now){
    Node<T,K> *pu=now->fa;Node<T,K> *gu=pu->fa;
    Node<T,K> *fa=gu->fa;
    Node<T,K> *temp1=gu->leftson;Node<T,K> *temp2=pu->leftson;
    if(fa->leftson==gu){
        fa->leftson=pu;
        pu->leftson=gu;pu->rightson=now;
        gu->leftson=temp1;gu->rightson=temp2;
        pu->fa=fa;
        gu->fa=pu;now->fa=pu;
        temp1->fa=gu;temp2->fa=gu;
    }
    if(fa->rightson==gu){
        fa->rightson=pu;
        pu->leftson=gu;pu->rightson=now;
        gu->leftson=temp1;gu->rightson=temp2;
        pu->fa=fa;
        gu->fa=pu;now->fa=pu;
        temp1->fa=gu;temp2->fa=gu;
    }
    pu->nodecolor=0;gu->nodecolor=1;now->nodecolor=1;
    pu->leftedge_color=1,pu->rightedge_color=1;
    gu->leftedge_color=0,gu->rightedge_color=0;
}
template<class T,class K>
void Binary_search_tree<T,K>::splay_RL(Node<T,K> *now){
    Node<T,K> *pu=now->fa;Node<T,K> *gu=pu->fa;
    Node<T,K> *fa=gu->fa;
    Node<T,K> *temp1=gu->leftson;Node<T,K> *temp2=pu->rightson;
    Node<T,K> *temp3=now->leftson;Node<T,K> *temp4=now->rightson;
    if(fa->leftson==gu){
        fa->leftson=now;
        now->leftson=gu;now->rightson=pu;
        gu->leftson=temp1;gu->rightson=temp3;
        pu->leftson=temp4;pu->rightson=temp2;
        now->fa=fa;
        gu->fa=now;pu->fa=now;
        temp1->fa=gu;temp3->fa=gu;
        temp4->fa=pu;temp2->fa=pu;
    } 
    if(fa->rightson==gu){
        fa->rightson=now;
        now->leftson=gu;now->rightson=pu;
        gu->leftson=temp1;gu->rightson=temp3;
        pu->leftson=temp4;pu->rightson=temp2;
        now->fa=fa;
        gu->fa=now;pu->fa=now;
        temp1->fa=gu;temp3->fa=gu;
        temp4->fa=pu;temp2->fa=pu;
    }
    now->nodecolor=0;pu->nodecolor=1;gu->nodecolor=1;
    now->leftedge_color=1,now->rightedge_color=1;
    gu->leftedge_color=0,gu->rightedge_color=0;    
    pu->leftedge_color=0;pu->rightedge_color=0;
}
/*template<class T,class K>
void Binary_search_tree<T,K>::check(Node<T,K> *now){
    Node<T,K> *fa=now->fa;
    Node<T,K> *grand_fa=fa->fa;
    if(grand_fa==NULL) return ;
    if(now==fa->leftson) Node<T,K> *temp_one=fa->rightson;
    if(now==fa->rightson) Node<T,K> *temp_one=fa->leftson;
    cout<<"test "<<now->index<<" "<<grand_fa->index<<" "<<fa->index<<endl;
    if(grand_fa->rightson==fa){   //当前pu是gu的右儿子 pu,gu的定义看PPT now等价于PPT中的节点u
        Node<T,K> *temp_two=grand_fa->leftson;
        if(grand_fa->rightedge_color==0) return ;
        if(grand_fa->leftedge_color==0){ //此时2-3-4树还没有满 另一边是黑色的
            if(now==fa->leftson) splay_RL(now);  //RL是指插入到了某节点右儿子的左节点 
            if(now==fa->rightson) splay_RR(now); 
        }
        else{                               //现在是右节点
            if(now==fa->leftson) dyeing_RL(now);
            if(now==fa->rightson) dyeing_RR(now);
        }
    }
    else if(grand_fa->leftson==fa){
        Node<T,K> *temp_two=grand_fa->rightson;
        if(grand_fa->leftedge_color==0) return ;
        if(grand_fa->rightedge_color==0){
            if(now==fa->leftson) splay_LL(now);
            if(now==fa->rightson) splay_LR(now);
        }
        else{
            if(now==fa->leftson) dyeing_LL(now);
            if(now==fa->rightson) dyeing_LR(now);
        }
    }
}*/
template<class T,class K>
void Binary_search_tree<T,K>::splay_LL(Node<T,K> *now){
    Node<T,K> *temp1=now->rightson;
    Node<T,K> *temp2=NULL;
    if(temp1!=NULL) temp2=temp1->leftson;
    now->rightson=temp2;
    if(temp2!=NULL) temp2->fa=now;
    Node<T,K> *fa=now->fa;
    temp1->leftson=now;now->fa=temp1;
    if(fa==NULL){
        root=temp1;root->fa=NULL;
        return ;
    }
    if(fa->leftson==now) fa->leftson=temp1;
    else fa->rightson=temp1;
    temp1->fa=fa;
}
template<class T,class K>
void Binary_search_tree<T,K>::splay_RR(Node<T,K> *now){
    Node<T,K> *temp1=now->leftson;
    Node<T,K> *temp2=NULL;
    if(temp1!=NULL) temp2=temp1->rightson;
    now->leftson=temp2;
    if(temp2!=NULL) temp2->fa=now;
    Node<T,K> *fa=now->fa;
    temp1->rightson=now;now->fa=temp1;
    if(fa==NULL){
        root=temp1;root->fa=NULL;
        return ;
    }
    if(fa->leftson==now) fa->leftson=temp1;
    else fa->rightson=temp1;
    temp1->fa=fa;
}
template<class T,class K>
void Binary_search_tree<T,K>::splay_LR(Node<T,K> *now){
    splay_LL(now->leftson);
    splay_RR(now);
}
template<class T,class K>
void Binary_search_tree<T,K>::splay_RL(Node<T,K> *now){
    splay_RR(now->rightson);
    splay_LL(now);
}
template<class T,class K>
void Binary_search_tree<T,K>::insert(T val,K index){
    Node<T,K> *newnode=new Node<T,K>(val,index);
    if(root==NULL){
        root=newnode;
        root->color=0;//红黑树根节点颜色必为黑色
        return ;
    }
    Node<T,K> *current=root;
    Node<T,K> *fa=current;
    while(current!=NULL){  //第一个循环找插入节点的前驱，即找到新建节点的父亲
        fa=current;
        if(current->index>index) current=current->leftson;
        else if(current->index<index) current=current->rightson;   
    }
    if(fa->index<newnode->index){
        fa->rightson=newnode;newnode->fa=fa;
        current=newnode;
    }
    if(fa->index>newnode->index){
        fa->leftson=newnode;newnode->fa=fa;
        current=newnode;
    }
    int ans=1;
    while(fa!=NULL&&fa->color==1&&ans<=3){
        ans++;
        Node<T,K> *gu=fa->fa;Node<T,K> *brother=NULL;
        if(gu->leftson==fa) brother=gu->rightson;
        else brother=gu->leftson;
        if(brother!=NULL&&brother->color==1){ //只需要染色 不需要旋转的情况
            gu->color=1;fa->color=0;brother->color=0;
            current=gu;fa=current->fa;
        } //current是待插入节点 fa是其父亲 gu是其爷爷
        else if(brother==NULL||brother->color==0){//需要旋转的情况
            if(gu->leftson==fa){
                if(fa->leftson==current){   
                    splay_RR(gu);
                    fa->color=0;
                }
                
                else if(fa->rightson==current){
                    splay_LR(gu);
                    current->color=0;
                }
            }
            else{
                if(fa->rightson==current){
                    splay_LL(gu);
                    fa->color=0;
                }
                else if(fa->leftson==current){
                    splay_RL(gu);
                    current->color=0;
                }
            }
            gu->color=1;if(gu==root) root=fa;
        }
        if(root->color==1) root->color=0;
    }
}
template<class T,class K>
Binary_search_tree<T,K>::Binary_search_tree(int l){
    root=NULL;size=0;
}
/*template<class T,class K>
void Binary_search_tree<T,K>::insert(K index,T element){
    Node<T,K> *current=root;
    Node<T,K> *fa=NULL;
    while(current!=NULL){  //第一个循环找插入节点的前驱，即找到新建节点的父亲
        fa=current;
        if(current->index>index) current=current->leftson;
        else if(current->index<index) current=current->rightson;   
    }
    Node<T,K> *newnode=new Node<T,K>(element,index,NULL,NULL);
    if(root==NULL) {root=newnode;size++;root->nodecolor=0;root->fa=NULL;return ;}
    cout<<"root "<<root->index<<" "<<fa->index<<endl;
    if(fa->index<newnode->index){
        fa->rightson=newnode;newnode->fa=fa;
        newnode->nodecolor=1;fa->rightedge_color=1;
        check(newnode);
    }
    if(fa->index>newnode->index){
        fa->leftson=newnode;newnode->fa=fa;
        newnode->nodecolor=1;fa->leftedge_color=1;
        check(newnode);
    }
    size++;
}*/
template<class T,class K>
T Binary_search_tree<T,K>::find(K index){
    Node<T,K> *current=root;
    while(current!=NULL){
        if(current->index==index) return current->element;
        else if(index<current->index) current=current->leftson;
        else current=current->rightson;
    }
    return '0';
}
int main(){
    int n,index;
    int m,op;
    char ch;
    Binary_search_tree<char,int> tree(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>index>>ch;
        tree.insert(ch,index);        
        //tree.insert(index,ch);
        tree.bfs(tree.root);
        cout<<endl;
    }
    cout<<tree.root->index<<endl;
    cout<<"Now there is the Node's index and there's color"<<endl;
    tree.bfs(tree.root);
    cout<<"Now we are going to erase some nodes in BST."<<endl;
    cin>>m;
    for(int i=1;i<=m;i++){
        cin>>op;
        tree.erase(op);
    }
    cout<<"After deleting some nodes,the rest of nodes are below:"<<endl;
    tree.ascend(tree.root);
    system("pause");
    return 0;
}
/*
输入格式 
第一行为一个整数n 代表红黑树有n个节点
接下来n行每行一个整数a和一个字符b 其中a为在BST的索引 b为其存储的value
输出格式
层次遍历，输出每一行的节点（只输出索引值）以及对应的颜色
11
50 a
10 b
80 c
90 d
70 e
60 f
65 g
62 h
71 i
99 j
1 k


接下来进行删除操作 输入一个整数m 代表删除m个节点
接下来m行 每行一个整数代表待删除节点的索引值
输出格式同上
4
62
71
99
1
最后调用函数ascend 将其中的索引值从小到大的顺序输出 时间复杂度为线性级别

*/