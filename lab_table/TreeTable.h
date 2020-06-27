#pragma once
#ifndef _treetable_h
#define _treetable_h
#include <stack>
#include "Table.h"
#include "TreeNode.h"

class TTreeTable : public TTable
{
protected:
	TTreeNode  *pRoot;
	TTreeNode* ppRef;
	TTreeNode  *pCurrent;
	TTreeNode* pPrev;
	int CurrPos;
	stack<TTreeNode*> St;

	void PrintTreeTable(ostream& os, TTreeNode *pNode);
	void DrawTreeTable(TTreeNode *pNode, int Level);
	void DeleteTreeTable(TTreeNode *pNode);
	string tk[20];
	int tl[20], pos;
	void PutValues(TTreeNode *pNode, int Level);
public:
	TTreeTable() : TTable()
	{
		CurrPos = 0;
		pRoot = pCurrent = ppRef = NULL;
	}
	~TTreeTable() { DeleteTreeTable(pRoot); }

	virtual bool IsFull() const;

	virtual bool FindRecord(TKey k);
	virtual int  InsRecord(TKey k, TValue pVal);
	virtual int  DelRecord(TKey k);

	virtual int Reset(void);
	virtual int IsTabEnded(void) const;
	virtual int GoNext(void);

	virtual TKey GetKey(void) const;
	virtual TValue GetValue(void) const;

	friend ostream& operator<<(ostream& os, TTreeTable& tab);
	void Draw(void);
};

#endif
