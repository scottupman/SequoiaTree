#include "sequoia.h"

//*** Left off at trying to figure out how to update the height when the tree is rotated ***

void SequoiaNode::insert(int x)
{
	// Same as BST
	// Update the height
	if (x < value)
	{
		if (left != nullptr)
			left->insert(x);
		else
		{
			left = new SequoiaNode(x);
			left->parent = this;
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
		}
	}
}

void SequoiaNode::updateHeight()
{
	// Recursive function
	if (parent != nullptr)
	{
		if (right->height > left->height)
		{
			this->height = right->height + 1;
		}
		else
			this->height = left->height + 1;

		parent->updateHeight();	
	}
}

bool SequoiaNode::isTall() const
{
	if (left->height >= 2 * right->height || right->height >= 2 * left->height || (left->height && right->height == 0))
	{
		return true;
	}
	return false;
}