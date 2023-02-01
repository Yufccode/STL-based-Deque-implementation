#pragma once


/*ϣ����ʦ������֮ǰ���Կ�һ�´�����ĵ� -- README.md -- лл��*/
/*�����Ѱ���Ҫ��ʵ������Ŀ�����й��ܣ��������������ĵ�*/


#include<cassert>
#include<string.h>
#include<algorithm>
#include<functional>
#include<initializer_list>
#include<iostream>
using namespace std;
template<class T>
class MyVector {
public:
	typedef T* iterator;//���Ҫ�ųɹ��У���Ȼ������������ʲ��� -- ���������������ָ������
	typedef const T* const_iterator;
	//vector�ĵ���������ԭ��ָ��
	iterator begin() {
		return _start;
	}
	iterator end() {
		return _finish;
	}
	//������ṩconst������ -- �������const��vector�Ǳ������˵ģ���ΪȨ�޲��ܷŴ�
	const_iterator begin()const { //���ܷ�����ͨ��������Ҫ����const������
		return _start;
	}
	const_iterator end()const {
		return _finish;
	}
	MyVector() :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}
	~MyVector() {
		delete[] _start;
		_start = _finish = _end_of_storage = nullptr;
	}
	//�ó�ʼ���б��ʼ��
	MyVector(const initializer_list<T>& list)
	{
		//��n��ֵȥ����
		reserve(list.size());
		for (const auto& e : list)
		{
			push_back(e);
		}
	}
	//stl��vector��֧��ʹ�õ���������ȥ����
	//Ҫ֧�������������ĵ����������乹��
	template<class InputIterator>
	MyVector(InputIterator first, InputIterator last)
		:_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
	{
		while (first != last) {
			//����ֱ��push_back()��ֱ��push_back()����� -- ��Ϊû�г�ʼ�� -- Ұָ��
			push_back(*first);
			++first;
		}
	}

	//debug��¼��
	//�����int n����д��size_t ���д��uint���ͣ���(10,5)�����Ĺ����ʱ��
	//���������10����int���ͣ��Ӷ�����������첻��ƥ�� -- ����ȥ�ߵ���������Ĺ��� -- ��ɱ���
	//��������һ��Ҫд��int
	MyVector(int n, const T& val = T())
		:_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
	{
		//��n��ֵȥ����
		reserve(n);
		for (size_t i = 0; i < n; i++) {
			push_back(val);
		}
	}
	//�ִ�д���������� -- ���õ��������乹�캯��
	void swap(MyVector<T>& v) {
		std::swap(_start, v._start);
		std::swap(_finish, v._finish);
		std::swap(_end_of_storage, v._end_of_storage);
	}
#if 1
	MyVector(const MyVector<T>& v)
		:_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
	{
		MyVector<T>tmp(v.begin(), v.end());
		swap(tmp);//��Ȼ�Զ��������Լ�д��swap����Ч -- �����Լ�ʵ��һ��
	}
