#include<bits/stdc++.h>
using namespace std;
long long n,ans=1,dp[200005],aa[200005],k;
struct info{long long a,b;}x[200005];
bool cmp(info x,info y){
    if(x.a==y.a) return x.b>y.b;
    return x.a<y.a;
}
int main(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> x[i].a;
    for(int i=1;i<=n;i++) cin >> x[i].b;
    sort(x+1,x+n+1,cmp);
    for(int i=1;i<=n;i++) aa[i]=x[i].b;
    dp[1]=x[1].b;
    for(int i=2;i<=n;i++) {
        if(dp[ans]<aa[i]) k=++ans;
        else k=lower_bound(dp,dp+ans,aa[i])-dp;
        dp[k]=aa[i];
    }
    cout << ans;
    return 0;
}
