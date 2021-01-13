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

int main() {
  //Variables
  Node* head = NULL;
  const int RED = 0;
  const int BLACK = 1;
  //Commands
  cout << "commands: add, read, print, quit" << endl;
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
    Node* uncle = getUncle(*head, getParent(*head, (*node)->getValue())->getValue());
    if ((grandparent->getLchild() == parent && parent->getRchild() == *node) ||
	(grandparent->getRchild() == parent && parent->getLchild() == *node)) {
      if (grandparent->getLchild() == parent) {
	grandparent->setLchild(*node);
      }
      else {
	grandparent->setRchild(*node);
      }
      if (parent->getLchild() == *node) {
	(*node)->setRchild(parent);
	parent->setLchild(NULL);
      }
      else {
	(*node)->setLchild(parent);
	parent->setRchild(NULL);
      }
      if (grandparent->getLchild() == *node) {
	if (grandparent == *head) {
	  (*node)->setRchild(grandparent);
	  grandparent->setLchild(NULL);
	  *head = *node;
	  (*node)->setColor(1);
	  grandparent->setColor(0);
	}
	else {
	  Node* ggrandparent = getParent(*head, (grandparent)->getValue());
	  (*node)->setRchild(grandparent);
	  grandparent->setLchild(NULL);
	  (*node)->setColor(1);
	  grandparent->setColor(0);
	  if (ggrandparent->getLchild() == grandparent) {
	    ggrandparent->setLchild(*node);
	  }
	  else {
	    ggrandparent->setRchild(*node);
	  }
	}
      }
      else {
	if (grandparent == *head) {
	  (*node)->setLchild(grandparent);
	grandparent->setRchild(NULL);
	*head = *node;
	(*node)->setColor(1);
	grandparent->setColor(0);
	}
	else {
	  Node* ggrandparent = getParent(*head, (grandparent)->getValue());
	  (*node)->setLchild(grandparent);
	  grandparent->setRchild(NULL);
	  (*node)->setColor(1);
	  grandparent->setColor(0);
	  if (ggrandparent->getLchild() == grandparent) {
	    ggrandparent->setLchild(*node);
	  }
	  else {
	    ggrandparent->setRchild(*node);
	  }
	}
      }
    }
    else {
      if (grandparent->getLchild() == parent) {
	if (grandparent == *head) {
	  (parent)->setRchild(grandparent);
	  grandparent->setLchild(NULL);
	  *head = parent;
	  (parent)->setColor(1);
	  grandparent->setColor(0);
	}
	else {
	  Node* ggrandparent = getParent(*head, (grandparent)->getValue());
	  (parent)->setRchild(grandparent);
	  grandparent->setLchild(NULL);
	  (parent)->setColor(1);
	  grandparent->setColor(0);
	  if (ggrandparent->getLchild() == grandparent) {
	    ggrandparent->setLchild(parent);
	  }
	  else {
	    ggrandparent->setRchild(parent);
	  }
	}
      }
      else {
	if (grandparent == *head) {
	  (parent)->setLchild(grandparent);
	  grandparent->setRchild(NULL);
	  *head = parent;
	  (parent)->setColor(1);
	  grandparent->setColor(0);
	}
	else {
	  Node* ggrandparent = getParent(*head, (grandparent)->getValue());
	  (parent)->setLchild(grandparent);
	  grandparent->setRchild(NULL);
	  (parent)->setColor(1);
	  grandparent->setColor(0);
	  if (ggrandparent->getLchild() == grandparent) {
	    ggrandparent->setLchild(parent);
	  }
	  else {
	    ggrandparent->setRchild(parent);
	  }
	}
      }
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
    int input = 0;
    file >> input;
    //Run individual value through Add function
    Add(head, input);
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
