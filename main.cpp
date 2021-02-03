//Willem van Veldhuisen
//12/29/20
//Red-Black Tree

#include <iostream>
#include <cstring>
#include "Node.h"
#include <fstream>

using namespace std;

//Functions
void add(Node** head);
void Add(Node** head, int value);
Node* addValue(int a, Node** current);
void Read(Node** head);
void Print(Node* current, int dist);
void Update(Node** node, Node** head);
Node* getParent(Node* current, int val);
Node* getUncle(Node* current, int val);
Node* find(Node* current, int val);
void removal(Node* node, Node** head);
void remove(Node** head);
Node* goRight(Node* current);
void replace(Node* parent, Node* node, Node* child);
Node* getSibling(Node* current, Node* node);
void removeCase1(Node* node, Node** head, Node* parent, Node* s);
void removeCase2(Node* node, Node** head, Node* parent, Node* s);
void removeCase3(Node* node, Node** head, Node* parent, Node* s);
void removeCase4(Node* node, Node** head, Node* parent, Node* s);
void removeCase5(Node* node, Node** head, Node* parent, Node* s);
void removeCase6(Node* node, Node** head, Node* parent, Node* s);
void findf(Node** head);
void rotateR(Node* node, Node** head);
void rotateL(Node* node, Node** head);
void replace(Node* node, Node* child, Node** head);

