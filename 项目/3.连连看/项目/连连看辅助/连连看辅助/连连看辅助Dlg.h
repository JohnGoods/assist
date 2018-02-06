
// 连连看辅助Dlg.h : 头文件
//

#pragma once


// C连连看辅助Dlg 对话框
class C连连看辅助Dlg : public CDialogEx
{
// 构造
public:
	C连连看辅助Dlg(CWnd* pParent = NULL);	// 标准构造函数

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
	int m_edit_x;
	int m_edit_y;
	afx_msg void OnBnClickedButtonStart();
	int m_edit_seat;
	afx_msg void OnBnClickedButtonSeat();
	CString m_edit_chess_data;
	afx_msg void OnBnClickedButtonChatData();
	afx_msg void OnBnClickedButtonClick();
	bool ClearPiar();
	afx_msg void OnBnClickedButtonSingle();
	int m_p1x;
	int m_p1y;
	int m_p2x;
	int m_p2y;
};
