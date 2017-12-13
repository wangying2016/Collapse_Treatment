#include <windows.h>
#include <tchar.h>

// 这个版本的 SEH 使用不会使得编译器报错，因为我们将 CrashTest 对象
// 的调用封装成了一个简单的 Test 函数

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

void Test()
{
	CrashTest test;
	test.Test();
}

int _tmain(int argc, _TCHAR* argv[])
{
	__try {
		Test();
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		// 在这里添加处理程序崩溃的代码
	}
	return 0;
}