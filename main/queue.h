#include <string>

struct node {
    char symbol;
    int frequency;
    node *left;
    node *right;
};

struct qnode {
    node *qn;
    qnode *next;
    std::string code;

    qnode(node *v, qnode *u, std::string str) : qn(v), next(u), code(str) {}
};

class queue {
private:
    qnode *head;
    qnode *tail;
public:
    queue();
    ~queue();
    void push(node *, std::string);
    void del();
    qnode *front();
    bool isempty() const;
};
