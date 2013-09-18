/*
========================================================================
 Name        : AddingPluginView.cpp
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
#include "AddingPluginView.h"
#include "PluginsList.hrh"
#include "ListOfSettings.hrh"
#include "PluginsManager.hrh"
#include "SettingList.hrh"
#include "AddingPlugin.hrh"
#include "AddingPlugin.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]
#include <apgcli.h>
#include <TweakSAppUi.h>
#include <ListOfSettingsView.h>
#include <logger.h>
#include <aknpopup.h>

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CAddingPluginView::CAddingPluginView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iAddingPlugin = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CAddingPluginView::~CAddingPluginView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iAddingPlugin;
	iAddingPlugin = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CAddingPluginView
 */
CAddingPluginView* CAddingPluginView::NewL()
	{
	CAddingPluginView* self = CAddingPluginView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CAddingPluginView
 */
CAddingPluginView* CAddingPluginView::NewLC()
	{
	CAddingPluginView* self = new ( ELeave ) CAddingPluginView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CAddingPluginView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_ADDING_PLUGIN_ADDING_PLUGIN_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CAddingPluginView::Id() const
	{
	return TUid::Uid( EAddingPluginViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CAddingPluginView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
	
		case EAddingPluginViewControlPaneRightId:
			commandHandled = Back( aCommand );
			break;
		case EAddingPluginView_MenuItemCommand:
			commandHandled = Add( aCommand );
			break;
		case EAddingPluginView_MenuItem1Command:
			commandHandled = Edit( aCommand );
			break;
		case EAddingPluginView_C_MenuItemCommand:
			commandHandled = Remove( aCommand );
			break;
		case EAddingPluginView_MenuItem4Command:
			commandHandled = Reset( aCommand );
			break;
		case EAddingPluginView_MenuItem2Command:
			commandHandled = Info( aCommand );
			break;
		case EAddingPluginView_MenuItem3Command:
			commandHandled = Back( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EAddingPluginViewControlPaneRightId )
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

void CAddingPluginView::Active(TSettingData aData)
	{
	iData=aData;
	}
void CAddingPluginView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iAddingPlugin == NULL )
		{
		iAddingPlugin = CreateContainerL();
		iAddingPlugin->SetMopParent( this );
		AppUi()->AddToStackL( *this, iAddingPlugin );
		} 
	// ]]] end generated region [Generated Contents]
	TBuf<255> text;
	TInt res=R_ADDPLUGIN_EMPTY;
	TRAPD(err,
			{
			CRepository* CR=CRepository::NewL(TUid::Uid(iData.iUid));
			};);
	if (err!=KErrNone){res=R_ADDPLUGIN_NOT_SUPPORTED;}
	CEikonEnv::Static()->ReadResource(text,res);
	iAddingPlugin->ListBox()->View()->SetListEmptyTextL(text);
	if (err!=KErrNone)
		{
		TBuf<255> txt;
		CEikonEnv::Static()->ReadResource(txt,R_ADDPLUGIN_NOT_SUPPORTED);
		((CTweakSAppUi*)CEikonEnv::Static()->AppUi())->GlobalMsgQuery(txt,txt);
		return;
		}
	iCR=CRepository::NewL(TUid::Uid(iData.iUid));
	CListOfSettingsView::SetTitle(iData.iName);
	Update();
	}

/**
 */
void CAddingPluginView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iAddingPlugin != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iAddingPlugin );
		delete iAddingPlugin;
		iAddingPlugin = NULL;
		}
	// ]]] end generated region [Generated Contents]
	if (iCR){delete iCR;}
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CAddingPluginView::HandleStatusPaneSizeChange()
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
void CAddingPluginView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_ADDING_PLUGIN_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CAddingPluginView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CAddingPlugin::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CAddingPlugin
 */
CAddingPlugin* CAddingPluginView::CreateContainerL()
	{
	return CAddingPlugin::NewL( ClientRect(), NULL, this );
	}

