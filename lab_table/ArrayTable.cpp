#include "ArrayTable.h"

TKey TArrayTable::GetKey(TDataPos mode) const {
	if (!IsEmpty()) {
		switch (mode) {
		case FIRST_POS:
			return pRecs[0].Key;
		case LAST_POS:
			return pRecs[DataCount - 1].Key;
		default:
			return pRecs[CurrPos].Key;
		}
	}
}

TValue TArrayTable::GetValue(TDataPos mode) const {
	if (!IsEmpty()) {
		switch (mode) {
		case FIRST_POS:
			return pRecs[0].pValue;
		case LAST_POS:
			return pRecs[DataCount - 1].pValue;
		default:
			return pRecs[CurrPos].pValue;
		}
	}
}

int TArrayTable::Reset(void) {
	CurrPos = 0;
	return IsTabEnded();
}

int TArrayTable::IsTabEnded(void) const {
	return CurrPos >= DataCount;
}

int TArrayTable::GoNext(void) {
	if (!IsTabEnded())
		CurrPos++;
	return IsTabEnded();
}

int TArrayTable::SetCurrentPos(int pos) {
	CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
	return IsTabEnded();
}
