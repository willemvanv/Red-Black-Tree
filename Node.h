#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std;

class Node {
 public:
  Node(int v);
  ~Node();
  void setLchild(Node* child);
  void setRchild(Node* child);
  Node* getLchild();
  Node* getRchild();
  int getValue();
  void setValue(int v);
  int getColor();
  void setColor(int a);
  Node* getParent();
  void setParent(Node* a);
 private:
  int color;
  int value;
  Node* Lchild;
  Node* Rchild;
  Node* parent;
};
#endif
