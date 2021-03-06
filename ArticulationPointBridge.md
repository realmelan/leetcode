# Articulation Point
Articulation Point or cut vertex is a node in a graph whose removal would result in more connected components of the graph.
see https://en.wikipedia.org/wiki/Biconnected_component

The articulation point of a graph can be found using Tarjan's algorithm, which is a DFS search with two additional info:
* depth, the depth in DFS stack, or discovery time
* low point, the depth value of the topmost ancestor that a node u and its subtree can go back to (via a back edge)

A node u can be an articulation point if and only if:
* there is a node in the subtree rooted at u whose low point value is larger than u's depth.
* it is root node of DFS tree and it has more than one child. Here a child means DFS tree child. If the root has >=2 connected node, but only one DFS tree child(not visited by its decendants), then it is not a cut vertex.

![low point](https://media.geeksforgeeks.org/wp-content/cdn-uploads/20190702123438/TarjansAlgorithms.png "low point value")

```
GetArticulationPoints(i, d)
    visited[i] = true
    depth[i] = d
    low[i] = d
    childCount = 0
    isArticulation = false
    for each ni in adj[i]
        if not visited[ni]
            parent[ni] = i
            GetArticulationPoints(ni, d + 1)
            childCount = childCount + 1
            if low[ni] >= depth[i]
                isArticulation = true
            low[i] = Min(low[i], low[ni])
        else if ni != parent[i]
            low[i] = Min(low[i], depth[ni])
    // here childCount => # of subgraph 
    if (parent[i] != null and isArticulation) or (parent[i] == null and childCount > 1)
        Output i as articulation point
```

# Bridge
A bridge is an edge, removing which would result in more connected component. It is very similar to articulation point.

A bridge can be found using similar algorithm as the above articulation point algorithm. The only difference is that,
for edge u->v, only when low point of (v) is strictly larger than depth(or discovery time) of u, then u->v is a bridge.
The condition means that, if after entering subtree rooted at v, there is no back edge to u or u's ancestors, then u->v
is a bridge.

```
GetBridges(i, d)
    visited[i] = true
    depth[i] = d
    low[i] = d
    childCount = 0
    isArticulation = false
    for each ni in adj[i]
        if not visited[ni]
            parent[ni] = i
            GetBridges(ni, d + 1)
            childCount = childCount + 1
            if low[ni] > depth[i]
                isBridge(u,v) = true
            low[i] = Min(low[i], low[ni])
        else if ni != parent[i]
            low[i] = Min(low[i], depth[ni])
```


# problems
* https://leetcode.com/problems/critical-connections-in-a-network/

# Ref
* https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
* https://www.hackerearth.com/practice/algorithms/graphs/articulation-points-and-bridges/tutorial/
* https://www.hackerearth.com/practice/notes/nj/ (this one is interesting!)
