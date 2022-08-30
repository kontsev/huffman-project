//
// Created by Admin on 31.08.2022.
//

#ifndef HUFFMAN_GIT_PRIORITY_QUEUE_MIN_H
#define HUFFMAN_GIT_PRIORITY_QUEUE_MIN_H

#include "queue.h"
#include <unordered_map>
#include <fstream>

class priority_queue_min {
private:
    node **heap;
    int heap_size;
    int max_size;
    void sift_up(int );
    void sift_down(int );
    void swap (node **, node **);
public:
    priority_queue_min(std::unordered_map<char, int> );
    ~priority_queue_min();
    void insert(node *);
    node *extract_min();
    node *build_huffman_tree();

    //encoding every symbol with binar code by using huffman tree
    std::unordered_map<char, std::string> encode(node *);

    // using binary operations, encoding the original character with a new one
    int binar(char* , char* , std::unordered_map<char, std::string> );

    // decoding text
    void decode(char* , char* , int ) const;
};


#endif //HUFFMAN_GIT_PRIORITY_QUEUE_MIN_H
