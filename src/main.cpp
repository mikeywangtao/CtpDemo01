#include <iostream>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include "CustomMdSpi.h"
#include "CustomTradeSpi.h"
#include "TickToKlineHelper.h"

#include "boost\lexical_cast.hpp"

using namespace std;

// 链接库
#pragma comment (lib, "thostmduserapi.lib")
#pragma comment (lib, "thosttraderapi.lib")

// ---- 全局变量 ---- //
// 公共参数
TThostFtdcBrokerIDType gBrokerID = "9999";                         // 模拟经纪商代码
//TThostFtdcInvestorIDType gInvesterID = "";                         // 投资者账户名
//TThostFtdcPasswordType gInvesterPassword = "";                     // 投资者密码
//TThostFtdcInvestorIDType gInvesterID = ""; //"098923";                         // 投资者账户名
//TThostFtdcPasswordType gInvesterPassword = ""; //"qweasdzxc1974";                     // 投资者密码
TThostFtdcInvestorIDType gInvesterID = "098923";                         // 投资者账户名
TThostFtdcPasswordType gInvesterPassword = "qweasdzxc1974";                     // 投资者密码

// 行情参数
CThostFtdcMdApi *g_pMdUserApi = nullptr;                           // 行情指针
//char gMdFrontAddr[] = "tcp://180.168.146.187:10031";               // 模拟行情前置地址
char gMdFrontAddr1[] = "tcp://180.168.146.187:10010";               // 模拟行情前置地址
char gMdFrontAddr2[] = "tcp://180.168.146.187:10011";               // 模拟行情前置地址
char gMdFrontAddr3[] = "tcp://218.202.237.33:10012";               // 模拟行情前置地址
//char *g_pInstrumentID[] = {"TF1706", "zn1705", "cs1801", "CF705"}; // 行情合约代码列表，中、上、大、郑交易所各选一种
//int instrumentNum = 4;                                             // 行情合约订阅数量
char *g_pInstrumentID[] = { "rb1801" }; // 行情合约代码列表，中、上、大、郑交易所各选一种
int instrumentNum = 1;                                             // 行情合约订阅数量
unordered_map<string, TickToKlineHelper> g_KlineHash;              // 不同合约的k线存储表

// 交易参数
CThostFtdcTraderApi *g_pTradeUserApi = nullptr;                    // 交易指针
//char gTradeFrontAddr[] = "tcp://180.168.146.187:10030";            // 模拟交易前置地址
char gTradeFrontAddr1[] = "tcp://180.168.146.187:10000";            // 模拟交易前置地址
char gTradeFrontAddr2[] = "tcp://180.168.146.187:10001";            // 模拟交易前置地址
char gTradeFrontAddr3[] = "tcp://218.202.237.33:10001";            // 模拟交易前置地址
//TThostFtdcInstrumentIDType g_pTradeInstrumentID = "zn1705";        // 所交易的合约代码
TThostFtdcInstrumentIDType g_pTradeInstrumentID = "rb1801";        // 所交易的合约代码
TThostFtdcDirectionType gTradeDirection = THOST_FTDC_D_Sell;       // 买卖方向
TThostFtdcPriceType gLimitPrice = 2; //22735;                           // 交易价格


int main()
{
	// 账号密码
	//cout << "请输入账号： ";
	//scanf("%s", gInvesterID);
	//cout << "请输入密码： ";
	//scanf("%s", gInvesterPassword);

	//测试 boost
	int i = 8848;
	char *mystr = "2013";
	i = boost::lexical_cast<int>(mystr);
	cout << "boost TypeTre:" << i << endl;

	// 初始化行情线程
	cout << "初始化行情..." << endl;
	g_pMdUserApi = CThostFtdcMdApi::CreateFtdcMdApi();   // 创建行情实例
	CThostFtdcMdSpi *pMdUserSpi = new CustomMdSpi;       // 创建行情回调实例
	g_pMdUserApi->RegisterSpi(pMdUserSpi);               // 注册事件类
	g_pMdUserApi->RegisterFront(gMdFrontAddr1);           // 设置行情前置地址
	g_pMdUserApi->RegisterFront(gMdFrontAddr2);           // 设置行情前置地址
  g_pMdUserApi->RegisterFront(gMdFrontAddr3);           // 设置行情前置地址
	g_pMdUserApi->Init();                                // 连接运行
	
	// 等到线程退出
	g_pMdUserApi->Join();
	delete pMdUserSpi;
	g_pMdUserApi->Release();

	/*
	// 初始化交易线程
	cout << "初始化交易..." << endl;
	g_pTradeUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(); // 创建交易实例
	//CThostFtdcTraderSpi *pTradeSpi = new CustomTradeSpi;
	CustomTradeSpi *pTradeSpi = new CustomTradeSpi;               // 创建交易回调实例
	g_pTradeUserApi->RegisterSpi(pTradeSpi);                      // 注册事件类
	g_pTradeUserApi->SubscribePublicTopic(THOST_TERT_RESTART);    // 订阅公共流
	g_pTradeUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);   // 订阅私有流
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr1);              // 设置交易前置地址
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr2);              // 设置交易前置地址
	g_pTradeUserApi->RegisterFront(gTradeFrontAddr3);              // 设置交易前置地址
	g_pTradeUserApi->Init();                                      // 连接运行
	
	// 等到线程退出
	g_pTradeUserApi->Join();
	delete pTradeSpi;
	g_pTradeUserApi->Release();
	*/
	// 转换本地k线数据
	//TickToKlineHelper tickToKlineHelper;
	//tickToKlineHelper.KLineFromLocalData("market_data.csv", "K_line_data.csv");
	
	getchar();
	return 0;
}