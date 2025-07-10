# Research on Multi-dimensional Partially Ordered Set Series Problems

**Author:** Xu Runqi (徐润麒)

---

## Abstract

This paper presents a comparative study and analysis of approaches for solving multi-dimensional partially ordered set (poset) problems using CDQ divide-and-conquer, binary search, and block decomposition techniques.

**References:**

1. "Catch the Penguins" (4-dimensional poset problem) — Zhang Wentao, Hangzhou Xuejun High School
2. "On the Application of Block Decomposition in a Class of Data Processing Problems" (Block decomposition) — Luo Jianqiao, Beijing No.18 Middle School
3. "On a Class of Divide-and-Conquer Algorithms from \<Cash\>" (CDQ divide-and-conquer) — Chen Danqi (CDQ)

---

## Introduction

> "Let R be a relation on a set A. If R is reflexive, antisymmetric, and transitive, then R is called a **partial order relation** (or simply *partial order*) on A. For (a, b) ∈ R, we write a ≤ b. If a partial order relation is given on set A, then A is called a **partially ordered set** (poset) under the relation ≤. A and R together are called a poset."
>
> — Baidu Baike

### Definition of Partially Ordered Set (Poset)

Given two sets A = {x₁, x₂, x₃, …, xₙ} and B = {y₁, y₂, y₃, …, yₙ}, a partial order relation holds when:

$$x_1 < y_1 \;\wedge\; x_2 < y_2 \;\wedge\; x_3 < y_3 \;\wedge\; \cdots \;\wedge\; x_n < y_n$$

> **Note:** It is also possible to have x₁ ≤ y₁ ∧ x₂ ≤ y₂ ∧ …, depending on the specific problem.

### Properties of Partial Orders

Let A, B, C be elements of the set:

1. **Transitivity:** If A ≤ B and B ≤ C, then A ≤ C.
2. **Antisymmetry:** If A ≤ B and B ≤ A, then A = B.
3. **Reflexivity:** A ≤ A.

---

## Dilworth's (Antichain) Theorem

> **Theorem.** Let A be a finite partially ordered set, and let m be the maximum size of an antichain. Then A can be partitioned into m chains, but no fewer.

### Proof (excerpt)

Let p be the minimum number of chains in a partition.

1. First, we prove that A cannot be partitioned into fewer than r chains, where r is the size of the largest antichain C. Since any two elements in C are incomparable, no two can belong to the same chain. Hence p ≥ r.

2. Let B₁ = A, and let A₁ be the set of minimal elements of A. Remove A₁ from B₁ to obtain B₂. For any element a₂ in B₂, there exists an element a₁ in B₁ such that a₁ ≤ a₂. Let A₂ be the set of minimal elements of B₂, remove A₂ from B₂ to obtain B₃, and so on. Eventually Bₖ is non-empty and B(k+1) is empty. Then A₁, A₂, …, Aₖ is an antichain partition of A. Meanwhile, there exists a chain a₁ ≤ a₂ ≤ … ≤ aₖ where aᵢ ∈ Aᵢ. Since r is the maximum chain size, r ≥ k ≥ p. Therefore r = p. ∎

---

## Problem Formulation

Two fundamental types of problems arise from posets:

1. **Optimization problem:** Find the longest subsequence satisfying a partial order relation.
2. **Counting problem:** Count the number of elements that are in a partial order relation with a given element.

### General Problem Statement ("Russian Nesting Dolls" Series)

**Description:**

You have n independent Russian nesting dolls (matryoshka), numbered 1 to n, in a k-dimensional world. Each doll i has k size attributes a[i][1..k]. To place doll i inside doll j, the outer doll i must have **all** size attributes strictly greater than those of doll j:

$$a[i][1] > a[j][1] \;\wedge\; a[i][2] > a[j][2] \;\wedge\; \cdots \;\wedge\; a[i][k] > a[j][k]$$

**Goal:** Find the maximum number of dolls that can be nested together.

