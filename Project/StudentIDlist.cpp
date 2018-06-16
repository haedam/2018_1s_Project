#include "StudentIDlist.h"
using namespace std;

void StudentIDList::setHead() {
	Phead = new StudentIDNode;
}

StudentIDNode* StudentIDList::getHead()const {
	return Phead;
}

// insertion sort
bool StudentIDList::sort() {
	StudentIDNode* pre = Phead->Pfront;
	if (!pre) {
		return 1;
	}
	StudentIDNode* cur = pre->Pfront;
	StudentIDNode* cmp;
	StudentIDNode* preCmp;
	StudentIDNode* insert;

	while (cur) {
		insert = cur;
		if (cur->Pfront) {
			cur = cur->Pfront;
		}
		cmp = Phead->Pfront;
		preCmp = Phead;
		while (cmp != insert) {
			if (strcmp(cmp->studentid, insert->studentid) > 0) {
				preCmp->Pfront = insert;
				insert->Pfront = cmp;
				break;
			}
			cmp = cmp->Pfront;
			preCmp = preCmp->Pfront;
		}
		if (pre->Pfront != cur)
			pre = pre->Pfront;
	}
	return 0;
}