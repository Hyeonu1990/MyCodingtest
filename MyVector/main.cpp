#include "MyVector.h"
#include <iostream>
using namespace std;

void main()
{
	// MyVector(int capacity) 생성자 확인
	MyVector myvec(10); 
	for (int i = 0; i < 10; i++)
	{
		// Add 함수 확인
		myvec.Add(i%3); 
	}

	//MyVector(const MyVector & other) 생성자 확인
	MyVector newvec(myvec);
	//MyVector newvec(10);
	//newvec = myvec; // MyVector::operator=(const MyVector & other) 확인
	newvec.FindById(0)->_id = 12; // FindById 함수 확인
	cout << "newvec : " + newvec.ToString() << endl; // ToString 함수 확인

	int* groupvec_size = new int;
	// GroupById 및 TrimToSize 함수 확인
	MyVector* groupvec = myvec.GroupById(groupvec_size); 
	cout << "groupvec_size : " + to_string(*groupvec_size) << endl;
	cout << "groupvec : " + groupvec->ToString() << endl;

	// RemoveAll 함수 확인
	myvec.RemoveAll(0); 
	cout << "myvec : " + myvec.ToString() << endl;

	cout << "end~" << endl;
}