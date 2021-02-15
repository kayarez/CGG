
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Lab1.h"
#include "ChildView.h"
#include "CMatrix.h"
#include <string>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	CMatrix A(3, 3);
	CMatrix B(3, 3);
	CMatrix V1(3, 1);
	CMatrix V2(3, 1);
	arr = { A,B,V1,V2 };
	InitMatrixes(arr);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_TEST_MATRIX, &CChildView::OnTestMatrix)
	ON_COMMAND(ID_TEST_FUNCTIONS, &CChildView::OnTestFunctions)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this);
	CString titles[] = { L"Matrix A", L"Matrix B", L"Vector 1", L"Vector 2" };
	for (size_t i = 0; i < std::size(arr); i++)
	{
		dc.TextOut(i * 150, 0, titles[i]);
		PrintMatrix(dc, i * 150, 20, arr[i]);
	}
}

void CChildView::PrintMatrix(CDC & dc, int x, int y, CMatrix & M)
{
	CString cstr;
	for (int i = 0; i < M.cols(); i++)
	{
		for (int j = 0; j < M.rows(); j++)
		{
			cstr.Format(_T("%.1f"), M(j, i));
			dc.TextOutW(x + i * 50, y + j * 20, cstr);
		}
	}
}

void CChildView::InitMatrix(CMatrix & M)
{
	for (int i = 0; i < M.rows(); i++)
	{
		for (int j = 0; j < M.cols(); j++)
		{
			M(i, j) = rand() % 10;
		}
	}
}

void CChildView::InitMatrixes(std::vector<CMatrix> &vector)
{
	for (size_t i = 0; i < std::size(vector); i++)
	{
		InitMatrix(vector[i]);
	}
}

CMatrix VectorMult(CMatrix& V1, CMatrix& V2)
{
	CMatrix resultVector(3);
	resultVector(0, 0) = V1(1, 0)*V2(2, 0) - V2(1, 0)*V1(2, 0);
	resultVector(1, 0) = (-1)*(V1(0, 0)*V2(2, 0) - V2(0, 0)*V1(2, 0));
	resultVector(2, 0) = V1(0, 0)*V2(1, 0) - V2(0, 0)*V1(1, 0);
	return resultVector;
}

double ScalarMult(CMatrix& V1, CMatrix& V2)
{
	return V1(0, 0)*V2(0, 0) + V1(1, 0)*V2(1, 0) + V1(2, 0)*V2(2, 0);
}

double ModVec(CMatrix& V)
{
	return sqrt((double)(V(0, 0)*V(0, 0) + V(1, 0)*V(1, 0) + V(2, 0)*V(2, 0)));
}

double CosV1V2(CMatrix& V1, CMatrix& V2)
{
	return (ScalarMult(V1, V2) / (ModVec(V1)*ModVec(V2)));
}

CMatrix SphereToCart(CMatrix& PView)
{
	CMatrix result(3);
	result(0) = PView(0)*cos(PView(1))*sin(PView(2));
	result(1) = PView(0)*sin(PView(1))*sin(PView(2));
	result(2) = PView(0)*cos(PView(2));
	return result;
}

void CChildView::PrintCMatrixes(CDC & dc, int x, int y, CString * titles, std::vector<CMatrix> vector)
{
	for (size_t i = 0; i < std::size(vector); i++)
	{
		dc.TextOut(x + i * 150, y, titles[i]);
		PrintMatrix(dc, x + i * 150, y + 20, vector[i]);
	}
}

void CChildView::PrintDoubles(CDC & dc, int x, int y, CString * titles, std::vector<double> vector)
{
	for (size_t i = 0; i < std::size(vector); i++)
	{
		dc.TextOut(x + i * 150, y, titles[i]);
		CString s;
		s.Format(_T("%.1f"), vector[i]);
		dc.TextOut(x + i * 150, y + 20, s);
	}
}

void CChildView::OnTestMatrix()
{
	CClientDC dc(this);
	InvalidateRect(0);
	UpdateWindow();
	CString titles[] = { L"A+B", L"A*B", L"A*V1", L"V1(T)*V2", L"V1(T)*A*V2" };
	std::vector<CMatrix> vector = { arr[0] + arr[1], arr[0] * arr[1], arr[0] * arr[2], arr[2].Transp()*arr[3], arr[2].Transp()*arr[0] * arr[3] };
	PrintCMatrixes(dc, 0, 100, titles, vector);
}

void CChildView::OnTestFunctions()
{
	CClientDC dc(this);
	InvalidateRect(0);
	UpdateWindow();
	CMatrix sphere(3);
	InitMatrix(sphere);
	CString matrixTitles[] = { L"SphereMatrix", L"VectorMult", L"SphereToCart" };
	CString doublesTitles[] = { L"ScalarMult", L"ModVec", L"CosV1V2" };
	std::vector<CMatrix> cmatrixes = { sphere, VectorMult(arr[2], arr[3]),SphereToCart(sphere) };
	std::vector<double> doubles = { ScalarMult(arr[2],arr[3]), ModVec(arr[2]), CosV1V2(arr[2],arr[3]) };
	PrintCMatrixes(dc, 0, 100, matrixTitles, cmatrixes);
	PrintDoubles(dc, std::size(cmatrixes) * 150, 100, doublesTitles, doubles);
}
