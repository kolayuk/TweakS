/*
========================================================================
 Name        : PluginsListView.cpp
 Author      : Kolay
 Copyright   : TweakS - it is a tweaker for Symbian OS
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <TweakS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "TweakS.hrh"
#include "PluginsListView.h"
#include "PluginsList.hrh"
#include "ListOfSettings.hrh"
#include "PluginsManager.hrh"
#include "SettingList.hrh"
#include "AddingPlugin.hrh"
#include "PluginsList.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]


#include <const.h>
#include <TweakSAppUi.h>
#include <ListOfSettingsView.h>
#include <BAUTILS.H>
#include <aknglobalmsgquery.h>
#include <hlplch.h>
#include <ClientEngine.h>
#include <textutils.h>
#include <aknwaitdialog.h>
#include <documenthandler.h>
#include <APGCLI.H>
#include <logger.h>
#include <SmsSender.h>
#include <FileSelectDialog.h>
#include <ListOfSettings.h>
void CPluginsListView::ReadPlugins()
	{
	if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),KPluginsDir))
		{
		CEikonEnv::Static()->FsSession().MkDirAll(KPluginsDir);
		}
	CDir* results=NULL;
	TFindFile findFiles(CEikonEnv::Static()->FsSession());
	findFiles.FindWildByDir(KIniMask,KPluginsDir,results);

	TInt i;
	TBuf<255> fn;
	TBuf<255> temp;
	RFile filesave;
	TFileText ft;

	if (results==NULL){return;}
	for (i=0; i<results->Count();i++)
		{
		TPluginDescription descr;
		temp.Zero();
		fn.Zero();
		descr.iName.Zero();
		descr.iDescription.Zero();
		
		fn.Copy(KPluginsDir);
		fn.Append(((TEntry)(*results)[i]).iName);
		
		filesave.Open(CEikonEnv::Static()->FsSession(),fn,EFileRead);
		ft.Set(filesave);
		ft.Read(descr.iName);
		ft.Read(descr.iDescription);
		ft.Read(temp);
		filesave.Close();
		TLex conv(temp);
		conv.Val(descr.iUid,EHex);
		
		TBuf<255> a;
		a.Append(KPluginsDir);
		a.Append(temp);
		a.Append(KCREExtension);
		if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),a)){BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),a,KCREPath);BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),a);}
		
		iPlugins->AppendL(descr);
		}
	}

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CPluginsListView::CPluginsListView(): MProgressDialogCallback()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iPluginsList = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CPluginsListView::~CPluginsListView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iPluginsList;
	iPluginsList = NULL;
	// ]]] end generated region [Generated Contents]
	delete iPlugins;
	//delete iHTTP;
	delete iVersion; 
	delete iWait;
	delete iVersionInfo;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CPluginsListView
 */
