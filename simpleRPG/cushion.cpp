#include "cushion.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int cushion::intPut(){
	int in;

	cin>>in;


	while ( cin.fail() ){		//When the input is not an integer

		cout<<"\n\nThat's not an integer -_-\n"<<"Try again\n\n";
		cin.clear();
		cin.ignore(99999, '\n' ); //numeric_limits<int>::max doesn't work

		//Reading input again
		cin>>in;
		}

	cout<<endl;

	return in;
}

float cushion::floatPut(){

	float in;

	cin>>in;


	while ( cin.fail() ){		//When the input is not an integer

		cout<<"\n\nThat's not a float -_-\n"<<"Try again\n\n";
		cin.clear();
		cin.ignore(99999, '\n' ); //numeric_limits<int>::max doesn't work

		//Reading input again
		cin>>in;
		}

	cout<<endl;

	return in;
}

