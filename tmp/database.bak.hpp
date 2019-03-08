#pragma once

#include <iostream>
#include <cstdio>
#include <fstream>
#include <utility>

using namespace std;
typedef int int32_t;// cant use unsigned!!! because: i-- and i>= 0 will wrong

#pragma region class exception

class errors {};
class file_error : public errors { };
//class index_out : public errors { };
class repetition : public errors { };
class not_exist : public errors { };
class out_of_bound : public errors { };
class node_full : public errors { };

#pragma endregion

// if use template<char const * file>have to define file like:
// the whole program:: extern char const s[] = "filename"

#define bits 1024*4 // bits with one block
//#define fileNameSize 100

inline constexpr int32_t half(const int32_t &pos) noexcept {// with ceil()
	if (pos % 2 == 0) return pos / 2;
	else return pos / 2 + 1;
}

template<class Key, class V>//figure out can fugure idx and datanode
inline constexpr int32_t figure_size() noexcept {
	int32_t size1 = sizeof(int32_t) * 4;
	int32_t left = bits - size1;
	return left / (sizeof(Key) + sizeof(V));
}


template<class Key, class V, class Compare = std::less<Key>> 
class database {
private:

	class idxNode;
	class dataNode;

public:

	class iterator;

private:
	// tellp --- tellg
	// putp  --- kutg
	// put in file --- get from file
	// write --- read
	fstream idx;
	fstream data;
	
	Compare cmp;// cmp(k, key[ss]), k < key[ss] then s.t.
	const char *idxfile;//const char idxfile[fileNameSize];
	const char *datafile;//const char datafile[fileNameSize];
	const int32_t dataSize;
	const int32_t idxSize;
	const int32_t hdataSize;
	const int32_t hidxSize;

	// it is about nodeBlock with many small (key,v)s
	// real last pos = _last_data;
	// eg.
	// no data:_last_data = 0;
	// 2 datas:_last_data = 2;
	// like if we put first dataNode in file
	// node.pos = 1, and _last_data++;
	// but the ios::end is at ((_last_data+1)*bits,ios::beg))
	// because the fisrt block is filled by others
	int32_t _last_idx = 1;// in datafile, pos in 0
	int32_t _last_data = 0;// in datafile, pos in 1*sizeof(int32_t)
	int32_t allsize = 0;//in datafile, pos = 2*sizeof(int32_t), datapair<k, v> size
	dataNode tail;//pos == 0, only need left, which stored in 3*sizeof(int32_t) in datafile

	idxNode root;//pos == 1, in idxfile

	int32_t _tmpPosinNode;//no need to init
	int32_t _tmpPosinTree;//no need to init

private:

	// key   1 2 3 4 5
	// son  0 1 2 3 4 5
	// each part of son[k], s.t. son[k]'s all key >= key[k]
	//pos == 0 means it is point at the end, or invalid 
	class idxNode {
	public:

		// size means the size of son
		// size init with 0, key[] start at 1, son start at 0
		int32_t size = 1;
		int32_t pos = 0;

		Key key[figure_size<Key, int32_t>()];
		int32_t son[figure_size<Key, int32_t>()] = { 0 };

		// can be optimized
		// type == 1 last level; type == 0, not last level
		int32_t type = 1;

	public:
		idxNode() { }
		idxNode(const int32_t pos, const int32_t size, const int32_t type):pos(pos), size(size), type(type) { }
		idxNode(int status)  {
			if (status == 0) {
				//init root
				//root pos at 1, no father
				pos = 1;
				type = 1;//means it is the last level
				size = 1;
				son[0] = 1;//init
			}
		}
		~idxNode() = default;
		idxNode &operator=(const idxNode &other) {
			pos = other.pos;
			type = other.type;
			size = other.size;
			for (int32_t i = 0; i < other.size; ++i) {
				key[i] = other.key[i];
				son[i] = other.son[i];
			}
			return *this;
		}

	};

	// key  0 1 2 3 4 5
	// son  0 1 2 3 4 5
	//pos == 0 means it is point at the end, or invalid 
	class dataNode {
	public:

		int32_t pos = 0;// using pos == 0 to tag it haven't write in file
		int32_t size = 0;	

