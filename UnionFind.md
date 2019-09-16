group grid nodes based on their connectivity in the grid. This would give # of nodes in each group.
```
for i in 0...row:
  for j in 0...col:
    for dir in dirs (4 or 8 adjacent):
      ni = i + dir[0]
      nj = j + dir[1]
      if 0 <= ni < row && 0 <= nj < col:
        pid = find(id(i,j), p)
        npid = find(id(ni,nj), p)
        if pid < npid:
          p[npid] = pid
          // other merge actions
        else if npid < pid:
          p[pid] = npid
          // other merge actions

function find(i, j, p):
  pid = p(id(i,j))
  if pid != id(i,j):
    pid = find(pid,p)
  return pid

```

# Ref
* https://en.wikipedia.org/wiki/Disjoint_sets

# prolems:
