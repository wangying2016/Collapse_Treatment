#include <windows.h>
#include <tchar.h>

// 这个例子会报错：error C2712: 无法在要求对象展开的函数中使用 __try
// 因为 __try 块内使用了对象（SEH 的致命弱点，其不支持面向对象）。

// 一个有函数调用的类
class CrashTest
{
public:
	CrashTest() {}
	virtual ~CrashTest() {}

	void Test() { crash(); }

private:
	void crash() {
		// 除零，制造人为的程序崩溃
		int i = 13;
		int j = 0;
		int m = i / j;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	__try {
		CrashTest test;
		test.Test();
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		// 在这里添加处理程序崩溃的代码
	}
	return 0;
}