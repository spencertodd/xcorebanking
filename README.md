# xcorebanking
Basic CRUD Banking Application in C++

<pre>

# Build instructions for Ubuntu 18

# Compile individual files
g++ -c classes/account.cpp -o classes/account.o
g++ -c classes/transaction.cpp -o classes/transaction.o
g++ -c main.cpp -o main.o

# Link files to xcore object
g++ classes/account.o transaction.o main.o -o xcore 

# Run the executable
./xcore
</pre>
