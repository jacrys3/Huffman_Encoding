# Homework 2: Huffman Encoding

This homework is part of CSS 343 at the University of Washington Bothell. 
The point of the assignment was to create a functioning decoder and encoder of chars that were encoded based on Huffman Tree encoding. 

> You have recently been employed by the Data Transmission Corporation as a network engineer. Your 
first task at DTC is to reduce the cost and improve performance of their network.  Currently characters 
are encoded using UTF-8. Recent analysis of your network has indicated that the characters in use on 
the network are only those in the lowercase Latin (ascii) alphabet. Your task is to implement a new 
encoding for these characters that is better than UTF-8. The public interface should be as follows:

I implemented 3 functions as specified by the professor which are:

> Encoder(std::shared_ptr<std::vector<int>>);
  
> std::shared_ptr<std::vector<char>> Encode(std::string);
  
> std::string Decode(std::shared_ptr<std::vector<char>>);
