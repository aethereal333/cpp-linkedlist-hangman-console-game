#include "Linkedlist.h"
//NODE
Node::Node(char val = '-') { 
	value = val; 
	next = NULL; 
}						
Node::~Node() { 
	delete next; 
	next = NULL; 
	free(next); 
}
void Node::set_value(char val) { 
	value = val; 
}							
char Node::get_value() { 
	return value; 
}
void Node::set_next_node(Node* nxt) { 
	next = nxt; 
}									
Node* Node::get_next_node() { 
	return next; 
}
void Node::print() { 
	cout << value << " "; 
}
//LINKEDLIST
LinkedList::LinkedList() {
	Node* firstNode = new Node();												
	firstNode->set_next_node(NULL); 
	head = firstNode;															
	tail = firstNode; 
	current = firstNode;														
	size = 0;
}
LinkedList::~LinkedList() {
	Node* next;
	while (head != NULL) { 
		next = head->get_next_node(); 
		delete head; 
		head = next;
	}
}
Node* LinkedList::getCurrentNode()const {
	return current; 
}						
char LinkedList::get_current_node()const { 
	return current->get_value(); 
}
char LinkedList::get_tail_node()const { 
	return tail->get_value(); 
}				
int LinkedList::length()const { 
	return size; 
}
void LinkedList::add_value(char val) {
	Node* newNode = new Node(val);
	newNode->set_next_node(NULL);
	tail->set_next_node(newNode);
	tail = newNode;
	size++;
}
void LinkedList::reset() {
	Node* firstNode = new Node();
	firstNode->set_next_node(NULL);
	head = firstNode; 
	tail = firstNode; 
	current = firstNode;
	size = 0;
}
void LinkedList::next_node() {
	if (current->get_next_node() != NULL) { 
		current = current->get_next_node(); 
	}
}
void LinkedList::del() {
	Node* oldCurrent;
	oldCurrent = current;
	current = head;
	if (size == 1) { reset(); }
	else {
		for (int i = 0; i < size - 1; i++) {
			next_node();
		}
		current->set_next_node(NULL);
		tail = current;
		size--;
	}
	current = oldCurrent;
}
void LinkedList::edit_value(char val, int idx) {
	Node* oldCurrent;
	oldCurrent = current;
	current = head;
	for (int i = 0; i < size; i++) {
		next_node();
		if (i == idx) { 
			current->set_value(val); 
		}
	}
	current = oldCurrent;
}
void LinkedList::print() {
	Node* oldCurrent;
	oldCurrent = current;
	current = head;
	for (int i = 0; i < size; i++) {
		next_node();
		getCurrentNode()->print();
	}
	current = oldCurrent;
}
bool LinkedList::check_guess() {
	Node* oldCurrent;
	oldCurrent = current;
	current = head;
	for (int i = 0; i < size; i++) {
		next_node();
		if (current->get_value() == '_') {
			current = oldCurrent;
			return true;
		}
	}
	current = oldCurrent;
	return false;
}
bool LinkedList::check_guested_word(char word) {
	Node* oldCurrent;
	oldCurrent = current;
	current = head;
	for (int i = 0; i < size; i++) {
		next_node();
		if (current->get_value() == word) {
			current = oldCurrent;
			return true;
		}
	}
	current = oldCurrent;
	return false;
}