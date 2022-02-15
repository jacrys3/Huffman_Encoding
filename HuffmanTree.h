#ifndef HUFFMAN_TREE_H_
#define HUFFMAN_TREE_H_

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <bitset>

//using namespace std;

// this struct represents each Node in the HuffmanTree. leaf nodes will have a weight and 
// a letter, while 'junction' nodes will only have a weight which will be the sum of the leaf nodes. 
struct Node
{
    std::shared_ptr<char> letter = nullptr;
    std::shared_ptr<int> weight = nullptr;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
};

// this class represents the Huffman encoding process with a tree representation. 
class HuffmanTree
{
public:
    HuffmanTree(std::shared_ptr<std::vector<int>>);
    ~HuffmanTree();

    std::shared_ptr<Node> CreateTree(std::vector<std::shared_ptr<Node>>);
    bool isEmpty() const;
    void Clear();
    void PrintInOrder(std::shared_ptr<Node>);
    std::vector<char> FindWord(std::string);
    std::string Retrieve(std::vector<char>);
    char RecurRetrieve(std::string&, std::shared_ptr<Node>);
private:
    std::shared_ptr<Node> root;
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
};

#endif