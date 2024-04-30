#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <initializer_list>

class Node {
public:
	Node(int value, Node* left, Node* right);
	Node(int value);
	Node();
	Node(const Node& node);
	std::size_t length();

friend std::ostream &operator<<(std::ostream &output, const Node &node);
friend bool operator>(const Node &node, int val);
friend bool operator>(int val, const Node &node);
friend bool operator>=(const Node &node, int val);
friend bool operator>=(int val, const Node &node);
friend bool operator<(const Node &node, int val);
friend bool operator<(int val, const Node &node);
friend bool operator<=(const Node &node, int val);
friend bool operator<=(int val, const Node &node);
friend bool operator==(const Node &node, int val);
friend bool operator==(int val, const Node &node);

	int value;
	Node *left;
	Node *right;
};

class BST : public Node {
public:
	BST();
	BST(BST &bst);
	BST &operator=(BST &bst);
	BST(BST &&bst);
	BST &operator=(BST &&bst);

	BST(std::initializer_list<int> val);

	Node*& get_root();
	void bfs(std::function<void(Node*& node)> func);
	std::size_t length();
	bool add_node(int value);
	Node **find_node(int value);
	Node **find_parrent(int value);
	Node **find_successor(int value);
	bool delete_node(int value);

	friend std::ostream &operator<<(std::ostream &output, BST &bst);

	BST operator++(void);

	BST operator++(int);

	~BST();

private:
	Node *root;
};

#endif //BST_H
