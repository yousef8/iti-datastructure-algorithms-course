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

  ~Node()
  {
    std::cout << "Destroy value [" << data << "] at address [" << this << "]\n";
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

  Node<T> *search(const T &value)
  {
    for (Node<T> *cur{head}; cur; cur = cur->nxt)
    {
      if (cur->data == value)
      {
        return cur;
      }
    }

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
      add(new_value);
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
};

template <typename T>
void test_deletion(DLL<T> dll)
{
  std::cout << "\n-------------Deletion Feature------------------\n";
  std::cout << "Original DLL : \n";
  dll.display();
  std::cout << std::endl;

  // Test Delete Feature
  // Delete Middle
  std::cout << "Delete Middle Element : \n";
  dll.erase("omar");
  dll.display();
  std::cout << std::endl;

  // Delete Head
  std::cout << "Delete Head Element : \n";
  dll.erase("yousef");
  dll.display();
  std::cout << std::endl;

  // Delete Tail
  std::cout << "Delete Tail Element : \n";
  dll.erase("muhammed");
  dll.display();
  std::cout << std::endl;

  return;
}

template <typename T>
void test_insert_after(DLL<T> dll)
{
  std::cout << "\n----------------Test Insertion After Value--------------------\n";
  std::cout << "Current DLL : ";
  dll.display();

  std::cout << "\nInsert after head: \n";
  dll.insert_after("yousef", "mahmoud");
  dll.display();

  std::cout << "\nInsert after tail: \n";
  dll.insert_after("muhammed", "mazen");
  dll.display();

  std::cout << "\nInsert in middle: \n";
  dll.insert_after("mahmoud", "fathi");
  dll.display();
  std::cout << std::endl;

  return;
}

template <typename T>
void test_insert_idx(DLL<T> dll)
{
  std::cout << "\n----------------Test Insertion @ idx-------------------\n";
  std::cout << "Current DLL : ";
  dll.display();
  std::cout << std::endl;

  std::cout << "Insert @ head : \n";
  dll.insert_at_idx(0, "sayed");
  dll.display();
  std::cout << std::endl;

  std::cout << "Insert @ tail : \n";
  dll.insert_at_idx(3, "mazen");
  dll.display();
  std::cout << std::endl;

  std::cout << "Insert @ middle (e.g. 3) : \n";
  dll.insert_at_idx(3, "mahmoud");
  dll.display();
  std::cout << std::endl;

  return;
}

int main()
{

  // Test Add, Display, and Constructor feature
  std::cout << "\n------------------------Create DLL && Add elements-------------------\n";
  DLL<std::string> dll{"yousef", "omar", "muhammed"};
  dll.display();

  // Test copy Costructor
  std::cout
      << "\n---------------------------Copy DLL------------------------------\n";
  DLL<std::string> dllCpy{dll};
  std::cout << "Copied DLL : \n";
  dllCpy.display();

  // Test Search feature
  std::cout << "\n---------------------Search Feature-----------------\n";
  const Node<std::string> *res = dll.search("yousef");
  if (!res)
  {
    std::cout << "Didn't find anything\n";
  }
  else
  {
    std::cout << "Found a node with value " << res->data << std::endl;
  }
  std::cout << std::endl;

  test_deletion(dll);

  test_insert_after(dll);

  test_insert_idx(dll);
  return 0;
}