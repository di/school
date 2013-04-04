;
; Define boolean constants as functions
;

(define true (lambda (x y) x))
;Value: true

(define false (lambda (x y) y))
;Value: false

;
; Define the and, or, and not functions using the lambda calculus
;

(define and (lambda (p q) (p q false)))
;Value: and

(define or (lambda (p q) (p true q)))
;Value: or

(define not (lambda (p) (p false true)))
;Value: not

;
; Show that the correct result is obtained for all combinations of the inputs.
;

; Here `and' evaluates `true' with `true' and `false' as parameters.
; `true' returns the first parameter, the result is `true' => #t
((and true true) #t #f)
;Value: #t

; Here `and' evaluates `true' with `false' and `false' as parameters.
; `true' returns the first parameter, the result is `false' => #f 
((and true false) #t #f)
;Value: #f

; Here `and' evaluates `false' with `true' and `false' as parameters.
; `false' returns the second parameter, the result is `false' => #f 
((and false true) #t #f)
;Value: #f

; Here `and' evaluates `false' with `false' and `false' as parameters.
; `false' returns the second parameter, the result is `false' => #f 
((and false false) #t #f)
;Value: #f

; Here `or' evaluates `false' with `true' and `false' as parameters.
; `false' returns the second parameter, the result is `false' => #f 
((or false false) #t #f)
;Value: #f

; Here `or' evaluates `false' with `true' and `true' as parameters.
; `false' returns the second parameter, the result is `true' => #t 
((or false true) #t #f)
;Value: #t

; Here `or' evaluates `true' with `true' and `false' as parameters.
; `true' returns the first parameter, the result is `true' => #t 
((or true false) #t #f)
;Value: #t

; Here `or' evaluates `true' with `true' and `true' as parameters.
; `true' returns the first parameter, the result is `true' => #t 
((or true true) #t #f)
;Value: #t

; Here `not' evaluates `true' with `false' and `true' as parameters.
; `true' returns the first parapeter, the result is `false' => #f 
((not true) #t #f)
;Value: #f

; Here `not' evaluates `false' with `false' and `true' as parameters.
; `false' returns the first parapeter, the result is `true' => #t 
((not false) #t #f)
;Value: #t
