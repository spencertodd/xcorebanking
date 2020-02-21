# xcorebanking
Basic CRUD Banking Application in C++

;To build on Ubuntu 18

;Compile acocunt class
g++ -c classes/account.cpp -o classes/account.o

;Compile transaction class
g++ -c classes/transaction.cpp -o classes/transaction.o

;Compile main
g++ -c main.cpp -o main.o

;Link all objects to xcore object (can be named anything)
g++ classes/account.o transaction.o main.o -o xcore

;Run the executable 
./xcore
