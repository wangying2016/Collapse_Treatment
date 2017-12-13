#include <windows.h>
#include <tchar.h>
#include <Dbghelp.h>

// 添加对dbghelp.lib的编译依赖  
#pragma comment(lib, "dbghelp.lib")  

// 创建 Dump 文件
void CreateDumpFile(LPCSTR lpstrDumpFilePathName, EXCEPTION_POINTERS* pException)
{
	// 创建 Dump 文件
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Dump 信息
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = TRUE;

	// 写入 Dump 文件内容
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);
}

// 作为except块中表达式的函数  
LONG CrashHandler(EXCEPTION_POINTERS *pException)
{
	// 在这里添加处理程序崩溃情况的代码  

	// 这里以弹出一个对话框为例子  
	MessageBox(NULL, _T("Message from Catch handler"), _T("Test"), MB_OK);

	// 创建Dump文件  
	CreateDumpFile(_T("Test.dmp"), pException);

	return EXCEPTION_EXECUTE_HANDLER;
}

int _tmain(int argc, _TCHAR* argv[])
{
	__try {
		MessageBox(NULL, _T("Message from '__try' sectioin"), _T("Test"), MB_OK);

		// 除零，制造人为的程序崩溃
		int i = 13;
		int j = 0;
		int m = i / j;
	}
	// 捕捉到让程序崩溃的异常时创建 dump 文件
	__except (CrashHandler(GetExceptionInformation())) {
		// 这里以弹出一个对话框为例子
		MessageBox(NULL, _T("Message from '__except' section"), _T("Test"), MB_OK);
	}

	MessageBox(NULL, _T("Function completed"), _T("Test"), MB_OK);
	return 0;
}