
// ɨ�׸���Dlg.h : ͷ�ļ�
//

#pragma once


// Cɨ�׸���Dlg �Ի���
class Cɨ�׸���Dlg : public CDialogEx
{
// ����
public:
	Cɨ�׸���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	afx_msg void OnBnClickedButtonChujiGame();
	afx_msg void OnBnClickedButtonZhongjiGame();
	int m_editBase;
	afx_msg void OnBnClickedButtonReadFlag();
	afx_msg void OnBnClickedButtonGaojiGame();
	void OnBaseOpenMenu(int ID);
	afx_msg void OnBnClickedButtonCustom();
	afx_msg void OnBnClickedButtoncClick();
};
