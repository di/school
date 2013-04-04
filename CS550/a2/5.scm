(define (reduce exp)
  (if (null? (cdr exp))
      (car exp)
      (reduce (cons (car (sub (cddar exp) (caadar exp) (cadr exp))) (cddr exp)))))

(define (sub f a b)
  (if (null? f)
      '()
      (cons
       (cond ((equal? (car f) a) b)
             ((not (pair? (car f))) (car f))
             (else (sub (car f) a b)))
       (sub (cdr f) a b))))
