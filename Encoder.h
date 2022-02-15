#ifndef ENCODER_H_
#define ENCODER_H_

#include "HuffmanTree.h"
#include <vector>
#include <string>
#include <memory>

//using namespace std;

/**
 * Encoder is made up of a HuffmanTree which is in separate .h and .cpp files.
 * They should not have to be included separately as I have included them here. 
 */

class Encoder
{
public:
    // creates a HuffmanTree based on the frequencies of the lowercase letters passed in.
    Encoder(std::shared_ptr<std::vector<int>>);

    // encodes a string to binary with the Huffman encoding using the 
    // HuffmanTree created by the constructor.
    std::shared_ptr<std::vector<char>> Encode(std::string);

    // decodes binary to a string with the HuffmanTree created by the constructor.
    std::string Decode(std::shared_ptr<std::vector<char>>);
private:
    HuffmanTree huffmanTree;
};

#endif