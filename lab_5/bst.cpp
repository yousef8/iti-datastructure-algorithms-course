#include <iostream>

#define COUNT 3

template <typename T> class Node {
public:
  Node<T> *right;
  T data;
  Node<T> *left;

  Node() : right{nullptr}, data{}, left{nullptr} {}

  Node(T _data) : right{nullptr}, data{_data}, left{nullptr} {}

  ~Node() { std::cout << "Node with data [" << data << "] was destroyed\n"; }
};

template <typename T> class BST {
public:
  BST() : root{nullptr} {}

  Node<T> *insert(Node<T> *root, T data) {
    if (!root) {
      return new Node<T>{data};
    }

    if (data <= root->data) {
      root->left = insert(root->left, data);
    } else {
      root->right = insert(root->right, data);
    }

    return root;
  }

  void insert(T data) {
    root = insert(root, data);
    return;
  }

  T getMax(Node<T> *root) {
    if (root->right) {
      return getMax(root->right);
    }

    return root->data;
  }

  T getMax() { return getMax(root); }

  T getMin(Node<T> *root) {
    if (root->left) {
      return getMin(root->left);
    }

    return root->data;
  }

  T getMin() { return getMin(root); }

  int getHeight(Node<T> *root) {
    if (!root) {
      return -1;
    }

    return std::max(getHeight(root->left), getHeight(root->right)) + 1;
  }

  int getHeight() { return getHeight(root); }

  int count(Node<T> *root) {
    if (!root) {
      return 0;
    }

    return count(root->left) + count(root->right) + 1;
  }

  int count() { return count(root); }

  void inOrder(Node<T> *root) {
    if (!root)
      return;

    inOrder(root->left);
    std::cout << root->data << " ";
    inOrder(root->right);
    return;
  }

  void inOrder() {
    inOrder(root);
    std::cout << std::endl;
    return;
  }

  Node<T> *getParent(T searchData) {
    Node<T> *searchRoot{root};
    Node<T> *parent{searchRoot};

    while (searchRoot) {
      if (searchData == searchRoot->data) {
        return parent;
      }

      if (searchData < searchRoot->data) {
        parent = searchRoot;
        searchRoot = searchRoot->left;
      }

      if (searchData > searchRoot->data) {
        parent = searchRoot;
        searchRoot = searchRoot->right;
      }
    }

    return parent;
  }

  void deleteNode(T valueDel) {
    Node<T> *parentNode = getParent(valueDel);
    Node<T> *nodeDel{nullptr};
    Node<T> **parentNodeHook{nullptr};

    if (valueDel < parentNode->data) {
      nodeDel = parentNode->left;
      parentNodeHook = &parentNode->left;
    }

    if (valueDel > parentNode->data) {
      nodeDel = parentNode->right;
      parentNodeHook = &parentNode->right;
    }

    // Handle Leaf Node
    if (!nodeDel->left && !nodeDel->right) {
      *(parentNodeHook) = nullptr;
      delete nodeDel;
      return;
    }

    // Handle Node with Left Child Only
    if (!nodeDel->right) {
      *(parentNodeHook) = nodeDel->left;
      delete nodeDel;
      return;
    }

    // Handle Node with Right Child Only
    if (!nodeDel->left) {
      *(parentNodeHook) = nodeDel->right;
      delete nodeDel;
      return;
    }

    *(parentNodeHook) = nodeDel->right;
    Node<T> *treeTail = *(parentNodeHook);

    while (treeTail->left) {
      treeTail = treeTail->left;
    }

    treeTail->left = nodeDel->left;
    delete nodeDel;

    return;
  }

private:
  Node<T> *root;
};

int main() {
  BST<int> t{};
  t.insert(50);
  t.insert(60);
  t.insert(30);
  t.insert(25);
  t.insert(40);
  t.insert(35);
  t.insert(70);
  t.insert(65);
  ////////////////////////////////////////////////////////////////
  t.insert(11);
  t.insert(27);
  t.insert(26);
  t.insert(29);
  t.insert(45);
  t.inOrder();

  std::cout << "Nodes Count : " << t.count() << std::endl;
  std::cout << "Tree Height : " << t.getHeight() << std::endl;
  std::cout << "Minimum value is : " << t.getMin() << std::endl;
  std::cout << "Maximum value is : " << t.getMax() << std::endl;

  std::cout << "****************" << std::endl;
  Node<int> *Node = t.getParent(65);

  if (Node) {
    std::cout << "Parent of 65=" << Node->data << std::endl;
  } else {
    std::cout << "This node doesn't exist\n";
  }
  std::cout << "****************" << std::endl;

  t.deleteNode(70);
  t.inOrder();
  std::cout << "****************" << std::endl;

  t.deleteNode(65);
  t.inOrder();

  t.deleteNode(30);
  t.inOrder();
  std::cout << "****************" << std::endl;
  std::cout << t.count() << std::endl;
  return 0;
}
