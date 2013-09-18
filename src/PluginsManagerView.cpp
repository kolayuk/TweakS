/*
========================================================================
 Name        : PluginsManagerView.cpp
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
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
#include "PluginsManagerView.h"
#include "PluginsList.hrh"
#include "ListOfSettings.hrh"
#include "PluginsManager.hrh"
#include "SettingList.hrh"
#include "AddingPlugin.hrh"
#include "PluginsManager.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]
#include <const.h>
#include <PluginsListView.h>
#include <bautils.h>
#include <ClientEngine.h>
#include <textutils.h>
#include <TweakSAppUi.h>
#include <aknwaitdialog.h>
#include <logger.h>
#include <centralrepository.h>
void CPluginsManagerView::ReadUninstalledPlugins()
	{
	iPage->Des().Copy(iPage->Left(iPage->Length()-1));
	HBufC* data=CTextUtils::Des8To16(iPage);
	
	TPtr ptr(data->Des());
	TBuf<1> sym(_L("|"));
	CDesCArray* arr=CTextUtils::Split16(ptr,sym);
	TInt i;
	TInt j;
	sym.Copy(_L("*"));
	for (i=0;i<arr->Count();i++)
		{
		TInt noerr=0;
		TInt fullerr=0;
		ptr.Copy(arr->MdcaPoint(i));
		CDesCArray* plg=CTextUtils::Split16(ptr,sym);
		TPluginInfo info;
		info.iPlgName.Copy(plg->MdcaPoint(2));
		TLex conv(plg->MdcaPoint(4));
		conv.Val(info.iSize);
		TInt found=0;
		//uids
		TBuf<1> uidsep(_L("%"));
		TBuf<512> uids_str(plg->MdcaPoint(5));
		CDesC16Array* uids=CTextUtils::Split16(uids_str,uidsep);
		for (TInt uidi=0;uidi<uids->Count()-1;uidi++)
			{
			TUint uid;
			conv.Assign(uids->MdcaPoint(uidi));
			conv.Val(uid,EDecimal);
			_LOGDATA2(_L("Plugin %S, uid %d"),&info.iPlgName,uid);
			info.iUids.Append(uid);
			TRAPD(err,
				{
				CRepository* rep=CRepository::NewL(TUid::Uid(uid));
				if (rep){delete rep;}
				};);
			if (err==KErrNone){noerr=1;}
			fullerr+=err;
			}
		if (noerr!=1){continue;}
		_LOGDATA(_L("Full error: %d"),fullerr);
		_LOGDATA(_L("Must be %d"),(-1)*info.iUids.Count());
		for (j=0;j<iPlugins->Count();j++)
			{
			if (iPlugins->At(j).iPlgName.Compare(info.iPlgName)==0)
				{
				if (iPlugins->At(j).iSize!=info.iSize)
					{
					//update
				info.iName.Copy(plg->MdcaPoint(0));
				info.iDescription.Copy(plg->MdcaPoint(1));
#ifdef _DEBUG
				TInt l=100500;
				info.iPlgUrl.Format(KPluginsPathURL(),l,&plg->MdcaPoint(2));
				_LOG(info.iPlgUrl);
				info.iCreUrl.Format(KPluginsPathURL(),l,&plg->MdcaPoint(3));
				_LOG(info.iCreUrl);	
#else
				info.iPlgUrl.Format(KPluginsPathURL(),User::Language(),&plg->MdcaPoint(2));
				_LOG(info.iPlgUrl);
				info.iCreUrl.Format(KPluginsPathURL(),User::Language(),&plg->MdcaPoint(3));
				_LOG(info.iCreUrl);		
#endif
				info.iCreName.Copy(plg->MdcaPoint(3));
				info.iPLGPath=iPlugins->At(j).iPLGPath;
				info.iCREPath=iPlugins->At(j).iCREPath;
					found++;
					TBuf<255> r;
					CEikonEnv::Static()->ReadResource(r,R_PLUGIN_UPDATE);
					info.iType=r;
					info.iTypeInt=EPluginUpdateAvailable;
					iPlugins->Delete(j);
					iPlugins->InsertL(j,info);
					iPluginsManager->Update();
					}
				else {found++; break;}
				}
			}
		if (found==0)
			{
			//add new plugin (not installed)
		info.iName.Copy(plg->MdcaPoint(0));
		info.iDescription.Copy(plg->MdcaPoint(1));
#ifdef _DEBUG
				TInt l=100500;
				info.iPlgUrl.Format(KPluginsPathURL(),l,&plg->MdcaPoint(2));
				_LOG(info.iPlgUrl);
				info.iCreUrl.Format(KPluginsPathURL(),l,&plg->MdcaPoint(3));
				_LOG(info.iCreUrl);	
#else
				info.iPlgUrl.Format(KPluginsPathURL(),User::Language(),&plg->MdcaPoint(2));
				_LOG(info.iPlgUrl);
				info.iCreUrl.Format(KPluginsPathURL(),User::Language(),&plg->MdcaPoint(3));
				_LOG(info.iCreUrl);		
#endif
		info.iCreName.Copy(plg->MdcaPoint(3));
			TBuf<255> r;
			CEikonEnv::Static()->ReadResource(r,R_PLUGIN_NOT_INSTALLED);
			info.iType=r;
			info.iTypeInt=EPluginNotInstalled;
			iPlugins->AppendL(info);
			iPluginsManager->Update();
			}
		delete plg;
		}
	delete arr;
	delete data;
	}

void CPluginsManagerView::ReadDisabledPlugins()
	{
	if (!BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(),KDisabledPluginsDir))
		{
		CEikonEnv::Static()->FsSession().MkDirAll(KDisabledPluginsDir);
		}
	CDir* results=NULL;
	TFindFile findFiles(CEikonEnv::Static()->FsSession());
	findFiles.FindWildByDir(KIniMask,KDisabledPluginsDir,results);

	TInt i;
	TBuf<255> fn;
	TBuf<255> temp;
	RFile filesave;
	TFileText ft;

	if (results==NULL){return;}
	for (i=0; i<results->Count();i++)
		{
		TPluginInfo descr;
		temp.Zero();
		fn.Zero();
		descr.iName.Zero();
		descr.iDescription.Zero();
		
		fn.Copy(KDisabledPluginsDir);
		fn.Append(((TEntry)(*results)[i]).iName);
		descr.iPlgName.Copy(((TEntry)(*results)[i]).iName);
		filesave.Open(CEikonEnv::Static()->FsSession(),fn,EFileRead);
		ft.Set(filesave);
		ft.Read(descr.iName);
		ft.Read(descr.iDescription);
		ft.Read(temp);
		
		TLex conv(temp);
		conv.Val(descr.iUid,EHex);
		
		TBuf<255> a;
		a.Append(KCREPath);
		a.Append(temp);
		a.Append(KCREExtension);
		descr.iCREPath=a;
		descr.iCreName.Copy(temp);
		descr.iCreName.Append(KCREExtension);
		descr.iPLGPath=fn;
		TEntry entry;
		CEikonEnv::Static()->FsSession().Entry(a, entry);
		TInt CRESize = entry.iSize;
		CEikonEnv::Static()->FsSession().Entry(fn, entry);
		TInt PLGSize = entry.iSize;
		descr.iSize=PLGSize+CRESize;
		//if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),a)){BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),a,KCREPath);BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),a);}
		TBuf<255> t;
		CEikonEnv::Static()->ReadResource(t,R_PLUGIN_DISABLED);
		descr.iType=t;
		descr.iTypeInt=EPluginDisabled;
		iPlugins->AppendL(descr);
		filesave.Close();
		}
	}

void CPluginsManagerView::ReadInstalledPlugins()
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
		TPluginInfo descr;
		temp.Zero();
		fn.Zero();
		descr.iName.Zero();
		descr.iDescription.Zero();
		
		fn.Copy(KPluginsDir);
		fn.Append(((TEntry)(*results)[i]).iName);
		descr.iPlgName.Copy(((TEntry)(*results)[i]).iName);
		filesave.Open(CEikonEnv::Static()->FsSession(),fn,EFileRead);
		ft.Set(filesave);
		ft.Read(descr.iName);
		ft.Read(descr.iDescription);
		ft.Read(temp);
		filesave.Close();
		TLex conv(temp);
		conv.Val(descr.iUid,EHex);
		
		TBuf<255> a;
		a.Append(KCREPath);
		a.Append(temp);
		a.Append(KCREExtension);
		descr.iCREPath=a;
		descr.iCreName.Copy(temp);
		descr.iCreName.Append(KCREExtension);
		descr.iPLGPath=fn;
		TEntry entry;
		CEikonEnv::Static()->FsSession().Entry(a, entry);
		TInt CRESize = entry.iSize;
		CEikonEnv::Static()->FsSession().Entry(fn, entry);
		TInt PLGSize = entry.iSize;
		descr.iSize=PLGSize+CRESize;
		//if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),a)){BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),a,KCREPath);BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),a);}
		TBuf<255> t;
		CEikonEnv::Static()->ReadResource(t,R_PLUGIN_ACTIVE);
		descr.iType=t;
		descr.iTypeInt=EPluginActive;
		iPlugins->AppendL(descr);
		}
	}


/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CPluginsManagerView::CPluginsManagerView(): MProgressDialogCallback()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iPluginsManager = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CPluginsManagerView::~CPluginsManagerView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iPluginsManager;
	iPluginsManager = NULL;
	// ]]] end generated region [Generated Contents]
	delete iHTTP;
	delete iPage;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CPluginsManagerView
 */
