This algorithm finds out the majority element if there is one. A majority element is the element whose # of appearances exceeds half of total # of elements.

The algorithm goes as below:

```python
candidate = 0
counter = 0
for e in array:
  if counter == 0:
    candidate = e
  else if e == candidate:
    counter += 1
  else:
    counter -= 1

total_counter = len(array)
counter = 0
for e in array:
  if e == candidate:
    counter += 1
if counter > total_counter / 2:
  print "candidate found"
