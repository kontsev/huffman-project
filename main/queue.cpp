#include "queue.h"

queue::queue() : head(NULL), tail(NULL) {}

queue::~queue() {
    qnode *tmp = head;
    while (tmp != NULL) {
        qnode *tmp_n = tmp->next;
        delete tmp;
        tmp = tmp_n; 
    }
}

void queue::push(node *v, std::string str) {
    qnode *new_node = new qnode(v, NULL, str);

    if (head == NULL)
        head = tail = new_node;
    else {
        tail->next = new_node;
        tail = new_node;
    }
}

void queue::del() {
    qnode *tmp = head;
    head = head->next;
    delete tmp;
}

qnode* queue::front() {
    return head;
}

bool queue::isempty() const{
    if (head == NULL)
        return true;
    return false;
}