CPluginsManagerView* CPluginsManagerView::NewL()
	{
	CPluginsManagerView* self = CPluginsManagerView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CPluginsManagerView
 */
CPluginsManagerView* CPluginsManagerView::NewLC()
	{
	CPluginsManagerView* self = new ( ELeave ) CPluginsManagerView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CPluginsManagerView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_PLUGINS_MANAGER_PLUGINS_MANAGER_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	iPlugins=new (ELeave) CArrayFixSeg<TPluginInfo>(1);
	iHTTP=CHTTPDownloader::NewL();
	iPage=HBufC8::NewL(10*1024);
	
	}

/**
 * @return The UID for this view
 */
TUid CPluginsManagerView::Id() const
	{
	return TUid::Uid( EPluginsManagerViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CPluginsManagerView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
	
		case EPluginsManagerViewControlPaneRightId:
			commandHandled = HandleControlPaneRightSoftKeyPressedL( aCommand );
			break;
		case EPluginsManagerView_MenuItem5Command:
			commandHandled = Handle_MenuItem5SelectedL( aCommand );
			break;
		case EPluginsManagerView_MenuItemCommand:
			commandHandled = Handle_MenuItemSelectedL( aCommand );
			break;
		case EPluginsManagerView_MenuItem1Command:
			commandHandled = Handle_MenuItem1SelectedL( aCommand );
			break;
		case EPluginsManagerView_MenuItem2Command:
			commandHandled = Handle_MenuItem2SelectedL( aCommand );
			break;
		case EPluginsManagerView_MenuItem3Command:
			commandHandled = Handle_MenuItem3SelectedL( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EPluginsManagerViewControlPaneRightId )
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
void CPluginsManagerView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iPluginsManager == NULL )
		{
		iPluginsManager = CreateContainerL();
		iPluginsManager->SetMopParent( this );
		AppUi()->AddToStackL( *this, iPluginsManager );
		} 
	// ]]] end generated region [Generated Contents]
	iPlugins->Delete(0,iPlugins->Count());
	TBuf<255> url;
	TBuf<255> format; format.Copy(KPluginsListURL);
#ifdef _DEBUG
	TInt l=100500;
	url.Format(KPluginsListURL(),l);
#else
	url.Format(KPluginsListURL(),User::Language());
#endif
	iHTTP->GetPage(url,iPage,TCallBack(Downloaded,this));
	ReadInstalledPlugins();
	ReadDisabledPlugins();
	iPluginsManager->Update();
	}
TInt CPluginsManagerView::Downloaded(TAny* aObject)
	{
	((CPluginsManagerView*)aObject)->ReadUninstalledPlugins();
	return 0;
	}
/**
 */
void CPluginsManagerView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iPluginsManager != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iPluginsManager );
		delete iPluginsManager;
		iPluginsManager = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CPluginsManagerView::HandleStatusPaneSizeChange()
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
void CPluginsManagerView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_PLUGINS_MANAGER_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CPluginsManagerView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CPluginsManager::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CPluginsManager
 */
