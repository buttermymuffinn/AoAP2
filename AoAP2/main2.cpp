/*
 * Project Name: MaxSum_P2
 * Date: 11/10/19
 * Authors: Diego Hernandez, Adrian Miranda, Emil Dobrzynski, Justinle Tran
 * Description: This program takes in a matrix of positive integers and finds the maximum sum by
selecting one element from every column in the matrix, moving left-to-right. As you move through
the matrix column-by-column, though, there is a penalty to your sum depending on how you
move relative to your previous two positions. If the next row you select is between the previous two
selected rows, there is no penalty; however, there is a penalty of 2 to your sum for every row above
the maximum of the previous two or below the minimum of the previous two.
 */


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/*
a lot of messing around with +1's here due to how we calculate the true value of elements
based on "free" rows and the fact that our array starts at element 0,0 - not 1,1 \
but honestly I went mad trying to get the +1's to line up correctly, and don't feel like messing with them
anymore right now - someone else feel free to revamp the function if you have the time
- Adrian Miranda
*/
/*void calculateSum(int secPrev, int prev, int rows, int columns, int iter, vector<vector <int> > inputArray, vector<int> *outputArray, int *penalties){
    int value, temp = 0, row = 0;
    int colMax = 0, colMin = 0;
    int min1 = min(secPrev, prev);
    int max1 = max(secPrev, prev);
    int directNext, nextBestElem;
    int *penalt = penalties;
    // debug print function
    // std::cout << "Running calculate with min: " << min << " and max: " << max << std::endl;

    for(int j=0; j<rows; j++){




        //*penalt +=1;
        //cout << *penalt << " ";
        // calculating real value of an element based on "free" rows
        if(j+1 >= min1 && j+1 <= max1){
            value = inputArray[j][iter];
        }else{
            value = inputArray[j][iter] - min((2*abs(((j+1)-min1)) ), (2*abs((j + 1 - max1))));
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
        calculateSum(secPrev, prev, rows, columns, iter+1, inputArray, outputArray, penalties);
    }
}
 */

int calSum(int row, int cols, vector<vector<int>> inputArray, vector<int> *outputArray){

    int ans[row][cols][row];
    int index[row][cols][row];

    int firstCol[row];

    for(int i=0;i<row;i++){

        firstCol[i]= inputArray[i][0] - 2*(i);
    }

    for(int i=0;i<row;i++){

        for(int j=0;j<row;j++){
            int penalty;

            if(i<=j){
                penalty=0;
            }else{
                penalty= 2* (i-j);
            }

            ans[i][1][j]= inputArray[i][1] - penalty+ firstCol[j];

        }
    }

    for(int j=2;j<cols;j++){

        for(int i=0;i<row;i++){


            int nextRow= i;

            for(int k=0;k<row;k++){

                int currRow= k;
                int ind=-1;
                int maxVal= INT_MIN;
                for(int l=0;l<row;l++){

                    int prevRow=l;
                    int max1= max(prevRow, currRow);
                    int min1= min(prevRow, currRow);

                    int penalty;
                    if(nextRow<=max1&&nextRow>= min1){
                        penalty=0;
                    }else if(nextRow>max1){
                        penalty= 2*(nextRow-max1);
                    }else{
                        penalty= 2*(min1-nextRow);
                    }

                    int val= -penalty+ inputArray[i][j] + ans[k][j-1][l];
                    if(val>maxVal){
                        maxVal=val;
                        ind=l;
                    }
                }

                ans[i][j][k]=maxVal;
                index[i][j][k]=ind;

            }

        }

    }

    int max=INT_MIN;
    int x=-1;
    int y=-1;

    for(int i=0;i<row;i++){

        for(int j=0;j<row;j++){

            if(ans[i][cols-1][j]>max){
                max= ans[i][cols-1][j];
                x=i;
                y=i;
            }

        }
    }

    for(int j=cols-1;j>=2;j--) {

        outputArray->push_back(x);
        int temp=x;
        x= y;
        y= index[temp][j][y];
    }

    outputArray->push_back(x);
    outputArray->push_back(y);

    return max;

}


int main(){
    // stream object to hold input from file for sanitation
    stringstream ostringStream;
    string line;
    ifstream inputFile;
    ofstream outputFile;
    // value to keep track of the sum of the choices
    int runningSum = 0;
    //value to keep track of penalties
    int penalties = 0;
    inputFile.open("../input.txt", ios::in);

    if(inputFile.is_open()){
        cout << "File successfully opened - continuing program" << endl;
        getline (inputFile, line);
        ostringStream.str(line);
    }else{
        cout << "File not found" << endl;
        exit(EXIT_FAILURE);
    }

    // setting the initial rows and columns of the 2D array
    int rows, columns, temp;
    ostringStream >> rows >> columns;
    vector<vector<int> > inputArray(rows, vector<int> (columns));
    // array to hold the integers we select for the answer
    vector<int> answerArray;

    // reading input from file and filling up the 2D array
    for(int i=0; i<rows; i++){
        ostringStream.clear();
        getline(inputFile, line);
        ostringStream.str(line);
        for(int j=0; j<columns; j++){
            ostringStream >> inputArray[i][j];
        }
    }
    inputFile.close();

    // test printing the array to make sure everything copied over properly
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            cout << inputArray[i][j] << ' ';
        }
        cout << endl;
    }

    //   calculateSum(1, 1, rows, columns, 0, inputArray, &answerArray, &penalties);

    // for(int i = 0; i < columns ; i++){
    //   runningSum += answerArray[i];
    //}

    runningSum = calSum(rows,columns,inputArray, &answerArray);

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
    inputFile.open("../output.txt");
    if(inputFile.peek() == ifstream::traits_type::eof()){
        inputFile.close();
        outputFile.open("../output.txt");
    }else{
        inputFile.close();
        outputFile.open("../temp.txt");
        remove("../output.txt");
        outputFile.close();
        rename("../temp.txt", "../output.txt");
        outputFile.open("../output.txt");
    }

    // write results to the output file and close it
    outputFile << runningSum << '\n';
    for(auto i= static_cast<int>(answerArray.size() - 1); i >= 0; i--){
        outputFile << answerArray[i] << ' ';
    }
    outputFile.close();


    return 0;
}

