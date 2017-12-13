#include <windows.h>
#include <tchar.h>

// 在异常处理代码被调用执行后，程序继续可以运行，并正常退出，并没有崩溃！
// 通过使用 __try/__except 可以捕捉到任何类型的异常，并保证程序不会崩溃

int _tmain(int argc, _TCHAR* argv[])
{
	__try {
		MessageBox(NULL, _T("Message from '__try' section"), _T("Test"), MB_OK);

		// 除零，制造人为的程序崩溃
		int i = 13;
		int j = 0;
		int m = i / j;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		// 在这里处理程序崩溃情况的代码
		MessageBox(NULL, _T("Message from '__except' section"), _T("Test"), MB_OK);
	}

	MessageBox(NULL, _T("Function completed"), _T("Test"), MB_OK);
	return 0;
}
