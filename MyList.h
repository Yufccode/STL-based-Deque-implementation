#pragma once


/*ϣ����ʦ������֮ǰ���Կ�һ�´�����ĵ� -- README.md -- лл��*/
/*�����Ѱ���Ҫ��ʵ������Ŀ�����й��ܣ��������������ĵ�*/


#include<iostream>
#include<algorithm>
#include<cassert>
//#include<list>
#include"reverse_iterator.h" //������������� -- ���Թ�vector��listͬʱ��

using namespace std;

template<class T>
struct list_node {
	T _data;
	list_node<T>* _next;
	list_node<T>* _prev;
	list_node(const T& x = T()) //��ȱʡ
		:_data(x), _next(nullptr), _prev(nullptr)
	{}
};

/* ----------------------------------- ����������Ĺ��� ----------------------------------- */
template<class T, class Ref, class Ptr>
struct __list__iterator {
	typedef list_node<T>Node;
	//��׼��stl������Ҫ������͵�
	//����������漸���ò���algorithm��find
	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef ptrdiff_t difference_type;

	Node* _node;
	__list__iterator(Node* node)//����
		:_node(node) {}
	//���Ŀ�����Ϊ
	bool operator!=(const __list__iterator& it)const {
		return _node != it._node;
	}
	//������Ƿ��� const T& ���ǾͲ��ܸ���
	//�Ե����������� -- ע�⣬Ҫ�������� -- �ɶ���д
	Ref operator*() { // ͬ�������ͻ�
		return _node->_data;
	}
	__list__iterator& operator++() {
		_node = _node->_next;
		return *this;
	}
	//����һ��+��-
	__list__iterator operator+(size_t n)
	{
		__list__iterator tmp(*this);
		while (n--)
		{
			tmp._node = tmp._node->_next;
		}
		return tmp;
	}
	__list__iterator operator-(size_t n)
	{
		__list__iterator tmp(*this);
		while (n--)
		{
			tmp._node = tmp._node->_prev;
		}
		return tmp;
	}
	bool operator==(const __list__iterator& it)const {
		return _node == it._node;
	}
	__list__iterator operator++(int) {
		__list__iterator tmp(*this);//�ȱ���һ��֮ǰ��ֵ
		_node = _node->_next;
		return tmp;//ֻ�ܴ�ֵ������ -- ��Ϊ����ʱ����
	}
	__list__iterator operator--(int) {
		__list__iterator tmp(*this);//�ȱ���һ��֮ǰ��ֵ
		_node = _node->_prev;
		return tmp;//ֻ�ܴ�ֵ������ -- ��Ϊ����ʱ����
	}
	__list__iterator& operator--() {
		_node = _node->_prev;
		return *this;
	}
	//stl���滹������һ�� -> �Ͼ�����������[ָ����Ϊ]��һ����������
	//ʲôʱ����� -> �أ� ���������ǽṹ��(���ʱ��)����Ҫ��
	//T* operator->() {
	Ptr operator->() { //���ͻ� -- �㴫ʲô���;͵���ʲô����
		//���ز��� -- ��Ϊ����ֵ��ͬ����������
		return &(operator*());
	}
};





