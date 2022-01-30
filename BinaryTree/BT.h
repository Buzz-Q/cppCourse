#ifndef BT_H
#define BT_H

class BT
{
	private:
		struct node{
			int key;
			node* left;
			node* right; 
		};
		
		node* root;
		node* createleaf(int key);

		void addPrivateleaf(int key, node* ptr);
		void orderPrintPrivate(node* ptr);

		node* returnNode(int key);
		node* returnNodePrivate(int key, node* ptr);
		
		int findSmallestPrivate(node* ptr);
		
		void removeNodePrivate(int key, node* parent);
		void removeRootMatch();
		void removeMatch(node* parent, node* match, bool left);
		
		void removeSubtree(node* ptr);


		
	public:
		BT();
		~BT();
		
		void addleaf(int key);
		void printTree();
		
		int returnRoot();
		void printChildren(int key);
		
		int findSmallest();
		void removeNode(int key);
		
};

#endif
