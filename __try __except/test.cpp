#include <windows.h>
#include <tchar.h>

// ���쳣������뱻����ִ�к󣬳�������������У��������˳�����û�б�����
// ͨ��ʹ�� __try/__except ���Բ�׽���κ����͵��쳣������֤���򲻻����

int _tmain(int argc, _TCHAR* argv[])
{
	__try {
		MessageBox(NULL, _T("Message from '__try' section"), _T("Test"), MB_OK);

		// ���㣬������Ϊ�ĳ������
		int i = 13;
		int j = 0;
		int m = i / j;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		// �����ﴦ������������Ĵ���
		MessageBox(NULL, _T("Message from '__except' section"), _T("Test"), MB_OK);
	}

	MessageBox(NULL, _T("Function completed"), _T("Test"), MB_OK);
	return 0;
}
