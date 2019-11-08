#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>

/*
a lot of messing around with +1's here due to how we calculate the true value of elements
based on "free" rows and the fact that our array starts at element 0,0 - not 1,1 \
but honestly I went mad trying to get the +1's to line up correctly, and don't feel like messing with them
anymore right now - someone else feel free to revamp the function if you have the time
- Adrian Miranda
*/
void calculateSum(int secPrev, int prev, int rows, int columns, int iter, std::vector<std::vector <int> > inputArray, std::vector<int> *outputArray){
    int value, temp = 0, row = 0;
    int min = std::min(secPrev, prev);
    int max = std::max(secPrev, prev);
    // debug print function
    // std::cout << "Running calculate with min: " << min << " and max: " << max << std::endl;
    for(int j=0; j<rows; j++){

        // calculating real value of an element based on "free" rows
        if(j+1 >= min && j+1 <= max){
            value = inputArray[j][iter];
        }else{
            value = inputArray[j][iter] - std::min((2*std::abs(((j+1)-min)) ), (2*std::abs(((j+1)-max))));
        }

        if(value >= temp){
            temp = value;
            row = j;
        }
    }
    temp = inputArray[row][iter];
    secPrev = prev;
    prev = row+1;
    outputArray->push_back(temp);
    if(iter+1 < columns){
        calculateSum(secPrev, prev, rows, columns, iter+1, inputArray, outputArray);
    }
}

int main(){
    // stream object to hold input from file for sanitation
    std::stringstream ostringStream;
    std::string line;
    std::ifstream inputFile;
    std::ofstream outputFile;
    // value to keep track of the sum of the choices
    int runningSum = 0;
    inputFile.open("input.txt", std::ios::in);

    if(inputFile.is_open()){
        std::cout << "File successfully opened - continuing program" << std::endl;
        std::getline (inputFile, line);
        ostringStream.str(line);
    }else{
        std::cout << "File not found" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // setting the initial rows and columns of the 2D array
    int rows, columns, temp;
    ostringStream >> rows >> columns;
    std::vector<std::vector<int> > inputArray(rows, std::vector<int> (columns));
    // array to hold the integers we select for the answer
    std::vector<int> answerArray;

    // reading input from file and filling up the 2D array
    for(int i=0; i<rows; i++){
        ostringStream.clear();
        std::getline(inputFile, line);
        ostringStream.str(line);
        for(int j=0; j<columns; j++){
            ostringStream >> inputArray[i][j];
        }
    }
    inputFile.close();

    // test printing the array to make sure everything copied over properly
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            std::cout << inputArray[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    
    calculateSum(1, 1, rows, columns, 0, inputArray, &answerArray);

    /*
    we still need to calculate the final sum of the chosen array values
    and output that to the text file
    - Adrian Miranda
    */

    /* 
    this chunk of code checks to see if output.txt is an empty file
    if it is empty, then it creates an output file stream to it
    otherwise it creates a new temporary file, deletes output
    and renames temp to output - this is to make sure we are writing to a clean output.txt
    that doesn't have information from a previous run of the code
    */
    inputFile.open("output.txt");
    if(inputFile.peek() == std::ifstream::traits_type::eof()){
        inputFile.close();
        outputFile.open("output.txt");
    }else{
        inputFile.close();
        outputFile.open("temp.txt");
        remove("output.txt");
        outputFile.close();
        rename("temp.txt", "output.txt");
        outputFile.open("output.txt");
    }
    
    // write results to the output file and close it
    outputFile << runningSum << '\n';
    for(int i=0; i<answerArray.size(); i++){
        outputFile << answerArray[i] << ' ';
    }
    outputFile.close();

    
    return 0;
}