/** 
 * Handle the rightSoftKeyPressed event.
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CAddingPluginView::Back( TInt aCommand )
	{
	AppUi()->ActivateLocalViewL(TUid::Uid(EPluginsListViewId));
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CAddingPluginView::Add( TInt aCommand )
	{
	
	TUint32 key;
	_LOGDATA(_L("View: %d"),iData.iViewType);
	if (iData.iViewType==EViewAddUidCombo)
		{
		TInt val;
		key=CListOfSettingsView::UIDNumSelect(iData,-1);
		if (key==-1) {return ETrue;}
		TInt curr=CListOfSettingsView::PopupMenu(iData);
		if (curr==-1){return ETrue;}
		val=iData.iComboElements->At(curr).iIntValue;
		_LOGDATA2(_L("Creating: %d, %d"),key,val);
		iCR->Create(key,val);
		}
	else if (iData.iViewType==EViewAddUid)
		{
		TInt val;
		RArray<TUint32> keys;
		iCR->FindL(0,0,keys);
		TInt i=1;
		while (keys.Find((TUint32)i)!=-1){i++;}
		key=i;
		val=CListOfSettingsView::UIDNumSelect(iData,-1);
		if (val==-1){return ETrue;}
		_LOGDATA2(_L("Creating: %d, %d"),key,val);
		iCR->Create(key,val);
		}
	else if (iData.iViewType==EViewAddFolder)
		{
		TInt i;
		TBuf<512> val;
		CDesCArray* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_ACTIONS);
		TInt type=PopupMenu(iData.iName,arr);
		if (type==-1){return ETrue;}
		if (type==0){i=0x10001;}
		else {i=0x20001;}
		RArray<TUint32> keys;
		iCR->FindL(0,0,keys);
		while (keys.Find((TUint32)i)!=-1){i++;}
		key=i;
		CListOfSettingsView::FileSelectDialog(iData,val);
		_LOG(_L("In Add again"));
		if (val.Compare(_L(""))==0){return ETrue;}
		val.Copy(val.Right(val.Length()-2));
		_LOGDATA2(_L("Creating: %d, %S"),key,&val);
		iCR->Create(key,val);
		}
	Update();
	return ETrue;
	}
void CAddingPluginView::HandleLBSelect()
	{
	Edit(0);
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CAddingPluginView::Edit( TInt aCommand )
	{
	TUint32 key;
	if (iAddingPlugin->ListBox()->Model()->NumberOfItems()==0){return ETrue;}
	RArray<TUint32> keys;
	iCR->FindL(0,0,keys);
	TInt i=iAddingPlugin->ListBox()->CurrentItemIndex();
	if (iData.iViewType==EViewAddUidCombo)
		{
		TInt val;
		key=keys[i];
		TInt curr=CListOfSettingsView::PopupMenu(iData);
		if (curr==-1){return ETrue;}
		val=iData.iComboElements->At(curr).iIntValue;
		_LOGDATA2(_L("Editing: %d, %d"),key,val);
		iCR->Set(key,val);
		}
	else if (iData.iViewType==EViewAddUid)
		{
		TInt val;
		key=keys[i];
		val=CListOfSettingsView::UIDNumSelect(iData,-1);
		if (val==-1){return ETrue;}
		_LOGDATA2(_L("Editing: %d, %d"),key,val);
		iCR->Set(key,val);
		}
	else if (iData.iViewType==EViewAddFolder)
		{
		TBuf<512> val;
		key=keys[i];
		CListOfSettingsView::FileSelectDialog(iData,val);
		_LOG(_L("In edit again"));
		if (val.Compare(_L(""))==0){return ETrue;}
		val.Copy(val.Right(val.Length()-2));
		_LOGDATA2(_L("Editing: %d, %S"),key,&val);
		iCR->Set(key,val);
		}
	Update();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CAddingPluginView::Remove( TInt aCommand )
	{
	if (iAddingPlugin->ListBox()->Model()->NumberOfItems()==0){return ETrue;}
	RArray<TUint32> keys;
	iCR->FindL(0,0,keys);
	TInt i=iAddingPlugin->ListBox()->CurrentItemIndex();
	iCR->Delete(keys[i]);
	Update();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CAddingPluginView::Info( TInt aCommand )
	{
	((CTweakSAppUi*)AppUi())->GlobalMsgQuery(iData.iDescription,iData.iName);
	return ETrue;
	}
				
void CAddingPluginView::Update()
	{
	CDesCArray* items=((CDesCArray*)iAddingPlugin->ListBox()->Model()->ItemTextArray());
	if (items->Count()>0){items->Reset();}
	RArray<TUint32> arr;
	iCR->FindL(0,0,arr);
	RApaLsSession ls;
	ls.Connect();
	TApaAppInfo info;
	TBuf<512> title,subtitle;
	TBuf<1024> LBBuffer;
	for (TInt i=0;i<arr.Count();i++)
		{
		if (iData.iViewType==EViewAddUidCombo)
			{
			TBuf<10> uid;
			TInt val;
			iCR->Get(arr[i],val);
			ls.GetAppInfo(info,TUid::Uid(arr[i]));
			if (iData.iNumOfCombo!=0) // combo
				{
				TInt j=0;
				subtitle.Num(val);
				for (j=0;j<iData.iNumOfCombo;j++)
					{
					if (val==iData.iComboElements->At(j).iIntValue){subtitle.Copy(iData.iComboElements->At(j).iDescription);}	
					}
				}
			uid.Num((TUint)info.iUid.iUid,EHex);
			uid.UpperCase();
			title.Copy(info.iCaption);
			title.Append(_L(" ["));
			title.Append(uid);
			title.Append(_L("]"));
			}
		else if (iData.iViewType==EViewAddUid)
			{
			TBuf<10> uid; 
			TInt val;
			iCR->Get(arr[i],val);
			_LOGDATA(_L("Val in update (EViewAddUid): %d"),val);
			ls.GetAppInfo(info,TUid::Uid(val));
			uid.Num((TUint)info.iUid.iUid,EHex);
			uid.UpperCase();
			title.Copy(info.iCaption);
			subtitle.Copy(uid);
			}
		else if (iData.iViewType==EViewAddFolder)
			{
			TInt temp=arr[i]/0x10000;
			TBuf<255> txt;
			if (!(temp==1||temp==2)){continue;}
			iCR->Get(arr[i],title);
			CDesC16Array* arr=CEikonEnv::Static()->ReadDesC16ArrayResourceL(R_ACTIONS);
			subtitle.Copy(arr->MdcaPoint(temp-1));
			delete arr;
			}
		iAddingPlugin->CreateListBoxItemL(LBBuffer,title,subtitle);
		iAddingPlugin->AddListBoxItemL(iAddingPlugin->ListBox(),LBBuffer);
		}
	ls.Close();
	iAddingPlugin->ListBox()->SetCurrentItemIndex(0);
	iAddingPlugin->ListBox()->DrawNow();
	}

TInt CAddingPluginView::PopupMenu(TDes& aTxt,CDesCArray* itemList)
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
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CAddingPluginView::Reset( TInt aCommand )
	{
	iCR->Reset();
	return ETrue;
	}
				
