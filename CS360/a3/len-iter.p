define len proc(l)
   return := 0;
   while return != -1 do
        if null?(l) then
             return := -1
        else
             return := return + 1
             l := cdr(l);
        fi
   od;
end
