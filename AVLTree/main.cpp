//Jackson Oravetz; Ahmed, Kishwar. Code for an insertion into an AVL tree

#include <iostream>
#include <random>
#include <chrono>
#include "AVLTree.h"
using namespace std;

int main() {
	// Single rotate left
	AVLTree b;
	Node* bRoot = new Node(2);
	b.AVLTreeInsert(bRoot, true);
	b.AVLTreeInsert(new Node(1), true);
	b.AVLTreeInsert(new Node(3), true);
	b.AVLTreeInsert(new Node(4), true);
	b.AVLTreeInsert(new Node(5), true);
	cout << bRoot->key << endl;
	cout << bRoot->left->key << " " << bRoot->right->key << endl;
	cout << bRoot->right->left->key << " " << bRoot->right->right->key
		<< endl;
	// Rotate left then right
	AVLTree c;
	Node* cRoot = new Node(4);
	c.AVLTreeInsert(cRoot, true);
	c.AVLTreeInsert(new Node(3), true);
	c.AVLTreeInsert(new Node(5), true);
	c.AVLTreeInsert(new Node(1), true);
	c.AVLTreeInsert(new Node(2), true);
	cout << cRoot->key << endl;
	cout << cRoot->left->key << " " << cRoot->right->key << endl;
	cout << cRoot->left->left->key << " " << cRoot->left->right->key << endl;

	int N = 100;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();	//get a seed from system clock to get random double
	default_random_engine generator(seed);
	uniform_real_distribution<double> distribution(0.0, 1.0);	//get the double between 0 and 1
	for (int i = 0; i < 4; i++) {	//loop for each different N
		int maxAVLHeight = 0;
		int minAVLHeight = 0;
		double avgAVLHeight = 0;
		int maxBSTHeight = 0;
		int minBSTHeight = 0;
		double avgBSTHeight = 0;
		for (int j = 0; j < 10; j++) {	//loop for 10 trials
			AVLTree d;	//create new trees
			AVLTree e;
			for (int k = 0; k < N; k++) {	//loop for every N
				double randNum = distribution(generator);	//get random number
				d.AVLTreeInsert(new Node(randNum), true);	//insert in AVL and BST
				e.insertWithoutRebalance(new Node(randNum));
			}
			if (d.root->height < minAVLHeight || minAVLHeight == 0)	//find min
				minAVLHeight = d.root->height;
			if (d.root->height > maxAVLHeight || maxAVLHeight == 0)	//find max
				maxAVLHeight = d.root->height;
			avgAVLHeight += d.root->height;	//sum for avg
			if (e.root->height < minBSTHeight || minBSTHeight == 0)
				minBSTHeight = e.root->height;
			if (e.root->height > maxBSTHeight || maxBSTHeight == 0)
				maxBSTHeight = e.root->height;
			avgBSTHeight += e.root->height;
			cout << "AVL height: " << d.root->height << endl;
			cout << "BST height: " << e.root->height << endl << endl;
		}

		avgAVLHeight /= 10.0;	//get avgs
		avgBSTHeight /= 10.0;
		cout << "Minimum AVL height: " << minAVLHeight << endl;
		cout << "Maximum AVL height: " << maxAVLHeight << endl;
		cout << "Average AVL height: " << avgAVLHeight << endl << endl;
		cout << "Minimum BST height: " << minBSTHeight << endl;
		cout << "Maximum BST height: " << maxBSTHeight << endl;
		cout << "Average BST height: " << avgBSTHeight << endl << endl;
		N *= 10;	//move on to next magnitude of N
	}
}