CPluginsListView* CPluginsListView::NewL()
	{
	CPluginsListView* self = CPluginsListView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CPluginsListView
 */
CPluginsListView* CPluginsListView::NewLC()
	{
	CPluginsListView* self = new ( ELeave ) CPluginsListView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CPluginsListView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_PLUGINS_LIST_PLUGINS_LIST_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	iFirstActivation=ETrue;
	iPos=0; iTop=0;	
	}

TDateTime CPluginsListView::ParseDateTime(TDes& aDate,TDes& aTime)
	{
	TDateTime newD;
	TBuf<1> s; s.Copy(_L(" "));
		CDesCArray* ArrD=CTextUtils::Split16(aDate,s);
		s.Copy(_L(":"));
		CDesCArray* ArrT=CTextUtils::Split16(aTime,s);
		
		TBuf<3> m=ArrD->MdcaPoint(0);
		TMonth month;
		if (m.Compare(_L("Jan"))==0){month=EJanuary;}
		else if (m.Compare(_L("Feb"))==0){month=EFebruary;}
		else if (m.Compare(_L("Mar"))==0){month=EMarch;}
		else if (m.Compare(_L("Apr"))==0){month=EApril;}
		else if (m.Compare(_L("May"))==0){month=EMay;}
		else if (m.Compare(_L("Jun"))==0){month=EJune;}
		else if (m.Compare(_L("Jul"))==0){month=EJuly;}
		else if (m.Compare(_L("Aug"))==0){month=EAugust;}
		else if (m.Compare(_L("Sep"))==0){month=ESeptember;}
		else if (m.Compare(_L("Oct"))==0){month=EOctober;}
		else if (m.Compare(_L("Nov"))==0){month=ENovember;}
		else if (m.Compare(_L("Dec"))==0){month=EDecember;}
		RArray<TInt> RArrT,RArrD;
		TLex conv1,conv2;
		for (TInt i=0;i<ArrD->Count();i++)
			{
			RDebug::Print(ArrD->MdcaPoint(i));
			conv1.Assign(ArrD->MdcaPoint(i));
			conv2.Assign(ArrT->MdcaPoint(i));
			TInt t,d;
			conv1.Val(d);
			conv2.Val(t);
			RArrD.Append(d);
			RArrT.Append(t);
			}
		newD.Set(RArrD[2],month,RArrD[1],RArrT[0],RArrT[1],RArrT[2],0);
		delete ArrD; delete ArrT;
		return newD;
	}

TInt CPluginsListView::CheckVersionAuto(TAny* aObj)
	{
	TBuf<20> currVerDate;
	TBuf<20> currVerTime;
	TBuf<20> newVerTime;
	TBuf<20> newVerDate;
	
	HBufC* data=CTextUtils::Des8To16(((CPluginsListView*)aObj)->iVersion);
	currVerDate.Copy(KBuildDate);
	if (currVerDate[4]==32){currVerDate[4]=48;}
	currVerTime.Copy(KBuildTime);
	TBuf<512> buf; buf.Copy(data->Des());
	TBuf<1> separator(_L("|"));
	CDesCArray* arr=CTextUtils::Split16(buf,separator);
	newVerDate.Copy(arr->MdcaPoint(0));
	newVerTime.Copy(arr->MdcaPoint(1));
	delete arr;
	
	_LOG(_L("AutoUpdate CheckVer"));
	_LOG(_L("Current: "));
	_LOG(currVerDate);
	_LOG(currVerTime);
	_LOG(_L("Server: "));
	_LOG(newVerDate);
	_LOG(newVerTime);
	
	TDateTime currD; TTime currT; 
	TDateTime newD; TTime newT;
	
	currD=ParseDateTime(currVerDate,currVerTime);
	newD=ParseDateTime(newVerDate,newVerTime);
	
	_LOG(_L("Server:"));
	_LOGDATA(_L("Secs: %d"),newD.Second());
	_LOGDATA(_L("Min: %d"),newD.Minute());
	_LOGDATA(_L("Hour: %d"),newD.Hour());
	_LOGDATA(_L("Day: %d"),newD.Day());
	_LOGDATA(_L("Month: %d"),newD.Month()+1);
	_LOGDATA(_L("Year: %d"),newD.Year());
	
	_LOG(_L("Current:"));
	_LOGDATA(_L("Sec: %d"),currD.Second());
	_LOGDATA(_L("Min: %d"),currD.Minute());
	_LOGDATA(_L("Hour: %d"),currD.Hour());
	_LOGDATA(_L("Day: %d"),currD.Day()+1);
	_LOGDATA(_L("Month: %d"),currD.Month()+1);
	_LOGDATA(_L("Year: %d"),currD.Year());
	
	newT=TTime(newD);
	currT=TTime(currD);
	TBuf<50> a;
	TTimeIntervalSeconds secsFrom;
	newT.SecondsFrom(currT,secsFrom);
	a.Num(secsFrom.Int());

	_LOGDATA(_L("Seconds to: %d"),secsFrom.Int());

	CEikonEnv::Static()->InfoMsg(a);
	User::After(1000000);
	if (secsFrom.Int()>60*30)
		{
		//update nedeed
		TBuf<255> url;
		url.Copy(KVersionInfoURL);
		((CPluginsListView*)aObj)->iVersion->Des().Zero();
		((CPluginsListView*)aObj)->iHTTP->GetPage(url,((CPluginsListView*)aObj)->iVersionInfo,TCallBack(GetVersionInfo,aObj));
		}
	}

void CPluginsListView::HandleLBSelect()
	{
	if (iPluginsList->ListBox()->Model()->NumberOfItems()!=0)
		{
	TInt i=iPluginsList->ListBox()->CurrentItemIndex();
	iPos=i;
	iTop=iPluginsList->ListBox()->TopItemIndex();
	((CListOfSettingsView*)(((CTweakSAppUi*)AppUi())->View(TUid::Uid(EListOfSettingsViewId))))->Active(iPlugins->At(i).iUid,iPlugins->At(i).iName);
	AppUi()->ActivateLocalViewL(TUid::Uid(EListOfSettingsViewId));
		}
	}

/**
 * @return The UID for this view
 */
TUid CPluginsListView::Id() const
	{
	return TUid::Uid( EPluginsListViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CPluginsListView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	TBuf<255> url;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		case EPluginsListView_MoreApps:
			url.Copy(_L("http://store.ovi.com/content/116079"));
			OpenBrowser(url);
			break;
		case EPluginsListView_MenuItemCommand:
			commandHandled = Handle_MenuItemSelectedL( aCommand );
			break;
		case EPluginsListView_MenuItem8Command:
			commandHandled = Handle_MenuItem6SelectedL( aCommand );
			break;
		case EPluginsListView_MenuItem9Command:
			commandHandled = Handle_MenuItem4SelectedL( aCommand );
			break;
		case EPluginsListView_MenuItem5Command:
			commandHandled = UnlockAll( aCommand );
			break;
		case EPluginsListView_MenuItem12Command:
			commandHandled = Export( aCommand );
			break;
		case EPluginsListView_MenuItem11Command:
			commandHandled = Handle_MenuItem5SelectedL( aCommand );
			break;
		case EPluginsListView_MenuItem10Command:
			commandHandled = Handle_MenuItem3SelectedL( aCommand );
			break;
		case EPluginsListView_MenuItem6Command:
			commandHandled = Handle_MenuItem1SelectedL( aCommand );
			break;
		case EPluginsListView_MenuItem1Command:
			commandHandled = ConnectToDev( aCommand );
			break;
		case EPluginsListView_MenuItem3Command:
			commandHandled = SendSMS( aCommand );
			break;
		case EPluginsListView_MenuItem2Command:
			commandHandled = Handle_MenuItem2SelectedL( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EAknSoftkeyExit )
			{
			AppUi()->HandleCommandL( EEikCmdExit );
			}
	
		}
	// ]]] end generated region [Generated Code]
	
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CPluginsListView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iPluginsList == NULL )
		{
		iPluginsList = CreateContainerL();
		iPluginsList->SetMopParent( this );
		AppUi()->AddToStackL( *this, iPluginsList );
		} 
	// ]]] end generated region [Generated Contents]
	if (iFirstActivation)
		{
		iFirstActivation=EFalse;
		TBuf<255> curd;
		TBuf<255> curt;
		curd.Copy(KBuildDate);
		curt.Copy(KBuildTime);
		curd.Append(_L(" - "));
		curd.Append(curt);
		CEikonEnv::Static()->InfoMsg(curd);
			
		iPlugins=new (ELeave) CArrayFixSeg<TPluginDescription>(1);
		iHTTP=CHTTPDownloader::NewL();
		iVersion=HBufC8::NewL(255);
		iVersionInfo=HBufC8::NewL(5*1024);
			
			
		if (((CTweakSAppUi*)AppUi())->iSettings[1]!=0)
			{
			TBuf<255> url;
			url.Copy(KCheckUpdateURL);
			iVersion->Des().Zero();
			iHTTP->GetPage(url,iVersion,TCallBack(CheckVersionAuto,this));
			}
		}
	iPlugins->Delete(0,iPlugins->Count());
	ReadPlugins();
	iPluginsList->Update();
	if (iPluginsList->ListBox()->Model()->NumberOfItems()!=0)
		{
		iPluginsList->ListBox()->SetTopItemIndex(iTop);
		iPluginsList->ListBox()->SetCurrentItemIndexAndDraw(iPos);
		}
	}

