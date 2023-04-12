struct Node {
    int val;
    Node* next;
    Node(int _val);
};

struct MyList {
    Node* first;
    Node* last;

    MyList();

    bool is_empty();
    void add(int _val);
    void add(const int index, int _val);
    void print();
    int indexOf(int _val);
    void removeFirst();
    void removeLast();
    void remove(int _val);
    void removeAt(const int index);

    Node* operator[] (const int index);
};
