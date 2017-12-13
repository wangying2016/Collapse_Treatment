#include <windows.h>
#include <tchar.h>
#include <Dbghelp.h>

// ��Ӷ�dbghelp.lib�ı�������  
#pragma comment(lib, "dbghelp.lib")  

// ���� Dump �ļ�
void CreateDumpFile(LPCSTR lpstrDumpFilePathName, EXCEPTION_POINTERS* pException)
{
	// ���� Dump �ļ�
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Dump ��Ϣ
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;

	// д�� Dump �ļ�����
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);
}

// ��Ϊexcept���б��ʽ�ĺ���  
LONG CrashHandler(EXCEPTION_POINTERS *pException)
{
	// ��������Ӵ�������������Ĵ���  

	// �����Ե���һ���Ի���Ϊ����  
	MessageBox(NULL, _T("Message from Catch handler"), _T("Test"), MB_OK);

	// ����Dump�ļ�  
	CreateDumpFile(_T("Test.dmp"), pException);

	return EXCEPTION_EXECUTE_HANDLER;
}

int _tmain(int argc, _TCHAR* argv[])
{
	__try {
		MessageBox(NULL, _T("Message from '__try' sectioin"), _T("Test"), MB_OK);

		// ���㣬������Ϊ�ĳ������
		int i = 13;
		int j = 0;
		int m = i / j;
	}
	// ��׽���ó���������쳣ʱ���� dump �ļ�
	__except (CrashHandler(GetExceptionInformation())) {
		// �����Ե���һ���Ի���Ϊ����
		MessageBox(NULL, _T("Message from '__except' section"), _T("Test"), MB_OK);
	}

	MessageBox(NULL, _T("Function completed"), _T("Test"), MB_OK);
	return 0;
}