/**
 */
void CPluginsListView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iPluginsList != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iPluginsList );
		delete iPluginsList;
		iPluginsList = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CPluginsListView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	
	// this may fail, but we're not able to propagate exceptions here
	TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}

// [[[ begin generated function: do not modify
void CPluginsListView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_PLUGINS_LIST_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CPluginsListView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CPluginsList::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CPluginsList
 */
CPluginsList* CPluginsListView::CreateContainerL()
	{
	return CPluginsList::NewL( ClientRect(), NULL, this );
	}


				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::Handle_MenuItemSelectedL( TInt aCommand )
	{
	if (iPluginsList->ListBox()->Model()->NumberOfItems()!=0)
		{
		TInt i=iPluginsList->ListBox()->CurrentItemIndex();
		((CListOfSettingsView*)(((CTweakSAppUi*)AppUi())->View(TUid::Uid(EListOfSettingsViewId))))->Active(iPlugins->At(i).iUid,iPlugins->At(i).iName);
		AppUi()->ActivateLocalViewL(TUid::Uid(EListOfSettingsViewId));
		}
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::HandleMenuItemSelectedL( TInt aCommand )
	{
	//plugin info
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::Handle_MenuItem1SelectedL( TInt aCommand )
	{
	//about
	TBuf<500> aboutheader;
	TBuf<500> abouttext;
	CEikonEnv::Static()->ReadResource(abouttext,R_ABOUT_TEXT);
	CEikonEnv::Static()->ReadResource(aboutheader,R_ABOUT_HEADER);
	abouttext.Append(_L("WMR R321502538916\nWMZ Z208634876649\nWMU U221598315212\nWME E234802202031\nYandex: 41001686491180"));
	((CTweakSAppUi*)AppUi())->GlobalMsgQuery(abouttext,aboutheader);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::Handle_MenuItem2SelectedL( TInt aCommand )
	{
	AppUi()->Exit();
	return ETrue;
	}


				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::Handle_MenuItem3SelectedL( TInt aCommand )
	{
	CArrayFix <TCoeHelpContext>* buf = ((CTweakSAppUi*)AppUi())->Help();
	HlpLauncher::LaunchHelpApplicationL(iEikonEnv->WsSession(), buf);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::Handle_MenuItem4SelectedL( TInt aCommand )
	{
	AppUi()->ActivateLocalViewL(TUid::Uid(EPluginsManagerViewId));
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::Handle_MenuItem5SelectedL( TInt aCommand )
	{
	TBuf<255> url;
	url.Copy(KCheckUpdateURL);
	iVersion->Des().Zero();
	iHTTP->GetPage(url,iVersion,TCallBack(CheckVersion,this));
	return ETrue;
	}
TInt CPluginsListView::CheckVersion(TAny* aObj)
	{
	TBuf<20> currVerDate;
	TBuf<20> currVerTime;
	TBuf<20> newVerTime;
	TBuf<20> newVerDate;
	
	HBufC* data=CTextUtils::Des8To16(((CPluginsListView*)aObj)->iVersion);
	
	currVerDate.Copy(KBuildDate);
	if (currVerDate[4]==32){currVerDate[4]=48;}
	currVerTime.Copy(KBuildTime);
	TBuf<512> buf; buf.Copy(data->Des());
	TBuf<1> separator(_L("|"));
	CDesCArray* arr=CTextUtils::Split16(buf,separator);
	newVerDate.Copy(arr->MdcaPoint(0));
	newVerTime.Copy(arr->MdcaPoint(1));
	delete arr;
	
	_LOG(_L("AutoUpdate CheckVer"));
	_LOG(_L("Current: "));
	_LOG(currVerDate);
	_LOG(currVerTime);
	_LOG(_L("Server: "));
	_LOG(newVerDate);
	_LOG(newVerTime);
	
	TDateTime currD; TTime currT; 
	TDateTime newD; TTime newT;
	
	currD=ParseDateTime(currVerDate,currVerTime);
	newD=ParseDateTime(newVerDate,newVerTime);
	
	_LOG(_L("Server:"));
	_LOGDATA(_L("Secs: %d"),newD.Second());
	_LOGDATA(_L("Min: %d"),newD.Minute());
	_LOGDATA(_L("Hour: %d"),newD.Hour());
	_LOGDATA(_L("Day: %d"),newD.Day()+1);
	_LOGDATA(_L("Month: %d"),newD.Month()+1);
	_LOGDATA(_L("Year: %d"),newD.Year());
	
	_LOG(_L("Current:"));
	_LOGDATA(_L("Sec: %d"),currD.Second());
	_LOGDATA(_L("Min: %d"),currD.Minute());
	_LOGDATA(_L("Hour: %d"),currD.Hour());
	_LOGDATA(_L("Day: %d"),currD.Day());
	_LOGDATA(_L("Month: %d"),currD.Month()+1);
	_LOGDATA(_L("Year: %d"),currD.Year());
	
	newT=TTime(newD);
	currT=TTime(currD);
	TBuf<50> a;
	TTimeIntervalSeconds secsFrom;
	newT.SecondsFrom(currT,secsFrom);
	a.Num(secsFrom.Int());

	_LOGDATA(_L("Seconds to: %d"),secsFrom.Int());

	CEikonEnv::Static()->InfoMsg(a);
	User::After(1000000);
	if (secsFrom.Int()>60*30)
		{
		//update nedeed
		TBuf<255> url;
		url.Copy(KVersionInfoURL);
		((CPluginsListView*)aObj)->iVersion->Des().Zero();
		((CPluginsListView*)aObj)->iHTTP->GetPage(url,((CPluginsListView*)aObj)->iVersionInfo,TCallBack(GetVersionInfo,aObj));
		}
	else
		{
		//last version
		TBuf<255> text; TBuf<255> header;
		CEikonEnv::Static()->ReadResource(header,R_UPDATE_HEADER);
		CEikonEnv::Static()->ReadResource(text,R_NO_UPDATE_AVAILABLE);
		if (((CTweakSAppUi*)((CPluginsListView*)aObj)->AppUi())->GlobalMsgQuery(text,header))
			{((CPluginsListView*)aObj)->Download();}
		}
	}

TInt CPluginsListView::GetVersionInfo(TAny* aObj)
	{
	HBufC* data=CTextUtils::Des8To16(((CPluginsListView*)aObj)->iVersionInfo);
	HBufC*text; TBuf<255> header; TBuf<255> temp;
	CEikonEnv::Static()->ReadResource(header,R_UPDATE_HEADER);
	CEikonEnv::Static()->ReadResource(temp,R_UPDATE_AVAILABLE);
	text=HBufC::NewL(data->Length()+255);
	text->Des().Append(temp);
	text->Des().Append(*data);
	if (((CTweakSAppUi*)((CPluginsListView*)aObj)->AppUi())->GlobalMsgQuery(*text,header))
		{
		//download
		((CPluginsListView*)aObj)->Download();
		}
	delete data;
	delete text;
	}
void CPluginsListView::Download()
	{
	TBuf<255> url;
	url.Copy(KDownloadUpdateURL);
	TBuf<255> file(KUpdatePath);
	iWait = new ( ELeave )CAknWaitDialog(reinterpret_cast<CEikDialog**>(&iWait),ETrue);
	iWait->SetCallback(this); 
	isDialogActive=ETrue;
	iWait->ExecuteLD(R_UPDATE_WAIT_DIALOG);
	iHTTP->DownloadFile(url,file,TCallBack(UpdateDownloaded,this));
	}
void CPluginsListView::DialogDismissedL(TInt aButtonId)
	{
	CEikonEnv::Static()->InfoMsg(_L("Dialog canceled"));
	isDialogActive=EFalse;
	if (iHTTP->iClient->IsRunning())
		{
		iHTTP->iClient->CancelTransaction();
		TBuf<255> file(KUpdatePath);
		if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),file)){BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),file);}
		}
	}
