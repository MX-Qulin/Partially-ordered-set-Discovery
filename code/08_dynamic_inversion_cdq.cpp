#include <bits/stdc++.h>
using namespace std;
struct node {
  int op, x, y, id, t;
} b[200005];
int n, m, a[100005], pos[100005], tot;
long long ans[100005];
struct BIT {
  int c[100005];
  void clear() { memset(c, 0, sizeof(c)); }
  void add(int x, int v) { for (; x <= n; x += x & -x) c[x] += v; }
  int query(int x) {
    int s = 0;
    for (; x; x -= x & -x) s += c[x];
    return s;
  }
} bit;

void cdq(int l, int r) {
  if (l == r) return;
  int mid = (l + r) >> 1;
  cdq(l, mid);
  sort(b + l, b + mid + 1, [](const node& a, const node& b) {
    return a.x < b.x;
  });
  sort(b + mid + 1, b + r + 1, [](const node& a, const node& b) {
    return a.x < b.x;
  });
  int i = l, j = mid + 1;
  for (; j <= r; j++) {
    while (i <= mid && b[i].x < b[j].x) {
      if (b[i].op == 1) bit.add(b[i].y, 1);
      i++;
    }
    if (b[j].op == -1) ans[b[j].t] += bit.query(n) - bit.query(b[j].y);
    else ans[b[j].t] += bit.query(b[j].y - 1);
  }
  for (int k = l; k < i; k++)
    if (b[k].op == 1) bit.add(b[k].y, -1);
  sort(b + l, b + r + 1, [](const node& a, const node& b) {
    return a.t < b.t;
  });
  cdq(mid + 1, r);
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    cin >> a[i], pos[a[i]] = i, b[++tot] = {1, a[i], i, 0, tot};
  for (int i = 1, x; i <= m; ++i)
    cin >> x, b[++tot] = {-1, x, pos[x], i, tot};
  cdq(1, tot);
  for (int i = 1; i <= m; ++i) ans[i] += ans[i - 1];
  for (int i = 0; i < m; ++i) cout << ans[i] << endl;
  return 0;
}