**Input:**

```
n k
n×k two-dimensional array
```

**Constraints:**

- n ≤ 200,000
- k ≤ 100

> Why k ≤ 100? Because for large k the input becomes too slow and arrays cannot fit in memory.

### Brute-Force Solution (n dimensions, for benchmarking)

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, k, a[10005][50], vst[10005], ans, flag, fflag;
void dfs(long long x, long long pre) {
    for (int i = 1; i <= n; i++, fflag = 0) {
        if (vst[i] == 0) {
            flag = 0;
            for (int j = 1; j <= k; j++)
                if (a[i][j] <= a[pre][j]) { flag = 1; break; }
            if (flag == 0)
                vst[i] = 1, dfs(x + 1, i), vst[i] = 0, fflag = 1;
        }
    }
    if (fflag == 0) { ans = max(ans, x); return; }
}
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= k; j++)
            cin >> a[i][j];
    dfs(1, 0), cout << ans - 1;
    return 0;
}
```

---

## 1-Dimensional Poset

**Time Complexity:** O(n), O(n log n); **Space:** O(n)

### Problem Type 1 (Optimization)

Sort the array and count the number of elements satisfying a[i] > a[i-1].

### Problem Type 2 (Counting)

After sorting, for a query element, output the number of preceding elements (excluding equal elements).

---

## 2-Dimensional Poset

**Time Complexity:** O(n log n) for both problem types.

### Problem Type 1 (Optimization: Longest Increasing Subsequence)

Since one dimension of the LIS must be monotonically increasing, sort by one dimension first.

```
First dimension sorted: 1, 3, 4, 6, 8
LIS on the second dimension: 1 → 3 → 6 → 8
```

After sorting, apply the 1D LIS algorithm (Dilworth's theorem → greedy + binary search) on the remaining dimension.

**Code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, ans = 1, dp[200005], aa[200005], k;
struct info { long long a, b; } x[200005];
bool cmp(info x, info y) {
    if (x.a == y.a) return x.b > y.b;
    return x.a < y.a;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i].a;
    for (int i = 1; i <= n; i++) cin >> x[i].b;
    sort(x + 1, x + n + 1, cmp);
    for (int i = 1; i <= n; i++) aa[i] = x[i].b;
    dp[1] = x[1].b;
    for (int i = 2; i <= n; i++) {
        if (dp[ans] < aa[i]) k = ++ans;
        else k = lower_bound(dp, dp + ans, aa[i]) - dp;
        dp[k] = aa[i];
    }
    cout << ans;
    return 0;
}
```

### Problem Type 2 (Counting: Partially Ordered Set Cardinality)

Maintain a prefix sum array; using a **2D Binary Indexed Tree (BIT)** as the data structure improves time efficiency and can handle dynamically added points. *(This is the foundation for multi-dimensional poset problems below.)*

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, a[200066], b[200066], bit[10066][566];
inline long long LSB(long long x) { return x & (-x); }
void add(long long x, long long y) {
    for (int i = x; i <= H; i += LSB(i))
        for (int j = y; j <= W; j += LSB(j))
            bit[i][j]++;
}
ll query(long long x, long long y) {
    ll sum = 0;
    for (int i = x; i; i -= LSB(i))
        for (int j = y; j; j -= LSB(j))
            sum += bit[i][j];
    return sum;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i], a[i]++, b[i]++, add(a[i], b[i]);
    for (int i = 1; i <= n; i++)
        cout << query(a[i] - 1, b[i] - 1) - 1 << " ";
    return 0;
}
```

---

## 3-Dimensional Poset

**Time Complexity:** O(n log n)

### Special Case: Third Dimension Has Only Two Values

If the third dimension takes only values {1, 2}, the partial order between any two elements in dimension 3 is fully determined. We can reduce this to a 2D poset problem by classifying by the third dimension.

**Idea:** Enumerate the split point — the last element with z=1 and the first with z=2. Compute a 2D LIS for each class, then merge.

```cpp
#include <bits/stdc++.h>
using namespace std;
struct node { long long x, y, z; } a[100005];
long long p, l[100005], r[100005], f1[100005], f2[100005],
          n, ans1, ans2, ans;
