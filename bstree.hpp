#ifndef __bstree_included
#define __bstree_included


enum TRAVERSAL_METHOD {
    INORDER,
    PREORDER,
    POSTORDER
};
template <typename TKey, typename TVal> class BSTree {

    
    public: 
        typedef struct node {
            TKey key;
            TVal data;
            struct node* left;
            struct node* right;
            struct node* parent;

        } node;

        class iterator {
            public:
                iterator();
                bool operator== (const iterator& rhs) const;
                bool operator!= (const iterator& rhs) const;
                const node& operator* () const;
                iterator& operator= (const iterator& rhs);
                iterator& operator++ ();
                iterator operator++ (int);
                iterator& operator-- ();
                iterator operator-- (int);
                /*iterator& operator+ (const int rhs);
                iterator& operator- (const int rhs);*/
                const TVal get();

            private: 
                node* currentNode;
                BSTree<TKey, TVal>* tree;
                iterator(node* currentNode, BSTree<TKey, TVal>* tree) : currentNode(currentNode), tree(tree) {};
                
            friend class BSTree;
            
        };

        BSTree() {};
        ~BSTree();

        void insert(TKey, TVal);
        bool del(TKey);
        bool remove(TKey); // identical with "del"
        bool change(TKey, TVal);
        void print(TRAVERSAL_METHOD);
        bool has(TKey);
        const node* findNode(TKey);
        const TVal* getVal(TKey);


        iterator begin();
        iterator begin(int);
        iterator rbegin(); // returns a forward iterator at the last element, not a reverse iterator.
        iterator end();

    
    private:
        

        node* root = NULL;

        node* _insert(node*, TKey, TVal);
        node* _newNode(TKey, TVal);
        void _deleteTree(node* root);
        void _printInOrder(node*);
        void _printPreOrder(node*);
        void _printPostOrder(node*);
        bool _has(node*, TKey);
 

    
};

#endif