#include <bits/stdc++.h>
using namespace std;
long long ans,n,m,x,y,k,ll,rr,rec,num,block,a[500005],b[500005],
bit[500005],tmp[500005],belong[500005],l[500005],
r[500005],s[500005],id[500005];
bool f[500005];
inline long long lowbit(long long x){return x&-x;}
void add(long long x,long long v){
  for(;x<=n;x+=lowbit(x))bit[x]+=v;
}
long long query(long long x){
  long long sum=0;
  for(;x;x-=lowbit(x)) sum+=bit[x];
  return sum;
}
long long finder(long long pos,long long val){
  ll=l[pos],rr=r[pos],rec=r[pos];
  while(ll<=rr){
    int mid=(ll+rr)/2;
    if(b[mid]<=val) rec=mid,ll=mid+1;
    else rr=mid-1;
  }
  if(b[rec]>val) return l[pos]-1;
  else return rec;
}
int main(){
  cin >> n >> m;
  block=sqrt(n),num=n/block+1;
  for(int i=1; i<=num; i++) l[i]=(i-1)*block+1,r[i]=i*block;
  r[num]=n;
  for(int i=1; i<=n; i++) belong[i]=(i-1)/block+1;
  for(int i=1; i<=n; i++)
    cin >> a[i],tmp[i]=a[i],id[a[i]]=i,
    add(a[i],1),ans+=i-query(a[i]),b[i]=a[i],f[i]=1;
  for(int i=1; i<=num; i++) sort(b+l[i],b+r[i]+1);
  while(m--){
    cout << ans << endl,cin >> y;
    x=id[y],k=belong[x];
    for(int i=1; i<k; i++) ans-=(r[i]-finder(i,a[x]));
    for(int i=k+1;i<=num;i++) ans-=finder(i,a[x])-l[i]+1-s[i];
    for(int i=l[k]; i<x; i++) if(f[a[i]]&&a[i]>a[x]) ans--;
    for(int i=x+1;i<=r[k];i++)if(f[a[i]]&&a[i]<a[x]) ans--;
    b[finder(k,a[x])]=0,s[k]++,f[a[x]]=0;
    sort(b+l[k],b+r[k]+1);
  }
  return 0;
}
