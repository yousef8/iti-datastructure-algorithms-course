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

  Node<T> *findMinNode(Node<T> *root) {
    if (!root->left) {
      return root;
    }
    return findMinNode(root->left);
  }

  Node<T> *deleteNode(Node<T> *root, T valueDel) {
    if (!root) {
      return nullptr;
    }

    if (valueDel < root->data) {
      root->left = deleteNode(root->left, valueDel);
      return root;
    }

    if (valueDel > root->data) {
      root->right = deleteNode(root->right, valueDel);
      return root;
    }

    // We found the node

    // Handle Leaf Node
    if (!root->left && !root->right) {
      delete root;
      return nullptr;
    }

    // Handle Node with Left Child Only
    if (!root->right) {
      Node<T> *delNode = root;
      root = root->left;
      delete delNode;
      return root;
    }

    // Handle Node with Right Child Only
    if (!root->left) {
      Node<T> *delNode = root;
      root = root->right;
      delete delNode;
      return root;
    }

    // Handle Node with both children
    Node<T> *rightSubTreeMinNode = findMinNode(root->right);
    rightSubTreeMinNode->left = root->left;

    Node<T> *delNode = root;
    root = root->right;
    delete delNode;
    return root;
  }

  void deleteNode(T valueDel) {
    root = deleteNode(root, valueDel);
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
  std::cout << "\n****************" << std::endl;
  t.deleteNode(70);
  t.inOrder();
  std::cout << "Nodes Count : " << t.count() << std::endl;

  std::cout << "\n****************" << std::endl;
  t.deleteNode(65);
  t.inOrder();
  std::cout << "Nodes Count : " << t.count() << std::endl;

  std::cout << "\n****************" << std::endl;
  t.deleteNode(30);
  t.inOrder();
  std::cout << "Nodes Count : " << t.count() << std::endl;

  std::cout << "\n****************" << std::endl;
  t.deleteNode(50);
  t.inOrder();
  std::cout << "Nodes Count : " << t.count() << std::endl;

  std::cout << "\n****************" << std::endl;
  t.deleteNode(99);
  t.inOrder();
  std::cout << "Nodes Count : " << t.count() << std::endl;

  return 0;
}
