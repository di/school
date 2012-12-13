(define (be exp env)
  (cond ((boolean? exp) exp)
        ((symbol? exp) (sym exp env))
        ((m? exp 'and 3) (and (be (cadr exp) env) (be (caddr exp) env)))
        ((m? exp 'or 3) (or (be (cadr exp) env) (be (caddr exp) env)))
        ((m? exp 'not 2) (not (be (cadr exp) env)))
        ((m? exp 'implies 3) (be (list 'or (list 'not (cadr exp)) (caddr exp)) env))
        ((m? exp 'equiv 3)
         (be
          (list 'and
                (list 'implies (cadr exp) (caddr exp))
                (list 'implies (caddr exp) (cadr exp)))
          env))
        ((> (length exp) 3)
         (be (list (car exp) (cadr exp) (be (cons (car exp) (cddr exp)) env)) env))
        (else (error "Error"))))

(define (m? exp op n)
  (and (pair? exp)
       (eq? (car exp) op)
       (= (length exp) n)))

(define (sym exp env)
  (cond ((null? env) (error "Error"))
        ((eq? exp (caar env)) (cadar env))
        (else (sym exp (cdr env)))))

(define (union a b)
  (if (null? a)
      b
      (union (cdr a) (if (memq (car a) b) b (cons (car a) b)))))

(define (comb bool vars)
  (map (lambda (env) (cons (list (car vars) bool) env)) (bind (cdr vars))))

(define (bind vars)
  (if (null? vars)
      '(())
      (append (comb #t vars) (comb #f vars))))

(define (bv exp)
  (cond ((boolean? exp) '())
        ((symbol? exp) (list exp))
        ((or (m? exp 'and (length exp))
             (m? exp 'or (length exp)))
         (reduce union '() (map bv (cdr exp))))
        ((m? exp 'not 2) (bv (cadr exp)))
        ((or (m? exp 'implies 3)
             (m? exp 'equiv 3))
         (union (bv (cadr exp)) (bv (caddr exp))))
        (else (error "Error"))))

(define (prove? exp)
  (every (lambda (b) (eq? b #t)) (map (lambda (env) (be exp env)) (bind (bv exp)))))
