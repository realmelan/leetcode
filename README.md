New Algorithms learned:

Next Permutation from Knuth:
    Starting from the last digit, find a digit which is smaller than the one on its right, named p; find another one digit from the last digit which is larger than the p, swap them; Now reverse the all digits after position p.
    
Gray code: consecutive codes differ in only one bit

Le Bruijn sequence: given (n, k), generate a string of digits which covers all n-lenght k-digit sequence.
    Generate a list of necklace (which is the largest among all rotations), and reduce them to their simplest form (A^p to A)

Fenwick Tree:
    To get sums of any range in O(logn) and update the data structure also in O(logn), Fenwich tree(or Binary Indexed Tree) will help. see https://en.wikipedia.org/wiki/Fenwick_tree