		int32_t left = 0, right = 0;

		Key key[figure_size<V, Key>()];
		V data[figure_size<V, Key>()];

	public:

		dataNode() { };

		// default dont write in the file
		dataNode(const Key &k, const V &val, int32_t _pos):pos(_pos), size(1) {
			key[0] = k;
			data[0] = val;
		}
		~dataNode() = default;
		dataNode &operator=(const dataNode &other) {
			size = other.size;
			pos = other.pos;
			left = other.left;
			right = other.right;
			for (int32_t i = 0; i < other.size; ++i) {
				key[i] = other.key[i];
				data[i] = other.data[i];
			}
			return *this;
		}

	};

private:

	// in the faNode, but not add in the file
	// have to judge all things outside
	// and suppose no repetition
	void add(idxNode &x, const Key &k, const int32_t son_pos, bool flag = 0) {
		if (x.size == idxSize) throw node_full();

		int32_t i;
		for (i = flag ? 0 : 1; i < x.size; ++i)// to prevent i = 0 can also insert
			if (cmp(k, x.key[i])) break;

		for (int32_t j = x.size; j > i; --j) {
			x.key[j] = x.key[j - 1];
			x.son[j] = x.son[j - 1];
		}
		x.key[i] = k;
		x.son[i] = son_pos;

		++x.size;
		return;
	}

	//no writing
	//no judging merge or adopt
	//judge delpos ouotside
	void del(idxNode &x,  const int32_t pos) {
		if (x.size == 0) throw not_exist();
		--x.size;
		for (int32_t i = pos; i < x.size; ++i) {
			x.key[i] = x.key[i + 1];
			x.son[i] = x.son[i + 1];
		}
		return;
	}

	// in the faNode, but not add in the file
	int32_t add(dataNode &x, const Key &k, const V &val) {

		if (x.size == dataSize) throw node_full();

		//way 2
		int32_t i;
		for (i = 0; i < x.size; ++i)
			if (cmp(k, x.key[i])) 	break;//??

		if (i > 0 && !cmp(k, x.key[i - 1]) && !cmp(x.key[i - 1], k)) throw repetition();

		for (int32_t j = x.size; j > i; --j) {
			x.key[j] = x.key[j - 1];
			x.data[j] = x.data[j - 1];
		}
		x.key[i] = k;
		x.data[i] = val;
		++x.size;

		return i;//insert pos
	}

	//no file writing
	//no merge adopt
	int32_t del(dataNode &x, int32_t _deletepos) {
		if (x.size == 0) throw not_exist();

		--x.size;
		for (int32_t i = _deletepos; i < x.size; ++i) {
			x.key[i] = x.key[i + 1];
			x.data[i] = x.data[i + 1];
		}

		//if (size == 0) valid = 0;
		return _deletepos;
	}

public:

	//just for datafile
	class iterator {
	private:

		int32_t cur;//in the dataNode
		dataNode now;
		database *mine;

	public:

		friend class database;// necessary?

		iterator()
			: cur(0), mine(nullptr), now(dataNode()) { }
		iterator(database *p, const dataNode &x, const int32_t &cur = 0)
			: now(x), cur(cur), mine(p) { }
		iterator(database *p, const int32_t &_posintree, const int32_t &_posinnode)
			: cur(_posinnode), mine(p) {
			(*mine).read(_posintree, now);
		}
		iterator(const iterator &other)
			: cur(other.cur), mine(other.mine), now(other.now) { }
		~iterator() { }
		iterator &operator=(const iterator &other) {
			cur = other.cur;
			mine = other.mine;
			now = other.now;
			return *this;
		}

		iterator &operator++() {

			if (now.pos == 0) throw out_of_bound();
			if (now.size > cur + 1) {
				++cur;
				return *this;
			}
			if (now.right == 0) {
				now = (*mine).tail;
				cur = 0;
				return *this;
			}
			(*mine).read(now.right, now);
			cur = 0;
			return *this;
		}
		iterator operator++(int) {
			iterator tmp = *this;
			++(*this);
			return tmp;
		}
		Key &getkey() {
			return now.key[cur];
		}
		iterator &operator--() {
			if (cur > 0) {
				--cur;
				return *this;
			}
			if (now.left == 0) throw out_of_bound();
			(*mine).read(now.left, now);//now.pos == 0 //tail also ok
			cur = now.size - 1;
			return *this;
		}
		iterator operator--(int) {
			iterator tmp = *this;
			--(*this);
			return tmp;
		}

