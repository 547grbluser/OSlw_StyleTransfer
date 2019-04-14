/*(Ver.=0.96)
 * OSLW_gift.h
 *
 *  Created on: 2017-7-14
 *      Author: slw
 */

#ifndef OSLW_GIFT_H_
#define OSLW_GIFT_H_

#include "OSLW_define.h"
#include "OSLW_parameter.h"
#include "OSLW_tool_basic.h"

#if !(OSLW_SIMPLE_LEVEL >= 3)


//------------------------------------------
//<��������>OSlwGiftUnitUN</��������>
//<�����幦��>����ģ��˽�е�Ԫ ���ж��ط��ʹ���</�����幦��>
//------------------------------------------
typedef struct OSLW_GIFT_UNIT_UNION{

	

	struct OSLW_PARAMETER_STRUCT *pParaData;
	struct {
		lw_u8 ComID;
		lw_u8 RxD[OSLW_GIFT_COMMUN_RXD_LENGTH];
	} ComCmd;
	
	lw_u8 str[OSLW_GIFT_UNIT_STR_LENGTH];
	lw_u8 KeyBoardInput;
}OSlwGiftUnitUN;



//------------------------------------------
//<�ṹ����>OSlwGiftExternUnitSTU</�ṹ����>
//<�ṹ�幦��>�����ⲿ�洢�ռ�</�ṹ�幦��>
//------------------------------------------
//typedef struct OSLW_GIFT_EXTERN_UNIT_STRUCT{
//	lw_16 Length;
//	void *arr;
//}OSlwGiftExternUnitSTU;

typedef OSlwExternMemorySTU OSlwGiftExternUnitSTU;

//------------------------------------------
//<ö��>GiftUnitStatusNUM</ö��>
//<ö�ٹ���>����״̬����</ö�ٹ���>
//------------------------------------------
typedef enum{
	GiftUnitStatus_NAN=0,
	GiftUnitStatus_Free=1,
	GiftUnitStatus_InDelivery,
	GiftUnitStatus_Received
}GiftUnitStatusNUM;

//------------------------------------------
//<ö��>GiftPostmanStatusNUM</ö��>
//<ö�ٹ���>���Ա״̬����</ö�ٹ���>
//------------------------------------------
typedef enum{

	GiftPostmanStatus_NAN=0,//Ϊ��ʼ��
	GiftPostmanStatus_Free=1,//����״̬
	GiftPostmanStatus_InDelivery,//��������
	GiftPostmanStatus_Received,//��ǩ�� ��ʾĿ�������Ѿ�����
	GiftPostmanStatus_Return//���� ��ʾĿ�������Ѿ�����(�������ݾ���˫���Ե�ģʽ)
}GiftPostmanStatusNUM;


//------------------------------------------
//<�ṹ����>OSlwGiftUnitSTU</�ṹ����>
//<�ṹ�幦��>���ﵥԪ�ռ� ����һƬ˽�����ⲿ��Ԫ</�ṹ�幦��>
//------------------------------------------
typedef struct OSLW_GIFT_UNIT_STRUCT{
	
	OSlwGiftExternUnitSTU ExternUnit;//�����ⲿ��Ԫ
	OSlwGiftUnitUN PrivateUnit;//����˽�е�Ԫ
	
	
}OSlwGiftUnitSTU;


//------------------------------------------
//<�ṹ����>OSlwGiftPostmanSTU</�ṹ����>
//<�ṹ�幦��>���Ա �ṹ�� ����Ϊ˫������Ľڵ�</�ṹ�幦��>
//------------------------------------------
typedef struct OSLW_GIFT_POSTMAN_STRUCT{

	OSlwToolDListNodeSTU node;
	
	lw_u8 GroupFlag;
	
	lw_u8 PostmanID;

	struct OSLW_TASK_STRUCT *pSource,*pAim;//ָ��Դ������Ŀ�������ָ�� ��ʱ����
	
	struct OSLW_MEMORY_BASIC_STRUCT *pmem;
	
	GiftPostmanStatusNUM Status,Method;//���Ա��ǰ״̬��Ŀ�� ��Ŀ����״̬��ͬʱ ��ʾ���Աʹ������
		
	struct OSLW_GIFT_TRANSMIT_STRUCT *pGT;//ָ���������͵�λ��ָ��


}OSlwGiftPostmanSTU;