int main() {
  //Variables
  Node* head = NULL;
  const int RED = 0;
  const int BLACK = 1;
  //Commands
  cout << "commands: add, read, print, find, remove, quit" << endl;
  while (1) {
    char* input;
    input = new char[10];
    cin.getline(input, 10);
    if (strcmp(input, "add") == 0) {
      add(&head);
    }
    if (strcmp(input, "read") == 0) {
      Read(&head);
    }
    if (strcmp(input, "print") == 0) {
      Print(head, 0);
    }
    if (strcmp(input, "find") == 0) {
      findf(&head);
    }
    if (strcmp(input, "remove") == 0) {
      remove(&head);
    }
    if (strcmp(input, "quit") == 0) {
      break;
    }
  }
  return 0;
}
//Get single value to add
void add(Node** head) {
  cout << "enter value" << endl;
  int input;
  cin >> input;
  Add(head, input);
}
//Add single value
void Add(Node** head, int value) {
  Node* a = addValue(value, head);
  Update(&a, head);
  if (*head != a) {
    Node* temp = getParent(*head, a->getValue());
    a->setParent(temp);
  }
}
//Add a value to the tree using binary search
Node* addValue(int a, Node** current) {
  Node* temp;
  //If the head is empty fill it in
  if (*current == NULL) {
    *current = new Node(a);
    return *current;
  }
  //If a is less than the current value it goes to the left
  else if ((*current)->getValue() > a) {
    if ((*current)->getLchild() == NULL) {
      (*current)->setLchild(new Node(a));
      return (*current)->getLchild();
    }
    else {
      temp = (*current)->getLchild();
      addValue(a, &temp);
    }
  }
  //If a is greater than the current value it goes to the right
  else if ((*current)->getValue() < a) {
    if ((*current)->getRchild() == NULL) {
      (*current)->setRchild(new Node(a));
      return (*current)->getRchild();
    }
    else {
      temp = (*current)->getRchild();
      addValue(a, &temp);
    }
  }
}
void Update(Node** node, Node** head) {
  //Case 1: node is root, turn to black
  if (*node == *head) {
    (*node)->setColor(1);
  }
  //Case 2: node's parent is black, do nothing
  else if (getParent(*head, (*node)->getValue())->getColor() == 1) {
    //Do nothing, tree is valid
  }
  //Case 3: node's uncle and parent are red, switch colors of node, parent, uncle, and grandparent
  //and run grandparent through all 4 cases
  else if (getUncle(*head, getParent(*head, (*node)->getValue())->getValue()) != NULL &&
	   getUncle(*head, getParent(*head, (*node)->getValue())->getValue())->getColor() == 0) {
    getParent(*head, (*node)->getValue())->setColor(1);
    getUncle(*head, getParent(*head, (*node)->getValue())->getValue())->setColor(1);
    Node* grandparent = getParent(*head, getParent(*head, (*node)->getValue())->getValue());
    grandparent->setColor(0);
    Update(&grandparent, head);
  }
  //Case 4: node's parent is red and the uncle is black, shift
  else {
    Node* grandparent = getParent(*head, getParent(*head, (*node)->getValue())->getValue());
    Node* parent = getParent(*head, (*node)->getValue());
    if ((grandparent->getLchild() == parent && parent->getRchild() == *node) ||
	(grandparent->getRchild() == parent && parent->getLchild() == *node)) {
      if (parent->getLchild() == *node) {
	rotateR(parent, head);
      }
      else {
	rotateL(parent, head);
      }
      if ((*node)->getLchild() == parent) {
	rotateR(grandparent, head);
      }
      else {
	rotateL(grandparent, head);
      }
      grandparent->setColor(0);
      (*node)->setColor(1);
    }
    else {
      if (parent->getLchild() == *node) {
	rotateR(grandparent, head);
      }
      else {
	rotateL(grandparent, head);
      }
      grandparent->setColor(0);
      parent->setColor(1);
    }
  }
}
//Read file of values and read them into the tree
void Read(Node** head) {
  cout << "enter file name" << endl;
  char fileName[30];
  cin.getline(fileName, 30);
  fstream file;
  file.open (fileName);
  while(!file.eof()) {
    int input = -1;
    file >> input;
    //Run individual value through Add function
    if (input != -1) {
      Add(head, input);
    }
    else
      break;
  }
}
//Print visual representation of the tree
void Print(Node* current, int dist) {
  if (current == NULL) {
    return;
  }
  dist += 5;
  //cout << "dist: " << dist << endl;
  Print(current->getRchild(), dist);
  cout << endl;
  for (int i = 2; i < dist; i++) {
    cout << ' ';
  }
  cout << current->getValue();
  if (current->getColor() == 0) {
    cout << 'R';
  }
  else {
    cout << 'B';
  }
  cout << "\n";
  Print(current->getLchild(), dist);
}
//Get parent of a node
Node* getParent(Node* current, int val) {
  if (current == NULL) {
    return NULL;
  }
  if (current->getValue() == val) {
      return NULL;
  }
  if (current->getValue() > val) {
    if (current->getLchild()->getValue() == val) {
      return current;
    }
    else {
      return getParent(current->getLchild(), val);
    }
  }
  else if (current->getValue() < val) {
    if (current->getRchild()->getValue() == val) {
      return current;
    }
    else {
      return getParent(current->getRchild(), val);
    }
  }
  return NULL;
}
//Get uncle of a node
Node* getUncle(Node* current, int val) {
  if (current->getValue() > val) {
    if (current->getLchild()->getValue() == val) {
      return current->getRchild();
    }
    else if (current->getLchild() != NULL) {
      return getUncle(current->getLchild(), val);
    }
    else {
      return NULL;
    }
  }
  else if (current->getValue() < val) {
    if (current->getRchild()->getValue() == val) {
      return current->getLchild();
    }
    else if (current->getRchild() != NULL) {
      return getUncle(current->getRchild(), val);
    }
    else {
      return NULL;
    }
  }
}
Node* find(Node* current, int val) {
  if (current == NULL) {
    return NULL;
  }
  else if (current->getValue() == val) {
    return current;
  }
  else if (current->getValue() > val) {
    return find(current->getLchild(), val);
  }
  else if (current->getValue() < val) {
    return find(current->getRchild(), val);
  }
}
Node* goRight(Node* current) {
  if (current->getRchild() == NULL) {
    return current;
  }
  else {
    goRight(current->getRchild());
  }
}
void replace(Node* parent, Node* node, Node* child) {
  if (parent->getLchild() == node) {
    parent->setLchild(child);
  }
  else {
    parent->setRchild(child);
  }
}
Node* getSibling(Node* node) {
  if (node->getParent() != NULL) {
    if (node->getParent()->getLchild() == node && node->getParent()->getRchild() != NULL) {
      return node->getParent()->getRchild();
    }
    else if (node->getParent()->getLchild() != NULL){
      return node->getParent()->getLchild();
    }
  }
  return NULL;
}
void findf(Node** head) {
  cout << "enter value" << endl;
  int a;
  cin >> a;
  if (find(*head, a) != NULL) {
    cout << "value exists" << endl;
  }
  else {
    cout << "value does not exist" << endl;
  }
}
void rotateR(Node* node, Node** head) {
  Node* left = node->getLchild();
  Node* right = node->getRchild();
  if (left->getRchild() != NULL) {
    Node* temp = left->getRchild();
    left->setRchild(node);
    node->setLchild(temp);
    temp->setParent(node);
  }
  else {
    left->setRchild(node);
    node->setLchild(NULL);
  }
  if (node->getParent() != NULL) {
    Node* temp = node->getParent();
    if (node->getParent()->getRchild() == node) {
      node->getParent()->setRchild(left);
    }
    else {
      node->getParent()->setLchild(left);
    }
    left->setParent(temp);
  }
  else {
    *head = left;
    left->setParent(NULL);
  }
  node->setParent(left);
}
void rotateL(Node* node, Node** head) {
  Node* left = node->getLchild();
  Node* right = node->getRchild();
  if (right->getLchild() != NULL) {
    Node* temp = right->getLchild();
    right->setLchild(node);
    node->setRchild(temp);
    temp->setParent(node);
  }
  else {
    right->setLchild(node);
    node->setRchild(NULL);
  }
  if (node->getParent() != NULL) {
    Node* temp = node->getParent();
    if (node->getParent()->getRchild() == node) {
      node->getParent()->setRchild(right);
    }
    else {
      node->getParent()->setLchild(right);
    }
    right->setParent(temp);
  }
  else {
    *head = right;
    right->setParent(NULL);
  }
  node->setParent(right);
}

