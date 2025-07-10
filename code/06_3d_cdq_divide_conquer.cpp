#include<bits/stdc++.h>
using namespace std;
struct node {long long x,y,z,id;} a[100005],tl[100005],tr[100005];
long long dp[100005],n,m,d[100005],ans[100005],bit[100005],mid,t1,t2;
bool cmpx(node aa,node bb) {
  if(aa.x==bb.x&&aa.y==bb.y)return aa.z<bb.z;
  if(aa.x==bb.x)return aa.y<bb.y;
  return aa.x<bb.x;
}
bool cmpy(node aa,node bb) {
  if(aa.y==bb.y)return aa.z<bb.z;
  return aa.y<bb.y;
}
inline void clear(long long x) { for(;x<=m;x+=x&(-x)) bit[x]=0; }
void add(long long x,long long k) {
  for(;x<=m;x+=x&(-x)) bit[x]=max(k,bit[x]);
}
long long query(long long x) {
  long long ans=0;
  for(;x;x-=x&(-x)) ans=max(ans,bit[x]);
  return ans;
}
void calc(int l,int r) {
  if(l>=r)return;
  mid=(l+r)>>1,calc(l,mid),t1=0,t2=0;
  for(int i=l; i<=mid; i++)tl[++t1]=a[i];
  for(int i=mid+1; i<=r; i++)tr[++t2]=a[i];
  sort(tl+1,tl+t1+1,cmpy),sort(tr+1,tr+t2+1,cmpy);
  for(int i=1,j=1; j<=t2; j++) {
    for(;tl[i].y<=tr[j].y&&i<=t1;i++) add(tl[i].z,dp[tl[i].id]);
    long long sum=query(tr[j].z)+1;
    if(dp[tr[j].id]<sum) dp[tr[j].id]=sum;
  }
  for(int i=l; i<=mid; i++)clear(a[i].z);
  calc(mid+1,r);
}
int main() {
  cin >> n;
  for(int i=1; i<=n; i++)
    a[i].id=i,dp[i]=1,cin >> a[i].x >> a[i].y >> a[i].z,d[i]=a[i].z;
  sort(d+1,d+n+1),m=unique(d+1,d+n+1)-d-1;
  for(int i=1; i<=n; i++)a[i].z=lower_bound(d+1,d+m+1,a[i].z)-d;
  sort(a+1,a+n+1,cmpx),calc(1,n);
  cout << *max_element(dp+1,dp+n+1);
  return 0;
}