		V &operator*() { 
			if (now.pos == 0) throw out_of_bound();
			return now.data[cur];
		}
		V *operator->() noexcept { return &(now.data[cur]); }
		void write(){ (*mine).write(now); }

		bool operator==(const iterator &rhs) const {
			if (rhs.mine != mine) return 0; // node != override havent done, so cant use it
			if (!cmp(now.key[cur], rhs.now.key[cur]) && !cmp(rhs.now.key[cur], now.key[cur])) return 1;		
			return 0;
		}
		bool operator!=(const iterator &rhs) const { return !(*this == rhs); }

	};

private:

	void read(int32_t pos, dataNode &x) {
		if (pos == 0) throw not_exist();
		data.seekg(pos*bits);
		data.read(reinterpret_cast<char*>(&x), sizeof(dataNode));
	}
	void read(int32_t pos, idxNode &x) {
		if (pos == 0) throw not_exist();
		idx.seekg(pos*bits);
		idx.read(reinterpret_cast<char*>(&x), sizeof(idxNode));
	}
	void write(dataNode &x) {
		data.seekp(x.pos*bits);
		data.write(reinterpret_cast<char*>(&x), sizeof(dataNode));
	}
	void write(idxNode &x) {
		idx.seekp(x.pos*bits);
		idx.write(reinterpret_cast<char*>(&x), sizeof(idxNode));
	}

	// if cant't find cur key, return the next pair which s.t. key[] >= k
	//but here only return datanode, which is no use
	int32_t pfind(const Key &k, idxNode cur) {
		if (empty()) {
			return  0;
		}

		int32_t i;
		while (true) {
			if (cur.type == 1) {// next is leaf
				for (i = cur.size - 1; i > 0; --i)
					if (!cmp(k, cur.key[i])) break;
				return cur.son[i];
				
			}
			//type == 0, not the last level idxnode

			//way
			for (i = cur.size - 1; i > 0; --i)
				if (!cmp(k, cur.key[i])) break;

			read(cur.son[i], cur);
		}

	}

	int32_t pbegin(const int32_t _cur) {
		idxNode cur;
		read(_cur, cur);

		while (true) {
			if (cur.type == 1) {// next is leaf
				int32_t _curpos2 = cur.son[1];
				read(cur.son[0], cur);
				if (cur.size == 0) return _curpos2;
				return cur.son[0];
			}
			int32_t _curpos2 = cur.son[1];
			read(cur.son[0], cur);
			if (cur.size == 1) read(_curpos2, cur);
		}
	}

	//havent write oldnode and newnode
	//key[_breaksize] is the boundary
	void split(const int32_t _breaksize, idxNode &cur, idxNode &_new) {
		int32_t i, j;
		for (i = _breaksize, j = 0; i < cur.size; ++i, ++j) {
			_new.key[j] = cur.key[i];//for j = 0, key[_breaksize] is useless
			_new.son[j] = cur.son[i];
		}

		_new.type = cur.type;
		_new.size = cur.size - _breaksize;
		cur.size = _breaksize;

		++_last_idx;
		_new.pos = _last_idx;

		return;
	}

