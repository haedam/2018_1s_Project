#pragma once
#include <string>
#include "Contact.h"
#include "Department.h"
#include "Grade.h"
#include "Name.h"
#include "StudentID.h"

// �̸� ����� Linked list�� ������ Class
class NameList {
private:
	NameNode* Phead;

public:
	NameList() :Phead(NULL) {}
	~NameList() {
		delete Phead;
	}
	void setHead(GradeNode* gradeHead, StudentIDNode* IDHead, ContactNode* contctHead);
	NameNode* insert(char name[], int grade, char studentid[], char contact[]);
	bool pop(char name[]);
	bool sort();
	bool get(char name[]);
	bool printID(StudentIDNode* iD);
	bool printContct(ContactNode* contact);
};