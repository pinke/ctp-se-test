#ifndef TEST_H_
#define TEST_H_

#include "config.h"
#include "api/trade/win/public/ThostFtdcTraderApi.h"
#include "order/traderspi.h"
#include "windows.h"
#include <iostream>
using namespace std;

HANDLE g_hEvent;

void Menu(){
	cerr << "-----------------------------------------------" << endl;
	cerr << "[10] auth                      -- ��֤" << endl;
	cerr << "[11] Submit                      -- �ϴ�������Ϣ" << endl;
	cerr << " [1] ReqUserLogin              -- ��¼" << endl;
	cerr << " [2] ReqSettlementInfoConfirm  -- ���㵥ȷ��" << endl;
	cerr << " [3] ReqQryInstrument          -- ��ѯ��Լ" << endl;
	cerr << " [4] ReqQryTradingAccount      -- ��ѯ�ʽ�" << endl;
	cerr << " [5] ReqQryInvestorPosition    -- ��ѯ�ֲ�" << endl;
	cerr << " [6] ReqOrderInsert            -- ����" << endl;
	cerr << " [7] ReqOrderAction            -- ����" << endl;
	cerr << " [8] PrintOrders               -- ��ʾ����" << endl;
	cerr << " [9] PrintOrders               -- ��ʾ�ɽ�" << endl;
	cerr << " [99] Menu		              -- ��ʾ�˵�" << endl;
	cerr << " [0] Exit                      -- �˳�" << endl;
	cerr << "----------------------------------------------" << endl;
}


char *GetIniKeyString(char *title, char *key, char *filename, char* defVal)
{
	//cout <<" GetIniKeyString "<< title <<"|"<< key <<"|"<< filename <<"|"<< defVal << endl;
	FILE *fp = NULL;
	int  flag = 0;
	char sTitle[32], *wTmp;
	static char sLine[1024];

	sprintf(sTitle, "[%s]", title);
	if (NULL == (fp = fopen(filename, "r"))) {
		fclose(fp);
		cout << "�޷���config.ini" << endl;
		perror("fopen");
		return defVal;
	}
	else {

		//cout<<"start found "<< key <<endl;
		while (NULL != fgets(sLine, 1024, fp)) {
			// ����ע����
			if (0 == strncmp("//", sLine, 2)) continue;
			if ('#' == sLine[0])              continue;
			if ('\n' == sLine[0]) continue;
			if ('\r' == sLine[0]) continue;

			wTmp = strchr(sLine, '=');
			if ((NULL != wTmp) && (1 == flag)) {
				if (0 == strncmp(key, sLine, wTmp - sLine)) { // �������ļ���ȡ��Ϊ׼
					sLine[strlen(sLine) - 1] = '\0';
					fclose(fp);
					//		cout<<"Found value of title :"<< sLine <<" of "<< sTitle <<"=>"<< key <<endl;
					return wTmp + 1;
				}
			}
			else {
				if (0 == strncmp(sTitle, sLine, strlen(sLine) - 1)) { // �������ļ���ȡ��Ϊ׼
					//cout<<"Found title :" << sLine <<" of "<< sTitle <<"=>"<< key <<endl;
					flag = 1; // �ҵ�����λ��
					continue;
				}
			}
			if (flag == 1 && '[' == sLine[0]) {
				//cout<<"Found next title :"<< sLine <<" of "<< sTitle <<"=>"<< key <<endl;
				return defVal;

			}
		}
	}
	fclose(fp);
	return defVal;
}
void ShowTraderCommand(CtpTraderSpi* p, bool print = false){
	if (print){
		Menu();
	}

	extern TThostFtdcBrokerIDType brokerid;		// Ӧ�õ�Ԫ
	extern TThostFtdcUserIDType userId;		// Ͷ���ߴ���
	extern TThostFtdcAppIDType  appID;
	extern TThostFtdcPasswordType	passwd;
	extern bool	connected;



	TThostFtdcInstrumentIDType instId;
	TThostFtdcDirectionType dir;
	TThostFtdcCombOffsetFlagType kpp;
	TThostFtdcPriceType price;
	TThostFtdcVolumeType vol;
	TThostFtdcSequenceNoType orderSeq;

	char* cc = "0";
	int cmd = atoi(cc);
	while (true){
		cin >> cc;
		cmd = atoi(cc);
		if (!connected){
			cout << "��û�����Ϸ�����,���Ժ�..." << endl;
		}
		else{
			cout << " ��������� " << cmd << "(" << cc << ")" << endl;
			break;
		}
	}
		switch (cmd){
		case 10:
		{
				   p->ReqAuth();
				   break;
		}
		case 99:
		{
				   Menu();
				   break;
		}
		case 11:
		{
				   p->ReqSubmit();
				   break;
		}
		case 1: {
					p->ReqUserLogin(brokerid, userId, passwd); break;
		}
		case 2: p->ReqSettlementInfoConfirm(); break;
		case 3: {
					cerr << " ��Լ > "; cin >> instId;
					p->ReqQryInstrument(instId); break;
		}
		case 4: p->ReqQryTradingAccount(); break;
		case 5: {
					cerr << " ��Լ > "; cin >> instId;
					p->ReqQryInvestorPosition(instId); break;
		}
		case 6: {
					cerr << " ��Լ > "; cin >> instId;
					cerr << " ���� > "; cin >> dir;
					cerr << " ��ƽ > "; cin >> kpp;
					cerr << " �۸� > "; cin >> price;
					cerr << " ���� > "; cin >> vol;
					p->ReqOrderInsert(instId, dir, kpp, price, vol); break;
		}
		case 7: {
					cerr << " ��� > "; cin >> orderSeq;
					p->ReqOrderAction(orderSeq); break;
		}
		case 8: p->PrintOrders(); break;
		case 9: p->PrintTrades(); break;
		case 0: exit(0);
		} 
	WaitForSingleObject(g_hEvent, INFINITE);
	ResetEvent(g_hEvent);
	ShowTraderCommand(p);
}
#endif