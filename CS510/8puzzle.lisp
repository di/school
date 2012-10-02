;; 8-puzzle
;; Copyright 2006--2012, Evan A. Sultanik
;;                       http://www.sultanik.com/

(defun random-puzzle (&optional (max-moves 20))
  "Returns a random puzzle that requires no more than `max-moves' moves to solve."
  (let ((puzzle (make-array '(3 3) :initial-contents '((1 2 3)(4 5 6)(7 8 9)))) (next nil))
    (loop for i from 1 to max-moves do
	  (let ((vm (valid-moves puzzle)))
	    (setf puzzle (move puzzle (nth (random (length vm)) vm)))))
    puzzle))

(defun value (puzzle row col)
  "Returns the value of the piece at position (`row',`col') in the `puzzle' (a value of 9 represents the open space)"
  (aref puzzle row col))

(defun print-puzzle (puzzle)
  "Prints the puzzle on the screen."
  (format t "-------------
")
  (loop for row from 0 to 2 do
	(loop for col from 0 to 2 do
	      (if (= 9 (value puzzle row col))
		  (format t "|   ")
		(format t "| ~d " (value puzzle row col))))
	(format t "|
-------------
")))

(defun copy-array (array)
  "Utility function for making a copy of an array."
  (let ((dims (array-dimensions array)))
    (adjust-array
     (make-array dims :element-type (array-element-type array) :displaced-to array)
     dims)))

(defun set-cell (puzzle row col new-value)
  "Sets the cell (`row',`col') in `puzzle' to `new-value'."
  (let ((newpuzzle (copy-array puzzle)))
    (setf (aref newpuzzle row col) new-value)
    newpuzzle))

(defun swap-cells (puzzle row1 col1 row2 col2)
  "Swaps the values of two cells in a puzzle."
  (let ((cell1 (value puzzle row1 col1)))
    (set-cell (set-cell puzzle row1 col1 (value puzzle row2 col2)) row2 col2 cell1)))

(defun space-position (puzzle &optional (idx 0))
  "Returns a list containing two elements: the row and column of the space in the puzzle."
  (let ((r nil) (c nil))
    (loop for row from 0 to 2 do
	  (loop for col from 0 to 2 do
		(when (= (value puzzle row col) 9)
		  (setf r row)
		  (setf c col)
		  (return))))
    (list r c)))

(defun move (puzzle direction)
  "Returns the puzzle resulting from making the given move in the given puzzle (note that the validity of the move is not checked)."
  (let ((pos (space-position puzzle)))
    (let ((row (car pos)) (col (car (cdr pos))))
      (cond
       ((equal direction 'RIGHT)
	(if (>= col 2)
	    nil
	  (swap-cells puzzle row col row (+ col 1))))
       ((equal direction 'LEFT)
	(if (<= col 0)
	    nil
	  (swap-cells puzzle row col row (- col 1))))
       ((equal direction 'UP)
	(if (<= row 0)
	    nil
	  (swap-cells puzzle row col (- row 1) col)))
       ((equal direction 'DOWN)
	(if (>= row 2)
	    nil
	  (swap-cells puzzle row col (+ row 1) col)))
       (t nil)))))

(defun valid-moves (puzzle)
  "Returns a list containing the valid directions in which a move can be made in the givel puzzle."
  (let ((moves nil) (pos (space-position puzzle)))
    (let ((row (car pos)) (col (car (cdr pos))))
      (if (< col 2) (push 'RIGHT moves))
      (if (> col 0) (push 'LEFT moves))
      (if (< row 2) (push 'DOWN moves))
      (if (> row 0) (push 'UP moves)))
    moves))
