#include "Gradelist.h"

GradeList::GradeList() :Phead(NULL) {};
GradeList::~GradeList() {
	delete Phead;
}
void GradeList::setHead() {
	Phead = new GradeNode;
}

GradeNode* GradeList::getHead()const {
	return Phead;
}