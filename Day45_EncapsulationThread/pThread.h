
#include <Windows.h>
class threadInterface{	
public:
	virtual DWORD threadFunc(LPVOID pPM)=0;
};
class pThread{	

	DWORD dwResult;

	LPDWORD pThreadID;										//线程ID指针

	void *pArgList;											//线程与回调函数通讯的

	LPVOID lpParameterList;									//线程之间通讯的传递参数

	HANDLE hThread;

	threadInterface *pthreadInce;

	//**************************************//
	//线程回调函数
	//**************************************//
public:
	static DWORD WINAPI pThreadFunc(LPVOID lpParameter){
		((pThread*)lpParameter)->dwResult=((pThread*)lpParameter)->pthreadInce->threadFunc(((pThread*)lpParameter)->lpParameterList);	//线程回调函数里调用接口函数
		return ((pThread*)lpParameter)->dwResult;
	}
	
public:
	
	pThread();												//默认构造函数，用于初始化多个对象
	
	pThread(threadInterface *ince,LPVOID lpParameterList=NULL);	//构造函数，传递回调函数指针和参数指针
	
	~pThread();												//释放线程对象和ID指针
	
	void operator=(pThread&);								//拷贝赋值运算符，不拷贝线程ID指针
	
	HANDLE createThread();									//创建线程对象，返回句柄
	
	DWORD getThreadID();									//获取线程ID

	DWORD getResult();
	
};