	//k is the insert key, and insert son pos is son_pos which > key
	pair<Key, int32_t> addIdx(const Key &k, const int32_t son_pos, idxNode &cur) {
		if (cur.size < idxSize) {
			//if (!cur.pos) cur.pos = ++_last_idx;
			add(cur, k, son_pos);
			write(cur);
			
			return pair<Key, int32_t>(cur.key[1], 0);
		}

		//split
		idxNode newNode;// newNode is hte same level of dataNode
		int32_t i;
		for (i = cur.size - 1; i > 0; --i)///!!!!!!!,for what ? --i not ++i, but can figure out the problem because break;
			if (!cmp(k, cur.key[i])) break;

		Key tmp;//tmp is the key between old and newnode
		int32_t mid = hidxSize;
		if (i + 2 <= mid) { ///half dont need, for what? i + 1 is not enough, mid means the 1st half node size;
			mid = mid - 1;
			tmp = cur.key[mid];
			split(mid, cur, newNode);
			add(cur, k, son_pos);
		}
		else {
			if (cmp(k, cur.key[mid])) tmp = k;///for what?  maybe k is even smaller than keymid, so add is not allowed,???maybe not necessary
			else tmp = cur.key[mid];
			split(mid, cur, newNode);
			add(newNode, k, son_pos, 1);
		}
		//newNode always larger than curnode
		write(newNode);
		write(cur);

		return pair<Key, int32_t>(tmp, newNode.pos);
	}

	//havent write oldnode and newnode
	void split(const int32_t _breaksize, dataNode &cur, dataNode &_new) {
		int32_t i, j;
		for (i = _breaksize, j = 0; i < cur.size; ++i, ++j) {
			_new.key[j] = cur.key[i];
			_new.data[j] = cur.data[i];
		}
		
		_new.size = cur.size - _breaksize;
		cur.size = _breaksize;
		
		++_last_data;
		_new.pos = _last_data;

		if (cur.right) {
			dataNode tmp;
			read(cur.right, tmp);
			_new.right = cur.right;
			tmp.left = _last_data;
			write(tmp);
		}
		else {
			tail.left = _last_data;
			//data.seekp(bits - sizeof(int32_t));
			//data.write(reinterpret_cast<char*>(&tail.left), sizeof(int32_t));
		}

		cur.right = _last_data;//newNode pos
		_new.left = cur.pos;
		return;
	}

	pair<Key, int32_t> addData(const Key &k, const V &val, int32_t _cur) {
		++allsize;
		dataNode cur;
		read(_cur, cur);

		if (cur.size < dataSize) {
			_tmpPosinTree = _cur;
			_tmpPosinNode = add(cur, k, val);
			write(cur);

			return pair<Key, int32_t>(cur.key[0], 0);
		}

		//split
		dataNode newNode;// newNode is hte same level of dataNode

		int32_t i;
		for (i = 0; i < cur.size; ++i)
			if (cmp(k, cur.key[i])) break;// i is the pos of <key, val> which will be replace by the insert pair

		// 1 2 3 ----- hidxSize    hidxSize+1 ---- size
		// 0 1 2 ---- hidxSize-1    hidxSize+2 ----- size-1
		//   ^k, then 
		// start from 0 to hidxSize-1 is oldnode
		int32_t mid = hdataSize;
		if (i + 1 <= mid) { //half dont need
			mid = mid - 1;
			split(mid, cur, newNode);
			_tmpPosinTree = _cur;
			_tmpPosinNode = add(cur, k, val);
		}
		else {
			split(mid, cur, newNode);
			_tmpPosinTree = newNode.pos;
			_tmpPosinNode = add(newNode, k, val);
		}
		//newNode always larger than curnode
		write(newNode);
		write(cur);
		return pair<Key, int32_t>(newNode.key[0], newNode.pos);
	}

	//key always return the min key between(oldnode, newnode) for usage
	pair<Key, int32_t> pinsert(const Key &k, const V &val, int32_t _cur) {
		idxNode cur;
		read(_cur, cur);
		//read(1, root);
		int32_t i;
		for (i = cur.size - 1; i > 0; --i)
			if (!cmp(k, cur.key[i])) break;

		pair<Key, int32_t> p;
		if (cur.type == 1)  p = addData(k, val, cur.son[i]);
		else 	p = pinsert(k, val, cur.son[i]);

		if (p.second) p = addIdx(p.first, p.second, cur);// once p.second == 0, all of the recursive functions.second == 0
		//write(cur);

		return p;

	}


