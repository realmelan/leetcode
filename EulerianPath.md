Eulerian Path is a path that visits every edge of a connected graph.
Similarly an Eulerian cycle is an Eulerian path that goes to the starting vertex.

The way to find Eulerian path is through DFS:
```
def dfs(graph, u, res):
  for v in graph[u]:
    remove u->v from graph
    res.add(v)
    dfs(graph, v)

```

De Bruijn sequence can also be found using this way.

# Problems
* https://leetcode.com/problems/cracking-the-safe/

# Ref
* https://en.wikipedia.org/wiki/Eulerian_path
