//Isaac Fowler
//OS Programming Assignment #2
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::vector; using std::string;

const int processCount = 5; //Set amount of processes
const int resourceCount = 3; //Set amount of resources
//Matrices
int allocation[processCount][resourceCount];
int max[processCount][resourceCount];
int need[processCount][resourceCount];
int available[resourceCount];

//This function takes the user specificed input file and will read its integers into their corresponding matrices. This function will only 
//work as long as the processCount and resourceCount integers are set accordingly.
void readMatrices(std::ifstream& ifile) {
    int number, number2, columns=0;
    string str;
    while (ifile >> str) { //loops as long as there are strings in the file.
        if (str == "Allocation:") { //If allocation string is read, it will take integers from file and add them into the allocation matrix
            for (int i = 0; i < processCount; ++i) {
                for (int j = 0; j < resourceCount; ++j) {
                    ifile >> number; //Take number from file
                    allocation[i][j] = number; //assign it to corresponding matrix
                    //std::cout << allocation[i][j];
                }
                //std::cout << std::endl;
            }
            //std::cout << std::endl;
        }
        else if (str == "Max:") { //If Max string is read, it will take integers from file and add them into the max matrix
            for (int i = 0; i < processCount; ++i) {
                for (int j = 0; j < resourceCount; ++j) {
                    ifile >> number; //Take number from file
                    max[i][j] = number; //assign it to corresponding matrix
                    //std::cout << max[i][j];
                }
                //std::cout << std::endl;
            }
            //std::cout << std::endl;
        }
        else if (str == "Available:") { //If available string is read, it will take integers from file and add them into available array
            for (int i = 0; i < resourceCount; ++i) {
                ifile >> number;
                available[i] = number;
                //std::cout << available[i];
            }
        }
    }
}

//This function gets the need matrix by subtracting Allocation from max. (Formula: Need = Max - Allocation)
void getNeed() {
    for (int i = 0; i < processCount; ++i) {
        for (int j = 0; j < resourceCount; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
            //std::cout << need[i][j];
         }
    }
}


//Checks if all of the resources in a process are less than or equal to the available resources.
bool isLess(int process) {
    int count = 0; //Counter for the row in matrix
    for (int i = 0; i < resourceCount; ++i) { //loops through resouruceCount
        if (need[process][i] <= available[i]) { //Checks if need resource is less than or equal to available resource
            count++;
        }
    }
    if (count == resourceCount) { //If all resources in process row are less than availalbe resources, return true
        return true;
    }
    else return false; //Else return false because this row is unable to be allocated right now.
}

void printSequence(vector<int> sequence) {
    std::cout << "Safe sequence is: ";
    for (int i = 0; i < sequence.size(); ++i) {
        if (i < sequence.size() - 1) {
            std::cout << "P" << sequence[i] << ", ";
        }
        else {
            std::cout << "P" << sequence[i];
        }
    }
}

int main() {
    std::cout << "Banker's Algorithm by Isaac F.\nPlease refer to the README file if you wish to use custom matrices.\n--------------------------------------------------------------------";
    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cout << "Unable to open file\n";
        return 0;
    }
    readMatrices(file);
    file.close();
    getNeed();
    std::cout << std::endl;

    vector<int> sequence; //Vector for holding the safe sequence. Process indices are pushed to this vector.
    int allTrue = 0; //Counter that is compared to processCount. If all allTrue=processCount, then all of the rows are safe.
    bool lineTrue[processCount]; //boolean array to keep track of each row.
    for (int i = 0; i < processCount; ++i) { //initialize lineTrue boolean array values to false
        lineTrue[i] = false; 
    }
    bool notsafe = false; int loop = 0;
    while (allTrue != processCount && notsafe == false) { //Loop until all processes are allocated or the system is deemed unsafe.
        for (int line = 0; line < processCount; ++line) { //Iterate through the rows of a matrix
            if (lineTrue[line] == false) { //If the current row of a matrix is false then proceed
                if (isLess(line)) {
                    for (int j = 0; j < resourceCount; ++j) {
                        available[j] += allocation[line][j]; //Add allocation process to available processes
                    }
                    lineTrue[line] = true; //Set line to true (it can be safely allocated)
                    ++allTrue; //Increment allTrue counter for while loop
                    sequence.push_back(line); //Add process to safe sequence
                }
            }
            //std::cout << "New available is: " << available[0] << available[1] << available[2] << std::endl;
        }
        ++loop;
        if (loop > 10) {//I'm assuming if the program iterates more than 10 times through the processes, then it most likely isn't safe.
            notsafe = true; //This will stop an infite loop and display that there is a deadlock.
        }
    }
    std::cout << std::endl;
    if (notsafe == true) {
        std::cout << "There is a deadlock. This system is not in a safe state.";
    }
    else {
        std::cout << "This system is in a safe state. ";
        printSequence(sequence);
    }
    std::cout << std::endl << std::endl;
}