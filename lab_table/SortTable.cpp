#include "SortTable.h"

TSortTable& TSortTable::operator=(const TScanTable& tab)
{
	if (pRecs != NULL)
	{
		delete[] pRecs;
		delete[] pBuff;
		pRecs = NULL;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new TTabRecord[TabSize];
	pBuff = new TTabRecord[TabSize];
	for (int i = 0; i < DataCount; i++) {
		pRecs[i] = tab.pRecs[i];
	}
	SortData();
	CurrPos = 0;
	return *this;
}

bool TSortTable::FindRecord(TKey k) {
	int i, i1 = 0, i2 = DataCount - 1;
	Efficiency = 0;
	while (i1 <= i2) {
		Efficiency++;
		i = (i1 + i2) >> 1;
		if (pRecs[i].Key == k) {
			i1 = i + 1;
			i2 = i;
			break;
		}
		if (pRecs[i].Key > k)
			i2 = i - 1;
		else
			i1 = i + 1;
	}
	if ((i2 < 0) || (pRecs[i2].Key < k))
		i2++;
	CurrPos = i2;
	if ((i2 < DataCount) && (pRecs[i].Key == k)) {
		return true;
	}
	return false;
}

int TSortTable::InsRecord(TKey k, TValue pVal) {
	if (IsFull()) {
		return TabFull;
	}
	else {
		bool temp = FindRecord(k);
		if (temp == true) return TabRecDbl;
		else {
			for (int i = DataCount; i > CurrPos; i--)
			{
				pRecs[i] = pRecs[i - 1];
				Efficiency++;
			}
			pRecs[CurrPos].Key = k;
			pRecs[CurrPos].pValue = pVal;
			DataCount++;
			Efficiency++;
			return TabOK;
		}
	}
}
int TSortTable::DelRecord(TKey k) {
	bool temp = FindRecord(k);
	for (int i = CurrPos; i < DataCount - 1; i++)
		pRecs[i] = pRecs[i + 1];
	DataCount--;
	return TabOK;
}

void TSortTable::SortData() {
	Efficiency = 0;
	switch (SortMethod)
	{
	case INSERT_SORT:
		InsertSort(pRecs, DataCount); break;
	case MERGE_SORT:
		MergeSort(pRecs, DataCount);
		break;
	}
}

void TSortTable::InsertSort(TTabRecord* pRecs, int DataCount) {
	TTabRecord pR;
	Efficiency = DataCount;
	for (int i = 1, j; i < DataCount; i++) {
		pR = pRecs[i];
		for (j = i - 1; j > -1; j--)
			if (pRecs[j].Key > pR.Key) {
				pRecs[j + 1] = pRecs[j];
				Efficiency++;
			}
			else
				break;
		pRecs[j + 1] = pR;
	}
}

void TSortTable::MergeSort(TTabRecord *pRecs, int DataCount) {
	TTabRecord *pData = pRecs;
	TTabRecord *pBuff = new TTabRecord[DataCount];
	pBuff = pData;
	TTabRecord *pTemp = pBuff;
	MergeSorter(pData, pBuff, DataCount);
	if (pData == pTemp)
		for (int i = 0; i < DataCount; i++)
			pBuff[i] = pData[i];
	delete pTemp;
}
void TSortTable::MergeSorter(TTabRecord *&pData, TTabRecord *&pBuff, int Size) {
	int n1 = (Size + 1) / 2;
	int n2 = Size - n1;
	if (Size > 2) {
		TTabRecord *pDat2 = pData + n1, *pBuff2 = pBuff + n1;
		MergeSorter(pData, pBuff, n1);
		MergeSorter(pDat2, pBuff2, n2);
	}
	MergeData(pData, pBuff, n1, n2);
}
void TSortTable::MergeData(TTabRecord *&pData, TTabRecord *&pBuff, int n1, int n2) {
	int i = 0, i1 = 0, i2 = 0;
	TTabRecord *pDat1 = pData, *pDat2 = pData + n1;
	while ((i1 < n1) && (i2 < n2)) {
		if (pDat1[i1].Key < pDat2[i2].Key)
			pBuff[i++] = pDat1[i1++];
		else
			pBuff[i++] = pDat2[i2++];
	}

	while (i1 < n1)
		pBuff[i++] = pDat1[i1++];
	while (i2 < n2)
		pBuff[i++] = pDat2[i2++];
	pData = pBuff;
	pBuff = pDat1;
	Efficiency += n1 + n2;
}
