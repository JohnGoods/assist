
// 扫雷辅助Dlg.h : 头文件
//

#pragma once


// C扫雷辅助Dlg 对话框
class C扫雷辅助Dlg : public CDialogEx
{
// 构造
public:
	C扫雷辅助Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonChujiGame();
	afx_msg void OnBnClickedButtonZhongjiGame();
	int m_editBase;
	afx_msg void OnBnClickedButtonReadFlag();
	afx_msg void OnBnClickedButtonGaojiGame();
	void OnBaseOpenMenu(int ID);
	afx_msg void OnBnClickedButtonCustom();
	afx_msg void OnBnClickedButtoncClick();
};
