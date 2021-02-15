
// ChildView.h : interface of the CChildView class
//
#include "CMatrix.h"
#include <vector>
#pragma once


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();
	std::vector<CMatrix> arr;
// Attributes
public:
	
// Operations
public:
	void InitMatrix(CMatrix &);
	void InitMatrixes(std::vector<CMatrix>&);
	void PrintMatrix(CDC&, int, int, CMatrix&);
	void PrintCMatrixes(CDC&, int, int, CString *, std::vector<CMatrix>);
	void PrintDoubles(CDC &, int, int, CString*, std::vector<double>);
// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTestMatrix();
	afx_msg void OnTestFunctions();
};

