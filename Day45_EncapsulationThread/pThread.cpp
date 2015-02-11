#include "stdafx.h"
#include "pThread.h"

//***********************************//
//默认构造函数，用于初始化多个对象
//***********************************//
pThread::pThread(){
	lpParameterList=NULL;
	pArgList=this;
	hThread=NULL;
	pThreadID=new DWORD;
	pthreadInce=NULL;
}


//***************************************//
//构造函数，传递实现接口类的对象和参数指针
//***************************************//
pThread::pThread(threadInterface *ince,LPVOID pPM){
	lpParameterList=pPM; 
	pArgList=this;
	hThread=NULL;
	pThreadID=new DWORD;
	pthreadInce=ince;
}


//*****************************************************************//
//拷贝赋值运算符，不拷贝线程ID指针，只拷贝接口类对象的指针和参数指针
//*****************************************************************//
void pThread::operator=(pThread&rhs){	
	this->lpParameterList=rhs.lpParameterList;
	this->pthreadInce=rhs.pthreadInce;
}


//**********************//
//释放线程对象和ID指针
//**********************//
pThread::~pThread(){	
	CloseHandle(hThread);
	delete pThreadID;
}


//**********************//
//创建线程对象，返回句柄
//**********************//
HANDLE pThread::createThread(){	
	hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)pThreadFunc,pArgList,0,pThreadID);		
	return hThread;
}


//**********************//
//获取线程ID
//**********************//
DWORD pThread::getThreadID(){
	return *pThreadID;
}


DWORD pThread::getResult(){
	return dwResult;
}