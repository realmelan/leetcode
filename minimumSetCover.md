The problem wants to find minimum number of entities to cover a given entity. For example like the smallest sufficient team problem, it wants to cover a given set of skills with minimum number of people with different set of skills; the stickers problem wants to cover a word of characters with minimum number of stickers of different set of characters.

As long as the entity has small different states, it can use below updating method.

use bit to represent existance of some entity, and an integer is a state. The DP algorithm goes like
```
for i in 0 to (1<<n):
  for entity in entities:
    if allowed to update state i:
      new_state = i | <bit by entity>
      dp[new_state] = dp[i] + entity

``` 

# problems
* https://leetcode.com/problems/smallest-sufficient-team/
* https://leetcode.com/problems/stickers-to-spell-word/

