#include <bits/stdc++.h>
using namespace std;
struct node{long long x,y,z;}a[100005];
long long p,l[100005],r[100005],f1[100005],f2[100005],n,ans1,ans2,ans;
bool cmp(node a,node b) {
  if(a.x==b.x&&a.y==b.y) return a.z<=b.z;
  if(a.x==b.x) return a.y<=b.y;
  return a.x<=b.x;
}
int main() {
  cin >> n;
  for(int i=1;i<=n;i++) cin >> a[i].x >> a[i].y >> a[i].z;
  sort(a+1,a+1+n,cmp);
  for(int i=1;i<=n;i++)
   if(a[i].z==1)
    if(a[i].y>=f1[ans1]) f1[++ans1]=a[i].y,l[i]=ans1;
    else p=upper_bound(f1+1,f1+1+ans1,a[i].y)-f1,l[i]=p,f1[p]=a[i].y;
   else l[i]=upper_bound(f1+1,f1+1+ans1,a[i].y)-f1;
   fill(f2,f2+100004,987654321);
   for(int i=n;i>=1;i--)
    if(a[i].z==2)
     if(a[i].y<=f2[ans2])f2[++ans2]=a[i].y,r[i]=ans2;
     else p=upper_bound(f2+1,f2+1+ans2,a[i].y,greater<int>())-f2,r[i]=p,f2[p]=a[i].y;
    else r[i]=upper_bound(f2+1,f2+1+ans2,a[i].y,greater<int>())-f2;
   for(int i=1;i<=n;i++) ans=max(ans,l[i]+r[i]-1);
   cout << ans;
   return 0;
}
