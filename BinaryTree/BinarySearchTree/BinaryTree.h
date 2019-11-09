#include <iostream>
#include <cstdlib> // rand() and srand()
#include <ctime>   // use time() to set seed for srand()

#ifndef _BINARYT_
#define _BINARYT_
template <typename elemType>
class Node
{
public:
    elemType info;
    Node<elemType> *llink;
    Node<elemType> *rlink;
    Node() : llink(NULL), rlink(NULL) {}
    Node(const elemType &data) : info(data), llink(NULL), rlink(NULL) {}
};
template <class elemType>
class BinaryTree
{
private:
    //-- AUX functions
    std::ostream &inorder_aux(Node<elemType> *treePtr, std::ostream &out) const;
    std::ostream &preorder_aux(Node<elemType> *treePtr, std::ostream &out) const;
    std::ostream &postorder_aux(Node<elemType> *treePtr, std::ostream &out) const;

    Node<elemType> *search_aux(Node<elemType> *treePtr, const elemType &data) const;
    void delete_aux(Node<elemType> *&treePtr, const elemType &data);
    void insert_aux(Node<elemType> *&treePtr, const elemType &data);

    void destroy_tree(Node<elemType> *treePtr);
    Node<elemType> *inorder_succ(Node<elemType> *treePtr) const;
    Node<elemType> *getsuccessor(Node<elemType> *treePtr, const elemType &data);
    Node<elemType> *find_min(Node<elemType> *treePtr);
    //void Shuffle(elemType *arr, size_t n);

    Node<elemType> *root;

public:
    BinaryTree();
    ~BinaryTree();

    Node<elemType> *Search(const elemType &data) const;
    void Delete(const elemType &data);
    void Insert(const elemType &data);

    void Inorder(std::ostream &out) const;
    void Preorder(std::ostream &out) const;
    void Postorder(std::ostream &out) const;

    int TreeHeight() const;
    int TreeLeaves() const;
    //void MakeRandomTree(int size);
};

// -- Default constructor
template <class elemType>
BinaryTree<elemType>::BinaryTree()
{
    root = NULL;
}
template <class elemType>
void BinaryTree<elemType>::destroy_tree(Node<elemType> *treePtr)
{
    if (treePtr)
    {
        destroy_tree(treePtr->llink);
        destroy_tree(treePtr->rlink);
        delete treePtr;
    }
}

// -- destructor
template <class elemType>
BinaryTree<elemType>::~BinaryTree()
{
    destroy_tree(root);
}

/***************************************************************************
 *                               Traversal Functions 
 ***************************************************************************/
template <class elemType>
std::ostream &BinaryTree<elemType>::inorder_aux(Node<elemType> *treePtr, std::ostream &out) const
{
    if (treePtr != NULL)
    {
        inorder_aux(treePtr->llink, out);
        out << treePtr->info << " ";
        inorder_aux(treePtr->rlink, out);
    }
    return out;
}
template <class elemType>
std::ostream &BinaryTree<elemType>::preorder_aux(Node<elemType> *treePtr, std::ostream &out) const
{
    if (treePtr != NULL)
    {
        out << treePtr->info << std::endl;
        inorder_aux(treePtr->llink, out);
        inorder_aux(treePtr->rlink, out);
    }
}
template <class elemType>
std::ostream &BinaryTree<elemType>::postorder_aux(Node<elemType> *treePtr, std::ostream &out) const
{
    if (treePtr != NULL)
    {
        inorder_aux(treePtr->llink, out);
        inorder_aux(treePtr->rlink, out);
        out << treePtr->info << std::endl;
    }
}

template <class elemType>
void BinaryTree<elemType>::Inorder(std::ostream &out) const
{
    inorder_aux(root, out);
}
template <class elemType>
void BinaryTree<elemType>::Preorder(std::ostream &out) const
{
    preorder_aux(root, out);
}
template <class elemType>
void BinaryTree<elemType>::Postorder(std::ostream &out) const
{
    postorder_aux(root, out);
}

