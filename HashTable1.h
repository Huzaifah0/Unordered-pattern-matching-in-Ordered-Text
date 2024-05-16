#pragma once
#include<iostream>
#include<string>
using namespace std;
typedef unsigned long long int lint;


template <class T>
struct node {
	T value;
	node<T>* next;
	node(T val=0) {
		value = val;
		next = NULL;
	}
};

template <class T>
struct c_node {
	T value;
	int count;
	c_node<T>* next;
	c_node(T val = 0) {
		value = val;
		next = NULL;
		count = 1;
	}
};

template <class T>
class list {
public:
	node<T>* head;
	list() {
		head = NULL;
	}
	void insert(T val){
		if (!head) {
			head = new node<T>(val);
			return;
		}
		node<T>* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new node<T>(val);
	}
	bool remove(T val) {
		node<T>* temp = head->next;
		node<T>* prev = head;
		if (head->value == val) {
			delete head;
			head = temp;
			return true;
		}
		while (temp != NULL) {
			if (temp->value == val) {
				prev->next = temp->next;
				delete temp;
				return true;
			}
			prev = temp;
			temp = temp->next;
		}
		return false;
	}
	void print() {
		node<T>* temp = head;
		while (temp->next != NULL) {
			cout << temp->value<<"->";
			temp = temp->next;
		}
		cout << temp->value;
		cout << endl;
	}
	node<T>* get_head() {
		return head;
	}
};

template <class T>
class count_list {
	c_node<T>* head;
public:
	count_list() {
		head = NULL;
	}
	void insert(T val) {
		if (!head) {
			head = new c_node<T>(val);
			return;
		}
		if (head->value == val) {
			head->count++;
			return;
		}
		c_node<T>* temp = head;
		while (temp->next != NULL) {
			if (temp->next->value == val) {
				temp->next->count++;
				return;
			}
			temp = temp->next;
		}
		temp->next = new c_node<T>(val);
	}
	bool remove(T val) {
		c_node<T>* temp = head->next;
		c_node<T>* prev = head;
		if (head->value == val) {
			head->count--;
			if (head->count <= 0) {
				delete head;
				head = temp;
			}
			return true;
		}
		while (temp != NULL) {
			if (temp->value == val) {
				temp->count--;
				if (temp->count <= 0) {
					prev->next = temp->next;
					delete temp;
				}
				return true;
			}
			prev = temp;
			temp = temp->next;
		}
		return false;
	}
	int search(T val) {
		c_node<T>* temp = head;
		while (temp != NULL) {
			if (temp->value == val) {
				return temp->count;
			}
			temp = temp->next;
		}
		return 0;
	}
	void print() {
		c_node<T>* temp = head;
		if (!head) { 
			cout << endl;
			return;
		}
		while (temp->next != NULL) {
			cout <<"(" << temp->value << " , " << temp->count << ") ->";
			temp = temp->next;
		}
		cout << "(" << temp->value << " , " << temp->count << ")";
		cout << endl;
	}
};

template <class T>
class HashTable{
	int hash;
	count_list<T>* table;
public:
	HashTable(int size=5) {
		if (size <= 5) {
			size = 5;//prime number close to powers of 2 for good distributions
		}
		table = new count_list<T>[size];
		hash = size;
	}
	void insert(T value) {
		int key = value % hash;
		table[key].insert(value);
	}
	bool remove(T value) {
		int key = value % hash;
		return table[key].remove(value);
	}
	int search(T value) {
		int key = value % hash;
		return table[key].search(value);
	}
	void print() {
		for (int i = 0; i < hash; i++) {
			cout << "Key " << i << ": "; table[i].print();
		}
	}
};

bool is_prime(int n) {
	if (n == 1) {
		return false;
	}
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int compute_hash(int n) {
	int hash = 1;
	for (; n > hash; hash *= 2);
	for (hash--; !is_prime(hash); hash-= 2);
	return hash;
}

struct group {
	int size;
	HashTable<lint>* values;
	group(int s=0):size(s), values(NULL) {
	}
	void insert(lint value) {
		values->insert(value);
	}
	void init() {
		values = new HashTable<lint>(size);
	}
};