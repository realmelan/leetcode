# Suffix Array
Suffix array can be used to find longest common substring of a string.
* https://en.wikipedia.org/wiki/Suffix_array
* https://en.wikipedia.org/wiki/LCP_array
* http://web.stanford.edu/class/cs97si/suffix-array.pdf

## How to efficiently build suffix array

Below code is from http://web.stanford.edu/class/cs97si/suffix-array.pdf, which is O(n\*lgn\*lgn). The idea is that, the suffix array elements are all substring of the same string. If the rank of the first 2^k characters of a suffix, say *a*, is known, then the rank of the first 2^(k+1) can also be computed, as the second half of the 2^(k+1) characters is also the first half 2^k characters of another suffix, *b*.
```c
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN 65536
#define MAXLG 17
char A[MAXN];
struct entry {
    int nr[2], p;
} L[MAXN];
int P[MAXLG][MAXN], N, i, stp, cnt;
int cmp(struct entry a, struct entry b)
{
    return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1] ? 1 : 0) : (a.nr[0] < b.nr[0] ? 1 : 0);
}
int main(void)
{
    gets(A);
    for (N = strlen(A), i = 0; i < N; i ++)
        P[0][i] = A[i] - 'a';
    for (stp = 1, cnt = 1; cnt >> 1 < N; stp ++, cnt <<= 1)
    {
        // here, L[i] always stores the i-th suffix(from i'th char to n-1'th)
        // p stores the index of the suffix.
        for (i = 0; i < N; i ++)
        {
            L[i].nr[0] = P[stp - 1][i];
            L[i].nr[1] = i + cnt < N ? P[stp - 1][i + cnt] : -1;
            L[i].p = i;
        }
        sort(L, L + N, cmp);
        // after sort, L[i] no longer stores the i-th suffix, rather the suffix that ranks (lexicographically) the i-th.
        // P[round][i] stores the rank of the i-th suffix.
        for (i = 0; i < N; i ++)
            P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] && L[i].nr[1] == L[i - 1].nr[1] ? P[stp][L[i - 1].p] : i;
    }
    return 0;
}
```

# Longest common prefix of a Suffix Array
## how to efficiently compute LCP from given suffix array
Kasai algorithm: https://www.geeksforgeeks.org/%C2%AD%C2%ADkasais-algorithm-for-construction-of-lcp-array-from-suffix-array/

Problems:
https://leetcode.com/problems/longest-duplicate-substring/
