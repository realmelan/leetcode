Longest proper prefix is also a suffix of str s[0..i], and the two don't overlap, that is s[0,k] = s\[i-k,i\](k!=i).
longest proper prefix is used in KMP search, by skipping the length of the longest proper prefix of pattern that last matches text.

```c++
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
            } else { // s[i] != s[k]
                if (i > 0) {
                    // move i back to next possible position and continue comparison
                    // i might become 0.
                    i = res[i-1];
                } else { // i=0 && s[i] != s[k]
                    // this happens after i becomes 0 and still s[i] != s[k]
                    res[k] = 0;
                    ++k;
                }
            }
        }
        return res;
    }
```

Here is how to search pattern inside text using longest proper prefix table
```c++
    void kmp_search(std::string& text, const std::string& pattern) {
        int nt = text.size();
        int np = pattern.size();
        vector<int> lps = build_lps(pattern);
        int i = 0;
        int j = 0;
        while (i < nt) {
            if (text[i] == pattern[j]) {
                ++i;
                ++j;
            }
            if (j == np) { // pattern found
                cout << "pattern found at " << i-j+1 << endl;
                j = lps[j-1];
            } else if (i < nt && pattern[j] != text[i]) { // update j when there is a mismatch.
                if (j > 0) {
                    j = lps[j-1];
                } else {
                    ++i;
                }
            }
        }
    }
```

# Ref
* https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
