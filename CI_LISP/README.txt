This is my submission for Task Three.
 
I added the ability to specify types when adding a symbol. I also realized that previously I was not properly promoting numbers when performing certain operations on them, like sqrt. Now whenever one on these operations is performed the number is automatically promoted to a double as it is when an operation is performed with an operand that is a double.

There are no issues that exist at this time, my sample runs are below

/Users/tristan.nibbe114/Desktop/CI_LISP/cmake-build-debug/cilisp


> ((let (int a 1.25))(add a 1))
WARNING: precision loss in the assignment for variable a

Type: Integer Value: 2
> (add ((let (abcd 1)) (sub 3 abcd)) 4)

Type: Integer Value: 6
> (mult ((let (a 1) (b 2)) (add a b)) (sqrt 2))

Type: Double Value: 4.24
> (add ((let (a ((let (b 2)) (mult b (sqrt 10))))) (div a 2)) ((let (c 5)) (sqrt c)))

Type: Double Value: 5.40
> ((let (first (sub 5 1)) (second 2)) (add (pow 2 first) (sqrt second)))

Type: Double Value: 17.41
> ((let (a ((let (c 3) (d 4)) (mult c d)))) (sqrt a))

Type: Double Value: 3.46
> ((let (abc 1)) (sub ((let (abc 2)) (add abc de)) abc))

ERROR: ENTRY NOT FOUND IN SYMBOL TABLE
Proce