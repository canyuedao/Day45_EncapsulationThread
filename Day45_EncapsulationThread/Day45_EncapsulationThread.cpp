// Day45_EncapsulationThread.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "pThread.h"

const int num=10;
DWORD pThreadID[num];

//*****************************//
//ʵ�ֽӿ�
//*****************************//
CRITICAL_SECTION gCS;
int arrTicketNum[num]={10,20,30,40,50,60,70,80,90,100};	//����ÿ�����ڵ���Ʊ����
int iarrSelled[num]={};									//ÿ����������Ʊ������
class threadTest1:public threadInterface{
public:	
	DWORD threadFunc(LPVOID pPM){						//�봴���߳�֮��Ĳ�������	
		int iTickerTotal=arrTicketNum[(int)pPM];		//�̵߳���Ʊ��
		int iTicketNum=0;								//Ʊ��
		int *iTicketRepeat=new int[iTickerTotal];		//�߳�ÿ��Ʊ��������������
		memset(iTicketRepeat,0,iTickerTotal*4);			//��ʼ��Ʊ����������
		while(iTicketNum<iTickerTotal){
			int itemp=iTicketNum;	
			iTicketNum++;									
			printf("%d�Ŵ�����Ʊ %d %d\n",(int)pPM,itemp,pThreadID[(int)pPM]);
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
	threadTest1 test1;									//ʵ�����̳��Խӿڵ���
	HANDLE hThread[num];								//�߳̾������
	pThread *thread=new pThread[num];					//��ʼ������߳������
	for(int i=0;i<num;i++){			
		thread[i]=pThread(&test1,(void*)i);		
		hThread[i]=thread[i].createThread();			//�����߳�
		pThreadID[i]=thread[i].getThreadID();			//��ȡ�߳�ID
	}
	WaitForMultipleObjects(num,hThread,true,INFINITE);	
	for(int i=0;i<num;i++){
		int *pThreadNum=(int*)thread[i].getResult();	//ÿ��Ʊ��������������
		int iLeakNum=0;									//©Ʊ
		int iRepeatNum=0;								//��Ʊ
		for(int j=0;j<arrTicketNum[i];j++){
			if(pThreadNum[j]==0){
				iLeakNum++;
			}
			else if(pThreadNum[j]>1){
				iRepeatNum+=pThreadNum[j]-1;
			}
		}
		printf("%d����\n©Ʊ %d\n��Ʊ %d\n��Ʊ %d\n",i,iLeakNum,iRepeatNum,iarrSelled[i]);
		delete pThreadNum;
	}	
	delete []thread;									//�ͷ��߳���Դ
	return 0;
}

