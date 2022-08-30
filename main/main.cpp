#include "priority_queue_min.h"
#include <iostream>
#include <unordered_map>

int main(int argc, char *argv[]) {
    if (argc != 4)
        std::cout << "problem" << std::endl;

    std::ifstream fin(argv[1]);
    std::string str, tmp;

    while (getline(fin, tmp)) {
        str += "\n";
        str += tmp;
    }

    std::unordered_map<char, int> freq;
    for (char ch: str)
        freq[ch]++;

    priority_queue_min tree(freq);
    node *root = tree.build_huffman_tree();

    std::unordered_map<char, std::string> codes = tree.encode(root);
    int number = tree.binar(argv[1], argv[2], codes);
    tree.decode(argv[2], argv[3], number);
    fin.close();
    return 0;
}