CPluginsManager* CPluginsManagerView::CreateContainerL()
	{
	return CPluginsManager::NewL( ClientRect(), NULL, this );
	}

/** 
 * Handle the rightSoftKeyPressed event.
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsManagerView::HandleControlPaneRightSoftKeyPressedL( TInt aCommand )
	{
	AppUi()->ActivateLocalViewL(TUid::Uid(EPluginsListViewId));
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsManagerView::Handle_MenuItemSelectedL( TInt aCommand )
	{
	//disable
	TInt i=iPluginsManager->ListBox()->CurrentItemIndex();
	TPluginInfo info=iPlugins->At(i);
	BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),info.iPLGPath,KDisabledPluginsDir);
	BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),info.iPLGPath);
	TBuf<255> b;
	CEikonEnv::Static()->ReadResource(b,R_PLUGIN_DISABLED);
	info.iType=b;
	info.iTypeInt=EPluginDisabled;
	iPlugins->Delete(i);
	iPlugins->InsertL(i,info);
	iPluginsManager->UpdateItem(i);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsManagerView::Handle_MenuItem1SelectedL( TInt aCommand )
	{
	//enable
	TInt i=iPluginsManager->ListBox()->CurrentItemIndex();
	TPluginInfo info=iPlugins->At(i);
	BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),info.iPLGPath,KPluginsDir);
	BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),info.iPLGPath);
	TBuf<255> b;
	CEikonEnv::Static()->ReadResource(b,R_PLUGIN_ACTIVE);
	info.iType=b;
	info.iTypeInt=EPluginActive;
	iPlugins->Delete(i);
	iPlugins->InsertL(i,info);
	iPluginsManager->UpdateItem(i);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsManagerView::Handle_MenuItem2SelectedL( TInt aCommand )
	{
	//delete
	TInt i=iPluginsManager->ListBox()->CurrentItemIndex();
	TPluginInfo info=iPlugins->At(i);
	BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),info.iPLGPath);
	BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),info.iCREPath);
	CDesCArray* itemArray = static_cast<CDesCArray*> (iPluginsManager->ListBox()->Model()->ItemTextArray());
	itemArray->Delete(i);
	iPluginsManager->ListBox()->HandleItemRemovalL();
	if (iPluginsManager->ListBox()->Model()->NumberOfItems()>0){if (i!=0){iPluginsManager->ListBox()->SetCurrentItemIndexAndDraw(i-1);}else {iPluginsManager->ListBox()->SetCurrentItemIndexAndDraw(i);}}
	iPluginsManager->ListBox()->DrawNow();
	iPlugins->Delete(i);
	/* full update
	TBuf<255> url;
	TBuf<255> format; format.Copy(KPluginsListURL);
	url.Format(KPluginsListURL(),User::Language());
	iHTTP->GetPage(url,iPage,TCallBack(Downloaded,this));
	ReadInstalledPlugins();
	ReadDisabledPlugins();
	iPluginsManager->Update();
	*/
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsManagerView::Handle_MenuItem3SelectedL( TInt aCommand )
	{
	//install
	TInt i=iPluginsManager->ListBox()->CurrentItemIndex();
	iWait = new ( ELeave )CAknWaitDialog(reinterpret_cast<CEikDialog**>(&iWait),ETrue);
	iWait->SetCallback(this); 
	isDialogActive=ETrue;
	iWait->ExecuteLD(R_DOWNLOAD_WAIT_DIALOG);
	TBuf<255> url;
	TBuf<255> file;
	url.Copy(iPlugins->At(i).iCreUrl);
	file.Copy(KPluginsDir);
	file.Append(iPlugins->At(i).iCreName);
	iPlugins->At(i).iCREPath.Copy(file);
	_LOG(_L("Downloading cre:"));
	_LOG(url);
	iHTTP->DownloadFile(url,file,TCallBack(CREDownloaded,this));
	
	
	return ETrue;
	}
