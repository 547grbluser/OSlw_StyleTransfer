/*(Ver.=0.96)
 * OSLW_gift.c
 *
 *  Created on: 2017-7-14
 *      Author: slw
 */

#include "OSLW_include.h"

#if OSLW_OS_ENABLE && OSLW_GIFT_EN

#if !(OSLW_SIMPLE_LEVEL >= 3)
//------------------------------------------
//<������>OSlwGiftConciergeInitial</������>
//<����˵��>��������ϵͳ ��ʼ��</����˵��>
//<����˵��>pgc:this</����˵��>
//<���˵��>void</���˵��>
//------------------------------------------


void OSlwGiftConciergeInitial(OSlwGiftConciergeSTU *pgc)
{

    OSLW_assert(!pgc);
    memset(pgc,0,sizeof(OSlwGiftConciergeSTU));//��ʼ������
    OSlwToolDListInitial(&(pgc->giftR.List), 0, NULL);
#if !(OSLW_SIMPLE_MODE)
    pgc->giftR.MoveNextFun=OSlwGiftReceiveMoveNext;//˫�������ƶ���Ա����
    pgc->giftR.SlipNextFun=OSlwGiftReceiveSlipNext;//��������
    pgc->giftR.AppendFun=OSlwGiftReceiveAppend;//׷�ӳ�Ա����
#endif
    pgc->giftR.pGC=pgc;//������ ָ��

    //OSlwGiftTransmitInitial(&(pgc->giftT));

    // pgc->giftT.pGC=pgc;//������ ָ��

}


//�𽥷��� �����ڴ������ƴ���
#if 0
void OSlwGiftTransmitInitial(OSlwGiftTransmitSTU *pgt)
{
    int n=0;

    OSLW_assert(!pgt);
#if !(OSLW_SIMPLE_MODE)
    pgt->IdleFun=OSlwGiftTransmitIdle;//�õ����г�Ա��������
#endif

    for(; n<OSLW_GIFT_POSTMAN_MAX; n++) //���Ա��ʼ��
    {
        pgt->PostmanList[n].PostmanID = n;
        pgt->PostmanList[n].Status = GiftPostmanStatus_Free;//����״̬Ϊ����
        pgt->PostmanList[n].pGT = pgt;//���Ա ����ָ���ʼ��
    }

}
#endif


//------------------------------------------
//<������>OSlwGiftReceiveAppend</������>
//<����˵��>���﷢�ͺ���</����˵��>
//<����˵��>pgr:this pgp:���Աָ��</����˵��>
//<���˵��>˫������ͷ��</���˵��>
//------------------------------------------
OSlwGiftPostmanSTU * OSlwGiftReceiveAppend(OSlwGiftReceiveSTU *pgr,OSlwGiftPostmanSTU *pgp)
{

    OSLW_assert(!pgr);
    OSLW_assert(!pgp);

#if 0

    if(!(pgr->GiftNum))//�жϵ�ǰ���������Ƿ�==0
    {   //Ϊ0

        pgr->pHead=pgr->pTail=pgp;//��β��ͬ
        pgr->pHead->pPrior=NULL;//��һ��Ϊ��
    }
    else
    {   //��Ϊ0
        pgr->pTail->pNext=pgp;//��ǰβ������һ������
        pgp->pPrior=pgr->pTail;//pgp��ǰһ��Ϊ��ǰβ��
        pgr->pTail=pgp;	//����β��
    }

    pgp->pGT->PostmanFlag.all|=((lw_u64)1<<pgp->ID);//���ͱ�־������

    pgp->Status=GiftPostmanStatus_InDelivery;//���Ա״̬Ϊ����Ͷ��
    pgr->pTail->pNext=NULL;//β����һ��Ϊ��
    pgr->GiftMax++;//�����++
    pgr->GiftNum++;//��������++

    return pgr->pHead;//����ͷ��
#endif // 0

    pgr->List.AppendFUN(&(pgr->List), &(pgp->node));

    //�𽥷��� �����ڴ������ƴ���
#if 0
    if(pgp->pGT)//˵���������ʵ�Ա
    {
        pgp->pGT->PostmanFlag.all |= ((lw_u64)1 << pgp->PostmanID);//���ͱ�־������
        if(pgp->Status!=GiftPostmanStatus_Free)//������Ա ״̬Ϊ���� �ſ��Է���ȴ�����
        {
            //�����Ϊ����
            pgr->pGC->pta->pOS->CoreError=OSlwCoreError_GiftStatusError;//���ں˴����־����
            return NULL;//����NULL
        }

    }
#endif

    pgp->Status = GiftPostmanStatus_InDelivery;//���Ա״̬Ϊ����Ͷ��
    return pgp;

}


