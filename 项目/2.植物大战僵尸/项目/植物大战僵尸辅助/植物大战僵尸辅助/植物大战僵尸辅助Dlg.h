
// 植物大战僵尸辅助Dlg.h : 头文件
//

#pragma once


// C植物大战僵尸辅助Dlg 对话框
class C植物大战僵尸辅助Dlg : public CDialogEx
{
// 构造
public:
	C植物大战僵尸辅助Dlg(CWnd* pParent = NULL);	// 标准构造函数

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
	BOOL m_b_CD;
	afx_msg void OnBnClickedCheckCd();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	UINT m_edit_money;
	afx_msg void OnEnChangeEditMoney();
	afx_msg void OnBnClickedButtonMoney();
	UINT m_edit_sun;
	afx_msg void OnEnChangeEditSun();
	afx_msg void OnBnClickedButtonSun();
	afx_msg void OnBnClickedButtonPlan();
	afx_msg void OnBnClickedButtonOpenplan();
	afx_msg void OnBnClickedButtonClosePlan();
	afx_msg void OnBnClickedCheckWudi();
	afx_msg void OnBnClickedCheckSunFast();
};
