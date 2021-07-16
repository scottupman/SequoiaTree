// Scott Upman

#include "sequoia.h"

// ***SequoiaNode functions***

// Similar to BST insert, except that the height of SequoiaNodes are recursively updated
void SequoiaNode::insert(int x)
{
	// Update the height after inserting
	if (x < value)
	{
		if (left != nullptr)
			left->insert(x);
		else
		{
			left = new SequoiaNode(x);
			left->parent = this;
			updateHeight();			// Updates height starting at the parent of newly inserted node and recursively go up the tree
		}
	}
	else
	{
		if (right != nullptr)
			right->insert(x);
		else
		{
			right = new SequoiaNode(x);
			right->parent = this;
			updateHeight();			// Updates height starting at the parent of newly inserted node and recursively go up the tree
		}
	}
}

// Recursively searches for the node with value x
SequoiaNode *SequoiaNode::search(int x)
{
	// Base case
	if (x == value)
		return this;	
	else if (x < value)
	{
		if (left != nullptr)
			return left->search(x);
		else
			return nullptr;
	}
	else
	{
		if (right != nullptr)
			return right->search(x);
		else
			return nullptr;
	}
}

// Updates the height of current node based off of children, only updates when Node is tall
void SequoiaNode::updateHeight()
{
	// Only updates the height of the node if it's tall
	if (checkIfTall())
	{
		// Recursively calls updateHeight() until parent reaches a nullptr (if parent = nullptr, then currentNode = root)
		if (parent != nullptr)
		{
			// Cases for updating the height based off of children
			if (right == nullptr && left == nullptr)
			{
				this->height = 1;
			}
			else if (right == nullptr)
			{
				this->height = left->height + 1;
			}
			else if (left == nullptr)
			{
				this->height = right->height + 1;
			}
			else if (right->height > left->height)
			{
				this->height = right->height + 1;
			}
			else if (left->height > right->height)
				this->height = left->height + 1;

			parent->updateHeight();
		}
	}
	else	// Rotation will occur since SequoiaNode is not tall
	{
		// Rotate the right child left
		if (left->height >= right->height)
		{
			right->rotateLeft();
		}
		// Rotate the left child right
		else if (right->height > left->height)
		{
			left->rotateRight();
		}

		// Calls the updateHeight function based off rotated nodes
		updateHeight();
	}
}
// Rotates the node to the right assigning the pointers to their respective positions
void SequoiaNode::rotateRight()
{
	parent->left = right;
	if (right != nullptr)
		right->parent = parent;

	// Old parent becomes right child of pivot
	right = parent;

	parent = parent->parent;
	if (right->isLeftChild())
		parent->left = this;
	else if (right->isRightChild())
		parent->right = this;
	right->parent = this;
}
// Rotates the node to the left assigning the pointers to their respective positions
void SequoiaNode::rotateLeft()
{
	parent->right = left;

	if (left != nullptr)
	{
		left->parent = parent;
	}

	// Old parent becomes left child of pivot
	left = parent;

	parent = parent->parent;

	if (left->isLeftChild())
	{
		parent->left = this;
	}
	else if (left->isRightChild())
		parent->right = this;

	left->parent = this;
}

// Checks if tallness property of SequoiaNode holds
bool SequoiaNode::checkIfTall()
{
	if (this->left == nullptr || this->right == nullptr)
	{
		return true;
	}
	else if (left->height >= 2 * right->height || right->height >= 2 * left->height)
		return true;

	return false;
}

// Used for SequoiaNode rotation, checks if parent's left child is assigned to this current node
bool SequoiaNode::isLeftChild() const
{
	return parent != nullptr && parent->left == this;
}

// Used for SequoiaNode rotation, checks if parent's right child is assigned to this current node
bool SequoiaNode::isRightChild() const
{
	return parent != nullptr && parent->right == this;
}

// Similar to BST Remove, updates height after node is removed
SequoiaNode *SequoiaNode::remove()
{
	int numChildren = (left != nullptr) + (right != nullptr);
	
	//Separate cases based on # of children
	if (numChildren == 0)
	{
		if (isLeftChild())
			parent->left = nullptr;
		else if (isRightChild())
			parent->right = nullptr;
		//don't dereference parent if root
		SequoiaNode* parent = this->parent;
		delete this;
		parent->updateHeight();
		return nullptr; //tree has no root
	}
	else if (numChildren == 1)
	{
		SequoiaNode *child;
		if (left != nullptr)
			child = left;
		else
			child = right;

		//Point child to parent
		child->parent = parent;

		//Point parent to child
		if (isLeftChild())
			parent->left = child;
		else if (isRightChild())
			parent->right = child;

		left = right = nullptr; //important so we don't delete child
		SequoiaNode* parent = this->parent;
		delete this;
		parent->updateHeight();
		return child; //child is now root
	}
	else //2 children
	{
		SequoiaNode *swap = left->findMax();
		value = swap->value;
		swap->remove(); //recursively delete other node
		return this;	//still the root of the subtree
	}
	
}
// Traverses down the right side of the tree until it reaches a nullptr
SequoiaNode* SequoiaNode::findMax()
{
  if (right == nullptr)
    return this;
  else
    return right->findMax();
}

// ***Sequoia Tree functions***

// Uses SequoiaNode insert function by utilizing the root pointer
void Sequoia::insert(int x)
{
	// Call the function from SequoiaNode
	if (root != nullptr)
		root->insert(x);
	else
		root = new SequoiaNode(x);

	// Occurs when root is rotated
	if (root->parent != nullptr)
		root = root->parent;

	// Update the height of root based off children
	updateHeight();

	// Increase the size of the tree
	size++;
}

// Updates height of root since SequoiNode updateHeight stops updating height just before the root (since root->parent = nullptr)
void Sequoia::updateHeight()
{
	// Cases for updating height of root
	if (root->left == nullptr && root->right == nullptr)
		root->height = 1;

	else if (root->left == nullptr)
		root->height = root->right->height + 1;

	else if (root->right == nullptr)
		root->height = root->left->height + 1;

	else if (root->right->height > root->left->height)
		root->height = root->right->height + 1;

	else if (root->left->height > root->right->height)
		root->height = root->left->height + 1;
}

// Uses SequoiaNode remove function by utilizing the root pointer
void Sequoia::remove(int x)
{
	if (root == nullptr)
		return;

	SequoiaNode *victim = root->search(x); // Search for the node to delete within the tree
	if (victim == nullptr)
		return; //doesn't contain x

	if (victim == root) //update root if deleting
		root = victim->remove();
	else
		victim->remove();

	// Update the height of root based off children
	updateHeight();

	// Decrease the size of tree
	size--;
}