/* ----------------------------------- ����Ĺ��� ----------------------------------- */
template<class T>
class Mylist {
	typedef list_node<T>Node;
public:
	typedef __list__iterator<T, T&, T*>iterator;
	typedef __list__iterator<T, const T&, const T*>const_iterator;
	typedef __reverse_iterator<iterator, T&, T*>reverse_iterator;
	typedef __reverse_iterator<const_iterator, const T&, const T*>const_reverse_iterator;
	/* -------------------------------------- �������Ķ��� -------------------------------------- */
	iterator begin() {
		return iterator(_head->_next);//begin()���ڱ�λ����һ��λ��
	}
	iterator end() {
		return iterator(_head);//end()���ڱ�λ
	}
	reverse_iterator rbegin() {
		return reverse_iterator(end());//��Ϊǰ��������Ƶ��ǶԳƵģ���������������ҵķ�����ķ������ҵ���
	}
	reverse_iterator rend() {
		return reverse_iterator(begin());
	}
	const_iterator begin() const {
		return const_iterator(_head->_next);//begin()���ڱ�λ����һ��λ��
	}
	const_iterator end() const {
		return const_iterator(_head);//end()���ڱ�λ
	}
	/* -------------------------------------- �������Ķ��� -------------------------------------- */
	Mylist() {
		empty_init();
	}
	~Mylist() {
		//�������д������ -- ��ǳ���� -- �ͻ�϶��������
		//��clearһ�£��ٰ�ͷŪ��������
		this->clear();
		delete _head;
		_head = nullptr;
		__size = 0;
	}
	//��ʼ�������� -- �������Ը���������͹��캯���Ĵ��븴�� -- ���ٴ�����ظ�
	void empty_init() {
		//��������ʼ���ڱ�λͷ�ڵ�
		_head = new Node;
		_head->_next = _head;
		_head->_prev = _head;
		__size = 0;
	}//����д��֮�����ǵĹ���Ҳֱ�ӵ������empty_init()������
	//��������
	//����д�� -- ���ù��캯�� -- ������캯���Ǵ�һ������������ģ���һ��Ҫ��list�ĵ�������
	template<class InputIterator>
	Mylist(InputIterator first, InputIterator last) { //����
		empty_init();//��������ʼ���ڱ�λͷ�ڵ� -- һ��Ҫ�ȳ�ʼ��ͷ�ڵ�
		while (first != last) { //��Ȼ���ǲ���ֱ�Ӳ��� -- ͷ�ڵ�Ҫ��Ū�� -- ��Ȼֱ��pushֱ�ӱ�
			push_back(*first);
			++first;
		}
	}
	void swap(Mylist<T>& x) {
		std::swap(_head, x._head);
		std::swap(__size, x.__size);
	}
	//��������
	Mylist(const Mylist<T>& lt) {
		//ֱ�Ӹ���list(InputIterator first, InputIterator last)���캯������
		//lt2(lt1)
		empty_init();//�Ȱ��Լ���ʼ��һ��
		Mylist<T>tmp(lt.begin(), lt.end());//�������������lt2��Ҫ��
		swap(tmp);
	}
	//�����ֵ����
	Mylist<T>& operator=(Mylist<T> lt) {
		//lt��һ�������ʱ���󣬻����� -- �������ͷ�
		swap(lt);
		return*this;
	}
	void clear() {
		//������ -- �ڱ�λ��Ҫ������
		iterator it = begin();
		while (it != end()) {
			it = erase(it);
			//erase֮�� -- ��ʧЧ�� -- ���ǻ᷵����һ��λ�õĵ�����
			//����it = erase(it) ����д������
		}
		__size = 0;
	}
	//β��
	void push_back(const T& x) {
		//����insert
		insert(end(), x);
	}
	//ͷ��
	void push_front(const T& x) {
		insert(begin(), x);
	}
	//ͨ������������
	iterator insert(iterator pos,const T&x){
		__size++;
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* newnode = new Node(x);

		//prev newnode cur
		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = cur;
		cur->_prev = newnode;

		return iterator(newnode);
	}
	//βɾ
	void pop_back() {
		erase(--end());
	}
	//ͷɾ
	void pop_front() {
		erase(begin());
	}
	//ͨ��������ɾ��
	iterator erase(iterator pos) {
		assert(pos != end());
		__size--;
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* next = cur->_next;

		prev->_next = next;
		next->_prev = prev;
		delete cur;
		return iterator(next);//������һ��λ�õĵ�����
	}
	size_t size()
	{
		return __size;
	}
public:
	T& operator[](size_t pos) //pos���±�
	{
		//��stl�Ļ����ϣ����һ��[]���أ��Ա�ListQueue��װ�ı��
		assert(pos >= 0 && pos < __size);
		Node* cur = _head;
		for (size_t i = 0; i <= pos; i++)
		{
			//��һ�������±�0�������������±�1����pos+1�������±�pos
			cur = cur->_next;
		}
		return cur->_data;
	}
private:
	Node* _head;
	size_t __size = 0;
};

/* ---------------------- ��֤Mylist��һЩ���Ժ�������װListQueue�������������ݣ�---------------------- */
#if 0
void print_list(Mylist<int>&lt) {
	for (auto e : lt) {
		cout << e << " ";
	}
	cout << endl;
}
void test() {
	Mylist<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);

	lt.push_front(0);
	lt.push_front(-1);

	Mylist<int>::iterator it = lt.begin();
	while (it != lt.end()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;
	for (auto e : lt) {//��Ӧ�ģ���Ҳ������
		cout << e << " ";
	}
	cout << endl;
	lt.pop_back();
	lt.pop_back();
	for (auto e : lt) {//��Ӧ�ģ���Ҳ������
		cout << e << " ";
	}
	cout << endl;
	lt.pop_front();
	lt.pop_front();
	for (auto e : lt) {//��Ӧ�ģ���Ҳ������
		cout << e << " ";
	}
	cout << endl;

	//find
	//��3֮ǰ����һ��30,��3��һ��100
	auto pos = find(lt.begin(), lt.end(), 3);
	if (pos != lt.end()) {
		//pos��ʧЧ�𣿲���
		lt.insert(pos, 30);
		*pos *= 100; // ������ָ�����3
	}
	for (auto e : lt) {
		cout << e << " ";
	}
	cout << endl;
}

void func(const Mylist<int>& lt) {
	//������ȥ����һ��
	//�϶����ܲ��˵� -- ��Ҫconst������
	Mylist<int>::const_iterator it = lt.begin();
	while (it != lt.end()) {
		//*it = 10;
		cout << *it << " ";
		++it;
	}
}
void test2() {
	Mylist<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	func(lt);
}

void test3() {
	//��ǳ��������
	Mylist<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	Mylist<int>copy = lt;
	*lt.begin() = 10;
	print_list(lt);
	cout << endl;
	print_list(copy);
	//�����ǳ�����Ļ����������� -- ����list��ͷ��ָ��ͬһ���ڱ�λͷ�ڵ� -- ͬһ������
	lt.clear();
	cout << endl;
	print_list(lt);
	lt.push_back(1);
	print_list(lt);
}
void test4() {
	Mylist<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	Mylist<int>copy;
	copy = lt;
	print_list(lt);
	print_list(copy);
	*lt.begin() = 10;
	print_list(lt);
	print_list(copy);
}

//�������������
void test5() {
	Mylist<int>lt;
	lt.push_back(1);
	lt.push_back(2);
	lt.push_back(3);
	lt.push_back(4);
	lt.push_back(5);
	lt.push_back(6);
	lt.push_back(7);
	lt.push_back(8);
	print_list(lt);
	//�������������
	Mylist<int>::reverse_iterator rit = lt.rbegin();
	while (rit != lt.rend()) {
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}
#endif