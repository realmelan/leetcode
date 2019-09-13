Given a list of intervals in [a, b], find a value c in [a, b], which are covered by most intervals.

This can be solved by counting, which adds 1 when encountering the start point of an interval and minus 1 when encountering the end point of an interval. During counting, update max overlap.

```
map<int, int> cnt;
for (a,b) in intervals:
    ++cnt[a]
    --cnt[b]

res = -1;
max_cnt = INT_MIN;
for p in [a, b]:
    if cnt[p] > max_cnt:
        max_cnt = cnt[p]
        res = p
```
