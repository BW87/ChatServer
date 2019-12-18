
#pragma once
#include <afxsock.h>
class CListenSocket :
	public CAsyncSocket
{
public:

	CPtrList m_PtrClientSocketList;
	virtual void OnAccept(int nErrorCode);
	virtual void CloseClientSocket(CSocket* pClient);
	virtual void SendChatDataAll(TCHAR* pszMessage);
};
