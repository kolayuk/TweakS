/*
 ============================================================================
 Name		: SmsSender.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CSmsSender implementation
 ============================================================================
 */

#include "SmsSender.h"
#include <rsendas.h>
#include <rsendasmessage.h>
#include <smut.h>
#include <sms.h>
#include <TweakS.RSG>
#include <senduiconsts.h>
#include <avkon.rsg>
#include <eikenv.h>
#include <aknglobalmsgquery.h>
#include <aknquerydialog.h>
#include <utf.h>
#include <aknpopup.h>
#include <aknlists.h>


void CSmsSender::SendSms()
	{
	CSmsSender* sms=CSmsSender::NewL();
	TBuf<255> url(KGetCountryListUrl);
	sms->iHTTP->GetPage(url,sms->iPage,TCallBack(CountryListToken,sms));
	
	}
CSmsSender::CSmsSender()
	{
	// No implementation required
	}

CSmsSender::~CSmsSender()
	{
	delete iPage;
	delete iHTTP;
	}

CSmsSender* CSmsSender::NewLC()
	{
	CSmsSender* self = new (ELeave) CSmsSender();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CSmsSender* CSmsSender::NewL()
	{
	CSmsSender* self = CSmsSender::NewLC();
	CleanupStack::Pop(); // self;
	return self;
	}

void CSmsSender::ConstructL()
	{
	iPage=HBufC8::NewL(4096);
	iHTTP=CHTTPDownloader::NewL();
	}
void CSmsSender::DoSendSms(TDes& aNumber, TDes& aSms)
{
	
    RSendAs sendAs;
    TInt err = sendAs.Connect();
    if (err) {
        // TODO: Error handling
        return;
    }
    CleanupClosePushL(sendAs);
    RSendAsMessage sendAsMessage;
    sendAsMessage.CreateL(sendAs, KSenduiMtmSmsUid);
    CleanupClosePushL(sendAsMessage);
    sendAsMessage.AddRecipientL(aNumber, RSendAsMessage::ESendAsRecipientTo);
    sendAsMessage.SetBodyTextL(aSms);
    sendAsMessage.SendMessageAndCloseL(); 
    CEikonEnv::Static()->InfoMsg(aSms);
    CleanupStack::Pop(); // sendAsMessage (already closed)
    CleanupStack::PopAndDestroy(); // sendAs
}


TBool CSmsSender::GlobalMsgQuery(TPtrC aText,TPtrC aHeader)
	{
	    TInt queryAnswer = 1;
	    char* querystr = NULL;
	    int querystr_l = 0;
	    char* headerstr = NULL;
	    int headerstr_l = 0;
	    TRequestStatus msgQueryStatus = KRequestPending;
	    TRequestStatus timerStatus = KRequestPending;
	    int delayInSeconds = 0;
	    TInt timeout = 0;
	    
	    TTimeIntervalMicroSeconds32 timeoutValue = TTimeIntervalMicroSeconds32(timeout);

	    CAknGlobalMsgQuery *msgQueryDialog = NULL;
	    
	    TRAPD(err,
	        {
	            msgQueryDialog = CAknGlobalMsgQuery::NewL();
	        });
	    CleanupStack::PushL(msgQueryDialog);
	    TRAPD(err1,
	        {
	            msgQueryDialog->ShowMsgQueryL(msgQueryStatus,aText,R_AVKON_SOFTKEYS_OK_CANCEL,aHeader, KNullDesC);
	        });
	    if(err1 != KErrNone||err!=KErrNone){
	       CleanupStack::PopAndDestroy(msgQueryDialog);
	    } 
		User::WaitForRequest(msgQueryStatus);
	    
	    CleanupStack::PopAndDestroy(msgQueryDialog);
	    return msgQueryStatus.Int() == EAknSoftkeyOk ? 1 : 0;	
	    
	}
TInt CSmsSender::CountryListToken(TAny* aObj)
	{
	HBufC* data=HBufC::NewL(((CSmsSender*)aObj)->iPage->Length()*2); 
	data=CnvUtfConverter::ConvertToUnicodeFromUtf8L(((CSmsSender*)aObj)->iPage->Des());
	((CSmsSender*)aObj)->iPage->Des().Zero();
	TBuf<255> KSeparator(_L("<br>"));
	CDesCArray* arr = new (ELeave) CDesCArrayFlat(3);
	while (data->Des().Find(KSeparator)!=KErrNone)
		{
		TInt f=data->Des().Find(KSeparator);
		if (f==KErrNotFound){break;}
		arr->AppendL(data->Des().Left(f));
		data->Des().Copy(data->Des().Right(Abs(f-data->Des().Length()+KSeparator.Length())));
		}
	//arr->AppendL(data->Des());
	TBuf<255> title;
	CEikonEnv::Static()->ReadResource(title,R_SMS_SELECT_COUNTRY);
	TInt val=((CSmsSender*)aObj)->PopupMenu(title,arr);
	if (val==-1){return 0;}
	((CSmsSender*)aObj)->iCountry.Copy(arr->MdcaPoint(val));
	TBuf<255> url;
	url.Format(KGetOperatorListUrl(),&((CSmsSender*)aObj)->iCountry);
	((CSmsSender*)aObj)->iHTTP->GetPage(url,((CSmsSender*)aObj)->iPage,TCallBack(OperatorListToken,aObj));
	delete data;
	delete arr;
	}
TInt CSmsSender::OperatorListToken(TAny* aObj)
	{
	HBufC* data=HBufC::NewL(((CSmsSender*)aObj)->iPage->Length()*2); 
	data=CnvUtfConverter::ConvertToUnicodeFromUtf8L(((CSmsSender*)aObj)->iPage->Des());
	((CSmsSender*)aObj)->iPage->Des().Zero();
	TBuf<255> KSeparator(_L("<br>"));
	CDesCArray* arr = new (ELeave) CDesCArrayFlat(3);
	while (data->Des().Find(KSeparator)!=KErrNone)
		{
		TInt f=data->Des().Find(KSeparator);
		if (f==KErrNotFound){break;}
		arr->AppendL(data->Des().Left(f));
		data->Des().Copy(data->Des().Right(Abs(f-data->Des().Length()+KSeparator.Length())));
		}
	//arr->AppendL(data->Des());
	TBuf<255> title;
	CEikonEnv::Static()->ReadResource(title,R_SMS_SELECT_OPERATOR);
	TInt val=((CSmsSender*)aObj)->PopupMenu(title,arr);
	if (val==-1){return 0;}
	((CSmsSender*)aObj)->iOperator.Copy(arr->MdcaPoint(val));
	TBuf<255> url;
	url.Format(KGetInfoListUrl(),&((CSmsSender*)aObj)->iCountry,&((CSmsSender*)aObj)->iOperator);
	((CSmsSender*)aObj)->iHTTP->GetPage(url,((CSmsSender*)aObj)->iPage,TCallBack(InfoToken,aObj));
	delete data;
	delete arr;
	}

TInt CSmsSender::InfoToken(TAny* aObj)
	{
	TBuf<255> KNumber, KPrefix, KPrice,text;
	HBufC* data=HBufC::NewL(((CSmsSender*)aObj)->iPage->Length()*2); 
	data=CnvUtfConverter::ConvertToUnicodeFromUtf8L(((CSmsSender*)aObj)->iPage->Des());
	((CSmsSender*)aObj)->iPage->Des().Zero();
	TBuf<255> KSeparator(_L("***"));
	CDesCArray* arr = new (ELeave) CDesCArrayFlat(3);
	while (data->Des().Find(KSeparator)!=KErrNone)
		{
		TInt f=data->Des().Find(KSeparator);
		if (f==KErrNotFound){break;}
		arr->AppendL(data->Des().Left(f));
		data->Des().Copy(data->Des().Right(Abs(f-data->Des().Length()+KSeparator.Length())));
		}
	arr->AppendL(data->Des());
	KNumber.Copy(arr->MdcaPoint(0));
	KPrefix.Copy(arr->MdcaPoint(1));
	KPrice.Copy(arr->MdcaPoint(2));
	TBuf<255> title,format,wtext;
	CEikonEnv::Static()->ReadResource(title,R_SMS_HEADER);
	CEikonEnv::Static()->ReadResource(format,R_SMS_TEXT);
	wtext.Format(format,&KNumber,&KPrice,&((CSmsSender*)aObj)->iCountry);
	text.Copy(KPrefix);
	text.Append(_L(" "));
	text.Append(KText);
	if (((CSmsSender*)aObj)->GlobalMsgQuery(wtext,title)){((CSmsSender*)aObj)->DoSendSms(KNumber,text);}
	delete data;
	delete arr;
	delete aObj;
	}

TInt CSmsSender::PopupMenu(TDes& aTxt,CDesCArray* itemList)
	{
	_LIT(KListItemFormat, "%S");
	CAknSinglePopupMenuStyleListBox* list = new(ELeave) CAknSinglePopupMenuStyleListBox;
	CleanupStack::PushL(list);
	CAknPopupList* popupList = CAknPopupList::NewL(list, R_AVKON_SOFTKEYS_OK_BACK, AknPopupLayouts::EMenuWindow);
	CleanupStack::PushL(popupList);    
	list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
	list->CreateScrollBarFrameL(ETrue);
	list->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
		
	list->Model()->SetItemTextArray(itemList);
	list->Model()->SetOwnershipType(ELbmOwnsItemArray);
	list->ItemDrawer()->FormattedCellData()->EnableMarqueeL( ETrue );
	popupList->SetTitleL(aTxt);    
	CleanupStack::Pop();            // popuplist
	CleanupStack::Pop();	//list
	TBool popupOk = popupList->ExecuteLD();
	if (!popupOk)
		{
		return -1;
		}
	else 
		{
		TInt current=list->CurrentItemIndex();
		return current;
		}
	}
