(define (eval prog)
  (let ((env initial-environment))
       (if (stmtlist? prog)
           (eval-stmtlist prog env)
           (error "illegal program"))))

(define (eval-stmtlist stmtlist env)
  (if (null? stmtlist)
      env
      (eval-stmtlist (cdr stmtlist) (eval-stmt (car stmtlist) env))))  

(define (eval-stmt stmt env)
  (cond
    ((assign-stmt? stmt) (eval-assign stmt env))
    ((if-stmt? stmt) (eval-if stmt env))
    ((while-stmt? stmt) (eval-while stmt env))
    (else (error "illegal statement"))
  )
)

(define (eval-assign stmt env)
  (let ((var (cadr stmt)) (expr (caddr stmt)))
    (insert-binding var (eval-expr expr env) env)))

(define (eval-if stmt env)
  (let ((expr (cadr stmt)) (S1 (caddr stmt)) (S2 (cadddr stmt)))
    (if (> (eval-expr expr env) 0) 
	(eval-stmtlist S1 env)
	(eval-stmtlist S2 env))))

(define (eval-while stmt env)
  (define (loop expr S env)
    (if (<= (eval-expr expr) 0)
        env
        (loop expr (eval-stmtlist S env))))
  (let ((expr (cadr stmt)) (S (caddr stmt)))
    (loop expr S env)))

(define (lookup name alist)
  (cond ((null? alist) '())
	((eq? name (caar alist)) (cadar alist))
	(else (lookup name (cdr alist)))))

(define (get-binding name alist)
  (cond ((null? alist) '())
	((eq? name (caar alist)) (car alist))
	(else (get-binding name (cdr alist)))))

(define (insert-binding name val alist)
  (let ((binding (get-binding name alist)))
    (if (null? binding)
	(cons (list name val) alist)
	(begin (set-car! (cdr binding) val) (env)))))

; predicate to check if exp is a list whose car field is equal to tag
; taken from SICP 
(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      false))

(define (eval-expr expr env)
  (cond ((number? expr) (eval-num expr env))
        ((ident? expr) (eval-ident expr env))
        ((plus? expr) (eval-plus expr env))
        ((minus? expr) (eval-minus expr env))
        ((times? expr) (eval-times expr env))
        (else (error "illegal eval-exprssion"))))

(define (eval-num expr env)
  (expr))

(define (eval-ident expr env)
  (env expr))

(define (eval-plus expr env)
    (let ((expr1 (cadr expr)) (expr2 (caddr expr)))
      (+ ((eval-expr expr1 env)) ((eval-expr expr2 env)))))

(define (eval-minus expr env)
    (let ((expr1 (cadr expr)) (expr2 (caddr expr)))
      (- ((eval-expr expr1 env)) ((eval-expr expr2 env)))))

(define (eval-times expr env)
    (let ((expr1 (cadr expr)) (expr2 (caddr expr)))
      (* ((eval-expr expr1 env)) ((eval-expr expr2 env)))))

(define (stmtlist? l)
  (and (pair? l)
       (stmt? (car l))))

(define initial-environment (lambda (ident)
  'undef))

(define (ident? exp)
  (symbol? exp))

(define (plus? exp)
  (tagged-list? exp '+))

(define (minus? exp)
  (tagged-list? exp '-))

(define (times? exp)
  (tagged-list? exp '*))

(define (assign-stmt? prog)
  (tagged-list? prog 'assign))

(define (if-stmt? prog)
  (tagged-list? prog 'if))

(define (while-stmt? prog)
  (tagged-list? prog 'while))

(define (stmt? s)
  (or (assign-stmt? s)
      (if-stmt? s)
      (while-stmt? s)))


; testing ------------

(define prog
'((assign i 5)
(assign j 0)
(while i 
((assign j (+ j (* i 2)))
(assign i (- i 1))))))
;Value: prog

(eval prog)