//------------------------------------------
//<������>OSlwGiftReceiveMoveNext</������>
//<����˵��>����������ƶ� ���� do{...}while(..move..)ѭ��</����˵��>
//<����˵��>pgr:this</����˵��>
//<���˵��>��ǰͷ��</���˵��>
//------------------------------------------
OSlwGiftPostmanSTU * OSlwGiftReceiveMoveNext(OSlwGiftReceiveSTU *pgr)
{

    OSlwGiftPostmanSTU *p,*q;
//    OSlwMemoryBasicSTU *pmem;

    OSLW_assert(!pgr);

    if(pgr->List.NowLen<=1)//��������Ѿ�Ϊ0 �������ƶ�
    {
        return NULL;
    }
#if 0
    p=pgr->pHead;//ȡ��ͬ��
    if(pgr->GiftNum==1)//��������Ѿ�==1
    {
        pgr->pHead=NULL;//�ͷ�ͷ��
        pgr->pTail=NULL;//�ͷ�β��
        q=NULL;//����NULL ��Ϊ����do {}while() ѭ��
    }
    else
    {
        pgr->pHead=p->pNext;//ͷ����һ��
        q=pgr->pHead;//���ص�ǰͷ��
    }
    pgr->GiftNum--;//��������--

    if(p->Status == p->Method)//���֮ǰ����״̬ �� ģʽϵͳ
    {
        p->pGT->PostmanFlag.all &= ~((lw_u64)1<<p->ID);//������ͱ�־
        p->Status=GiftPostmanStatus_Free;//����״̬Ϊ����

    }
#endif // 0


    p = (OSlwGiftPostmanSTU *)pgr->List.Head.con.pNext;//ȡ�ó���ͷ���ĵ�һ��

    if (!p)
    {
        return NULL;
    }
    //�𽥷��� �����ڴ������ƴ���
#if 0
    if (p->Status == p->Method && (p->pGT))//�������״̬ �� Ŀ��ģʽһ�� �� �ʵ�Ա����
    {
        p->pGT->PostmanFlag.all &= ~((lw_u64)1 << p->PostmanID);//������ͱ�־
        p->Status = GiftPostmanStatus_Free;//����״̬Ϊ����

    }
#endif

    q = (OSlwGiftPostmanSTU *)(pgr->List.RemoveFUN(&(pgr->List), OSlwToolDListCmpCount, 1, NULL));


    return q;
}



//------------------------------------------
//<������>OSlwGiftReceiveSlipNext</������>
//<����˵��>����������ƶ� ���� do{...}while(..slip(,&pgp)..)ѭ��</����˵��>
//<����˵��>pgr:this,ppGP:ָ��ָ���ָ��</����˵��>
//<���˵��>�޸�֮���ָ��ֵ</���˵��>
//------------------------------------------
OSlwGiftPostmanSTU * OSlwGiftReceiveSlipNext(OSlwGiftReceiveSTU *pgr,OSlwGiftPostmanSTU **ppGP)
{
    OSlwGiftPostmanSTU *p;

    OSLW_assert(!pgr);
    OSLW_assert(!ppGP);
    OSLW_assert(!(*ppGP));

    p=(OSlwGiftPostmanSTU *)((*ppGP)->node.con.pNext);

    /*(Ver.=0.96)
    if(_OSlwToolDListRemoveNode(&(pgr->List),(OSlwToolDListNodeSTU *)(*ppGP)))
    {
    	return NULL;
    }
    */



    if((*ppGP)->Method == (*ppGP)->Status && (*ppGP)->pmem)
    {
        _OSlwToolDListRemoveNode(&(pgr->List),(OSlwToolDListNodeSTU *)(*ppGP));

        if(!((*ppGP)->pmem->Free((*ppGP)->pmem,(*ppGP))))//����ͷ�ʧ��
        {

            (*ppGP)=p;
            return p;

        }
    }

    (*ppGP)=p;
    return *ppGP;
}


