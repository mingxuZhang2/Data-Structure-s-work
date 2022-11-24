#include <bits/stdc++.h>
using namespace std;
int n;int b[101][101];
class Martix{
    public:
        int value[101][101];
        int edge;
        Martix(int *pr,int n);
        Martix(){}
        friend inline Martix operator+(Martix a,Martix b){
            Martix c;
            for(int i=1;i<=a.edge;i++)
            for(int j=1;j<=a.edge;j++)
            c.value[i][j]=a.value[i][j]+b.value[i][j];
            return c;
        }
        friend inline Martix operator*(Martix a,Martix b){
            Martix c;
            for(int i=1;i<=a.edge;i++){
                for(int j=1;j<=a.edge;j++)
                for(int k=1;k<=a.edge;k++){
                    c.value[i][j]+=a.value[i][k]*b.value[k][j];
                }
            }
            return c;
        }
};
Martix::Martix(int *pr,int n){
    edge=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            value[i][j]=pr[i*101+j];
        }
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>b[i][j];
        }
    }
    int *pr=b[1];
    Martix a;
    a=Martix(b[0],n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>b[i][j];
            b[i][j]*=-1;
        }
    }
    
    Martix B;
    B=Martix(b[0],n);
    Martix C=a+B;
    cout<<"The Martix plus result is:"<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) cout<<C.value[i][j]<<" ";
        cout<<endl;
    }
    Martix D=a*B;
    cout<<"another result of the mutiply is"<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) cout<<D.value[i][j]<<" ";
        cout<<endl;
    }
    system("pause");
    return 0;
}