This is my submission for Task Five.
 
I added the ability to have multiple arguments for the addition subtraction and multiplication operations. I also added the ability to print multiple terms at once. If not enough operators are included for any operation that requires more than one the program will now print an error.

There are no issues that exist at this time, my sample runs are below

/Users/tristan.nibbe114/Desktop/CILISP-master/CI_LISP/cmake-build-debug/cilisp

> ((let (int a 1)(double b 2))(print a b 3))
Integer Value: 1    Integer Value: 2    Integer Value: 3    
Type: Integer Value: 3

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

> (print 1 2 3 4)
Integer Value: 1    Integer Value: 2    Integer Value: 3    Integer Value: 4    
Type: Integer Value: 4

> (add 1 2 3 4 5)

Type: Integer Value: 15

> (sub 1 2 3 4 5)

Type: Integer Value: -13

> (mult 2 2 2 2)

Type: Integer Value: 16

> (add 1)

Too few parameters for function type addition
Process finished with exit code 0