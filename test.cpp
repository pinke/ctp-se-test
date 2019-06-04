#include "test.h"


void test_order(void)
{
	
  extern TThostFtdcBrokerIDType brokerid;		// 应用单元
  extern TThostFtdcUserIDType userId;		// 投资者代码
  extern TThostFtdcAppIDType  appID;
  extern TThostFtdcPasswordType	passwd;
  
  extern TThostFtdcAuthCodeType	AuthCode;
  extern TThostFtdcUserProductIDType	UserProductInfo;
  
  char* test = "-----";
  strcpy(test,GetIniKeyString("default", "test","config.ini"," "));
  strcpy(brokerid,GetIniKeyString(test, "brokerId","config.ini"," "));
  strcpy(userId,GetIniKeyString(test, "userId","config.ini"," "));
  strcpy(passwd,GetIniKeyString(test, "passwd","config.ini"," "));
  strcpy(appID,GetIniKeyString(test, "appId","config.ini","  "));
  strcpy(AuthCode,GetIniKeyString(test, "authCode","config.ini"," "));
  strcpy(UserProductInfo,GetIniKeyString(test, "userProductInfo","config.ini",""));
  strcpy(tradeFront,GetIniKeyString(test, "tradeFront","config.ini"," "));
  
	cout <<"连接配置信息 "<<"["<< test<<"]" <<endl ;
	cout <<"["<< test<<"]"<<"brokerId="<< brokerid <<endl ;
	cout <<"["<< test<<"]"<<"userId="<< userId <<endl ;
	cout <<"["<< test<<"]"<<"passwd="<< passwd <<endl ;
	cout <<"["<< test<<"]"<<"appId="<< appID <<endl ;
	cout <<"["<< test<<"]"<<"authCode="<< AuthCode <<endl ;
	cout <<"["<< test<<"]"<<"tradeFront="<< tradeFront <<endl ;
	
  //初始化UserApi
  CThostFtdcTraderApi* pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi("./tmp/");
  CtpTraderSpi* pUserSpi = new CtpTraderSpi(pUserApi);
  pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// 注册事件类
  pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);					// 注册公有流
  pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);			  // 注册私有流
  pUserApi->RegisterFront(tradeFront);							// 注册交易前置地址
    
  cout <<"连接 初始化中 "<< test <<  "中... "<<endl ;
  pUserApi->Init();  
  ShowTraderCommand(pUserSpi,true); 
  
  pUserApi->Join();  
  //pUserApi->Release();
}



void main(int argc, const char* argv[]){
  g_hEvent=CreateEvent(NULL, true, false, NULL); 

  test_order();
 
}