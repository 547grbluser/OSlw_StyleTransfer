/*(Ver.=0.96)
 * OSLW_core.h
 *
 *  Created on: 2017-7-14
 *      Author: slw
 */

#ifndef OSLW_CORE_H_
#define OSLW_CORE_H_

#include "OSLW_define.h"
#include "OSLW_parameter.h"
#include "OSLW_memory.h"
#include "OSLW_show.h"
#include "OSLW_communication.h"
#include "OSLW_timer.h"
#include "OSLW_task.h"
#include "OSLW_string_debug.h"
#include <limits.h>
#include <stdlib.h>

typedef lw_16 (*_compar_fn)(const void *,const void *);


//------------------------------------------
//<ö��>OSlwCoreErrorNUM</ö��>
//<ö�ٹ���>ö���ں˴�������</ö�ٹ���>
//------------------------------------------
typedef enum{
	OSlwCoreError_NoError=0,//�޴���
	OSlwCoreError_PriorityRedefine,//�������ȼ��ض������
	OSlwCoreError_GiftStatusError,
	OSlwCoreError_ParaListLengthOver,
	OSlwCoreError_TimerListLengthOver,
	OSlwCoreError_FixedMalloc
}OSlwCoreErrorNUM;

//------------------------------------------
//<ö��>OSlwCoreStatusNUM</ö��>
//<ö�ٹ���>ö���ں�״̬����</ö�ٹ���>
//------------------------------------------
typedef enum{
	OSlwCoreStatus_NAN=0,//δ����״̬
	OSlwCoreStatus_Initial=1,//��ʼ����
	OSlwCoreStatus_Running=0x0a,//����������
	OSlwCoreStatus_Error=0x05//�ں˴���
}OSlwCoreStatusNUM;



#if OSLW_OS_ENABLE
//------------------------------------------
//<�ṹ����>OSlwParameter_toForm</�ṹ����>
//<�ṹ�幦��>����ϵͳ�ں˽ṹ��</�ṹ�幦��>
//------------------------------------------
typedef struct OSLW_CORE_STRUCT{
	//��Ա����
#if !OSLW_SIMPLE_MODE
	_BP DispatchBreakPoint;//�������ϵ�
#endif
	
	OSlwCoreGroupUN InitialFlagGroup;//��ʼ����־��
	
	OSlwCoreGroupUN ReadyFlagGroup;//׼����ɱ�־��

	struct OSLW_TASK_STRUCT *pTaskList[OSLW_TASK_NUM_MAX];//ע���������Ŀ��ƿ�

	struct OSLW_TASK_STRUCT *pCurrentTask;//��ǰ������ƿ�

#if !OSLW_SIMPLE_MODE	
	struct OSLW_TASK_STRUCT *pLastTask;//֮ǰ��������ȼ�
#endif
	
	struct OSLW_TASK_STRUCT OSlwInlineTaskBoring;

	OSlwTimerCtrlSTU TimerCtrl;
	
	//OSlwShowSTU Show;

	lw_u8 DispatchEable:1;//������ʹ�ܱ�־ 0:�رյ����� 1:����������
	OSlwCoreStatusNUM CoreStatus:7;//�ں�״̬
	OSlwCoreErrorNUM CoreError:8;//�ں˴���
	
	lw_u8 TaskRunningNum;//��ǰע����������
	
	lw_u8 TaskRunningList[OSLW_TASK_NUM_MAX];//�Լ�ע�����������ȼ� ���ڿ��ٲ�ѯ����
	
	lw_u8 CurrentTaskIndex;//��ǰ��������ȼ�
	
#if !OSLW_SIMPLE_MODE	
	lw_u8 LastTaskIndex;//֮ǰ��������ȼ�
#endif

#if OSLW_SIMPLE_LEVEL<4 && OSLW_STR_DBG_EN

	struct OSLW_STRING_DEBUG_STRUCT StrDbg;

#endif // OSLW_SIMPLE_LEVEL<4 && OSLW_STR_DBG_EN



	
	OSlwGroupAllType _flag_BK;
	OSlwGroupAllType _mask_list[__OSLW_LOG2_TASK_NUM-2];
	OSlwGroupAllType _move_reg[__OSLW_LOG2_TASK_NUM-2];

#if OSLW_TASK_COMMUN_ENABLE==1
	//struct OSLW_COMMUN_STRCUT Comm[OSLW_CORE_COMMUN_LIST_LENGTH];
#endif

	//OSlwParaListCtrlSTU ParaBook[OSLW_CORE_PARA_PAGE_NUM];
	//lw_u16 ParaIdCount;




	//��Ա����
#if OSLW_STEP_RUNNING
	void(*StepFun)(struct OSLW_CORE_STRUCT *pOS);//ϵͳ��ʼ����
#else
	void(*StartFun)(struct OSLW_CORE_STRUCT *pOS);//ϵͳ��ʼ����
#endif
	struct OSLW_CORE_STRUCT *(*TaskAppendFun)(struct OSLW_CORE_STRUCT *pOS, struct OSLW_TASK_STRUCT *pta);//����ע�ắ��
	struct OSLW_CORE_STRUCT *(*TimerAppendFun)(struct OSLW_CORE_STRUCT *pOS, OSlwTimerSTU *pT);
	/*(Ver.=0.96)
#if !(OSLW_SIMPLE_MODE)
	void (*DispatchFun)(struct OSLW_CORE_STRUCT *pOS);//����������
	void (*ClockCBFun)(struct OSLW_CORE_STRUCT *pOS);//ϵͳʱ�ӻص����� !!!!!!!!!�������Գ�Ա��������!!!!!!!!!
	void (*StartFun)(struct OSLW_CORE_STRUCT *pOS);//ϵͳ��ʼ����
	struct OSLW_CORE_STRUCT *(*TaskAppendFun)(struct OSLW_CORE_STRUCT *pOS,struct OSLW_TASK_STRUCT *pta);//����ע�ắ��
	struct OSLW_CORE_STRUCT *(*ParaAppendFun)(struct OSLW_CORE_STRUCT *pOS,lw_u8 num,struct OSLW_PARAMETER_STRUCT *p);
	struct OSLW_CORE_STRUCT *(*TimerAppendFun)(struct OSLW_CORE_STRUCT *pOS,OSlwTimerSTU *pT);
#endif
*/

#if OSLW_SIMPLE_LEVEL<4 && OSLW_STR_DBG_EN
	lw_u8 *(*StrDbgFun)(struct OSLW_CORE_STRUCT *pOS, lw_u8 *instr);
#endif // OSLW_SIMPLE_LEVEL<4 && OSLW_STR_DBG_EN

	//������ʱ�м����
	lw_u8 n1_Dispatch,n2_Dispatch;
	lw_u8 Temp;
	lw_u8 temp2;
	lw_u8 _ReadyTaskIndex;

	//�ȶ�����ʱ�����
	lw_u64 NormalRunningTimerCount;

#if OSLW_SIMPLE_LEVEL >= 3
	lw_u8 CPU_Usage;
	lw_u8 _CPU_Usage_cal_reg;
	lw_u8 _CPU_Usage_count;
#else
	lw_u16 CPU_Usage;
	lw_u16 _CPU_Usage_cal_reg;
	lw_u16 _CPU_Usage_count;
#endif // OSLW_SIMPLE_LEVEL >= 3



}OSlwCoreSTU;



