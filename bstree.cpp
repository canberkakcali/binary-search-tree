#include <iostream>
#include "bstree.hpp"


/*
*
********* BSTREE CLASS
*   
********* Public Methods   
*
*/

/*
*   Function: Destructor
*   
*   Description: Destroys the tree by freeing all nodes it possesses
*
*/
template <typename TKey, typename TVal> BSTree<TKey, TVal>::~BSTree() {
    _deleteTree(root);
}

/*
*   Function: insert
*   @param1: TKey key : Lookup key.
*   @param2: TVal data : The data which the key leads to.
*   @returns: void
*   
*   Description: This function inserts the specified data (@param2) to the binary search tree
*                and uses the key (@param1) to determine the node's location.
*
*/
template <typename TKey, typename TVal> void BSTree<TKey, TVal>::insert(TKey key, TVal data) {

    // If the BSTree is empty, create the node at the root.
    if(!root) {
        root = _newNode(key, data);

    } else {

        BSTree<TKey, TVal>::node** current = &root, *parent = NULL;

        // Loop until an empty slot is found in the tree
        while(*current) {

            parent = *current;

            if(key < (*current)->key) {
                current = &parent->left;
            } else {
                current = &parent->right;
            }
        }
        // Empty slot is found, fill it with the given parameters.
        *current = _newNode(key,data);
        (*current)->parent = parent;
    }
}


