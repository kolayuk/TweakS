/*
 * ============================================================================
 *  Name     : CClientEngine of ClientEngine.cpp
 *  Part of  : HTTP Client Example
 *  Created  : 06/20/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#include <avkon.hrh>
#include <aknnotewrappers.h>
#include <uri8.h>
#include <http.h>
#include <chttpformencoder.h>
#include <HttpStringConstants.h>
#include <http\RHTTPTransaction.h>
#include <http\RHTTPSession.h>
#include <http\RHTTPHeaders.h>


#include <COMMDB.H> 		//Communications database 
#include <CDBPREFTABLE.H>	//Connection Preferences table
#include <CommDbConnPref.h>

#include "ClientEngine.h"
#include <aknlists.h>
#include <bautils.h>
#include <utf.h>
#include <uriutils.h>
#include <TweakSAppUi.h>
#include <centralrepository.h>


//_LIT8(KUserAgent, "SimpleClient 1.0");

// This client accepts all content types.
// (change to e.g. "text/plain" for plain text only)
_LIT8(KAccept, "*/*");

const TInt KStatustextBufferSize = 32;
const TInt KInfotextBufferSize = 64;
const TInt KURIBufferSize = 128;
const TInt KDefaultBufferSize = 255;


_LIT(KUser,"");
_LIT(KPassword,"");


_LIT(KRunError, "MHFRunError: %d");
_LIT(KUnrecognisedEvent, "Unrecognised event: %d");
_LIT(KErrorStr, "Error: %d");
_LIT(KTransactionFailed, "Transaction Failed");
_LIT(KTransactionSuccessful, "Transaction Successful");
_LIT(KTransactionComplete, "Transaction Complete");
_LIT(KBodyReceived,"Body received");
_LIT(KBodyPartReceived, "%d bytes received... ");
_LIT(KHeaderReceived, "Header received. Status: %d %S");
_LIT(KTransactionCancelled, "Transaction cancelled");
_LIT(KConnecting,"Connecting...");



 



CHTTPDownloader::CHTTPDownloader(): MClientObserver()
	{
	}
CHTTPDownloader::~CHTTPDownloader()
	{
	delete iClient;
	delete iData;
	//delete iIdle;
	}
CHTTPDownloader* CHTTPDownloader::NewL()
	{
	CHTTPDownloader* self = CHTTPDownloader::NewLC();
	return self;
	}
CHTTPDownloader* CHTTPDownloader::NewLC()
	{
	CHTTPDownloader* self = new (ELeave) CHTTPDownloader();
	self->ConstructL();
	return self;
	}
void CHTTPDownloader::ConstructL()
	{
	iSize=0;
	iData=HBufC8::NewL(1024);
	iClient=CClientEngine::NewL(*this);
	iEnd=EFalse;
	
	}
void CHTTPDownloader::ClientBodyReceived(const TDesC8& aBodyData,TInt aLength)
	{
	iSize=iSize+aLength;
		if (iType==EDownloadFile)
				{
				iFile.Write(aBodyData);
				}
		else if (iType==EDownloadPage)
			{
			iData=iData->ReAlloc(iSize);
			iData->Des().Append(aBodyData.Ptr(),aLength);
			}
	}
void CHTTPDownloader::ClientEvent(const TDesC& aEventDescription)
	{
#ifdef _DEBUG
	RDebug::Print(aEventDescription);
#endif
	CEikonEnv::Static()->InfoMsg(aEventDescription);
	if (aEventDescription==KTransactionSuccessful){Complete();}
	}
void CHTTPDownloader::GetPage(TDes& aUrl,HBufC8* aPageData,TCallBack aCallBack)
	{
	iData->Des().Zero();
	aPageData->Des().Zero();
	aPageData->Des().Delete(0,aPageData->Des().Length());
	iClient->IssueHTTPGetL(aUrl);
	iType=EDownloadPage;
	iPageData=aPageData;
	iCallBack=aCallBack;
	}
void CHTTPDownloader::DownloadFile(TDes& aUrl,TDes& aFileName,TCallBack aCallBack)
	{
	iClient->IssueHTTPGetL(aUrl);
	iType=EDownloadFile;
	iFileName=aFileName;
	iFile.Replace(CEikonEnv::Static()->FsSession(),iFileName,EFileWrite);
	iCallBack=aCallBack;
	}
