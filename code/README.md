# Code Examples

All C++ implementations from "Research on Multi-dimensional Partially Ordered Set Series Problems" by manni.

| File | Algorithm | Complexity | Description |
|------|-----------|------------|-------------|
| `01_brute_force_dfs.cpp` | Brute-force DFS | O((n·k)^k) | Exhaustive search with backtracking |
| `02_2d_lis_optimization.cpp` | 2D LIS | O(n log n) | Sort by dim-1, LIS on dim-2 |
| `03_2d_bit_counting.cpp` | 2D BIT counting | O(n log²n) | Count poset pairs using 2D Fenwick tree |
| `04_3d_special_two_values_split.cpp` | 3D split (z∈{1,2}) | O(n log n) | Enumerate split point on 3rd dimension |
| `05_3d_bit_counting_with_if.cpp` | 3D BIT + branch | O(n log²n) | Two-layer BIT with conditional branch on z |
| `06_3d_cdq_divide_conquer.cpp` | CDQ divide-and-conquer | O(n log²n) | **Recommended** — best all-around method |
| `07_kd_block_decomposition_bitset.cpp` | Block + bitset | O(n·k + m·k·√n) | Simple brute-force alternative with bitset |
| `08_dynamic_inversion_cdq.cpp` | Dynamic inversions (CDQ) | O(n log²n) | Reduction to 3D counting problem |
| `09_dynamic_inversion_block.cpp` | Dynamic inversions (block) | O(n√n) | Block decomposition approach |
