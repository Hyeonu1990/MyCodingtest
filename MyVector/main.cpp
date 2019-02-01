#include "MyVector.h"
#include <iostream>
using namespace std;

void main()
{
	// MyVector(int capacity) ������ Ȯ��
	MyVector myvec(10); 
	for (int i = 0; i < 10; i++)
	{
		// Add �Լ� Ȯ��
		myvec.Add(i%3); 
	}

	//MyVector(const MyVector & other) ������ Ȯ��
	MyVector newvec(myvec);
	//MyVector newvec(10);
	//newvec = myvec; // MyVector::operator=(const MyVector & other) Ȯ��
	newvec.FindById(0)->_id = 12; // FindById �Լ� Ȯ��
	cout << "newvec : " + newvec.ToString() << endl; // ToString �Լ� Ȯ��

	int* groupvec_size = new int;
	// GroupById �� TrimToSize �Լ� Ȯ��
	MyVector* groupvec = myvec.GroupById(groupvec_size); 
	cout << "groupvec_size : " + to_string(*groupvec_size) << endl;
	cout << "groupvec : " + groupvec->ToString() << endl;

	// RemoveAll �Լ� Ȯ��
	myvec.RemoveAll(0); 
	cout << "myvec : " + myvec.ToString() << endl;

	cout << "end~" << endl;
}