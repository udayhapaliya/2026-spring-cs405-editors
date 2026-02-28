# Editorial: Farthest-in-Future Caching

## Introduction
Caching in computer system helps store small amounts of data in a fast memory  which helps in easy and fast access of data.

If the requested data is present in the cache it is called cache hit.

If the requested data is not present in the cache it is called cache miss.

When a cache miss occurs and the cache is full, an existing item must be evicted to make room for the new data.
## The Problem 
Suppose we have a cache $C$ which hold exactly k items.

$D = d_1, d_2, \dots, d_n$ are a sequence of memory references given to us.

- If $d_i\$ is already present in the cache it is a cache hit.
- If $d_i\$ is not present in the cache it is a cache miss and  $d_i\$ must be brought into cache .
- If cache is full and $d_i\$ is not present in the cache we will need to evict some other piece of data already present in the cache to make room for $d_i\$ .

**To Find:** The sequence of evictions that incurs as few cache misses as possible.

## The Intuition
We have a cache which holds 3 items= ${A,B,C}$

Suppose our cache is full and we must choose an item to evict:
- Item $A$ will be requested again in 2 steps.
- Item $B$ will be requested again in 10 steps.
- Item $C$ will never be requested again.

Evicting $A$ would be a bad choice as we would need it again after 2 steps.
Evicting $B$ would be better choice but not the best as we would need it again after 10 steps.
Evicting $C$ would be the best choice as it will need be never requested again.

When $d_i$ needs to be brought into the cache, evict the item that is needed the farthest into the future.We call this the **Farthest-in-Future Algorithm**.

## Pseudocode

```text
Algorithm Farthest-in-Future(k, D, n)
    Initialize an empty cache C
    miss_count ← 0

    For i = 1 to n:
        current_req ← D[i]
        
        If current_req is not in C:
            miss_count ← miss_count + 1
            
            If size of C < k:
                Add current_req to C
                
            Else:
                farthest_item ← null
                max_distance ← 0
                
                // Find the item to evict
                For each item e in C:
                    distance ← index of next appearance of e in D after step i
                    
                    If e never appears again:
                        distance ← infinity
                        
                    If distance > max_distance:
                        max_distance ← distance
                        farthest_item ← e
                
                Remove farthest_item from C
                Add current_req to C

    Return miss_count
```
## Proof of Optimality

As outlined in Kleinberg and Tardos, Farthest-in-Future is an optimal offline algorithm. We prove this using an exchange argument.

### The Exchange Argument

Let $S_{FF}$ be the schedule produced by Farthest-in-Future.
Let $S^*$ be an optimal schedule.

If the schedules are the same, $S_{FF}$ is optimal. If not, let step $i$ be the first step in which they differ in the evictions made during a cache miss:
- $S_{FF}$ swaps item $e$ (the item whose next request is farthest in the future).
- $S^*$ swaps item $f$.

We will build a new schedule, called $S'$.
At step $i$, $S'$ will swap $e$ (as $S_{FF}$ does) instead of $f$.

Just after step $i$, the caches of $S^*$ and $S'$ are almost the same, differing in only one item:
- $S^*$ has $e$ but not $f$.
- $S'$ has $f$ but not $e$.

For all remaining steps $j > i$, $S'$ will merely imitate the evictions of $S^*$ until the caches naturally return to being 100% identical.

Let's analyze the future request sequence to determine when this happens and how it impacts the number of misses:

**Case 1: $S^*$ evicts $e$ before either $e$ or $f$ is requested**
- $S^*$ finally decides to evict $e$.
- At this very same instant, $S'$ (which did not have $e$ to begin with) decides to evict $f$.
- The caches are now perfectly synchronized again. $S'$ had no additional misses over $S^*$.

**Case 2: The sequence requests $f$ before $e$**
- When $f$ is requested, $S^*$ gets a cache miss since it previously evicted $f$ at step $i$.
- But $S'$ still has $f$ in its cache. $S'$ gets a cache hit!
- To synchronize the caches, $S'$ can now freely evict $e$ to conform to whatever the state of $S^*$ is forced into.
- In this case, $S'$ actually had fewer misses than the optimal strategy $S^*$.

**Case 3: The sequence requests $e$ before $f$**
- This is simply a mathematical impossibility.
- By definition of our greedy algorithm, $S_{FF}$ previously decided to evict $e$ at step $i$ because its next request came along strictly later than $f$. Hence, $f$ must be requested before $e$.
  
### Conclusion

In all valid cases, we have successfully constructed a schedule $S'$ that matches the Farthest-in-Future optimal choice for an additional step, and ensured that:
$$\text{Misses}(S') \le \text{Misses}(S^*)$$

By applying this exchange step at all points where the two schedules differ, we can fully convert the optimal schedule $S^*$ into $S_{FF}$. This means that $S_{FF}$ is also an optimal schedule.



## Caching Strategies in Modern CPUs

### 1. Least Recently Used (LRU)

When the cache fills up, the Least Recently Used (LRU) cache eviction algorithm, which is widely used, removes the items that have been accessed the least recently first. It works on the idea that data that has recently been accessed is probably going to be accessed again soon. A hash map and a doubly linked list are frequently used in its implementation.

### 2. Pseudo-LRU (PLRU)

A popular and effective approximation of actual LRU. Instead of keeping an ideal, ordered list of items, it tracks usage using tree-based bits or a "Clock" algorithm (a bit per cache line).

### 3.RRIP (Re-Reference Interval Prediction)

RRIP, a more recent version of LRU, expects when a line will be used again, managing "streaming" data that could otherwise damage the cache and remove frequently used, helpful items.

---
## Related Problems

LeetCode:

- LRU Cache : 
  https://leetcode.com/problems/lru-cache/

- LFU Cache :
  https://leetcode.com/problems/lfu-cache/

- Design Browser History (stack-like recency behavior) :
  https://leetcode.com/problems/design-browser-history/

- Cache With Time Limit :
  https://leetcode.com/problems/cache-with-time-limit/

Codeforces:

- Little Elephant and Array (cache-style simulation flavor) :
  https://codeforces.com/problemset/problem/220/B

- Valera and Queries (offline processing idea — useful for understanding future knowledge tricks) :
  https://codeforces.com/problemset/problem/369/E
---
