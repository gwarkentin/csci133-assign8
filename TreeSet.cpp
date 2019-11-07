#include <iostream>

//binary tree, each node has char key
class TreeSet {
	//Node object, could point to some data but I left it out
	//Not certain why the left, right and parent have any need
	//to be private, given that we are getting and setting
	//all of them essentially directly
	class Node {
		char key;
		Node * left;
		Node * right;
		Node * parent;
		//Data * data;
		public:
			//constructor taking in key
			Node (char k) {
				key = k;
				left = NULL;
				right = NULL;
				parent = NULL;
			}
			//mutator methods for the node variables
			void setParent(Node *pa) {parent = pa;}
			void setLeft(Node *le) {left = le;}
			void setRight(Node *ri){right = ri;}
			//accessor methods for the node variables
			char getKey() {return key;}
			Node * getParent() {return parent;}
			Node * getLeft() {return left;}
			Node * getRight() {return right;}
			/*
			void setData(Data * d) {data = d;}
			Data * getData() {return data;}
			*/
	};

	//pointer to first item
	Node * root;
	//since we have function that calculates this we could do without.
	//slower to calculate if big tree though
	int count;
	
	//recursively finds key given head initially	
	//honestly I just made this off the cuff and am surprised it works
	Node * findKey (char key, Node *n) {
		//in case empty list given
		if (n != NULL) {
			//when it matches return that node
			if (n->getKey() == key) {
				return n;
			}
			//call this function with the left child
			else if (key < n->getKey()) {
				return findKey(key, n->getLeft());
			}
			//call this function with the right child
			else if (key > n->getKey()) {
				return findKey(key, n->getRight());
			}
		}
		return NULL;
	}
	//find leftmost deepest item recursively
	Node * findMinimum(Node * n) {
		//checks to ensure list isn't empty first
		if (n != NULL) {
			//if there's something on the right recursively call function
			if (n->getLeft() != NULL) {
				return findMinimum(n->getLeft());
			}
			//otherwise return this node
			return n;
		}
		//avoid seg fault
		return NULL;
	}
	//find rightmost deepest item recursively
	Node * findMaximum(Node * n) {
		//checks to ensure list isn't empty first
		if (n != NULL) {
			//if there's something on the right recursively call function
			if (n->getRight() != NULL) {
				return findMaximum(n->getRight());
			}
			//otherwise return this node
			return n;
		}
		//avoid seg fault
		return NULL;
	}
	//counts all children and self.
	int countChildren(Node * n) {
		if (n == NULL) {
			return 0;
		}
		else {
			int children = (countChildren(n->getLeft()) + countChildren(n->getRight()));
			return ++children;
		}
	}
	//prints tree in order recursively
	void printInorder(Node * n) {
		if (n == NULL) {
			return;
		}
		//I used my accessor methods rather than the original direct access
		printInorder(n->getLeft());
		std::cout << n->getKey() << " ";
		printInorder (n->getRight());
	}

	//given head(or any node), recursively return deepest branch plus self
	int getMaxDepth(Node * n) {
		if (n == NULL) {
			return 0;
		}
		else {
			int left = getMaxDepth(n->getLeft());
			int right = getMaxDepth(n->getRight());
			if (left > right) {
				//increment before return
				return ++left;
			}
			else {
				//increment before return
				return ++right;
			}
		}
	}