TInt CPluginsListView::UpdateDownloaded(TAny* aObj)
	{
	TBuf<255> file(KUpdatePath);
	if (((CPluginsListView*)aObj)->isDialogActive){((CPluginsListView*)aObj)->iWait->ProcessFinishedL();((CPluginsListView*)aObj)->isDialogActive=EFalse;}
	//install and close
	RApaLsSession session;
	User::LeaveIfError(session.Connect());
	CleanupClosePushL(session);
	TUid uid;
	TDataType dataType;
	User::LeaveIfError(session.AppForDocument(file, uid, dataType));
	TThreadId threadId;
	User::LeaveIfError(session.StartDocument(file, dataType, threadId));
	CleanupStack::PopAndDestroy(&session);
	User::Exit(0);
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::Handle_MenuItem6SelectedL( TInt aCommand )
	{
	//settings
	if (((CTweakSAppUi*)AppUi())->iNeedRestart)
		{
			TBuf<255> header(_L("TweakS"));
			TBuf<255> text;
			CEikonEnv::Static()->ReadResource(text,R_SETTING_UNVAILABLE_NEED_RESTART);
			if (((CTweakSAppUi*)AppUi())->GlobalMsgQuery(text,header)){((CListOfSettingsView*)((CTweakSAppUi*)AppUi())->View(TUid::Uid(EListOfSettingsViewId)))->Restart();}
		}
	else
		{AppUi()->ActivateLocalViewL(TUid::Uid(ESettingListViewId));}
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::ConnectToDev( TInt aCommand )
	{
	// TODO: implement selected event handler
	((CTweakSAppUi*)AppUi())->CallBackDialog();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::SendSMS( TInt aCommand )
	{
	CSmsSender::SendSms();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::UnlockAll( TInt aCommand )
	{
	TInt Unlocked=0;
	for (TInt i=0;i<iPlugins->Count();i++)
		{
		TPluginDescription plg=iPlugins->At(i);
		CRepository* iInfoCR=CRepository::NewL(TUid::Uid(plg.iUid));
		TInt NumOfSettings;
		iInfoCR->Get(0x1,NumOfSettings);
		TInt Current;
		for (TInt j=1; j<NumOfSettings+1; j++)
			{
			TSettingData setting;
			Current=i*100;
			iInfoCR->Get(Current+2,setting.iUid);
			iInfoCR->Get(Current+4,setting.iType);
			if (setting.iType!=EPropertyInt&&setting.iType!=EPropertyString16&&setting.iType!=EPropertyString8)
				{Unlocked+=CListOfSettingsView::TestUnlock(setting.iUid);}
			}
		delete iInfoCR;
		}
	_LOGDATA(_L("Unlocked in all plugins: %d"),Unlocked);
	if (Unlocked>0)
		{ 
		TBuf<500> header;
		TBuf<500> text;
		CEikonEnv::Static()->ReadResource(text,R_RESTART_NEEDED_TEXT);
		CEikonEnv::Static()->ReadResource(header,R_RESTART_NEEDED_HEADER);
		if (((CTweakSAppUi*)AppUi())->GlobalMsgQuery(text,header))
			{CListOfSettingsView::Restart();}
		}
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsListView::Export( TInt aCommand )
	{
	CAknSinglePopupMenuStyleListBox* list = new(ELeave) CAknSinglePopupMenuStyleListBox;
	CleanupStack::PushL(list);
	CAknPopupList* popupList = CAknPopupList::NewL(list, R_AVKON_SOFTKEYS_OK_BACK, AknPopupLayouts::EMenuWindow);
	CleanupStack::PushL(popupList);    
	list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
	list->CreateScrollBarFrameL(ETrue);
	list->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
	CDesCArray* itemList=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_EXPORT_TYPES);
	list->Model()->SetItemTextArray(itemList);
	list->Model()->SetOwnershipType(ELbmOwnsItemArray);
	list->ItemDrawer()->FormattedCellData()->EnableMarqueeL( ETrue );   
	CleanupStack::Pop();            // popuplist
	TBool popupOk = popupList->ExecuteLD();
	if (!popupOk)
		{
		return ETrue;
		}
	else 
		{
		TInt current=list->CurrentItemIndex();
		StartExport(current);
		}
	return ETrue;
	}
void CPluginsListView::StartExport(TInt aFullCR)
	{
	if (aFullCR)
		{
		TBuf<255> folderForExport,title(_L("Select folder to export:")),root,mask(_L("*"));
		if(!CFileSelectDialog::RunDlgLD(title,EFolder,root,mask,folderForExport)){return;}
		iFolderToExp.Copy(folderForExport);
		iExportWait = new ( ELeave )CAknWaitDialog(reinterpret_cast<CEikDialog**>(&iExportWait),ETrue); 
		iExportWait->SetCallback(this);
		iExportWait->ExecuteLD(R_EXPORT_WAIT_DIALOG);
		
		if (!iIdle){iIdle=CIdle::NewL(CActive::EPriorityStandard);}
		iIdle->Start(TCallBack(DoExportFull,this));
		}
	else
		{
		CDesC16Array* arr=new (ELeave) CDesC16ArrayFlat(3);
		CArrayFixFlat<TInt>* selection=new (ELeave) CArrayFixFlat<TInt>(3);
		TBuf<255> item; TInt sel=0;
		for (TInt i=0; i<iPlugins->Count();i++)
			{
			item.Copy(_L("\t"));
			item.Append(iPlugins->At(i).iName);
			item.Append(_L("\t"));
			arr->AppendL(item);
			selection->AppendL(i);
			}
		
#ifdef __S60_50__
		CAknListQueryDialog* dlg = new ( ELeave ) CAknListQueryDialog(selection);
		dlg->PrepareLC( R_SISXUI_OPTIONS_QUERY );
		dlg->SetItemTextArray(arr);
		dlg->SetTitleL(_L("Export"));
		dlg->ListBox()->SetSelectionIndexesL(selection);    
	    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
	    ((CEikFormattedCellListBox*)(dlg->ListBox()))->ItemDrawer()->FormattedCellData()->EnableMarqueeL( ETrue );
#else
	    CAknMarkableListDialog* dlg=CAknMarkableListDialog::NewL(sel,selection,arr,R_AVKON_DIALOG_EMPTY_MENUBAR,0,0);
	    dlg->PrepareLC(R_TXT_UID_SELECTION_LIST);
	    dlg->SetTitleL(_L("Export"));
	    ((CEikListBox*)dlg->Control(ESelectionListControl))->SetSelectionIndexesL(selection);
	    ((CAknSingleStyleListBox*)dlg->Control(ESelectionListControl))->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);
#endif
	    TInt popupOk = dlg->RunLD();
		if (!popupOk){return;}
		else
			{
			iPluginsToExp.Reset();
			TBuf<255> folderForExport,title(_L("Select folder to export:")),root,mask(_L("*"));
			if(!CFileSelectDialog::RunDlgLD(title,EFolder,root,mask,folderForExport)){return;}
			iFolderToExp.Copy(folderForExport);
			iExportWait = new ( ELeave )CAknWaitDialog(reinterpret_cast<CEikDialog**>(&iExportWait),ETrue); 
			iExportWait->SetCallback(this);
			iExportWait->ExecuteLD(R_EXPORT_WAIT_DIALOG);
			ReadDataForExport(selection);
			if (!iIdle){iIdle=CIdle::NewL(CActive::EPriorityStandard);}
			iIdle->Start(TCallBack(DoExportPlugins,this));
			}
		}
	}
void CPluginsListView::ReadDataForExport(CArrayFixFlat<TInt>* aArr)
	{
	
	for (TInt i=0;i<aArr->Count();i++)
		{
		_LOGDATA2(_L("Reading data, plugin %d of %d"),i,iPluginsToExp.Count());
		CRepository* iInfoCR=CRepository::NewL(TUid::Uid(iPlugins->At(aArr->At(i)).iUid));
			TInt NumOfSettings;
			iInfoCR->Get(0x1,NumOfSettings);
			
			TInt Current=0;
			TInt Unlocked=0;
			for (TInt j=1; j<NumOfSettings+1; j++)
				{
				TInt uid;
				TSettingData Data;
				Current=j*100;
				iInfoCR->Get(Current+2,uid);
				TKeyArrayFix key(0,ECmpNormal); TInt ind;
				if (iPluginsToExp.Find(TUid::Uid(uid))==KErrNotFound){iPluginsToExp.AppendL(TUid::Uid(uid));}
				_LOGDATA(_L("Iteration %d - ok"),j);
				}
			
		}
	}
TInt CPluginsListView::DoExportPlugins(TAny* aObj)
	{
	RArray<TUid> arri=((CPluginsListView*)aObj)->iPluginsToExp;
	RArray<TUint32> keys;
	for (TInt i=0;i<arri.Count();i++)
		{
				_LOGDATA2(_L("I: %d of %d"),i,arri.Count());
				//get owner
				_LIT(KOwnerName,"[owner]");
				_LIT(KVersionName,"version");
				_LIT(KCenrep,"cenrep");
				_LIT(KDefaultMeta,"[defaultmeta]\n0");
				_LIT(KPlatSec,"[platsec]\n");
				_LIT(KMain,"[Main]");
				_LIT(KStringFormat,"%d string \"%S\" 0 cap_rd=alwayspass cap_wr=alwayspass");
				_LIT(KIntFormat,"%d int %d 0 cap_rd=alwayspass cap_wr=alwayspass");
				_LIT(KRealFormat,"%d int %f 0 cap_rd=alwayspass cap_wr=alwayspass");
				_LIT(KString8Format,"%d string8 \"%S\" 0 cap_rd=alwayspass cap_wr=alwayspass");
				
				TBuf<255> owner;
				TBuf<255> version;
				TBuf<255> txtzpath;
				txtzpath.Copy(KTXTPath);
				txtzpath.AppendNum((TUint)arri[i].iUid,EHex);
				txtzpath.Append(KTXTExtension);
				if (!BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),txtzpath)){continue;}
				_LOGDATA(_L("Path to z-txt file %S"),&txtzpath);			
				TBuf<512> val;
				RFile filesave;
				TFileText ft;
				filesave.Open(CEikonEnv::Static()->FsSession(), txtzpath, EFileRead);
				ft.Set(filesave);
				TBool ownerInNext=EFalse;
				while (ft.Read(val)==KErrNone)
					{
					if (val.Find(KVersionName)!=KErrNotFound){version.Copy(val);}
					if (ownerInNext){owner.Copy(val);break;}
					if (val.Find(KOwnerName)!=KErrNotFound){ownerInNext=ETrue;}
					}
				filesave.Close();
				_LOGDATA(_L("Owner: %S"),&owner);
				_LOGDATA(_L("Version: %S"),&version);
				if (owner.Find(_L("@"))!=KErrNotFound){continue;}
				
				CDesC16Array* arr=new CDesC16ArrayFlat(1);
				TBuf8<2> enc; enc.Append(0xff); enc.Append(0xfe);
				//arr->AppendL(enc);
				arr->AppendL(KCenrep);
				arr->AppendL(version);
				arr->AppendL(KOwnerName);
				arr->AppendL(owner);
				arr->AppendL(KDefaultMeta);
				arr->AppendL(KPlatSec);
				arr->AppendL(KMain);
				TUint uid=arri[i].iUid;
				 
				TRAPD(err,{
						CRepository* CR=CRepository::NewL(TUid::Uid(uid));
						if (CR){delete CR;}
				});
				if (err!=KErrNone){continue;}
				CRepository* CR=CRepository::NewL(TUid::Uid(uid));
				CR->FindL(0,0,keys);
				for (TInt j=0; j<keys.Count();j++)
					{
					TBuf<512> buf;
					TBuf<255> DesVal;
					TBuf8<255> DesVal8;
					TInt IntVal;
					TReal RealVal;
					
					TRAPD(err1,User::LeaveIfError(CR->Get(keys[j],DesVal)));
					TRAPD(err2,User::LeaveIfError(CR->Get(keys[j],IntVal)));
					TRAPD(err3,User::LeaveIfError(CR->Get(keys[j],RealVal)));
					TRAPD(err4,User::LeaveIfError(CR->Get(keys[j],DesVal8)));
					if (err1==KErrNone){buf.Format(KStringFormat(),keys[j],&DesVal);}
					else if (err2==KErrNone){buf.Format(KIntFormat(),keys[j],IntVal);}
					else if (err3==KErrNone){buf.Format(KRealFormat(),keys[j],RealVal);}
					else if (err4==KErrNone){buf.Format(KString8Format(),keys[j],&DesVal8);}
					arr->AppendL(buf);
					}
				delete CR;
				TBuf<512> SavePath;
				SavePath.Copy(((CPluginsListView*)aObj)->iFolderToExp);
				SavePath.Append(_L("TweakS\\"));
				SavePath.AppendNum((TUint)arri[i].iUid,EHex);
				SavePath.Append(KTXTExtension);
				TParse parse;
				CEikonEnv::Static()->FsSession().Parse(SavePath,parse);
				if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
					{CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());}
						
				filesave.Replace(CEikonEnv::Static()->FsSession(),SavePath, EFileWrite);
				filesave.Write(enc);
				ft.Set(filesave);
				for (TInt j=0;j<arr->Count();j++)
					{
					ft.Write(arr->MdcaPoint(j));
					}
				filesave.Close();
				delete arr;
				}
	CPluginsListView* v=((CPluginsListView*)aObj);
	if (v->iExportWait){v->iExportWait->ProcessFinishedL();}
	if (v->iExportWait){delete v->iExportWait;}
	if (v->iIdle) {delete v->iIdle;}
	return 0;
	}

