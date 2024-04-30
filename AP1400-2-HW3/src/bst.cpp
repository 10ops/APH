#include "bst.h"

Node::Node(int value, Node* left, Node* right) : value(value), left(left), right(right) { }
Node::Node(int value) : Node(value, nullptr, nullptr) { }

Node::Node() : Node(0, nullptr, nullptr) { }
Node::Node(const Node& node) : value(node.value), left(node.left), right(node.right) { }

std::ostream &operator<<(std::ostream &output, const Node &node) {
	output << &node << " \t=> value:" << node.value << " \tleft:" << node.left << " \tright:" << node.right;
	output << std::endl;
	return output;
}

bool operator>(const Node &node, int val) {
	if (&node == nullptr) { return false;}
	return node.value > val;
}

bool operator>(int val, const Node &node) {
	return node.value < val;
}

bool operator>=(const Node &node, int val) {
	return node.value >= val;
}

bool operator>=(int val, const Node &node) {
	return node.value <= val;
}

bool operator<(const Node &node, int val) {
	if (&node == nullptr) { return false;}
	return node.value < val;
}

bool operator<(int val, const Node &node) {
	return node.value > val;
}

bool operator==(const Node &node, int val) {
	return node.value == val;
}

bool operator==(int val, const Node &node) {
	return node.value == val;
}

bool operator<=(const Node &node, int val) {
	return node.value <= val;
}

bool operator<=(int val, const Node &node) {
	return val <= node.value;
}


// ------------------------------BST----------------------------------

Node *&BST::get_root() {
	Node *&res = root;
	return res;
}

void BST::bfs(std::function<void(Node*& node)> func) {
	// use vector storage the node
	std::vector<Node*> qe;
	if (root == nullptr) {
		return;
	}
	qe.push_back(root);
	while (qe.size() != 0) {
		auto layer_end = qe.end();
		if ((*qe.begin())->left != nullptr) {
			qe.push_back((*qe.begin())->left);
		}
		if ((*qe.begin())->right != nullptr) {
			qe.push_back((*qe.begin())->right);
		}
		func(*qe.begin());
		qe.erase(qe.begin());
	}
}

std::size_t Node::length() {
	if (this == nullptr) {
		return 0;
	}
	else {
		std::size_t leftl = this->left->length();
		std::size_t rightl = this->right->length();
		return leftl + rightl + 1;
	}
}

std::size_t BST::length() {
	return root->length();
}

std::ostream &operator<<(std::ostream &output, BST &bst) {
	output << "*********************************************************************" << std::endl;
	bst.bfs([](BST::Node*& node){ std::cout << *node;});
	output << "binary search tree size: " << bst.length() << std::endl;
	output << "*********************************************************************" << std::endl;
	return output;
}

Node **BST::find_node(int value) {
	Node **res = &root;
	while (*res != nullptr) {
		if (**res > value) {
			res = &((*res)->left);
		}
		else if (**res < value) {
			res = &((*res)->right);
		}
		else {
			return res;
		}
	}
	if (*res == nullptr) {
		res = nullptr;
	}
	return res;
}

Node **BST::find_parrent(int value) {
	if (*root == value) {
		return nullptr;
	}
	Node **parrent = &root; 
	Node **res = (*root > value ? &(root->left) : &(root->right));
	while (*res != nullptr) {
		if (**res > value) {
			parrent = res;
			res = &((*res)->left);
		}
		else if (**res < value) {
			parrent = res;
			res = &((*res)->right);
		}
		else {
			return parrent;
		}
	}
	return res;
}

// predecessor
Node **BST::find_successor(int value) {
	Node **res = find_node(value);
	if (res == nullptr) {
		return res;
	}
	// left node is not null
	res = &((*res)->left);
	while ((*res) != nullptr && (*res)->right != nullptr) {
		res = &((*res)->right);
	}
	return res;
}

bool BST::add_node(int value) {
	if (find_node(value) != nullptr) {
		return false;
	}
	Node *sto = new Node(value, nullptr, nullptr);
	Node **pos = &root;
	if (root == nullptr) {
		root = sto;
		return true;
	}
	Node **itr = (*root > value ? &(root->left) : &(root->right));
	while (*itr != nullptr) {
		if (**itr > value) {
			pos = itr;
			itr = &((*itr)->left);
		}
		else {
			pos = itr;
			itr = &((*itr)->right);
		}
	}
	if (**pos > value) {
		(*pos)->left = sto;
	}
	else {
		(*pos)->right = sto;
	}	
	return true;
}

bool BST::delete_node(int value) {
	if (this->root == nullptr) { return false;}
	Node **find = find_node(value);
	if (find == nullptr || *find == nullptr) { return false;}
	Node **parrent_f = find_parrent(value);
	if (parrent_f == nullptr || *parrent_f == nullptr) {
		if ((*find)->left != nullptr && (*find)->right == nullptr) {
			this->root = (*find)->left;
		}
		else if ((*find)->left == nullptr && (*find)->right != nullptr) {
			this->root = (*find)->right;
		}
		else {
			Node **predecessor = find_successor(value);
			Node **parrent_p = find_parrent((*predecessor)->value);
			(*find)->value = (*predecessor)->value;
			Node **pre_pos = ((*parrent_p)->left == (*predecessor) ? &((*parrent_p)->left) : &((*parrent_p)->right));
			*pre_pos = (*predecessor)->left;
		}
	}
	else {
		Node **find_pos = ((*parrent_f)->left == (*find) ? &((*parrent_f)->left) : &((*parrent_f)->right));
		if ((*find)->right == nullptr) {
			*find_pos = (*find)->left;
		}
		else if ((*find)->left == nullptr && (*find)->right != nullptr) {
			*find_pos	= (*find)->right;
		}
		else {
			Node **predecessor = find_successor(value);
			Node **parrent_p = find_parrent((*predecessor)->value);
			(*find)->value = (*predecessor)->value;
			Node **pre_pos = ((*parrent_p)->left == (*predecessor) ? &((*parrent_p)->left) : &((*parrent_p)->right));
			*pre_pos = (*predecessor)->left;
		}
	}
	return true;
}

BST BST::operator++(int) { // BST++
	BST res = BST(*this);  // move assignment but its copy 
	bfs([](BST::Node*& node){ node->value++;});
	return res;
}


BST BST::operator++(void) { // ++BST
	bfs([](BST::Node*& node){ ++node->value;});
	return BST(*this);
}

// default constructor
BST::BST() : root(nullptr) { }

//copy assignment constructor
BST::BST(BST &bst){ 
	this->root = nullptr;
	
	bst.bfs([this](Node*& node)
	{
		this->add_node(node->value);
	});
}

BST &BST::operator=(BST &bst) {
	if (this == &bst) {
		return *this;
	} 
	this->root = nullptr;
	
	bst.bfs([this](Node*& node)
	{
		add_node(node->value);
	});
	return *this;
}

// move assignment constructor
BST::BST(BST &&bst) : root(bst.root) { 
	bst.root = nullptr;
}

BST &BST::operator=(BST &&bst) {
	if (this == &bst) {
		return *this;
	}
	this->root = bst.root;
	bst.root = nullptr;
	return *this;
}

// use brace to initialize a BST class
BST::BST(std::initializer_list<int> val) {
	this->root = nullptr;
	std::for_each(val.begin(), val.end(), [this](const int &value){add_node(value);});
}

BST::~BST() {
	std::vector<Node*> nodes;
	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
	for(auto& node: nodes) {
		delete node;
	}
}

















