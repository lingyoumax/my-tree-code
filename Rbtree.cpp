#include<iostream>
#include<queue>
#include<stack>
#include<cmath>
struct RBnode {
	T data;//树的节点上的值
	RBnode<T> * last = nullptr;//上节点指针
	RBnode<T> * left = nullptr;//左节点指针
	RBnode<T> * right = nullptr;//右节点指针
	bool color = 0;//节点颜色 0:黑,1:红
	~RBnode(){}
	RBnode() = default;
};
template <typename T>
struct RBtree {
	RBnode<T> * root = nullptr;//根节点
	RBtree() = default;
	RBnode<T> * RBtree_find(T data) {//返回指向特定值的指针
		RBnode<T> * ptr = this->root;
		while (ptr != nullptr) {
			if (ptr->data == data) {
				return ptr;
			}
			else {
				if (ptr->data < data) {
					ptr = ptr->right;
				}
				else {
					ptr = ptr->left;
				}
			}
		}
		return nullptr;
	}
	void RBtree_show() {//打印树
		RBnode<T> * ptr = this->root;
		queue<RBnode<T> *> q[2];
		int i = 0;
		q[i].push(this->root);
		while (!q[i].empty()) {
			while (!q[i].empty()) {
				RBnode<T> *ptr = q[i].front();
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
	void RBtree_insert(T data) {//RB树中插入指定值的节点
		RBnode<T> * ptr = new RBnode<T>;
		ptr->data = data;
		RBnode<T> * pt = this->root;
		if (pt == nullptr) {
			this->root = ptr;
			ptr->color = 0;
			return;
		}
		else {
			while (true) {
				if (pt->data == data) {
					return;
				}
				else {
					if (pt->data < data) {
						if (pt->right != nullptr) {
							pt = pt->right;
						}
						else {
							pt->right = ptr;
							ptr->color = 1;
							ptr->last = pt;
							break;
						}
					}
					else {
						if (pt->left != nullptr) {
							pt = pt->left;
						}
						else {
							pt->left = ptr;
							ptr->last = pt;
							ptr->color = 1;
							break;
						}
					}
				}
			}
			this->RBtree_insert_adjust(ptr);
		}
	}
	void RBtree_insert_adjust(RBnode<T> * ptr) {//红黑树中插入节点后对该节点进行双红调整
		if ((ptr->last==nullptr)||!((ptr->last)->color)) {
			return;
		}
		else {
			RBnode<T> * father = ptr->last;
			RBnode<T> * grandfather = father->last;
			if (grandfather->left == father) {
				if ((grandfather->right == nullptr) || !(grandfather->right->color)) {
					if (father->left == ptr) {
						if (this->root == grandfather) {
							this->root = father;
						}
						if (father->right != nullptr) {
							father->right->last = grandfather;
						}
						grandfather->left = father->right;
						father->last = grandfather->last;
						if (grandfather->last != nullptr) {
							if (grandfather->last->left == grandfather) {
								grandfather->last->left = father;
							}
							else {
								grandfather->last->right = father;
							}
						}
						father->right = grandfather;
						grandfather->last = father;
						father->left = ptr;
						ptr->last = father;
					}
					else {
						if (this->root == grandfather) {
							this->root = ptr;
						}
						if (ptr->left != nullptr) {
							ptr->left->last = father;
						}
						father->right = ptr->left;
						if (ptr->right != nullptr) {
							ptr->right->last = grandfather;
						}
						grandfather->left = ptr->right;
						ptr->last = grandfather->last;
						if (grandfather->last != nullptr) {
							if (grandfather->last->left == grandfather) {
								grandfather->last->left = ptr;
							}
							else {
								grandfather->last->right = ptr;
							}
						}
						ptr->left = father;
						father->last = ptr;
						ptr->right = grandfather;
						grandfather->last = ptr;
					}
				}
				else {
					RBnode<T> * uncle = nullptr;
					if (grandfather->right == father) {
						uncle = grandfather->last;
					}
					else {
						uncle = grandfather->right;
					}
					father->color = 0;
					uncle->color = 0;
					if (grandfather->last != nullptr) {
						grandfather->color = 1;
						this->RBtree_insert_adjust(grandfather);
					}
				}
			}
			else {
				if ((grandfather->left == nullptr) || !(grandfather->left->color)) {
					if (father->right == ptr) {
						if (this->root == grandfather) {
							this->root = father;
						}
						if (father->left!= nullptr) {
							father->left->last = grandfather;
						}
						grandfather->right = father->left;
						father->last = grandfather->last;
						if (grandfather->last != nullptr) {
							if (grandfather->last->right == grandfather) {
								grandfather->last->right = father;
							}
							else {
								grandfather->last->left = father;
							}
						}
						father->left = grandfather;
						grandfather->last = father;
						father->right = ptr;
						ptr->last = father;
					}
					else {
						if (this->root == grandfather) {
							this->root = ptr;
						}
						if (ptr->right != nullptr) {
							ptr->right->last = father;
						}
						father->left = ptr->right;
						if (ptr->left != nullptr) {
							ptr->left->last = grandfather;
						}
						grandfather->right = ptr->left;
						ptr->last = grandfather->last;
						if (grandfather->last != nullptr) {
							if (grandfather->last->right == grandfather) {
								grandfather->last->right = ptr;
							}
							else {
								grandfather->last->left = ptr;
							}
						}
						ptr->right = father;
						father->last = ptr;
						ptr->left = grandfather;
						grandfather->last = ptr;
					}
				}
				else {
					RBnode<T> * uncle = nullptr;
					if (grandfather->right == father) {
						uncle = grandfather->last;
					}
					else {
						uncle = grandfather->right;
					}
					father->color = 0;
					uncle->color = 0;
					if (grandfather->last != nullptr) {
						grandfather->color = 1;
						this->RBtree_insert_adjust(grandfather);
					}
				}
			}
		}
	}
	void RBtree_preorder() {//节点的前序遍历
		stack<RBnode<T> *> p;
		p.push(this->root);
		while (!p.empty()) {
			RBnode<T> * ptr = p.top();
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
	void RBtree_inorder() {//节点的中序遍历
		stack<RBnode<T> *> p;
		p.push(this->root);
		RBnode<T> * ptr = this->root->left;
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
	void RBtree_postorder1() {//节点的后序遍历1
		stack<RBnode<T> *> p[2];
		p[0].push(this->root);
		while (!p[0].empty()) {
			RBnode<T> * ptr = p[0].top();
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
	void RBtree_postorder2() {//节点的后序遍历2
		stack <RBnode<T> *> p1;
		stack<bool> p2;
		RBnode<T> * ptr = this->root;
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
	void RBtree_postorder3() {//节点的后序遍历3
		stack<RBnode<T> *> s1;
		RBnode<T> * ptr = this->root;
		while (ptr != nullptr) {
			s1.push(ptr);
			ptr = ptr->left;
		}
		RBnode<T> * pt = nullptr;
		while (!s1.empty()) {
			if (((s1.top())->right == pt) || (((s1.top())->left == pt) && ((s1.top())->right == nullptr))) {
				pt = (s1.top());
				cout << pt->data << " ";
				s1.pop();
			}
			else {
				RBnode<T> * p = (s1.top())->right;
				while (p != nullptr) {
					s1.push(p);
					p = p->left;
				}
				pt = nullptr;
			}
		}
	}
	int RBtree_height() {//返回树的高度
		if (this->root == nullptr) {
			return 0;
		}
		int i = 0;
		int cs = 0;
		queue<RBnode<T> *> q[2];
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
	int RBtree_height(RBnode<T> * ptr) {//返回该节点的高度
		if (ptr == nullptr) {
			return 0;
		}
		int i = 0;
		int cs = 0;
		queue<RBnode<T> *> q[2];
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
	int RBtree_blackheight(RBnode<T> * ptr) {//从一个节点开始计算黑高度
		int i = 0;
		ptr = ptr->left;
		while (ptr != nullptr) {
			if (!ptr->color) {
				i++;
			}
			ptr = ptr->left;
		}
		return (i + 1);
	}
	int RBtree_blackheight() {//返回整棵树的黑高度
		return this->RBtree_balckheight(this->root);
	}
	void RBtree_delete(RBnode<T> * ptr) {//红黑树中删除指定节点
		if (ptr != nullptr) {
			if ((ptr->left != nullptr) && (ptr->right != nullptr)) {
				RBnode<T> * pt = ptr->left;
				while (pt->right != nullptr) {
					pt = pt->right;
				}
				T dt = ptr->data;
				ptr->data = pt->data;
				pt->data = dt;
				this->RBtree_delete(pt);
			}
			else {
				if ((ptr->left == nullptr) && (ptr->right == nullptr)) {
					if (ptr->color) {
						if (ptr->last->left == ptr) {
							ptr->last->left = nullptr;
						}
						else {
							ptr->last->right = nullptr;
						}
						ptr->~RBnode();
					}
					else {
						if (this->root == ptr) {
							this->root = nullptr;
							ptr->~RBnode();
						}
						else {
							RBnode<T> * father = ptr->last;
							if (father->left == ptr) {
								father->left = nullptr;
							}
							else {
								father->right = nullptr;
							}
							ptr->~RBnode();
							this->RBtree_delete_adjust(father);
						}
					}
				}
				else {
					if (ptr->left != nullptr) {
						if (ptr->last != nullptr) {
							if (ptr->last->left = ptr) {
								ptr->last->left = ptr->left;
							}
							else {
								ptr->last->right = ptr->left;
							}
						}
						else {
							this->root = ptr->left;
						}
						ptr->left->last = ptr->last;
						ptr->left->color = 0;
						ptr->~RBnode();
					}
					else {
						if (ptr->last != nullptr) {
							if (ptr->last->left = ptr) {
								ptr->last->left = ptr->right;
							}
							else {
								ptr->last->right = ptr->right;
							}
						}
						else {
							this->root = ptr->right;
						}
						ptr->right->last = ptr->last;
						ptr->right->color = 0;
						ptr->~RBnode();
					}
				}
			}
		}
	}
	void RBtree_delete(T data) {//红黑树中删除指定值的节点
		RBnode<T> * ptr = this->RBtree_find(data);
		if (ptr != nullptr) {
			if ((ptr->left != nullptr) && (ptr->right != nullptr)) {
				RBnode<T> * pt = ptr->left;
				while (pt->right != nullptr) {
					pt = pt->right;
				}
				T dt = ptr->data;
				ptr->data = pt->data;
				pt->data = dt;
				this->RBtree_delete(pt);
			}
			else {
				if ((ptr->left == nullptr) && (ptr->right == nullptr)) {
					if (ptr->color) {
						if (ptr->last->left == ptr) {
							ptr->last->left = nullptr;
						}
						else {
							ptr->last->right = nullptr;
						}
						ptr->~RBnode();
					}
					else {
						if (this->root == ptr) {
							this->root = nullptr;
							ptr->~RBnode();
						}
						else {
							RBnode<T> * father = ptr->last;
							if (father->left == ptr) {
								father->left = nullptr;
							}
							else {
								father->right = nullptr;
							}
							ptr->~RBnode();
							this->RBtree_delete_adjust(father);
						}
					}
				}
				else {
					if (ptr->left != nullptr) {
						if (ptr->last != nullptr) {
							if (ptr->last->left = ptr) {
								ptr->last->left = ptr->left;
							}
							else {
								ptr->last->right = ptr->left;
							}
						}
						else {
							this->root = ptr->left;
						}
						ptr->left->last = ptr->last;
						ptr->left->color = 0;
						ptr->~RBnode();
					}
					else {
						if (ptr->last != nullptr) {
							if (ptr->last->left = ptr) {
								ptr->last->left = ptr->right;
							}
							else {
								ptr->last->right = ptr->right;
							}
						}
						else {
							this->root = ptr->right;
						}
						ptr->right->last = ptr->last;
						ptr->right->color = 0;
						ptr->~RBnode();
					}
				}
			}
		}
	}
	void RBtree_delete_adjust(RBnode<T> * ptr) {//对双黑节点的父节点开始进行平衡化操作
		RBnode<T> * child = nullptr;
		if (ptr->right != nullptr) {
			child = ptr->right;
			if (!child->color) {
				RBnode<T> * grandson = nullptr;
				if (child->right != nullptr) {
					grandson = child->right;
					child->color = ptr->color;
					grandson->color = 0;
					ptr->color = 0;
					child->last = ptr->last;
					if (this->root == ptr) {
						this->root = child;
					}
					else {
						if (ptr->last->left == ptr) {
							ptr->last->left = child;
						}
						else {
							ptr->last->right = child;
						}
					}
					child->left = ptr;
					ptr->last = child;
					ptr->right = nullptr;
				}
				else {
					if (child->left != nullptr) {
						grandson = child->left;
						grandson->color = ptr->color;
						ptr->color = 0;
						grandson->last = ptr->last;
						if (this->root == ptr) {
							this->root = ptr;
						}
						else {
							if (ptr->last->left == ptr) {
								ptr->last->left = grandson;
							}
							else {
								ptr->last->right = grandson;
							}
						}
						grandson->left = ptr;
						ptr->right = nullptr;
						ptr->last = grandson;
						grandson->right = child;
						child->left = nullptr;
						child->last = grandson;
					}
					else {
						if ((ptr->last==nullptr)||(ptr->color)) {
							child->color = 1;
							ptr->color = 0;
						}
						else {
							child->color = 1;
							this->RBtree_delete_adjust(ptr->last);
						}
					}
				}
			}
			else {
				RBnode<T> * lgrandson = child->left;
				child->last = ptr->last;
				if (this->root == ptr) {
					this->root = child;
				}
				else {
					if (ptr->last->left == ptr) {
						ptr->last->left = child;
					}
					else {
						ptr->last->right = child;
					}
				}
				ptr->right = lgrandson;
				lgrandson->last = ptr;
				ptr->last = child;
				child->left = ptr;
				ptr->color = 1;
				child->color = 0;
				this->RBtree_delete_adjust(ptr);
			}
		}
		else {
			child = ptr->left;
			if (!child->color) {
				RBnode<T> * grandson = nullptr;
				if (child->left != nullptr) {
					grandson = child->left;
					child->color = ptr->color;
					grandson->color = 0;
					ptr->color = 0;
					child->last = ptr->last;
					if (this->root == ptr) {
						this->root = child;
					}
					else {
						if (ptr->last->left == ptr) {
							ptr->last->left = child;
						}
						else {
							ptr->last->right = child;
						}
					}
					child->right = ptr;
					ptr->last = child;
					ptr->left = nullptr;
				}
				else {
					if (child->right != nullptr) {
						grandson = child->right;
						grandson->color = ptr->color;
						ptr->color = 0;
						grandson->last = ptr->last;
						if (this->root == ptr) {
							this->root = ptr;
						}
						else {
							if (ptr->last->left == ptr) {
								ptr->last->left = grandson;
							}
							else {
								ptr->last->right = grandson;
							}
						}
						grandson->right = ptr;
						ptr->left = nullptr;
						ptr->last = grandson;
						grandson->left = child;
						child->right = nullptr;
						child->last = grandson;
					}
					else {
						if ((ptr->last == nullptr) || (ptr->color)) {
							child->color = 1;
							ptr->color = 0;
						}
						else {
							child->color = 1;
							this->RBtree_delete_adjust(ptr->last);
						}
					}
				}
			}
			else {
				RBnode<T> * rgrandson = child->right;
				child->last = ptr->last;
				if (this->root == ptr) {
					this->root = child;
				}
				else {
					if (ptr->last->left == ptr) {
						ptr->last->left = child;
					}
					else {
						ptr->last->right = child;
					}
				}
				ptr->left = rgrandson;
				rgrandson->last = ptr;
				ptr->last = child;
				child->right = ptr;
				ptr->color = 1;
				child->color = 0;
				this->RBtree_delete_adjust(ptr);
			}
		}
	}
	~RBtree() {};
};
