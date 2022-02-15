#include "Encoder.h"

// Encoder Implementation

Encoder::Encoder(std::shared_ptr<std::vector<int>> vect) : huffmanTree(HuffmanTree(vect))
{
}

std::shared_ptr<std::vector<char>> Encoder::Encode(std::string str)
{
    std::vector<char> result = huffmanTree.FindWord(str);
    std::shared_ptr<std::vector<char>> encoded = std::make_shared<std::vector<char>>(result);
    return encoded;
}

std::string Encoder::Decode(std::shared_ptr<std::vector<char>> bits)
{
    std::string answer = huffmanTree.Retrieve(*bits);
    return answer;
}

// HuffmanTree Implementation

HuffmanTree::HuffmanTree(std::shared_ptr<std::vector<int>> vect) : root(nullptr)
{
    // starts the process of creating the tree with the given frequencies
    std::vector<std::shared_ptr<Node>> nodes = std::vector<std::shared_ptr<Node>>();
    // creates nodes that hold letters and frequencies that will go into a 
    // vector to be inserted into the tree
    if(vect->size() < 26)
    {
        throw "ERROR NOT ENOUGH FREQUENCIES, PLEASE INPUT 26 FREQUENCIES";
    }
    for(int i = 0; i < vect->size(); i++)
    {
        if(vect->at(i) < 0)
        {
            throw "ERROR INPUTTED A NEGATIVE FREQUENCY";
        }
        std::shared_ptr<Node> newNode = std::make_shared<Node>();
        std::shared_ptr<int> newInt = std::make_shared<int>(vect->at(i));
        std::shared_ptr<char> newChar = std::make_shared<char>(alphabet[i]);
        newNode->weight = newInt;
        newNode->letter = newChar;
        nodes.push_back(newNode);
    }
    root = CreateTree(nodes);
}

HuffmanTree::~HuffmanTree()
{
    Clear();
}

std::shared_ptr<Node> CreateSubTree(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2)
{
    std::shared_ptr<Node> root = std::make_shared<Node>();
    std::shared_ptr<int> w = std::make_shared<int>(*node1->weight + *node2->weight);
    root->weight = w;

    if(*node1->weight >= *node2->weight)
    {
        root->left = node1;
        root->right = node2;
    }
    else
    {
        root->left = node2;
        root->right = node1;
    }
    return root;
}

int FindMins(std::vector<std::shared_ptr<Node>> nodes)
{
    int min = *nodes.at(0)->weight;
    int index = 0;
    for(int i = 1; i < nodes.size(); i++)
    {
        if(*nodes.at(i)->weight < min)
        {
            min = *nodes.at(i)->weight;
            index = i;
        }
    }
    return index;
}

std::shared_ptr<Node> HuffmanTree::CreateTree(std::vector<std::shared_ptr<Node>> nodes)
{
    // if nodes has more than 1 node, keep making subtrees
    while(nodes.size() > 1)
    {
        // find 2 lowest weights and delete from list
        int index1 = FindMins(nodes);
        std::shared_ptr<Node> node1 = std::make_shared<Node>();
        node1 = nodes.at(index1);
        nodes.erase(nodes.begin() + index1);

        int index2 = FindMins(nodes);
        std::shared_ptr<Node> node2 = std::make_shared<Node>();
        node2 = nodes.at(index2);
        nodes.erase(nodes.begin() + index2);

        // make subtree with lowest weights
        std::shared_ptr<Node> temp = std::make_shared<Node>();
        temp = CreateSubTree(node1, node2);
        // subtree weight = combined weights
        std::shared_ptr<int> tempWeight = std::make_shared<int>(*node1->weight + *node2->weight);
        temp->weight = tempWeight;
        // add subtree back to nodes
        nodes.push_back(temp);
    }
    std::shared_ptr<Node> hTTop = std::make_shared<Node>();
    hTTop = nodes.at(0);
    // create delimiter and push to right node of the root
    std::shared_ptr<Node> dTop = std::make_shared<Node>();
    std::shared_ptr<Node> newNode = std::make_shared<Node>();
    // the root of the huffman tree starts on the first left node
    dTop->left = hTTop;
    dTop->right = newNode;
    return dTop;
}

