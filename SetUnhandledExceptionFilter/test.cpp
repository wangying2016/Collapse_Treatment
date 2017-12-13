#include <windows.h>
#include <tchar.h>

// ʹ�� Windows API ���� SetHandledExceptionFilter ����һ���ص�����
// �������޷�Ԥ�ϵ��쳣

// ���� Unhandled Exception �Ļص�����
LONG ApplicationCrashHanlder(EXCEPTION_POINTERS* pException)
{
	// ��������Ӵ�������������Ĵ���
	// ���ںܶ�������ǵ���һ�����ʹ��󱨸�ĶԻ���

	// ���ﵯ��һ������Ի����˳�����
	FatalAppExit(0, _T("*** Unhandled Exception! ***"));

	return EXCEPTION_EXECUTE_HANDLER;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ���ô��� Unhandled Exception �Ļص�����
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHanlder);

	// ���㣬������Ϊ�ĳ������
	int i = 13;
	int j = 0;
	int m = i / j;

	return 0;
}