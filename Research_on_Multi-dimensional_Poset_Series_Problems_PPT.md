# Research on Multi-dimensional Partially Ordered Set Series Problems — Presentation

**Author:** Xu Runqi (徐润麒)

---

## Slide 1: Title

**Research on Multi-dimensional Partially Ordered Set Series Problems**

Xu Runqi (徐润麒)

---

## Slide 2: Concepts

> "Let R be a relation on a set A. If R is reflexive, antisymmetric, and transitive, then R is called a **partial order relation** (or simply *partial order*) on A."
>
> — Baidu Baike

**Definition of Partially Ordered Set (Poset):**

Given A = {x₁, x₂, x₃, …, xₙ} and B = {y₁, y₂, y₃, …, yₙ}:

$$x_1 < y_1 \;\wedge\; x_2 < y_2 \;\wedge\; x_3 < y_3 \;\wedge\; \cdots \;\wedge\; x_n < y_n$$

(Or with ≤ depending on the problem.)

**Properties of Partial Orders (A, B, C ∈ set):**

1. **Transitivity:** A ≤ B ∧ B ≤ C ⟹ A ≤ C
2. **Antisymmetry:** A ≤ B ∧ B ≤ A ⟹ A = B
3. **Reflexivity:** A ≤ A

---

## Slide 3: Dilworth's (Antichain) Theorem

> Let A be a finite partially ordered set, and let m be the maximum size of an antichain. Then A can be partitioned into m chains, but no fewer.

**Proof (outline):**

- **Step 1:** Prove A cannot be partitioned into fewer than r chains, where r is the max antichain size. Since any two elements in the largest antichain are incomparable, they cannot share a chain ⟹ number of chains ≥ r.
- **Step 2:** Iteratively extract minimal elements A₁, A₂, … from the remaining set. The process yields exactly k antichain layers and a chain of length k. Since r ≥ k ≥ p (min chain partition), r = p. ∎

---

## Slide 4: Problem Statement — Russian Nesting Dolls

From a k-dimensional world, you have n nesting dolls (matryoshka), numbered 1 to n. Each doll i has k size attributes a[i][1..k].

To nest doll i inside doll j: **all** attributes must be strictly greater:

$$a[i][1] > a[j][1] \;\wedge\; \cdots \;\wedge\; a[i][k] > a[j][k]$$

**Goal:** Maximum number of nested dolls.

**Constraints:** n ≤ 200,000, k ≤ 100

---

## Slide 5: Step-by-Step Solutions by Dimension

- **k = 1:** Sort and count. Time: O(n log n).
- **k = 2:** 2D LIS. Time: O(n log n).
- **k = 3+:** Brute-force DFS becomes infeasible.

| N, K | Time | Memory |
|------|------|--------|
| 100, 3 | 0.97s | 10.2 MB |
| 1000, 3 | 10.2s | 77.6 MB |
| 10000, 5 | 692.7s | 298.9 MB |
| 200000, 100 | ∞ (stack overflow) | ∞ |

---

## Slide 6: Special Case — 3D with Two Values in Dimension 3

If the third dimension has only values {1, 2}:

- Sort by dimension 1.
- Compute 2D LIS for z=1 elements → store in l[].
- Compute 2D LIS for z=2 elements → store in r[].
- Enumerate the split point, merge l[] + r[] to find the optimal answer.

---

## Slide 7: Code for the Special Case

Key idea: `l[i]` and `r[i]` represent the maximum subsequence length ending at element i when the 3rd dimension is 1 or 2 respectively. Enumerate all possible split points and take the max of l[i] + r[i] - 1.

---

## Slide 8: General 3D Poset — Solution Methods

### Approaches

| Method | Time Complexity | Notes |
|--------|----------------|-------|
| BIT + Balanced BST | O(t·n log n·q) | Small constant t |
| SegTree + SegTree | O(16·q·n log n) | Large constant — avoid |
| SegTree + BIT | Same, reduced constant | Optimization of above |
| **CDQ Divide & Conquer** | **O(n log²n)** | **Best choice** |
| K-D Tree | Varies with pruning | Prune aggressively |

