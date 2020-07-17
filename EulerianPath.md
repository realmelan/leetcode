Eulerian Path is a path that visits every edge of a connected graph.
Similarly an Eulerian cycle is an Eulerian path that goes to the starting vertex.

The way to find Eulerian path is through DFS:
```
def dfs(graph, u, res):
  while (graph[u].size()):
    v = first node in graph[u]
    remove u->v from graph
    dfs(graph, v)
  res.add(v)
 
dfs(graph, u, res)
reverse(res)

```
Note, the while loop may run just once(no end branch) or twice(one for a circle, one for end branch).

De Bruijn sequence can also be found using this way.

# Problems
* https://leetcode.com/problems/cracking-the-safe/
* https://leetcode.com/problems/reconstruct-itinerary/

# Ref
* https://en.wikipedia.org/wiki/Eulerian_path
