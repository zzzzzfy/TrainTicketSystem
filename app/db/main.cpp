#include "main.hpp"
#include <string>
#include<boost/python.hpp>
#include<boost/python/list.hpp>
#include<boost/python/dict.hpp>

using namespace boost::python;

struct user_get
{
	user_get() {};
	int uid, privilege, valid;
	string name, phone, email, password;
	bool confirm;
	bool find(int U)
	{
		iter_user it = user_db.find(U);
		if (it.getkey() != U)
		{
			valid = 0;
			return 0;
		}
		valid = 1;
		uid = U;
		privilege = it->privilege;
		name = it->name;
		phone = it->phone;
		email = it->email;
		password = it->password;
		if(!privilege)
			confirm = 0;
		else
			confirm = 1;
		return 1;
	}
	bool find_by_email(string em)
	{
		iter_email it = email_db.find(mstring(em.c_str()));
		if(cmp(it.getkey().a, em.c_str()))
			return find(*it);
		else
		{
			valid = 0;
			return 0;
		}
	}
	void modify()
	{
		iter_user it = user_db.find(uid);
		user tmp(name.c_str(), password.c_str(), email.c_str(), phone.c_str(), privilege); //id bucun
		user_db.modify(it, tmp);
	}
	void add_user()
	{
		if (inner_id == 2017)
			_privilege = 2;
		else
			_privilege = 0;
		++inner_id;
		ofstream ou("user");
		ou << inner_id;
		ou.close();
		user tmp(name.c_str(), password.c_str(), email.c_str(), phone.c_str(), _privilege); //id bucun
		email_db.insert(mstring(email.c_str()), inner_id);
		user_db.insert(inner_id, tmp);
	}
};

void empty_list(boost::python::list &a)
{
	for (int i = boost::python::len(a); i > 0; --i)
		a.pop();
}

