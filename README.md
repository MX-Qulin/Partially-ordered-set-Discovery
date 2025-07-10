# Partially-ordered-set-Discovery

### Research Background

A **partially ordered set** (poset) is a fundamental concept in combinatorics and order theory. Given a set A and a relation ≤ that is reflexive, antisymmetric, and transitive, the pair (A, ≤) forms a poset. The study of posets connects deeply with lattice theory, graph theory, and the theory of well-quasi-orderings. In computer science, poset problems manifest as **k-dimensional dominance queries**: given n points in k-dimensional space, find the longest chain under the coordinate-wise ordering, or count the number of comparable pairs.

These problems arise naturally in competitive programming (e.g., the "Russian Nesting Dolls" problem), database query optimization, computational geometry, and parallel computing. As the dimensionality k grows, naive O(n^k) approaches become intractable, motivating sophisticated techniques such as CDQ divide-and-conquer, tree-of-trees structures, K-D trees, and bitset-accelerated block decomposition.

> **We recommend reading the Chinese PDFs for the complete visual experience.** While the English translations cover all text content, the original PDFs contain numerous diagrams (step-by-step LIS demonstrations, CDQ divide-and-conquer flow charts, block decomposition visualizations, dynamic inversion pair demos) that cannot be fully reconstructed as text.

### Repository Structure

| File | Description |
|------|-------------|
| `关于多维偏序集系列问题的研究.pdf` | Main research paper (Chinese, with full diagrams) |
| `关于多维偏序集系列问题的研究-PPT.pdf` | Presentation slides (Chinese, with full diagrams) |
| `english/Research_on_Multi-dimensional_Poset_Series_Problems.md` | Full English translation of the paper |
| `english/Research_on_Multi-dimensional_Poset_Series_Problems.pdf` | Paper English PDF |
| `english/Research_on_Multi-dimensional_Poset_Series_Problems_PPT.md` | Full English translation of the slides |
| `english/Research_on_Multi-dimensional_Poset_Series_Problems_PPT.pdf` | Slides English PDF |
| `code/` | Standalone C++ implementations of all algorithms |

### Topics Covered

- **Dilworth's Theorem** — decomposition of a finite poset into chains
- **1D / 2D Poset** — sorting + LIS, BIT-based counting
- **3D Poset** — CDQ divide-and-conquer, segment-tree-of-trees, K-D tree approaches
- **K-Dimensional Poset** — nested CDQ for arbitrary dimensions
- **Block Decomposition** — sqrt-decomposition with bitset optimization
- **Derived Problems** — dynamic inversion counting via 3D poset reduction

### Performance Benchmarks

| n | BIT + BST | SegTree² | SegTree + BIT | **CDQ** | K-D Tree |
|---|-----------|----------|---------------|---------|----------|
| 100 | 4ms | 9ms | 6ms | **5ms** | 4ms |
| 5,000 | 83ms | 69ms | 50ms | **44ms** | 38ms |
| 10,000 | 81ms | 775ms | 360ms | **92ms** | 132ms |
| 50,000 | 428ms | 1.76s | 763ms | **132ms** | 406ms |
| 100,000 | 641ms | 4.28s | 1.09s | **148ms** | 766ms |

CDQ divide-and-conquer is the recommended approach — fastest and shortest implementation (46 lines).

### References

