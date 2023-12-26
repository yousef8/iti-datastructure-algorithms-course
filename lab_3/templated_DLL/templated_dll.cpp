#include <iostream>
#include <cassert>
#include <initializer_list>

template <typename T>
class Node
{
public:
  Node *nxt;
  T data;
  Node *prv;

  Node() : data{}, nxt{nullptr}, prv{nullptr}
  {
  }

  Node(const T &_data) : data{_data}, nxt{nullptr}, prv{nullptr}
  {
  }
};

template <typename T>
class DLL
{
private:
  Node<T> *head;
  Node<T> *tail;
  int size;

  void link(Node<T> *head, Node<T> *tail)
  {
    if (head)
    {
      head->nxt = tail;
    }

    if (tail)
    {
      tail->prv = head;
    }

    return;
  }

  void debug_verify_data_integrity()
  {
    int length = size;
    if (length == 0)
    {
      assert(head == nullptr);
      assert(tail == nullptr);
    }
    else
    {
      assert(head != nullptr);
      assert(tail != nullptr);
      if (length == 1)
        assert(head == tail);
      else
        assert(head != tail);
      assert(!head->prv);
      assert(!tail->nxt);
    }
    int len = 0;
    for (Node<T> *cur{head}; cur; cur = cur->nxt, len++)
    {
      if (len == length - 1) // make sure we end at tail
        assert(cur == tail);
    }

    assert(length == len);
    // assert(length == (int)debug_data.size());

    len = 0;
    for (Node<T> *cur = tail; cur; cur = cur->prv, len++)
    {
      if (len == length - 1) // make sure we end at head
        assert(cur == head);
    }
  }

public:
  DLL() : head{nullptr}, tail{nullptr}, size{0}
  {
  }

  DLL(const std::initializer_list<T> &lst) : head{nullptr}, tail{nullptr}, size{0}
  {
    for (const T &e : lst)
    {
      add(e);
    }
  }

  DLL(DLL<T> &other) : DLL{}
  {
    for (Node<T> *cur{other.head}; cur; cur = cur->nxt)
    {
      add(cur->data);
    }
  }

  void add(const T &data)
  {
    Node<T> *node = new Node<T>{data};
    link(tail, node);

    if (!head)
    {
      head = node;
    }

    tail = node;

    ++size;

    debug_verify_data_integrity();
  }

  void display()
  {
    std::cout << "NULL <-> ";
    for (Node<T> *ptr{head}; ptr; ptr = ptr->nxt)
    {
      std::cout << ptr->data << " <-> ";
    }

    std::cout << "NULL\n";
  }
};

int main()
{
  DLL<std::string> dll{"yousef", "omar", "muhammed"};

  dll.display();

  DLL<std::string> dllCpy{dll};

  dllCpy.display();

  return 0;
}