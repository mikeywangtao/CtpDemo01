#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "TickToKlineHelper.h"

#include "boost\lexical_cast.hpp"

using namespace std;

// ���ӿ�
#pragma comment (lib, "thostmduserapi.lib")
#pragma comment (lib, "thosttraderapi.lib")

// ---- ȫ�ֱ��� ---- //
// ��������
TThostFtdcBrokerIDType gBrokerID = "9999";                         // ģ�⾭���̴���
//TThostFtdcInvestorIDType gInvesterID = "";                         // Ͷ�����˻���
//TThostFtdcPasswordType gInvesterPassword = "";                     // Ͷ��������
//TThostFtdcInvestorIDType gInvesterID = ""; //"098923";                         // Ͷ�����˻���
//TThostFtdcPasswordType gInvesterPassword = ""; //"qweasdzxc1974";                     // Ͷ��������
TThostFtdcInvestorIDType gInvesterID = "098923";                         // Ͷ�����˻���
TThostFtdcPasswordType gInvesterPassword = "qweasdzxc1974";                     // Ͷ��������

// �������
CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // ����ָ��
//char gMdFrontAddr[] = "tcp://180.168.146.187:10031";               // ģ������ǰ�õ�ַ
char gMdFrontAddr1[] = "tcp://180.168.146.187:10010";               // ģ������ǰ�õ�ַ
char gMdFrontAddr2[] = "tcp://180.168.146.187:10011";               // ģ������ǰ�õ�ַ
char gMdFrontAddr3[] = "tcp://218.202.237.33:10012";               // ģ������ǰ�õ�ַ
//char *g_pInstrumentID[] = {"TF1706", "zn1705", "cs1801", "CF705"}; // �����Լ�����б��С��ϡ���֣��������ѡһ��
//int instrumentNum = 4;                                             // �����Լ��������
char *g_pInstrumentID[] = { "rb1801" }; // �����Լ�����б��С��ϡ���֣��������ѡһ��
int instrumentNum = 1;                                             // �����Լ��������
unordered_map<string, TickToKlineHelper> g_KlineHash;              // ��ͬ��Լ��k�ߴ洢��

// ���ײ���
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // ����ָ��
//char gTradeFrontAddr[] = "tcp://180.168.146.187:10030";            // ģ�⽻��ǰ�õ�ַ
char gTradeFrontAddr1[] = "tcp://180.168.146.187:10000";            // ģ�⽻��ǰ�õ�ַ
char gTradeFrontAddr2[] = "tcp://180.168.146.187:10001";            // ģ�⽻��ǰ�õ�ַ
char gTradeFrontAddr3[] = "tcp://218.202.237.33:10001";            // ģ�⽻��ǰ�õ�ַ
//TThostFtdcInstrumentIDType g_pTradeInstrumentID = "zn1705";        // �����׵ĺ�Լ����
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "rb1801";        // �����׵ĺ�Լ����
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // ��������
TThostFtdcPriceType gLimitPrice = 2; //22735;                           // ���׼۸�


int main()
{
	// �˺�����
	//cout << "�������˺ţ� ";
	//scanf("%s", gInvesterID);
	//cout << "���������룺 ";
	//scanf("%s", gInvesterPassword);

	//���� boost
	int i = 8848;
	char *mystr = "2013";
	i = boost::lexical_cast<int>(mystr);
	cout << "boost TypeTre:" << i << endl;












	// ��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // ��������ʵ��
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;       // ��������ص�ʵ��
	g_pMdUserApi->RegisterSpi(pMdUserSpi);               // ע���¼���
	g_pMdUserApi->RegisterFront(gMdFrontAddr1);           // ��������ǰ�õ�ַ
	g_pMdUserApi->RegisterFront(gMdFrontAddr2);           // ��������ǰ�õ�ַ
  g_pMdUserApi->RegisterFront(gMdFrontAddr3);           // ��������ǰ�õ�ַ
	g_pMdUserApi->Init();                                // ��������
	
	// �ȵ��߳��˳�
	g_pMdUserApi->Join();
	delete pMdUserSpi;
	g_pMdUserApi->Release();

	/*
	// ��ʼ�������߳�
	cout << "��ʼ������..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // ��������ʵ��
	//CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;
	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;               // �������׻ص�ʵ��
	g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // ע���¼���
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // ���Ĺ�����
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // ����˽����
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr1);              // ���ý���ǰ�õ�ַ
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr2);              // ���ý���ǰ�õ�ַ
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr3);              // ���ý���ǰ�õ�ַ
	g_pTradeUserApi->Init();                                      // ��������
	
	// �ȵ��߳��˳�
	g_pTradeUserApi->Join();
	delete pTradeSpi;
	g_pTradeUserApi->Release();
	*/
	// ת������k������
	//TickToKlineHelper tickToKlineHelper;
	//tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");
	
	getchar();
	return 0;
}