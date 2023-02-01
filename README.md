
C++��װ������漰��ģ�� -- ��֧��ֱ�ӷ��ļ�(.h��.cpp)
	����������Ͷ������ -- ��Ҫ�ںܶ�ط�����typename�ȹؼ��ֲ�����������
	����ᱨ�����Ӵ���
��˱��δ���ҵ�����ۿ���2�������Ͷ������.h�ļ���ʵ��
���ۿ���1��ʵ����������Ͷ��������

���Խ������result.txt�У���test.cpp�����Ѿ�����˵�һ�ʣ��ڶ��ʣ������ʵĲ��Խ��

## ListQueue��ʵ��
�ڲ��ṹ��
	Mylist<MyVector<Type>> __inner_list;
	size_t __nodes_count = 0;
	size_t __size = 0;

### ֧�ֵĹ���:���������й��ܶ���result.txt�еĲ��Խ�������֣�
#### ��ĿҪ��Ĺ���:
	β�塢βɾ��ͷ�塢ͷɾ������λ�õ�ɾ���Ĳ��롢[]���ء��Լ���ӡ�ڲ���Ϣprint�ӿ�
#### ����ʵ�ֵĹ��ܣ�
	1. ͨ��ʵ�� __list_queue_iterator ��
		֧��stl����������Ϊ������const��������
		֧�ֵ���������
		֧�ַ�Χfor����
		����stl�㷨�в����������find,find_if��
			���÷�ʽ��stl����������÷�ʽһ�£��磺
			auto it = find(lq.begin(),lq.end(),3);
	2. �ṩclear(),size()������stl����Ҳ�еĽӿ�
	3. ֧��ListQueue<T>::sort()
	4. ֧�ֳ�ʼ���б����͵Ĺ��죬�磺
		ListQueue<int>lq = {1,2,3,4,5};
	5. ֧�ֵ���������Ĺ��죬�磺
		std::set<int>s = {1,2,3};
		ListQueue<int>lq(s.begin(),s.end());

### �ڲ��ṹ�Ĺ��ܣ�
	MyVector��Mylist
	��ģ��stl::vector,stl::list�Ĺ���ʵ��
	����MyVector��˳���ʵ�֣�list����˫������ʵ��
#### MyVector
	1. ֧��stl::vector�д󲿷ֺ��Ĺ��ܣ����˻�����push_back/pop_back/erase/insert
		��֧��resize,reverse,swap,capacity,size�ȹ���
	2. ֧����stlһ���Ķ��ֹ��췽ʽ���������������乹�죬��ʼ���б����
	3. ֧�ֵ�����������const����������Ϊ -- ֧�ֵĹ��ܺ�ListQueueһ��
#### Mylist
	1. ֧��stl::list�д󲿷ֺ��Ĺ��ܣ����˻�����push_back/pop_back/push_front/pop_front/erase/insert
		**Ϊ��ListQueue�ķ�װ�������ף��һ������[]���أ��Ա㱣֤�ϲ��װ����ļ��**
	2. ֧����stlһ���Ķ��ֹ��췽ʽ���������������乹�죬��ʼ���б����
	3. ͨ��ʵ�� __list__iterator ��
		֧�ֵ�������Ϊ������const�������� -- ֧�ֵĹ��ܺ�ListQueueһ��
	4. ͨ��ʵ��	reverse_iterator.h ֧�ַ�����������ܣ��ù���ͬ����������MyVector�ϣ�

### �ڲ��ṹ��ʵ��ϸ��
	MyVector��Mylist ������stl�ķ�ʽ��������һ���̶��ϵļ�ʵ�� -- �����stl��vector��list���Ѿ�ʵ���˴󲿷ֺ��Ĺ���
#### ListQueueʵ��ϸ��
	ListQueue����ṹ������ĿҪ�����ʵ�� -- ������std::deque
#### ListQueue�ṹ���ڲ��Ĺ���
	push_back -- ֱ����˫���������һ���ڵ��vector����
		������vector���� -- ���½ڵ�
	pop_back -- ɾ��˫���������һ���ڵ��vector�����һ��Ԫ��
		���ɾ��֮�󣬸�vector���� -- ����pop_back()һ�£�ɾ���ýڵ�
	insert -- ͨ������Ԫ�ظ����ķ�ʽ -- �ҵ�Ҫ�����λ����������һ��vector��
		�����ʱ���vector���� -- �ȰѶ��������ȥ����ʱ����vector�Ĵ�С�����涨����һ����λ
		1. ��ʱ������ýڵ����һ�ڵ��ϵ�vector��δ�� -- �ѵ�ǰ��������vector�����һ��Ԫ��insert����һ���ڵ��vector��ͷ����ͷ��
		2. ��ʱ������ýڵ����һ�ڵ��vector�Ѿ����� -- ����Mylist��insert���ڵ�ǰ�ڵ�ĺ������һ���µĽڵ�
			Ȼ��ѳ�������vector������ǰ�ڵ��vector�������һ��Ԫ�ز��뵽�½ڵ����vector��
	push_front -- ����insert
	erase -- ͨ������Ԫ�ظ����ķ�ʽ -- �ҵ�Ҫɾ����Ԫ����������һ��vector��
		ͨ������λ�õķ�ʽ -- �ҵ����Ԫ����vector�е�λ�� -- ֱ�ӵ���MyVector��eraseɾ������
		���ɾ��֮��vector���� -- ����Mylist��eraseɾ���ýڵ㼴��
	[]���� -- ����posλ�õ�Ԫ�������ĸ�vector -- ��ͨ������λ�ü��ɵõ����
#### ��������ʵ��ϸ��
	����������clear -- clearֱ�ӵ���Mylist��clear���� -- ���õ���vector���ͷţ�����ֱ�ӵ���Ĭ����������
		�Զ������͵�Ĭ������ -- ������Լ�����������
		�������ýṹ��ʱ���� Mylist<MyVector<Type>> __inner_list;
		������ Mylist<MyVector<Type>*> __inner_list;
		��˲�������ڴ�й©
	sort -- �Ȱ�Ԫ�ؿ�����һ��std::vector�ϣ��ź����ٿ�����ȥ