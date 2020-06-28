#pragma once
#ifndef _sorttable_h
#define _sorttable_h

#include "ScanTable.h"

//sorted table
enum TSortMethod { INSERT_SORT = 1, MERGE_SORT = 2 };

class TSortTable : public TScanTable {
protected:

	TTabRecord* pBuff;
	TSortMethod SortMethod;
	void SortData(void);
	void InsertSort(TTabRecord* pMem, int DataCount);
	void MergeSort(TTabRecord* pMem, int DataCount);
	void MergeSorter(TTabRecord*& pData, TTabRecord*& pBuff, int Size);
	void MergeData(TTabRecord*& pData, TTabRecord*& pBuff, int n1, int n2);
public:
	TSortTable(int Size = TabMaxSize) : TScanTable(Size) {
		pBuff = new TTabRecord[DataCount];
	};
	~TSortTable()
	{
		delete[] pBuff;
	}
	TSortTable(const TScanTable& tab) { *this = tab; }
	TSortTable& operator=(const TScanTable& tab);
	TSortMethod GetSortMethod(void) { return SortMethod; }
	void SetSortMethod(TSortMethod sm) { SortMethod = sm; }

	virtual bool FindRecord(TKey k);
	virtual int InsRecord(TKey k, TValue pVal);
	virtual int DelRecord(TKey k);
};

#endif 
