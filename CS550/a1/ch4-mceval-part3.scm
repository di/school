;;;;METACIRCULAR EVALUATOR FROM CHAPTER 4 (SECTIONS 4.1.1-4.1.4) of
;;;; STRUCTURE AND INTERPRETATION OF COMPUTER PROGRAMS

;;;;Matches code in ch4.scm

;;;;This file can be loaded into Scheme as a whole.
;;;;Then you can initialize and start the evaluator by evaluating
;;;; the two commented-out lines at the end of the file (setting up the
;;;; global environment and starting the driver loop).

;;;;**WARNING: Don't load this file twice (or you'll lose the primitives
;;;;  interface, due to renamings of apply).

;;;from section 4.1.4 -- must precede def of metacircular apply
(define apply-in-underlying-scheme apply)

;;;SECTION 4.1.1

(define (eval exp env)
  (display (list 'eval exp))
  (display "\n")
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((lambda? exp)
         (make-procedure (lambda-parameters exp)
                         (lambda-body exp)
                         env))
        ((begin? exp) 
         (eval-sequence (begin-actions exp) env))
        ((cond? exp) (eval (cond->if exp) env))
        ((application? exp)
         (apply (eval (operator exp) env)
                (list-of-values (operands exp) env)))
        (else
         (error "Unknown expression type -- EVAL" exp))))

(define (apply procedure arguments)
  (display (list 'apply arguments))
  (display "\n")
  (cond ((primitive-procedure? procedure)
         (apply-primitive-procedure procedure arguments))
        ((compound-procedure? procedure)
         (eval-sequence
           (procedure-body procedure)
           (extend-environment
             (procedure-parameters procedure)
             arguments
             (procedure-environment procedure))))
        (else
         (error
          "Unknown procedure type -- APPLY" procedure))))


(define (list-of-values exps env)
  (display (list 'list-of-values exps))
  (display "\n")
  (if (no-operands? exps)
      '()
      (cons (eval (first-operand exps) env)
            (list-of-values (rest-operands exps) env))))

(define (eval-if exp env)
  (display (list 'eval-if exp))
  (display "\n")
  (if (true? (eval (if-predicate exp) env))
      (eval (if-consequent exp) env)
      (eval (if-alternative exp) env)))

(define (eval-sequence exps env)
  (display (list 'eval-sequence exps))
  (display "\n")
  (cond ((last-exp? exps) (eval (first-exp exps) env))
        (else (eval (first-exp exps) env)
              (eval-sequence (rest-exps exps) env))))

(define (eval-assignment exp env)
  (display (list 'eval-assignment exp))
  (display "\n")
  (set-variable-value! (assignment-variable exp)
                       (eval (assignment-value exp) env)
                       env)
  'ok)

(define (eval-definition exp env)
  (display (list 'eval-definition exp))
  (display "\n")
  (define-variable! (definition-variable exp)
                    (eval (definition-value exp) env)
                    env)
  'ok)

;;;SECTION 4.1.2

(define (self-evaluating? exp)
  (display (list 'self-evaluating exp))
  (display "\n")
  (cond ((number? exp) true)
        ((string? exp) true)
        (else false)))

(define (quoted? exp)
  (display (list 'quoted exp))
  (display "\n")
  (tagged-list? exp 'quote))

(define (text-of-quotation exp) 
  (display (list 'text-of-quotation exp))
  (display "\n")
  (cadr exp))

(define (tagged-list? exp tag)
; Too much output to trace
  (if (pair? exp)
      (eq? (car exp) tag)
      false))

(define (variable? exp)
  (display (list 'variable exp))
  (display "\n")
  (symbol? exp))

(define (assignment? exp)
  (display (list 'assignment? exp))
  (display "\n")
  (tagged-list? exp 'set!))

(define (assignment-variable exp)
  (display (list 'assignment-variable exp))
  (display "\n")
  (cadr exp))

(define (assignment-value exp)
  (display (list 'assignment-value exp))
  (display "\n")
  (caddr exp))

(define (definition? exp)
  (display (list 'definition? exp))
  (display "\n")
  (tagged-list? exp 'define))

(define (definition-variable exp)
  (display (list 'definition-variable exp))
  (display "\n")
  (if (symbol? (cadr exp))
      (cadr exp)
      (caadr exp)))

(define (definition-value exp)
  (display (list 'definition-value exp))
  (display "\n")
  (if (symbol? (cadr exp))
      (caddr exp)
      (make-lambda (cdadr exp)
                   (cddr exp))))

(define (lambda? exp)
  (display (list 'lambda? exp))
  (display "\n")
  (tagged-list? exp 'lambda))

(define (lambda-parameters exp)
  (display (list 'lambda-parameters exp))
  (display "\n")
  (cadr exp))

(define (lambda-body exp)
  (display (list 'lambda-body exp))
  (display "\n")
  (cddr exp))

(define (make-lambda parameters body)
  (display (list 'make-lambda parameters body))
  (display "\n")
  (cons 'lambda (cons parameters body)))

(define (if? exp)
  (display (list 'if? exp))
  (display "\n")
  (tagged-list? exp 'if))

(define (if-predicate exp)
  (display (list 'if-predicate exp))
  (display "\n")
  (cadr exp))

(define (if-consequent exp)
  (display (list 'if-consequent exp))
  (display "\n")
  (caddr exp))

(define (if-alternative exp)
  (display (list 'if-alternative exp))
  (display "\n")
  (if (not (null? (cdddr exp)))
      (cadddr exp)
      'false))

(define (make-if predicate consequent alternative)
  (display (list 'make-if predicate consequent alernative))
  (display "\n")
  (list 'if predicate consequent alternative))

(define (begin? exp)
  (display (list 'begin? exp))
  (display "\n")
(tagged-list? exp 'begin))

(define (begin-actions exp)
  (display (list 'begin-actions exp))
  (display "\n")
  (cdr exp))

(define (last-exp? seq)
  (display (list 'last-exp? seq))
  (display "\n")
  (null? (cdr seq)))

(define (first-exp seq)
  (display (list 'first-exp seq))
  (display "\n")
  (car seq))

(define (rest-exps seq)
  (display (list 'rest-exps seq))
  (display "\n")
  (cdr seq))

(define (sequence->exp seq)
  (cond ((null? seq) seq)
        ((last-exp? seq) (first-exp seq))
        (else (make-begin seq))))

(define (make-begin seq)
  (display (list 'make-begin seq))
  (display "\n")
  (cons 'begin seq))

(define (application? exp)
  (display (list 'application? exp))
  (display "\n")
(pair? exp))

(define (operator exp)
  (display (list 'operator exp))
  (display "\n")
(car exp))

(define (operands exp)
  (display (list 'operator exp))
  (display "\n")
(cdr exp))

(define (no-operands? ops)
(null? ops))

(define (first-operand ops)
(car ops))

(define (rest-operands ops)
(cdr ops))

(define (cond? exp) (tagged-list? exp 'cond))

(define (cond-clauses exp) (cdr exp))

(define (cond-else-clause? clause)
  (eq? (cond-predicate clause) 'else))

(define (cond-predicate clause) (car clause))

(define (cond-actions clause) (cdr clause))

(define (cond->if exp)
  (expand-clauses (cond-clauses exp)))

(define (expand-clauses clauses)
  (if (null? clauses)
      'false                          ; no else clause
      (let ((first (car clauses))
            (rest (cdr clauses)))
        (if (cond-else-clause? first)
            (if (null? rest)
                (sequence->exp (cond-actions first))
                (error "ELSE clause isn't last -- COND->IF"
                       clauses))
            (make-if (cond-predicate first)
                     (sequence->exp (cond-actions first))
                     (expand-clauses rest))))))

;;;SECTION 4.1.3

(define (true? x)
  (display (list 'true? x))
  (display "\n")
  (not (eq? x false)))

(define (false? x)
  (display (list 'false? x))
  (display "\n")
  (eq? x false))

(define (make-procedure parameters body env)
  (list 'procedure parameters body env))

(define (compound-procedure? p)
  (tagged-list? p 'procedure))


(define (procedure-parameters p) (cadr p))
(define (procedure-body p) (caddr p))
(define (procedure-environment p) (cadddr p))


(define (enclosing-environment env) (cdr env))

(define (first-frame env) (car env))

(define the-empty-environment '())

(define (make-frame variables values)
  (cons variables values))

(define (frame-variables frame) (car frame))
(define (frame-values frame) (cdr frame))

(define (add-binding-to-frame! var val frame)
  (set-car! frame (cons var (car frame)))
  (set-cdr! frame (cons val (cdr frame))))

(define (extend-environment vars vals base-env)
  (if (= (length vars) (length vals))
      (cons (make-frame vars vals) base-env)
      (if (< (length vars) (length vals))
          (error "Too many arguments supplied" vars vals)
          (error "Too few arguments supplied" vars vals))))

(define (lookup-variable-value var env)
  (define (env-loop env)
    (define (scan vars vals)
      (cond ((null? vars)
             (env-loop (enclosing-environment env)))
            ((eq? var (car vars))
             (car vals))
            (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
        (error "Unbound variable" var)
        (let ((frame (first-frame env)))
          (scan (frame-variables frame)
                (frame-values frame)))))
  (env-loop env))

(define (set-variable-value! var val env)
  (define (env-loop env)
    (define (scan vars vals)
      (cond ((null? vars)
             (env-loop (enclosing-environment env)))
            ((eq? var (car vars))
             (set-car! vals val))
            (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
        (error "Unbound variable -- SET!" var)
        (let ((frame (first-frame env)))
          (scan (frame-variables frame)
                (frame-values frame)))))
  (env-loop env))

(define (define-variable! var val env)
  (let ((frame (first-frame env)))
    (define (scan vars vals)
      (cond ((null? vars)
             (add-binding-to-frame! var val frame))
            ((eq? var (car vars))
             (set-car! vals val))
            (else (scan (cdr vars) (cdr vals)))))
    (scan (frame-variables frame)
          (frame-values frame))))

;;;SECTION 4.1.4

(define (setup-environment)
  (let ((initial-env
         (extend-environment (primitive-procedure-names)
                             (primitive-procedure-objects)
                             the-empty-environment)))
    (define-variable! 'true true initial-env)
    (define-variable! 'false false initial-env)
    initial-env))

;[do later] (define the-global-environment (setup-environment))

(define (primitive-procedure? proc)
  (tagged-list? proc 'primitive))

(define (primitive-implementation proc) (cadr proc))

(define primitive-procedures
  (list (list 'car car)
        (list 'cdr cdr)
        (list 'cons cons)
        (list 'null? null?)
        (list '- -)
        (list '* *)
        (list '= =)
;;      more primitives
        ))

(define (primitive-procedure-names)
  (map car
       primitive-procedures))

(define (primitive-procedure-objects)
  (map (lambda (proc) (list 'primitive (cadr proc)))
       primitive-procedures))

;[moved to start of file] (define apply-in-underlying-scheme apply)

(define (apply-primitive-procedure proc args)
  (apply-in-underlying-scheme
   (primitive-implementation proc) args))



(define input-prompt ";;; M-Eval input:")
(define output-prompt ";;; M-Eval value:")

(define (driver-loop)
  (prompt-for-input input-prompt)
  (let ((input (read)))
    (let ((output (eval input the-global-environment)))
      (announce-output output-prompt)
      (user-print output)))
  (driver-loop))

(define (prompt-for-input string)
  (newline) (newline) (display string) (newline))

(define (announce-output string)
  (newline) (display string) (newline))

(define (user-print object)
  (if (compound-procedure? object)
      (display (list 'compound-procedure
                     (procedure-parameters object)
                     (procedure-body object)
                     '<procedure-env>))
      (display object)))

;;;Following are commented out so as not to be evaluated when
;;; the file is loaded.
(define the-global-environment (setup-environment))
(trace eval)
(trace apply)
(driver-loop)

'METACIRCULAR-EVALUATOR-LOADED
