//
// Created by Admin on 31.08.2022.
//

#include "priority_queue_min.h"

#include "priority_queue_min.h"
#include <iostream>
#include <fstream>

//private
void priority_queue_min::sift_up(int index) {
    while(index > 0 && heap[index]->frequency < heap[(index-1)/2]->frequency) {
        swap(&heap[index], &heap[(index-1)/2]);
        index = (index-1)/2;
    }
}

void priority_queue_min::sift_down(int index) {
    while (2*index + 1 < heap_size) {
        if (2*index + 1 == heap_size - 1) {
            if (heap[2*index + 1]->frequency < heap[index]->frequency)
                swap(&heap[2*index + 1], &heap[index]);
            else
                break;
        }
        else {
            int minimum = std::min(heap[2*index + 1]->frequency, heap[2*index + 2]->frequency);
            if (heap[index]->frequency > minimum) {
                if (heap[2*index + 1]->frequency == minimum) {
                    swap(&heap[2*index+1], &heap[index]);
                    index = 2*index + 1;
                }
                else {
                    swap(&heap[2*index+2], &heap[index]);
                    index = 2*index + 2;
                }
            }
            else
                break;
        }
    }
}

void priority_queue_min::swap(node **a, node **b) {
    node *tmp = *a;
    *a = *b;
    *b = tmp;
}

//public methods
priority_queue_min::priority_queue_min(std::unordered_map<char, int> freq) {
    heap_size = max_size = freq.size();
    heap = new node*[heap_size];

    int index = 0;
    for(auto pair: freq) {
        heap[index] = new node;
        heap[index]->symbol = pair.first;
        heap[index]->frequency = pair.second;
        heap[index]->left = heap[index]->right = NULL;
        index++;
    }

    for(int i = heap_size/2 - 1; i > -1; i--)
        sift_down(i);
}

priority_queue_min::~priority_queue_min() {
    for(int i = 0; i < heap_size; i++)
        delete [] heap[i];
    delete [] heap;
}

void priority_queue_min::insert(node *ptr) {
    if (heap_size + 1 < max_size) {
        ++heap_size;
        heap[heap_size-1] = ptr;
        sift_up(heap_size-1);
    }
}

node* priority_queue_min::extract_min() {
    if (heap_size > 0) {
        node *res = heap[0];
        swap(&heap[0], &heap[heap_size-1]);
        --heap_size;
        sift_down(0);
        return res;
    }
}

node* priority_queue_min::build_huffman_tree() {
    while(heap_size > 1) {
        node* nd1 = extract_min();
        node* nd2 = extract_min();
        node* res = new node;
        res->symbol = '*';
        res->frequency = nd1->frequency + nd2->frequency;
        res->right = nd2;
        res->left = nd1;
        insert(res);
    }
    return extract_min();
}

std::unordered_map<char, std::string> priority_queue_min::encode(node *root) {
    std::unordered_map<char, std::string> huffmanCodes;

    if (root == NULL)
        return huffmanCodes;

    queue q;
    q.push(root, "");
    while (!q.isempty()) {
        qnode *tmp = q.front();
        qnode *u = new qnode(tmp->qn, tmp->next, tmp->code);
        q.del();

        if (u->qn->left == NULL && u->qn->right == NULL) {
            huffmanCodes[u->qn->symbol] = u->code;
            continue;
        }

        q.push(u->qn->left, u->code + "0");
        q.push(u->qn->right, u->code + "1");
        delete u;
    }

    return huffmanCodes;
}

int priority_queue_min::binar(char *argv_in, char *argv_out, std::unordered_map<char, std::string> codes) {
    std::ifstream in(argv_in);
    std::ofstream out(argv_out);
    char end = 0;
    int s = 7;
    char a;
    in >> std::noskipws;

    while(in >> a) {
        for(int i = 0; i < max_size; i++) {
            if (codes.find(a) != codes.end()) {
                for(char k: codes[a]) {
                    if (k == '1') {
                        end = 1 << s | end;
                        s--;
                    }
                    else if (k == '0') {
                        end = ~(1 << s) & end;
                        s--;
                    }
                    if (s < 0) {
                        out << end;
                        s = 7;
                        end = 0;
                    }
                }
            }
            break;
        }
    }
    if (s != 7)
        out << end;

    in.close();
    out.close();
    return s;
}

void priority_queue_min::decode(char *argv_in, char *argv_out, int number) const{
    std::ifstream in(argv_in);
    std::ofstream out(argv_out);
    node *tmp = heap[0];
    char ch1, ch2;
    bool flag = true;
    int numer = 0;

    in >> std::noskipws;
    in >> ch1;
    while (flag) {
        if (!(in >> ch2)) {
            numer = number + 1;
            flag = false;
        }
        for (int i = 7; i > -1 + numer; i--) {
            char ch_tmp = ((1 << i) & ch1) >> i;
            if (tmp->left != NULL || tmp->right != NULL) {
                if (ch_tmp == 0)
                    tmp = tmp->left;
                else if (ch_tmp == 1)
                    tmp = tmp->right;
            }
            if (tmp->left == NULL && tmp->right == NULL) {
                out << tmp->symbol;
                tmp = heap[0];
            }
        }
        ch1 = ch2;
    }
    in.close();
    out.close();
}