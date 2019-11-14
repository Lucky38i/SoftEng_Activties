#pragma once
#include <iostream>

template <typename K, typename I>

class binarySearchTree {

    public:
        using Key = K;
        using Item = I;

        binarySearchTree() = default;
        void displayEntries(){
            displayEntriesRec(root);
        };
        void insert(Key key, Item item){
            if (root == nullptr) {
                root = new Node(key, item);
            }
            else insertRec(key, item,root);
        };
        Item* lookup(Key key){
            return lookupRec(key, root);
        };
        void displayTree(){
            displayTreeRec(root, 0);
        };
        void remove(Key key){
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
        };
        binarySearchTree(const binarySearchTree<K, I> & original){
            deepCopy(original.root);
        };

	private:
		struct Node{
            Key key;
            Item item;
            Node* leftChild;
            Node* rightChild;

            Node(Key key, Item & item) {
                this->item = item;
                this->key = key;
                leftChild = nullptr;
                rightChild = nullptr;
            }
		};

		Node* root = nullptr;

        static bool isLeaf(Node* n ){
            return n == nullptr;
        };
        static Item* lookupRec(Key key,  Node* currentNode){
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
        };
        static void insertRec(Key key, Item & item, Node* & currentNode){
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
        };
        static void displayEntriesRec(Node* givenNode){
            if (!isLeaf(givenNode)){
                //Traverse left
                displayEntriesRec(givenNode->leftChild);

                //Visit the Node?
                std::cout << givenNode->key << " " << givenNode->item << std::endl;

                //Traverse Right
                displayEntriesRec(givenNode->rightChild);

            }
        };
        static void displayTreeRec(Node* givenNode, int level){
            if (!isLeaf(givenNode)){
                for (int i=0; i < level; i++) std::cout<< " ";
                std::cout << givenNode->key << " " << givenNode->item << std::endl;

                displayTreeRec(givenNode->leftChild, level + 1);
                displayTreeRec(givenNode->rightChild, level + 1);
            }
            else {
                for (int i=0; i < level; i++) std::cout<< " ";
                std::cout << "LEAF" << std::endl;
            }
        };
        static Node* findMin(Node* & node){
            if(isLeaf(node->leftChild->leftChild)){
                Node* tempNode = node->leftChild;
                node->leftChild = node->leftChild->rightChild;
                return tempNode;
            }
            else {
                findMin(node->leftChild);
            }
        };
        void deepCopy(Node* original){
            //Valid but inefficient
            if (!isLeaf(original)) {
                //Copy the node
                this->insert(original->key, original->item);

                //Traverse left
                deepCopy(original->leftChild);

                //Traverse Right
                deepCopy(original->rightChild);
            }
        };
        binarySearchTree & operator=(const binarySearchTree<K,I> & bst){
            //TODO fullfill this
        };
        static void rotateRight(Node* & localRoot){
            Node* b = localRoot;
            assert(!isLeaf(b));
            Node* a = b->leftChild;
            assert(!isLeaf(a));

            a->rightChild = localRoot;
            b->leftChild = a->rightChild;

            localRoot = a;
        };
        static void rotateLeft(Node* & localRoot){
            Node* a = localRoot;
            assert(!isLeaf(a));
            Node* b = a->rightChild;
            assert(!isLeaf(b));

            b->leftChild = localRoot;
            a->rightChild = b->leftChild;

            localRoot = b;
        };

};

//std::ostream & operator<<(std::ostream &, const typename binarySearchTree<K, I> &);