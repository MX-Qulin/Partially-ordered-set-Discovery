#include<bits/stdc++.h>
using namespace std;
long long n,a[200066],b[200066],bit[10066][566];
inline long long LSB(long long x) {return x&(-x);}
void add(long long x,long long y){
    for(int i=x;i<=H;i+=LSB(i))
     for(int j=y;j<=W;j+=LSB(j))
      bit[i][j]++;
}
ll query(long long x,long long y){
    ll sum=0;
    for(int i=x;i;i-=LSB(i))
     for(int j=y;j;j-=LSB(j))
      sum+=bit[i][j];
    return sum;
}
int main(){
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i] >> b[i],a[i]++,b[i]++,add(a[i],b[i]);
    for(int i=1;i<=n;i++) cout << query(a[i]-1,b[i]-1)-1) << " ";
    return 0;
}
