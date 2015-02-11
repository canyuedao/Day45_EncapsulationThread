// Day45_EncapsulationThread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "pThread.h"

const int num=10;
DWORD pThreadID[num];

//*****************************//
//实现接口
//*****************************//
CRITICAL_SECTION gCS;
int arrTicketNum[num]={10,20,30,40,50,60,70,80,90,100};	//给定每个窗口的卖票张数
int iarrSelled[num]={};									//每个窗口总卖票数数组
class threadTest1:public threadInterface{
public:	
	DWORD threadFunc(LPVOID pPM){						//与创建线程之间的参数传递	
		int iTickerTotal=arrTicketNum[(int)pPM];		//线程的总票数
		int iTicketNum=0;								//票号
		int *iTicketRepeat=new int[iTickerTotal];		//线程每个票号卖的张数数组
		memset(iTicketRepeat,0,iTickerTotal*4);			//初始化票号卖的张数
		while(iTicketNum<iTickerTotal){
			int itemp=iTicketNum;	
			iTicketNum++;									
			printf("%d号窗口买票 %d %d\n",(int)pPM,itemp,pThreadID[(int)pPM]);
			iTicketRepeat[itemp]++;
			EnterCriticalSection(&gCS);
			iarrSelled[(int)pPM]++;
			LeaveCriticalSection(&gCS);			
		}				
		return (DWORD)iTicketRepeat;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{	
	InitializeCriticalSection(&gCS);	
	threadTest1 test1;									//实例化继承自接口的类
	HANDLE hThread[num];								//线程句柄数组
	pThread *thread=new pThread[num];					//初始化多个线程类对象
	for(int i=0;i<num;i++){			
		thread[i]=pThread(&test1,(void*)i);		
		hThread[i]=thread[i].createThread();			//创建线程
		pThreadID[i]=thread[i].getThreadID();			//获取线程ID
	}
	WaitForMultipleObjects(num,hThread,true,INFINITE);	
	for(int i=0;i<num;i++){
		int *pThreadNum=(int*)thread[i].getResult();	//每张票号卖的张数数组
		int iLeakNum=0;									//漏票
		int iRepeatNum=0;								//重票
		for(int j=0;j<arrTicketNum[i];j++){
			if(pThreadNum[j]==0){
				iLeakNum++;
			}
			else if(pThreadNum[j]>1){
				iRepeatNum+=pThreadNum[j]-1;
			}
		}
		printf("%d窗口\n漏票 %d\n重票 %d\n总票 %d\n",i,iLeakNum,iRepeatNum,iarrSelled[i]);
		delete pThreadNum;
	}	
	delete []thread;									//释放线程资源
	return 0;
}

