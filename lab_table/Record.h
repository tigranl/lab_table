#ifndef _record_h
#define _record_h

#include <iostream>
#include <string>

using namespace std;

typedef int TKey;
typedef string TValue;

class TTabRecord {

protected:
	TKey Key;
	TValue pValue;
	virtual void Print(ostream &os) { os << Key << " " << pValue; }

public:

	TTabRecord(TKey k = 0, TValue pVal = "") {
		Key = k;
		pValue = pVal;
	}
	void SetKey(TKey k) { Key = k; }
	TKey GetKey() { return Key; }
	void SetValue(TValue p) { pValue = p; }
	TValue GetValue() { return pValue; }


	virtual int operator==(const TTabRecord &tr) { return Key == tr.Key; }
	virtual int operator< (const TTabRecord &tr) { return Key < tr.Key; }
	virtual int operator> (const TTabRecord &tr) { return Key > tr.Key; }
	virtual int operator=(const TTabRecord &tr) { return Key = tr.Key; }
	virtual int operator!=(const TTabRecord &tr) { return Key != tr.Key; }

	friend class TArrayTable;
	friend class TScanTable;
	friend class TSortTable;
	friend class TTreeNode;
	friend class TTreeTable;
	friend class TArrayHash;
	friend class THashTable;

	friend ostream& operator<<(ostream& os, const TTabRecord &rec)
	{
		return os << rec.Key << " | " << rec.pValue;
	}
};

#endif
