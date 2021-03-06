#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;
//Constructor
Node::Node(int v) {
  color = 0;
  value = v;
  Lchild = NULL;
  Rchild = NULL;
  parent = NULL;
}
//Deconstructor
Node::~Node() {
  
}
//Set the left child
void Node::setLchild(Node* child) {
  Lchild = child;
}
//Set the right child
void Node::setRchild(Node* child) {
  Rchild = child;
}
//Get the left child
Node* Node::getLchild() {
  return Lchild;
}
//Get the right child
Node* Node::getRchild() {
  return Rchild;
}
//Get the value
int Node::getValue() {
  return value;
}
//Change value of a node
void Node::setValue(int v) {
  value = v;
}
//Get the color
int Node::getColor() {
  return color;
}
void Node::setColor(int a) {
  color = a;
}
Node* Node::getParent() {
  return parent;
}
void Node::setParent(Node* a) {
  parent = a;
}