void CPluginsManagerView::DialogDismissedL(TInt aButtonId)
	{
	isDialogActive=EFalse;
	if (iHTTP->iClient->IsRunning())
		{
	iHTTP->Cancel();
	TInt i=iPluginsManager->ListBox()->CurrentItemIndex();
	//RDebug::Print(iPlugins->At(i).iCREPath);
	//RDebug::Print(iPlugins->At(i).iPLGPath);
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),iPlugins->At(i).iCREPath)){BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),iPlugins->At(i).iCREPath);}
	if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),iPlugins->At(i).iPLGPath)){BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),iPlugins->At(i).iPLGPath);}
		}
	}

TInt CPluginsManagerView::CREDownloaded(TAny* aObj)
	{
	TInt i=((CPluginsManagerView*)aObj)->iPluginsManager->ListBox()->CurrentItemIndex();
	TBuf<255> url;
	TBuf<255> file;
	url.Copy(((CPluginsManagerView*)aObj)->iPlugins->At(i).iPlgUrl);
	file.Copy(KPluginsDir);
	file.Append(((CPluginsManagerView*)aObj)->iPlugins->At(i).iPlgName);
	_LOG(_L("Downloading plg:"));
	_LOG(url);
	((CPluginsManagerView*)aObj)->iPlugins->At(i).iPLGPath.Copy(file);
	((CPluginsManagerView*)aObj)->iHTTP->DownloadFile(url,file,TCallBack(PLGDownloaded,((CPluginsManagerView*)aObj)));
	}
