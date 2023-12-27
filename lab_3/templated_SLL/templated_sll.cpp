#include <iostream>
#include <string>
#include <initializer_list>
#include <cassert>

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

  ~Node()
  {
    std::cout << "Destroy value [" << data << "] at address [" << this << "]\n";
  }
};

template <typename T>
class SLL
{
public:
  SLL() : head{nullptr}, tail{nullptr}, size{0}
  {
  }

  SLL(const std::initializer_list<T> &lst) : SLL()
  {
    for (const T &e : lst)
    {
      append(e);
    }
  }

  SLL(SLL<T> &other) : SLL{}
  {
    for (Node<T> *cur{other.head}; cur; cur = cur->nxt)
    {
      append(cur->data);
    }
  }

  ~SLL()
  {
    Node<T> *node_to_delete{nullptr};

    for (Node<T> *cur{head}; cur;)
    {
      node_to_delete = cur;
      cur = cur->nxt;
      delete node_to_delete;
    }
  }

  void append(const T &value)
  {
    Node<T> *node = new Node<T>{value};
    if (!head)
    {
      head = node;
      tail = node;
      ++size;
      debug_verify_data_integrity();
      return;
    }

    assert(head != nullptr);
    assert(tail != nullptr);

    tail->nxt = node;
    tail = node;
    ++size;
    debug_verify_data_integrity();
    return;
  }

  void display()
  {
    for (Node<T> *cur{head}; cur; cur = cur->nxt)
    {
      std::cout << cur->data << " -> ";
    }
    std::cout << "NULL\n";
    return;
  }

  bool is_empty()
  {
    return (head == nullptr && tail == nullptr);
  }

  Node<T> *search(const T &search_value)
  {
    for (Node<T> *cur{head}; cur; cur = cur->nxt)
    {
      if (search_value == cur->data)
      {
        return cur;
      }
    }

    return nullptr;
  }

  const Node<T> *search(const T &search_value) const
  {
    for (Node<T> *cur{head}; cur; cur = cur->nxt)
    {
      if (search_value == cur->data)
      {
        return cur;
      }
    }

    return nullptr;
  }

  bool erase(const T &search_value)
  {
    Node<T> *node_to_del{nullptr};
    Node<T> *before_del_node{nullptr};

    for (Node<T> *cur{head}; cur && !node_to_del; cur = cur->nxt)
    {
      if (search_value == cur->data)
      {
        node_to_del = cur;
      }
      else
      {
        before_del_node = cur;
      }
    }

    // No match found
    if (!node_to_del)
    {
      return false;
    }

    // Match found
    if (head == node_to_del)
    {
      head = node_to_del->nxt;
    }

    if (tail == node_to_del)
    {
      tail = before_del_node;
      if (tail)
      {
        tail->nxt = nullptr;
      }
    }

    if (before_del_node)
    {
      before_del_node->nxt = node_to_del->nxt;
    }
    --size;
    delete node_to_del;

    debug_verify_data_integrity();
    return true;
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

    debug_verify_data_integrity();
    return;
  }

private:
  Node<T> *head;
  Node<T> *tail;
  int size;

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
      assert(!tail->nxt);
    }
    int len = 0;
    for (Node<T> *cur = head; cur; cur = cur->nxt, len++)
      assert(len < 10000); // Consider infinite cycle?
    assert(length == len);
    // assert(length == (int)debug_data.size());
  }
};

template <typename T>
void test_deletion(SLL<T> sll)
{
  std::cout << "-------------------Deletion Feature-------------------------------\n";
  std::cout << "Delete Middle : \n";
  sll.erase("omar");
  sll.display();
  std::cout << std::endl;

  std::cout << "Delete Head : \n";
  sll.erase("yousef");
  sll.display();
  std::cout << std::endl;

  std::cout << "Delete Tail : \n";
  sll.erase("muhammed");
  sll.display();
  std::cout << std::endl;

  return;
}

template <typename T>
void test_search(const SLL<T> &sll)
{
  std::cout << "-------------------Search Feature-------------------------------\n";
  std::cout << "Search for [yousef]\n";
  const Node<std::string> *res = sll.search("yousef");
  if (res)
  {
    std::cout << "Found [" << res->data << "]\n";
  }
  else
  {
    std::cout << "No match found\n";
  }
  std::cout << std::endl;

  std::cout << "Search for [fathi]\n";
  res = sll.search("fathi");
  if (res)
  {
    std::cout << "Found [" << res->data << "]\n";
  }
  else
  {
    std::cout << "No match found\n";
  }
  std::cout << std::endl;

  return;
}

template <typename T>
void test_reverse(SLL<T> sll)
{
  std::cout << "------------------Reverse Functionality---------------------\n";
  std::cout << "Current SLL  : ";
  sll.display();
  std::cout << std::endl;

  sll.reverse();
  std::cout << "Reversed SLL : ";
  sll.display();
  std::cout << std::endl;
  return;
}
int main()
{
  std::cout << "------------------Create SLL & Add Elements---------------------\n";
  SLL<std::string> sll{"yousef", "omar", "muhammed"};
  sll.display();
  std::cout << "Is Empty : " << (sll.is_empty() ? "True" : "False") << "\n";
  std::cout << std::endl;

  std::cout << "------------------Copy SLL By Value---------------------\n";
  SLL<std::string> sll_cpy{sll};
  sll_cpy.display();
  std::cout << "Is Empty : " << (sll_cpy.is_empty() ? "True" : "False") << "\n";
  std::cout << std::endl;

  test_search(sll);
  test_deletion(sll);

  test_reverse(sll);

  return 0;
}
