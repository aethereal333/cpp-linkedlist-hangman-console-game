#pragma once
#include <iostream>
#include <string>
using namespace std;
class Node {
	Node* next;
	char value;
public:
	Node(char val);									
	~Node();
	void set_value(char value2);					
	char get_value();
	void set_next_node(Node* n);					
	Node* get_next_node();
	void print();
};
class LinkedList {
	Node* head, * tail, * current;
	int size;
public:
	LinkedList();									
	~LinkedList();
	void add_value(char val);					
	void edit_value(char val, int idx);
	void reset();									
	void del();
	void next_node();								
	char get_tail_node()const;
	Node* getCurrentNode()const;					
	char get_current_node()const;
	bool check_guess();								
	bool check_guested_word(char word);
	int length()const;
	void print();
};