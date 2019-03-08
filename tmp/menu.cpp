#include "database.hpp"
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
using db = database<int, long long>;
using iter = database<int, long long>::iterator;

struct cmp {
	template<class Key>
	bool operator ()(const Key &a, const Key &b)const { return a.x > b.x; }
};
#define mysize 10000
int p[mysize];
void swap(int &a, int&b) {
	int c;
	c = a;
	a = b;
	b = c;
}

int32_t i, j, k;
	const char a[] = "idxfile";
	const char b[] = "datafile";
	db mydb(a, b);
	map<int, long long> m;
	//ofstream out("testfile");
	//out.close();
	//fstream file("testfile");
	iter tmp = mydb.begin();
	map<int, long long>::iterator it = m.begin();
void init() {
	int32_t i;
	for (i = 0; i < mysize; ++i) p[i] = rand();
	for (i = mysize - 1; i > 0; --i) swap(p[i], p[rand() % i]);
	mydb.clear();
}
void f(){
	for (int32_t i = 0; i < mysize; ++i) {
		k = p[i];
		//k = 100 - i;
		// printf("insert:%d %d\n", k, i);
		if(m.find(k) != m.end()) continue;
		mydb.insert(k, i);		
		m.insert(pair<int, long long>(k, i));
	}
	// cout<<"::"<<mydb.size()<<endl;
	int k = 0;
	// for(tmp = mydb.find(424238335); tmp != mydb.end(); tmp++){
	// 	cout<<tmp.findkey()<<" "<<*tmp<<endl;
	// }
	// cout<<"==============="<<endl;
	// for(it = m.begin(); it != m.end();it++){
	// 	cout<<it->first<<" "<<it->second<<endl;
	// }
	// cout<<"==============="<<endl;
	for(int32_t i = 0; i< mysize;i++){
		int k = (rand()%mysize);
		// cout<<p[k]<<endl;
		it = m.find(p[k]);
		 tmp = mydb.find(p[k]);
		 if((it->second!=(*tmp)))
		 {cout<<k<<" "<<"!!!"<<endl;}
		// cout<<endl;
	}
	for (int32_t i = 0; i < mysize; ++i){
		int t = rand();
		it = m.lower_bound(t);
		tmp = mydb.find(t);
		// cout<<"find:"<<t<<" "<<(it == m.end())<<" "<<(tmp == mydb.end())<<" "<<endl;
		if(it == m.end()){
			if(tmp != mydb.end()){
				cout<<"1"<<endl;
				continue;
			}
		}
		else {
			if(tmp == mydb.end()){
				cout<<"2"<<endl;
				continue;
			
			}
			// cout<<(it!=m.end()) <<" "<<(tmp!=mydb.end())<<" "<<(it->second)<<" "<<(*tmp)<<endl;
			else {
				if(*tmp != it->second)
					cout<<*tmp<<" "<<it->second<<endl;
			}
		}
		// if(it == m.end() && tmp == mydb.end()){
		// 	continue;
		// }
		// else if(it->second == *tmp){
		// 	continue;
		// }
		// else {
		// 	cout<<"!!!"<<t<<" "<<it->second<<" "<<*tmp<<" "<<(it == m.end())<<" "<<(tmp == mydb.end())<<endl;
		// }

	}
}
int main() {
	//srand(time(0));
	init();
	f();
	

	mydb.clear();
	return 0;
}

