#include <windows.h>
#include <tchar.h>

// __try��__finally ���Ա�֤���� try ���ڵĴ���ִ�н����Σ�finally ���ڵĴ���
// �ܻᱻ���ú�ִ��
// ע���ʱ�� __except �������ǣ��˳����ǻ������ֻ�Ǳ���������ִ�� __finally
// ���ڵĴ���

int _tmain(int argc, TCHAR* argv[])
{
	__try {
		MessageBox(NULL, _T("Message from '__try' section"), _T("Test"), MB_OK);

		// ���㣬������Ϊ�ı���
		int i = 13;
		int j = 0;
		int m = i / j;
	}
	__finally {
		// ������Ӵ�������������Ĵ���
		MessageBox(NULL, _T("Message from '__finally' section"), _T("Test"), MB_OK);
	}
	
	MessageBox(NULL, _T("Function completed"), _T("Test"), MB_OK);
	return 0;
}
