
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
};