struct train_get
{
	train_get(){};
	int sale, valid, num_station, num_price;
	string name, catalog, train_id;
	boost::python::list ticket_name, station_name, arriv_time, start_time,
		stopover_time, price;
	void empty_list_members()
	{
		empty_list(ticket_name);
		empty_list(station_name);
		empty_list(arriv_time);
		empty_list(start_time);
		empty_list(stopover_time);
		empty_list(price);
	}
	bool find(string tid)
	{
		iter_train it = train_db.find(tid.c_str());
		if (!cmp(tid.c_str(), it.getkey().a))
		{
			valid = 0;
			return 0;
		}
		valid = 1;
		sale = it->sale;
		num_station = it->num_station;
		num_price = it->num_price;
		name = it->name;
		catalog = it->catalog;
		train_id = it->train_id.a;
		empty_list_members();
		for (int i = 0; i < num_price; ++i)
			ticket_name.append(it->ticket_name[i]);
		for (int i = 0; i < num_station; ++i)
		{
			station_name.append(it->station_name[i]);
			arriv_time.append(it->arriv_time[i]);
			start_time.append(it->start_time[i]);
			stopover_time.append(it->stopover_time[i]);
			boost::python::list tmp;
			for (int j = 0; j < num_price; ++j)
				tmp.append(it->price[i][j]);
			price.append(tmp);
		}
		return 1;
	}
	void generage_list(int ns, int np)
	{
		sale = -1;
		num_station = ns;
		num_price = np;
		empty_list_members();
		for (int i = 0; i < num_price; ++i)
			ticket_name.append("--");
		for (int i = 0; i < num_station; ++i)
		{
			station_name.append("--");
			arriv_time.append("--");
			start_time.append("--");
			stopover_time.append("--");
			boost::python::list tmp;
			for (int j = 0; j < num_price; ++j)
				tmp.append(0);
			price.append(tmp);
		}
	}
	void generate_train(train &a)
	{
		a.sale = sale;
		a.num_station = num_station;
		a.num_price = num_price;
		a.train_id = train_id.c_str();
		strcpy(a.name, name.c_str());
		a.catalog = catalog[0];
		string tmps;
		for (int i = 0; i < num_price; ++i)
		{
			tmps = boost::python::extract<string>(ticket_name[i]);
			strcpy(a.ticket_name[i], tmps.c_str());
		}
		for (int i = 0; i < num_station; ++i)
		{
			tmps = boost::python::extract<string>(station_name[i]);
			strcpy(a.station_name[i], tmps.c_str());
			tmps = boost::python::extract<string>(arriv_time[i]);
			strcpy(a.arriv_time[i], tmps.c_str());
			tmps = boost::python::extract<string>(start_time[i]);
			strcpy(a.start_time[i], tmps.c_str());
			tmps = boost::python::extract<string>(stopover_time[i]);
			strcpy(a.stopover_time[i], tmps.c_str());
			for (int j = 0; j < num_price; ++j){
				tmps = boost::python::extract<string>(price[i][j]);
				a.price[i][j] = atof((tmps).c_str());
			}
		}
	}
	void add_train()
	{
		train tmp;
		generate_train(tmp);
		train_db.insert(train_id.c_str(), tmp);
	}
	bool sale_train()
	{
		iter_train it = train_db.find(train_id.c_str());
		if (it->sale != -1)
			return 0;
		for (int i = 0; i < it->num_station; ++i)
		{
			_train_order.read(it->catalog, it->train_id, it->station_name[i]);
			train_order_db.insert(_train_order, _catalog);
		}
		it->sale = 0;
		it.write();
		find(train_id);
		return 1;
	}
	bool delete_train()
	{
		iter_train it3 = train_db.find(train_id.c_str());
		if (it3->sale >= 0)
			return 0;
		train_db.erase(train_id.c_str());
		return 1;
	}
	bool modify_train()
	{
		generate_train(_train);
		_train_id = _train.train_id;
		iter_train it3 = train_db.find(_train_id);
		if (it3->sale >= 0)
			return 0;
		if (!cmp(it3.getkey().a, _train_id.a))
			return 0;
		train_db.modify(_train_id, _train);
		return 1;
	}
};
struct ticket_operate
{
	int uid, num;
	string train_id, loc1, loc2, date, ticket_name;
	ticket_operate(){};
	bool buy_ticket() //required uid, train_id, loc1, loc2, date, ticket_name, num
	{
		_id1 = uid;
		strcpy(_train_id.a, train_id.c_str());
		_num1 = num;
		strcpy(_loc1, loc1.c_str());
		strcpy(_loc2, loc2.c_str());
		strcpy(_date, date.c_str());
		strcpy(_ticket_name, ticket_name.c_str());
		iter_train it = train_db.find(_train_id);
		if (!cmp(it.getkey().a, _train_id.a))
			return 0;
		if (it->sale == -1)
			return 0;
		int i, j, p;
		for (i = 0; i < it->num_station; ++i)
		{
			if (strcmp(_loc1, it->station_name[i]) == 0)
				break;
		}
		for (j = 0; j < it->num_station; ++j)
		{
			if (strcmp(_loc2, it->station_name[j]) == 0)
				break;
		}
		for (p = 0; p < it->num_price; ++p)
		{
			if (strcmp(_ticket_name, it->ticket_name[p]) == 0)
				break;
		}
		if (i == it->num_station || j == it->num_station || p == it->num_price)
			return 0;
		if (i >= j)
			return 0;
		_date_train.read(_date, _train_id);
		iter_left_ticket it2 = left_ticket_db.find(_date_train);
		// cout<<":"<<_date<<" "<<_date_train.train_id.a<<" "<<_date_train.date<<endl;
		if (_date_train == it2.getkey())
		{
			if (it2->check(i, j, p) < _num1)
				return 0;
			it2->buy(i, j, p, _num1);
			it2.write();
		}
		else
		{
			// if (it2->check(i, j, p) < _num1) return 0;
			it2 = left_ticket_db.insert(_date_train, left_ticket());
			it2 = left_ticket_db.find(_date_train);
			// cout<<":"<<_date<<endl;
			it2->buy(i, j, p, _num1);
			// cout<<(*it2)
			it2.write();
			//it->sale++;
			it.write();
		}

		// cout << fixed<< setprecision(6) <<"!!"<<endl;
		_user_ticket.read(it->catalog, _id1, _date, _train_id, _loc1, _loc2);
		iter_ticket it3 = ticket_db.find(_user_ticket);
		if (!_c4(_user_ticket, it3.getkey()) && !_c4(it3.getkey(), _user_ticket))
		{
			it3->num_ticket[p] += _num1;
			it3.write();
		}
		else
		{
			int tmp[ssize] = {0};
			tmp[p] = _num1;
			double allprice[xssize] = {0};
			for (int m = 0; m < it->num_price; ++m)
			{
				for (int n = i + 1; n <= j; ++n)
					allprice[m] += it->price[n][m];
			}

			_ticket.read(_train_id, it->catalog, _loc1, _loc2, _date, it->start_time[0],
						 it->start_time[i], it->arriv_time[j],
						 it->num_price, it->ticket_name, allprice, tmp);
			ticket_db.insert(_user_ticket, _ticket);
		}
		return 1;
	}
	bool refund_ticket()
	{
		_id1 = uid;
		strcpy(_train_id.a, train_id.c_str());
		_num1 = num;
		strcpy(_loc1, loc1.c_str());
		strcpy(_loc2, loc2.c_str());
		strcpy(_date, date.c_str());
		strcpy(_ticket_name, ticket_name.c_str());
		// cout << fixed<< setprecision(6) <<":"<<endl;
		iter_train it = train_db.find(_train_id);
		// cout << fixed<< setprecision(6) <<it.getkey().a<<" "<<_train_id.a<<endl;
		if (!cmp(it.getkey().a, _train_id.a))
			return 0;
		if (it->sale == -1)
			return 0;

		int i, j, p;
		for (i = 0; i < it->num_station; ++i)
		{
			if (strcmp(_loc1, it->station_name[i]) == 0)
				break;
		}
		for (j = 0; j < it->num_station; ++j)
		{
			if (strcmp(_loc2, it->station_name[j]) == 0)
				break;
		}
		for (p = 0; p < it->num_price; ++p)
		{
			if (strcmp(_ticket_name, it->ticket_name[p]) == 0)
				break;
		}

		_date_train.read(_date, _train_id);
		iter_left_ticket it2 = left_ticket_db.find(_date_train);
		// cout << fixed<< setprecision(6) <<"````"<<endl;
		if (!_c3(it2.getkey(), _date_train) && !_c3(_date_train, it2.getkey()))
			;
		else
			return 0;
		it2->refund(i, j, p, _num1);
		// it2.write();
		// cout << fixed<< setprecision(6) <<"````"<<endl;
		// cout << fixed<< setprecision(6) <<_id1<<endl;
		_user_ticket.read(it->catalog, _id1, _date, _train_id, _loc1, _loc2);
		iter_ticket it3 = ticket_db.find(_user_ticket);
		// (*it3).print();
		if (!_c4(_user_ticket, it3.getkey()) && !_c4(it3.getkey(), _user_ticket))
			;
		else
			return 0;
		if (it3->num_ticket[p] < _num1)
			return 0;
		it3->num_ticket[p] -= _num1;
		// if(it3->num_ticket[p] == 0){
		//     for(int i = 0; i < it3->num_price; ++i)
		//         if(it3->num_ticket[p] > 0) break;

		//     // if(it3->num_price == i) ticket_db.erase();
		// }
		it3.write();
		return 1;
	}
};
int minutes(char *t0, char *t1)
{
	int min = 0;
	int hour = 0;
	if (strcmp(t0, t1) >= 0)
	{
		hour += 24;
	}
	hour += (t0[0] - t1[0]) * 10 + (t0[1] - t1[1]);
	min += (t0[3] - t1[3]) * 10 + (t0[3] - t1[3]);
	min += hour * 60;
	return min;
}
struct prin
{
	char train_id[msize];
	char loc1[msize];
	char loc2[msize];
	char time1[xssize], time2[xssize];
	char date1[msize];
	char date2[msize];
	char ticket_name[xlsize][msize];
	int left[xssize];
	double pri[xssize];
	int l, r, num_price;

