#include<bits/stdc++.h>
using namespace std;
struct node {
  long long val,id;
  const bool operator < (const node& o) const { return val < o.val;}
} a[105][100005];
long long len,T,n,m,siz,cnt,l[505],r[505],bb[100005],ans,gg;
bitset<100005> mp[105][505],tmp,tmp1;
int main() {
  cin >> n >> len,siz=sqrt(n),cnt=(n-1)/siz+1;
  for(int j=1; j<=cnt; j++) {
    l[j]=r[j-1]+1;
    if(j==cnt) r[j]=n;
    else r[j]=siz*j;
    for (int k=l[j]; k<=r[j]; k++) bb[k]=j;
  }
  for (int i=1; i<=len; i++)
    for (int j=1; j<=n; j++)
      cin >> a[i][j].val,a[i][j].id=i;
  for (int i=1; i<=len; i++) {
    sort(a[i]+1,a[i]+n+1);
    for (int j=1; j<=cnt; j++) mp[i][j]=0;
  }
  for(int i=1; i<=len; i++)
    for (int j=1; j<=cnt; j++) {
      for (int k=l[j]; k<=r[j]; k++) mp[i][j][a[i][k].id]=1;
      mp[i][j]|=mp[i][j-1];
    }
  cin >> m,ans=0;
  node x= {0,n+1};
  for(int j=1; j<=m; j++) {
    tmp.set(),gg=0;
    for(long long t,i=1; i<=len; i++) {
      cin >> x.val; if(gg)continue;
      t=upper_bound(a[i]+1,a[i]+1+n,x)-a[i]-1;
      if (t<1) {tmp.reset(),gg = 1;continue;}
      tmp1=mp[i][bb[t]-1];
      for (int j=l[bb[t]]; j<=t; j++) tmp1[a[i][j].id]=1;
      tmp&=tmp1;
    }
    cout << tmp.count() << endl;
  }
  return 0;
}