bool cmp(node a, node b) {
    if (a.x == b.x && a.y == b.y) return a.z <= b.z;
    if (a.x == b.x) return a.y <= b.y;
    return a.x <= b.x;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].x >> a[i].y >> a[i].z;
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++)
        if (a[i].z == 1)
            if (a[i].y >= f1[ans1]) f1[++ans1] = a[i].y, l[i] = ans1;
            else p = upper_bound(f1 + 1, f1 + 1 + ans1, a[i].y) - f1,
                 l[i] = p, f1[p] = a[i].y;
        else l[i] = upper_bound(f1 + 1, f1 + 1 + ans1, a[i].y) - f1;
    fill(f2, f2 + 100004, 987654321);
    for (int i = n; i >= 1; i--)
        if (a[i].z == 2)
            if (a[i].y <= f2[ans2]) f2[++ans2] = a[i].y, r[i] = ans2;
            else p = upper_bound(f2 + 1, f2 + 1 + ans2, a[i].y, greater<int>()) - f2,
                 r[i] = p, f2[p] = a[i].y;
        else r[i] = upper_bound(f2 + 1, f2 + 1 + ans2, a[i].y, greater<int>()) - f2;
    for (int i = 1; i <= n; i++) ans = max(ans, l[i] + r[i] - 1);
    cout << ans;
    return 0;
}
```

### General Case

**Why is brute force slow?** It computes redundant information. If we have already determined A ≤ B ≤ C, any future enumeration where C appears before B can be immediately rejected. We must eliminate redundant computation.

After sorting by the first dimension, we need to find a 2D poset on the remaining two dimensions. Since the first dimension is already sorted, we cannot simply reduce dimensionality again. Available methods:

#### Method 1: Tree-of-Balanced-Trees (BIT + Balanced BST)

Use a BIT where each node contains a balanced BST (splay, treap, etc.) maintaining the rank of the 3rd dimension, while the BIT itself maintains prefix counts on the 2nd dimension.

**Time:** O(t·n log n · q) where t is a small constant.

#### Method 2: Segment Tree of Segment Trees

Sort by the first dimension, then solve the 2D poset using dynamic node creation + quadrant decomposition, recursively splitting intervals into four quadrants.

**Time:** O(16·q·n log n) — large constant warning!

#### Method 3: Segment Tree of BITs

Optimization of Method 2. Replace the outer segment tree with a BIT to reduce the constant factor.

---

## CDQ Divide and Conquer (Dimension Reduction)

CDQ divide and conquer reduces dimensions. The key idea:

1. Sort by the first dimension (x).
2. Divide [l, r] into [l, mid] and [mid+1, r].
3. Sort both halves by the second dimension (y). Since x was pre-sorted, all elements in [mid+1, r] have x ≥ max of [l, mid].
4. For each element j in [mid+1, r], scan the left half with cursor i: when a[i].y ≤ a[j].y, update the BIT at position a[i].z with max(dp[i], bit[a[i].id]).
5. Then dp[j] = query(1, a[j].z) + 1.
6. The answer is max(dp[1..n]).

**Time Complexity:** O(n log²n)

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node { long long x, y, z, id; } a[100005], tl[100005], tr[100005];
long long dp[100005], n, m, d[100005], ans[100005], bit[100005], mid, t1, t2;
bool cmpx(node aa, node bb) {
    if (aa.x == bb.x && aa.y == bb.y) return aa.z < bb.z;
    if (aa.x == bb.x) return aa.y < bb.y;
    return aa.x < bb.x;
}
bool cmpy(node aa, node bb) {
    if (aa.y == bb.y) return aa.z < bb.z;
    return aa.y < bb.y;
}
inline void clear(long long x) { for (; x <= m; x += x & (-x)) bit[x] = 0; }
void add(long long x, long long k) {
    for (; x <= m; x += x & (-x)) bit[x] = max(k, bit[x]);
}
long long query(long long x) {
    long long ans = 0;
    for (; x; x -= x & (-x)) ans = max(ans, bit[x]);
    return ans;
}
void calc(int l, int r) {
    if (l >= r) return;
    mid = (l + r) >> 1, calc(l, mid), t1 = 0, t2 = 0;
    for (int i = l; i <= mid; i++) tl[++t1] = a[i];
    for (int i = mid + 1; i <= r; i++) tr[++t2] = a[i];
    sort(tl + 1, tl + t1 + 1, cmpy), sort(tr + 1, tr + t2 + 1, cmpy);
    for (int i = 1, j = 1; j <= t2; j++) {
        for (; tl[i].y <= tr[j].y && i <= t1; i++)
            add(tl[i].z, dp[tl[i].id]);
        long long sum = query(tr[j].z) + 1;
        if (dp[tr[j].id] < sum) dp[tr[j].id] = sum;
    }
    for (int i = l; i <= mid; i++) clear(a[i].z);
    calc(mid + 1, r);
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        a[i].id = i, dp[i] = 1,
        cin >> a[i].x >> a[i].y >> a[i].z, d[i] = a[i].z;
    sort(d + 1, d + n + 1), m = unique(d + 1, d + n + 1) - d - 1;
    for (int i = 1; i <= n; i++)
        a[i].z = lower_bound(d + 1, d + m + 1, a[i].z) - d;
    sort(a + 1, a + n + 1, cmpx), calc(1, n);
    cout << *max_element(dp + 1, dp + n + 1);
    return 0;
}
```

