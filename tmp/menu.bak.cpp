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
#define mysize 10 
int p[mysize];
void swap(int &a, int&b) {
	int c;
	c = a;
	a = b;
	b = c;
}
void init() {
	int32_t i;
	for (i = 0; i < mysize; ++i) p[i] = i;
	for (i = mysize - 1; i > 0; --i) swap(p[i], p[rand() % i]);
}

int main() {
	//srand(time(0));
	init();
	int32_t i, j, k;
	const char a[] = "idxfile";
	const char b[] = "datafile";
	db mydb(a, b);
	map<int, long long> m;
	mydb.clear();
	//ofstream out("testfile");
	//out.close();
	//fstream file("testfile");
	iter tmp = mydb.begin();
	map<int, long long>::iterator it = m.begin();

	for (int32_t i = 0; i < mysize; ++i) {
		k = p[i];
		//k = 100 - i;
		mydb.insert(k, i);		
		m.insert(pair<int, long long>(k, i));

		tmp = mydb.find(k);
		it = m.find(k);
		//cout << *tmp << " and " << it->second << '\n';
		if (*tmp != it->second) {
			tmp = mydb.find(k);
			cout << i << " find  " << *tmp;
			cout << " map " << it->second << '\n';
		}
	}

	for (int32_t i = 0; i < mysize; ++i) {
		k = p[i];
		tmp = mydb.find(k);
		it = m.find(k);
		//cout << *tmp << " and " << it->second << '\n';
		if (*tmp != it->second) {
			tmp = mydb.find(k);
			cout << i << " find  " << *tmp;
			cout << " map " << it->second << '\n';
		}
	}


	//for (int32_t i = 0; i < 300; ++i) {
	//	k = p[i];
	//	mydb.modify(k, k);
	//	m[k] = k;
	//	tmp = mydb.find(k);
	//	it = m.find(k);
	//	//cout << *tmp << " and " << it->second << '\n';
	//	if (*tmp != it->second) {
	//		tmp = mydb.find(k);
	//		cout << i << " find  " << *tmp;
	//		cout << " map " << it->second << '\n';
	//	}
	//}cout << endl;
	//tmp = mydb.begin();
	//it = m.begin();
	//for (int32_t i = 0; i < mysize; ++i) {
	//	if (*tmp != it->second) {
	//		cout << i << " find  " << *tmp;
	//		cout << " map " << it->second << '\n';
	//	}
	//	++tmp;
	//	++it;
	//}cout << endl;

	int er = mysize - 3;
	for (int32_t i = 0; i < er; ++i) {
		printf("%d\n", i);
		k = p[i];
		tmp = mydb.find(k);
		it = m.find(k);
		//cout << *tmp << " and " << it->second << '\n';
		if (*tmp != it->second) {
			tmp = mydb.find(k);
			cout << i << " find  " << *tmp;
			cout << " map " << it->second << '\n';
		} 
		printf("%d\n", i);
		m.erase(k);
		mydb.erase(k);
	}cout << endl;
	if (mydb.empty()) cout << "empty\n";
	for (int32_t i = er; i < mysize; ++i) {
		k = p[i];
		tmp = mydb.find(k);
		it = m.find(k);
		//cout << *tmp << " and " << it->second << '\n';
		if (*tmp != it->second) {
			tmp = mydb.find(k);
			cout << i << " find  " << *tmp;
			cout << " map " << it->second << '\n';
		}
	}cout << endl;

	mydb.clear();
	return 0;
}

