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

// ���� Unhandled Exception �Ļص�����
LONG ApplicationCrashHanlder(EXCEPTION_POINTERS* pException)
{
	// д�� dump
	CreateDumpFile(_T("E:\\Test.dmp"), pException);
	// ���ﵯ��һ������Ի����˳�����
	FatalAppExit(0, _T("*** Unhandled Exception! ***"));
	return EXCEPTION_EXECUTE_HANDLER;
}

// һ���к������õ���  
//   
class CrashTest
{
public:
	void Test() { Crash(); }

private:
	void Crash() {
		// ���㣬������Ϊ�ĳ������  
		int i = 13;
		int j = 0;
		int m = i / j;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	// ���� Unhandled Exception �Ļص�����
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHanlder);

	CrashTest test;
	test.Test();

	return 0;
}