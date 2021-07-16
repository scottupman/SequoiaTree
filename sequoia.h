// Scott Upman

#ifndef __SEQUOIA_H
#define __SEQUOIA_H

#include <iostream>
using namespace std;

class SequoiaNode;
class Sequoia;

class SequoiaNode
{
  friend Sequoia;
  friend ostream& operator<<(ostream&, const SequoiaNode*);
private:
  int value;
  SequoiaNode* left;
  SequoiaNode* right;
  SequoiaNode* parent;
  int height;
public:
  //Basic constructor and destructor
  SequoiaNode(int x) { value = x; height = 1; left = right = parent = nullptr; } // Height = 1 when instantiated
  ~SequoiaNode() { delete left; delete right; }
  //Optional:  copy constructor or copy assignment

  //These functions are *required*
  void insert(int x);         // Inserts a node and updates the height based off modified tree
  SequoiaNode* remove();      // Removes the node and updates the height based off modified tree
  int checkHeight() const; 
  bool isTall() const; 

  //May add any number of additional functions
  //E.g.,
  SequoiaNode* search(int x); // Searches for node with value x
  void updateHeight();        // Updates the height of each SequoiaNode
  bool checkIfTall();         // Determines if the SequoiaNode is tall
  void rotateLeft();          // Rotates the right child left
  void rotateRight();         // Rotates the left child right
  bool isLeftChild() const;   // Determines if current node = parent's left
  bool isRightChild() const;  // Determines if current node = parent's right
  SequoiaNode* findMax();     // Finds the max node to swap with the node being deleted
};

class Sequoia
{
  friend ostream& operator<<(ostream&, const Sequoia&);
private:
  SequoiaNode* root;
  int size;
public:
  //Basic constructor and destructor
  Sequoia() { root = nullptr; size = 0; }
  ~Sequoia() { delete root; }
  //Optional: copy constructor or copy assignment

  //***These functions are required***
  void insert(int x);
  void remove(int x);
  bool checkHeight() const;
  bool isTall() const;  
  void updateHeight();        // Updates the height of the root of Sequoia tree

  //May add any number of additional functions
};

//Print functions
ostream& operator<<(ostream&, const Sequoia&);
ostream& operator<<(ostream&, const SequoiaNode*);

#endif //__SEQUOIA_H