// Apr19_HuffmanTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node() = delete; // no allow to use default constructor
    Node(char c, int f) : ch{ c }, freq{ f }, left{ nullptr }, right{ nullptr } {  }
};

typedef Node* NodePtr;

// TODO 2: write a function that reads a file and retursn ch freq
std::unordered_map<char, int>
getFrequencies(const std::string& filename) {
    std::unordered_map<char, int> um;
    // read each character and accumulate its freq
    std::fstream file;
    file.open(filename, std::ios::in);
    char ch;
    // while (file >> ch) { // to calculate without endl and blank
    while(file.get(ch)){
        std::cout << ch;
    }
    file.close();





    return um;
}

int main()
{
    getFrequencies("Pride_and_Prejudice.txt");
}
