#pragma once
#include <iostream>

template <typename K, typename I>

class avlTree {

    public:
        using Key = K;
        using Item = I;

        avlTree() = default;
        void displayEntries();
        void insert(Key key, Item item);;
        Item* lookup(Key key);;
        void displayTree();;
        void remove(Key key);;
        avlTree(const avlTree<K, I> &);;

	private:

        struct Node {
            Key key;
            Item item;
            Node* leftChild;
            Node* rightChild;
            int balanceFactor;

            Node(Key key, Item & item) {
                this->item = item;
                this->key = key;
                leftChild = nullptr;
                rightChild = nullptr;
                balanceFactor = 0;
            }
        };
		Node* root = nullptr;

        static bool isLeaf(Node* n );
        static Item* lookupRec(Key key,  Node* currentNode);
        static void insertRec(Key key, Item & item, Node* & currentNode);
        static void displayEntriesRec(Node* givenNode);
        static void displayTreeRec(Node* givenNode, int level);
        static Node* findMin(Node* & node);
        void deepCopy(Node* original);
        avlTree & operator=(const avlTree<K,I> & bst);
        static void rotateRight(Node* & localRoot);
        static void rotateLeft(Node* & localRoot);

};

template<typename K, typename I>
void avlTree<K, I>::displayEntries() {
    displayEntriesRec(root);
}

template<typename K, typename I>
void avlTree<K, I>::insert(Key key, Item item) {
    if (root == nullptr) {
        root = new Node(key, item);
    }
    else insertRec(key, item,root);
}

template<typename K, typename I>
typename avlTree<K,I>::Item *avlTree<K, I>::lookup(Key key) {
    return lookupRec(key, root);
}

template<typename K, typename I>
void avlTree<K, I>::displayTree() {
    displayTreeRec(root, 0);
}

template<typename K, typename I>
void avlTree<K, I>::remove(Key key) {
    //Find the node
    Node* nodeToRemove = nullptr;
    Node* currentNode = root;
    Node* prevNode = root;
    bool found = false;
    while (!found) {
        if (key == currentNode->key) {
            nodeToRemove = currentNode;
            found = true;
        }
        else if (key > currentNode->key) {
            prevNode = currentNode;
            currentNode = currentNode->rightChild;
        }
        else {
            prevNode = currentNode;
            currentNode = currentNode->leftChild;
        }
    }
    Node* & pointerFromParent =  (nodeToRemove->key < prevNode->key) ? prevNode->leftChild : prevNode->rightChild;

    //Both children are leaves
    if (isLeaf(nodeToRemove->leftChild) && isLeaf(nodeToRemove->rightChild)) {
        pointerFromParent = nullptr;
        delete (nodeToRemove);
        delete(pointerFromParent);
    }

        //Neither child is a leaf
    else if ((!isLeaf(nodeToRemove->leftChild)) && (!isLeaf(nodeToRemove->rightChild))) {

        //Identify Minimum Node
        Node* minNode = findMin(nodeToRemove->rightChild);

        //Reattach branches to tree
        minNode->leftChild = nodeToRemove->leftChild;
        minNode->rightChild = nodeToRemove->rightChild;

        //Reattach newly formed tree to root tree
        pointerFromParent = minNode;
        delete(pointerFromParent);
        delete(nodeToRemove);
    }

        //One child is a leaf
    else  {
        if (!isLeaf(nodeToRemove->rightChild)) {
            pointerFromParent = nodeToRemove->rightChild;
            delete(nodeToRemove);
            delete(pointerFromParent);
        }
        else {
            pointerFromParent = nodeToRemove->leftChild;
            delete(nodeToRemove);
            delete(pointerFromParent);
        }
    }
}

template<typename K, typename I>
avlTree<K, I>::avlTree(const avlTree<K,I> & original) {
    deepCopy(original.root);
}

template<typename K, typename I>
bool avlTree<K, I>::isLeaf(avlTree::Node *n) {
    return n == nullptr;
}

