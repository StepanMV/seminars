#include <memory>
#include <stdexcept>

template<typename T>
class ForwardList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    std::unique_ptr<Node> head;

public:
    void pushFront(const T& value) {
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(head);
        head = std::move(newNode);
    }

    void popFront() {
        if (head) {
            head = std::move(head->next);
        }
    }

    bool empty() const {
        return head == nullptr;
    }

    const T& front() const {
        if (head) {
            return head->data;
        }
        throw std::runtime_error("List is empty");
    }
};