// -- insert_aux
template <class elemType>
void BinaryTree<elemType>::insert_aux(Node<elemType> *&treePtr, const elemType &data)
{
    if (treePtr == NULL)
    {
        treePtr = new Node<elemType>;
        treePtr->info = data;
    }
    else if (treePtr->info > data)
    {
        insert_aux(treePtr->llink, data);
    }
    else if (treePtr->info < data)
    {
        insert_aux(treePtr->rlink, data);
    }
    else
    {
        std::cout << "Item already in tree." << std::endl;
    }
}
// -- Insert
template <class elemType>
void BinaryTree<elemType>::Insert(const elemType &data)
{
    insert_aux(root, data);
}

template <class elemType>
Node<elemType> *BinaryTree<elemType>::inorder_succ(Node<elemType> *treePtr) const
{
    Node<elemType> *temp = treePtr->rlink;
    while (temp != NULL)
    {
        temp = temp->llink;
    }
    return temp;
}
// -- find_min -helper function for the getsuccessor function
template <class elemType>
Node<elemType> *BinaryTree<elemType>::find_min(Node<elemType> *treePtr)
{
    if (treePtr == NULL)
        return NULL;
    while (treePtr->llink != NULL)
        treePtr = treePtr->llink;
    return treePtr;
}
// --getsuccessor alternative method to find the inorder successor
template <class elemType>
Node<elemType> *BinaryTree<elemType>::getsuccessor(Node<elemType> *treePtr, const elemType &data)
{
    // Search the Node - O(h)
    Node<elemType> *current = search_aux(root, data);
    if (current == NULL)
    {
        return NULL;
    }
    // Case 1: Node has right subtree
    if (current->rlink != NULL)
    {
        return find_min(current->rlink);
    }
    // Case 2: No right subtree
    // walk the tree from root to current node and find deepest
    // ancestor for which current node will be in its left subtree
    else
    {
        Node<elemType> *successor = NULL;
        Node<elemType> *ancestor = root;
        while (ancestor != current)
        {
            if (current->info < ancestor->info)
            {
                successor = ancestor;
                ancestor = ancestor->llink;
            }
            else
            {
                ancestor = ancestor->rlink;
            }
        }
        return successor;
    }
}

// -- search_aux - O(h)
template <class elemType>
Node<elemType> *BinaryTree<elemType>::search_aux(Node<elemType> *treePtr, const elemType &data) const
{
    if (treePtr == NULL)
    {
        std::cout << "Item: " << data << " not in tree." << std::endl;
        Node<elemType> *garbage = NULL;
        std::cout << "Returning garbage value: " << garbage << std::endl;
        return garbage;
    }

    if (treePtr->info == data)
    {
        return treePtr;
    }
    else if (treePtr->info > data)
    {
        search_aux(treePtr->llink, data);
    }
    else if (treePtr->info < data)
    {
        search_aux(treePtr->rlink, data);
    }
}

template <class elemType>
Node<elemType> *BinaryTree<elemType>::Search(const elemType &data) const
{
    search_aux(root, data);
}

template <class elemType>
void BinaryTree<elemType>::delete_aux(Node<elemType> *&treePtr, const elemType &data)
{
    if (treePtr == NULL)
    {
        std::cout << "Cannot delete because tree is empty." << std::endl;
    }
    else if (treePtr->info > data)
    {
        delete_aux(treePtr->llink, data);
    }
    else if (treePtr->info < data)
    {
        delete_aux(treePtr->rlink, data);
    }
    else
    {
        Node<elemType> *temp;
        if (treePtr->llink == NULL)
        {
            temp = treePtr->rlink;
            delete treePtr;
            treePtr = temp;
        }
        else if (treePtr->rlink == NULL)
        {
            temp = treePtr->llink;
            delete treePtr;
            treePtr = temp;
        }
        else
        {
            temp = getsuccessor(treePtr, data);
            treePtr->info = temp->info;
            delete_aux(treePtr->llink, temp->info);
        }
    }
}

template <class elemType>
void BinaryTree<elemType>::Delete(const elemType &data)
{
    delete_aux(root, data);
}

/* template <class elemType>
void BinaryTree<elemType>::Shuffle(elemType *arr, size_t n)
{
    if (n > 1)
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand();
            int t = arr[j];
            arr[j] = arr[i];
            arr[i] = t;
        }
    }
}

template <class elemType>
void BinaryTree<elemType>::MakeRandomTree(int size)
{
    elemType arr[size];
    for (size_t i = 0; i < size - 1; i++)
    {
        arr[i] = i;
    }
    Shuffle(arr, size);
} */
#endif