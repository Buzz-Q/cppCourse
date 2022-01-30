#include <iostream>
#include <cstdlib>
#include <string>

#include "BT.h"

using namespace std;

int main(){
	
	int tree[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
	
	BT t;
	cout<<"Printing tree in order\nBefor adding numbers\n";
	
	t.printTree();
		
	for(int i=0; i<16; i++){
		t.addleaf(tree[i]);
	}
	
	cout<<"Printing tree in order\nAfter adding numbers\n";
	t.printTree();
	cout<<endl<<endl;
	
	t.printChildren(t.returnRoot());

/*	
	//to show all nodes parent child relationship
	for(int i=0; i<16; i++){
			t.printChildren(tree[i]);
		}
*/
//	t.removeNode(3);
	t.printTree();
	cout<<endl;
	return 0;
}
