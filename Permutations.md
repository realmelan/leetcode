### Fisher&Yate's algorithm:
```
-- To shuffle an array a of n elements (indices 0..n-1):
  for i from n−1 downto 1 do
     j ← random integer such that 0 ≤ j ≤ i
     exchange a[j] and a[i]
```

### Steihaus-Johnson-Trotter algorithm:
```
  procedure Move( x, d : N);
  local j : N;
  begin
    j := pos[x]; val[j] := val[j + d]; val[j + d] := x;
    pos[x] := j + d; pos[val[j]] := j;
  end of Move;
  
  procedure Perm ( n : N);
  local i : N;
  begin
    if n > N then PrintIt
    else
      Perm( n+1 );
      for i := 1 to n - 1 do
        Move( n, dir[n] ); Perm( n + 1 );
      dir[n] := -dir[n];
    end of Perm;
```

### iterative of SJT algorithm:
```
    procedure Next;
    {Assumes that ¼0 = ¼n+1 = n + 1}
    begin
      m := n;
      while val[pos[m] + d[m]] > m do // Find largest mobile integer
        d[m] := -d[m]; m := m - 1;
      val[pos[m]] :=: val[pos[m] + d[m]]; // update val
      pos[val[pos[m]]] :=: pos[m]; //update pos
    end of Next;
```