---

## K-D Tree (General K-Dimensional Poset)

A K-D tree is a data structure for organizing points in k-dimensional Euclidean space. The approach to 3D poset problems using K-D trees is similar to CDQ divide and conquer:

1. Sort by the first dimension x.
2. Build a K-D tree on dimensions (y, z) to maintain the number of qualifying points (with both y and z smaller) among preceding elements.
3. Query the K-D tree for the maximum point weight in the rectangle {(-∞, -∞), (y[i], z[i])}; the answer is max_weight + 1 = f[i].
4. Insert (y[i], z[i]) with weight f[i] into the K-D tree.

**Important:** During K-D tree queries, prune branches when the maximum value in the entire subtree is less than or equal to the current best. Otherwise, the solution will TLE!

---

## Performance Comparison Table

| n       | BIT + Balanced BST | SegTree + SegTree | SegTree + BIT | CDQ Divide | K-D Tree |
|---------|--------------------|--------------------|---------------|------------|----------|
| 100     | 4ms / 656KB        | 9ms / 6.75MB       | 6ms / 2.11MB  | 5ms / 788KB | 4ms / 652KB |
| 5,000   | 83ms / 4.56MB      | 69ms / 17.12MB     | 50ms / 6.89MB | 44ms / 1.77MB | 38ms / 1.14MB |
| 10,000  | 81ms / 5.89MB      | 775ms / 129.84MB   | 360ms / 60.72MB | 92ms / 2.53MB | 132ms / 2.06MB |
| 50,000  | 428ms / 12.77MB    | 1.76s / 179.63MB   | 763ms / 118.88MB | 132ms / 4.41MB | 406ms / 4.66MB |
| 100,000 | 641ms / 19.01MB    | 4.28s / 347.83MB   | 1.09s / 239.52MB | 148ms / 5.09MB | 766ms / 7.66MB |
| Code Lines | 119             | 81                 | 78            | 46         | 114      |

### Summary

1. **CDQ is the absolute best choice** — it wins across the board.
2. Be careful with segment tree space and time complexity.
3. Avoid segment trees if possible — the code is too long.
4. For higher dimensions, nest CDQ divide and conquer (use if-statements to distinguish dimensions): complexity O(k·n log n).

