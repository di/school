;
; Church encodings
;

(define zero 
  (lambda (f)
    (lambda (x) x)))
;Value: zero

(define one
  (lambda (f)
    (lambda (x) (f x))))
;Value: one

(define two
  (lambda (f)
    (lambda (x) (f (f x)))))
;Value: two

(define three 
  (lambda (f)
    (lambda (x) (f (f (f x))))))
;Value: two

(define add1
  (lambda (x) (+ x 1)))
;Value: add1

;
; successor function:  (succ n) => n+1
;

(define succ
  (lambda (n)
    (lambda (f)
      (lambda (x)
    (f ((n f) x))))))
;Value: succ