#endif
	MyVector<T>& operator=(MyVector<T> v) { //v1=v2
		//v��v2�Ŀ����������Ǿֲ��ģ�swap��֮�����v1��v�����Զ���������Ϊ�Ǿֲ�����
		swap(v);
		return *this;
	}
	size_t capacity()const {
		return _end_of_storage - _start;
	}
	size_t size()const {
		return _finish - _start;
	}
	void reserve(size_t n) {
		if (n > capacity()) {
			T* tmp = new T[n];
			size_t sz = size();
			if (_start) {
				//memcpy(tmp, _start, sizeof(T) * sz);//����size()���ֽڹ�ȥ���ȷŵ�tmp����
				//ͬ�������
				//vector<�Զ�������>������
				for (size_t i = 0; i < sz; i++) {
					tmp[i] = _start[i];//��T���Զ�������ʱ������T���͵�operator=
				}
				delete[] _start;
			}
			_start = tmp;
			//_finish = _start + size();//���ﲻҪ�ֳ�ȥ��size()
			//��Ϊsize()����start�������ģ�������һ��start�Ѿ�����
			//������ǰ��������ñ���һ��size��
			_finish = _start + sz;
			_end_of_storage = _start + n;
		}
	}
	void resize(size_t n, const T& val = T()) {
		//1.����+��ʼ��
		//2.��ʼ��
		//3.ɾ������
		if (n > capacity()) {
			reserve(n);
		}
		if (n > size()) {
			//��ʼ����ֵ
			while (_finish < _start+n) {
				*_finish = val;
				++_finish;
			}
		}
		else {
			_finish = _start + n;
		}
	}
	T& operator[](size_t pos) {
		assert(pos < size());
		return _start[pos];
	}
	const T& operator[](size_t pos) const {
		assert(pos < size());
		return _start[pos];
	}
	void push_back(const T& x) {
		//����const��֤��ʲô���Ͷ��У���Ϊ��ʽ����ת����ʱ�������г���
		if (_finish == _end_of_storage) {
			reserve(capacity() == 0 ? 4 : capacity() * 2);
		}
		*_finish = x;
		++_finish;
	}
	void pop_back() {
		assert(_finish > _start);//Ϊ���ǲ���ɾ��
		--_finish;
	}
	void insert(iterator pos, const T& x) {
		assert(pos >= _start);
		assert(pos <= _finish);
		if (_finish == _end_of_storage) {//����
			//��סpos��start�����λ��
			size_t len = pos - _start;
			reserve(capacity() == 0 ? 4 : capacity() * 2);
			pos = _start + len;//����pos��λ�� -- ���������ʧЧ
		}
		//Ų������
		iterator end = _finish - 1;
		while (end >= pos) { // insertҪ���ݵ�ʱ�����ѭ����ʧЧ�ˣ�ͣ�������ˣ�Ϊʲô��
			*(end + 1) = *end;
			end--;
		}
		//����֮�󣬾ɿռ�����ݿ������¿ռ�
		//�ɿռ��Ѿ����ͷ��� -- pos��ָ��ɿռ��һ�����ֵ�λ�õ�
		//pos����Ұָ�룡 -- ������ʧЧ
		//��������Ҫ��pos����һ��
		// -- �޸����ڲ���pos֮����ʵ���⻹û�и����Ľ��
		*pos = x;
		++_finish;
	}
	iterator erase(iterator pos) {
		assert(pos >= _start);
		assert(pos < _finish);
		//Ų������ɾ��
		iterator begin = pos + 1;
		while (begin < _finish) {
			*(begin - 1) = *begin;
			++begin;
		}
		--_finish;
		//ɾ����λ�õ���һ��λ�� -- ����pos
		return pos;
	}
	T& front() {
		assert(size() > 0);
		return *_start;
	}
	T& back() {
		assert(size() > 0);
		return *(_finish - 1);
	}
private:
	iterator _start;//start�൱����������Ŀ�ʼλ��
	iterator _finish;//[_start,_finish)
	iterator _end_of_storage;
};


