
// ֲ���ս��ʬ����Dlg.h : ͷ�ļ�
//

#pragma once


// Cֲ���ս��ʬ����Dlg �Ի���
class Cֲ���ս��ʬ����Dlg : public CDialogEx
{
// ����
public:
	Cֲ���ս��ʬ����Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
};