//------------------------------------------
//<������>OSlwGiftReceiveForeah</������>
//<����˵��>��������/����˵��>
//<����˵��>pgr:this,ppGP:ָ��ָ���ָ��</����˵��>
//<���˵��>��һ������</���˵��>
//------------------------------------------
OSlwGiftPostmanSTU * OSlwGiftReceiveForeah(OSlwGiftReceiveSTU *pgr,OSlwGiftPostmanSTU **ppGP)
{
    OSlwGiftPostmanSTU *p;

    OSLW_assert(!pgr);
    OSLW_assert(!ppGP);
    OSLW_assert(!(*ppGP));

    p=(OSlwGiftPostmanSTU *)((*ppGP)->node.con.pNext);
	
		if((*ppGP) != (OSlwGiftPostmanSTU *)(&(pgr->List.Head)))
		{
			if((*ppGP)->Method == (*ppGP)->Status && (*ppGP)->pmem)
			{
					_OSlwToolDListRemoveNode(&(pgr->List),(OSlwToolDListNodeSTU *)(*ppGP));

					if(!((*ppGP)->pmem->Free((*ppGP)->pmem,(*ppGP))))//����ͷ�ʧ��
					{

							(*ppGP)=p;
							return p;

					}
			}
			 
		}
		(*ppGP)=p;
    return *ppGP;
}

//�𽥷��� �����ڴ������ƴ���
#if 0
//------------------------------------------
//<������>OSlwGiftTransmitIdleIndex</������>
//<����˵��>�õ������ʵ�Ա����</����˵��>
//<����˵��>pgt:this</����˵��>
//<���˵��>�����ʵ�Ա��ID �������-1��ʾû�п���</���˵��>
//------------------------------------------
OSlwGiftPostmanSTU * OSlwGiftTransmitIdle(OSlwGiftTransmitSTU *pgt)
{

    lw_u64 sta=pgt->PostmanFlag.all;

    lw_8 n=0;

    while(((1<<n)&sta) && n<OSLW_GIFT_POSTMAN_MAX) n++;//ѭ���ж��ʵ�Ա ����ж��������� �����ҵ��� ��ֹͣѭ��

    return n<OSLW_GIFT_POSTMAN_MAX? (pgt->PostmanList+n):NULL;

}
#endif


//------------------------------------------
//<������>OSlwGiftAllocPostman</������>
//<����˵��>��������ʵ�Ա</����˵��>
//<����˵��>pmem:�ڴ���亯��</����˵��>
//<���˵��>NUL��ʾû��</���˵��>
//------------------------------------------
OSlwGiftPostmanSTU * OSlwGiftAllocPostman(OSlwMemoryBasicSTU *pmem)
{

    OSlwGiftPostmanSTU *pgp;

    OSLW_assert(!pmem);

    pgp=(OSlwGiftPostmanSTU *)pmem->Malloc(pmem,sizeof(OSlwGiftPostmanSTU));

    if(!pgp)
    {
        return pgp;
    }

    pgp->pmem=pmem;
    pgp->Method=GiftPostmanStatus_Received;


    return pgp;

}

#endif // !(OSLW_SIMPLE_LEVEL >= 3)

#if OSLW_SIMPLE_LEVEL ==3

void * OSlwGiftReceiveMoveNext(OSlwToolDListNodeConnectSTU *pgr)
{
	OSlwToolDListNodeConnectSTU *p;
	OSlwMemoryBasicSTU *pmem;
	if(pgr->pLast == NULL || pgr->pNext == NULL)
	{
		return NULL;
	}
	
	p=pgr->pNext;
	pmem=(OSlwMemoryBasicSTU *)(p->pLast);
	
	if(pgr->pLast == pgr->pNext)//ֻҪһ����Ϣ
	{
		
		pgr->pLast=NULL;
		pgr->pNext=NULL;
		pmem->Free(pmem,p);
		
		return NULL;
	}
	else
	{
		pgr->pNext=p->pNext;
		pmem->Free(pmem,p);
		return 	pgr->pNext;	
	}
	
	
//	return NULL;
}

#endif


#endif
