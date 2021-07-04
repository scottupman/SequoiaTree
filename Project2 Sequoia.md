- Each node stores a height, value, parent, left, and right child data member
- Sequoia itself stores a root pointer and size

![image-20210703011545291](C:\Users\Scott\AppData\Roaming\Typora\typora-user-images\image-20210703011545291.png)



## Sequoia Insertion

- Inserts node similar to BST
- Also adjusts other nodes to maintain tallness property, similar to AVL tree rebalancing

### Fixing Sequoi Node's tallness property (similar to fixing an AVL tree balance)

- iterate up the tree, starting at parent of newly inserted node
- Recalculate height of each node by examining heigh of left and right children
  - **Recommended to write an updateHeight() function, but not required**

- Check if height of left and right trees satify tallness property
  - If so continue, to parent of the current node
  - Else,
    - ![image-20210703010154868](C:\Users\Scott\AppData\Roaming\Typora\typora-user-images\image-20210703010154868.png)

- Case 1: rotate right child to the left
- Case 2: Rotate left child to the right
- Update height of rotated child
- Iterate all the way up to root node

![image-20210703010619837](C:\Users\Scott\AppData\Roaming\Typora\typora-user-images\image-20210703010619837.png)



## Sequoia insertion example

![image-20210703011008549](C:\Users\Scott\AppData\Roaming\Typora\typora-user-images\image-20210703011008549.png)

![image-20210703011025675](C:\Users\Scott\AppData\Roaming\Typora\typora-user-images\image-20210703011025675.png)

![image-20210703011208158](C:\Users\Scott\AppData\Roaming\Typora\typora-user-images\image-20210703011208158.png)

- Updating the Sequoia means updating the root from 4 to 3



## Sequoia Deletion

- Similar to Insertion
- Tallness property will be restored after at most 1 rotation
- Delete given node same manner as a BST
- Begin iterating up the tree starting from parent of deleted node
- Update the height of each node based on it's children
- Check if node is tall
  - If tall
    - Continue to parent of current node
  - Else,
    - Same 2 cases for insert
    - ![image-20210703010154868](C:\Users\Scott\AppData\Roaming\Typora\typora-user-images\image-20210703010154868.png)

- Rotate the same as you did with the cases with insert
- Update the height of rotates child



NOTE: If a node has a **height of 1**, that node has **no children** and is therefore **"tall"**

![image-20210703013104427](C:\Users\Scott\AppData\Roaming\Typora\typora-user-images\image-20210703013104427.png)

![image-20210703013117519](C:\Users\Scott\AppData\Roaming\Typora\typora-user-images\image-20210703013117519.png)

- All nodes are tall
- update root of tree to 1



Driver file