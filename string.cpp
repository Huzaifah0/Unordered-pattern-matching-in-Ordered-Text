#include"HashTable1.h"
#include<fstream>
void read_from_file(string,group*&,list<lint>*&,int&,int&);
lint compute_value(string);//capable of doing around 14 length strings any greater cannot be declared unique
bool search(group*,node<lint>*&);


int main() {
	string path = "p1_input.txt";
	int test_count = 0,recipe_count=0;
	list<lint>* lists=NULL;
	group* recipes=NULL;
	read_from_file(path,recipes,lists,test_count,recipe_count);
	/*for (int i = 0; i < test_count; i++) {
		lists[i].print();
	}
	for (int i = 0; i < recipe_count; i++) {
		recipes[i].values->print();
	}*/
	int counter=0;
	for (int i = 0; i < test_count; i++) {
		counter = 0;
		for (int j = 0; j < recipe_count; j++) {
			bool found=search(&recipes[j], lists[i].head);
			if (found) {
				counter++;
			}
		}
		if (counter == recipe_count) {
			cout << "Test case " << i + 1 << ": Passed." << endl;
		}
		else {
			cout << "Test case " << i + 1 << ": Failed." << endl;
		}
	}
	return 0;
}

void read_from_file(string path,group* &recipes,list<lint>* &lists,int& test_count,int& recipe_count) {
	ifstream fin;
	fin.open(path);
	string text;
	getline(fin, text, '\0');
	fin.close();
	recipe_count = 0;
	test_count = 0;
	int i = 0;
	for (int j = 0; j < text.length(); j++) { if (text[j] == '[') { test_count++; } }
	while (text[i] != '}'||text[i+1]==44) {
		i++;
		if (text[i] == '}') {
			recipe_count++;
		}
	}
	recipes = new group[recipe_count];
	lists = new list<lint>[test_count];
	list<lint>* temp_val = new list<lint>[recipe_count];
	int current = 0;
	for (int k = 0; k < i; k++) {
		if (text[k] == 39) {
			string temp = "";
			k++;
			while (text[k] != 39) {
				temp += text[k];
				k++;
			}
			//insert temp into its recipe
			recipes[current].size++;
			temp_val[current].insert(compute_value(temp));
		}
		if (text[k] == '}') {
			current++;
		}
	}
	for (int i = 0; i < recipe_count;i++) {
		recipes[i].init();
		node<lint>* temp = temp_val[i].get_head();
		while (temp != NULL) {
 			recipes[i].insert(temp->value);
			temp = temp->next;
		}
	}
	current = 0;
	for (int k = i; k < text.length(); k++) {
		if (text[k] == 39) {
			string temp = "";
			k++;
			while (text[k] != 39) {
				temp += text[k];
				k++;
			}
			lists[current].insert(compute_value(temp));
		}
		if (text[k] == ']') {
			current++;
		}
	}
}

lint compute_value(string str) {
	lint value=0,power=1;
	for (int i = str.length()-1; i >=0; i--) {
		if (str[i] > 'A' && str[i] < 'Z') {
			str[i] += 32;
		}
		if (str[i] < 'a' || str[i]>'z') {
			return -1;
		}
		value += (str[i] - 97) * power;
		power *= 26;
	}
	return value;
}

bool search(group* search, node<lint>* &head) {
	node<lint>* temp = head;
	int size = search->size;
	int found = 0;
	HashTable<lint> searching(size);
	for (int i = 0; i < size; i++) {
		if (temp == NULL) {
			return false;
		}
		searching.insert(temp->value);
		int n1 = searching.search(temp->value);
		int n2 = search->values->search(temp->value);
		if (n1 == n2) {
			found += n2;
		}
		if (found == size) {
			head = temp->next;
			head = temp->next;
			return true;
		}
		temp = temp->next;
	}
	node<lint>* tbr = head;
	node<lint>* del_index= head;
	while (temp != NULL) {
		int n1 = searching.search(tbr->value);
		int n2 = search->values->search(tbr->value);
		if (n1 == n2) {
			found -= n2;
		}
		searching.remove(tbr->value);
		//search code
		searching.insert(temp->value);
		n1 = searching.search(temp->value);
		n2 = search->values->search(temp->value);
		if (n1 == n2) {
			found += n2;
		}
		if (found == size) {
			tbr->next = temp->next;
			return true;
		}
		temp = temp->next;
		del_index = tbr;
		tbr = tbr->next;
	}
	return false;
}