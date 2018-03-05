

template <class T>
class BTreeNode()
{
	int *keys;
	int t;
	BTreeNode **children;
	int n;
	bool isLeaf;
	public:
		BTreeNode(int _t, bool _leaf);
		
		void traverse();
	BTreeNode *search(int k);

	friend class BTree;
};


template<class T>
class BTree{
	BTreeNode *root;
	public:
		BTree(int _t);
		void traverse()
		{return (root != NULL) root->traverse();}
	private:
		T * tree
}