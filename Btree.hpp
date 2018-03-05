template <class T>
class BTreeNode()
{
	T *keys; //
	int maxKeys; //the max amount of keys in each node
	BTreeNode **children; //array of children
	int numberOfKeys;
	bool isLeaf;
	public:
		BTreeNode(int _t, bool _leaf); //need to do
		void traverse();
		void insertNotFull();
		void splitChild();

	friend class BTree;
};


template<class T>
class BTree{
	BTreeNode *root;
	int maxKeys;
	public:
		BTree(int _maxKeys);
		{  root = NULL;  maxKeys = _maxKeys; }
		void traverse()
		{return (root != NULL) root->traverse();}
		void insert(int new_key)
	private:
		T * tree
}