TInt CPluginsListView::DoExportFull(TAny* aObj)
	{
	RArray<TUint32> keys;
	CDir* results=NULL;
	TFindFile findFiles(CEikonEnv::Static()->FsSession());
	_LIT(KMask,"*.txt");
	findFiles.FindWildByDir(KMask,KTXTPath,results);
	
	if (results==NULL){return 1;}
	_LOGDATA(_L("Count: %d"),results->Count());
	for (TInt i=0; i<results->Count();i++)
		{
		_LOGDATA(_L("I: %d"),i);
		//get owner
		_LIT(KOwnerName,"[owner]");
		_LIT(KVersionName,"version");
		_LIT(KCenrep,"cenrep");
		_LIT(KDefaultMeta,"[defaultmeta]\n0");
		_LIT(KPlatSec,"[platsec]\n");
		_LIT(KMain,"[Main]");
		_LIT(KStringFormat,"%d string \"%S\" 0 cap_rd=alwayspass cap_wr=alwayspass");
		_LIT(KIntFormat,"%d int %d 0 cap_rd=alwayspass cap_wr=alwayspass");
		_LIT(KRealFormat,"%d int %f 0 cap_rd=alwayspass cap_wr=alwayspass");
		_LIT(KString8Format,"%d string8 \"%S\" 0 cap_rd=alwayspass cap_wr=alwayspass");
		
		TBuf<255> owner;
		TBuf<255> version;
		TBuf<255> txtzpath;
		txtzpath.Copy(KTXTPath);
		txtzpath.Append(((TEntry)(*results)[i]).iName);
		_LOGDATA(_L("Path to z-txt file %S"),&txtzpath);			
		TBuf<512> val;
		RFile filesave;
		TFileText ft;
		filesave.Open(CEikonEnv::Static()->FsSession(), txtzpath, EFileRead);
		ft.Set(filesave);
		TBool ownerInNext=EFalse;
		while (ft.Read(val)==KErrNone)
			{
			if (val.Find(KVersionName)!=KErrNotFound){version.Copy(val);}
			if (ownerInNext){owner.Copy(val);break;}
			if (val.Find(KOwnerName)!=KErrNotFound){ownerInNext=ETrue;}
			}
		filesave.Close();
		_LOGDATA(_L("Owner: %S"),&owner);
		_LOGDATA(_L("Version: %S"),&version);
		if (owner.Find(_L("@"))!=KErrNotFound){continue;}
		
		CDesC16Array* arr=new CDesC16ArrayFlat(1);
		TBuf8<2> enc; enc.Append(0xff); enc.Append(0xfe);
		//arr->AppendL(enc);
		arr->AppendL(KCenrep);
		arr->AppendL(version);
		arr->AppendL(KOwnerName);
		arr->AppendL(owner);
		arr->AppendL(KDefaultMeta);
		arr->AppendL(KPlatSec);
		arr->AppendL(KMain);
		TUint uid;
		TLex conv(((TEntry)(*results)[i]).iName.Left(8)); conv.Val(uid,EHex);
		TRAPD(err,{
				CRepository* CR=CRepository::NewL(TUid::Uid(uid));
				if (CR){delete CR;}
		});
		if (err!=KErrNone){continue;}
		CRepository* CR=CRepository::NewL(TUid::Uid(uid));
		CR->FindL(0,0,keys);
		for (TInt j=0; j<keys.Count();j++)
			{
			TBuf<512> buf;
			TBuf<255> DesVal;
			TBuf8<255> DesVal8;
			TInt IntVal;
			TReal RealVal;
			
			TRAPD(err1,User::LeaveIfError(CR->Get(keys[j],DesVal)));
			TRAPD(err2,User::LeaveIfError(CR->Get(keys[j],IntVal)));
			TRAPD(err3,User::LeaveIfError(CR->Get(keys[j],RealVal)));
			TRAPD(err4,User::LeaveIfError(CR->Get(keys[j],DesVal8)));
			if (err1==KErrNone){buf.Format(KStringFormat(),keys[j],&DesVal);}
			else if (err2==KErrNone){buf.Format(KIntFormat(),keys[j],IntVal);}
			else if (err3==KErrNone){buf.Format(KRealFormat(),keys[j],RealVal);}
			else if (err4==KErrNone){buf.Format(KString8Format(),keys[j],&DesVal8);}
			arr->AppendL(buf);
			}
		delete CR;
		TBuf<512> SavePath;
		SavePath.Copy(((CPluginsListView*)aObj)->iFolderToExp);
		SavePath.Append(_L("TweakS\\"));
		SavePath.Append(((TEntry)(*results)[i]).iName);
		TParse parse;
		CEikonEnv::Static()->FsSession().Parse(SavePath,parse);
		if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),parse.DriveAndPath()))
			{CEikonEnv::Static()->FsSession().MkDirAll(parse.DriveAndPath());}
				
		filesave.Replace(CEikonEnv::Static()->FsSession(),SavePath, EFileWrite);
		filesave.Write(enc);
		ft.Set(filesave);
		for (TInt j=0;j<arr->Count();j++)
			{
			ft.Write(arr->MdcaPoint(j));
			}
		filesave.Close();
		delete arr;
		}
	CPluginsListView* v=((CPluginsListView*)aObj);
	if (v->iExportWait){v->iExportWait->ProcessFinishedL();}
	if (v->iExportWait){delete v->iExportWait;}
	if (v->iIdle) {delete v->iIdle;}
	return 0;
	}


#ifndef __WINS__
	const TInt KBrowserUid = 0x10008D39;
#else
	const TInt KBrowserUid = 0x1020724D;
#endif

void CPluginsListView::OpenBrowser(const TDesC& aUrl)
	{
		TUid id(TUid::Uid(KBrowserUid));
		TApaTaskList taskList(CEikonEnv::Static()->WsSession());
		TApaTask task = taskList.FindApp(id);

		if (task.Exists())
		{
			HBufC8* param8 = HBufC8::NewLC(100);
			param8->Des().Append(aUrl);
			// Uid is not used
			task.SendMessage(TUid::Uid(0), *param8);
			CleanupStack::PopAndDestroy();
		}
		else
		{
			RApaLsSession appArcSession;
			// connect to AppArc server
			User::LeaveIfError(appArcSession.Connect());
			TThreadId id;
			TInt ret = appArcSession.StartDocument(aUrl, TUid::Uid(KBrowserUid), id);
			appArcSession.Close();
		}
	}
