#pragma once
#include "Grade.h"

// �г� ����� Linked list�� ������ Class
class GradeList {
private:
	GradeNode* Phead;

public:
	GradeList();
	~GradeList();
	void setHead();
	GradeNode* getHead()const;
};