#include <iostream>
#include <string>
#include <list>
using namespace std;

class PeopleInfo
{
private:
	string name;
	string phone_number;

public:
	PeopleInfo()
	{
		name = "";
		phone_number = "";
	}
	PeopleInfo(string input_name, string input_num)
	{
		name = input_name;
		phone_number = input_num;
	}

	bool operator< (PeopleInfo& other) const
	{
		return name.c_str()[0] < other.getName().c_str()[0];
	}

	bool operator== (PeopleInfo& other) const
	{
		return (name == other.getName() && phone_number == other.getPhoneNumber());
	}

	void setName(string input_name)
	{
		name = input_name;
	}
	string getName() { return name; }

	void setPhoneNumber(string input_num)
	{
		phone_number = input_num;
	}
	string getPhoneNumber() { return phone_number; }
	
};

template <typename T>
class Node 
{
private:
	T data;
public:
	
	Node* next;
	Node* prev;

	Node(T DATA)
	{
		data = DATA;
		next = NULL;
		prev = NULL;
	}

	T getData() { return data; }
	void setData(T DATA) { data = DATA; }
};

template <typename T>
class MyLinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;
	
public:
	Node<T>* getHead() { return head; }
	Node<T>* getTail() { return tail; }

	int length;

	MyLinkedList() { init(); }
	~MyLinkedList() { clear(); }

	void init()
	{
		head = NULL;
		tail = NULL;
		length = 0;
	}

	void Insert_Front(T data)
	{
		Node<T>* newNode = new Node<T>(data);

		if (head == NULL)
		{
			head = newNode;
			tail = head;
		}
		else
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;			
		}
		length++;
	}

	void Insert_Back(T data)
	{
		Node<T>* newNode = new Node<T>(data);

		if (head == NULL)
		{
			head = newNode;
			tail = head;
		}
		else
		{
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		length++;
	}

	Node<T>* get(int index) {
		if (index == 0) {
			return this->head;
		}
		else if (index == length - 1) {
			return this->tail;
		}
		else if (index < 0 || index >= length) {
			return NULL;
		}
		if (index < length / 2) {
			Node<T>* temp = this->head;
			int i = 0;
			while (temp) {
				if (i == index) { return temp; }
				i++;
				temp = temp->next;
			}
		}
		else {
			Node<T>* temp = this->tail;
			int i = length - 1;
			while (temp) {
				if (i == index) { return temp; }
				i--;
				temp = temp->prev;
			}
		}
		return NULL;
	}

	void deleteNode(int index)
	{
		Node<T>* node = get(index);
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
	}

	void clear()
	{
		while (this->head) {
			Node<T>* next = this->head->next;
			delete this->head;
			length = length - 1;
			this->head = next;
		}
	}

	void selectionSort(bool IsAscending)
	{
		for (int i = 0; i < length; i++)
		{
			int tmp = i;
			for (int j = i; j < length; j++)
			{
				if (IsAscending)
				{
					if (get(tmp)->getData().getName().c_str()[0] >= get(j)->getData().getName().c_str()[0]) tmp = j;
				}
				else
				{
					if (get(tmp)->getData().getName().c_str()[0] <= get(j)->getData().getName().c_str()[0]) tmp = j;
				}
			}
			PeopleInfo temp = get(i)->getData();
			get(i)->setData(get(tmp)->getData());
			get(tmp)->setData(temp);
		}
	}
};

void createNewAddress(MyLinkedList<PeopleInfo>* lists);
void showAllAddress(MyLinkedList<PeopleInfo>* lists);
void deleteAddress(MyLinkedList<PeopleInfo>* lists);
void sortAddress(MyLinkedList<PeopleInfo>* lists);

void main()
{
	MyLinkedList<PeopleInfo> address;
	address.Insert_Back(PeopleInfo("excalibur", "01020121219"));
	address.Insert_Back(PeopleInfo("mag", "01020130913"));
	address.Insert_Back(PeopleInfo("volt", "01020150324"));
	address.Insert_Back(PeopleInfo("loki", "01020140611"));
	address.Insert_Back(PeopleInfo("ash", "01020150707"));

	while (1)
	{
		printf("---------------------------\n");
		printf("--  1. 신규 연락처 등록  --\n");
		printf("--  2. 전체 연락처 목록  --\n");
		printf("--  3. 기존 연락처 삭제  --\n");
		printf("--  4. 연락처 정렬       --\n");
		printf("--  5. 종료              --\n");
		printf("---------------------------\n");
		printf("입력>");
		int input;		
		cin >> input;
		printf("input : %d\n", input);
		switch (input)
		{
			case 1:
				createNewAddress(&address);
				break;

			case 2:
				showAllAddress(&address);
				break;

			case 3:
				deleteAddress(&address);
				break;

			case 4:
				sortAddress(&address);
				break;

			case 5:
				printf("Bye");
				return;
				break;

			default:
				//system("cls");
				printf("유효한 숫자를 입력하세요.\n");
				break;
		}
	}
}

void createNewAddress(MyLinkedList<PeopleInfo>* lists)
{
	//system("cls");
	cin.ignore();
	printf("\n");
	char input[12];
	printf("이름 입력(최대 10자)>");
	cin.getline(input, 11);
	if (cin.fail())
	{
		printf("입력 제한 초과\n");
		cin.clear();
		cin.ignore();
		return;
	}
	string newName(input);	
	printf("전화번호 입력(최대 11자)>");
	cin.getline(input, 12);
	if (cin.fail())
	{
		printf("입력 제한 초과\n");
		cin.clear();
		cin.ignore();
		return;
	}
	string newPhonenum(input);
	lists->Insert_Back(PeopleInfo(newName, newPhonenum));
	printf("등록 완료!\n");
}

void showAllAddress(MyLinkedList<PeopleInfo>* lists)
{
	printf("  Name  |  PhoneNumber  \n");
	if (lists->length == 0)
	{
		printf("표시할 목록 없음\n");
		return;
	}

	for (Node<PeopleInfo>* node = lists->getHead() ; node != NULL; )
	{
		printf("  %s  |  %s  \n", node->getData().getName().c_str(), node->getData().getPhoneNumber().c_str());
		node = node->next;
	}
	printf("\n");

}

void deleteAddress(MyLinkedList<PeopleInfo>* lists)
{
	Node<PeopleInfo>* node = lists->getHead();
	printf("Id  |  Name  |  PhoneNumber  \n");
	for (int i = 0; i < lists->length; i++)
	{
		printf("%d  |  %s  |  %s  \n", i+1, node->getData().getName().c_str(), node->getData().getPhoneNumber().c_str());
		node = node->next;
	}
	printf("삭제할 번호 입력(0은 뒤로가기)>");
	int input;
	cin.ignore();
	cin >> input;

	if (input == 0) return;
	
	lists->deleteNode(input - 1);

	printf("삭제 완료!\n");
}

void sortAddress(MyLinkedList<PeopleInfo>* lists)
{
	printf("---------------------------\n");
	printf("--  1. 이름 오름차순     --\n");
	printf("--  2. 이름 내림차순     --\n");
	printf("---------------------------\n");

	int input;
	cin.ignore();
	cin >> input;

	switch (input)
	{
		case 1:
			lists->selectionSort(true);
			printf("정렬 성공\n");
			break;

		case 2:
			lists->selectionSort(false);
			printf("정렬 성공\n");
			break;

		default:
			printf("잘못된 숫자입니다. 이전 화면으로 돌아갑니다.\n");
			return;
	}
}