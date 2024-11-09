#include "AVL.h"
#include <cctype>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include<vector>
#include <queue>
using namespace std;

// PRIVATE FUNCTIONS

// Checks if the UFID meets all necessary conditions (will be used in insertNameID function)
bool AVLTree::checkUFID(const string& UFID)
{

    // Make sure UFIDs are exactly 8 digits long and don't contain letters
    if (UFID.length() != 8)
    {
        return false;
    }

    for (char c : UFID)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }

    return true;

    // References:
    // https://stackoverflow.com/questions/35490236/colon-and-auto-in-for-loop-c-need-some-help-understanding-the-syntax
}

// Checks if the name meets all necessary conditions (will be used in insertNameID function)
bool AVLTree::checkName(const string& name)
{
    // Check name is only made up of strings/spaces
    for (char c : name)
    {
        if (!isalpha(c) && !isspace(c))
        {
            return false;
        }
    }
    return true;

    // References:
    // https://cplusplus.com/reference/cctype/isalpha/
    // https://cplusplus.com/reference/cctype/isspace/
}

// Rotate Right functionality to be implemented in insert function (logic from lecture slides)
Node* AVLTree::rotateRight(Node* node)
{
    Node* newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;

    node->setHeight(max(height(node->left), height(node->right)) + 1);
    newParent->setHeight(max(height(newParent->left), height(newParent->right)) + 1);

    return newParent;

    // References:
    // Office Hours/CISE Tutoring (Oscar)
    // Lecture slides
}

// Rotate Left functionality to be implemented in insert function (logic from lecture slides)
Node* AVLTree::rotateLeft(Node* node)
{
    Node* newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

    node->setHeight(max(height(node->left), height(node->right)) + 1);
    newParent->setHeight(max(height(newParent->left), height(newParent->right)) + 1);

    return newParent;

    // References:
    // Office Hours/CISE Tutoring (Oscar)
    // Lecture slides
}

// Rotate Right Left functionality to be implemented in insert function (logic from lecture slides)
Node* AVLTree::rotateRightLeft(Node* node)
{
    // Preform right rotation on right child
    node->right = rotateRight(node->right);
    // Preform left rotation on original root node
    Node* newParent = rotateLeft(node);

    // Preform left rotation on root node
    return newParent;
}

// Rotate Left Right functionality to be implemented in insert function (logic from lecture slides)
Node* AVLTree:: rotateLeftRight(Node* node)
{
    // Preform left rotation on left child
    node->left = rotateLeft(node->left);
    // Preform right rotation on original root node
    Node* newParent = rotateRight(node);

    return newParent;
}


// Function to store the height of individual nodes (will make calculating balance factor easier later)
int AVLTree::height(Node* node)
{
    // Return -1 for a nullptr and 0 for a leaf node
    if (node == nullptr)
    {
        return -1;
    }

    return node->getHeight();
}

// Function used to calculate updated heights as nodes are inserted/removed
void AVLTree::calcHeight(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    // Get the heights of the left and right children of the root and add one to whichever one is larger to yield updated height
    int leftHeight = height(node->getLeft());
    int rightHeight = height(node->getRight());

    node->setHeight(max(leftHeight, rightHeight) + 1);

    // References:
    // Discord after I asked a question/Lecture Slides
}

// Calculate balance factor using formula height of left subtree - height of right subtree
int AVLTree::balanceFactor(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return height(node->getLeft()) - height(node->getRight());

    // References:
    // Lecture slides/Project Breakdown slides
}

