Articulation Point or cut vertex is a node in a graph whose removal would result in more connected components of the graph.
see https://en.wikipedia.org/wiki/Biconnected_component

The articulation point of a graph can be found using Tarjan's algorithm, which is a DFS search with two additional info:
* depth, the depth in DFS stack
* low point, the depth value of the topmost ancestor that a node u and its subtree can go back to (via a back edge)

A node u can be an articulation point if and only if:
* there is a node in the subtree rooted at u whose low point value is larger than u's depth.


# Ref
https://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/