TInt CPluginsManagerView::PLGDownloaded(TAny* aObj)
	{
	TBuf<255> r;
	if (((CPluginsManagerView*)aObj)->isDialogActive){((CPluginsManagerView*)aObj)->iWait->ProcessFinishedL();((CPluginsManagerView*)aObj)->isDialogActive=EFalse;}
	TInt i=((CPluginsManagerView*)aObj)->iPluginsManager->ListBox()->CurrentItemIndex();
	((CPluginsManagerView*)aObj)->iPlugins->At(i).iTypeInt=EPluginActive;
	CEikonEnv::Static()->ReadResource(r,R_PLUGIN_ACTIVE);
	((CPluginsManagerView*)aObj)->iPlugins->At(i).iType.Copy(r);
	((CPluginsManagerView*)aObj)->iPluginsManager->UpdateItem(i);
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsManagerView::Handle_MenuItem4SelectedL( TInt aCommand )
	{
	AppUi()->ActivateLocalViewL(TUid::Uid(EPluginsListViewId));
	return ETrue;
	}
void CPluginsManagerView::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
	{
	if (iPluginsManager->ListBox()->Model()->NumberOfItems()>0)
		{
		if ((aResourceId==R_PLUGINS_MANAGER_MENU_PANE1_MENU_PANE))
			{
			TInt i=iPluginsManager->ListBox()->CurrentItemIndex();
			TPluginInfo info=iPlugins->At(i);
			
			if (info.iTypeInt==EPluginActive)
				{
				aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem1Command,ETrue);
				aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem3Command,ETrue);
				}
			else if(info.iTypeInt==EPluginDisabled)
				{
				aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItemCommand,ETrue);
				aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem3Command,ETrue);
				}
			else if (info.iTypeInt==EPluginUpdateAvailable)
				{
				aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItemCommand,ETrue);
				aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem1Command,ETrue);
				//aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem2Command,ETrue);
				}
			else if (info.iTypeInt==EPluginNotInstalled)
				{
				aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItemCommand,ETrue);
				aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem1Command,ETrue);
				aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem2Command,ETrue);
				}
			}
		}
	else 
		{
		if (aResourceId==R_PLUGINS_MANAGER_MENU_PANE1_MENU_PANE)
			{
			aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItemCommand,ETrue);
			aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem1Command,ETrue);
			aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem2Command,ETrue);
			aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem3Command,ETrue);
			aMenuPane->SetItemDimmed(EPluginsManagerView_MenuItem5Command,ETrue);
			}
		}
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CPluginsManagerView::Handle_MenuItem5SelectedL( TInt aCommand )
	{
	TInt i=iPluginsManager->ListBox()->CurrentItemIndex();
	((CTweakSAppUi*)AppUi())->GlobalMsgQuery(iPlugins->At(i).iDescription,iPlugins->At(i).iName);
	return ETrue;
	}
void CPluginsManagerView::HandleLBSelect()
	{
	MenuBar()->TryDisplayMenuBarL();
	}
