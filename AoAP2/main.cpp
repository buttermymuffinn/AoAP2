#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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
    



    /*


        project code here


    */





    // The following code should be at the end of the project
    // it is the output file management and formatting 
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
    outputFile << '\n';
    outputFile.close();

    return 0;
}