	//create node with given key where it belongs
	//maybe this could be smaller but it works well enough as is
	void addAt(char key, Node *n) {
		//if less than current node, go left
		if (key <= n->getKey()) {
			//if left has no child on that side already
			if (n->getLeft() == NULL) {
				//create the node, point to it from parent and point to parent
				Node * newNode = new Node(key);
				n->setLeft(newNode);
				newNode->setParent(n);
				return;
			}
			//otherwise step into children recursively
			else {
				addAt(key, n->getLeft());
				return;
			}
		}
		//otherwise go right
		else {
			//if right has no child on that side already
			if (n->getRight() == NULL) {
				//create the node, point to it from parent and point to parent
				Node * newNode = new Node(key);
				n->setRight(newNode);
				newNode->setParent(n);
				return;
			}
			//otherwise step into children recursively
			else {
				addAt(key, n->getRight());
				return;
			}
		}
	}
	//swap two items in tree, doesn't necessarily keep tree correct order
	void transfer(Node * a, Node * b) {
		if (a->getParent()->getLeft() == a) {
			a->getParent()->setLeft(b);
		}
		else {
			a->getParent()->setRight(b);
		}
		if (b->getParent()->getLeft() == b) {
			b->getParent()->setLeft(a);
		}
		else {
			b->getParent()->setRight(a);
		}
		Node * tmp;
		tmp = a->getParent();	
		a->setParent(b->getParent());
		b->setParent(tmp);
	}
	public:
		//constructor makes very empty tree
		TreeSet() {
			root = NULL;
			count = 0;
		}	
		//adds new node with given key to tree
		void add(char key) {
			//we don't want upper and lowercase to be considered different
			key = std::toupper(key);
			//if first item, create at root position
			if (root == NULL) {
				Node * newNode = new Node(key);
				root = newNode;
				count++;
			}
			//otherwise step through children starting at root
			else {
				addAt(key, root);
				count++;
			}
		}
		//remove item keeping children rearange tree to still be in order
		//we were literally given the function in class but I wanted to 
		//solve it myself, obviously this is a poorly factored solution
		bool remove(char key) {
			key = std::toupper(key);
			Node * n = NULL;
			Node * tmp = NULL;
			Node * s = NULL;//successor
			//get the node of given key
			n = findKey(key, root);	
			//if item found
			if (n != NULL) {
				//if no left child just move everything up a spot
				if (n->getLeft() == NULL) {
					if (n->getRight() != NULL) {
						tmp = n->getRight();
						tmp->setParent(n->getParent());
					}
					if (n->getParent() == NULL) {
						root = tmp;
					}
					else if(n == n->getParent()->getLeft()) {
						n->getParent()->setLeft(tmp);
					}
					else {
						n->getParent()->setRight(tmp);
					}
				}
				//if no right child just move everything up a spot
				else if (n->getRight() == NULL) {
					if (n->getLeft() != NULL) {
						tmp = n->getLeft();
						tmp->setParent(n->getParent());
					}
					if (n->getParent() == NULL) {
						root = tmp;
					}
					else if(n->getParent()->getRight() == n) {
						n->getParent()->setRight(tmp);
					}
					else {
						n->getParent()->setLeft(tmp);
					}
				}
				//otherwise take rightmost child of left and replace
				//node with that
				else {
					s = findMaximum(n->getLeft());
					if (s->getParent() != n) {
						s->getParent()->setRight(NULL);
						s->setLeft(n->getLeft());
						n->getLeft()->setParent(s);
					}
					s->setParent(n->getParent());
					s->setRight(n->getRight());
					n->getRight()->setParent(s);
					if (n->getParent() == NULL) {
						root = s;
					}
					else if(n->getParent()->getRight() == n) {
						n->getParent()->setRight(s);
					}
					else {
						n->getParent()->setLeft(s);
					}
				}
				//item found and removed
				count--;
				return true;
			}
			//item not found
			return false;
		}
		//lose the first node, lose everything
		void clear() {
			root = NULL;
			count = 0;
		}
		//return true if found, false if not
		bool find(char key) {
			//we don't want upper and lower to be considered different
			key = std::toupper(key);
			Node * n;
			n = findKey(key,root);
			//if found
			if (n == NULL) {
				return false;
			}
			//not found
			else {
				return true;
			}
		}
		//get cound of items
		int getCount() {
			return count;
		}
		//so that user doesn't have to provide root
		int getHeight() {
			return getMaxDepth(root);
		}
		//returns min key, otherwise blank
		char minimum() {
			Node * n;
			n = findMinimum(root);
			if (n != NULL) {
				return n->getKey(); 
			}
			return ' ';
		}
		//returns max key, otherwise blank
		char maximum() {
			Node * n;
			n = findMaximum(root);
			if (n != NULL) {
				return n->getKey(); 
			}
			return ' ';
		}
		//so main doesn't have to provide root
		void printTree() {
			printInorder(root);
		}
		//count from scratch to test
		int doCount() {
			return countChildren(root);
		}

};
int main() {
	//create tree and some children
	TreeSet ts;
	ts.add('r');
	ts.add('f');
	ts.add('b');
	ts.add('x');
	ts.add('a');
	ts.add('t');
	ts.add('z');
	ts.add('g');

	//count added to with .add() function
	std::cout << "Stored Count: " << ts.getCount() << std::endl;

	std::cout << "Tree in order:\n";
	ts.printTree();
	std::cout << std::endl;

	std::cout << "Did we find: " << ts.find('f') << std::endl;
	std::cout << "Max: " << ts.maximum() << std::endl;
	std::cout << "Height: " << ts.getHeight() << std::endl;
	std::cout << "Remove 'f': " << std::boolalpha << ts.remove('f') << std::endl;
	
	//just a test to make sure these matched
	std::cout << "Stored Count: " << ts.getCount() << std::endl;
	std::cout << "Count: " << ts.doCount() << std::endl;
	std::cout << "Tree in order:\n";
	ts.printTree();
	std::cout << std::endl;
	return 0;
}