	void print()
	{
		cout << fixed << setprecision(6) << train_id << " " << loc1 << " " << date1 << " " << time1 << " " << loc2 << " " << date2 << " " << time2;
		for (int p = 0; p < num_price; ++p)
		{
			cout << fixed << setprecision(6) << " " << ticket_name[p] << " " << left[p] << " " << pri[p];
		}
		cout << fixed << setprecision(6) << '\n';
	}
};
struct ticket_info
{
	string train_id, loc1, loc2, time1, time2, date1, date2;
	boost::python::list ticket_name, left, pri;
	void empty_list_members()
	{
		empty_list(ticket_name);
		empty_list(left);
		empty_list(pri);
	}
	void get_info(const prin &ob)
	{
		train_id = ob.train_id;
		loc1 = ob.loc1;
		loc2 = ob.loc2;
		time1 = ob.time1;
		time2 = ob.time2;
		date1 = ob.date1;
		date2 = ob.date2;
		empty_list_members();
		for (int p = 0; p < ob.num_price; ++p)
		{
			ticket_name.append(ob.ticket_name[p]);
			left.append(ob.left[p]);
			pri.append(ob.pri[p]);
		}
	}
	void get_info(const ticket &ob)
	{
		train_id = ob.train_id.a;
		loc1 = ob.loc1;
		loc2 = ob.loc2;
		time1 = ob.time1;
		time2 = ob.time2;
		date1 = ob.date;
		empty_list_members();
		for (int p = 0; p < ob.num_price; ++p)
		{
			ticket_name.append(ob.ticket_name[p]);
			left.append(ob.num_ticket[p]);
			pri.append(ob.price_ticket[p]);
		}
	}
};
struct ticket_get
{
	string loc1, loc2, date, catalog;
	int uid;
	boost::python::list result;
	void query_ticket()
	{
		empty_list(result);
		mstring x = mstring();
		strcpy(_loc1, loc1.c_str());
		strcpy(_loc2, loc2.c_str());
		strcpy(_date, date.c_str());
		strcpy(_tmpcatalog, catalog.c_str());
		int i = 0;
		prin tt[xxxsize];
		for (int jp = 0; jp < strlen(_tmpcatalog); ++jp)
		{
			_catalog = _tmpcatalog[jp];
			_train_order.read(_catalog, x, _loc1);
			iter_train_order it1 = train_order_db.find(_train_order);
			//	cout << fixed<< setprecision(6)  << "233:" << it1.getkey().catalog << ' ' << it1.getkey().train_id.a << endl;
			train_order _train_order2;
			_train_order2.read(_catalog, x, _loc2);
			iter_train_order it2 = train_order_db.find(_train_order2);
			//	cout << fixed<< setprecision(6)  << "233:" << it2.getkey().catalog << ' ' << it2.getkey().train_id.a << endl;

			while (1)
			{
				//		cout << fixed<< setprecision(6)  << 1 << endl;
				if (it1.getkey().catalog != it2.getkey().catalog || it1.getkey().catalog != _catalog)
					break;

				//		cout << fixed<< setprecision(6)  << 2 << endl;
				if (strcmp(it1.getkey().station_name, _loc1) != 0)
					break;
				//		cout << fixed<< setprecision(6)  << 3 << endl;
				if (strcmp(it2.getkey().station_name, _loc2) != 0)
					break;
				//		cout << fixed<< setprecision(6)  << 4 << endl;
				if (strcmp(it1.getkey().train_id.a, it2.getkey().train_id.a) < 0)
				{
					++it1;
				}
				else if (strcmp(it1.getkey().train_id.a, it2.getkey().train_id.a) > 0)
				{
					++it2;
				}
				else
				{
					iter_train it3 = train_db.find(it1.getkey().train_id);
					//cout << fixed<< setprecision(6)  << "kkk:" << it3 -> ticket_name << endl;
					_date_train.read(_date, it1.getkey().train_id);

					iter_left_ticket it4 = left_ticket_db.find(_date_train);
					bool flag;
					if (_c3(it4.getkey(), _date_train) || _c3(_date_train, it4.getkey()))
						flag = 0;
					else
						flag = 1; //has date in lef_ticket

					char date1[ssize], date2[ssize];
					strcpy(date1, _date);
					strcpy(date2, _date);
					int l, r;
					for (l = 0; l < it3->num_station; ++l)
					{
						if (cmp(_loc1, it3->station_name[l]))
							break;
					}
					check_date(date1, it3->start_time[0], it3->start_time[l]);

					for (r = 0; r < it3->num_station; ++r)
					{
						if (cmp(_loc2, it3->station_name[r]))
							break;
					}
					check_date(date2, it3->start_time[0], it3->arriv_time[r]);

					if (l < r)
					{
						// cout << fixed<< setprecision(6)  << it3->train_id.a << ' ' << l << ' ' << r << ' ' << _loc1 << ' ' << _loc2 << endl;
						++i;
						// printf("%s %s %s %s %s ", it1.getkey().train_id.a, _loc1, date1, _loc2, date2);
						strcpy(tt[i].train_id, it3->train_id.a);
						strcpy(tt[i].loc1, _loc1);
						strcpy(tt[i].loc2, _loc2);
						strcpy(tt[i].date1, date1);
						strcpy(tt[i].date2, date2);
						strcpy(tt[i].time1, it3->start_time[l]);
						strcpy(tt[i].time2, it3->arriv_time[r]);
						tt[i].num_price = it3->num_price;
						tt[i].l = l;
						tt[i].r = r;

						for (int p = 0; p < it3->num_price; ++p)
						{
							// printf("%s %d %.2f ", it3->ticket_name[p], it4->check(l, r, p), it3->price[p]);
							strcpy(tt[i].ticket_name[p], it3->ticket_name[p]);
							if (flag)
								tt[i].left[p] = it4->check(l, r, p);
							else
								tt[i].left[p] = 2000;

							tt[i].pri[p] = 0;
							for (int se = l + 1; se <= r; ++se)
								tt[i].pri[p] += it3->price[se][p];
						}
					}
					++it1;
					++it2;
				}
			}
		}
		for (int j = 1; j <= i; ++j)
		{
			ticket_info tmp;
			tmp.get_info(tt[j]);
			result.append(tmp);
		}
	}
	bool _query_ticket(mstring x = mstring())
	{
		int i = 0;
		prin tt[xxxsize];
		_catalog = _tmpcatalog[0];
		_train_order.read(_catalog, x, _loc1);
		iter_train_order it1 = train_order_db.find(_train_order);
		//	cout << fixed<< setprecision(6)  << "233:" << it1.getkey().catalog << ' ' << it1.getkey().train_id.a << endl;
		train_order _train_order2;
		_train_order2.read(_catalog, x, _loc2);
		iter_train_order it2 = train_order_db.find(_train_order2);
		//	cout << fixed<< setprecision(6)  << "233:" << it2.getkey().catalog << ' ' << it2.getkey().train_id.a << endl;

		while (1)
		{
			//		cout << fixed<< setprecision(6)  << 1 << endl;
			if (it1.getkey().catalog != it2.getkey().catalog || it1.getkey().catalog != _catalog)
				break;

			//		cout << fixed<< setprecision(6)  << 2 << endl;
			if (strcmp(it1.getkey().station_name, _loc1) != 0)
				break;
			//		cout << fixed<< setprecision(6)  << 3 << endl;
			if (strcmp(it2.getkey().station_name, _loc2) != 0)
				break;
			//		cout << fixed<< setprecision(6)  << 4 << endl;
			if (strcmp(it1.getkey().train_id.a, it2.getkey().train_id.a) < 0)
			{
				++it1;
			}
			else if (strcmp(it1.getkey().train_id.a, it2.getkey().train_id.a) > 0)
			{
				++it2;
			}
			else
			{
				iter_train it3 = train_db.find(it1.getkey().train_id);
				//cout << fixed<< setprecision(6)  << "kkk:" << it3 -> ticket_name << endl;
				_date_train.read(_date, it1.getkey().train_id);

				iter_left_ticket it4 = left_ticket_db.find(_date_train);
				bool flag;
				if (_c3(it4.getkey(), _date_train) || _c3(_date_train, it4.getkey()))
					flag = 0;
				else
					flag = 1; //has date in lef_ticket

				char date1[ssize], date2[ssize];
				strcpy(date1, _date);
				strcpy(date2, _date);
				int l, r;
				for (l = 0; l < it3->num_station; ++l)
				{
					if (cmp(_loc1, it3->station_name[l]))
						break;
				}
				check_date(date1, it3->start_time[0], it3->start_time[l]);

				for (r = 0; r < it3->num_station; ++r)
				{
					if (cmp(_loc2, it3->station_name[r]))
						break;
				}
				check_date(date2, it3->start_time[0], it3->arriv_time[r]);

				if (l < r)
				{
					// cout << fixed<< setprecision(6)  << it3->train_id.a << ' ' << l << ' ' << r << ' ' << _loc1 << ' ' << _loc2 << endl;
					++i;
					// printf("%s %s %s %s %s ", it1.getkey().train_id.a, _loc1, date1, _loc2, date2);
					strcpy(tt[i].train_id, it3->train_id.a);
					strcpy(tt[i].loc1, _loc1);
					strcpy(tt[i].loc2, _loc2);
					strcpy(tt[i].date1, date1);
					strcpy(tt[i].date2, date2);
					strcpy(tt[i].time1, it3->start_time[l]);
					strcpy(tt[i].time2, it3->arriv_time[r]);
					tt[i].num_price = it3->num_price;
					tt[i].l = l;
					tt[i].r = r;

					for (int p = 0; p < it3->num_price; ++p)
					{
						// printf("%s %d %.2f ", it3->ticket_name[p], it4->check(l, r, p), it3->price[p]);
						strcpy(tt[i].ticket_name[p], it3->ticket_name[p]);
						if (flag)
							tt[i].left[p] = it4->check(l, r, p);
						else
							tt[i].left[p] = 2000;

						tt[i].pri[p] = 0;
						for (int se = l + 1; se <= r; ++se)
							tt[i].pri[p] += it3->price[se][p];
					}
				}
				++it1;
				++it2;
			}
		}

		//cout << fixed<< setprecision(6) << i << '\n';
		empty_list(result);
		for (int j = 1; j <= i; ++j)
		{
			ticket_info tmp;
			tmp.get_info(tt[j]);
			result.append(tmp);
		}

		return 0;
	}

