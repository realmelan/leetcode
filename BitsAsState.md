use bit to represent existance of some entity, and an integer is a state. The DP algorithm goes like
```
for i in 0 to (1<<n):
  for entity in entities:
    if allowed to update state i:
      new_state = i | <bit by entity>
      dp[new_state] = dp[i] + entity

``` 

Here is a sample code problem:
* https://leetcode.com/problems/smallest-sufficient-team/

