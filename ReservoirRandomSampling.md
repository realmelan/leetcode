Return k random element from an array of unknown size or dynamic.

It can be used to return a random element from a linked list, where k=1.

```
(*
  S has items to sample, R will contain the result
 *)
ReservoirSample(S[1..n], R[1..k])
  // fill the reservoir array
  for i = 1 to k
      R[i] := S[i]

  // replace elements with gradually decreasing probability
  for i = k+1 to n
    j := random(1, i)   // important: inclusive range
    if j <= k
      R[j] := S[i]
```

The algorithm creates a "reservoir" array of size k and populates it with the first k items of S. It then iterates through the remaining elements of S until S is exhausted. At the ith element of S, the algorithm generates a random number j between 1 and i. If j is less than or equal to k, the jth element of the reservoir array is replaced with the ith element of S. In effect, for all i, the ith element of S is chosen to be included in the reservoir with probability k/i. Similarly, at each iteration the jth element of the reservoir array is chosen to be replaced with probability 1/k * k/i = 1/i. It can be shown that when the algorithm has finished executing, each item in S has equal probability (i.e., k/length(S)) of being chosen for the reservoir.

To see this, consider the following proof by induction. First, the base case: when i=k, each of the first k elements of S is in the reservoir with probability k/i=k/k=1.

Second, the induction step. We may assume that before round i, each of the first i-1 elements of S is in the reservoir with probability k/(i-1). The probability of any particular element of the reservoir being replaced during round i is 1/i, so the probability of it not being replaced is (i-1)/i. Thus, the odds of any of the first i-1 elements remaining in the reservoir after round i is k/(i-1) *  (i-1)/i=k/i, as desired.

Finally, during round i, the ith element is added to the reservoir with probability k/i. Thus, after round i, each of the first i elements of S is in the reservoir with probability k/i.


#


# Ref
https://en.wikipedia.org/wiki/Reservoir_sampling