	bool _query_transfer(const mstring &first, const mstring &second, int &min, const char *begin, const char *end, char *loc_mid)
	{
		int tmp = min;
		iter_train it1, it2;
		it1 = train_db.find(first);
		it2 = train_db.find(second);
		if (it1->sale == -1 || it2->sale == -1)
			return 0;
		int cnt = 0;
		int l, r; //l --- i, j --- r
		for (l = 0; l < it1->num_station; ++l)
			if (strcmp(it1->station_name[l], begin) == 0)
				break;
		for (r = 0; r < it2->num_station; ++r)
			if (strcmp(it2->station_name[r], end) == 0)
				break;
		for (int i = l; i < it1->num_station; ++i)
		{
			for (int j = 0; j <= r; ++j)
			{
				if (strcmp(it1->station_name[i], it2->station_name[j]) == 0)
				{
					//some rules
					int time = 0;
					time += minutes(it1->start_time[l], it1->arriv_time[i]);
					time += minutes(it1->start_time[i], it2->start_time[j]);
					time += minutes(it1->start_time[j], it2->arriv_time[l]);
					if (time < min)
					{
						min = time;
						strcpy(loc_mid, it1->station_name[i]);
					}
				}
			}
		}
		if (min < tmp)
			return 1;
		else
			return 0;
	}

