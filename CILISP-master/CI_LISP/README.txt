This is my submission for Task Six.
 
I added the ability to enter the following functions, rand read, equal less and greater.
I also added the ability to use conditions.

I am beginning to have some issues with my output, the calculator will sometimes print more than it should and also sometimes prints out of order I have tried to resolve this as best I can but I have not been able to yet, my sample runs are below

/Users/tristan.nibbe114/Desktop/CILISP-master/CI_LISP/cmake-build-debug/cilisp

> (add 1 2)

Result: Type: Integer Value: 3

> (add ((let (abc 1)) (sub 3 abc)) 4)

Result: Type: Integer Value: 6

> (mult ((let (a 1) (b 2)) (add a b)) (sqrt 2))

Result: Type: Double Value: 4.24264

> (add ((let (a ((let (b 2)) (mult b (sqrt 10))))) (div a 2)) ((let (c 5)) (sqrt c)))

Result: Type: Double Value: 5.39835

> ((let (first (sub 5 1)) (second 2)) (add (pow 2 first) (sqrt second)))

Result: Type: Double Value: 17.4142

> ((let (abc 1)) (sub ((let (abc 2) (de 3)) (add abc de)) abc))

Result: Type: Integer Value: 3

> 

> (add ((let (abcd 1)) (sub 3 abcd)) 4)

Result: Type: Integer Value: 6

> (mult ((let (a 1) (b 2)) (add a b)) (sqrt 2))

Result: Type: Double Value: 4.24264

> (add ((let (a ((let (b 2)) (mult b (sqrt 10))))) (div a 2)) ((let (c 5)) (sqrt c)))

Result: Type: Double Value: 5.39835

> ((let (first (sub 5 1)) (second 2)) (add (pow 2 first) (sqrt second)))

Result: Type: Double Value: 17.4142

> ((let (a ((let (c 3) (d 4)) (mult c d)))) (sqrt a))

Result: Type: Double Value: 3.4641

> ((let (int a 1.25))(add a 1))
WARNING: precision loss in the assignment for variable a

Result: Type: Integer Value: 2

> (add 1 2 3 4 5)

Result: Type: Integer Value: 15

> ((let (int a 1)(double b 2))(print a b 3))
Print: Integer Value: 1    Integer Value: 2    Integer Value: 3    
Result: Type: Integer Value: 3

> ((let (int a (read)) (double b (read)) ( c (read)) ( d (read))) (print a b c d))
Print: read:=3
read:=5.0
Double Value: 5    read:=10
Integer Value: 10    read:=5.175
Double Value: 5.175    
> 
> ((let (a 0)) (cond (less (rand) 0.5) (add a 1) (sub a 1)))

Result: Type: Integer Value: 1

> ((let (myA (read))(myB (rand)))(cond (less myA myB) (print myA) (print myB)))
read:=5
Print: Double Value: 0.755605    
Result: Type: Double Value: 0.45865

> 
> ((let (myA (read))(myB (rand)))(cond (less myA myB) (print myA) (print myB)))
read:=7
Print: Double Value: 0.218959    
Result: Type: Double Value: 0.0470446

> 
> ((let (myA (read))(myB (rand)))(cond (less myA myB) (print myA) (print myB)))
read:=.1
Print: Double Value: 0.679296    
Result: Type: Double Value: 0.934693

> 
> ((let (myA (read))(myB (rand)))(cond (less myA myB) (print myA) (print myB)))
read:=0
Print: Double Value: 0.519416    
Result: Type: Double Value: 0.830965