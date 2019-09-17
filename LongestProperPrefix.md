Longest proper prefix is also a suffix of str s[0..i], and the two don't overlap, that is s[0,k] = s\[i-k,i\](k!=i).
longest proper prefix is used in KMP search, by skipping the length of the longest proper prefix of pattern that last matches text.

```
    vector<int> build_lps(string s) {
        int n = s.size();
        vector<int> res(n, 0);
        res[0] = 0;
        int i = 0;
        int k = 1;
        while (k < n) {
            if (s[i] == s[k]) {
                ++i;
                res[k] = i;
                ++k;
            } else {
                res[k] = 0;
                while (i > 0 && s[i] != s[k]) {
                    i = res[i-1];
                }
                if (i > 0 || s[0] == s[k]) {
                    res[k] = ++i;
                }
                ++k;
            }
        }
        return res;
    }
```

# Ref
* https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
