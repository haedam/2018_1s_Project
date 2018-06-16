#include "Contctlist.h"

ContactNode* ContctList::getHead()const {
	return Phead;
}

void ContctList::setHead() {
	Phead = new ContactNode;
}

// selection sort
bool ContctList::sort() {
	ContactNode* cur = Phead->Pright;
	ContactNode* pre = Phead;
	if (cur == NULL) {
		return 1;
	}
	ContactNode* cmp;
	ContactNode* preCmp;
	ContactNode* preSelect;
	ContactNode* select;

	while (!cur->Pright) {
		preCmp = cur;
		cmp = cur->Pright;
		preSelect = pre;
		select = cur;
		while (cmp) {
			if (strcmp(cmp->contact, select->contact) > 0) {
				preSelect = preCmp;
				select = cmp;
			}
			preCmp = preCmp->Pright;
			cmp = cmp->Pright;
		}
		if (select != cur) {
			preSelect->Pright = select->Pright;
			pre->Pright = select;
			select->Pright = cur;
			pre = pre->Pright;
		} // relocate select
		else {
			pre = pre->Pright;
			cur = cur->Pright;
		} // move cur and pre
	}
	return 0;
}