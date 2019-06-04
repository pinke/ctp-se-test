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
	cerr << "[10] auth                      -- 认证" << endl;
	cerr << "[11] Submit                      -- 上传报送信息" << endl;
	cerr << " [1] ReqUserLogin              -- 登录" << endl;
	cerr << " [2] ReqSettlementInfoConfirm  -- 结算单确认" << endl;
	cerr << " [3] ReqQryInstrument          -- 查询合约" << endl;
	cerr << " [4] ReqQryTradingAccount      -- 查询资金" << endl;
	cerr << " [5] ReqQryInvestorPosition    -- 查询持仓" << endl;
	cerr << " [6] ReqOrderInsert            -- 报单" << endl;
	cerr << " [7] ReqOrderAction            -- 撤单" << endl;
	cerr << " [8] PrintOrders               -- 显示报单" << endl;
	cerr << " [9] PrintOrders               -- 显示成交" << endl;
	cerr << " [99] Menu		              -- 显示菜单" << endl;
	cerr << " [0] Exit                      -- 退出" << endl;
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
		cout << "无法打开config.ini" << endl;
		perror("fopen");
		return defVal;
	}
	else {

		//cout<<"start found "<< key <<endl;
		while (NULL != fgets(sLine, 1024, fp)) {
			// 这是注释行
			if (0 == strncmp("//", sLine, 2)) continue;
			if ('#' == sLine[0])              continue;
			if ('\n' == sLine[0]) continue;
			if ('\r' == sLine[0]) continue;

			wTmp = strchr(sLine, '=');
			if ((NULL != wTmp) && (1 == flag)) {
				if (0 == strncmp(key, sLine, wTmp - sLine)) { // 长度依文件读取的为准
					sLine[strlen(sLine) - 1] = '\0';
					fclose(fp);
					//		cout<<"Found value of title :"<< sLine <<" of "<< sTitle <<"=>"<< key <<endl;
					return wTmp + 1;
				}
			}
			else {
				if (0 == strncmp(sTitle, sLine, strlen(sLine) - 1)) { // 长度依文件读取的为准
					//cout<<"Found title :" << sLine <<" of "<< sTitle <<"=>"<< key <<endl;
					flag = 1; // 找到标题位置
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

	extern TThostFtdcBrokerIDType brokerid;		// 应用单元
	extern TThostFtdcUserIDType userId;		// 投资者代码
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
			cout << "还没连接上服务器,请稍后..." << endl;
		}
		else{
			cout << " 你输入的是 " << cmd << "(" << cc << ")" << endl;
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
					cerr << " 合约 > "; cin >> instId;
					p->ReqQryInstrument(instId); break;
		}
		case 4: p->ReqQryTradingAccount(); break;
		case 5: {
					cerr << " 合约 > "; cin >> instId;
					p->ReqQryInvestorPosition(instId); break;
		}
		case 6: {
					cerr << " 合约 > "; cin >> instId;
					cerr << " 方向 > "; cin >> dir;
					cerr << " 开平 > "; cin >> kpp;
					cerr << " 价格 > "; cin >> price;
					cerr << " 数量 > "; cin >> vol;
					p->ReqOrderInsert(instId, dir, kpp, price, vol); break;
		}
		case 7: {
					cerr << " 序号 > "; cin >> orderSeq;
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