//��������
void OSlwTaskDispatch(OSlwCoreSTU *_pOS);
void OSlwClockCallBack(OSlwCoreSTU *pOS);
void OSlwCoreInitial(OSlwCoreSTU *pOS);
OSlwCoreSTU* OSlwTaskAppend(OSlwCoreSTU *pOS,struct OSLW_TASK_STRUCT *pta);
OSlwCoreSTU* OSlwParaAppend(OSlwCoreSTU *pOS,lw_u8 num,struct OSLW_PARAMETER_STRUCT *p);
OSlwCoreSTU* OSlwTimerAppend(OSlwCoreSTU *pOS,OSlwTimerSTU *pT);
#if OSLW_STEP_RUNNING
void OSlwCoreStep(OSlwCoreSTU *pOS);
#else
void OSlwCoreStart(OSlwCoreSTU *pOS);
#endif

void _quicksort (void *const pbase, size_t total_elems, size_t size,_compar_fn cmp);
lw_16 comp(const void*a,const void*b);


#endif //OSLW_OS_ENABLE


//<�����㷨��>
#define SWAP(a, b, size)						      \
  do									      \
    {									      \
      size_t __size = (size);						      \
      char *__a = (a), *__b = (b);					      \
      do								      \
	{								      \
	  char __tmp = *__a;						      \
	  *__a++ = *__b;						      \
	  *__b++ = __tmp;						      \
	} while (--__size > 0);						      \
    } while (0)

#define MAX_THRESH 4


typedef struct
  {
    char *lo;
    char *hi;
} stack_node;

#define STACK_SIZE	(CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)	((void) ((top->lo = (low)), (top->hi = (high)), ++top))
#define	POP(low, high)	((void) (--top, (low = top->lo), (high = top->hi)))
#define	STACK_NOT_EMPTY	(stack < top)
//</�����㷨��>