/* ---------------------- ��֤MyVector��һЩ���Ժ�������װListQueue�������������ݣ�---------------------- */
#if 0
void PrintVector(MyVector<int>& v) {//��û��д���������ʱ������һ��Ҫ���õģ���Ȼǳ�������ͷ����λ������
	MyVector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void PrintVector(const MyVector<int>& v) {
	MyVector<int>::const_iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
void test_vector1() {
	//����β��
	MyVector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	for (int i = 0; i < v.size(); i++) {
		++v[i];
		cout << v[i] << " ";
	}
	cout << endl;
}
void test_vector2() {
	//���Ե�����
	MyVector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	MyVector<int>::iterator it = v.begin();
	while (it != v.end()) {
		(*it)--;
		cout << *it << " ";
		it++;
	}
	cout << endl;

	for (auto& e : v) {
		e++;
		cout << e << " ";
	}
	cout << endl;

	it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;

	PrintVector(v);
}
void test_vector3() {
	//����const������
	const MyVector<int>v;
#if 0 //�Ĳ��˵�
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
#endif
	PrintVector(v);
}
//������ʧЧ����
void test_vector4() {
	MyVector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	//v.push_back(5); // ���Ƿ���  -- ԭ��4�����ݣ�insert֮��Ҫ���ݵ�ʱ�򣬾ͳ��������ˣ�
	//v.push_back(6);
	MyVector<int>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
	cout << endl;
	//
	auto p = find(v.begin(), v.end(), 3);
	if (p != v.end()) {
		v.insert(p, 30);

		//���ڲ��������������ʧЧ֮����ʵ���⻹��û�и��������
		//��Ϊ�ڲ���pos���²���Ӱ��p
		//����������ʹ�õ�ʱ��
		//��pλ�ò��������Ժ󣬲�Ҫ����p����Ϊp����ʧЧ��
		//��Ϊ����ʹ��STL��ʱ�򣬲��˽�ײ�����ݻ��ƣ������Ժ�����insert֮�󣬲�Ҫȥ����pλ�ã� -- ���ܻ�������

		//���ܷ��insert��һ�������ĳ�&���� -- ������Ҫ������ -- �ͿⱣ��һ�º�
		//��Ȼ���ǿ��ƽ�������� -- ���Ǹ��˿��ܻ������������� -- ���磬ͷ�壬�����봫v.begin();v.insert(v.begin(), 0);
		//�಻������Ϊ���Ͳ�ƥ��
#if 0
		cout << *p << endl;
		v.insert(p, 40);
#endif
	}
	PrintVector(v);
}
//erase��������ʧЧ��
//�������erase��ʧЧ�� -- ��֪��
//STL��û�й涨ʲô����
//��û��һ�ֿ��ܣ���size()<capacity()/2��ʱ����һ���ݣ����ݣ���ʱ�任�ռ䣩
//���������Ǹ�����ʣ����Ǹ�p�����ˣ�
void test_vector5() {
	MyVector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	auto p = find(v.begin(), v.end(), 3);
	if (p != v.end()) {
		v.erase(p);
	}
	PrintVector(v);
}
void test_vector6() {
	MyVector<int>v;
#if 0
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
#endif
	//���1��2
	//���Ƿ��ִ�ʱ�����5 -- ����������û�� -- ����
#if 1
	//���3
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
#endif
	//Ҫ��ɾ�����е�ż��
	auto it = v.begin();
	//���3��ʱ��it������end()��ֱ�Ӽ��������� -- ����
	//������������㷨�ǲ���ȷ�ģ�
	//��ʵ���ǿ�Դ������Է��� -- erase���з���ֵ�� -- �����һ�µ�����
	//STL�涨erase����ɾ��λ����һ��λ�õĵ�������
	//vs����������ǲ�ĺ��ϸ�� -- erase֮������ȥ���ʣ� -- ���ʾͱ���
	//Linux�¾Ͳ�ͬ
	while (it != v.end()) {
		if (*it % 2 == 0) {
			it = v.erase(it);//����Ҫ����һ��it����
		}
		else {
			++it;
		}
	}
	PrintVector(v);
}
//�ܽ�
//��ʵ������ʧЧ���������Լ���OJ��ʱ��Ҳ�����ģ��������ɾ��֮�󣬵�����ָ����������ָ��ĵط�
//��ʹ��vector�ĵ�������ʱ��Ҫ����ԣ�

void test_vector7() {
	//ϵͳĬ�ϵĿ���
	//1.�Զ������� -- ���������� -- Ĭ�����ɵ� -- ǳ����
	//2.�������� -- ֵ���� -- ǳ����
	MyVector<int>arr;
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(3);
	for (auto i : arr) {
		cout << i << " ";
	}
	cout << endl;
	MyVector<int>arr2 = arr;
	//����ϵͳĬ�ϵĻ�����ǳ��������������϶�������� -- ����������
	//���������ǳ��������һ�ߵ�ֵ��һ��Ҳ�ᱻ�ı�
	arr2[0] = 100; //���߶��ᱻ�ı�� -- ����������Ҫ�����
	for (auto i : arr) {
		cout << i << " ";
	}
	cout << endl;
	for (auto i : arr2) {
		cout << i << " ";
	}
}
void test_vector8() {
	string s("hell");
	MyVector<int>vs(s.begin(), s.end());
	for (auto i : vs) {
		cout << i << " ";
	}
	cout << endl;
	//��ֵ
	MyVector<int>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	vs = v;//Ҫʵ��һ�����
	//��Ȼ�����f11 -- �������Ƚ�ȥ�����ģ���Ϊ����Ҫ����
	//���꿽���ͽ�ȥ��ֵ��
	for (auto i : vs) {
		cout << i << " ";
	}
}
//��ʵ��������Ҳ�й���
void test_type() {
	int i = 0;
	int j = int();
	int k = int(10);
}
void test_vector9() {
	MyVector<int>v(10, 1);//�����ͱ�����,�������������������int
	//������������ƥ�����⣬��ƥ�䵽����ȥ�ĵط�ȥ��
	//Ϊʲô -- ��Ϊ���������乹���Ǹ����������ʺ��������� -- ���Խ�������ȥ��
	//�����
	//1.���ε�ʱ��д(10u,1)��ʾ����Ǹ�usigned int����
	//2.��vector(size_t n,const T&val=T())�����size_t�ĳ�int��Ҳ���Խ�� -- ����stl�ٷ�������size_t
	//3.����һ�ݣ��ĳ�int��Ū�����ؾ��� -- stl_3.0�����������
	for (auto i : v) {
		cout << i << " ";
	}
	cout << endl;
}
void test_vector10() {
	MyVector<int>v;
	v.resize(10, 1);
	for (auto e : v) {
		cout << e << " ";
	}
	cout << endl;

	MyVector<int>v1;
	v1.reserve(10);
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.resize(8, 8);
	for (auto e : v1) {
		cout << e << " ";
	}
	cout << endl;

	v1.resize(20, 20);
	for (auto e : v1) {
		cout << e << " ";
	}
	cout << endl;

	v1.resize(3);
	for (auto e : v1) {
		cout << e << " ";
	}
	cout << endl;
}
#endif