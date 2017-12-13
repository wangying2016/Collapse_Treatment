#include <windows.h>
#include <tchar.h>

// __try、__finally 可以保证无论 try 块内的代码执行结果如何，finally 块内的代码
// 总会被调用和执行
// 注意此时与 __except 的区别是，此程序还是会崩溃，只是崩溃结束后执行 __finally
// 块内的代码

int _tmain(int argc, TCHAR* argv[])
{
	__try {
		MessageBox(NULL, _T("Message from '__try' section"), _T("Test"), MB_OK);

		// 除零，制造人为的崩溃
		int i = 13;
		int j = 0;
		int m = i / j;
	}
	__finally {
		// 这里添加处理程序崩溃情况的代码
		MessageBox(NULL, _T("Message from '__finally' section"), _T("Test"), MB_OK);
	}
	
	MessageBox(NULL, _T("Function completed"), _T("Test"), MB_OK);
	return 0;
}
