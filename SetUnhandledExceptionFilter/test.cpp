#include <windows.h>
#include <tchar.h>

// 使用 Windows API 函数 SetHandledExceptionFilter 设置一个回调函数
// 来处理无法预料的异常

// 处理 Unhandled Exception 的回调函数
LONG ApplicationCrashHanlder(EXCEPTION_POINTERS* pException)
{
	// 在这里添加处理程序崩溃情况的代码
	// 现在很多软件都是弹出一个发送错误报告的对话框

	// 这里弹出一个错误对话框并退出程序
	FatalAppExit(0, _T("*** Unhandled Exception! ***"));

	return EXCEPTION_EXECUTE_HANDLER;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// 设置处理 Unhandled Exception 的回调函数
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHanlder);

	// 除零，制造人为的程序崩溃
	int i = 13;
	int j = 0;
	int m = i / j;

	return 0;
}