//
//  main.cpp
//  BinaryToDecimal
//
//  Created by Edgar Olvera on 3/13/20.
//  Copyright © 2020 Edgar Olvera. All rights reserved.
//
//  This is a simple program for converting set a binary digits to decimal.
//  This program implements a stack to store binary digits as well as store the result decimal.
//  The program will use files to read any input binary digits and output decimal answers.
//
//  I have not designed any error checking methods. We assume that the input file will be as intended.
//  Such as test file input.txt: "11000101, 10101010, 11111111, 10000000, 1111100000"
//


#include <iostream>
#include <fstream>
#include <cmath>
#include <stack>
using namespace std;

void readFile(stack<int>&, ifstream&, ofstream&);
void biDeciConversion(stack<int>&);
void writeResult(stack<int>&, ofstream&, char);

int main(int argc, const char * argv[]) {
    
    stack<int> s;
    ifstream infile;
    ofstream outfile;
    
    infile.open("input.txt");
    
    if(!infile){
        cout << "Cannot open the input file." << endl;
        return -1;
    }
    
    outfile.open("output.txt");
    readFile(s, infile, outfile);       //  Function will reading the input file and writing the output file
    
    infile.close();
    outfile.close();
    return 0;
}

void readFile(stack<int> &s, ifstream &file, ofstream &out){
    char num{};
    file >> num;
    
    while(file){
        if(num == '1' or num == '0')        //  Checks to see if there is a binary digit
            s.push(num - '0');      //  pushes the binary digit into the stack, converted from char to int
        else if(num == ',')     //  else checks for instance when set of binary numbers have been read
        {
            biDeciConversion(s);            // function will convert binary number to decimal
            writeResult(s, out, ',');       //  writes the result to output file
        }
        file >> num;        //  continues reading file
      }
    
    //  We check for any dangling set of binary numbers by calling the conversion and write function again
    biDeciConversion(s);
    writeResult(s, out, ' ');
}

void biDeciConversion(stack<int> &s){
    int it{}, decimal{};            //  initialize an iterator and decimal result variable
                                    
    //  since the binary digits were pushed from right to left
    //  they will be read from left to right, as they are popped from the stack
    
    while (!s.empty() and (s.top() == 1 or s.top() == 0))   // while stack is not empty or contains a binary digit
    {
        decimal += (s.top() * pow(2, it));          //  we multiply the binary digit, on top of the stack, by 2^iterator. then add to
                                                    //  the result decimal variable
        s.pop();
        it++;           //  increment interator after each loop
    }
    
    s.push(decimal);        // push the result into the stack
}

void writeResult(stack<int> &s, ofstream &out, char end){
    while (!s.empty())      //  the function will loop through the stack, writing the top into the output file then popping the stack.
    {
        out << s.top() << end << " ";           //  for readability, i've included the option of adding ',' to split results
        s.pop();
    }
}
