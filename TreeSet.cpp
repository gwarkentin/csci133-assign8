#include <iostream>

class TreeSet {
	//Node object, could point to some data but I left it out
	//Not certain why the left, right and parent have any need
	//to be private, given that we can get and set all of them
	//with direct functions
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
		//when it matches return that node
		if (n != NULL) {
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
	//counts all children. Needed to keep track of count after removal.
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

	public:
		TreeSet() {
			root = NULL;
			count = 0;
		}	
		//adds new node with given key to tree
		void add(char key) {
			//we don't want upper and lower to be considered different
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
		//deletes node if found, including node's children
		bool remove(char key) {
			key = std::toupper(key);
			Node * n;
			//get the node of given key
			n = findKey(key, root);	
			//if found in tree
			if (n != NULL) { 
				//check if on left or right of parent
				//dereference parent's appropriate pointer
				if (n->getParent()->getLeft() == n) {
					n->getParent()->setLeft(NULL);
				}
				else {
					n->getParent()->setRight(NULL);
				}
				//reduce count by item and children removed
				//rather than recounting entire tree which could be big
				count -= countChildren(n);
				//it was found and deleted
				return true;
			}
			//not found return false
			return false;
		}
		//lose the first node, lose everything
		void clear() {
			root = NULL;
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

	//count added to with .add() function
	std::cout << "Stored Count: " << ts.getCount() << std::endl;

	std::cout << "Tree in order:\n";
	ts.printTree();
	std::cout << std::endl;

	std::cout << "Did we find: " << ts.find('b') << std::endl;
	std::cout << "Max: " << ts.maximum() << std::endl;
	std::cout << "Height: " << ts.getHeight() << std::endl;
	std::cout << "Removed?: " << ts.remove('b') << std::endl;
	
	//just a test to make sure these matched
	std::cout << "Stored Count: " << ts.getCount() << std::endl;
	std::cout << "Count: " << ts.doCount() << std::endl;
	return 0;
}
