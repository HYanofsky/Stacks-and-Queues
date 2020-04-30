/*Hadassah Yanofsky
ECE264 - Data Structures and Algorithms 1
Cooper Union
Fall 2019
This code uses an absract classs called SimpleList to implements stacks and queues in a singly linked list*/

#include<iostream>
#include<fstream>
#include<string>
#include<list>
using namespace std;

//parent class that holds a pointer to the first and last of the list as well as the name of the list
template <class T>
class SimpleList {
	//This stores the value and pointer to the next node for each node of the list
	class node {
	public:
		T value;
		node* next;
	};
protected:
	node* head, * tail;
	string name;
public:
	//constructor
	SimpleList() {
		head = NULL;
		tail = NULL;
	}
	string get_name() {
		return name;
	}
	virtual void push(T x) = 0;
	virtual T pop() = 0;
	//removes top node from the list and return the value stored there
	T remove_top() {
		if(head != NULL) {
			T value;
			node* temp = new node;
			temp = head;
			head = head->next;
			value = temp->value;
			delete temp;
			return value;
		}
	}
	//adds a node to the end of the list with a value given
	void add_end(T x) {
		node* temp = new node;
		temp->value = x;
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	//adds a node to the start of the list with a value given
	void add_start(T x) {
		node* temp = new node;
		temp->value = x;
		temp->next = head;
		head = temp;
	}
	//checks if the list is empty
	bool check_list() {
		if (head == NULL) {
			return false;
		}
		return true;
	}
};

//child class of SimpleList, this is just for Queue kind of lists. Last in is first out.
template<class T>
class Queue : public SimpleList<T> {
public:
	//constructor
	Queue(string x) {
		this->head = NULL;
		this->tail = NULL;
		this->name = x;
	}
	//inserts node at the end of the list
	void push(T x) {
		this->add_end(x);
	}
	//displays and then deletes node from the front of the list
	T pop() {
		return this->remove_top();
	}
};

//child class of SimpleList, holds just Stack kind of list. First in is first out.
template <class T>
class Stack : public SimpleList<T> {
public:
	//constructor
	Stack(string x) {
		this->head = NULL;
		this->tail = NULL;
		this->name = x;
	}
	//adds node to the front of the list.
	void push(T x) {
		this->add_start(x);
	}
	//displays and then removes node from the front of the list.
	T pop() {
		return this->remove_top();
	}
};

//Class that holds functions that read and print from files.
class file {
	string in, out;
	//list of all the diffrent kind of lists made, both Queues and Stacks.
	list<SimpleList<int>*>listSLi;
	list<SimpleList<double>*>listSLd;
	list<SimpleList<string>*>listSLs;

