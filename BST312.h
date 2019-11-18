
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode *root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);

};

/*******************************
//Function implementations
********************************/

//Constructor of the templated BST, sets the root of BST to a null pointer
template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

//Copy Constructor, calls a helper function to deep copy a templated BST
template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

//Destructor, calls the makeEmpty() function to dynamically deallocate BST memory
template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();
}

//Function that makes a deep copy of a templated BST
template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}

//Deletes a given node of a templated BST if said node is found in the tree
template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}

//Helper function to delete a specific node of a templated BST based on a given data value
template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}

//Calls a helper function to delete a specific node of a BST based on a given data value if said value is found
template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

//Helper function that dynamically deallocates all memory of a templated BST and clears all nodes
template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    if(t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}

//Function that calls a helper function to dynamically deallocate a BST
template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

//Function that checks if a given templated BST is empty or not, returning true if so, false otherwise
template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}

//Function that checks if a given templated BST is full or not, return true if so, false otherwise
template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}

//Helper function which inserts a new item into a templated BST if said item is not already in the tree, otherwise does
//nothing
template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{
    if(!isItemInTree(newItem)) {
        if (t == NULL) {
            TreeNode *temp = new TreeNode;
            temp->data = newItem;
            temp->left = NULL;
            temp->right = NULL;
            t = temp;
        } else if (newItem < t->data)
            insertItem(t->left, newItem);
        else
            insertItem(t->right, newItem);
    }
}

//Function that calls a helper function to insert a new item into a BST
template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    insertItem(root,newItem);
}

//Helper function that counts the number of nodes in a templated BST
template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    int count = 0;
    if(t != NULL)
    {
        count += countNodes(t->left);
        count += countNodes(t->right);
        count += 1;
    }
    return count;
}

//Function that calls the helper function to count nodes in the BST
template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    return countNodes(root);
}

//Helper function to preOrder traverse a templated BST
template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if(t != NULL)
    {
        result.push_back(t->data);
        preOrderTraversal(t->left,result);
        preOrderTraversal(t->right,result);
    }
}

//Function that calls a helper function to preOrder traverse a BST and return said values in a vector
template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    vector<ItemType> values;
    preOrderTraversal(root,values);
    return values;
}

//Helper function to inOrder traverse a templated BST
template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if(t != NULL)
    {
        inOrderTraversal(t->left,result);
        result.push_back(t->data);
        inOrderTraversal(t->right,result);
    }
}

//Function that calls a helper function to inOrder traverse a BST and return said values in a vector
template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    vector<ItemType> values;
    inOrderTraversal(root,values);
    return values;
}

//Helper function to postOrder traverse a templated BST
template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if(t != NULL)
    {
        postOrderTraversal(t->left,result);
        postOrderTraversal(t->right,result);
        result.push_back(t->data);
    }
}

//Function that calls a helper function to postOrder traverse a BST and return said values in a vector
template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    vector<ItemType> values;
    postOrderTraversal(root,values);
    return values;
}

//Function that checks if a given item is in a templated BST, returns true if so, false otherwise
template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{
    TreeNode *temp = root;

    while(temp != NULL && temp->data != item)
    {
        if(item < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if(temp == NULL)
        return false;
    return true;
}
#endif

