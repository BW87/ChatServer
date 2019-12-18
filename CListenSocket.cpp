#include "pch.h"
#include "CListenSocket.h"
#include "CClientSocket.h"


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CClientSocket* pClient = new CClientSocket;
	if (Accept(*pClient)) {
		pClient->SetListenSocket(this);
		m_PtrClientSocketList.AddTail(pClient);
	}
	else {
		delete pClient;
		AfxMessageBox(L"ERROR : Failed to accept new client!");
	}
	CAsyncSocket::OnAccept(nErrorCode);
}
void CListenSocket::CloseClientSocket(CSocket* pClient) {
	POSITION pos;
	pos = m_PtrClientSocketList.Find(pClient);
	if (pos != NULL) {
		if (pClient != NULL) {
			pClient->ShutDown();
			pClient->Close();
		}
		m_PtrClientSocketList.RemoveAt(pos);
		delete pClient;
	}
	
}
void CListenSocket::SendChatDataAll(TCHAR* pszMessage) {
	POSITION pos;
	pos = m_PtrClientSocketList.GetHeadPosition();
	CClientSocket* pClient = NULL;

	while (pos != NULL) {
		pClient = (CClientSocket*)m_PtrClientSocketList.GetNext(pos);
		if (pClient != NULL) {
			pClient->Send(pszMessage, lstrlen(pszMessage)* 2);

		}
	}
}