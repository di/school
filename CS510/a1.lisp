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