//------------------------------------------
//<�ṹ����>OSlwGiftReceiveSTU</�ṹ����>
//<�ṹ�幦��>����������ṹ�� ����Ϊ˫������Ŀ��Ƶ�Ԫ</�ṹ�幦��>
//------------------------------------------
typedef struct OSLW_GIFT_RECEIVE_STRUCT{
	//��Ա����

	OSlwToolDListSTU List;
	
	struct OSLW_GIFT_CONCIERGE_STRUCT *pGC;//ָ���Լ���������������ָ��
	
	//��Ա����
#if !(OSLW_SIMPLE_MODE)	
	struct OSLW_GIFT_POSTMAN_STRUCT *(*AppendFun)(struct OSLW_GIFT_RECEIVE_STRUCT *pgr,struct OSLW_GIFT_POSTMAN_STRUCT *pgp);//׷�Ӻ���
	struct OSLW_GIFT_POSTMAN_STRUCT *(*MoveNextFun)(struct OSLW_GIFT_RECEIVE_STRUCT *pgr);//�ƶ����� 
	struct OSLW_GIFT_POSTMAN_STRUCT *(*SlipNextFun)(struct OSLW_GIFT_RECEIVE_STRUCT *pgr,struct OSLW_GIFT_POSTMAN_STRUCT **ppGP);//�������� 	
#endif
}OSlwGiftReceiveSTU;




//------------------------------------------
//<�ṹ����>OSlwGiftTransmitSTU</�ṹ����>
//<�ṹ�幦��>���﷢�����ṹ��</�ṹ�幦��>
//�𽥷��� �����ڴ������ƴ���
//------------------------------------------
#if 0
typedef struct OSLW_GIFT_TRANSMIT_STRUCT{
	
	OSlwGiftPostmanSTU PostmanList[OSLW_GIFT_POSTMAN_MAX];//���Ա�б� �洢һ���ֿ��Ա
	
	union OSLW_CORE_GROUP_UNION PostmanFlag;//״̬��־�� Ϊ0��ʾ������� һλ����һ�����Ա 
	
	struct OSLW_GIFT_CONCIERGE_STRUCT *pGC;	//ָ���Լ���������������ָ��
#if !(OSLW_SIMPLE_MODE)		
	OSlwGiftPostmanSTU* (*IdleFun)(struct OSLW_GIFT_TRANSMIT_STRUCT *pgt);
#endif	
}OSlwGiftTransmitSTU;
#endif // 0

//------------------------------------------
//<�ṹ����>OSlwGiftConciergeSTU</�ṹ����>
//<�ṹ�幦��>���������ṹ��</�ṹ�幦��>
//------------------------------------------
typedef struct OSLW_GIFT_CONCIERGE_STRUCT{

	
	OSlwGiftReceiveSTU giftR;//����
	//OSlwGiftTransmitSTU giftT;//����

	struct OSLW_TASK_STRUCT *pta;//ָ���Լ����������ָ��
	
}OSlwGiftConciergeSTU;


//��������
void OSlwGiftConciergeInitial(OSlwGiftConciergeSTU *pgc);

//�𽥷��� �����ڴ������ƴ���
#if 0
void OSlwGiftTransmitInitial(OSlwGiftTransmitSTU *pgt);
OSlwGiftPostmanSTU * OSlwGiftTransmitIdle(OSlwGiftTransmitSTU *pgt);
#endif


OSlwGiftPostmanSTU * OSlwGiftReceiveAppend(OSlwGiftReceiveSTU *pgr,OSlwGiftPostmanSTU *pgp);
OSlwGiftPostmanSTU * OSlwGiftReceiveMoveNext(OSlwGiftReceiveSTU *pgr);
OSlwGiftPostmanSTU * OSlwGiftReceiveSlipNext(OSlwGiftReceiveSTU *pgr,OSlwGiftPostmanSTU **ppGP);
OSlwGiftPostmanSTU * OSlwGiftReceiveForeah(OSlwGiftReceiveSTU *pgr,OSlwGiftPostmanSTU **ppGP);


OSlwGiftPostmanSTU * OSlwGiftAllocPostman(struct OSLW_MEMORY_BASIC_STRUCT *pmem);

#endif // !(OSLW_SIMPLE_LEVEL >= 3)


#define OSLW_GIFT_RECE_GIFT(PTA) do{OSlwTaskReceOnceGift(PTA);}while(0)

#define OSLW_GIFT_SIGNE(PGP) do{(PGP)->Method=(PGP)->Status;}while(0)

