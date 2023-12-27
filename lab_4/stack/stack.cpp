#include <iostream>
#include <initializer_list>
#include <string>

template <typename T>
class Node
{
public:
  Node *nxt;
  T data;

  Node() : data{}, nxt{nullptr}
  {
  }

  Node(const T &_data) : data{_data}, nxt{nullptr}
  {
  }
};

template <typename T>
class Stack
{
public:
  Stack() : tos{nullptr}, size{0}
  {
  }

  Stack(const std::initializer_list<T> &lst) : Stack()
  {
    for (auto &e : lst)
    {
      push(e);
    }
  }

  ~Stack()
  {
    Node<T> *node_to_delete{nullptr};

    for (Node<T> *cur{tos}; cur;)
    {
      node_to_delete = cur;
      cur = cur->nxt;
      delete node_to_delete;
    }
  }

  int is_empty()
  {
    return (!(size > 0));
  }

  void push(const T &data)
  {
    Node<T> *new_node = new Node<T>{data};

    if (!tos)
    {
      tos = new_node;
      ++size;
      return;
    }

    new_node->nxt = tos;
    tos = new_node;
    ++size;

    return;
  }

  T pop()
  {

    if (is_empty())
    {
      return T{};
    }
    Node<T> *node_to_delete = tos;

    T data = node_to_delete->data;

    tos = tos->nxt;
    --size;

    return data;
  }

  void reverse()
  {

    Node<T> *prv_node{nullptr};
    Node<T> *cur_node{tos};
    Node<T> *nxt_node{nullptr};
    while (cur_node)
    {
      // Secure access to next node
      nxt_node = cur_node->nxt;

      // Reverse the node
      cur_node->nxt = prv_node;

      // Advance the current and previous nodes
      prv_node = cur_node;
      cur_node = nxt_node;
    }

    tos = prv_node;

    return;
  }

  void print()
  {
    if (!tos)
    {
      std::cout << "Empty\n";
    }

    std::cout << "tos [" << tos->data << "] -> ";
    for (Node<T> *cur{tos->nxt}; cur; cur = cur->nxt)
    {
      std::cout << cur->data << " -> ";
    }

    std::cout << "NULL\tsize : " << size << "\n";

    return;
  }

private:
  Node<T> *tos;
  int size;
};

int main()
{
  Stack<std::string> stack{"yousef", "omar", "muhammed"};
  stack.print();
  std::cout << "Is Empty : " << (stack.is_empty() ? "True" : "False") << "\n";
  std::cout << std::endl;

  stack.reverse();

  std::cout << "Stack Reversed : ";
  stack.print();
  std::cout << std::endl;

  std::cout << "Pop the stack: \n";
  std::cout << "You just popped : " << stack.pop() << "\n";
  std::cout << "You just popped : " << stack.pop() << "\n";
  std::cout << "You just popped : " << stack.pop() << "\n";
  std::cout << "You just popped : " << stack.pop() << "\n";

  return 0;
}