//�꺯�� & ��ģ��

//�͹��ĺ�
//����ģʽ��û��
#if !OSLW_SPEED_RUNNING
#define OSLW_LOW_POW_ENABLE() ((void)0)
#define OSLW_LOW_POW_DISABLE() ((void)0)
#endif



//�ϵ㱣�� 
#define REMEMBER(x,r) r=_OSLW_SAVE((x));if(!(r))


#if !OSLW_SIMPLE_MODE

//����׼�� AΪ����ָ��
#define DISPATCH_READY(A) A->BreakPointReturn[OSLW_TASK_BREAKPOINT_DEEP - 1] = _OSLW_SAVE((A->BreakPoint[OSLW_TASK_BREAKPOINT_DEEP - 1]));\
	if (!(A->BreakPointReturn[OSLW_TASK_BREAKPOINT_DEEP - 1]) && A->TaskStatus == OSlwTaskStatus_Running)

//���ȷ��� AΪ����ָ��
#define DISPATCH_RETURN(A) else{A->TaskStatus = OSlwTaskStatus_Running;}

#else

#define DISPATCH_READY(A) 	case __LINE__:(A)->BreakPoint=__LINE__;\
			if((A)->TaskStatus == OSlwTaskStatus_Ready){(A)->TaskStatus=OSlwTaskStatus_Running;}else

#define DISPATCH_RETURN(A) return;

#endif


			
//����ʼ			
		
#if OSLW_SIMPLE_MODE 
#define OSlw_5_2(A) 	switch((A)->BreakPoint){\
		default:\
		case 0:\
		case __LINE__:(A)->BreakPoint=__LINE__;\
		if((A)->TaskStatus == OSlwTaskStatus_Init){(A)->TaskStatus=OSlwTaskStatus_Running;return;}
		

#define	OSlw_2_5(A) }

#else

#define OSlw_5_2(A)		do{if(!_OSLW_SAVE(A->BreakPoint[OSLW_TASK_BREAKPOINT_DEEP-1]))\
{\
	A->TaskStatus=OSlwTaskStatus_Ready;\
	_OSLW_LOAD(A->pOS->DispatchBreakPoint,A->Priority,NULL);\
}}while(0)


#define OSlw_2_5(A) ;

#endif
	
	
	
#define OSLW_TASK_BENGIN(A) OSlw_5_2((A))

//�ȼ��� ���¾㱸
#define OSlwJiJi(A) OSlw_5_2(A)

//δ����	 ��Ƿ����
#define OSlwWeiJi(A) OSlw_2_5(A)			


//�����Ӻ�������
//<����>LV:Ƕ�׵ȼ��ȼ�(����������ֱ��ʹ�õ�����ȼ�Ϊ0 ����һ��Ϊ1 ��������) pta:����ָ�� F:�����õĺ���</����>
//<ʾ��> TaskSubFunCall(0,pta,fun1); pta�������fun1Ƕ�׵ȼ�0 </ʾ��> 
//!!!!!!!!!!!!void fun1(OSlwTaskSTU *pta,void *p)!!!!!!!!!!!!!!!!!!!!!!!!!

#define OSlwTaskSubFunCall(LV,PTA,F) do {REMEMBER(PTA->BreakPoint[LV],PTA->BreakPointReturn[LV])\
																				{F(PTA,(void *)(&(PTA->BreakPoint[LV])));}}while(0)

																				
																																				
																				
//�����Ӻ�������
//!!!!!!��TaskSubFunCall�ɶԵ��� ���ڷ���!!!!!!																				
#define OSlwTaskSubFunReturn(PTA,P) do { _OSLW_LOAD((*((_BP *)(P))),PTA->Priority,(PTA));}while(0)


#define OSlwCoreTaskIsReady(POS,PTA,ID) 					do{POS->ReadyFlagGroup.all|=(1<<ID);\
					PTA->TaskStatus=OSlwTaskStatus_Ready;}while(0)

					
					
					

//˯��N��ʱ��
//<����>A:������ƿ�ָ�� N:����</����>
#if OSLW_SIMPLE_MODE
#define OSlwSleepN(A,N) do {DISPATCH_READY(A){ OSlwTaskSleep(A,N-1);DISPATCH_RETURN(A)}} while(0)
#else
#define OSlwSleepN(A,N) do {DISPATCH_READY(A){ OSlwTaskSleep(A,N-1);}DISPATCH_RETURN(A)} while(0)
#endif


#define OSlwSleepSec(A,SEC,MS) OSlwSleepN(A,((((lw_u32)(SEC)*1000+(MS)))/(lw_u32)OSLW_CORE_TICK_MS))