void CHTTPDownloader::Complete()
	{
	
	if (iType==EDownloadPage)
		{
			
			iPageData->Des().Zero();
			//iPageData=iPageData->ReAlloc(iData->Length());
			iPageData->Des().Copy(*iData);
		}
	else if (iType==EDownloadFile)
		{
		iFile.Close();
		}
	iCallBack.CallBack();
	}
void CHTTPDownloader::Cancel()
	{
		iClient->CancelTransaction();
		if (iType==EDownloadFile)
			{
			iFile.Close();
			}
		//if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),iFileName)){BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),iFileName);}
	}


// ----------------------------------------------------------------------------
// CClientEngine::NewL()
//
// Creates instance of CClientEngine.
// ----------------------------------------------------------------------------
CClientEngine* CClientEngine::NewL(MClientObserver& aObserver)
	{
    CClientEngine* self = CClientEngine::NewLC(aObserver);
    CleanupStack::Pop(self);
    return self;
	}


// ----------------------------------------------------------------------------
// CClientEngine::NewLC()
//
// Creates instance of CClientEngine.
// ----------------------------------------------------------------------------
CClientEngine* CClientEngine::NewLC(MClientObserver& aObserver)
	{
    CClientEngine* self = new (ELeave) CClientEngine(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
	}


// ----------------------------------------------------------------------------
// CClientEngine::CClientEngine()
//
// First phase constructor.
// ----------------------------------------------------------------------------
CClientEngine::CClientEngine(MClientObserver& aObserver)
:	iObserver(aObserver),
	iPostData(NULL),
	iRunning(EFalse)
	{
	}


// ----------------------------------------------------------------------------
// CClientEngine::~CClientEngine()
//
// Destructor.
// ----------------------------------------------------------------------------
CClientEngine::~CClientEngine()
	{	
	iSession.Close();

    // and finally close handles
    iConnection.Close();
    iSocketServ.Close();

	delete iPostData;
	}


// ----------------------------------------------------------------------------
// CClientEngine::ConstructL()
//
// Second phase construction.
// ----------------------------------------------------------------------------
void CClientEngine::ConstructL()
	{
	iConnectionSetupDone=EFalse;
	// Open RHTTPSession with default protocol ("HTTP/TCP")
	TRAPD(err, iSession.OpenL());
	if(err != KErrNone) 
		{
		// Most common error; no access point configured, and session creation
		// leaves with KErrNotFound.
		_LIT(KErrMsg,
			"Cannot create session. Is internet access point configured?");
		_LIT(KExitingApp, "Exiting app.");
		CEikonEnv::Static()->InfoWinL(KErrMsg, KExitingApp);
		User::Leave(err);
		}

	// Install this class as the callback for authentication requests. When
	// page requires authentication the framework calls GetCredentialsL to get
	// user name and password.
	InstallAuthenticationL(iSession);

	}


// ----------------------------------------------------------------------------
// CClientEngine::SetHeaderL()
//
// Used to set header value to HTTP request
// ----------------------------------------------------------------------------
void CClientEngine::SetHeaderL(RHTTPHeaders aHeaders,
							 TInt aHdrField,
							 const TDesC8& aHdrValue)
	{
	RStringF valStr = iSession.StringPool().OpenFStringL(aHdrValue);
	CleanupClosePushL(valStr);
	THTTPHdrVal val(valStr);
	aHeaders.SetFieldL(iSession.StringPool().StringF(aHdrField,
		RHTTPSession::GetTable()), val);
	CleanupStack::PopAndDestroy(); // valStr
	}


// ----------------------------------------------------------------------------
// CClientEngine::IssueHTTPGetL()
//
// Start a new HTTP GET transaction.
// ----------------------------------------------------------------------------
void CClientEngine::IssueHTTPGetL(const TDesC& aUri)
	{
	if (!iConnectionSetupDone)
		{	
			TInt iap;
			if (((CTweakSAppUi*)CEikonEnv::Static()->AppUi())->iSettings[0]==-1)
				{iap=SelectIAP();}
			else
				{iap=((CTweakSAppUi*)CEikonEnv::Static()->AppUi())->iSettings[0];}
			if (iap==-1){return;}
			if (!SetupConnectionL(iap)){return;}
		}
		
	// Parse string to URI (as defined in RFC2396)
	CUri8* uriPtr= UriUtils::CreateUriL(aUri);
	TUriC8 uri=uriPtr->Uri();

	// Get request method string for HTTP GET
	RStringF method = iSession.StringPool().StringF(HTTP::EGET,
		RHTTPSession::GetTable());

	// Open transaction with previous method and parsed uri. This class will
	// receive transaction events in MHFRunL and MHFRunError.
	iTransaction = iSession.OpenTransactionL(uri, *this, method);
	
	TBuf8<255> KUserAgent;
	TBuf<255> KUserAgentR;
	CRepository* CR=CRepository::NewL(TUid::Uid(0x101f8731));
	CR->Get(0x2,KUserAgentR);
	delete CR;
	KUserAgent.Copy(KUserAgentR);
	
	// Set headers for request; user agent and accepted content type
	RHTTPHeaders hdr = iTransaction.Request().GetHeaderCollection();
	SetHeaderL(hdr, HTTP::EUserAgent, KUserAgent);
	SetHeaderL(hdr, HTTP::EAccept, KAccept);

	// Submit the transaction. After this the framework will give transaction
	// events via MHFRunL and MHFRunError.
	iTransaction.SubmitL();

	iRunning = ETrue;
	iObserver.ClientEvent(KConnecting);
	}


// ----------------------------------------------------------------------------
// CClientEngine::IssueHTTPPostL()
//
// Start a new HTTP POST transaction.
// ----------------------------------------------------------------------------
void CClientEngine::IssueHTTPPostL(const TDesC8& aUri,
								 const TDesC8& aContentType,
								 const TDesC8& aBody)
	{
	SetupConnectionL(SelectIAP());	
		
	// Parse string to URI
	TUriParser8 uri;
	uri.Parse(aUri);

	// Copy data to be posted into member variable; iPostData is used later in
	// methods inherited from MHTTPDataSupplier.
	delete iPostData;
	iPostData = aBody.AllocL();

	// Get request method string for HTTP POST
	RStringF method = iSession.StringPool().StringF(HTTP::EPOST,
		RHTTPSession::GetTable());

	// Open transaction with previous method and parsed uri. This class will
	// receive transaction events in MHFRunL and MHFRunError.
	iTransaction = iSession.OpenTransactionL(uri, *this, method);

	
	_LIT(KFilename,"Z:\\resource\\versions\\model.txt");
		RFile file;
		file.Open(CCoeEnv::Static()->FsSession(),KFilename,EFileRead);
		TFileText text;
		text.Set(file);
		TBuf16<128> szModelName;
		text.Read(szModelName);
		
		TBuf8<255> KUserAgent;
		KUserAgent.Copy(szModelName);
	
	// Set headers for request; user agent, accepted content type and body's
	// content type.
	RHTTPHeaders hdr = iTransaction.Request().GetHeaderCollection();
	SetHeaderL(hdr, HTTP::EUserAgent, KUserAgent);
	SetHeaderL(hdr, HTTP::EAccept, KAccept);
	SetHeaderL(hdr, HTTP::EContentType, aContentType);

	// Set this class as an data supplier. Inherited MHTTPDataSupplier methods
	// are called when framework needs to send body data.
	MHTTPDataSupplier* dataSupplier = this;
	iTransaction.Request().SetBody(*dataSupplier);

	// Submit the transaction. After this the framework will give transaction
	// events via MHFRunL and MHFRunError.
	iTransaction.SubmitL();

	iRunning = ETrue;
	iObserver.ClientEvent(KConnecting);
	}

// ----------------------------------------------------------------------------
// CClientEngine::CancelTransaction()
//
// Cancels currently running transaction and frees resources related to it.
// ----------------------------------------------------------------------------
void CClientEngine::CancelTransaction()
	{
	if(!iRunning)
		return;

	// Close() also cancels transaction (Cancel() can also be used but
	// resources allocated by transaction must be still freed with Close())
	iTransaction.Close();

	// Not running anymore
	iRunning = EFalse;
	iObserver.ClientEvent(KTransactionCancelled);
	}


// ----------------------------------------------------------------------------
// CClientEngine::MHFRunL()
//
// Inherited from MHTTPTransactionCallback
// Called by framework to pass transaction events.
// ----------------------------------------------------------------------------
void CClientEngine::MHFRunL(RHTTPTransaction aTransaction,
						  const THTTPEvent& aEvent)
	{
	switch (aEvent.iStatus)
		{
		case THTTPEvent::EGotResponseHeaders:
			{
			// HTTP response headers have been received. Use
			// aTransaction.Response() to get the response. However, it's not
			// necessary to do anything with the response when this event occurs.

			// Get HTTP status code from header (e.g. 200)
			RHTTPResponse resp = aTransaction.Response();
			TInt status = resp.StatusCode();

			// Get status text (e.g. "OK")
			TBuf<KStatustextBufferSize> statusText;
			statusText.Copy(resp.StatusText().DesC());

			TBuf<KDefaultBufferSize> text;
			text.Format(KHeaderReceived, status, &statusText);
			iObserver.ClientEvent(text);
			}
			break;

		case THTTPEvent::EGotResponseBodyData:
			{
			// Part (or all) of response's body data received. Use
			// aTransaction.Response().Body()->GetNextDataPart() to get the actual
			// body data.
	
			// Get the body data supplier
			MHTTPDataSupplier* body = aTransaction.Response().Body();
			TPtrC8 dataChunk;

			// GetNextDataPart() returns ETrue, if the received part is the last
			// one.
			TBool isLast = body->GetNextDataPart(dataChunk);
			iObserver.ClientBodyReceived(dataChunk,dataChunk.Length());
			TBuf<KInfotextBufferSize> text;
			text.Format(KBodyPartReceived, dataChunk.Length());
			iObserver.ClientEvent(text);

			// NOTE: isLast may not be ETrue even if last data part received.
			// (e.g. multipart response without content length field)
			// Use EResponseComplete to reliably determine when body is completely
			// received.
			if (isLast)
				{
				iObserver.ClientEvent(KBodyReceived);
				}

			// Always remember to release the body data.
			body->ReleaseData();
			}
			break;

		case THTTPEvent::EResponseComplete:
			{
			// Indicates that header & body of response is completely received.
			// No further action here needed.
			iObserver.ClientEvent(KTransactionComplete);
			}
			break;

		case THTTPEvent::ESucceeded:
			{
			// Indicates that transaction succeeded.
			iObserver.ClientEvent(KTransactionSuccessful);

			// Transaction can be closed now. It's not needed anymore.
			aTransaction.Close();
			iRunning = EFalse;
			}
			break;

		case THTTPEvent::EFailed:
			{
			// Transaction completed with failure.
			iObserver.ClientEvent(KTransactionFailed);
			aTransaction.Close();
			iRunning = EFalse;
			}
			break;

		default:
			// There are more events in THTTPEvent, but they are not usually
			// needed. However, event status smaller than zero should be handled
			// correctly since it's error.
			{
			TBuf<KInfotextBufferSize> text;
			if (aEvent.iStatus < 0)
				{
				text.Format(KErrorStr, aEvent.iStatus);
				// Just close the transaction on errors
				aTransaction.Close();
				iRunning = EFalse;
				} 
			else 
				{
				// Other events are not errors (e.g. permanent and temporary
				// redirections)
				text.Format(KUnrecognisedEvent, aEvent.iStatus);
				}
			iObserver.ClientEvent(text);
			}
			break;
		}
	}


// ----------------------------------------------------------------------------
// CClientEngine::MHFRunError()
//
// Inherited from MHTTPTransactionCallback
// Called by framework when *leave* occurs in handling of transaction event.
// These errors must be handled, or otherwise HTTP-CORE 6 panic is thrown.
// ----------------------------------------------------------------------------
TInt CClientEngine::MHFRunError(TInt aError,
							  RHTTPTransaction /*aTransaction*/,
							  const THTTPEvent& /*aEvent*/)
	{
	// Just notify about the error and return KErrNone.
	TBuf<KInfotextBufferSize>	text;
	text.Format(KRunError, aError);
	iObserver.ClientEvent(text);
	return KErrNone;
	}


// ----------------------------------------------------------------------------
// CClientEngine::GetNextDataPart()
//
// Inherited from MHTTPDataSupplier
// Called by framework when next part of the body is needed. In this
// this provides data for HTTP post.
// ----------------------------------------------------------------------------
TBool CClientEngine::GetNextDataPart(TPtrC8& aDataPart)
	{
	if(iPostData)
		{
		// Provide pointer to next chunk of data (return ETrue, if last chunk)
		// Usually only one chunk is needed, but sending big file could require
		// loading the file in small parts.
		aDataPart.Set(iPostData->Des());
		}
	return ETrue;
	}


// ----------------------------------------------------------------------------
// CClientEngine::ReleaseData()
//
// Inherited from MHTTPDataSupplier
// Called by framework. Allows us to release resources needed for previous
// chunk. (e.g. free buffers)
// ----------------------------------------------------------------------------
void CClientEngine::ReleaseData()
	{
	// It's safe to delete iPostData now.
	delete iPostData;
	iPostData = NULL;
	}

// ----------------------------------------------------------------------------
// CClientEngine::Reset()
//
// Inherited from MHTTPDataSupplier
// Called by framework to reset the data supplier. Indicates to the data
// supplier that it should return to the first part of the data.
// In practise an error has occured while sending data, and framework needs to
// resend data.
// ----------------------------------------------------------------------------
TInt CClientEngine::Reset()
	{
	// Nothing needed since iPostData still exists and contains all the data.
	// (If a file is used and read in small parts we should seek to beginning
	// of file and provide the first chunk again in GetNextDataPart() )
	return KErrNone;
	}


// ----------------------------------------------------------------------------
// CClientEngine::OverallDataSize()
//
// Inherited from MHTTPDataSupplier
// Called by framework. We should return the expected size of data to be sent.
// If it's not know we can return KErrNotFound (it's allowed and does not cause
// problems, since HTTP protocol allows multipart bodys without exact content
// length in header).
// ----------------------------------------------------------------------------
TInt CClientEngine::OverallDataSize()
	{
	if(iPostData)
		return iPostData->Length();
	else
		return KErrNotFound ;
	}

// ----------------------------------------------------------------------------
// CClientEngine::GetCredentialsL()
//
// Inherited from MHTTPAuthenticationCallback
// Called by framework when we requested authenticated page and framework
// needs to know username and password.
// ----------------------------------------------------------------------------
TBool CClientEngine::GetCredentialsL(const TUriC8& aURI,
								   RString aRealm,
								   RStringF aAuthenticationType,
								   RString& aUsername,
								   RString& aPassword)
	{
	// aURI, aReal and aAuthenticationType are informational only. We only need
	// to set aUsername and aPassword and return ETrue, if aUsername and
	// aPassword are provided by user.

	// Informational only
	TBuf<KURIBufferSize> authType;
	TBuf<KURIBufferSize> uri;
	TBuf<KDefaultBufferSize> authText;
	authType.Copy(aAuthenticationType.DesC());
	uri.Copy(aURI.UriDes());
	_LIT(KAuthRequired, "%S requires %S authentication.");
	authText.Format(KAuthRequired, &uri, &authType);
	_LIT(KAuthNote, "Authentication required.");
	CEikonEnv::Static()->InfoWinL(KAuthNote, authText);

	// Query user name and password
	TBuf<KDefaultBufferSize> userName(KUser);
	TBuf<KDefaultBufferSize> password(KPassword);

	// Set aUsername and aPassword
	TBuf8<KDefaultBufferSize> temp;
	temp.Copy(userName);
	TRAPD(err, aUsername = aRealm.Pool().OpenStringL(temp));
	if (!err)
		{
		temp.Copy(password);
		TRAP(err, aPassword = aRealm.Pool().OpenStringL(temp));
		if (!err) return ETrue;
		}

	// Return ETrue if user has given credentials (username and password),
	// otherwise EFlase
	return EFalse;
	}
	
// ----------------------------------------------------------------------------
// CClientEngine::SetupConnectionL()
//
// The method set the internet access point and connection setups.
// ----------------------------------------------------------------------------	
TInt CClientEngine::SetupConnectionL(TInt aID)
    {
    
    iConnectionSetupDone = ETrue;
    TRAPD(err,{
    //open socket server and start the connection
    User::LeaveIfError(iSocketServ.Connect());
    User::LeaveIfError(iConnection.Open(iSocketServ));
    };);
    if (err!=KErrNone){return 0;}
	TUint32 iapID = aID; 
	// Now we have the iap Id. Use it to connect for the connection.
	// Create a connection preference variable.
	TCommDbConnPref connectPref;

	// setup preferences 
	connectPref.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	connectPref.SetDirection(ECommDbConnectionDirectionUnknown);
	connectPref.SetBearerSet(ECommDbBearerGPRS);
	//Sets the CommDb ID of the IAP to use for this connection
	connectPref.SetIapId(iapID);
    
	TRAPD(err1,{
	    User::LeaveIfError(iConnection.Start(connectPref));
	    };);
	    if (err1!=KErrNone){return 0;}
	
    //set the sessions connection info
    RStringPool strPool = iSession.StringPool();
    RHTTPConnectionInfo connInfo = iSession.ConnectionInfo();
    
    //to use our socket server and connection
    connInfo.SetPropertyL ( strPool.StringF(HTTP::EHttpSocketServ,
        RHTTPSession::GetTable() ), THTTPHdrVal (iSocketServ.Handle()) );

    connInfo.SetPropertyL ( strPool.StringF(HTTP::EHttpSocketConnection,
        RHTTPSession::GetTable() ), 
        THTTPHdrVal (REINTERPRET_CAST(TInt, &(iConnection))) );
    return 1;
    }

TInt CClientEngine::SelectIAP()
{
	CArrayFixFlat<TIapData>* iEApList=new (ELeave) CArrayFixFlat<TIapData>(2) ;
	TInt stack=0;
	// Make listitems. and PUSH it
	CAknSinglePopupMenuStyleListBox* list = new(ELeave) CAknSinglePopupMenuStyleListBox;
	CleanupStack::PushL(list);stack++; 
 
	// Create popup list and PUSH it.
	CAknPopupList* popupList = CAknPopupList::NewL(list,
		R_AVKON_SOFTKEYS_OK_CANCEL, AknPopupLayouts::EMenuWindow);
	CleanupStack::PushL(popupList);stack++; 
 
	CDesCArrayFlat* items = new (ELeave) CDesCArrayFlat(5);
	CleanupStack::PushL(items);stack++; 
	// initialize listbox.
	list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
	list->CreateScrollBarFrameL(ETrue);
	list->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,
		CEikScrollBarFrame::EAuto);
 
 
	TBuf<52> iapfromtable;
	TInt err = KErrNone;
 
	CCommsDatabase* iCommsDB=CCommsDatabase::NewL(EDatabaseTypeIAP);
	CleanupStack::PushL(iCommsDB);stack++; 
	CCommsDbTableView* gprsTable = iCommsDB->OpenIAPTableViewMatchingBearerSetLC(
		ECommDbBearerGPRS|ECommDbBearerWLAN|ECommDbBearerVirtual,
		ECommDbConnectionDirectionOutgoing); 

	User::LeaveIfError(gprsTable->GotoFirstRecord());
	TInt i=0;
	TUint32 id;
	TIapData eap;	
 
	TInt cur =0; //current value
	do
	{
		gprsTable->ReadTextL(TPtrC(COMMDB_NAME), iapfromtable);
		gprsTable->ReadUintL(TPtrC(COMMDB_ID), id);
		items->AppendL(iapfromtable);
		eap.iIap = id;
		eap.iName.Copy(iapfromtable);
		iEApList->AppendL(eap);
 
		err = gprsTable->GotoNextRecord();
		i++;
	}
	while (err == KErrNone);
	CleanupStack::PopAndDestroy(2); stack--; 
 
	// Set listitems.
	CTextListBoxModel* model = list->Model();
	model->SetItemTextArray(items);
	model->SetOwnershipType(ELbmOwnsItemArray);
	CleanupStack::Pop();    
 
	popupList->SetTitleL(_L("Select access point"));
	list->SetListBoxObserver(popupList);
	TInt popupOk = popupList->ExecuteLD();
	CleanupStack::Pop();    
	TInt iap=0;
	if (popupOk)
	{	
		TInt index = list->CurrentItemIndex();
		iap=(*iEApList)[index].iIap;
	}
	else {iap=-1;}
	CleanupStack::PopAndDestroy();  
	iEApList->Reset();
	delete iEApList;
	return iap;
}
