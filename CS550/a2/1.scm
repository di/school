(define (fv exp)
  (cond ((null? exp) ())
        ((symbol? exp) (list exp))
        ((eq? (car exp) 'lambda) (diff (fv (caddr exp)) (cadr exp)))
        (else (union (fv (car exp)) (fv (cdr exp))))))

(define (union a b)
  (if (null? a)
      b
      (union (cdr a) (if (memq (car a) b) b (cons (car a) b)))))

(define (diff a b)
  (cond ((null? a) '())
        ((memq (car a) b) (diff (cdr a) b))
        (else (cons (car a) (diff (cdr a) b)))))
