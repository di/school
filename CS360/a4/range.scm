(define (range l)
  (if (> (car l) (caddr l)) '()
    (cons 
      (car l) 
      (range (list (+ (car l) (cadr l)) (cadr l) (caddr l)))
    )
  )
)
