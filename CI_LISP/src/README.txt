This is my submission for Task Two.
 
I expanded the grammar to include symbols which can be assigned a numerical value, the values of these symbols are stored as a symbol table the is a linked list. 

There are no issues that exist at this time, my sample runs are below

/Users/tristan.nibbe114/Desktop/CI_LISP/cmake-build-debug/cilisp

> (add ((let (abcd 1)) (sub 3 abcd)) 4)
Type: Integer Value: 6

> (mult ((let (a 1) (b 2)) (add a b)) (sqrt 2))
Type: Integer Value: 4

> (add ((let (a ((let (b 2)) (mult b (sqrt 10))))) (div a 2)) ((let (c 5)) (sqrt c)))
Type: Integer Value: 5

> ((let (first (sub 5 1)) (second 2)) (add (pow 2 first) (sqrt second)))
Type: Integer Value: 17

> ((let (a ((let (c 3) (d 4)) (mult c d)))) (sqrt a))
Type: Integer Value: 3

> ((let (abc 1)) (sub ((let (abc 2)) (add abc de)) abc))

ERROR: ENTRY NOT FOUND IN SYMBOL TABLE
Process finished with exit code 0