bool HuffmanTree::isEmpty() const
{
    if(root == nullptr)
    {
        return true;
    }
    return false;
}



void HuffmanTree::Clear()
{
    //PrintInOrder(root);
    root.reset();
}

void HuffmanTree::PrintInOrder(std::shared_ptr<Node> node)
{
    if(node == nullptr) return;
    PrintInOrder(node->left);
    if(node->letter == nullptr)
    {
        std::cout << "branch node with weight " << *node->weight << std::endl;
    }
    else
    {
        std::cout << "letter " << *node->letter << " with weight " << *node->weight << std::endl;
    }
    PrintInOrder(node->right);
}

void Traverse(char letter, std::shared_ptr<Node> node, std::string temp, std::string& path)
{
    
    if(node != nullptr)
    {
        if(node->letter != nullptr && letter == *node->letter)
        {
            path = temp;
            return;
        }
        Traverse(letter, node->left, temp + "1", path);
        Traverse(letter, node->right, temp + "0", path);
    }
    return;
}

std::vector<char> StrToChar(std::string word)
{
    std::vector<char> vect;
    char temp = 0b00000000;
    int i = 0;
    for(char c : word)
    {
        if(c == '1')
        {
            temp |= 0b00000001;
        }
        else
        {
            temp |= 0b00000000;
        }
        if(i >= 7)
        {
            i = 0;
            vect.push_back(temp);
            temp = 0b00000000;
        }
        else
        {
            temp = temp << 1;
            i++;
        }
    }
    if(i > 0)
    {
        temp = temp << (7 - i);
        vect.push_back(temp);
    }
    return vect;
}

std::vector<char> HuffmanTree::FindWord(std::string word)
{
    std::string answer = "";
    //traverse through tree to find same letter
    for(char c : word)
    {
        if(isspace(c))
        {
            throw "ENTERED INVALID \" \" CHARACTER";
        }
        std::string temp;
        Traverse(c, root, "", temp);
        answer += temp;
        
    }
    //std::cout << "full path is " << answer << std::endl;
    // pack the path into bits
    std::vector<char> vect = StrToChar(answer);
    return vect;
}

char HuffmanTree::RecurRetrieve(std::string& path, std::shared_ptr<Node> node)
{
    // if tree is not empty and curr node is not null
    if(node != nullptr)
    {
        if(path == "" && node->letter == nullptr)
        {
            return '-';
        }
        // if we are at a leaf node, then return letter
        if(node->letter != nullptr)
        {
            return *node->letter;
        }
        // if not then recur based on 1 and 0s
        else if(path.at(0) == '1')
        {
            path.erase(0, 1);
            return RecurRetrieve(path, node->left);
        }
        else
        {
            path.erase(0, 1);
            return RecurRetrieve(path, node->right);
        }
    }
    //throw "ERROR CHARACTER NOT IN TREE";
    return '-';
}

bool SameBit(char a, char b)
{
    unsigned char diff = a^b;
    return !diff;
}

std::string HuffmanTree::Retrieve(std::vector<char> bits)
{
    std::string fullPath = "";
    for(char c : bits)
    {
        unsigned char temp = 0b10000000;
        for(int i = 0; i < 8; i++)
        {
            if(SameBit((c & temp), temp))
            {
                fullPath.push_back('1');
            }
            else
            {
                fullPath.push_back('0');
            }
            temp = temp >> 1;
        }
    }
    std::string answer = "";
    // need to travel tree until we find selected letter and return that letter
    while(fullPath != "")
    {
        char letter = RecurRetrieve(fullPath, root);
        if(letter != '-')
        {
            answer += letter;
        }
    }
    return answer;
}