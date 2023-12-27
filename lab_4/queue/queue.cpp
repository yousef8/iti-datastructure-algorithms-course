#include <iostream>
#include <initializer_list>
#include <cassert>
#include <string>

template <typename T>
class Node
{
public:
  Node<T> *nxt;
  T data;

  Node() : data{}, nxt{nullptr}
  {
  }

  Node(const T &_data) : data{_data}, nxt{nullptr}
  {
  }

  ~Node()
  {
    std::cout << "Destroy [" << data << "] at address " << this << std::endl;
  }
};

template <typename T>
class Queue
{
public:
  Queue() : head{nullptr}, tail{nullptr}, size{0}
  {
  }

  Queue(const std::initializer_list<T> &lst) : Queue()
  {
    for (auto &e : lst)
    {
      enqueue(e);
    }
  }

  ~Queue()
  {
    while (head)
    {
      Node<T> *node_to_delete{head};

      head = head->nxt;
      --size;
      delete node_to_delete;
    }
    tail = nullptr;
  }

  int is_empty()
  {
    return !(size > 0);
  }

  void reverse()
  {
    Node<T> *prv_node{nullptr};
    Node<T> *cur_node{head};
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

    std::swap(head, tail);

    return;
  }

  void enqueue(const T &data)
  {
    Node<T> *node = new Node<T>{data};
    if (!head)
    {
      head = node;
      tail = node;
      ++size;
      return;
    }

    assert(head != nullptr);
    assert(tail != nullptr);

    tail->nxt = node;
    tail = node;
    ++size;
    return;
  }

  T dequeue()
  {
    if (is_empty())
    {
      return T{};
    }

    Node<T> *node_to_delete = head;
    head = head->nxt;
    --size;

    T data = node_to_delete->data;
    delete node_to_delete;

    return data;
  }

  void print()
  {
    for (Node<T> *cur{head}; cur; cur = cur->nxt)
    {
      std::cout << cur->data << " -> ";
    }

    std::cout << "NULL\t";
    std::cout << "size : " << size << "\n";
  }

private:
  Node<T> *head;
  Node<T> *tail;
  int size;
};

int main()
{
  Queue<std::string> queue{"yousef", "omar", "muhammed"};
  std::cout << "Current Queue : ";
  queue.print();

  std::cout << "Reverse\n";
  queue.reverse();
  queue.print();

  std::cout << "Dequeue the whole queue : \n";
  std::cout << "You just dequeued : " << queue.dequeue() << "\n";
  std::cout << "You just dequeued : " << queue.dequeue() << "\n";
  std::cout << "You just dequeued : " << queue.dequeue() << "\n";
  std::cout << "You just dequeued : " << queue.dequeue() << "\n";

  return 0;
}