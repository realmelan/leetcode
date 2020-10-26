# Topological sort

Topological sort can be used to find a progression of elements that meet conditions.

Normally a previously met condition will trigger some dependent elements, such that conditions for some of these elements will be met.
These elements form a DAG(directed acyclic graph).

One use of topological sort is in combinatorial game theory. In combinatorial game theory, there are N(ext)-Positions and P(revious)-Positions. P-Position is previous player win, N-Position is next player (current player) win.
A position is a N-Position as long as one of its following positions is P-Position, i.e. if current player take this move, in next turn he as the previous player is guaranteed to win.
A position is a P-Position only if all its following positions are N-Position, i.e. no matter how current player move, the previous player is guaranteed to win in next turn.

So how do you find the game result for a particular position? We can start from the final states, positions that we know the results.
Then using topological sort, gradually find all N-positions and P-positions.


# Problems:
* https://leetcode.com/problems/cat-and-mouse/discuss/399346/C%2B%2B-solution-with-super-detailed-explanation-(topological-sort)
* https://leetcode.com/problems/trapping-rain-water-ii/