void remove(Node** head) {
  cout << "enter value of node you want to delete" << endl;
  int a;
  cin >> a;
  if (find(*head, a) == NULL) {
    cout << "value does not exist" << endl;
  }
  else {
    removal(find(*head, a), head);
  }
}
void removal(Node* node, Node** head) {
  Node* parent = node->getParent();
  Node* grandparent = NULL;
  if (parent != NULL) {
    grandparent = parent->getParent();
  }
  if (node->getLchild() != NULL && node->getRchild() != NULL) {
    Node* replacement = goRight(node->getLchild());
    Node* replacementParent = replacement->getParent();
    if (replacementParent == node) {
      node->setValue(replacement->getValue());
      node->setLchild(NULL);
      replacement->~Node();
      node->getRchild()->setColor(0);
    }
    else {
      if (replacement->getLchild() != NULL) {
	node->setValue(replacement->getValue());
	Node* temp = replacement->getLchild();
	replacement->setLchild(NULL);
	replacement->setValue(temp->getValue());
        temp->~Node();
      }
      else {
	node->setValue(replacement->getValue());
	replacementParent->setRchild(NULL);
	replacement->~Node();
      }
    }
  }
  else {
    Node* s = NULL;
    if (getSibling(node) != NULL) {
      s = getSibling(node);
    }
    Node* child = NULL;
    if (node->getRchild() != NULL || node->getLchild() != NULL) {
      if (node->getRchild() != NULL)
	child = node->getRchild();
      else
	child = node->getLchild();
    }
    replace(node, child, head);
    if (node->getColor() == 1) {
      if (child != NULL && child->getColor() == 0) {
	child->setColor(1);
      }
      else {
	removeCase1(child, head, parent, s);
      }
    }
    node->~Node();
  }
}
void replace(Node* node, Node* child, Node** head) {
  Node* parent = node->getParent();
  if (child != NULL) {
    child->setParent(parent);
  }
  if (parent != NULL) {
    if (parent->getLchild() == node)
      parent->setLchild(child);
    else
      parent->setRchild(child);
  }
  else
    *head = child;
}
void removeCase1(Node* node, Node** head, Node* parent, Node* s) {
  if (parent != NULL) {
    removeCase2(node, head, parent, s);
  }
}
void removeCase2(Node* node, Node** head, Node* parent, Node* s) {
  if (s != NULL && s->getColor() == 0) {
    parent->setColor(0);
    s->setColor(1);
    if (node == parent->getLchild())
      rotateL(parent, head);
    else
      rotateR(parent, head);
    if (parent->getLchild() == node)
      s = parent->getRchild();
    else
      s = parent->getLchild();
  }
  removeCase3(node, head, parent, s);
}
void removeCase3(Node* node, Node** head, Node* parent, Node* s) {
  if (s != NULL && (s->getLchild() == NULL || (s-> getLchild() != NULL && s->getLchild()->getColor() == 1))
      && (s->getRchild() == NULL || (s->getRchild() != NULL && s->getRchild()->getColor() == 1)) && parent->getColor() == 1 &&
      s->getColor() == 1) {
    s->setColor(0);
    Node* p = parent->getParent();
    Node* si = NULL;
    if (getSibling(parent) != NULL) {
      si = getSibling(parent);
    }
    removeCase1(parent, head, p, si);
  }
  else
    removeCase4(node, head, parent, s);
}
void removeCase4(Node* node, Node** head, Node* parent, Node* s) {
  if (s != NULL && (s->getLchild() == NULL || (s-> getLchild() != NULL && s->getLchild()->getColor() == 1))
      && (s->getRchild() == NULL || (s->getRchild() != NULL && s->getRchild()->getColor() == 1)) && parent->getColor() == 0 &&
      s->getColor() == 1) {
    s->setColor(0);
    parent->setColor(1);
  }
  else
    removeCase5(node, head, parent, s);
}
void removeCase5(Node* node, Node** head, Node* parent, Node* s) {
  if (s != NULL && s->getColor() == 1) {
    if (parent->getLchild() == node && s->getLchild() != NULL && s->getLchild()->getColor() == 0 &&
	s->getRchild() != NULL && s->getRchild()->getColor() == 1) {
      s->setColor(0);
      s->getLchild()->setColor(1);
      rotateR(s, head);
      s = parent->getRchild();
    }
    else if (parent->getRchild() == node && s->getRchild() != NULL && s->getRchild()->getColor() == 0 &&
	s->getLchild() != NULL && s->getLchild()->getColor() == 1) {
      s->setColor(0);
      s->getRchild()->setColor(1);
      rotateL(s, head);
      s = parent->getLchild();
    }
  }
  removeCase6(node, head, parent, s);
}
void removeCase6(Node* node, Node** head, Node* parent, Node* s) {
  if (s != NULL) {
    s->setColor(parent->getColor());
    parent->setColor(1);
    if (node == parent->getLchild()) {
      if (s->getRchild() != NULL) {
	s->getRchild()->setColor(1);
	rotateL(parent, head);
      }
    }
    else {
      if (s->getLchild() != NULL) {
	s->getLchild()->setColor(1);
	rotateR(parent, head);
      }
    }
  }
}
