#pragma once

/*ϣ����ʦ������֮ǰ���Կ�һ�´�����ĵ� -- README.md -- лл��*/
/*�����Ѱ���Ҫ��ʵ������Ŀ�����й��ܣ��������������ĵ�*/

#include<string>
#include<unordered_map>
#include<functional>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Person
{
protected:
	string __id;
	string __name;
public:
	//friend void DisplayPersonInfo(const shared_ptr<Person>& ptr);
	virtual void f() { ; }
public:
	Person(string id = "", string name = "")
		:__id(id), __name(name) {}
	Person(const Person&) = default;
	~Person() = default;
};

class Student :public Person
{
protected:
	string __schoolName;
	double __discountRate;
public:
	//friend void DisplayPersonInfo(const shared_ptr<Person>& ptr);
	friend ostream& operator<<(ostream& out, const Student& stu)
	{
		cout << "------ student info ------ " << endl;
		cout << "id: " << stu.__id << endl;
		cout << "name: " << stu.__name << endl;
		cout << "schoolName: " << stu.__schoolName << endl;
		cout << "discountRate: " << stu.__discountRate << endl;
		cout << "------ student info ------ " << endl;
		return out;
	}
public:
	Student(string id = "", string name = "", string schoolName = "", double discountRate = 0)
		:Person(id, name), __schoolName(schoolName), __discountRate(discountRate) {}
	Student(const Student&) = default;
	~Student() = default;
};