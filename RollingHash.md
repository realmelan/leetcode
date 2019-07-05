Rolling hash is to compute hash for a sliding window of a fixed length. It supports efficient hash computation given hash of previous sliding window.
Its computation is based on polynomial form: H = c1 * a^(k-1) + c2 * a^(k-2) + ... + ck * a^0.
Note, H might get too large, so that it should modulo a number, m. m can be 2^63-1, and 

Rolling hash can be used to search all appearance of substrings in a text.

## ref
* https://en.wikipedia.org/wiki/Rolling_hash

## Problems
* https://leetcode.com/problems/longest-duplicate-substring/

## sample code
https://leetcode.com/problems/longest-duplicate-substring/discuss/290871/Python-Binary-Search
```python
def longestDupSubstring(self, S):
        A = [ord(c) - ord('a') for c in S]
        mod = 2**63 - 1

        def test(L):
            p = pow(26, L, mod)
            cur = reduce(lambda x, y: (x * 26 + y) % mod, A[:L], 0)
            seen = {cur}
            for i in xrange(L, len(S)):
                cur = (cur * 26 + A[i] - A[i - L] * p) % mod
                if cur in seen: return i - L + 1
                seen.add(cur)
        res, lo, hi = 0, 0, len(S)
        while lo < hi:
            mi = (lo + hi + 1) / 2
            pos = test(mi)
            if pos:
                lo = mi
                res = pos
            else:
                hi = mi - 1
        return S[res:res + lo]
```
