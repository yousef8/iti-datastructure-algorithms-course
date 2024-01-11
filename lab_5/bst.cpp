#include <iomanip>
#include <iostream>

#define COUNT 3

template <typename T>
class Node {
  public:
  Node<T>* right;
  T data;
  Node<T>* left;

  Node(): right {nullptr}, data {}, left{nullptr}
  {}

  Node(T _data) : right {nullptr}, data {_data}, left{nullptr}
  {}

  ~Node() {
    std::cout << "Node with data [" << data << "] was destroyed\n";
  }
};

template <typename T>
class BST {
  public:
    BST(): root {nullptr}
    {}

    Node<T>* insert(Node<T>* root, T data){
      if(!root){
        return new Node<T> {data};
      }

      if(data <= root->data){
        root->left = insert(root->left, data);
      }
      else {
        root->right = insert(root->right, data);
      }

      return root;

    }

    void insert(T data){
      root = insert(root, data);
      return;
    }

  void print2DUtil(Node<T>* root, int space)
  {
      // Base case
      if (root == NULL)
          return;
   
      // Increase distance between levels
      space += COUNT;
   
      // Process right child first
      print2DUtil(root->right, space);
   
      // Print current node after space
      // count
      std::cout << std::endl;
      for (int i = COUNT; i < space; i++)
          std::cout << " ";
      std::cout << root->data << "";
   
      // Process left child
      print2DUtil(root->left, space);
  }
   
  // Wrapper over print2DUtil()
  void print()
  {
      // Pass initial space count as 0
      print2DUtil(root, 0);
      std::cout << std::endl;
  }

  private:
    Node<T>* root;
};

int main() {
  BST<int> t {};
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

    t.print();

    return 0;
}