	void merge(idxNode &remain, idxNode &del, const Key &k) {
		int32_t j, i;
		for (i = 0, j = remain.size; i < del.size; ++i, ++j) {
			remain.key[j] = del.key[i];
			remain.son[j] = del.son[i];
		}
		remain.key[remain.size] = k;
		remain.size += del.size;
		del.size = 0;//do it later than the sentence below
		return;
	}
	pair<Key, int32_t> delIdx(const int32_t delpos, int32_t _neighbor, idxNode &cur, const bool left, const Key &_k) {
		del(cur, delpos);

		if (cur.pos == 1) {// maybe for root
			write(cur);
			return pair<Key, int32_t>(cur.key[0], 0);
		}
		if (cur.size >= hidxSize) {
			write(cur);
			return pair<Key, int32_t>(cur.key[0], 0);
		}

		idxNode neighbor;
		read(_neighbor, neighbor);
		if (left) {
			if (neighbor.size > hidxSize) {
				--neighbor.size;
				//add(cur, _k, neighbor.son[neighbor.size], 1);----wrong code
				//for: _k may== neighbor.key[0] then can add(); 
				//add function:
				//     |--[key]--|
				//              son
				//here adopt from left sib
				//     |--[key]--|
				//    son
				//way1:
				cur.key[0] = _k;
				add(cur, neighbor.key[neighbor.size], neighbor.son[neighbor.size], 1);
				//way2
				//for(i = 0; i < cur.size; ++i) cur.son[i+1] = cur.son[i], cur.key[i+1] = cur.key[i];
				//cur.key[1] = _k; cur.son[0] = neighbor.son[neighbor.size];
				write(cur);
				write(neighbor);
				return pair<Key, int32_t>(neighbor.key[neighbor.size], 1);
			}
			else {//delete cur
				merge(neighbor, cur, _k);
				write(neighbor);
				return pair<Key, int32_t>(neighbor.key[0], 2);//key is useless
			}
		}
		else {
			if (neighbor.size > hidxSize) {
				cur.key[cur.size] = _k;
				cur.son[cur.size] = neighbor.son[0];
				++cur.size;
				del(neighbor, 0);
				write(cur);
				write(neighbor);
				return pair<Key, int32_t>(neighbor.key[0], 3);
			}
			else {//delete neighbor
				merge(cur, neighbor, _k);
				write(cur);
				return pair<Key, int32_t>(neighbor.key[0], 4);//key is useless
			}
		}
	}
	void merge(dataNode &remain, dataNode &del) {
		int32_t i, j;
		for (i = 0, j = remain.size; i < del.size; ++i, ++j) {
			remain.key[j] = del.key[i];
			remain.data[j] = del.data[i];
		}
		remain.size += del.size;
		del.size = 0;
		return;
	}
	pair<Key, int32_t> delData(const Key &k, int32_t _neighbor, int32_t _cur, const bool left) {
		dataNode cur;
		read(_cur, cur);

		int32_t i;
		for (i = 0; i < cur.size; ++i)
			if (!cmp(k, cur.key[i]) && !cmp(cur.key[i], k)) break;
		if (i == cur.size) throw not_exist();

		--allsize;
		_tmpPosinTree = cur.pos;
		_tmpPosinNode = del(cur, i);

		if (cur.size >= hdataSize) {
			write(cur);
			return pair<Key, int32_t>(cur.key[0], 0);//key is useless
		}

		dataNode neighbor;
		read(_neighbor, neighbor);
		if (left) {
			if (neighbor.size > hdataSize) {
				--neighbor.size;
				add(cur, neighbor.key[neighbor.size], neighbor.data[neighbor.size]);
				write(cur);
				write(neighbor);
				return pair<Key, int32_t>(neighbor.key[neighbor.size], 1);
			}
			else {
				merge(neighbor, cur);

				write(neighbor);
				return pair<Key, int32_t>(neighbor.key[neighbor.size], 2);//key is useless
			}
		}
		else {
			if (neighbor.size > hdataSize) {
				cur.data[cur.size] = neighbor.data[0];
				cur.key[cur.size] = neighbor.key[0];
				++cur.size;
				del(neighbor, 0);
				write(cur);
				write(neighbor);
				return pair<Key, int32_t>(neighbor.key[0], 3);
			}
			else {
				merge(cur, neighbor);
				write(cur);
				return pair<Key, int32_t>(neighbor.key[0], 4);//key is useless
			}
		}
	}
	pair<Key, int32_t> perase(const Key &k, int32_t _neighbor, int32_t _cur, bool left, const Key &_k) {
		idxNode cur;
		read(_cur, cur);

		int32_t i;
		for (i = cur.size - 1; i >= 0; --i)
			if (!cmp(k, cur.key[i])) break;

		pair<Key, int32_t> p;//1 -->adopt from left, 3 -->adopt from right, 0 nothing, 2 merge from left, 4 merge from right
		if (cur.type == 1) {
			if (i > 0) p = delData(k, cur.son[i - 1], cur.son[i], 1);
			else p = delData(k, cur.son[i + 1], cur.son[i], 0);
		}
		else {
			if (i > 0) p = perase(k, cur.son[i - 1], cur.son[i], 1, cur.key[i]);
			else p = perase(k, cur.son[i + 1], cur.son[i], 0, cur.key[i + 1]);
		}


		switch (p.second) {
		case 0:
			return p;
		case 1:
			cur.key[i] = p.first;
			p.second = 0;
			write(cur);
			return p;
		case 3:
			cur.key[i + 1] = p.first;
			p.second = 0;
			write(cur);
			return p;
		case 2:
			return delIdx(i, _neighbor, cur, left, _k);
		case 4:
			return delIdx(i + 1, _neighbor, cur, left, _k);
		default:
			throw not_exist();
		}
	}

public:
	//first block is nothing, node start from second block
	//	means root.pos = 1, read root : seekg(1 * bits, ios::beg);

