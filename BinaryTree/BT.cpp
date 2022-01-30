#include <iostream>
#include <cstdlib>

#include "BT.h"

using namespace std;


BT::BT(){
	root = NULL;
}

BT::node* BT::createleaf(int key){
	node* n = new node;
	n->key = key;
	n->left= NULL;
	n->right = NULL;
}

void BT::addleaf(int key){
	addPrivateleaf(key, root);
}


void BT::addPrivateleaf(int key, node* ptr){
	if (root == NULL){
		root = createleaf(key);
	}else if(key < ptr->key){
		if (ptr->left != NULL){
			addPrivateleaf(key, ptr->left);
		}else{
			ptr->left = createleaf(key);
		}
	}else if(key > ptr->key){
		if (ptr->right != NULL){
			addPrivateleaf(key, ptr->right);
		}else{
			ptr->right = createleaf(key);
		}
	}else{
		cout<<"The key"<< key<< " is already in the tree"<<endl;
		}
}

void BT::printTree(){
	orderPrintPrivate(root);
}

void BT::orderPrintPrivate(node* ptr){
	if (root != NULL){
		if(ptr->left != NULL){
			orderPrintPrivate(ptr->left);
		}
		cout<<ptr->key<<" ";
		if(ptr->right != NULL){
			orderPrintPrivate(ptr->right);
		}
		
		
	}else{
		cout<<"The tree is empty\n";
	}
	
	
}

BT::node* BT::returnNode(int key){
	return returnNodePrivate(key, root);
}

BT::node* BT::returnNodePrivate(int key, node* ptr){
	if(ptr != NULL){
		if(ptr->key == key){
			return ptr;
		}else{
			if(key < ptr->key){
				return returnNodePrivate(key, ptr->left);
			}else{
				return returnNodePrivate(key, ptr->right);
			}
		}
	}else{
		return NULL;
	}
}

int BT::returnRoot(){
	if (root != NULL){
		return root->key;
	}else{
		return -1000;
	}
}

void BT::printChildren(int key){
	node* ptr = returnNode(key);
	
	if(ptr != NULL){
		
		cout<<"parent node= "<<ptr->key<<endl;
		
		ptr->left == NULL ?
		cout<<"LeftChild = NULL\n" :
			cout<<"left Child = "<< ptr->left->key<<endl;
	
		ptr->right == NULL ?
		cout<<"right child = NULL\n" :
			cout<<"right Child = "<< ptr->right->key<<endl;			
			
	}else{
		cout<<"key "<<key<<"doesn't exist\n";
	}
}

int BT::findSmallest(){
	return findSmallestPrivate(root);
}

int BT::findSmallestPrivate(node* ptr){
	if (root == NULL){
		cout<<"The tree is empty\n";
		return -1000;
	}else{
		if(ptr->left != NULL){
			return findSmallestPrivate(ptr->left);
		}else{
			return ptr->key;
		}
	}
}

void BT::removeNode(int key){
	removeNodePrivate(key, root);
}
void BT::removeNodePrivate(int key, node* parent){
	if(root != NULL){
		if(root->key == key){
			removeRootMatch();
		}else if((key < parent->key) && (parent->left != NULL)){
				parent->left->key == key ?
				removeMatch(parent, parent->left, true) :
				removeNodePrivate(key, parent->left);
			}else if((key > parent->key) && (parent->right != NULL)){
				parent->right->key == key ?
				removeMatch(parent, parent->right, false) :
				removeNodePrivate(key, parent->right);
			}else{
				cout<<"The key "<<key<<" wasn't found\n";
			}
		}else{
		cout<<"The tree is empty\n";
	}
	
}

void BT::removeRootMatch(){
	if(root != NULL){
		node* delPtr = root;
		int rootKey = root->key;
		int smallestInRightSub;
		
		if ((root->left == NULL ) && (root->right == NULL)){
			root = NULL;
			delete delPtr;
		}else if((root->left == NULL) && (root->right != NULL)){
			root = root->right;
			delPtr->right = NULL;
			delete delPtr;
			cout<<"Root "<<root->key<<" has been deleted\n";
			cout<<"The new root is "<<root->key<<endl;			
		}else if((root->left != NULL) && (root->right == NULL)){
			root = root->left;
			delPtr->left = NULL;
			delete delPtr;
			cout<<"Root"<<root->key<<" has been deleted\n";
			cout<<"The new root is "<<root->key<<endl;			
		}else{
			smallestInRightSub = findSmallestPrivate(root->right);
			removeNodePrivate(smallestInRightSub, root);
			root->key = smallestInRightSub;
			cout<<"the root key "<<rootKey<<" was overwritten with "<<root->key<<endl;;
		}
	}else{
		cout<<"can't remove root, the tree is empty\n";
	}
}


void BT::removeMatch(node* parent, node* match, bool left){
	if (root != NULL){
		node* delPtr;
		int matchKey = match->key;
		int smallestInRightSub;
		
		if((match->left == NULL) && (match->right == NULL)){
			delPtr = match;
			left == true ? parent->left = NULL : parent->right = NULL;
			delete delPtr;
			cout<<"The node containing "<<matchKey<<" was removed\n";
		}else if ((match->left == NULL) && (match->right != NULL)){
			left == true? parent->left = match->right : parent->right = match->right;
			match->right = NULL;
			delPtr = match;
			delete delPtr;
			cout<<"The node containing "<<matchKey<<" was removed\n";
		}else if((match->left != NULL) && (match->right == NULL)){
			left == true? parent->left = match->left : parent->right = match->left;
			match->left = NULL;
			delPtr = match;
			delete delPtr;
			cout<<"The node containing "<<matchKey<<" was removed\n";
			}else{
				smallestInRightSub = findSmallestPrivate(match->right);
				removeNodePrivate(smallestInRightSub, match);
				match->key = smallestInRightSub;
			}
	}else{
		cout<<"Can't remove the match, the tree is empty\n";
	}
}

BT::~BT(){
	removeSubtree(root);
}

void BT::removeSubtree(node* ptr){
	if (ptr != NULL){
		if (ptr->left!= NULL){
			removeSubtree(ptr->left);
		}if (ptr->right!= NULL){
			removeSubtree(ptr->right);
		}
		cout<<ptr->key<<" deleted\n";
		delete ptr;
	}
}


