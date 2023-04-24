// Apr19_HuffmanTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>

#define COUNT 10

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node() = delete; // no allow to use default constructor
    Node(char c, int f) : ch{ c }, freq{ f }, left{ nullptr }, right{ nullptr } {  }
};

typedef Node* NodePtr;
// function to print node
void printNode(const NodePtr& node) {
    std::cout << "(" << node->ch<<":"<<node->freq << ")" << "--" << node->left->ch << ":" << node->left->freq << std::endl
        << "|" << std::endl << node->right->ch <<":" << node->right->freq << std::endl;
}
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
        um[ch] += 1;
    }
    file.close();

    return um;
}

// struct to compare frequencies between nodes for the priority queue
// ref: https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/
struct CompareFreq {
    bool operator()(NodePtr const& np1, NodePtr const& np2) {
        return np1->freq > np2->freq; // usually the other way "<" but we need the lowest at the top()
    }
};

// TODO 3: build a Huffman coding tree
// ref: https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
NodePtr huffmanTreeRoot(const std::unordered_map<char, int> charFreq) {
    //NodePtr n = new Node('3', 5);
    
    std::priority_queue<NodePtr, std::vector<NodePtr>, CompareFreq> pqN;
    for (auto& cf : charFreq) { // travers a map
        pqN.push(new Node(cf.first, cf.second));
    }
    //std::cout << "SIZE:" << pqN.size() << ":" << !(pqN.size() == 1) << std::endl;

   
    while (!(pqN.size() == 1)) {
        
        auto node1 = pqN.top();
        //std::cout << "node 1 '" << node1->ch << "'[" << node1->freq << "]" << std::endl;
        pqN.pop();
        auto node2 = pqN.top();
        //std::cout << "node 2 '" << node2->ch << "'[" << node2->freq << "]" << std::endl;
        pqN.pop();
        auto new_freq = node1->freq + node2->freq;
        //std::cout << "new freq = " << node1->freq << "+" << node2->freq << "=" << new_freq << std::endl;
        NodePtr aux = new Node('#', new_freq);
        aux->left = node1;
        aux->right = node2;
        pqN.push(aux);
        //std::cout << "NEW NODE\n";
        //printNode(aux);
    }

    //std::cout << "Final size:" << pqN.size() << std::endl;
    return pqN.top();
    
}
std::stringstream huffmanEncodingRecLeft(NodePtr& node, std::stringstream& huffman_encoding) {

    huffman_encoding << '0';
    if (node and node->left == nullptr and node->right == nullptr) {
        // leaf
    }
    if (node->left) huffmanEncodingRecLeft(node->left, huffman_encoding);
    if (node->right) huffmanEncodingRecRight(node->right, huffman_encoding);
    
}

std::stringstream huffmanEncodingRecRight(NodePtr& node, std::stringstream& huffman_encoding) {
    
    
    huffman_encoding << '1';
    if (node and node->left == nullptr and node->right == nullptr) {
        // leaf
    }
    if (node->left) huffmanEncodingRecLeft(node->left, huffman_encoding);
    if (node->right) huffmanEncodingRecRight(node->right, huffman_encoding);
}
// TODO 4: Function that takes the root, prints and outputs encoding scheme in a data structure object
std::unordered_map<char, std::string> huffmanEncoding(NodePtr& root) {
    
    std::stringstream huffman_encoding;
    huffmanEncodingRecLeft(root->left, huffman_encoding);
    huffmanEncodingRecRight(root->right, huffman_encoding);
}

// TODO 5: Function that takes the encoding scheme and filename, output encoded content(bit-string) to a file named pride.huff
void huffmanOuput(const std::unordered_map<char, std::string>& encodingScheme, std::string filename) {

}
int main()
{
    auto charFreq = getFrequencies("Pride_and_Prejudice.txt");
    // test to see all char and freq from um
    //for (auto& cf: charFreq) { // travers a map
    //    std::cout << cf.first << ": " << cf.second << std::endl;
    //}
    NodePtr root = huffmanTreeRoot(charFreq);
    

    
}
