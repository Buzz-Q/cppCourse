#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using namespace std;

class cushion
{
	public:
		int intPut(){
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
		float floatPut(){
	
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
};

class vending
{
	public:
		//product functions
		int purchase(int quantity, int required){
	if (quantity >= required && required > 0){
		quantity -= required;
		cout<<"\n\nENJOYY!!\n\n";
	}else{
		cout<<"\n\nrequested quantity is not available\n\n";
	}
	
	return quantity;
	}
	
	void refresh(int stock[]){
	
	int c;
	
	std::fstream f;
	
	f.open("vProducts.txt", ios::in | ios::out | ios::trunc);
	f.close();
	
	f.open("vProducts.txt", ios::in | ios::out);

		if(f.good()){
			
			f<<"1.Milka\t\t"<<stock[0]<<endl;
			f<<"2.Bounty\t"<<stock[1]<<endl;
			f<<"3.Sweetarts\t"<<stock[2]<<endl;
			f<<"4.Cookies\t"<<stock[3];
		
				for(c = 0; c<4; c++){
					if (stock[c] == 0){
						switch((c+1)){
							
							case 1:
							f<<"Notice: Please restock Milka\n";
							break;
							
							case 2:
							f<<"Notice: Please restock Bounty\n";
							break;
							
							case 3:
							f<<"Notice: Please restock sweetarts\n";
							break;
							
							case 4:
							f<<"Notice: Please restock the cookies\n";
							break;
							
							default:
							break;
						}
					}
				}

		}
		f.close();
	}
		//Money functions
		bool chaching(float price, int * pPool){
	
//paying process
	float paid = 0, change = -1, send;
	float pay;

	float money[]= {5, 2, 1, 0.5, 0.2, 0.1};	//money values
	int i = 0, j = 0, r = 0;	//counters

//in case of lack of coins to return	
	float *urMoney = new float(50);
	int * poolIndex= new int(50);	
	
	bool success = true;
//Ccustomer's change to be returned	
	float *urChange= new float(25);
	
	std::fstream m; //File object
	float val[6], q[6];	//for pool's values and quantities
	cushion cu; //input object
	
	m.open("pool.txt", ios::in | ios::out);

if (m.good()){	
	for (i=0; i<=5; i++){
		m << money[i] << "\t" << *(pPool + i) << endl;
	}

	i = 0;
	
	cout<<"enter only the value of each coin\n";
	cout<<"5PLN\t"<<"2PLN\t"<<"1PLN\t"<<"0.2PLN\t"<<"0.1PLN\n";
	
	pay = price*10;
	
	while(change < 0){
		
		cout<<"Pay: "<<pay/10<<" PLN"<<endl;
		paid = cu.floatPut();
		
		paid *= 10;
		pay -= paid;
		
	
		
		switch (int(paid)){
			case 50:
				*pPool += 1;
				
				urMoney[i] = paid/10;
				poolIndex[i]= 0;
				i++;
				break;
				
			case 20:
				*(pPool + 1) += 1;
				
				urMoney[i] = paid/10;
				poolIndex[i]= 1;
				i++;
				break;
			
			case 10:
				*(pPool + 2) += 1;
				
				urMoney[i] = paid/10;
				poolIndex[i]= 2;
				i++;
				break;
			
			case 5:
				*(pPool + 3) += 1;
				
				urMoney[i] = paid/10;
				poolIndex[i]= 3;
				i++;
				break;
				
			case 2:
				*(pPool + 4) += 1;
				cout<<*(pPool+4)<<endl;
				
				urMoney[i] = paid/10;
				poolIndex[i]= 4;
				i++;
				break;
				
			case 1:
				*(pPool + 5) += 1;
				
				urMoney[i] = paid/10;
				poolIndex[i]= 5;
				i++;
				break;
			
			default:
				cout<<"Invalid value, try again\n";
				pay += paid;
					
		}
		
		change = -pay;		
	}
		
	while(change > 0){
		
		if((change>=20) && (*(pPool + 1) > 0)){
			if(*(pPool+2) - *(pPool+1) >= 5){
				send = 1;
				*(pPool + 2) -= 2;
				*(urChange + j) = send;
				*(urChange + j + 1) = send;
				j += 2;
			}
			else{
				send = 2;
				*(pPool + 1) -= 1;
				*(urChange + j) = send;
				j++;
			}
			
			change -= 20;
			cout<<"Change: "<<change/10<<endl;
			continue;
			
		}else if ((change>=10) && (*(pPool + 2) > 0)){
			if(*(pPool+3) - *(pPool+2) >= 5){
				send = 0.5;
				*(pPool + 3) -= 2;
				*(urChange + j) = send;
				*(urChange + j + 1) = send;
				j += 2;
			}
			else{
				send = 1;
				*(pPool + 2) -= 1;
				*(urChange + j) = send;
				j++;
			}		
			change -= 10;			
			cout<<"Change: "<<change/10<<endl;

			continue;
			
		}else if ((change>=5) && (*(pPool + 3) > 0)){
			send = 0.5;
			*(pPool + 3) -= 1;
			*(urChange + j) = send;
			j++;
			change -= 5;		
			cout<<"Change: "<<change/10<<endl;

			continue;
				
		}else if ((change>=2) && (*(pPool + 4) > 0)){
			if(*(pPool+5) - *(pPool+4) >= 5){
				send = 0.1;
				*(pPool + 5) -= 2;
				*(urChange + j) = send;
				*(urChange + j + 1) = send;
				j += 2;
			}
			else{
				send = 0.2;
				*(pPool + 4) -= 1;
				*(urChange + j) = send;	
				j++;
				}
				change -= 2;		
				cout<<"Change: "<<change/10<<endl;

			continue;
		}else if ((change >= 1) && (*(pPool + 5) > 0)){
			
				send = 0.1;
				*(pPool + 5) -= 1;
				*(urChange + j) = send;
				j++;
				
				change -= 1;			
				cout<<"Change: "<<change/10<<endl;

				continue;
			}else if((change >= 1) && (*(pPool + 5) == 0)){
				cout<<"No sufficient amount of coins to return\n";
				cout<<"Please pay a smaller Value\n";
				cout<<"Returning your paid money..\n";
				
				for(r = 0; r < i; r++){
					cout<<urMoney[r]<<endl;
					*(pPool + poolIndex[r]) -= 1;
				}
				success = false;
				break;
				
			}
		}
	
		if(success){
			cout<<"Here's your change:\n";
			for(i = 0; i < j; i++){
				
				cout<<urChange[i]<<endl;
				
			}
		}

		m.seekg(0, std::ios_base::beg);
		
		i = 0;
		for (i=0; i<=5; i++){
			m << money[i] << "\t" << *(pPool + i) << endl;
		}
		cout<<endl<<endl;
		delete urMoney, poolIndex, urChange;
		m.close();}
			return success;
		}

		void poolEdit(int *pPool){
	
		std::fstream e; //File object
		float val[6]= { 5, 2, 1, 0.5, 0.2, 0.1}, q[6];	//for pool's values and quantities
		int i = 0;
		
		e.open("pool.txt", ios::in | ios::out);
		
		if(e.good()){
			cout<<"Change values of\n 5, 2, 1, 0.5, 0.2, 0.1 to: \n";
			for (i=0; i<6; i++){
				cin>>q[i];
				*(pPool + i) = q[i];
			}
			
			for (i=0; i<=5; i++){
				e << val[i] << "\t" << *(pPool + i) << endl;
			}
		} e.close();
		
		}

};


int main(){
	
//Data for the files
	std::fstream f; //File object
	
	string data;	//to sweep the file word by word
	string content; //to show the content of the file on the screen
	int k;			//to check numerical values within the file;
	
//Data for purchase
	int stock[4];	//Available stock
	int i=0, j=0, c=0;	//Counters
	bool startup = true, restocked = false; //For restocking 
	
	int picked, number; //User's desired inputs.
	
//pool concerns	
	int pool[] = {0, 14, 16, 9, 10, 15}; //default //10 w 15
	int * pPool = &pool[0];

	float price[4] = {3.90, 2.80, 5.0, 4.30};
	bool transaction;
	
//Class objects
	cushion cu;
	vending v;	

	while(1){
		f.open("vProducts.txt", ios::in | ios::out);		
			if(f.good()){					
					if(startup && !restocked){
						while(!f.eof()){
							f>>data;
							istringstream(data)>>k;
							if((k != 0) || data == "0"){
								i++;
								if(i % 2 == 0){
									stock[j] = k;
									if(stock[j] == 0){
										stock[j] +=10;
										restocked = true;
									}
									j++;
								}
							}
						}
						startup = false;
						f.close();
						v.refresh(stock);
						continue;
					}
					
					cout<<"Vending Maching\n"<<"*\n*\n";
					
					c=0;
					while(!f.eof()){
						getline(f, content);
						cout<<content<<"\t"<<price[c]<<endl;
						c++;
					}
					
					cout<<"*\n*\n";
					cout<<"Pick the number corresponding to your desired treat: ";
					picked = cu.intPut();
					
					if (picked == 38894020){
						cout<<"\nShutting down\n";
						break;
					}
					if (picked == 24173246){
						v.poolEdit(pool);
						continue;
					}
					if ((picked < 1) || (picked > 4)){
						cout<<"\n\nInvalid input\nPlease,try again\n";
						continue;
					}
					
					
					cout<<"\n"<<"How many?\n";
					number = cu.intPut();
					cout<<endl;
					
					if (number == 38894020){
						cout<<"\nShutting down\n";
						break;
					}
					if (number == 24173246){
						v.poolEdit(pool);
					}
					
					transaction = v.chaching((number*price[picked-1]), pool);
					
					if(transaction){
						stock[picked-1] = v.purchase(stock[picked-1], number);
						cout<<"New stock value is "<<stock[picked-1]<<endl;
						v.refresh(stock);
					}		
					
				
					
			}
		f.close();
	}
	return 0;
}
