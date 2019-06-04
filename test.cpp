#include "test.h"


void test_order(void)
{
	
  extern TThostFtdcBrokerIDType brokerid;		// Ӧ�õ�Ԫ
  extern TThostFtdcUserIDType userId;		// Ͷ���ߴ���
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
  
	cout <<"����������Ϣ "<<"["<< test<<"]" <<endl ;
	cout <<"["<< test<<"]"<<"brokerId="<< brokerid <<endl ;
	cout <<"["<< test<<"]"<<"userId="<< userId <<endl ;
	cout <<"["<< test<<"]"<<"passwd="<< passwd <<endl ;
	cout <<"["<< test<<"]"<<"appId="<< appID <<endl ;
	cout <<"["<< test<<"]"<<"authCode="<< AuthCode <<endl ;
	cout <<"["<< test<<"]"<<"tradeFront="<< tradeFront <<endl ;
	
  //��ʼ��UserApi
  CThostFtdcTraderApi* pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi("./tmp/");
  CtpTraderSpi* pUserSpi = new CtpTraderSpi(pUserApi);
  pUserApi->RegisterSpi((CThostFtdcTraderSpi*)pUserSpi);			// ע���¼���
  pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);					// ע�ṫ����
  pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);			  // ע��˽����
  pUserApi->RegisterFront(tradeFront);							// ע�ύ��ǰ�õ�ַ
    
  cout <<"���� ��ʼ���� "<< test <<  "��... "<<endl ;
  pUserApi->Init();  
  ShowTraderCommand(pUserSpi,true); 
  
  pUserApi->Join();  
  //pUserApi->Release();
}



void main(int argc, const char* argv[]){
  g_hEvent=CreateEvent(NULL, true, false, NULL); 

  test_order();
 
}