Provided by Donald Knuth, give current text, to find next larger text that contains same characters.

Starting from last position of the text, find a position i where text[i-1] < text[i], 
find from text[i..n-1] a character, text[k] that's just larger than  text[i-1], and swap them. 
then reorder current text[i] and text[i+1..n-1] into increasing order. Because text[i+1..n-1] is already in decreasing order,
it is enough to reverse text[i..n-1].

```c++
bool nextpermutation(string& s) 
{ 
    int n = s.length(), i = n - 2; 
    while (i >= 0 && s[i] >= s[i + 1]) 
        --i; 
    if (i < 0) 
        return false; 
    else { 
        int j = n-1;
        while (j>i && s[j]<=s[i]) {
            --j;
        }
        swap(s[i], s[j]);
        for (j = n-1; i < j; ++i,--j) {
            swap(s[i], s[j]);
        } 
        return true; 
    } 
} 
```
