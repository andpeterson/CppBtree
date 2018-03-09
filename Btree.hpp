#include <iostream>

template <class T>
class BTreeNode
{
	T *keys; //
	int maxKeys; //the max amount of keys in each node
	BTreeNode **children; //array of children
	int numberOfKeys;
	bool isLeaf;
	public:
		BTreeNode(int _t, bool _leaf); //need to do
		void traverse();
		void insertNotFull(T);
		void splitChild(int i, BTreeNode *lhsNode);
	template <class>
	friend class BTree;
};


template<class T>
class BTree{
	BTreeNode <T> *root;
	int maxKeys;
	public:
		BTree(int _maxKeys)
		{  root = nullptr;  maxKeys = _maxKeys; }
		void traverse()
		{  if (root != nullptr) root->traverse(); }
		void insert(T new_key);
	private:
		T * tree;
	
};


template <typename T>
BTreeNode<T>::BTreeNode(int _t, bool _leaf){
	maxKeys = _t;
	isLeaf = _leaf;
	
	keys = new T[2*maxKeys-1];
	children = new BTreeNode *[2*maxKeys-1];
	
	numberOfKeys = 0;
}

template <typename T>
void BTreeNode<T>::traverse(){
	int i;
	for(i = 0; i <  numberOfKeys; ++i){
		if(!isLeaf)
			children[i]->traverse();
		std::cout << " " << keys[i];
	}
	if(!isLeaf){
		children[i]->traverse();
	}
}

template <typename T>
void BTree<T>::insert(T new_key){
	//if root is equal to nullptr and tree is empty we will allocate 
	//the root of the tree and insert the key there
	if(root == nullptr)
	{
		//create root node
		root = new BTreeNode<T>(maxKeys, true);
		//give the first key in root the new key
		root->keys[0] = new_key;
		//set the number of keys in root to 1	
		root->numberOfKeys = 1;
	}
	else //else the tree isn't empty
	{
		//if root is full create a new root and split the old one
		if(root->numberOfKeys >= 2*maxKeys-1){
			//allocate a new root
			BTreeNode<T> *newroot = new BTreeNode<T>(maxKeys, false);
			//make the old root a child of the new root
			newroot->children[0] = root;
			//split the old root (raising the middle value)
			newroot->splitChild(0, root);
			//find which child to put the new value into
			if(newroot->keys[0] < new_key)
				newroot->children[1]->insertNotFull(new_key); //insert into the lhs child
			else
				newroot->children[0]->insertNotFull(new_key); //insert into the rhs child
			//set root to the new root
			root = newroot;
		}
		else //if not full then just insert the value
			root->insertNotFull(new_key);			
	}
}

template <typename T>
void BTreeNode<T>::insertNotFull(T new_key){
	int key_i = numberOfKeys-1;//iterator for iterating through keys in node
	
	//if this is the last child
	if(isLeaf){
		//Loops through the keys backwards, shifting all the keys 
		//lower than the new_key to the right then inserting the new key
		while(key_i >= 0 && keys[key_i] > new_key){
			keys[key_i+1] = keys[key_i]; //shift key over
			--key_i; //move new key down
		}
		keys[key_i+1] = new_key;
		++numberOfKeys;
	}
	else{ //if not the last child (!leaf)
		//find the child for the new key by checking the key values
		while(key_i <= 0 && keys[key_i] > new_key)
			--key_i; //if key at position key_i is greater than the new key decrement key_i
		
		//See if the found child is full
		if(children[key_i+1]->numberOfKeys == 2*maxKeys-1){
			splitChild(key_i+1, children[key_i+1]);
			
			if(keys[key_i+1] < new_key)
				key_i++;
		}
		children[key_i+1]->insertNotFull(new_key);
	}
}

template <typename T>
void BTreeNode<T>::splitChild(int i, BTreeNode *lhsNode){
	// Create a new node which is going to store (t-1) keys
    // of y
    BTreeNode *rhsNode = new BTreeNode<T>(lhsNode->maxKeys, lhsNode->isLeaf);
    rhsNode->numberOfKeys = maxKeys - 1;
 
    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < maxKeys-1; j++)
        rhsNode->keys[j] = lhsNode->keys[j+maxKeys];
 
    // Copy the last t children of y to z
    if (lhsNode->isLeaf == false)
    {
        for (int j = 0; j < maxKeys; j++)
            rhsNode->children[j] = lhsNode->children[j+maxKeys];
    }
 
    // Reduce the number of keys in y
    lhsNode->numberOfKeys = maxKeys - 1;
 
    // Since this node is going to have a new child,
    // create space of new child
    for (int j = numberOfKeys; j >= i+1; j--)
        children[j+1] = children[j];
 
    // Link the new child to this node
    children[i+1] = rhsNode;
 
    // A key of y will move to this node. Find location of
    // new key and move all greater keys one space ahead
    for (int j = numberOfKeys-1; j >= i; j--)
        keys[j+1] = keys[j];
 
    // Copy the middle key of y to this node
    keys[i] = lhsNode->keys[maxKeys-1];
 
    // Increment count of keys in this node
    numberOfKeys = numberOfKeys + 1;
}