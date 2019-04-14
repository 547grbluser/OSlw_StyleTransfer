/*(Ver.=0.96)
 * OSLW_tool.h
 *
 *  Created on: 2017-7-25
 *      Author: slw
 */

#ifndef OSLW_TOOL_BASIC_H_
#define OSLW_TOOL_BASIC_H_


#include "OSLW_define.h"
#include "OSLW_parameter.h"
#include "OSLW_memory.h"
#include "OSLW_tool_define.h"

#if OSLW_TOOL_IMPORT_SLIP_WIN|| OSLW_TOOL_IMPORT_ALL
//--------------------
//<����>
//pMasterData �����ݳ�
//pBufferData �������ݳ�
//MDataLen_forSize_t �����ݶ���size_t�Ĵ�С
//BufferLength �������Ѵ����ݴ�С!!!!!!!!!�û����뱣֤�������㹻!!!!!!!!!!!!!
//MDataLockFlag �����������־ ���Ϊ1 ��ʾ���������� �������뻺����
//AppendFun ��Ա���� psw:this pd:�����׵�ַ num:���ݳ���
//</����>
//--------------------
typedef struct OSLW_TOOL_SLIPWIN_STRUCT{

	void *pMasterData;
	void *pBufferData;

	lw_u32 MDataLen_forSize_t;
	
	
	lw_u16 BufferLength;	
	lw_u8 MDataLockFlag;
	
	struct OSLW_TOOL_SLIPWIN_STRUCT* (*AppendFun)(struct OSLW_TOOL_SLIPWIN_STRUCT *psw,void *pd,lw_u8 num);

}  OSlwToolSlipwinSTU;

OSlwToolSlipwinSTU* OSlwToolSlipwinAppend(OSlwToolSlipwinSTU *psw,void *pd,lw_u8 num);


#define OSLW_TOOL_SLIPWIN_DEFAULT(MD,BUF,DTYPE,LEN) {(MD),(BUF),(sizeof(DTYPE)*LEN),0,0,OSlwToolSlipwinAppend};

#define OSLW_TOOL_MEMCPY(P,Q,N) do {while((N)--)*(P)++=*(Q)++;}while(0)

#endif //OSLW_TOOL_IMPORT_SLIP_WIN


#if OSLW_TOOL_IMPORT_DLIST|| OSLW_TOOL_IMPORT_ALL
//-------------------
//<����ڵ�>
//</����ڵ�>
//--------------------
typedef struct OSLW_TOOL_DLIST_NODE_STRUCT{

	OSlwToolDListNodeConnectSTU con;
	OSlwExternMemorySTU Key;
	OSlwExternMemorySTU Data;
	
}OSlwToolDListNodeSTU;


typedef enum{
	OSlwToolDListIndexMode_byNum=0,
	OSlwToolDListIndexMode_byId=1

}OSlwToolDListIndexModeNUM;

typedef lw_8(*pOSlwDlistCmpFun)(OSlwToolDListNodeSTU *pDLN, lw_u16 data, lw_u16 count, void *pdata);
#define OSLW_TOOL_DLIST_FUN_PARA_DEFAULT pOSlwDlistCmpFun pCmpFun,lw_u16 data,void *pdata


//--------------------
//<˫������>
//</˫������>
//--------------------
typedef struct OSLW_TOOL_DLIST_STRUCT{
	OSlwToolDListNodeSTU Head,*pTail;
	lw_u16 MaxLen,NowLen;
	OSlwToolDListNodeSTU* (*IndexOfFUN)(struct OSLW_TOOL_DLIST_STRUCT *pDL, OSLW_TOOL_DLIST_FUN_PARA_DEFAULT);
	OSlwToolDListNodeSTU* (*AppendFUN)(struct OSLW_TOOL_DLIST_STRUCT *pDL,OSlwToolDListNodeSTU *pDLN);
	OSlwToolDListNodeSTU* (*InsertFUN)(struct OSLW_TOOL_DLIST_STRUCT *pDL,OSlwToolDListNodeSTU *pDLN, OSLW_TOOL_DLIST_FUN_PARA_DEFAULT);
	OSlwToolDListNodeSTU* (*RemoveFUN)(struct OSLW_TOOL_DLIST_STRUCT *pDL, OSLW_TOOL_DLIST_FUN_PARA_DEFAULT);
	
}OSlwToolDListSTU;

#define OSLW_TOOL_DLIST_FUN_PARA_DEFAULT pOSlwDlistCmpFun pCmpFun,lw_u16 data,void *pdata


#if !(OSLW_SIMPLE_LEVEL >= 4)
OSlwToolDListNodeSTU* OSlwToolDListIndexOf(OSlwToolDListSTU *pDL, OSLW_TOOL_DLIST_FUN_PARA_DEFAULT);
OSlwToolDListNodeSTU* OSlwToolDListAppend(struct OSLW_TOOL_DLIST_STRUCT *pDL, OSlwToolDListNodeSTU *pDLN);
OSlwToolDListNodeSTU* OSlwToolDListInsert(struct OSLW_TOOL_DLIST_STRUCT *pDL,OSlwToolDListNodeSTU *pDLN, OSLW_TOOL_DLIST_FUN_PARA_DEFAULT);
OSlwToolDListNodeSTU* OSlwToolDListRemove(struct OSLW_TOOL_DLIST_STRUCT *pDL, OSLW_TOOL_DLIST_FUN_PARA_DEFAULT);
OSlwToolDListNodeSTU* _OSlwToolDListRemoveNode (struct OSLW_TOOL_DLIST_STRUCT *pDL, OSlwToolDListNodeSTU *pDLNbuf);
#endif // !(OSLW_SIMPLE_LEVEL >= 4)