    database(const char *a, const char *b): idxfile(a), datafile(b),
		idxSize(10), dataSize(10)
		, hdataSize(half(dataSize)), hidxSize(half(idxSize)){

        ifstream in(idxfile);//read
		if (!in) {
			ofstream out(datafile);		
			if (!out) throw file_error();
			out.close();
			out.open(idxfile);
			if (!out) throw file_error();
			out.close();

			idx.open(idxfile, ios::binary | ios::in | ios::out);
			data.open(datafile, ios::binary | ios::in | ios::out);
			//root
			_last_data = 1;// init with data has no nodes
			_last_idx = 1;// init with data has 1 node(root)
			allsize = 0;

			root = idxNode(0);
			dataNode tmp;
			tmp.pos = 1;
			tail.left = 1;

			write(tmp);
			write(root);
			//write(root);
			//data.seekp(0);
			//data.write(reinterpret_cast<char*>(&_last_idx), sizeof(int32_t));
			//data.write(reinterpret_cast<char*>(&_last_data), sizeof(int32_t));
			//data.write(reinterpret_cast<char*>(&allsize), sizeof(int32_t));
			//data.write(reinterpret_cast<char*>(&tail.left), sizeof(int32_t));
		}
		else {
			in.close();

			idx.open(idxfile, ios::binary | ios::in | ios::out);
			if (!idx) throw file_error();
			data.open(datafile, ios::binary | ios::in | ios::out);
			if (!data) throw file_error();

			data.seekg(0);
			data.read(reinterpret_cast<char*>(&_last_idx), sizeof(int32_t));
			data.read(reinterpret_cast<char*>(&_last_data), sizeof(int32_t));
			data.read(reinterpret_cast<char*>(&allsize), sizeof(int32_t));
			data.read(reinterpret_cast<char*>(&tail.left), sizeof(int32_t));			

			read(1, root);
			//cout << 1 << '\n';

		}
    }

    ~database(){
		write(root);

		data.seekp(0);
		data.write(reinterpret_cast<char*>(&_last_idx), sizeof(int32_t));
		data.write(reinterpret_cast<char*>(&_last_data), sizeof(int32_t));
		data.write(reinterpret_cast<char*>(&allsize), sizeof(int32_t));
		data.write(reinterpret_cast<char*>(&tail.left), sizeof(int32_t));

		data.close();
		idx.close();
	}

