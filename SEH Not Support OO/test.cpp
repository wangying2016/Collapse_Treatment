#include <windows.h>
#include <tchar.h>

// ������ӻᱨ��error C2712: �޷���Ҫ�����չ���ĺ�����ʹ�� __try
// ��Ϊ __try ����ʹ���˶���SEH ���������㣬�䲻֧��������󣩡�

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

int _tmain(int argc, _TCHAR* argv[])
{
	__try {
		CrashTest test;
		test.Test();
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		// ��������Ӵ����������Ĵ���
	}
	return 0;
}