/*
*   Function: del
*   @param1: TKey key : Lookup key.
*   @returns: true if successful, false otherwise.
*   
*   Description: This function finds and deletes the desired node from the 
*                binary search tree using the given lookup key (@param1).
*
*/
template <typename TKey, typename TVal> bool BSTree<TKey, TVal>::del(TKey key) {

    // Check if the binary search tree is not empty.
    if(!root) {
        return false;
    }

    BSTree<TKey, TVal>::node** current = &root;

    // Loop until the node with given key is found, 
    // or until there are no nodes left to look for. 
    while(*current && (*current)->key != key) {

        if(key < (*current)->key) {
            current = &(*current)->left;
        } 
        else {
            current = &(*current)->right;
        }
    }
    // Check if the end of the tree is reached.
    if(!*current) {
        return false;
    }
    // If not then the desired node is found.


    // If the left node is empty, move the right node
    // to the current node.
    if(!(*current)->left) {
        if((*current)->right) {
            (*current)->right->parent = (*current)->parent;
        }
        BSTree<TKey, TVal>::node* ptrToFree = *current;
        *current = (*current)->left;
        delete ptrToFree;
        
    }
    // If the right node is empty, move the left node
    // to the current node.
    else if(!(*current)->right) {
        if((*current)->left) {
            (*current)->left->parent = (*current)->parent;
        }
        BSTree<TKey, TVal>::node* ptrToFree = *current;
        *current = (*current)->left;
        delete ptrToFree;
    }
    // If the left and the right nodes are both present,
    // find the leftmost (smallest) node in the right subtree
    // and copy the contents to the node that will be deleted.
    else {
        BSTree<TKey, TVal>::node** temp = &(*current)->right;

        while((*temp)->left) temp = &(*temp)->left;

        (*current)->data = (*temp)->data;
        (*current)->key = (*temp)->key;

        // Delete the copied node.
        BSTree<TKey, TVal>::node* ptrToFree = *temp;
        *temp = (*temp)->right;
        delete ptrToFree;
    }

    return true;

}
// Same as del
template <typename TKey, typename TVal> bool BSTree<TKey, TVal>::remove(TKey key) {

    return del(key);

}
/*
*   Function: print
*   @param1: TRAVERSAL_METHOD t : Method to be used to print the tree (inorder, preorder, postorder)
*   @returns: void
*   
*   Description: This function prints the values inside the binary search tree
*                to the stdout with desired order (@param1).
*
*/
template <typename TKey, typename TVal> void BSTree<TKey, TVal>::print(TRAVERSAL_METHOD t) {
    switch(t) {
        case INORDER : {
            _printInOrder(root);
            break;
        }
        case PREORDER : {
            _printPreOrder(root);
            break;
        }
        case POSTORDER : {
            _printPostOrder(root);
            break;
        }
    }
    std::cout << std::endl;
}
/*
*   Function: has
*   @param1: TKey key : Lookup key.
*   @returns: true if found, false otherwise.
*   
*   Description: This function checks if the binary search tree
*                has a node with the given key (@param1).
*
*/
template <typename TKey, typename TVal> bool BSTree<TKey, TVal>::has(TKey key) {

    BSTree<TKey, TVal>::node* current = root;

    // Loop until there are no nodes left to check.
    while(current) {
        // If the current key equals to the search key (@param1), the node is found; return
        if(key == current->key) {
            return true;
        }
        if(key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
    
}
/*
*   Function: findNode
*   @param1: TKey key : Lookup key.
*   @returns: The read-only reference of the node with given key.
*   
*   Description: This function finds the node with given key (@param1) and
*                returns its read-only reference.
*
*/
template <typename TKey, typename TVal> const typename BSTree<TKey, TVal>::node* BSTree<TKey, TVal>::findNode(TKey key) {

    // Same procedure with function "has"
    BSTree<TKey, TVal>::node* current = root;
    
    while(current) {
        if(key == current->key) {
            return current;
        }
        if(key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}
/*
*   Function: getVal
*   @param1: TKey key : Lookup key.
*   @returns: The read-only reference of the data that the key leads to.
*   
*   Description: This function finds the node with given key (@param1) and
*                returns its data field's read-only reference.
*
*/
template <typename TKey, typename TVal> const TVal* BSTree<TKey, TVal>::getVal(TKey key) {
    
    // Same procedure with function "has"
    BSTree<TKey, TVal>::node* current = root;

    while(current) {
        if(key == current->key) {
            return &(current->data);
        }
        if(key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return NULL;
}
/*
*   Function: change
*   @param1: TKey key : Lookup key.
*   @param2: TVal data : New data to change to.
*   @returns: true if successful, false otherwise.
*   
*   Description: This function finds the node with given key (@param1) and
*                changes its data field with the given data (@param2).
*
*/
template <typename TKey, typename TVal> bool BSTree<TKey, TVal>::change(TKey key, TVal data) {

    BSTree<TKey, TVal>::node** current = &root;

    // Loop until there are no nodes left to check.
    while(*current) {
        // If the current key equals to the search key (@param1),
        // change the node's data to the given data (@param2).
        if(key == (*current)->key) {
            (*current)->data = data;
            return true;
        }

        if(key < (*current)->key) {
            current = &(*current)->left;
        } else {
            current = &(*current)->right;
        }
    }
    return false;
}

/*
*   Function: begin
*   @returns: An inorder BSTree iterator object at the 
*             beginning of the tree (node with smallest key)
*/
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator BSTree<TKey, TVal>::begin() {

    BSTree<TKey, TVal>::node* current = root;

    // Check if the tree is empty
    if(current != NULL) {
        // If it's not, make the iterator object point to the leftmost node of the tree.
        while(current->left != NULL) current = current->left;
    }

    // Create the object with the private constructor and return it.
    // If the tree is empty, the iterator will point to the end of the tree (which is NULL).
    return iterator(current,this);

}
/*
*   Function: begin (overload)
*   @param1: int start : Offset
*   @returns: An inorder BSTree iterator object that points to the node 
*             at the given position (@param1) in the tree.
*/
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator BSTree<TKey, TVal>::begin(int start) {

    // Create an iterator that points to the first element.
    BSTree<TKey, TVal>::iterator temp = this->begin();
    
    // Iterate by desired amount (@param1).
    int i=0;
    while(i<start && temp != this->end()) {
        temp++;
        i++;
    }
    // Return it at the current position.
    return temp;
}
/*
*   Function: rbegin
*   @returns: An inorder BSTree iterator object that points to the
*             last node in the tree (node with greatest key).
*
*   Description: rbegin = reverse begin.
*/
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator BSTree<TKey, TVal>::rbegin() {

    BSTree<TKey, TVal>::node* current = root;
    
    if(current != NULL) {
        // Find the rightmost element
        while(current->right != NULL) current = current->right;
    }

    return iterator(current,this);

}

/*
*   Function: end
*   @returns: An inorder BSTree iterator object at the end of 
*             the tree (an iterator that points to a NULL node).
*
*   Description: Used to compare with other iterators, to represent the end condition.
*/
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator BSTree<TKey, TVal>::end() {

    return iterator(NULL,this);

}

/*
*********   Private Methods
*/

/*
*   Creates and initializes a node struct
*/

template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::node* BSTree<TKey, TVal>::_newNode(TKey key, TVal data) {
    node* newNode = new node;
    newNode->data = data;
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

/*
*   Destroys the tree with given root by freeing all nodes it possesses recursively
*/

template <typename TKey, typename TVal> void BSTree<TKey, TVal>::_deleteTree(node* root) {
    if(root != NULL) {
        _deleteTree(root->left);
        _deleteTree(root->right);
        delete root;
    }
}

/*
*   RECURSIVE PRINTERS
*/ 
template <typename TKey, typename TVal> void BSTree<TKey, TVal>::_printInOrder(node* root) {
    if(root != NULL) {
        _printInOrder(root->left);
        std::cout << root->data << " ";
        _printInOrder(root->right);
    }
}
template <typename TKey, typename TVal> void BSTree<TKey, TVal>::_printPreOrder(node* root) {
    if(root != NULL) {
        std::cout << root->data << " ";
        _printPreOrder(root->left);
        _printPreOrder(root->right);
    }
}
template <typename TKey, typename TVal> void BSTree<TKey, TVal>::_printPostOrder(node* root) {
    if(root != NULL) {
        _printPostOrder(root->right);
        _printPostOrder(root->left);
        std::cout << root->data << " ";
    }
}




/*
*
********* BSTREE ITERATOR SUBCLASS
*
*/

template <typename TKey, typename TVal> const TVal BSTree<TKey, TVal>::iterator::get() {
    return currentNode->data;
}

template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator& BSTree<TKey, TVal>::iterator::operator= (const iterator& rhs) {

    this->currentNode = rhs.currentNode;
    this->tree = rhs.tree;
    return *this;

}

// PRE-INCREMENT
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator& BSTree<TKey, TVal>::iterator::operator++ () {

    if(currentNode == NULL) {
            currentNode = tree->root;
            // If it is still NULL, then the tree is empty.

            while( currentNode->left != NULL)  currentNode =  currentNode->left;

    } else {

        if(currentNode->right != NULL) {
            currentNode = currentNode->right;
            while(currentNode->left != NULL) {
                currentNode = currentNode->left;
            }

        } else {
            BSTree<TKey, TVal>::node* parent = currentNode->parent;
            while(parent != NULL && currentNode != parent->left) {
                currentNode = parent;
                parent = parent->parent;
            }
            currentNode = parent;
        }
    }


    return *this;
}

// POST-INCREMENT
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator BSTree<TKey, TVal>::iterator::operator++ (int) {

    BSTree<TKey, TVal>::iterator temp = *this;
    
    if(currentNode == NULL) {
            currentNode = tree->root;
            // If it is still NULL, then the tree is empty.

            while( currentNode->left != NULL)  currentNode =  currentNode->left;

    } else {

        if(currentNode->right != NULL) {
            currentNode = currentNode->right;
            while(currentNode->left != NULL) {
                currentNode = currentNode->left;
            }

        } else {

            BSTree<TKey, TVal>::node* parent = currentNode->parent;
            while(parent != NULL && currentNode != parent->left) {
                currentNode = parent;
                parent = parent->parent;
            }
            currentNode = parent;
        }
    }


    return temp;
}

// PRE-DECREMENT
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator& BSTree<TKey, TVal>::iterator::operator-- () {

    if(currentNode == NULL) {
            currentNode = tree->root;
            // If it is still NULL, then the tree is empty.

            // Go to the rightmost leaf.
            while( currentNode->right != NULL)  currentNode =  currentNode->right;

    } else {

        if(currentNode->left != NULL) {
            currentNode = currentNode->left;
            while(currentNode->right != NULL) {
                currentNode = currentNode->right;
            }

        } else {
            BSTree<TKey, TVal>::node* parent = currentNode->parent;
            while(parent != NULL && currentNode != parent->right) {
                currentNode = parent;
                parent = parent->parent;
            }
            currentNode = parent;
        }
    }


    return *this;
}
// POST-DECREMENT
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator BSTree<TKey, TVal>::iterator::operator-- (int) {

    BSTree<TKey, TVal>::iterator temp = *this;

    if(currentNode == NULL) {
            currentNode = tree->root;
            // If it is still NULL, then the tree is empty.

            // Go to the rightmost leaf.
            while( currentNode->right != NULL)  currentNode =  currentNode->right;

    } else {

        if(currentNode->left != NULL) {
            currentNode = currentNode->left;
            while(currentNode->right != NULL) {
                currentNode = currentNode->right;
            }

        } else {
            BSTree<TKey, TVal>::node* parent = currentNode->parent;
            while(parent != NULL && currentNode != parent->right) {
                currentNode = parent;
                parent = parent->parent;
            }
            currentNode = parent;
        }
    }


    return temp;
}


template <typename TKey, typename TVal> bool BSTree<TKey, TVal>::iterator::operator== (const BSTree<TKey, TVal>::iterator& rhs) const {
    return this->currentNode == rhs.currentNode;
}
template <typename TKey, typename TVal> bool BSTree<TKey, TVal>::iterator::operator!= (const BSTree<TKey, TVal>::iterator& rhs) const {
    return this->currentNode != rhs.currentNode;
}
template <typename TKey, typename TVal> const typename BSTree<TKey, TVal>::node& BSTree<TKey, TVal>::iterator::operator* () const {
    return *(this->currentNode);
}

/*
*   NOT NEEDED AND DANGEROUS
*

// ADDITION
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator& BSTree<TKey, TVal>::iterator::operator+ (const int rhs) {
    for(int i=0; i<rhs; i++) (*this)++;
    return *this;
}
// SUBTRACTION
template <typename TKey, typename TVal> typename BSTree<TKey, TVal>::iterator& BSTree<TKey, TVal>::iterator::operator- (const int rhs) {
    for(int i=0; i<rhs; i++) (*this)--;
    return *this;
}*/


template class BSTree<int, int>;
template class BSTree<int, const char*>;

template class BSTree<char, int>;
template class BSTree<char, const char*>;

template class BSTree<const char*, int>;
template class BSTree<const char*, const char*>;

template class BSTree<float, const char*>;
//...
