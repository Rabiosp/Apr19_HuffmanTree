// Apr19_HuffmanTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>

#define COUNT 10

struct Node {
    char ch;
    int freq;
    Node* left{nullptr};
    Node* right{ nullptr };
    Node() = delete; // does'nt allow to use default constructor
    Node(char c, int f) : ch{ c }, freq{ f }, left{ nullptr }, right{ nullptr } {  }
};

typedef Node* NodePtr;
// function to print node
void printNode(const NodePtr& node) {
    std::cout << "(" << node->ch<<":"<<node->freq << ")" << "--" << node->left->ch << ":" << node->left->freq << std::endl
        << "|" << std::endl << node->right->ch <<":" << node->right->freq << std::endl;
}

// TODO 2: write a function that reads a file and return ch freq
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
    
    std::priority_queue<NodePtr, std::vector<NodePtr>, CompareFreq> pqN;
    for (auto& cf : charFreq) { // traverse a map
        pqN.push(new Node(cf.first, cf.second));
    }

    //// Traverse priority queue
    //while (!pqN.empty()) {
    //    auto node = pqN.top();
    //    std::cout << node->ch << ":" << node->freq << std::endl;
    //    pqN.pop();
    //}

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

void huffmanEncodingRec(NodePtr& node, std::string huffman_encoding, std::unordered_map<char, std::string>& map) {

    if (node) {

        huffmanEncodingRec(node->left,  huffman_encoding + '0', map);
        if (node->left == nullptr and node->right == nullptr) {
            // leaf
            map[node->ch] = huffman_encoding;

        }
        huffmanEncodingRec(node->right, huffman_encoding + '1', map);

    }
    
}

// TODO 4: Function that takes the root, prints and outputs encoding scheme in a data structure object
std::unordered_map<char, std::string> huffmanEncoding(NodePtr& root) {
    /*std::cout << "Encoding" << std::endl;*/
    std::unordered_map<char, std::string> encodingScheme;
    std::string huffman_encoding = "";
    huffmanEncodingRec(root, huffman_encoding, encodingScheme);
    return encodingScheme;
}

// TODO 5: Function that takes the encoding scheme and filename, output encoded content(bit-string) to a file named pride.huff
void huffmanOutput(const std::unordered_map<char, std::string>& encodingScheme, std::string filename) {
    std::ofstream output(filename, std::ios::out);
    if (!output) {
        std::cerr << "Error opening output file!" << std::endl;
        return;
    }
    
    for (auto& bitString : encodingScheme) {
        std::ostringstream encodedContent;
        encodedContent << bitString.first << "-" << bitString.second << std::endl;
        output << encodedContent.str();
    }
    output.close();
}
int main()
{
    auto charFreq = getFrequencies("Pride_and_Prejudice.txt");
    //// test to see all char and freq from um
    //for (auto& cf: charFreq) { // travers a map
    //    std::cout << cf.first << ": " << cf.second << std::endl;
    //}
    /*std::cout << std::endl;*/
    NodePtr root = huffmanTreeRoot(charFreq);
    std::unordered_map<char,std::string> encodingScheme = huffmanEncoding(root);
    huffmanOutput(encodingScheme, "pride.huff");

    
}