template<typename K, typename I>
typename avlTree<K,I>::Item *avlTree<K, I>::lookupRec(Key key, avlTree::Node *currentNode) {
    if (isLeaf(currentNode)) return nullptr;
    else{
        if (key == currentNode->key) return &currentNode->item;
        else if (key > currentNode->key) {
            return lookupRec(key, currentNode->rightChild);

        }
        else if (key < currentNode->key) {
            return lookupRec(key, currentNode->leftChild);
        }

        //This should never be reached
        return nullptr;
    }
}

template<typename K, typename I>
void avlTree<K, I>::insertRec(Key key, Item &item, avlTree::Node *&currentNode) {
    if (key == currentNode->key) {
        currentNode->item = item;
    }
    else if (key > currentNode->key) {
        if (isLeaf(currentNode->rightChild)) {
            currentNode->rightChild = new Node(key, item);
        }
        else insertRec(key, item, currentNode->rightChild);
    }
    else {
        if (isLeaf(currentNode->leftChild)) {
            currentNode->leftChild = new Node(key, item);
        }
        else insertRec(key, item, currentNode->leftChild);
    }
}

template<typename K, typename I>
void avlTree<K, I>::displayEntriesRec(avlTree::Node *givenNode) {
    if (!isLeaf(givenNode)){
        //Traverse left
        displayEntriesRec(givenNode->leftChild);

        //Visit the Node?
        std::cout << givenNode->key << " " << givenNode->item << std::endl;

        //Traverse Right
        displayEntriesRec(givenNode->rightChild);

    }
}

template<typename K, typename I>
void avlTree<K, I>::displayTreeRec(avlTree::Node *givenNode, int level) {
    if (!isLeaf(givenNode)){
        for (int i=0; i < level; i++) std::cout<< '-';
        std::cout << " Key: " << givenNode->key
                  << " Item: " << givenNode->item
                  << " Balance Factor: " << givenNode->balanceFactor <<std::endl;

        displayTreeRec(givenNode->leftChild, level + 1);
        displayTreeRec(givenNode->rightChild, level + 1);
    }
    else {
        for (int i=0; i < level; i++) std::cout<< " ";
        std::cout << "LEAF" << std::endl;
    }
}

template<typename K, typename I>
typename avlTree<K,I>::Node *avlTree<K, I>::findMin(avlTree::Node *&node) {
    if(isLeaf(node->leftChild->leftChild)){
        Node* tempNode = node->leftChild;
        node->leftChild = node->leftChild->rightChild;
        return tempNode;
    }
    else {
        findMin(node->leftChild);
    }
}

template<typename K, typename I>
void avlTree<K, I>::deepCopy(avlTree::Node *original) {
    //Valid but inefficient
    if (!isLeaf(original)) {
        //Copy the node
        this->insert(original->key, original->item);

        //Traverse left
        deepCopy(original->leftChild);

        //Traverse Right
        deepCopy(original->rightChild);
    }
}

template<typename K, typename I>
void avlTree<K, I>::rotateRight(avlTree::Node *&localRoot) {
    Node* b = localRoot;
    assert(!isLeaf(b));
    Node* a = b->leftChild;
    assert(!isLeaf(a));

    int tempBalanceA = a->balanceFactor;
    int tempBalanceB = b->balanceFactor;

    a->rightChild = localRoot;
    b->leftChild = a->rightChild;

    b->balanceFactor = tempBalanceB + 1 + std::max(-a->balanceFactor,0);
    a->balanceFactor = tempBalanceA + a + std::max(b->balanceFactor,0);

    localRoot = a;
}

template<typename K, typename I>
void avlTree<K, I>::rotateLeft(avlTree::Node *&localRoot) {
    Node* a = localRoot;
    assert(!isLeaf(a));
    Node* b = a->rightChild;
    assert(!isLeaf(b));

    int tempBalanceA = a->balanceFactor;
    int tempBalanceB = b->balanceFactor;

    b->leftChild = localRoot;
    a->rightChild = b->leftChild;

    a->balanceFactor = tempBalanceA - 1 - std::max(tempBalanceB, 0);
    b->balanceFactor = tempBalanceB - 1 - std::max(-tempBalanceA, 0);

    localRoot = b;
}

//std::ostream & operator<<(std::ostream &, const typename avlTree<K, I> &);