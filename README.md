# Banker's Algorithm
OS Programming Assignment #2 - Documentation is provided via comments within code. 
This program implements Banker's Algorithm in order to determine if a system is safe or unsafe. If no deadlock is found, then the safe sequence is printed to the console. This information is used to help properly allocate resources for processes. Data is read from the file "data.txt" as input.

### Running program:
Clone repository:
> git clone git@github.com:ifowl/Bankers_Algorithm.git

Compile code by using:
> g++ main.cpp -o algorithm

Run program:
> ./algorithm

### Expected output:
If system is safe:

![Output1](https://i.imgur.com/4oIFsqj.png)

If system is unsafe:

![Output2](https://i.imgur.com/QmceLbz.png)

## Using custom values:
In order to use your own data you must edit the numbers within data.txt. By default, each table/matrix is 3x5. Please do not edit the labels for each table, and make sure you include a space inbetween each number. When modifying the dimensions of the tables in data.txt, ensure you change the processCount and resourceCount global variables accordingly in main.cpp.

Data.txt:

![Data](https://i.imgur.com/PFzKIXE.png)