1. Dilworth, R. P. (1950). "A Decomposition Theorem for Partially Ordered Sets." *Annals of Mathematics*, 51(1), 161–166. [JSTOR](https://www.jstor.org/stable/1969589)
2. Chen, Danqi (陈丹琦). "On a Class of Divide-and-Conquer Algorithms from \<Cash\>" — Introduces CDQ divide-and-conquer for multidimensional problems.
3. Zhang, Wentao (张闻涛). "Catch the Penguins." Hangzhou Xuejun High School — 4D poset problem.
4. Luo, Jianqiao (罗剑桥). "On the Application of Block Decomposition in a Class of Data Processing Problems" — Beijing No.18 Middle School.
5. [Partially ordered set — Wikipedia](https://en.wikipedia.org/wiki/Partially_ordered_set)
6. [Dilworth's theorem — Wikipedia](https://en.wikipedia.org/wiki/Dilworth%27s_theorem)
7. [Longest increasing subsequence — Wikipedia](https://en.wikipedia.org/wiki/Longest_increasing_subsequence)

## 中文

### 研究背景

**偏序集**（Partially Ordered Set, Poset）是组合数学与序理论中的核心概念。给定集合 A 和满足自反性、反对称性、传递性的关系 ≤，则 (A, ≤) 构成一个偏序集。偏序集的研究与格理论、图理论以及良拟序理论深度关联。在计算机科学中，偏序集问题体现为 **k 维偏序查询**：在 k 维空间中给定 n 个点，求坐标逐维偏序下的最长链，或统计可比较的点对数量。

这些问题自然地出现在竞赛编程（如"俄罗斯套娃"问题）、数据库查询优化、计算几何和并行计算中。随着维度 k 增大，朴素的 O(n^k) 方法变得不可行，催生了 CDQ 分治、树套树、K-D 树和分块 bitset 加速等高级算法技术。

> **建议阅读中文 PDF 以获得完整图示体验。** 英文翻译版本虽然包含完整的文字翻译，但原始 PDF 中的大量示意图（LIS 分步演示、CDQ 分治流程图、分块可视化、动态逆序对演示等）无法完全还原为文本。

### 目录结构

| 文件                                                         | 说明                           |
| ------------------------------------------------------------ | ------------------------------ |
| `关于多维偏序集系列问题的研究.pdf`                           | 主论文（中文，含完整图示）     |
| `关于多维偏序集系列问题的研究-PPT.pdf`                       | 演示幻灯片（中文，含完整图示） |
| `english/Research_on_Multi-dimensional_Poset_Series_Problems.md` | 论文英文翻译                   |
| `english/Research_on_Multi-dimensional_Poset_Series_Problems.pdf` | 论文英文 PDF                   |
| `english/Research_on_Multi-dimensional_Poset_Series_Problems_PPT.md` | 幻灯片英文翻译                 |
| `english/Research_on_Multi-dimensional_Poset_Series_Problems_PPT.pdf` | 幻灯片英文 PDF                 |
| `code/`                                                      | 所有算法的独立 C++ 实现        |

### 涵盖主题

- **Dilworth 定理** — 有限偏序集的链分解
- **1D / 2D 偏序集** — 排序 + LIS、树状数组计数
- **3D 偏序集** — CDQ 分治、线段树套线段树、K-D 树
- **K 维偏序集** — 嵌套 CDQ 分治处理任意维度
- **分块思想** — sqrt 分解 + bitset 优化
- **衍生问题** — 动态逆序对的 3D 偏序集归约

### 性能对比

| n       | 树状数组+平衡树 | 线段树+线段树 | 线段树+树状数组 | **CDQ 分治** | K-D 树 |
| ------- | --------------- | ------------- | --------------- | ------------ | ------ |
| 100     | 4ms             | 9ms           | 6ms             | **5ms**      | 4ms    |
| 5,000   | 83ms            | 69ms          | 50ms            | **44ms**     | 38ms   |
| 10,000  | 81ms            | 775ms         | 360ms           | **92ms**     | 132ms  |
| 50,000  | 428ms           | 1.76s         | 763ms           | **132ms**    | 406ms  |
| 100,000 | 641ms           | 4.28s         | 1.09s           | **148ms**    | 766ms  |

CDQ 分治是首选方案 — 最快且代码最短（46 行）。

### 参考文献

1. Dilworth, R. P. (1950). "A Decomposition Theorem for Partially Ordered Sets." *Annals of Mathematics*, 51(1), 161–166.
2. 陈丹琦.《从\<Cash\>谈一类分治算法的应用》 — CDQ 分治的引入。
3. 张闻涛. "Catch the Pickets." 杭州学军中学 — 4 维偏序问题。
4. 罗剑桥.《浅谈分块思想在一类数据处理问题中的应用》— 北京市第18中学。
5. [偏序集 — Wikipedia](https://en.wikipedia.org/wiki/Partially_ordered_set)
6. [Dilworth 定理 — Wikipedia](https://en.wikipedia.org/wiki/Dilworth%27s_theorem)
7. [最长递增子序列 — Wikipedia](https://en.wikipedia.org/wiki/Longest_increasing_subsequence)