---

## Block Decomposition (Alternative Approach)

Block decomposition is a general-purpose technique for queries, extrema, and counting problems.

### Algorithm

1. Partition the dolls into √n blocks.
2. For each dimension independently, sort the values and record prefix information (cumulative counts at each sorted position).
3. Use l[j], r[j] to track each block's range.
4. For queries, perform binary search within each block.

**Time Complexity:** O(n·k + m·k·√n)

### Bitset Optimization

Using `bitset` as a constant-factor optimization reduces runtime from 4.76s to 753ms for n=200,000, k=100.

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node {
    long long val, id;
    const bool operator < (const node& o) const { return val < o.val; }
} a[105][100005];
long long len, T, n, m, siz, cnt, l[505], r[505], bb[100005], ans, gg;
bitset<100005> mp[105][505], tmp, tmp1;
int main() {
    cin >> n >> len, siz = sqrt(n), cnt = (n - 1) / siz + 1;
    for (int j = 1; j <= cnt; j++) {
        l[j] = r[j - 1] + 1;
        if (j == cnt) r[j] = n; else r[j] = siz * j;
        for (int k = l[j]; k <= r[j]; k++) bb[k] = j;
    }
    for (int i = 1; i <= len; i++)
        for (int j = 1; j <= n; j++)
            cin >> a[i][j].val, a[i][j].id = i;
    for (int i = 1; i <= len; i++) {
        sort(a[i] + 1, a[i] + n + 1);
        for (int j = 1; j <= cnt; j++) mp[i][j] = 0;
    }
    for (int i = 1; i <= len; i++)
        for (int j = 1; j <= cnt; j++) {
            for (int k = l[j]; k <= r[j]; k++) mp[i][j][a[i][k].id] = 1;
            mp[i][j] |= mp[i][j - 1];
        }
    cin >> m, ans = 0;
    node x = {0, n + 1};
    for (int j = 1; j <= m; j++) {
        tmp.set(), gg = 0;
        for (long long t, i = 1; i <= len; i++) {
            cin >> x.val; if (gg) continue;
            t = upper_bound(a[i] + 1, a[i] + 1 + n, x) - a[i] - 1;
            if (t < 1) { tmp.reset(), gg = 1; continue; }
            tmp1 = mp[i][bb[t] - 1];
            for (int j = l[bb[t]]; j <= t; j++) tmp1[a[i][j].id] = 1;
            tmp &= tmp1;
        }
        cout << tmp.count() << endl;
    }
    return 0;
}
```

---

## Derived Problem: Dynamic Inversion Counting

### Problem Statement

Given a permutation of 1~n, elements are deleted one by one in some order (m deletions total). Before each deletion, output the total number of inversions in the sequence.

**Constraints:** 1 ≤ n ≤ 100,000, 1 ≤ m ≤ 50,000

### Solution 1: CDQ Divide and Conquer

A deletion can be viewed as a reverse insertion. Define t[i] as the time the i-th element was inserted (t[1] = n for the last insertion). Undeleted nodes have t[i] set to 1, 2, 3, … from left to right.

This transforms the problem into counting triples (t, x, y) satisfying t < t₀, x < x₀, y > y₀ — a **3D poset counting problem**.

**Time:** O(n log²n), **Space:** O(n)

### Solution 2: Block Decomposition

Each deletion of element k removes (number of elements before k that are larger + number of elements after k that are smaller).

1. Precompute the total inversion count using a BIT.
2. Partition the sequence into √n blocks, sort within each block.
3. For each deletion: use a BIT for k's block, binary search in preceding blocks for elements > k, and in succeeding blocks for elements < k.

**Time Complexity:** O(n√n)

---

## Conclusion

Multi-dimensional poset problems appear in many areas of algorithm design. Readers are encouraged to explore more efficient algorithms. The block decomposition approach provides a simple yet effective alternative, often scoring 80+ points on competitive programming problems with minimal code.
