# LCS (Longest Common Subsequence)

## Introduction

In class, we discussed how to compute the **length** of the Longest Common Subsequence (LCS) using dynamic programming.

In this editorial, we focus on the **reconstruction phase** of LCS, which is how to retrieve the actual subsequence using the already computed DP table.

## Problem Statement

Given two strings:

- $X = x_1 x_2 \dots x_m$
- $Y = y_1 y_2 \dots y_n$

We first compute the DP table $dp[i][j]$ such that:
- $dp[i][j]$ represents the length of the LCS of the first $i$ characters of $X$ and the first $j$ characters of $Y$.
After filling this table, we want to reconstruct the actual LCS string.

## Key Idea Behind Reconstruction

While filling the DP table, we used the recurrence:

- If $x_i = y_j$:
    - $dp[i][j] = 1 + dp[i-1][j-1]$
- Otherwise:
    - $dp[i][j] = \max(dp[i-1][j], dp[i][j-1])$

The reconstruction process simply **reverses this logic**.

We start from $dp[m][n]$ and trace backwards:
- If characters match, include the character in the LCS and move diagonally.
- If they do not match, move in the direction of the larger value.
This process continues until we reach the first row or first column.

## Pseudocode

```
LCS_Reconstruct(X, Y, dp, m, n):
    i ← m
    j ← n
    result ← empty list

    while i > 0 and j > 0:
        if X[i] == Y[j]:
            append X[i] to result
            i ← i - 1
            j ← j - 1

        else if dp[i-1][j] >= dp[i][j-1]:
            i ← i - 1

        else:
            j ← j - 1

    reverse(result)
    return result
```

## Explanation

1. Start at cell $(m, n)$.
2. If the characters match:
    - That character must be part of the LCS.
    - Move diagonally to $(i-1, j-1)$.
3. If the characters do not match:
    - Compare $dp[i-1][j]$ and $dp[i][j-1]$.
    - Move to the larger one.
4. Stop when either $i = 0$ or $j = 0$.
5. Since characters were collected in reverse order, reverse the result at the end.

## Example

- $X = ABCBDAB$
- $Y = BDCABA$

After filling the DP table, suppose the LCS length is 4.
Backtracking might produce: **BCBA**
Another valid LCS: **BDAB**

## Proof of Correctness

We prove correctness using the structure of the DP recurrence.

### Case 1: Characters Match

If $X[i] = Y[j]$, then by recurrence:

- $dp[i][j] = 1 + dp[i-1][j-1]$

This means:

- The character must be part of an optimal solution.
- Moving diagonally ensures we follow the subproblem that contributed to the optimal answer.

Thus, adding the character is correct.

### Case 2: Characters Do Not Match

If $X[i] \ne Y[j]$, then:
- $dp[i][j] = \max(dp[i-1][j], dp[i][j-1])$

So the optimal solution came from either:
- Removing the last character of $X$, or
- Removing the last character of $Y$.
By moving in the direction of the larger value, we ensure we stay on a path that leads to an optimal LCS.
Thus, at every step, we follow a subproblem that preserves optimality.

### Termination

- The loop stops when either string becomes empty.
- At that point, no further common characters are possible.
- Hence, the constructed string is indeed a longest common subsequence.

## Time Complexity Analysis

### Reconstruction Phase

- At each step, either $i$ decreases or $j$ decreases.
- In the worst case, we move at most $m + n$ steps.
Therefore, reconstruction takes $O(m+n)$ time.

### Total Time Complexity

The DP table construction dominates, so the total time complexity is: $O(mn)$

## Space Complexity Analysis

- DP table requires $O(mn)$ space.
- Result string stores at most $O(\min(m, n))$ characters.
- Thus total space complexity is: $O(mn)$
