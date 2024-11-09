# AVL-Tree-Project
# Description:
The purpose of this project was to practice implementing an AVL Tree. The AVL Tree I implemented in this project is used to store the names of students and their respective student IDS. It has functionality to insert, remove, and search for certain names and IDS. When nodes are inserted into the tree, rotations are preformed to ensure the tree remains balanced using left, right, left-right, and right-left rotations depending on where the unbalanced node is placed.

To implement the tree, I used a node struct. I initialized the name and ID as strings, the left and right nodes as nullptr until they were needed to be used in my functionality, and the height of the tree as 0 until needed in my calculate height function. In order to avoid direct manipulation of nodes in my main function, I used "getters" to access these things throughout the program.
