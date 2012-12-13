; Y-Combinator
(define (Y g)
  (let ((x (lambda (x) (g (x x)))))
    (g (x x))))

; g
(define (g f n)
  (if (= n 0)
      1
      (* n (f (- n 1)))))
