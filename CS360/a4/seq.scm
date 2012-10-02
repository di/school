(define (seq f l)
  (if (> (car l) (caddr l)) '()
    (cons 
      (f (car l))
      (seq f (list (+ (car l) (cadr l)) (cadr l) (caddr l)))
    )
  )
)
