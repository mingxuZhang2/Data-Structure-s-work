#include <bits/stdc++.h>
using namespace std;
class Array{
    public:
        int a[10050],b[10050];
        int com[10000],Bub[10050],merge[10050],insert[10050];
        int length;int value[10050];
        Array(){
            
        }
        Array(int *arr,int n);
        inline void Bubble_sort();
        inline void select_sort();
        inline void Compare_sort();
        inline void Great_select_sort();
        inline void insert_sort();
        inline void merge_sort(int l,int r);
        inline void great_insert_sort();
};
Array::Array(int *arr,int n){
    length=n;
    for(int i=1;i<=n;i++) a[i]=arr[i];
}
void Array::Bubble_sort(){
    bool is_sort;
    for(int i=1;i<=length&&is_sort==0;i++){
        is_sort=1;
        for(int j=i+1;j<=length;j++)
        if(a[i]>a[j]) swap(a[i],a[j]),is_sort=0;
    }
    for(int i=1;i<=length;i++) Bub[i]=a[i];
}
void Array::Compare_sort(){
    for(int i=1;i<=length;i++){
        for(int j=i+1;j<=length;j++){
            if(a[i]<a[j]) value[j]++;
            else value[i]++;
        }
    }
    for(int i=1;i<=length;i++) com[value[i]+1]=a[i];
}
void Array::select_sort(){
    int pos=1;
    for(int i=1;i<=length;i++){
        for(int j=i+1;j<=length;j++){
            if(a[pos]>=a[j]) pos=j;
        }
        swap(a[pos],a[i]);pos=i+1;
    }
}
inline int search(int l,int r,int aim,int *a){
    int mid=(l+r)/2; 
    if(l==r&&a[l]>aim) return l;
    if(l==r&&a[l+1]<=aim) return l+1;
    if(a[mid]<aim) return search(mid+1,r,aim,a);
    if(a[mid]>aim)  return search(l,mid,aim,a); 
    if(a[mid]==aim) return mid; 
}
void Array::great_insert_sort(){
    insert[1]=a[1];int j;
    for(int i=2;i<=length;i++){
        j=search(1,i-1,a[i],insert);
        for(int k=i-1;k>=j;k--) insert[k+1]=insert[k];
        insert[j]=a[i];
    }
}
void Array::insert_sort(){
    insert[1]=a[1];
    int j=1;
    for(int i=2;i<=length;i++){
        for(j=i-1;j>=1&&a[i]<insert[j];j--){
            insert[j+1]=insert[j]; 
        }
        insert[j+1]=a[i];
    }
}
void Array::Great_select_sort(){ 
    int pos=1;
    bool is_sort=0;
    for(int i=1;i<=length&&is_sort==0;i++){
        is_sort=1;
        for(int j=i+1;j<=length;j++){
            if(a[pos]>=a[j]) pos=j,is_sort=0; //取最小的那个数放到数组前面
        }
        swap(a[pos],a[i]);pos=i+1;
    }
}
void Array::merge_sort(int l,int r){
    int mid=(l+r)/2;if(l>=r) return ;
    int left=l;int right=r;int middle=mid+1;int cnt=l;
    merge_sort(l,mid);merge_sort(mid+1,r);
    while(left<=mid||middle<=r){
        if(middle>r||(left<=mid&&a[left]<=a[middle])) b[cnt++]=a[left++];
        else b[cnt++]=a[middle++];
    }
    for(int i=l;i<=r;i++) a[i]=b[i];
}
int nn,n,a[10050];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    Array arr(a,n);
 //   arr.select_sort();
   // arr.Compare_sort();
  //  arr.Bubble_sort();
  //  arr.merge_sort(1,n);
  //  arr.Great_select_sort();
    //arr.insert_sort();
    arr.great_insert_sort();
    for(int i=1;i<=arr.length;i++){
        cout<<arr.insert[i]<<" ";
    }
    cout<<endl;
    system("pause");
}