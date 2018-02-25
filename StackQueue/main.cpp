#include <iostream>
#include <vector>
#include "stack"
#include "stdexcept"

using namespace std;

// Stack: FILO
// Queue: FIFO
template <typename T>
class StackQueue
{
public:
    StackQueue() = default;
    ~StackQueue(){}

    void appendTail(const T& node);
    T deleteHead();

private:
    stack<T> stack1;
    stack<T> stack2;
};

template <typename T>
void StackQueue<T>::appendTail(const T &node)
{
    stack1.push(node);
}

template <typename T>
T StackQueue<T>::deleteHead()
{
    // First pop from stack1 and push into stack2
    while(!stack1.empty())
    {
        T& temp = stack1.top();
        stack2.push(temp);
        stack1.pop();
    }

    if (stack2.empty())
        throw  runtime_error("No elements existing.");

    T Value = stack2.top();
    stack2.pop();

    return Value;
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    StackQueue<int> sq;
    sq.appendTail(6);
    sq.appendTail(2);
    sq.appendTail(3);

    int n = sq.deleteHead();
    cout << "Head = " << n << endl;

    return 0;
}
