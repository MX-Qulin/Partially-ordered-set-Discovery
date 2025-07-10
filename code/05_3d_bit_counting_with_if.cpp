#include <bits/stdc++.h>
using namespace std;
struct node{long long x,y,z;}a[100005];
long long n,f[100005], c[2][100005], pp[100005],cnt;
bool cmp(node a,node b) {
  if(a.y==b.y&&a.z==b.z) return a.x<b.x;
  if(a.y==b.y) return a.z<b.z;
  return a.y<b.y;
}
void add(long long p,long long x,long long w) {
  for(;p<=n;p+=p&-p) c[w][p] = max(c[w][p], x);
}
long long query(long long p,long long w) {
  long long res = 0;
  for(;p;p-=p&-p) res=max(res,c[w][p]);
  return res;
}
int main() {
  cin >> n;
  for(int i=1; i<=n;i++) cin >> a[i].x >> a[i].y >> a[i].z;
  sort(a+1,a+1+n,cmp);
  for(int i=1;i<=n;i++) pp[++cnt]=a[i].x;
  sort(pp+1,pp+cnt+1);
  cnt=unique(pp+1,pp+cnt+1)-pp-1;
  for(int i=1;i<=n;i++)
    a[i].x=lower_bound(pp+1,pp+1+cnt,a[i].x)-pp;
  for(int i=1;i<=n;i++)
    if(a[i].z == 1) f[i]=query(a[i].x,0)+1,add(a[i].x,f[i],0);
    else f[i]=max(query(a[i].x,0),query(a[i].x,1))+1,add(a[i].x,f[i],1);
  cout << *max_element(f+1,f+n+1);
  return 0;
}