// Add a Student object into the tree with the specified name and UFID
Node* AVLTree::insertNameID(Node* node, string name, string UFID)
{
    // 1. Begin by checking if name and UFID meet necessary conditions
    if (!checkName(name) || !checkUFID(UFID))
    {
        // Mark insertion as unsuccessful
        cout << "unsuccessful" << endl;
        return node;
    }

    // 2. If conditions are met, preform BST insertion
    if (node == nullptr)
    {
        // Node to be inserted in the tree, beginning height of 0 (keep track of the height of every node)
        node = new Node(name, UFID);

        // Print successful after every insertion
        cout << "successful" << endl;
        return node;

    }

    if (UFID < node->getUFID())
    {
        // Get the following node to traverse to the left depending on UFID
        node->left = insertNameID(node->getLeft(), name, UFID);
    }
    else if (UFID > node->getUFID())
    {
        // Get the following node to traverse the right way depending on UFID
        node->right = insertNameID(node->getRight(), name, UFID);
    }
    else
    {
        return node;
    }

    // Update height after every insertion to determine where balance is needed
    calcHeight(node);

    // 3. Get balance factor of this ancestor node to check whether this node became unbalanced (unbalanced = balance factor other than -1, 0, or 1)
    int balance_factor = balanceFactor(node);

    // Check if tree is already balanced and doesn't need any rotations
    if (balance_factor >= -1 && balance_factor <= 1)
    {
        return node;
    }

    // If balance factor of left parent node is +2 and left child is +1 preform a right rotation
    if (balanceFactor(node) >= 2 && balanceFactor(node->left) >= 1)
    {
        return rotateRight(node);
    }


    // If balance factor of right parent node is -2 and right child is -1 preform a left rotation
    if (balanceFactor(node) <= -2 && balanceFactor(node->right) <= -1)
    {
        return rotateLeft(node);
    }

    // If balance factor of left parent node is +2 and right child is -1 preform a left right rotation
    if (balanceFactor(node) >= 2 && balanceFactor(node->left) <= -1)
    {
        return rotateLeftRight(node);
    }

    // If balance factor of right parent node is -2 and left child is +1 preform a right left rotation
    if (balanceFactor(node) <= -2 && balanceFactor(node->right) >= 1)
    {
        return rotateRightLeft(node);
    }

    return node;

    // References:
    // Replit logic from BST programming quiz for physical insertions
    // Lecture Slides/Office Hours
    // https://www.ibm.com/docs/ru/aix/7.2?topic=c-ctype-isalpha-isupper-islower-isdigit-isxdigit-isalnum-isspace-ispunct-isprint-isgraph-iscntrl-isascii-subroutines
    // https://www.youtube.com/watch?v=zP2xbKerIds&t=458s
}

// Function that grabs a specified ID and returns it based on user input
Node* AVLTree::searchID(Node* node, string& UFID, vector<string>& nodes)
{
    // Use in order traversal to find matches to the desired name to search
    if (node == nullptr)
    {
        return nullptr;
    }

    // Begin by checking the left (first to check in an in order traversal)
    searchID(node->getLeft(), UFID, nodes);

    // If the input name equals the name of the current node, add to the vector
    if (UFID == node->getUFID())
    {
        nodes.push_back(node->getName());
    }

    // If not, go right
    searchID(node->getRight(), UFID, nodes);
    return node;

    // References:
    // Office Hours (Declan)
}

// Function that grabs a specified ID and returns it based on user input
Node* AVLTree::searchName(Node* node, string& name, vector<string>& nodes)
{
    // Use in order traversal to find matches to the desired name to search
    if (node == nullptr)
    {
        return nullptr;
    }

    // Begin by checking the left (first to check in an in order traversal)
    searchName(node->getLeft(), name, nodes);

    // If the input name equals the name of the current node, add to the vector
    if (name == node->getName())
    {
        nodes.push_back(node->getUFID());
    }

    // If not, go right
    searchName(node->getRight(), name, nodes);
    return node;

    // References:
    // Office Hours (Declan)

}

// Remove specified node from AVL Tree (got logic from lecture slides)
Node* AVLTree::removeID(Node* node, string UFID)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    // Compare node to remove with root
    if (UFID < node->getUFID())
    {
        node->left = removeID(node->getLeft(), UFID);
    }

    else if (UFID > node->getUFID())
    {
        node->right = removeID(node->getRight(), UFID);
    }

    // Actual deletion/removal
    else
    {
        // No children
        if (node->getLeft() == nullptr && node->getRight() == nullptr)
        {
            delete node;
            node = nullptr;
            cout << "successful" << endl;
            return node;
        }

        // One child
        else if (node->getLeft() == nullptr)
        {
            Node* temp = node;
            node = node->right;
            cout << "successful" << endl;
            delete temp;
        }

        else if (node->getRight() == nullptr)
        {
            Node* temp = node;
            node = node->left;
            cout << "successful" << endl;
            delete temp;
        }

        // Two children
        else
        {
            // Must use inorder successor to remove node with two children
            Node* inorder_successor = node->getRight();

            // Loop to get to rightmost node in right subtree of left child
            while (inorder_successor->getLeft() != nullptr)
            {
                inorder_successor = inorder_successor->getLeft();
            }

            // Copy data into local root's data to current node
            node->setName(inorder_successor->getName());
            node->setUFID(inorder_successor->getUFID());
            node->setHeight(inorder_successor->getHeight());

            // Remove inorder_successor
            node->right = removeID(node->getRight(), inorder_successor->getUFID());
        }
    }

    calcHeight(node);
    balanceFactor(node);

    return node;

    // References:
    // Pseudocode in lecture slides/Project Breakdown slides
    // https://www.youtube.com/watch?v=gcULXE7ViZw
}

