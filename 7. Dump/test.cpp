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

// 处理 Unhandled Exception 的回调函数
LONG ApplicationCrashHanlder(EXCEPTION_POINTERS* pException)
{
	// 写入 dump
	CreateDumpFile(_T("E:\\Test.dmp"), pException);
	// 这里弹出一个错误对话框并退出程序
	FatalAppExit(0, _T("*** Unhandled Exception! ***"));
	return EXCEPTION_EXECUTE_HANDLER;
}

// 一个有函数调用的类  
//   
class CrashTest
{
public:
	void Test() { Crash(); }

private:
	void Crash() {
		// 除零，制造人为的程序崩溃  
		int i = 13;
		int j = 0;
		int m = i / j;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	// 设置 Unhandled Exception 的回调函数
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHanlder);

	CrashTest test;
	test.Test();

	return 0;
}