#define OSLW_GIFT_SEND_GIFT(PTA,PM) do{OSlwGiftReceiveAppend(&((PTA)->Concierge.giftR),(PM));}while(0)

#define OSLW_GIFT_GET_GIFT(PTA) (OSlwTaskGetOnceGift(PTA))

#define OSLW_GIFT_GET_MAN(PTA) ((OSlwGiftPostmanSTU *)(PTA->Concierge.giftR.List.Head.con.pNext))

#define OSLW_GIFT_NEXT(PTA) ((PTA)->Concierge.giftR.MoveNextFun(&(PTA->Concierge.giftR)))

#define OSLW_GIFT_NUM(PTA) (((PTA)->Concierge.giftR.List.NowLen) & 0xFFFE)

#define OSLW_GIFT_JUDGE_FLAG(PGP,NUM,COND) if((((PGP)->GroupFlag)!=NUM) && (COND)) continue;

#define OSLW_GIFT_SLIP(PTA,PGP) (OSlwGiftReceiveSlipNext(&(PTA->Concierge.giftR),&(PGP)))

#define OSLW_GIFT_SG_SF(PTA,PM,NUM) do{(PM)->GroupFlag=(NUM);OSLW_GIFT_SEND_GIFT((PTA),(PM));OSLW_FLAG_SET((PTA),(NUM));}while(0)

#define OSLW_FLAG_POP(PTA,NUM) ((PTA)->TaskGroupFlag.CurrentStatus.bits.bit##NUM)

#define OSLW_FLAG_GET(PTA,NUM) ((((PTA)->TaskGroupFlag.CurrentStatus.all)>>(NUM))&1)

#define OSLW_FLAG_CLR(PTA,NUM) do {(PTA)->TaskGroupFlag.CurrentStatus.all &= (~(1<<(NUM)));}while(0)

#define OSLW_FLAG_SET(PTA,NUM) do {(PTA)->TaskGroupFlag.CurrentStatus.all |= ((1<<(NUM)));}while(0)





#if OSLW_SIMPLE_LEVEL ==3
void * OSlwGiftReceiveMoveNext(OSlwToolDListNodeConnectSTU *pgr);


//ȡ�����ֺ궨��
#undef OSLW_GIFT_SEND_GIFT
#undef OSLW_GIFT_GET_GIFT
#undef OSLW_GIFT_RECE_GIFT
#undef OSLW_GIFT_SIGNE
#undef OSLW_GIFT_SEND_GIFT
#undef OSLW_GIFT_GET_GIFT
#undef OSLW_GIFT_GET_MAN
#undef OSLW_GIFT_NEXT
#undef OSLW_GIFT_JUDGE_FLAG
#undef OSLW_GIFT_NUM




#define OSLW_GIFT_NEXT(PTA) (OSlwGiftReceiveMoveNext(&((PTA)->Concierge)))
#define OSLW_GIFT_GET_GIFT(PTA) ((void *)((lw_u8 *)((PTA)->Concierge.pNext) + (sizeof(OSlwToolDListNodeConnectSTU))))
#define OSLW_GIFT_GET_MAN(PTA) ((void *)(PTA)->Concierge.pNext)


#endif

typedef OSlwGiftPostmanSTU LwPostman;

#define LwGetMan OSLW_GIFT_GET_MAN 
#define LwGetGift(PGP) ((PGP)->node.Data.pData) 
#define LwSignGift OSLW_GIFT_SIGNE
#define LwNextGift OSLW_GIFT_SLIP
#define LwCheckGift OSLW_GIFT_JUDGE_FLAG
#define LwSendGift OSLW_GIFT_SEND_GIFT

#define LwCallPost(PMEM) OSlwGiftAllocPostman((void *)((PMEM)))

#define LwForeachGift(PTA,PGP) for((PGP)=((OSlwGiftPostmanSTU *)&((PTA)->Concierge.giftR.List.Head));OSlwGiftReceiveForeah(&((PTA)->Concierge.giftR),&(PGP));)

#define LwSetFlag OSLW_FLAG_SET
#define LwClearFlag OSLW_FLAG_CLR
#define LwGetFlag OSLW_FLAG_GET
#define LwPopFlag OSLW_FLAG_POP

#define LwSendGiFg OSLW_GIFT_SG_SF

#endif /*(Ver.=0.96) OSLW_GIFT_H_ */
