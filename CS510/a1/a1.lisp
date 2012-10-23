;; 8-puzzle
;; Dustin Ingram
(defun solved? (puzzle)
    (equalp puzzle #2a((1 2 3)(4 5 6)(7 8 9))))

(defun solve-8puzzle (cmd puzzle)
  (let ((visited '()) (queue (list (list puzzle '()))))
    (loop while (not (null queue)) do
      (let* ((cur (pop queue)) (board (car cur)) (moves (cadr cur)))
        (push board visited)
        (if (solved? board) (return moves)
          (mapcar #'(lambda (x) 
            (if (not (member (move board x) visited :test 'equalp))
              (insert (list (move board x) (append moves (list x))) queue cmd)))
            (valid-moves board)))))))
 
(defmacro insert (e l cmd)
  `(case cmd
    ((BFS) (setf ,l (append ,l (list ,e))))
    ((DFS) (push ,e ,l))
    ((A*) (setf ,l (append ,l (list (append ,e (list (manhattan ,e))))))
          (sort ,l #'(lambda (a b) (<= (third a) (third b)))))))

(defun manhattan (e)
  (let ((r (length (cadr e))) (board (car e)))
    (loop for row from 0 to 2 do
      (loop for col from 0 to 2 do
        (let ((i (value board row col)))
          (setf r (+ r
            (abs (- row (floor (/ (- i 1) 3))))
            (abs (- col (mod (+ 2 i) 3))))))))
    r))

(defun timeit (n)
  (let ((puzzles '()))
    (loop while (< (length puzzles) n) do
      (push (random-puzzle) puzzles))
    (loop for cmd in '(BFS A*) do
      (print cmd)
      (time (loop for puzzle in puzzles do (solve-8puzzle cmd puzzle))))))
