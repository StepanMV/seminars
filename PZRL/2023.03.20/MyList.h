template <typename T>
struct Node {
    T val;
    Node<T>* next;
    Node<T>(T _val);
};

template <typename T>
struct MyList {
    Node<T>* first;
    Node<T>* last;

    MyList();

    bool is_empty();
    void push_back(T _val);
    void print();
    Node<T>* find(T _val);
    void remove_first();
    void remove_last();
    void remove(T _val);

    Node* operator[] (const int index);
};