	void query_transfer()
	{
		empty_list(result);
		mstring x = mstring();
		strcpy(_loc1, loc1.c_str());
		strcpy(_loc2, loc2.c_str());
		strcpy(_date, date.c_str());
		strcpy(_tmpcatalog, catalog.c_str());
		mstring tt[xxxsize];
		char c1[xxxsize];
		int size = 0;
		iter_train_order it1;

		int min = 0x7ffffff;
		char loc_head[msize];
		char loc_mid[msize];
		char loc_tail[msize];
		strcpy(loc_head, _loc1);
		strcpy(loc_tail, _loc2);
		mstring first, second;
		char _c2;
		char _c1;

		for (int pp = 0; pp < strlen(_tmpcatalog); ++pp)
		{
			_catalog = _tmpcatalog[pp];
			_train_order.read(_catalog, mstring(), _loc1);
			it1 = train_order_db.find(_train_order);
			while (1)
			{
				if (_catalog != it1.getkey().catalog || strcmp(_loc1, it1.getkey().station_name) != 0)
					break;
				tt[++size] = it1.getkey().train_id;
				c1[size] = _catalog;
				++it1;
			}
		}
		//cout << size << endl;
		for (int pp = 0; pp < strlen(_tmpcatalog); ++pp)
		{
			_catalog = _tmpcatalog[pp];
			_train_order.read(_catalog, mstring(), _loc2);

			it1 = train_order_db.find(_train_order);
			int i = size;
			while (i)
			{
				if (_catalog != it1.getkey().catalog || strcmp(_loc2, it1.getkey().station_name) != 0)
					break;
				if (strcmp(tt[i].a, it1.getkey().train_id.a) == 0)
				{
					--i;
					continue;
				}
				if (_query_transfer(tt[i], it1.getkey().train_id, min, _loc1, _loc2, loc_mid))
				{
					_c2 = _catalog;
					_c1 = c1[i];
					first = tt[i];
					second = it1.getkey().train_id;
					//cout << "get  "<< i << endl;
				}
				i--;
			}
		}
		if (strlen(first.a) == 0)
		{
			cout << -1 << '\n';
			return;
		}

		strcpy(_loc1, loc_head);
		strcpy(_loc2, loc_mid);
		_train_id = first;
		memset(_tmpcatalog, '\0', msize);
		_tmpcatalog[0] = _c1;
		_query_ticket(_train_id);

		strcpy(_loc1, loc_mid);
		strcpy(_loc2, loc_tail);
		_train_id = second;
		memset(_tmpcatalog, '\0', msize);
		_tmpcatalog[0] = _c2;
		_query_ticket(_train_id);
	}
	/*
	bool query_order()
	{
		int sum = 0;
		ticket tt[xxxsize];
		for (int i = 0; i < strlen(_tmpcatalog); ++i)
		{
			_catalog = _tmpcatalog[i];
			// cout << fixed<< setprecision(6) <<_catalog<<endl;
			_user_ticket.read(_catalog, _id1, _date, _train_id, "\0", "\0");
			iter_ticket it = ticket_db.find(_user_ticket);
			while (1)
			{
				if (it == ticket_db.end())
					break;
				// cout << fixed<< setprecision(6) <<"!!!"<<" "<<_user_ticket.train_id<<endl;
				if (!_c4(_user_ticket, it.getkey()) && !_c4(it.getkey(), _user_ticket))
					break;
				//it->print();
				++sum;
				// cout << fixed<< setprecision(6) <<"~~~"<<endl;
				// cout << fixed<< setprecision(6) <<"!!!"<<endl;
				tt[sum].read(*it);
				// cout << fixed<< setprecision(6) <<"=.="<<endl;
				++it;
				// cout << fixed<< setprecision(6) <<"===="<<endl;
			}
		}
		// int i = size;
		cout << fixed << setprecision(6) << sum << '\n';
		while (sum)
		{
			tt[sum].print();
			sum--;
		}
		// cout << fixed<< setprecision(6) <<_catalog<<endl;
		return 1;
	}
	*/
	bool query_all_order()
	{
		int sum = 0;
		_id1 = uid;
		ticket tt[xxxsize];
		mstring x;
		_user_ticket.read('\0', _id1, "\0", x, "\0", "\0");
		iter_ticket it = ticket_db.find(_user_ticket);
		while (1)
		{
			if (it == ticket_db.end())
				break;
			if (it.getkey().userid != _id1)
				break;
			++sum;
			tt[sum].read(*it);
			++it;
		}
		empty_list(result);
		for (int j = 1; j <= sum; ++j)
		{
			ticket_info tmp;
			tmp.get_info(tt[j]);
			result.append(tmp);
		}
		return 1;
	}
};
bool clean()
{
	try
	{
		user_db.clear();
		train_db.clear();
		train_order_db.clear();
		left_ticket_db.clear();
		ticket_db.clear();
		//sss.clear();
		return 1;
	}
	catch (...)
	{
		return 0;
	}
}

