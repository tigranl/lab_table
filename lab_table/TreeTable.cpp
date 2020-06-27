#include "TreeTable.h"

bool TTreeTable::IsFull() const
{
	TTreeNode* pNode = new TTreeNode();
	int temp = pNode == NULL;
	delete pNode;
	return temp;
}

bool TTreeTable::FindRecord(TKey k)
{
	pPrev = NULL;
	pCurrent = pRoot;
	while (pCurrent != NULL) {
		Efficiency++;
		if (pCurrent->Key == k) break;
		pPrev = pCurrent;
		if (pCurrent->Key < k) pCurrent = pCurrent->pRight;
		else pCurrent = pCurrent->pLeft;
	}
	if (pCurrent != NULL) {
		return true;
	}
	else {
		pCurrent = pPrev;
		return false;
	}
}

int TTreeTable::InsRecord(TKey k, TValue pVal) {
	if (IsFull()) {
		return TabFull;
	}
	else if (FindRecord(k)) {
		return TabRecDbl;
	}
	else {
		TTreeNode* tmp = new TTreeNode(k, pVal);
		if (pRoot == NULL) {
			pRoot = tmp;
		}
		else {
			if (k < pCurrent->Key) {
				pCurrent->pLeft = tmp;
			}
			else {
				pCurrent->pRight = tmp;
			}
		}
		Efficiency++;
		DataCount++;
	}
}

int TTreeTable::DelRecord(TKey k) {
	if (FindRecord(k) == false) {
		return TabNoRec;
	}
	else {
		TTreeNode* pNode = pCurrent;
		if (pNode->pRight == NULL) {
			if (pPrev == NULL) {
				pRoot = pNode->pLeft;
			}
			else {
				if (pPrev->pRight == pNode) {
					pPrev->pRight = pNode->pLeft;
				}
				else {
					pPrev->pLeft = pNode->pLeft;
				}
			}
			Efficiency++;
		}
		else if (pNode->pLeft == NULL) {
			if (pPrev == NULL) {
				pRoot = pNode->pRight;
			}
			else {
				if (pPrev->pRight == pNode) {
					pPrev->pRight = pNode->pRight;
				}
				else {
					pPrev->pLeft = pNode->pRight;
				}
			}
			Efficiency++;
		}
		else {
			TTreeNode* pN = pNode->pLeft;
			pPrev = pNode;
			while (pN->pRight != NULL) {
				pPrev = pN;
				pN = pN->pRight;
				Efficiency++;
			}

			pNode->pValue = pN->pValue;
			pNode->Key = pN->Key;
			if (pPrev->pRight == pN) {
				pPrev->pRight = pN->pLeft;
			}
			else {
				pPrev->pLeft = pN->pLeft;
			}
			pNode = pN;
			Efficiency++;
		}
		delete pNode;
		DataCount--;
		return TabOK;
	}
}


TKey TTreeTable::GetKey(void) const
{
	return (pCurrent == NULL) ? 0 : pCurrent->Key;
}

TValue TTreeTable::GetValue(void) const
{
	return (pCurrent == NULL) ? NULL : pCurrent->pValue;
}

int TTreeTable::Reset(void)
{
	TTreeNode* pNode = pCurrent = pRoot;
	while (!St.empty())
		St.pop();
	CurrPos = 0;
	while (pNode != NULL)
	{
		St.push(pNode);
		pCurrent = pNode;
		pNode = pNode->GetLeft();
	}
	return IsTabEnded();
}

int TTreeTable::IsTabEnded(void) const
{
	return CurrPos >= DataCount;
}

int TTreeTable::GoNext(void)
{
	if (!IsTabEnded() && (pCurrent != NULL))
	{
		TTreeNode* pNode = pCurrent = pCurrent->GetRight();
		St.pop();
		while (pNode != NULL)
		{
			St.push(pNode);
			pCurrent = pNode;
			pNode = pNode->GetLeft();
		}

		if ((pCurrent == NULL) && !St.empty())
			pCurrent = St.top();
		CurrPos++;
	}
	return IsTabEnded();
}


ostream& operator<<(ostream& os, TTreeTable& tab)
{
	cout << "Table printing" << endl;
	tab.PrintTreeTable(os, tab.pRoot);
	return os;
}

void TTreeTable::Draw(void)
{
	cout << "Table printing" << endl;
	DrawTreeTable(pRoot, 0);
}


void TTreeTable::PutValues(TTreeNode* pNode, int Level)
{
	if ((pNode != NULL) && (pos < 20))
	{
		PutValues(pNode->pLeft, Level + 1);
		tk[pos] = pNode->Key;
		tl[pos] = Level;
		pos++;
		PutValues(pNode->pRight, Level + 1);
	}
}


void TTreeTable::PrintTreeTable(ostream& os, TTreeNode* pNode)
{
	if (pNode != NULL)
	{
		PrintTreeTable(os, pNode->pLeft);
		pNode->Print(os);
		os << endl;
		PrintTreeTable(os, pNode->pRight);
	}
}

void TTreeTable::DrawTreeTable(TTreeNode* pNode, int Level)
{
	if (pNode != NULL)
	{
		DrawTreeTable(pNode->pRight, Level + 1);
		for (int i = 0; i < 2 * Level; i++)
			cout << " ";
		pNode->Print(cout);
		cout << endl;
		DrawTreeTable(pNode->pLeft, Level + 1);
	}
}

void TTreeTable::DeleteTreeTable(TTreeNode* pNode)
{
	if (pNode != NULL)
	{
		DeleteTreeTable(pNode->pLeft);
		DeleteTreeTable(pNode->pRight);
		delete pNode;
	}
}
