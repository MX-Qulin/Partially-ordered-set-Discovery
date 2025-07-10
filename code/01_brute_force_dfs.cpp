#include<bits/stdc++.h>
using namespace std;
long long n,k,a[10005][50],vst[10005],ans,flag,fflag;
void dfs(long long x,long long pre){
  for(int i=1;i<=n;i++,fflag=0) {
    if(vst[i]==0){ flag=0;
     for(int j=1;j<=k;j++) if(a[i][j]<=a[pre][j]) {flag=1; break; }
     if(flag==0) vst[i]=1,dfs(x+1,i),vst[i]=0,fflag=1;
    }
  }
  if(fflag==0) {ans=max(ans,x); return;}
}
int main(){
    cin >> n >> k;
    for(int i=1;i<=n;i++)
     for(int j=1;j<=k;j++)
      cin >> a[i][j];
    dfs(1,0),cout << ans-1;
    return 0;
}
