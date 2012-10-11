;; 8-puzzle
;; Dustin Ingram

(defun solved-puzzle ()
    "Returns a solved puzzle"
    #2a((1 2 3)(4 5 6)(7 8 9)))

(defun solved? (puzzle)
    "Returns if the list is solved"
    (equalp puzzle (solved-puzzle)))

(defun successors (puzzle)
    "Returns successor states of the puzzle"
    (mapcar #'(lambda (x) (move puzzle x))
    (valid-moves puzzle)))

(defun apply-moves (puzzle moves)
    (if (null moves) puzzle
        (apply-moves (move puzzle (car moves)) (cdr moves))))


(defun solve-8puzzle (cmd puzzle)
    (print-puzzle puzzle)
    (case cmd
        ((BFS) (bfs puzzle))
        ((DFS) (print "dfs"))
        ((A*) (print "a*"))))

(defun bfs (puzzle)
    (let ((visited '())
          (queue (list (list puzzle '()))))
        (loop while (not (null queue)) do
            (cond 
                ((solved? (caar queue)) 
                    (print "solved")
                    (return (cadar queue))
                )
                (T 
                    (mapcar #'(lambda (x) 
                    (if (not (member (move (caar queue) x) visited))
                    
                    
                        (setf queue (append queue (list (list (move (caar queue) x) (append (cadar queue) (list x))))))
                        )
                    )
                    (valid-moves (caar queue)))
                    (setf queue (cdr queue))
                    (setf visited (append visited (list (caar queue))))
                )
            ) 
            )))
