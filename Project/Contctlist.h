#pragma once
#include "Contact.h"

// ��ȣ ����� Linked list�� ������ Class
class ContctList {
private:
	ContactNode* Phead;

public:
	ContctList() :Phead(NULL) {}
	~ContctList() {
		delete Phead;
	}

	ContactNode* getHead()const;
	void setHead();
	bool sort();
};