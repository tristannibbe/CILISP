This is my submission for Task Four.
 
I added the ability to specify a print function that will print the output of the given function

There are no issues that exist at this time, my sample runs are below

/Users/tristan.nibbe114/Desktop/CI_LISP/cmake-build-debug/cilisp

> (print(add 1 2))
Type: Integer Value: 3

> ((let (int a 1.25))(add a 1))
WARNING: precision loss in the assignment for variable a
Type: Integer Value: 2

> ((let (a ((let (c 3) (d 4)) (mult c d)))) (sqrt a))
Type: Double Value: 3.46

> ((let (first (sub 5 1)) (second 2)) (add (pow 2 first) (sqrt second)))
Type: Double Value: 17.41

> (add 1 2)
Type: Integer Value: 3

> ((let (abc 1)) (sub ((let (abc 2)) (add abc de)) abc))

ERROR: ENTRY NOT FOUND IN SYMBOL TABLE
Process finished with exit code 0