	void clear() {
		idx.close();
		data.close();
		ofstream out(idxfile);
		if (!out) throw file_error();
		out.close();		
		out.open(datafile);
		if (!out) throw file_error();
		out.close();

		idx.open(idxfile, ios::binary | ios::in | ios::out);
		data.open(datafile, ios::binary | ios::in | ios::out);

		_last_data = 1;//init with one dataNode
		_last_idx = 1;
		allsize = 0;

		dataNode tmp;
		tmp.pos = 1;
		tail.left = 1;
		
		root = idxNode(0);
		write(root);
		write(tmp);
		//data.seekp(0);
		//data.write(reinterpret_cast<char*>(&_last_idx), sizeof(int32_t));
		//data.write(reinterpret_cast<char*>(&_last_data), sizeof(int32_t));
		//data.write(reinterpret_cast<char*>(&allsize), sizeof(int32_t));
		//data.write(reinterpret_cast<char*>(&tail.left), sizeof(int32_t));
	}

	bool empty() {
		if (allsize) return 0;
		return 1;
	}

	int32_t size(){
		return allsize;
	}
	
	//pair<bool, iterator> find(const Key &k) {
	//	read(1, root);
	//	return pfind(k, root);
	//}
	iterator find(const Key &k) {
		read(1, root);
		int32_t _pos = pfind(k, root);
		if (_pos == 0) return end();
		dataNode leaf;
		read(_pos, leaf);
		//way 
		size_t i;
		for (i = leaf.size - 1; i >= 0; --i)
			if (!cmp(k, leaf.key[i]))
				return iterator(this, leaf, i);
		//way can be optimized by binary search

		if (leaf.right) read(leaf.right, leaf);
		else leaf = tail;
		return iterator(this, leaf, 0);
	}

	iterator begin() {
		if (empty()) return end();
		
		int32_t cur = pbegin(1);
		return iterator(this, cur, 0);
	}

	iterator end() {
		return iterator(this, tail, 0);
	}

	// while split node, new node always inherit the larger part
	// while merge node, old (the one left)node always inherit the smaller part
	iterator insert(const Key &k, const V &val) {
		pair<Key, int32_t> p = pinsert(k, val, 1);


		//split a new node with root level
		if (p.second) {//return newnode pos
			read(1, root);// may change the values
			idxNode _newroot(1, 2, 0);
			++_last_idx;// which may be the pos of old root

			_newroot.son[0] = root.pos = _last_idx;
			_newroot.key[1] = p.first;
			_newroot.son[1] = p.second;

			write(_newroot);
			write(root);

			root = _newroot;
		}

		return iterator(this, _tmpPosinTree, _tmpPosinNode);
	}
	iterator insert(const std::pair<Key, V> &value) { return insert(value.first, value.second); }

	iterator erase(const Key &k) {
		if (empty()) throw not_exist();

		read(1, root);
		if (root.size == 1) {//special
			--allsize;
			dataNode tmp;
			read(root.son[0], tmp);
			int32_t i;
			for ( i = 0; i < tmp.size; ++i)
				if (!cmp(k, tmp.key[i]) && !cmp(tmp.key[i], k)) break;
			if (i == tmp.size) throw not_exist();
			_tmpPosinNode = del(tmp, i);
			write(tmp);
			return iterator(this, tmp, _tmpPosinNode);
		}

		pair<Key, int32_t> p = perase(k, 0, 1, 1, Key());

		read(1, root);
		if (root.size == 1 && root.type == 0) {
			read(root.son[0], root);
			root.pos = 1;
			write(root);
		}
		return iterator(this, _tmpPosinTree, _tmpPosinNode);
	}


	iterator erase(const Key &k, const V &val) {
		iterator tmp = find(k);
		if (*tmp != val) throw not_exist();

		return erase(k);
	}
	iterator erase(const std::pair<Key, V> &value) { return erase(value.first, value.second); }
	iterator erase(const iterator &iter) {
		if (iter.pos == 0) throw out_of_bound();
		return erase(iter.now.key[iter.cur]);
	}

	//can only change the value
	// will writen in file
	iterator modify(const Key &k, const V &val) {
		iterator iter = find(k);
		*(iter) = val;
		write(iter.now);
		return iter;
	}
	iterator modify(const std::pair<Key, V> &value) { return modify(value.first, value.second); }
	iterator modify(iterator &iter, const V &val) {
		if (iter.now.pos == 0) throw not_exist();
		*(iter) = val;
		write(iter.now);
		return iter;
	}

};