---

## Slide 9: CDQ Divide and Conquer

### Algorithm Steps

1. **Divide:** Split [l, r] into [l, mid] and [mid+1, r].
2. **Merge:** Sort both halves by dimension y. Since x was pre-sorted, left half x ≤ right half x.
3. **Compute Contribution:** For each j in [mid+1, r], scan i in left half where a[i].y ≤ a[j].y; update BIT at a[i].z with max(dp[i], bit[·]).
4. **Query:** dp[j] = BIT.query(a[j].z) + 1.
5. **Recurse:** Process [mid+1, r] recursively.

**Time:** O(n log²n) — the y-sorting is maintained through merging.

---

## Slide 10: Computing Contributions in CDQ

The left half contributes to the right half. A BIT on dimension z stores the best dp values seen so far. As we sweep through y values:

- When a[left].y ≤ a[right].y → update BIT at a[left].z
- When processing a[right] → dp[right] = max in BIT over [1, a[right].z] + 1

---

## Slide 11: Visualization

*(Diagram showing the divide step with l, mid, r pointers; sorting by y; and BIT operations: update and query)*

---

## Slide 12: Performance Comparison

| n | BIT+BST | SegTree² | SegTree+BIT | **CDQ** | K-D Tree |
|---|---------|----------|-------------|---------|----------|
| 100 | 4ms | 9ms | 6ms | **5ms** | 4ms |
| 5,000 | 83ms | 69ms | 50ms | **44ms** | 38ms |
| 10,000 | 81ms | 775ms | 360ms | **92ms** | 132ms |
| 50,000 | 428ms | 1.76s | 763ms | **132ms** | 406ms |
| 100,000 | 641ms | 4.28s | 1.09s | **148ms** | 766ms |
| Code Lines | 119 | 81 | 78 | **46** | 114 |

**Conclusion:** CDQ wins everywhere — fastest, smallest code.

---

## Slide 13: Block Decomposition Alternative

For those who prefer simplicity:

- Partition into √n blocks.
- Sort each dimension independently, store prefix sums.
- Query using binary search per block.

**Time:** O(n·k + m·k·√n)

**Critical:** Use `bitset` for constant-factor optimization!

---

## Slide 14: Block Decomposition Code

```cpp
bitset<100005> mp[105][505], tmp, tmp1;
// Sort each dimension, build block-level bitsets
// For each query: intersect bitsets across dimensions
// Answer = tmp.count()
```

---

## Slide 15: Bitset Speedup

| Config | Without bitset | With bitset |
|--------|---------------|-------------|
| n=100,000, k=50 | 4.76s | — |
| n=200,000, k=100 | timeout | **753ms** |

---

## Slide 16: Derived Problem — Dynamic Inversion Counting

**Problem:** Given a permutation of 1~n, delete m elements sequentially. Before each deletion, output the current number of inversions.

**Constraints:** 1 ≤ n ≤ 100,000, 1 ≤ m ≤ 50,000

---

## Slide 17: Dynamic Inversions — Solution 1 (CDQ)

- Reverse the deletions into insertions.
- Assign time stamps t[i] to each element.
- The problem becomes: count (t, x, y) triples with t < t₀, x < x₀, y > y₀.
- **This is a 3D poset counting problem!** Apply CDQ directly.

**Time:** O(n log²n)

---

## Slide 18–19: Dynamic Inversions — Solution 2 (Block Decomposition)

Each deletion of element k removes:
- Inversions within k's block (use BIT)
- Inversions with preceding blocks (binary search for elements > k)
- Inversions with succeeding blocks (binary search for elements < k)

**Time:** O(n√n)

**Demo:** Starting with 15 inversions, deleting element "2" removes 4 inversions → 11 remain.

---

## Slide 20: Thanks

For questions and contributions, please open an issue on this repository.