// Remove the specified Nth item based on the Inorder (ascending order) of the nodes
Node* AVLTree::removeInorderN(Node* node, size_t& index, size_t N)
{
    // Use in order traversal to find desired node to remove ( will use similar to logic to insertion and search functions)
    if (node == nullptr)
    {
        return nullptr;
    }

    // Begin in order traversal by traversing the left subtree
    node->left = removeInorderN(node->getLeft(), index, N);

    // Increment index if we haven't found the node to remove, move to the next
    index++;

    // Check if index matches N, if so, remove that node
    if (N == index)
    {
        return removeID(node, node->getUFID());
    }

    // Traverse the right subtree
    node->right = removeInorderN(node->getRight(), index, N);
    return node;

    // References:
    // Search and Insertion functions
    // https://stackoverflow.com/questions/2550774/what-is-size-t-in-c
    //https://www.geeksforgeeks.org/inorder-traversal-of-binary-tree/
}

// Use vector get Inorder- Left -> Root -> Right
vector<string> AVLTree::printInorder(Node* node, vector<string>& nodes)
{
    if (node == nullptr)
    {
        return vector<string>();
    }
    else
    {
        printInorder(node->getLeft(), nodes);
        nodes.push_back(node->getName());
        printInorder(node->getRight(), nodes);
    }

    return vector<string>();

    // References:
    // CISE Tutoring (Divy)
    // Project Breakdown slides
}

// Preorder- Root -> Left -> Right
vector<string> AVLTree::printPreorder(Node* node, vector<string>& nodes)
{
    // create vector to store nodes
    if (node == nullptr)
    {
        return vector<string>();
    }
    else
    {
        nodes.push_back(node->getName());
        printPreorder(node->getLeft(), nodes);
        printPreorder(node->getRight(), nodes);
    }

    return vector<string>();

    // References:
    // CISE Tutoring (Divy)
    // Project Breakdown slides
}

// Postorder- Left -> Right -> Root
vector<string> AVLTree::printPostorder(Node* node, vector<string>& nodes)
{
    if (node == nullptr)
    {
        return vector<string>();
    }
    else
    {
        printPostorder(node->getLeft(), nodes);
        printPostorder(node->getRight(), nodes);
        nodes.push_back(node->getName());
    }

    return vector<string>();

    // References:
    // CISE Tutoring (Divy)
    // Project Breakdown slides
}

// Helper print function (was suggested to solve this way by one of the CISE tutors)
void AVLTree::helperPrint(const vector<string>& nodes)
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        cout << nodes[i];

        if (i < nodes.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << endl;

    // References:
    // CISE Tutoring (Divy)
}

// Function that returns the amount of levels in the tree
int AVLTree::printLevelCount(Node* node)
{
    if (root == nullptr)
    {
        // Level count will be zero if the head/root of the tree is nullptr
        cout << "0" << endl;
        return 0;
    }

    // The level count will be equal to the height of the root plus 1 (height begins at -1 for nullptr so we have to add 1)
    int level_count = node->getHeight() + 1;
    cout << level_count << endl;
    return level_count;
}

// Function to aid in deleting all the nodes by doing a post order traversal for the destructor
void AVLTree::destructorImplementation(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    // Delete in the following order: left->right->root
    destructorImplementation(node->left);
    destructorImplementation(node->right);
    delete node;

     // References:
    // Used similar logic to my printPostorder function
}

