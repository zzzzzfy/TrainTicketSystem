#define _CRT_SECURE_NO_WARNINGS
#include "database.hpp"
#include <cstring>
#include <cstdio>
#include <iomanip>
//just like the clothes
#define xlsize 63
#define lsize 43//large
#define msize 23//middle
#define ssize 13//small
#define xssize 8

#define xxxsize 600
//id(2018) = administrator
//last ok id == innerid, next new id = ++innerid
int inner_id = 2017;

//useful functions
int to_int(char *s) {
	return atoi(s);
}
double to_double(char *s) {
	return atof(s);
}
void itoa(int n, char *str){
	char buff[10] = "\0";
	int i = 0;
	int len = 0;
	int tmp = n < 0 ? -n : n ;
	if(str == NULL) return;
	while(tmp){
		buff[i++] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	len = n < 0 ? ++i : i;
	str[i] = 0;

	while(1){
		--i;
		if(buff[len - i - 1] == 0) break;
		str[i] = buff[len - i - 1];
		if(i == 0) str[i] = '-';
	}
}
void ftoa(double x, char *str){

}

void check_date(char *da, char *t1, char *t2) {
	if (strcmp(t1, t2) > 0) {
		if (*(da + 9) == '9') {
			*(da + 9) = '0';
			++*(da + 8);
		}
		else ++*(da + 9);
	}
}
bool cmp(const char a[], const char b[]) {
	// if(strncmp(a, b, strlen(a)) == 0 && 0 == strncmp(a, b, strlen(b))) 
	//     return 1;
	if (strcoll(a, b) == 0) return 1;
	return 0;
}



//simple string
class mstring {
public:
	char a[msize] = "\0";
	mstring() {}
	mstring(const char *p) {
		strcpy(a, p);
	}
	mstring(const mstring &o) {
		strcpy(a, o.a);
	}
	mstring &operator=(const mstring &o) {
		strcpy(a, o.a);
		return *this;
	}
	~mstring() {}
	friend istream &operator>>(istream &o, mstring& x);
};
istream &operator>>(istream &o, mstring& x) {
	o >> x.a;
	return o;
}
class cmp1 {
public:
	bool operator()(const mstring &a, const mstring &b) {
		if ((strcmp(a.a, b.a)) < 0) return 1;
		return 0;
	}
};

//xxxx-xx-xx
//xx:xx --- dont care
class Date {
public:
	char d[ssize];
	Date(const char *p) {
		strcpy(d, p);
	}
	Date &operator++() {
		if (d[9] == '9') {
			d[9] = '0';
			++d[8];
		}
		else ++d[9];
		return *this;
	}
};


class user {
public:
	//int id;
	char name[lsize];// 1 chinese word with 2 char
	char password[83];
	char email[31];//255+64+1
	char phone[msize];
	int privilege = 0;// 0--no, 1--re, 2--man

	user() {};
	user(const char *_name, const char *_password, const char *_email, const char *_phone, const int p = 0) : privilege(p) {
		//id = id;
		strcpy(name, _name);
		strcpy(password, _password);
		strcpy(email, _email);
		strcpy(phone, _phone);
	}
	void read(const char *_name, const char *_password, const char *_email, const char *_phone, const int p = 0) {
		//id = id;
		privilege = p;
		strcpy(name, _name);
		strcpy(password, _password);
		strcpy(email, _email);
		strcpy(phone, _phone);
	}
};

class train_order {
public:
	char catalog;
	mstring train_id;
	char station_name[msize];

	train_order() {}
	train_order(const char &c, const mstring &t, const char *p) :catalog(c), train_id(t) {
		strcpy(station_name, p);
	}
	void read(const char &c, const mstring &t = mstring(), const char *p = "\0") {
		catalog = c;
		train_id = t;
		strcpy(station_name, p);
	}
};
class cmp2 {//less: user--->date--->catalog
public:
	bool operator()(const train_order &a, const train_order &b) {
		int tmp(strcmp(a.station_name, b.station_name));
		if (tmp < 0) return 1;
		else if(tmp > 0) return 0;
		else if (a.catalog < b.catalog) return 1;
		else if (a.catalog > b.catalog) return 0;
		else if (strcmp(a.train_id.a, b.train_id.a) < 0) return 1;
		return 0;
	}
};
class train {
public:
	int sale = -1;//if -1, sale but not buyticket, 0 notsale, >0 sale dates
	mstring train_id;
	char name[lsize];
	char catalog;//?
				 //char train_kind[msize];
	int num_station;
	int num_price;//$...

	char ticket_name[xlsize][msize];
	char station_name[xlsize][msize];
	char arriv_time[xlsize][xssize];
	char start_time[xlsize][xssize];
	char stopover_time[xlsize][xssize];
	double price[xlsize][xssize];
	//int ticket[xlsize][xssize];

	train() { }
	void read() {
		//train
		cin >> train_id >> name >> catalog >> num_station >> num_price;
		for (int i = 0; i < num_price; i++)
			cin >> ticket_name[i];

		for (int i = 0; i < num_station; i++) {
			cin >> station_name[i];
			cin >> arriv_time[i] >> start_time[i] >> stopover_time[i];
			for (int j = 0; j < num_price; j++) {
				char pri[10];
				char tmp_s[14];
				cin>>tmp_s;
				int t_len(strlen(tmp_s));
				for(int t_k = 3; t_k <= t_len; ++t_k)
					pri[t_k - 3] = tmp_s[t_k];
				// scanf("%c%c%c", &_tmpch, &_tmpch, &_tmpch);
				// scanf("%s", pri);
				//char pri[10]
				//cin >> pri;     
				//strcpy(pri, pri+2, sizeof(pri) - 3);
				price[i][j] = to_double(pri);
			}
		}
	}
	void print() {
		// cout << fixed<< setprecision(6) <<train_id.a<<" "<<name<<" "<<catalog<<" "<<num_station<<" "<<num_price<<endl;
		// printf("%s %s %c %d %d\n", train_id.a, name, catalog, num_station, num_price);
		cout << fixed<< setprecision(6) <<train_id.a<<" "<<name<<" "<<catalog<<" "<<num_station<<" "<<num_price<<" ";
		for (int i = 0; i < num_price; ++i)
			cout << fixed<< setprecision(6)  << ' ' << ticket_name[i];
		cout << fixed<< setprecision(6)  << '\n';
		for (int i = 0; i < num_station; ++i) {
			// printf("%s %s %s %s ", station_name[i], arriv_time[i], start_time[i], stopover_time[i]);
			cout << fixed<< setprecision(6) <<station_name[i]<<" "<<arriv_time[i]<<" "<<start_time[i]<<" "<<stopover_time[i]<<" ";
			for (int j = 0; j < num_price; ++j)
				cout << fixed<< setprecision(6)  << "￥" << price[i][j] << ' ';
			cout << fixed<< setprecision(6)  << '\n';
		}
	}
};





class left_ticket {
public:
	int ticket[xlsize][xssize];
	left_ticket() {
		for (int i = 0; i < xlsize; ++i)
			for (int j = 0; j < xssize; ++j)
				ticket[i][j] = 2000;
	}

	void buy(int l, int r, int price, int num = 1) {//the level of seats
		for (int i = l; i < r; ++i)
			ticket[i][price] -= num;
	}
	void refund(int l, int r, int price, int num = 1) {
		for (int i = l; i < r; ++i)
			ticket[i][price] += num;
	}
	int check(int l, int r, int price) {
		int min = 2000;
		for (int i = l; i < r; ++i) {
			if (min > ticket[i][price]) min = ticket[i][price];
		}

		return min;
	}
};
class date_train {
public:
	char date[ssize] = "\0";
	mstring train_id;

	date_train() : train_id(mstring()) {}
	void read(const char *dat, mstring &tr_id) {
		strcpy(date, dat);
		train_id = tr_id;
	}
	bool operator==(const date_train &x) {
		if (strcmp(date, x.date) == 0 && strcmp(train_id.a, x.train_id.a) == 0) return 1;
		return 0;
	}
};
class cmp3 {
public:
	bool operator()(const date_train &x, const date_train &y) {
		int tmp(strcmp(x.date, y.date));
		if (tmp < 0) return 1;
		else if(tmp > 0) return 0;
		else if (strcmp(x.train_id.a, y.train_id.a) < 0) return 1;
		return 0;
	}
};


class ticket {
public:
	mstring train_id;
	char catalog;
	char loc1[msize], loc2[msize];
	char date[ssize];
	char time[xssize];
	char time1[xssize];
	char time2[xssize];

	int num_price;
	char ticket_name[xssize][msize];
	double price_ticket[xssize] = { 0 };
	int num_ticket[xssize];

	ticket() {}
	void read(ticket &x) {
		train_id = x.train_id;
		catalog = x.catalog;
		strcpy(loc1, x.loc1);
		strcpy(loc2, x.loc2);
		strcpy(date, x.date);
		strcpy(time, x.time);
		strcpy(time1, x.time1);
		strcpy(time2, x.time2);

		num_price = x.num_price;
		for (int i = 0; i < num_price; ++i) {
			strcpy(ticket_name[i], x.ticket_name[i]);
			price_ticket[i] = x.price_ticket[i];
			num_ticket[i] = x.num_ticket[i];
		}
	}
	void read(mstring &trid, char &c, char *l1, char *l2,
		char *dat, char *t, char *t1, char *t2,
		int num, char tic_kind[63][msize], double *pri, int *num_tic) {
		train_id = trid;
		catalog = c;
		strcpy(loc1, l1);
		strcpy(loc2, l2);
		strcpy(date, dat);
		strcpy(time, t);
		strcpy(time1, t1);
		strcpy(time2, t2);

		num_price = num;
		for (int i = 0; i < num; ++i) {
			strcpy(ticket_name[i], tic_kind[i]);
			price_ticket[i] = pri[i];
			num_ticket[i] = num_tic[i];
		}
	}
	void print() {
		char tmp[ssize], tmp2[ssize];
		strcpy(tmp, date);
		strcpy(tmp2, date);
		check_date(tmp, time, time1);
		check_date(tmp2, time, time2);
		// printf("%s %s %s %s %s %s %s\n", train_id.a, loc1, tmp, time1, loc2, tmp2, time2);
		cout << fixed<< setprecision(6) <<train_id.a<<" "<<loc1<<" "<<tmp<<" "<<time1<<" "<<loc2<<" "<<tmp2<<" "<<time2;
		for (int i = 0; i < num_price; ++i) 
		// printf("%s %d %.6f\n", ticket_name[i], num_ticket[i], price_ticket[i]);
			cout << fixed<< setprecision(6) <<" "<<ticket_name[i]<<" "<<num_ticket[i]<<" "<<price_ticket[i];
		cout << fixed<< setprecision(6) <<"\n";
		return;
	}
};
class user_ticket {
public:
	char catalog;
	int userid;
	char date[msize];
	mstring train_id;
	char loc1[msize], loc2[msize];
	void read(const char &c, const int &u, const char *p, mstring &x, const char *l1, const char *l2) {
		train_id = x;
		catalog = c;
		userid = u;
		strcpy(date, p);
		strcpy(loc1, l1);
		strcpy(loc2, l2);
	}
};
class cmp4 {//less: user--->date--->catalog
public:
	bool operator()(const user_ticket &a, const user_ticket &b) {
		int tmp1(strcmp(a.date, b.date));
		int tmp2(strcmp(a.loc1, b.loc1));
		if (a.userid < b.userid) return 1;
		else if(a.userid > b.userid) return 0;
		else if (a.catalog < b.catalog) return 1;
		else if (a.catalog > b.catalog) return 0;
		else if (tmp1 < 0) return 1;
		else if (tmp1 > 0) return 0;
		else if (tmp2 < 0) return 1;
		else if (tmp2 > 0) return 0;
		else if (strcmp(a.loc2, b.loc2) < 0) return 1;
		return 0;
	}
};



// class user_id{};-----> int
database<int, user> user_db("db//_user1", "db//_user2");
using iter_user = database<int, user>::iterator;

database<mstring, train, cmp1, 4> train_db("db//_train1", "db//_train2");
using iter_train = database<mstring, train, cmp1, 4>::iterator;

database<train_order, char, cmp2> train_order_db("db//_order1", "db//_order2");
using iter_train_order = database<train_order, char, cmp2>::iterator;

database<date_train, left_ticket, cmp3> left_ticket_db("db//_left1", "db//_left2");
using iter_left_ticket = database<date_train, left_ticket, cmp3>::iterator;

database<user_ticket, ticket, cmp4> ticket_db("db//_ticket1", "db//_ticket2");
using iter_ticket = database<user_ticket, ticket, cmp4>::iterator;

database<mstring, int, cmp1> email_db("db//_email1", "db//_email2");
using iter_email = database<mstring, int, cmp1> ::iterator;

/*
void update()
{
	user_db.update();
	train_db.update();
	train_order_db.update();
	left_ticket_db.update();
	ticket_db.update();
	email_db.update();
}
*/
























//temporary variables
char tmp_string[lsize + msize + msize + msize + 4];
int _privilege;// 0--no, 1--re, 2--admin
int _id1, _id2;
char _name[lsize];// 1 chinese word with 2 char
char _password[msize];
char _email[msize];//255+64+1
char _phone[msize];

mstring _train_id;
char _loc1[msize], _loc2[msize];
char _date[ssize];
char _ticket_name[msize];
int _num1, _num2;
char _catalog;
char _tmpcatalog[msize];

user _user;
train _train;
cmp1 _c1;

train_order _train_order;
cmp2 _c2;

left_ticket _left_ticket;
date_train _date_train;
cmp3 _c3;

user_ticket _user_ticket;//user, date, catalog
ticket _ticket;
cmp4 _c4;

