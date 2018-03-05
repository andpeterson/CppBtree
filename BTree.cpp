template <class T>
class BTreeNode()
{
	T *keys; //
	int maxKeys; //the max amount of keys in each node
	BTreeNode **children; //array of children
	int numberOfKeys; //current number of keys in node
	bool isLeaf; //is this the last child?
	public:
		BTreeNode(int _t, bool _leaf); //need to do
		void traverse(); //
		void insertNotFull(); //inserts value into child or if leaf into self
		void splitChild();

	friend class BTree;
};

BTreeNode::traverse(){
	int i;
	for(i = 0; i <  numberOfKeys; ++i){
		if(!isLeaf)
			children[i]->traverse();
		cout << " " << keys[i];
	}
	if(!isLeaf){
		children[i]->traverse();
	}
}

BTreeNode::insert(int new_key){
	//if root is equal to NULL and tree is empty we will allocate 
	//the root of the tree and insert the key there
	if(root == NULL)
	{
		//create root node
		root = new BTreeNode(maxKeys, true);
		//give the first key in root the new key
		root->keys[0] = new_key;
		//set the number of keys in root to 1	
		root->numberOfKeys = 1;
	}
	else //else the tree isn't empty
	{
		//if root is full create a new root and split the old one
		if(root->numberOfKeys >= maxKeys){
			//allocate a new root
			BTreeNode *newroot = new BTreeNode(t, false);
			//make the old root a child of the new root
			newroot->children[0] = root;
			//split the old root (raising the middle value)
			newroot->splitChild(0, root);
			//find which child to put the new value into
			if(newroot->keys[0] < new_key)
				newroot->children[0]->insertNotFull(); //insert into the lhs child
			else
				newroot->children[1]->insertNotFull(); //insert into the rhs child
			//set root to the new root
			root = newroot;
		}
		else //if not full then just insert the value
			root->insertNotFull();			
	}
}

BTreeNode::insertNotFull(int new_key){
	int key_i = numberOfKeys-1//iterator for iterating through keys in node
	
	//if this is the last child
	if(isLeaf){
		//Loops through the keys backwards, shifting all the keys 
		//lower than the new_key to the right then inserting the new key
		while(key_i >= 0 && keys[key_i] > newkey){
			keys[key_i+1] = keys[key_i]; //shift key over
			--key_i; //move new key down
		}
		keys[i+1] = new_key;
		++numberOfKeys;
	}
	else{ //if not the last child (!leaf)
		//find the child for the new key by checking the key values
		while(key_i <= && keys[key_i] > new_key)
			--key_i; //if key at position key_i is greater than the new key decrement key_i
		
		//See if the found child is full
		if(children[key_i+1]->numberOfKeys >= maxKeys){
			splitChild(key_i+1, children[key_i+1])
			
			if(keys[key_i+1] < new_key)
				++key_i;
		}
		children[key_i+1]->insertNotFull(new_key);
		
	}
}