#define OSLW_TOOL_DLIST_NODE_CONNECT(P1,P2) 	(P1)->con.pNext=(OSlwToolDListNodeConnectSTU *)(P2);/*(Ver.=0.96)β������һ��Ϊ�µ�*/\
(P2)->con.pLast = (OSlwToolDListNodeConnectSTU *)(P1);/*(Ver.=0.96)�½ڵ����һ��Ϊԭ��β��*/

#define OSLW_TOOL_DLIST_NODE_INSERT(P1,P_INSERT) (P_INSERT)->con.pLast = (OSlwToolDListNodeConnectSTU *)(P1);\
(P_INSERT)->con.pNext = (OSlwToolDListNodeConnectSTU *)(P1)->con.pNext;\
(P1)->con.pNext->pLast = (OSlwToolDListNodeConnectSTU *)(P_INSERT);\
(P1)->con.pNext = (OSlwToolDListNodeConnectSTU *)(P_INSERT);

#define OSLW_TOOL_DLIST_NODE_DELECT(P) 			(P)->con.pLast->pNext=(P)->con.pNext;/*(Ver.=0.96)��һ������һ��Ϊ��һ��*/\
(P)->con.pNext->pLast = (P)->con.pLast;/*(Ver.=0.96)��һ������һ��Ϊ��һ��*/


void OSlwToolDListInitial(OSlwToolDListSTU *pDL,lw_u8 len,void *p);

lw_8 OSlwToolDListCmpId(OSlwToolDListNodeSTU *pDLN, lw_u16 data, lw_u16 count, void *pdata);
lw_8 OSlwToolDListCmpCount(OSlwToolDListNodeSTU *pDLN, lw_u16 data, lw_u16 count, void *pdata);

#endif //OSLW_TOOL_IMPORT_DLIST



#if !(OSLW_SIMPLE_LEVEL >= 4)

#if OSLW_TOOL_IMPORT_HASH_LIST|| OSLW_TOOL_IMPORT_ALL

typedef lw_u8 (*HashCalFunType)(void *pData);
lw_u8 HashCalStringBKDR(void *pData);


typedef lw_8(*HashKeyCmpFunType)(void *p1, void *p2);
lw_8 HashCmpString(void *p1, void *p2);

//--------------------
//<��ϣ��>
//</��ϣ��>
//--------------------
typedef struct OSLW_TOOL_HASH_STRUCT {
	OSlwToolDListNodeSTU *pHashList[OSLW_TOOL_HASH_LIST_MAX];
	lw_u8 HashListLength;

	HashCalFunType HashCalFun;
	HashKeyCmpFunType HashKeyCmp;

	lw_u8(*SelectFun)(struct OSLW_TOOL_HASH_STRUCT *pH, void *pKey, lw_u8 *pIndexResult, OSlwToolDListNodeSTU **ppDLN);
	OSlwToolDListNodeSTU* (*AppendFun)(struct OSLW_TOOL_HASH_STRUCT *pH, void *pKey, OSlwToolDListNodeSTU *pDLN);
	OSlwToolDListNodeSTU* (*DeleteFun)(struct OSLW_TOOL_HASH_STRUCT *pH, void *pKey);

}OSlwToolHashSTU;


void OSlwToolHashInitial(OSlwToolHashSTU *pH, lw_u8 length, HashCalFunType pHashFun, HashKeyCmpFunType pHashKeyCmpFun);
lw_u8 OSlwToolHashSelect(struct OSLW_TOOL_HASH_STRUCT *pH, void *pKey, lw_u8 *pIndexResult,OSlwToolDListNodeSTU **ppDLN);
OSlwToolDListNodeSTU* OSlwToolHashAppend(struct OSLW_TOOL_HASH_STRUCT *pH, void *pKey, OSlwToolDListNodeSTU *pDLN);
OSlwToolDListNodeSTU* OSlwToolHashDelete(struct OSLW_TOOL_HASH_STRUCT *pH, void *pKey);

#endif //OSLW_TOOL_IMPORT_HASH_LIST


#if OSLW_TOOL_IMPORT_TABLE|| OSLW_TOOL_IMPORT_ALL
typedef struct OSLW_TOOL_TABLE_STRUCT{

	OSlwExternMemorySTU Row;

	OSlwExternMemorySTU Col;

	lw_u32 ColSize;

	OSlwMemoryBasicSTU *pmem;

	void *(*ReadFun)(struct OSLW_TOOL_TABLE_STRUCT *pT, lw_32 row,lw_32 col,lw_u16 *pLen);
	lw_32 (*WriteFun)(struct OSLW_TOOL_TABLE_STRUCT *pT, lw_32 row, lw_32 col, void *psrc, lw_u16 len);
	
	
}OSlwToolTableSTU;



void OSlwToolTableInitial(OSlwToolTableSTU *pT, lw_u16 RowLen, lw_u16 *pCol, lw_u16 ColLen, OSlwMemoryBasicSTU *pmem, void *pTable, lw_u32 *pColReal);
void * OSlwToolTableRead(struct OSLW_TOOL_TABLE_STRUCT *pT, lw_32 row, lw_32 col, lw_u16 *pLen);
lw_32 OSlwToolTableWrite(struct OSLW_TOOL_TABLE_STRUCT *pT, lw_32 row, lw_32 col, void *psrc, lw_u16 len);

#endif //OSLW_TOOL_IMPORT_TABLE

#endif // !(OSLW_SIMPLE_LEVEL >= 4)

#endif


