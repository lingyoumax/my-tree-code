#include<iostream>
#include<queue>
#include<string>
#include<stack>
#include<cmath>
using namespace std;
template<typename T>
struct node {
	T data;//树的节点上的值
	node<T> * left = nullptr;//左节点指针
	node<T> * right = nullptr;//右节点指针
	node()=default;
	~node<T>() {}
};
template<typename T>
struct tree {
	node<T> * root = nullptr;//树的根节点指针
	tree()=defualt;
	void tree_show(){//打印树
		node<T> * ptr = this->root;
		queue<node<T> *> q[2];
		int i = 0;
		q[i].push(this->root);
		while (!q[i].empty()) {
			while (!q[i].empty()) {
				node<T> *ptr = q[i].front();
				q[i].pop();
				if (ptr->left != nullptr) {
					cout << ptr->left->data;
					q[!i].push(ptr->left);
				}
				else {
					cout << "*";
				}
				cout << "||";
				cout << ptr->data;
				cout << "||";
				if (ptr->right != nullptr) {
					cout << ptr->right->data;
					q[!i].push(ptr->right);
				}
				else {
					cout << "*";
				}
				cout << "   ";
			}
			cout << endl;
			i = !i;
		}
	}
	void tree_insert(T data) {//节点的插入
		node<T>* ptr = new node<T>;
		ptr->data = data;
		if (this->root == nullptr) {
			this->root = ptr;
		}
		else {
			node<T> * pt = this->root;
			while (true) {
				if (pt->data > data) {
					if (pt->left == nullptr) {
						pt->left = ptr;
						break;
					}
					else {
						pt = pt->left;
					}
				}
				else {
					if (pt->data == data) {
						return;
					}
					if (pt->right == nullptr) {
						pt->right = ptr;
						break;
					}
					else {
						pt = pt->right;
					}
				}
			}
		}
	}
	void tree_preorder(){//节点的前序遍历
		stack<node<T> *> p;
		p.push(this->root);
		while (!p.empty()) {
			node<T> * ptr = p.top();
			p.pop();
			cout << ptr->data << " ";
			if (ptr->right != nullptr) {
				p.push(ptr->right);
			}
			if (ptr->left != nullptr) {
				p.push(ptr->left);
			}
		}
		cout << endl;
	}
	void tree_inorder(){//节点的中序遍历
		stack<node<T> *> p;
		p.push(this->root);
		node<T> * ptr = this->root->left;
		while ((ptr != nullptr) || (!p.empty())) {
			if (ptr != nullptr) {
				p.push(ptr);
				ptr = ptr->left;
			}
			else {
				ptr = p.top();
				p.pop();
				cout << ptr->data << " ";
				ptr = ptr->right;
			}
		}
		cout << endl;
	}
	void tree_postorder1(){//节点的后序遍历1
		stack<node<T> *> p[2];
		p[0].push(this->root);
		while (!p[0].empty()) {
			node<T> * ptr = p[0].top();
			p[0].pop();
			p[1].push(ptr);
			if (ptr->left != nullptr) {
				p[0].push(ptr->left);
			}
			if (ptr->right != nullptr) {
				p[0].push(ptr->right);
			}
		}
		while (!p[1].empty()) {
			cout << (p[1].top())->data << " ";
			p[1].pop();
		}
		cout << endl;
	}
	void tree_postorder2(){//节点的后序遍历2
		stack <node<T> *> p1;
		stack<bool> p2;
		node<T> * ptr = this->root;
		p1.push(ptr);
		p2.push(0);
		while (!p1.empty()) {
			if (p2.top() == 0) {
				ptr = (p1.top())->left;
				if (ptr == nullptr) {
					p2.pop();
					p2.push(1);
				}
				else {
					p1.push(ptr);
					p2.push(0);
				}
			}
			else {
				ptr = (p1.top())->right;
				if (ptr == nullptr) {
					while ((!p2.empty()) && (p2.top() == 1)) {
						cout << (p1.top())->data << " ";
						p1.pop();
						p2.pop();
					}
					if (!p2.empty()) {
						p2.pop();
						p2.push(1);
					}
				}
				else {
					p1.push(ptr);
					p2.push(0);
				}
			}
		}
		cout << endl;
	}
	void tree_postorder3() {//节点的后序遍历3
		stack<node<T> *> s1;
		node<T> * ptr = this->root;
		while (ptr != nullptr) {
			s1.push(ptr);
			ptr = ptr->left;
		}
		node<T> * pt = nullptr;
		while (!s1.empty()) {
			if (((s1.top())->right == pt) || (((s1.top())->left == pt) && ((s1.top())->right == nullptr))) {
				pt = (s1.top());
				cout << pt->data << " ";
				s1.pop();
			}
			else {
				node<T> * p = (s1.top())->right;
				while (p != nullptr) {
					s1.push(p);
					p = p->left;
				}
				pt = nullptr;
			}
		}
	}
	void tree_levelorder(){//节点的层次遍历
		node<T> * ptr = this->root;
		queue<node<T> *> q;
		q.push(this->root);
		while (!q.empty()) {
			node<T> * ptr = q.front();
			q.pop();
			cout << ptr->data << " ";
			if (ptr->left != nullptr) {
				q.push(ptr->left);
			}
			if (ptr->right != nullptr) {
				q.push(ptr->right);
			}
		}
		cout << endl;
	}
	bool tree_delete(T data){//按值删除节点
		node<T> *ptr = this->root;
		if (ptr->data == data) {
			if (ptr->left != nullptr) {
				node<T> * pt = ptr->left;
				while (pt->right != nullptr) {
					pt = pt->right;
				}
				pt->right = ptr->right;
				this->root = ptr->left;
				ptr->~node();
			}
			else {
				if (ptr->right != nullptr) {
					this->root = ptr->right;
					ptr->~node();
				}
				else {
					this->root = nullptr;
					ptr->~node();
				}
			}
		}
		else {
			node<T> * pt;
			int cs;
			if (ptr->data > data) {
				pt = ptr->left;
			}
			else {
				pt = ptr->right;
			}
			if (pt == nullptr) {
				return false;
			}
			while (pt->data != data) {
				ptr = pt;
				if (ptr->data > data) {
					pt = ptr->left;
					cs = 0;
				}
				else {
					pt = ptr->right;
					cs = 1;
				}
				if (pt == nullptr) {
					return false;
				}
			}
			if (pt->left != nullptr) {
				node<T> * pr = pt->left;
				while (pr->right != nullptr) {
					pr = pr->right;
				}
				pr->right = pt->right;
				if (!cs) {
					ptr->left = pt->left;
				}
				else {
					ptr->right = pt->left;
				}
			}
			else {
				if (!cs) {
					ptr->left = pt->right;
				}
				else {
					ptr->right = pt->right;
				}
			}
			pt->~node();
		}
	}
	int tree_level(){//返回树的高度
		if (this->root == nullptr) {
			return 0;
		}
		int i = 0;
		int cs = 0;
		queue<node<T> *> q[2];
		q[cs].push(this->root);
		while (!q[cs].empty()) {
			i++;
			while (!q[cs].empty()) {
				if ((q[cs].front())->left != nullptr) {
					q[!cs].push((q[cs].front())->left);
				}
				if ((q[cs].front())->right != nullptr) {
					q[!cs].push((q[cs].front())->right);
				}
				q[cs].pop();
			}
			cs = !cs;
		}
		return i;
	}
	int tree_level(node<T> * ptr) {//返回该节点的高度
		if (ptr == nullptr) {
			return 0;
		}
		int i = 0;
		int cs = 0;
		queue<node<T> *> q[2];
		q[cs].push(ptr);
		while (!q[cs].empty()) {
			i++;
			while (!q[cs].empty()) {
				if ((q[cs].front())->left != nullptr) {
					q[!cs].push((q[cs].front())->left);
				}
				if ((q[cs].front())->right != nullptr) {
					q[!cs].push((q[cs].front())->right);
				}
				q[cs].pop();
			}
			cs = !cs;
		}
		return i;
	}
};
