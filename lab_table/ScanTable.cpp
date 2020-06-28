#include "ScanTable.h"

bool TScanTable::FindRecord(TKey k) {
	int i;
	for (i = 0; i < DataCount; i++)
		if (pRecs[i].Key == k)
			break;
	Efficiency += i + 1;
	if (i < DataCount) {
		CurrPos = i;
		return true;
	}
	return false;
}

int TScanTable::InsRecord(TKey k, TValue pVal) {
	if (IsFull()) {
		return TabFull;
	}
	else {
		if (FindRecord(k))
		{
			return TabRecDbl;
		}
		else {
			pRecs[DataCount].Key = k;
			pRecs[DataCount].pValue = pVal;
			DataCount++;
			Efficiency++;
			return TabOK;
		}
	}
}

int TScanTable::DelRecord(TKey k) {
	int temp = FindRecord(k);
	if (temp == 0) {
		return temp;
	}
	else {
		pRecs[CurrPos] = pRecs[DataCount - 1];
		DataCount--;
		return TabOK;
	}
}
