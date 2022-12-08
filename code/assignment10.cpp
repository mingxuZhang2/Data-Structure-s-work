#include<bits/stdc++.h>
using namespace std;
struct Node{
    int to,nxt,dis;
    friend inline bool operator<(Node a,Node b){
        return a.dis<b.dis;
    }
};
struct Edge{
    int start;int end;int dis;
    friend inline bool operator<(Edge a,Edge b){
        return a.dis<b.dis;
    }
};
struct graphNode{
    int vertex;int dis;
    graphNode *nxt;
    graphNode(int u,int dis){
        this->vertex=u;this->dis=dis;this->nxt=NULL;
    }
    bool lessthan(const graphNode *pp) const{
        return dis>pp->dis;
    }
};
class Compare_Node_Pointer{
    public:
        bool operator () (graphNode* a, graphNode* b) const{/* Node::priority 小的优先 */
            return a->lessthan(b);
        }
};
class graph{
    public:
        graph(){
            memset(gra,0,sizeof(gra));top=0;memset(viss,0,sizeof(viss));
            for(int i=0;i<500;i++) g[i]=new graphNode(i,0);
            for(int i=1;i<=500;i++) fa[i]=i;
        }
        ~graph(){

        }
        inline void add(int i,int j,int dis); //建图 用邻接链表的方法
        inline void add_martix(int i,int j,int dis);//用邻接矩阵建图
        inline void add_LinearList(int i,int j,int dis);//建图 应用线性表 也叫链式前向星
        inline bool judge();//判断图是否连通
        inline void Kruskal(); //最小生成树
        inline void prim(); //最小生成树
        inline void Dijkstra(int now,int target);//单源最短路 无法判断负边权
        inline void Floyd(); //任意两点最短路 时间复杂度为n的立方
        inline void SPFA(int now,int target); //spfa 同样求单源最短路
        inline void undirectedTC();//计算传递闭包 时间复杂度为n的平方
        inline void dfs(graphNode *start);//深度优先搜索
        inline int find(int x); //并查集
        inline void bfs(graphNode *start);//宽度优先搜索
        inline void find_path(int start,int end); //用bfs方法实现寻求一条从start-end的路径 并且此路径是最短路径
        inline void output(); //输出图的邻接链表实例
        graphNode* g[500];//邻接链表
        bool viss[5000];
        Node grap[5000];int head[20050];int top;//链式前向星
        Edge e[5000]; //Kruskal存储边
        int gra[500][500];//邻接矩阵
        bool tc[500][500];//传递闭包
        int fa[5000]; //并查集检验是否在同一个集合中
        int n,m;//图中有n个节点 m条边
        int ans; //最小生成树
};
void graph::SPFA(int now,int target){ //另外一种计算最短路的方法 可用于判定负边权or环
    deque<graphNode*> q;
    int dis[5000];memset(dis,0x3f3f3f,sizeof(dis));dis[now]=0;
    bool vis[5000]={0};
    q.push_front(g[now]);
    while(q.size()!=0){
        graphNode *current=q.front();int now=current->vertex;
        q.pop_front();
        current=g[now];
        while(current->nxt!=NULL){
            current=current->nxt;int vertax=current->vertex;
            if(dis[vertax]>dis[now]+current->dis){
                dis[vertax]=dis[now]+current->dis;
                if(!vis[vertax]){
                    vis[vertax]=1;if(!q.empty()){
                        if(dis[q.front()->vertex]>dis[vertax]) q.push_front(current);
                        else q.push_back(current);
                    }
                    else q.push_back(current);
                }
            }
        }
        vis[now]=0;
    }
    cout<<"This is SPFA: ";
    cout<<"Now the start Node is "<<now<<" "<<"the nearest distance between the node and the other is: ";
    for(int i=1;i<=n;i++) cout<<dis[i]<<" ";
    cout<<endl;
}
void graph::Dijkstra(int now,int target){ //now是起点 最后的答案存储在diss数组中 diss[i]代表从now到i的最短路
    bool vis[500]={0};
    int diss[5000];
    memset(diss,0x3f3f3f,sizeof(diss));diss[now]=0;
    priority_queue<graphNode*,std::vector<graphNode*>,Compare_Node_Pointer> q;
    graphNode *emp=g[now];
    q.push(emp);
    while(q.size()!=0){
        graphNode *current=q.top();q.pop();
        int now=current->vertex;
        if(vis[current->vertex]==1) continue;
        vis[current->vertex]=1;
        current=g[current->vertex];
        while(current->nxt!=NULL){
            current=current->nxt;
            int the_next_node=current->vertex;
            if(diss[the_next_node]>diss[now]+current->dis){
                diss[the_next_node]=diss[now]+current->dis;
                q.push(current);
            }
        }
    }
    cout<<"This is Dijkstra: ";
    cout<<"Now the start Node is "<<now<<" "<<"the nearest distance between the node and the other is: ";
    for(int i=1;i<=n;i++) cout<<diss[i]<<" ";
    cout<<endl;
}
int graph::find(int x){
    while(x!=fa[x]) x=fa[x]=fa[fa[x]];
    return x;
}   
void graph::Kruskal(){ //Kruskal用临接链表不是很舒服 用临界线性表比较好
    int answer=0;int cnt=0;
    sort(e+1,e+1+m);
    for(int i=1;i<=m;i++){
        int u=find(e[i].start);int v=find(e[i].end);
        if(u==v) continue; //遇到重复边情况
        answer+=e[i].dis;
        fa[v]=u;cnt++;
        if(cnt==n-1) break;
    }
    cout<<"the minimum of the cost is "<<answer<<endl;
}
void graph::prim(){
    bool vis[500]={0};
    int dis[5000];
    memset(dis,0x3f3f3f,sizeof(dis));dis[1]=0;
    if(judge()==0) {cout<<"The graph is not fully connected!"<<endl;return ;}
    priority_queue<graphNode*,vector<graphNode*>,Compare_Node_Pointer> q;
    graphNode *emp=g[1];
    q.push(emp);int cnt=0;
    while(q.size()!=0&&cnt<n){
        graphNode *current=q.top();q.pop();int now=current->vertex;
        if(vis[now]==1) continue;
        ans+=current->dis;cnt++;vis[now]=1;  
        current=g[current->vertex];
        while(current->nxt!=NULL){
            current=current->nxt;
            int the_next_node=current->vertex;
            if(current->dis<dis[the_next_node]){dis[the_next_node]=current->dis;q.push(current);}
        }
    }   
    cout<<"the minimum of the cost is "<<ans<<endl;
}
void graph::output(){
    for(int i=1;i<=n;i++){
        graphNode *current=g[i];
        cout<<"The node is "<<i<<" and the other nodes and the distance is: ";
        while(current->nxt!=NULL){
            current=current->nxt;
            cout<<current->vertex<<" "<<current->dis<<" ";
        }
        cout<<endl;
    }
}
bool graph::judge(){
    dfs(g[1]);
    for(int i=1;i<=n;i++) if(viss[i]==0){cout<<"The graph is not fully connected!"<<endl;return 0;}
    cout<<"the graph is connected!"<<endl;
    return 1;
}
void graph::bfs(graphNode *current){
    bool vis[500]={0}; //1代表该节点已被遍历 0代表未被遍历
    queue<graphNode*> q;
    cout<<"now the source is: "<<current->vertex<<endl; //无论是dfs还是bfs都需要搜索源点 这里current就是搜索源点
    q.push(current);
    vis[current->vertex]=1;
    cout<<"The bfs's result is :";
    while(q.size()!=0){
        cout<<current->vertex<<" ";
        while(current!=NULL){
            if(vis[current->vertex]==0){q.push(g[current->vertex]),vis[current->vertex]=1;}
            current=current->nxt;
        }
        q.pop();
        current=q.front();
    }
    cout<<endl;
}
void graph::undirectedTC(){
    bool viz[500]={0};
    int vis[50][50];
    memset(vis,0,sizeof(vis));
    queue<graphNode*> q;
    graphNode *current=g[1];
    q.push(current);
    viz[1]=1;
    while(q.size()!=0){
        current=q.front();q.pop();
        int now=current->vertex;
        current=g[now];
        while(current->nxt!=NULL){
            current=current->nxt;
            if(viz[current->vertex]==0){q.push(g[current->vertex]),viz[current->vertex]=1;}
            vis[now][current->vertex]++;
        }
    }
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        if(vis[i][j]>=1&&vis[j][i]>=1) tc[i][j]=1;
    }
    cout<<"Now for the graph,the tansitive closure is :"<<endl;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout<<tc[i][j]<<" ";
        cout<<endl;
    }
    
}
void graph::find_path(int start,int end){
    bool vis[500]={0}; //1代表该节点已被遍历 0代表未被遍历
    int path[500]={0};int cnt=0;int num=0;
    queue<graphNode*> q;
    cout<<"now the source is: "<<start<<endl; //无论是dfs还是bfs都需要搜索源点 这里current就是搜索源点
    graphNode* current=g[start];q.push(current);
    vis[current->vertex]=1;
    cout<<"The bfs's result is :";
    while(q.size()!=0){
        path[++cnt]=current->vertex;
        if(current->vertex==end) break;
        if(current->nxt==NULL){  //有一个地方找到头还没有找到路径 那需要将其删掉
            int order=cnt-1%(num+1);//这是第几个通道
            for(int i=order;i<=cnt;i+=num) path[i]=0;
            int neww=0;int new_path[5000];
            for(int i=1;i<=cnt;i++) if(path[i]!=0) new_path[++neww]=path[i];
            memset(path,0,sizeof(path));
            for(int i=1;i<=neww;i++) path[i]=new_path[i];
            num--;cnt=neww;
        }        
        while(current!=NULL){
            if(vis[current->vertex]==0){q.push(g[current->vertex]),vis[current->vertex]=1;}
            current=current->nxt;
            if(cnt==1) num++;//通道数 即起点的出度
        }

        q.pop();
        current=q.front();
    }
    int i;
    int order=cnt-1%(num+1);
    cout<<path[1]<<" ";
    for(i=order;i<=cnt;i+=num) cout<<path[i]<<" ";
    if(i<cnt) cout<<path[cnt]<<endl;
}
void graph::dfs(graphNode *current){
    if(viss[current->vertex]==0) {cout<<current->vertex<<" ";viss[current->vertex]=1;}
    while(current->nxt!=NULL){
        current=current->nxt;
        if(viss[current->vertex]==0) dfs(g[current->vertex]);
    }
}
void graph::add_martix(int i,int j,int dis){
    gra[i][j]=dis;
}
void graph::add_LinearList(int i,int j,int dis){
    grap[++top].to=j;grap[top].nxt=head[i];grap[top].dis=dis;head[i]=top;
}
void graph::add(int i,int j,int dis){  //从i到j有一条边权为dis的边
    graphNode *current=g[i];
    while(current->nxt!=NULL) current=current->nxt;
    graphNode *newnode=new graphNode(j,dis);
    current->nxt=newnode;
}
int main(){
    int n,m,p,q,diss,s;
    cin>>n>>m;
    graph thegraph;
    thegraph.n=n;thegraph.m=m;
    for(int i=1;i<=m;i++){
        cin>>p>>q>>diss;
        thegraph.add(p,q,diss);
        thegraph.e[i].start=p;thegraph.e[i].end=q;thegraph.e[i].dis=diss;
    }
    thegraph.output();
    thegraph.bfs(thegraph.g[1]);
    cout<<"the dfs's result is: ";
    thegraph.dfs(thegraph.g[1]);
    cout<<endl;
    thegraph.judge();
    thegraph.prim();
    thegraph.Kruskal();
    thegraph.Dijkstra(1,1);
    thegraph.SPFA(1,1);
 //   thegraph.find_path(4,8);
    thegraph.undirectedTC();
    system("pause");
    return 0;
}
/*
10 15 
1 2 5
1 3 4
1 4 5
4 6 2
4 7 6
2 5 6
5 8 9
10 8 10
4 3 5
6 3 1
7 8 1
7 9 2
10 9 2
6 8 2
3 5 7

It is the example of building a graph.The answer is in the slide.
For find_path the answer should be:4 6 8

4 10
2 1 2
1 2 2
3 1 2
1 3 2
4 1 3
1 4 3
2 3 4
3 2 4
3 4 3
4 3 3

For Prim or kruskal,the expect answer is 7.
For tansitive closure,the expect answer is:
0 1 1 1
1 0 1 0
1 1 0 1
1 0 1 0

4 6 
1 2 2
2 3 2
2 4 1
1 3 5
3 4 3
1 4 4
For Dijkstra and SPFA,the expect answer is:0 2 4 3.


*/