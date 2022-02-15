# Homework 2: Huffman Encoding
You have recently been employed by the Data Transmission Corporation as a network engineer. Your 
first task at DTC is to reduce the cost and improve performance of their network.  Currently characters 
are encoded using UTF-8. Recent analysis of your network has indicated that the characters in use on 
the network are only those in the lowercase Latin (ascii) alphabet. Your task is to implement a new 
encoding for these characters that is better than UTF-8. The public interface should be as follows:

_//public constructor passing array of letter frequencies._

Encoder(std::shared_ptr<std::vector<int>>);
  
_//Encode std::string into a sequence of bytes._
  
std::shared_ptr<std::vector<char>> Encode(std::string);
  
_//Decode an array of bytes into a std::string._
  
std::string Decode(std::shared_ptr<std::vector<char>>);
  
