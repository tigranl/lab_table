#pragma once
#ifndef _ARRAYHASH_
#define _ARRAYHASH_

#include "HashTable.h"
#define TabHashStep 7

class TArrayHashTable : public HashTable
{
protected:
	TTabRecord* pRecs;
	int TabSize;
	int HashStep;
	int FreePos;
	int CurrPos;
	TTabRecord Mark;
	TTabRecord Empty;
public:
	TArrayHashTable(int size = TabMaxSize, int step = TabHashStep);
	virtual ~TArrayHashTable();
	virtual bool IsFull() const { return DataCount >= TabSize; };
	virtual bool FindRecord(TKey k);
	virtual int InsRecord(TKey k, TValue val);
	virtual int DelRecord(TKey k);
	virtual int Reset(void);
	virtual int IsTabEnded(void) const;
	virtual int GoNext(void);
	virtual TKey GetKey(void) const;
	virtual TValue GetValue(void) const;
	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; }

};

#endif