//�ȴ��������
//<����>A:������ƿ�ָ��</����>
#if OSLW_SIMPLE_MODE
#define OSlwGiftReceiveWait(A) do {DISPATCH_READY(A){ OSlwTaskWaitGiftReceice(A);DISPATCH_RETURN(A)}} while(0)
#else
#define OSlwGiftReceiveWait(A) do {DISPATCH_READY(A){ OSlwTaskWaitGiftReceice(A);}DISPATCH_RETURN(A)} while(0)
#endif

#define OSlwWaitGift(A) OSlwGiftReceiveWait((A))

//�ȴ��������
//<����>A:������ƿ�ָ��</����>
#if OSLW_SIMPLE_MODE
#define OSlwGiftTransmitWait(A) do {DISPATCH_READY(A){ OSlwTaskWaitGiftTransmit(A);DISPATCH_RETURN(A)}} while(0)
#else
#define OSlwGiftTransmitWait(A) do {DISPATCH_READY(A){ OSlwTaskWaitGiftTransmit(A);}DISPATCH_RETURN(A)} while(0)
#endif

//�ȴ���־��
//<����>A:������ƿ�ָ��</����>
#if OSLW_SIMPLE_MODE
#define OSlwGroupFlagWait(A) do {DISPATCH_READY(A){ OSlwTaskWaitGroupFlag(A);DISPATCH_RETURN(A)}} while(0)
#else
#define OSlwGroupFlagWait(A) do {DISPATCH_READY(A){ OSlwTaskWaitGroupFlag(A);}DISPATCH_RETURN(A)} while(0)
#endif


#define OSlwWaitFlag(A) OSlwGroupFlagWait((A))

//�ȴ�����
//<����>A:������ƿ�ָ�� COND:����ѭ�������� NUM:���������� ���ⲿ���崫�� MS:ÿ����ʱ���õĺ���</����>
#define OSlwWaitCondition(A,COND,NUM,MS)  do{OSlwSleepSec((A),0,(MS));}while(--NUM && (COND))

//����cpuʹ��Ȩ
//<����>A:������ƿ�ָ��</����>
#define OSlwGiveUp(A) OSlwSleepN((A),2)

//����ֹͣ
//<����>A:������ƿ�ָ��</����>
#define OSlwTaskStop(A) do{(A)->TaskFrozenFlag=1;OSlwGiveUp(A);}while(0)

//������������CPUʹ��Ȩ
//<����>A:������ƿ�ָ�� COND:��������</����>
#define OSlwConditionGiveUp(A,COND) do{\
									if (COND)\
									{\
										OSlwGiveUp((A));\
									}\
									}while(0)


//��������
//<����>A:������ƿ�ָ��</����>
#define OSlwSetAlarm(A,SEC,MS) do{(A)->TimeSliceMax=((((lw_u32)(SEC)*1000+(MS)))/(lw_u32)OSLW_CORE_TICK_MS);}while(0)


//������
//<����>A:������ƿ�ָ��</����>
#define OSlwWatchAlarm(A) OSlwConditionGiveUp((A),((A)->RunningTimeSinceRunning >= (A)->TimeSliceMax))

//����
//<����>A:������ƿ�ָ��</����>
#define OSlwAuction(A,PRICE) OSlwConditionGiveUp((A),(OSlwTaskAuctionJudge((A),(lw_8)(PRICE))))


//���Գ�������ʱ�� ��ʼ
//<����>A:������ƿ�ָ��</����>
#define OSlwTic(A) do{(A)->BackToSleep.bits.timer_start_flag=1;}while(0)


//���Գ�������ʱ�� ����
//<����>A:������ƿ�ָ��</����>
#define OSlwToc(A) OSlwTaskToc((A))

//����һ����Ϣʱ��
//<����>A:������ƿ�ָ��</����>
#define OSlwSetNap(A,S,MS) do{(A)->BackToSleep.bits.all_time_count=((S)*1000+(MS))/(OSLW_CORE_TICK_MS);OSlwTic(pta);}while(0)


//������Ϣʱ��
//<����>A:������ƿ�ָ��</����>
#define OSlwNap(A) do{lw_u16 _res_t=OSlwToc((A));if((A)->BackToSleep.bits.all_time_count >(1+ _res_t)){OSlwSleepN(A,(A)->BackToSleep.bits.all_time_count - _res_t);}}while(0)


//#define OSlwSleepN(A,N) do {DISPATCH_READY(A){ A->SleepFun(A,N-1);}} while(0)

#endif /*(Ver.=0.96) OSLW_CORE_H_ */