void m_init()
{
	fstream io("user");
	if (!io)
	{
		ofstream out("user");
		out << inner_id;
		out.close();
		io.open("user");
	}
	io >> inner_id;
	io.close();
}

BOOST_PYTHON_MODULE(database)
{
	def("clean", clean);
	def("minit", m_init);

	class_<user_get>("user_get", init<>())
		.def("find", &user_get::find)
		.def("find_by_email", &user_get::find_by_email)
		.def("modify", &user_get::modify)
		.def("add_user", &user_get::add_user)
		.def_readwrite("uid", &user_get::uid)
		.def_readwrite("valid", &user_get::valid)
		.def_readwrite("name", &user_get::name)
		.def_readwrite("email", &user_get::email)
		.def_readwrite("phone", &user_get::phone)
		.def_readwrite("privilege", &user_get::privilege)
		.def_readwrite("confirm", &user_get::confirm)
		.def_readwrite("password", &user_get::password);

	class_<train_get>("train_get", init<>())
		.def("find", &train_get::find)
		.def("generate_list", &train_get::generage_list)
		.def("add_train", &train_get::add_train)
		.def("sale_train", &train_get::sale_train)
		.def("delete_train", &train_get::delete_train)
		.def("modify_train", &train_get::modify_train)
		.def_readwrite("sale", &train_get::sale)
		.def_readwrite("valid", &train_get::valid)
		.def_readwrite("name", &train_get::name)
		.def_readwrite("catalog", &train_get::catalog)
		.def_readwrite("train_id", &train_get::train_id)
		.def_readwrite("ticket_name", &train_get::ticket_name)
		.def_readwrite("station_name", &train_get::station_name)
		.def_readwrite("start_time", &train_get::start_time)
		.def_readwrite("arriv_time", &train_get::arriv_time)
		.def_readwrite("stopover_time", &train_get::stopover_time)
		.def_readwrite("price", &train_get::price)
		.def_readonly("num_price", &train_get::num_price)
		.def_readonly("num_station", &train_get::num_station);

	class_<ticket_operate>("ticket_operate", init<>())
		.def("buy_ticket", &ticket_operate::buy_ticket)
		.def("refund_ticket", &ticket_operate::refund_ticket)
		.def_readwrite("uid", &ticket_operate::uid)
		.def_readwrite("num", &ticket_operate::num)
		.def_readwrite("loc1", &ticket_operate::loc1)
		.def_readwrite("loc2", &ticket_operate::loc2)
		.def_readwrite("date", &ticket_operate::date)
		.def_readwrite("train_id", &ticket_operate::train_id)
		.def_readwrite("ticket_name", &ticket_operate::ticket_name);

	class_<ticket_info>("ticket_info", init<>())
		.def_readwrite("train_id", &ticket_info::train_id)
		.def_readwrite("loc1", &ticket_info::loc1)
		.def_readwrite("loc2", &ticket_info::loc2)
		.def_readwrite("time1", &ticket_info::time1)
		.def_readwrite("time2", &ticket_info::time2)
		.def_readwrite("date1", &ticket_info::date1)
		.def_readwrite("date2", &ticket_info::date2)
		.def_readwrite("ticket_name", &ticket_info::ticket_name)
		.def_readwrite("left", &ticket_info::left)
		.def_readwrite("pri", &ticket_info::pri);

	class_<ticket_get>("ticket_get", init<>())
		.def("query_ticket", &ticket_get::query_ticket)
		.def("query_order", &ticket_get::query_all_order)
		.def("query_transfer", &ticket_get::query_transfer)
		.def_readwrite("uid", &ticket_get::uid)
		.def_readwrite("loc1", &ticket_get::loc1)
		.def_readwrite("loc2", &ticket_get::loc2)
		.def_readwrite("date", &ticket_get::date)
		.def_readwrite("catalog", &ticket_get::catalog)
		.def_readwrite("result", &ticket_get::result);
}