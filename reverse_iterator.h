#pragma once



/*ϣ����ʦ������֮ǰ���Կ�һ�´�����ĵ� -- README.md -- лл��*/
/*�����Ѱ���Ҫ��ʵ������Ŀ�����й��ܣ��������������ĵ�*/



//���ã�������������
template<class Iterator, class Ref, class Ptr>
struct __reverse_iterator {
	Iterator _cur;
	typedef __reverse_iterator<Iterator, Ref, Ptr> RIterator;
	__reverse_iterator(Iterator it)
		:_cur(it) {}
	//Ϊ�˶Գƣ�stlԴ�������һЩ����
	RIterator operator++() { //������++�����صĻ��ǵ�����
		--_cur;//���������++�����Ƿ�װ�����������--
		return *this;
	}
	RIterator operator--() {
		++_cur;//���������++�����Ƿ�װ�����������--
		return *this;
	}
	Ref operator*() {
		//return *_cur;
		//Ϊʲô������Ҫ����һ�¶����أ�
		//��Ϊ������ֻ��ȡһ�����ݣ�������λ�ÿ϶��ǲ��ܱ�� -- ���˿϶���������
		auto tmp = _cur;
		--tmp;
		return *tmp;
	}
	Ptr operator->() {
		return &(operator*());
	}
	bool operator!=(const RIterator& it) {
		return _cur != it._cur;
	}
};