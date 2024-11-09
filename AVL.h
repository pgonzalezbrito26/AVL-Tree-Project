#ifndef AVL_H
#define AVL_H
#include<iostream>
#include<cctype>
#include<string>
#include<vector>
using namespace std;

struct Node
{
    // Stores names of students
    string name;
    // Stores UFID's associated to students
    string UFID;
    // Pointer to left child
    Node* left;
    // Pointer to right child
    Node* right;
    // Pointer to parent node
    Node* parent;
    // Height of tree
    int height;



    // CONSTRUCTOR
    Node(string name, string UFID)
    {
        this->name = name;
        this->UFID = UFID;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->height = 0;
    }

    // GETTERS
    string getName()
    {
        return name;
    }

    string getUFID()
    {
        return UFID;
    }

    Node* getLeft()
    {
        return left;
    }

    Node* getRight()
    {
        return right;
    }

    Node* getParent()
    {
        return parent;
    }

    int getHeight()
    {
        return height;
    }


    //SETTERS
    void setName(string newName)
    {
        name = newName;
    }

    void setUFID(string newUFID)
    {
        UFID = newUFID;
    }

    void setLeft(Node* newLeft)
    {
        left = newLeft;
    }

    void setRight(Node* newRight)
    {
        right = newRight;
    }

    void setParent(Node* newParent)
    {
        parent = newParent;
    }

    void setHeight(int newHeight)
    {
        height = newHeight;
    }
};

class AVLTree
{
private:
    Node* root;

    // Helper functions to be used in insertNameID that check the validity of the input name and UFID to be inserted
    bool checkUFID(const string& UFID);
    bool checkName(const string& name);

    // Rotation functions that will be called when there is an unbalanced tree
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRightLeft(Node* node);
    Node* rotateLeftRight(Node* node);

    // Functions used to calculate/update the heights and balance factors of the nodes
    int height(Node* node);
    void calcHeight(Node* node);
    int balanceFactor(Node *node);

    // Function used to insert nodes into the tree and balance them if necessary
    Node* insertNameID(Node* node, string name, string UFID);

    // Functions used to search for and return a specific UFID or name in the tree
    Node* searchID(Node* node, string& UFID, vector<string>& nodes);
    Node* searchName(Node* node, string& name, vector<string>& nodes);

    // Functions used to remove specific nodes by calling a UFID or an index
    Node* removeID(Node* node, string UFID);
    Node* removeInorderN(Node* node, size_t& index, size_t N);

    // Functions that print the nodes in either Inorder, Preorder, or Postorder
    vector<string> printInorder(Node* node, vector<string>& nodes);
    vector<string> printPreorder(Node* node, vector<string>& nodes);
    vector<string> printPostorder(Node* node, vector<string>& nodes);

    // Function that simply returns the amount of levels in the tree
    int printLevelCount(Node* node);

    // Function that completes a post order traversal of the tree in order to delete the nodes
    void destructorImplementation(Node* node);


public:

    AVLTree() : root(nullptr) {}

    Node* getRoot()
    {
        return root;
    }

    // Helper functions to aid in shielding "main" from having access to the nodes in the tree
    bool testCheckUFID(const string& UFID)
    {
        return checkUFID(UFID);
    }

    bool testCheckName(const string& name)
    {
        return checkName(name);
    }

    void testInsertNameID(string name, string UFID)
    {
        root = insertNameID(root, name, UFID);
    }

    void testSearchID(string UFID)
    {
        vector<string> nodes;
        searchID(root, UFID, nodes);

        if (nodes.empty())
        {
            cout << "unsuccessful" << endl;
        }
        else
        {
            for (size_t i = 0; i < nodes.size(); i++)
            {
                cout << nodes[i] << endl;
            }
        }
    }

    void testSearchName(string name)
    {
        vector<string> nodes;
        searchName(root, name, nodes);

        if (nodes.empty())
        {
            cout << "unsuccessful" << endl;
        }
        else
        {
            for (size_t i = 0; i < nodes.size(); i++)
            {
                cout << nodes[i] << endl;
            }
        }

    }

    void testRemoveID(string UFID)
    {
        root = removeID(root, UFID);
    }

    vector<string> printInorder()
    {
        // Handle all vector logic internally so user doesn't have to explicitly define a vector each time one of these functions is called
        vector<string> nodes;
        printInorder(root, nodes);
        helperPrint(nodes);
        return nodes;
    }

    vector<string> printPreorder()
    {
        // Handle all vector logic internally so user doesn't have to explicitly define a vector each time one of these functions is called
        vector<string> nodes;
        printPreorder(root, nodes);
        helperPrint(nodes);
        return nodes;
    }

    vector<string> printPostorder()
    {
        // Handle all vector logic internally so user doesn't have to explicitly define a vector each time one of these functions is called
        vector<string> nodes;
        printPostorder(root, nodes);
        helperPrint(nodes);
        return nodes;
    }

    int testLevelCount()
    {
        return printLevelCount(root);
    }

    void testRemoveInorderN(size_t N)
    {
        // Index begins at -1, will increment throughout the function
        size_t index = -1;
        removeInorderN(root, index, N);

        // if n is greater than index then print unsuccessful
        if (N > index)
        {
            cout << "unsuccessful" << endl;
        }
    }

    // Helper print function to be used in unison with the print Inorder, Preorder, and Postorder functions
    void helperPrint(const vector<string>& nodes);

    // Destructor
    ~AVLTree()
    {
        destructorImplementation(root);
    }

};

// References:
// Lecture Slides/Project Breakdown slides/Office Hours/CISE Tutoring
// https://www.w3schools.com/cpp/cpp_constructors.asp

#endif


