define len proc(l)
     if null?(l) then
          return := 0
     else
          l := cdr(l);
          return := 1 + lenrec(l)
     fi
end
