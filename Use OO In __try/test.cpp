#include <windows.h>
#include <tchar.h>

// ����汾�� SEH ʹ�ò���ʹ�ñ�����������Ϊ���ǽ� CrashTest ����
// �ĵ��÷�װ����һ���򵥵� Test ����

// һ���к������õ���
class CrashTest
{
public:
	CrashTest() {}
	virtual ~CrashTest() {}

	void Test() { crash(); }

private:
	void crash() {
		// ���㣬������Ϊ�ĳ������
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
		// ��������Ӵ����������Ĵ���
	}
	return 0;
}