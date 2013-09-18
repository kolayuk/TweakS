/*
 ============================================================================
 Name		: SmsSender.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CSmsSender declaration
 ============================================================================
 */

#ifndef SMSSENDER_H
#define SMSSENDER_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <ClientEngine.h>
#include <bamdesca.h>
//URLs
_LIT(KGetCountryListUrl,"http://kolaysoft.ru/sms/get_info.php?get=countries");
_LIT(KGetOperatorListUrl,"http://kolaysoft.ru/sms/get_info.php?get=operators&country=%S");
_LIT(KGetInfoListUrl,"http://kolaysoft.ru/sms/get_info.php?get=info&country=%S&operator=%S");
_LIT(KText,"Thanks from TweakS");
// CLASS DECLARATION
class CSmsSender : public CBase
	{
public:
	~CSmsSender();
	static CSmsSender* NewL();
	static CSmsSender* NewLC();
	static void SendSms();
	TBool iSmsDialogActive;
	void DoSendSms(TDes& aNumber, TDes& aText);
	static TInt CountryListToken(TAny* aObj);
	static TInt OperatorListToken(TAny* aObj);
	static TInt InfoToken(TAny* aObj);
	TBool GlobalMsgQuery(TPtrC aText,TPtrC aHeader);
	TBuf<512> iCountry;
	TBuf<512> iOperator;
	CHTTPDownloader* iHTTP;
	TInt PopupMenu(TDes& aTxt,CDesCArray* itemList);
	HBufC8* iPage;
private:
	CSmsSender();
	void ConstructL();
	};

#endif // SMSSENDER_H
