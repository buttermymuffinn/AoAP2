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

    // reading input from file and filling up the 2D array
    for(int i=0; i<rows; i++){
        ostringStream.clear();
        std::getline(inputFile, line);
        ostringStream.str(line);
        for(int j=0; j<columns; j++){
            ostringStream >> inputArray[i][j];
        }
    }

    // test printing the array to make sure everything copied over properly
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            std::cout << inputArray[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}