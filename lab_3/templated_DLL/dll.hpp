#include <iostream>
#include <cassert>
#include <initializer_list>
#include <string>

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
      append(e);
    }
  }

  DLL(DLL<T> &other) : DLL{}
  {
    for (Node<T> *cur{other.head}; cur; cur = cur->nxt)
    {
      append(cur->data);
    }
    debug_verify_data_integrity();
  }

  ~DLL()
  {
    Node<T> *node_to_delete = nullptr;
    Node<T> *cur{head};

    while (cur)
    {
      node_to_delete = cur;
      cur = cur->nxt;
      delete node_to_delete;
    }
  }

  void append(const T &data)
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
    return;
  }

  T delete_back() {
    if(head == nullptr && tail == nullptr){
      return T{};
    }

    Node<T>* node_to_delete = tail;
    T data = tail->data;

    tail = tail->prv;

    if (head == node_to_delete)
    {
      head = node_to_delete->nxt;
    }

    if(tail){
      tail->nxt = nullptr;
    }

  
    --size;
    delete node_to_delete;
    debug_verify_data_integrity();

    return data;
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

  Node<T> *search(const T &value)
  {
    for (Node<T> *cur{head}; cur; cur = cur->nxt)
    {
      if (cur->data == value)
      {
        return cur;
      }
    }
    
    debug_verify_data_integrity();
    return nullptr;
  }

  void erase(const T &value)
  {
    const Node<T> *node_to_delete = search(value);

    // No match found
    if (!node_to_delete)
    {
      return;
    }

    // Match found
    if (head == node_to_delete)
    {
      head = node_to_delete->nxt;
    }

    if (tail == node_to_delete)
    {
      tail = node_to_delete->prv;
    }

    link(node_to_delete->prv, node_to_delete->nxt);
    --size;
    delete node_to_delete;

    debug_verify_data_integrity();
    return;
  }

  void insert_after(const T &search_value, const T &new_value)
  {
    Node<T> *node_found = search(search_value);

    // No match found
    if (!node_found)
    {
      return;
    }

    Node<T> *new_node = new Node<T>{new_value};

    link(new_node, node_found->nxt);
    link(node_found, new_node);

    if (tail == node_found)
    {
      tail = tail->nxt;
    }
    ++size;

    debug_verify_data_integrity();
    return;
  }

  void insert_at_idx(int idx, const T &new_value)
  {
    // Handle insertion in empty DLL
    if (0 == idx && 0 == size)
    {
      append(new_value);
      return;
    }

    // Assure index is in range
    assert((0 <= idx && idx < size));

    // Get the current node at idx
    Node<T> *cur_node = head;
    for (int i{0}; i < idx; ++i)
    {
      cur_node = cur_node->nxt;
    }

    Node<T> *new_node = new Node<T>{new_value};

    link(cur_node->prv, new_node);
    link(new_node, cur_node);

    if (head == cur_node)
    {
      head = head->prv;
    }

    ++size;

    debug_verify_data_integrity();
    return;
  }

  void reverse()
  {
    for (Node<T> *cur{head}; cur; cur = cur->prv)
    {
      Node<T> *tmp = cur->nxt;
      cur->nxt = cur->prv;
      cur->prv = tmp;
    }

    std::swap(head, tail);
    debug_verify_data_integrity();
    return;
  }
};