	//files to read and write to
	ifstream infile;
	ofstream outfile;

public:
	bool check_end() {
		if (infile.eof()) {
			return true;
		}
		return false;
	}
	//Prompt user to say which input and output file
	void getname() {
		cout << "Enter name of input file: ";
		cin >> in;
		cout << "Enter name of output file: ";
		cin >> out;
	}
	//open files
	void open_files() {
		infile.open(in);
		outfile.open(out);
	}
	//constructor
	file() {
		getname();
		open_files();
	}
	//destructor
	~file() {
		infile.close();
		outfile.close();
	}
	//read the commands and then call function accordingly
	void read() {
		string command, name;
		int y = 0;
		infile >> command;
		infile >> name;
		if (name.substr(0, 1) == "i") {
			y = 1;
		}
		else if (name.substr(0, 1) == "d") {
			y = 2;
		}
		else {
			y = 3;
		}
		if (command == "create") {
			create(y, name);
		}
		else if (command == "push") {
			push(y, name);
		}
		else if (command == "pop") {
			pop(y, name);
		}
	}
	//Search function
	template <typename T>
	SimpleList<T>* Search(list<SimpleList<T>*>& vartypeList, string listName) {
		for (typename list<SimpleList<T>*>::iterator it = vartypeList.begin(); it != vartypeList.end(); ++it) {
			if (((*it)->get_name()) == listName) {
				return *it;
			}
		}
		return nullptr;
	}
	//checks if list already exists and then if it doesn't it creates a new list
	void create(int y, string name) {
		string type;
		infile >> type;
		outfile << "PROCESSING COMMAND: create " << name << " " << type << "\n";
		if (y == 1) {
			SimpleList<int>* temp = Search(listSLi, name);
			if (temp!=nullptr) {
				outfile << "ERROR: This name already exists!\n";
			}
			else {
				SimpleList<int>* pSLi;
				if (type == "queue") {
					pSLi = new Queue<int>(name);
				}
				else {
					pSLi = new Stack<int>(name);
				}
				listSLi.push_front(pSLi);
			}
		}
		else if (y == 2) {
			SimpleList<double>* temp = Search(listSLd, name);
			if (temp != nullptr) {
				outfile << "ERROR: This name already exists!\n";
			}
			else {
				SimpleList<double>* pSLd;
				if (type == "queue") {
					pSLd = new Queue<double>(name);
				}
				else {
					pSLd = new Stack<double>(name);
				}
				listSLd.push_front(pSLd);
			}
		}
		else {
			SimpleList<string>* temp = Search(listSLs, name);
			if (temp != nullptr) {
				outfile << "ERROR: This name already exists!\n";
			}
			else {
				SimpleList<string>* pSLs;
				if (type == "queue") {
					pSLs = new Queue<string>(name);
				}
				else {
					pSLs = new Stack<string>(name);
				}
				listSLs.push_front(pSLs);
			}
		}
	}
	//finds the list and the calls list's push to add new node with value
	void push(int y, string name) {
		outfile << "PROCESSING COMMAND: push " << name << " ";
		if (y == 1) {
			int value;
			infile >> value;
			outfile << value << "\n";
			SimpleList<int>* temp= Search(listSLi, name);;
			if (temp == nullptr) {
				outfile << "ERROR: This name does not exist!\n";
			}
			else {
				temp->push(value);
			}
		}
		else if (y == 2) {
			double value;
			infile >> value;
			outfile << value << "\n";
			SimpleList<double>* temp = Search(listSLd, name);;
			if (temp == nullptr) {
				outfile << "ERROR: This name does not exist!\n";
			}
			else {
				temp->push(value);
			}
		}
		else if (y == 3) {
			string value;
			infile >> value;
			outfile << value << "\n";
			SimpleList<string>* temp = Search(listSLs, name);
			if (temp == nullptr) {
				outfile << "ERROR: This name does not exist!\n";
			}
			else {
				temp->push(value);
			}
		}
	}
	//finds list and then calls list's pop to remove node
	void pop(int y, string name) {
		outfile << "PROCESSING COMMAND: pop " << name << "\n";
		if (y == 1) {
			SimpleList<int>* temp = Search(listSLi, name);
			if (temp == nullptr) {
				outfile << "ERROR: This name does not exist!\n";
			}
			else {
				if (temp->check_list()) {
					outfile << "Value popped: " << temp->pop() << "\n";					
				}
				else {
					outfile << "ERROR: This list is empty!\n";
				}
			}
		}
		else if (y == 2) {
			SimpleList<double>* temp = Search(listSLd, name);
			if (temp==nullptr) {
				outfile << "ERROR: This name does not exist!\n";
			}
			else {
				if (temp->check_list()) {
					outfile << "Value popped: " << temp->pop() << "\n";
				}
				else {
					outfile << "ERROR: This list is empty!\n";
				}
			}
		}
		else if (y == 3) {
			SimpleList<string>* temp = Search(listSLs, name);;
			if (temp==nullptr) {
				outfile << "ERROR: This name does not exist!\n";
			}
			else {
				if (temp->check_list()) {
					outfile << "Value popped: " << temp->pop() << "\n";
				}
				else {
					outfile << "ERROR: This list is empty!\n";
				}
			}
		}
	}
};

int main() {
	file first;
	//reads until end of the file
	while (!first.check_end()) {
		first.read();
	}
	return 1;
}