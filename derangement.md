Derangement is to position objects such that every object is not at its original position.

Here is how derangment number is computed for n objects:
f(n) = (n-1)*(f(n-1)+f(n-2))

Say, the 1st object is at position i, now consider object i:

1. object i takes position 1, then there are n-2 objects to derange
1. object i doesn't take position 1, this equals to n-1 objects to derange. There is one position for each object not to take. For object i, the position is 1.

# Ref
* https://en.wikipedia.org/wiki/Derangement
