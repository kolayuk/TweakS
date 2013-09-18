/*
========================================================================
 Name        : SettingListView.cpp
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
#include "SettingListView.h"
#include "PluginsList.hrh"
#include "ListOfSettings.hrh"
#include "PluginsManager.hrh"
#include "SettingList.hrh"
#include "AddingPlugin.hrh"
#include "SettingList.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]


#include <aknlists.h>
#include <COMMDB.H> 		//Communications database 
#include <CDBPREFTABLE.H>	//Connection Preferences table
#include <CommDbConnPref.h>
#include <TweakSAppUi.h>
#include <ClientEngine.h>
#include <coecntrl.h>
#include <aknpopup.h>
/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CSettingListView::CSettingListView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iSettingList = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CSettingListView::~CSettingListView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iSettingList;
	iSettingList = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CSettingListView
 */
CSettingListView* CSettingListView::NewL()
	{
	CSettingListView* self = CSettingListView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CSettingListView
 */
CSettingListView* CSettingListView::NewLC()
	{
	CSettingListView* self = new ( ELeave ) CSettingListView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CSettingListView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_SETTING_LIST_SETTING_LIST_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CSettingListView::Id() const
	{
	return TUid::Uid( ESettingListViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CSettingListView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
	
		case ESettingListViewControlPaneRightId:
			commandHandled = HandleControlPaneRightSoftKeyPressedL( aCommand );
			break;
		case ESettingListView_MenuItemCommand:
			commandHandled = Handle_MenuItemSelectedL( aCommand );
			break;
		case ESettingListView_MenuItem2Command:
			commandHandled = Handle_MenuItem2SelectedL( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == ESettingListViewControlPaneRightId )
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
void CSettingListView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iSettingList == NULL )
		{
		iSettingList = CreateContainerL();
		iSettingList->SetMopParent( this );
		AppUi()->AddToStackL( *this, iSettingList );
		} 
	// ]]] end generated region [Generated Contents]
	
	
	Init();
	}

/**
 */
void CSettingListView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iSettingList != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iSettingList );
		delete iSettingList;
		iSettingList = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CSettingListView::HandleStatusPaneSizeChange()
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
void CSettingListView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_SETTING_LIST_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CSettingListView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CSettingList::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CSettingList
 */
CSettingList* CSettingListView::CreateContainerL()
	{
	return CSettingList::NewL( ClientRect(), NULL, this );
	}

/** 
 * Handle the rightSoftKeyPressed event.
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSettingListView::HandleControlPaneRightSoftKeyPressedL( TInt aCommand )
	{
	//back
	AppUi()->ActivateLocalViewL(TUid::Uid(EPluginsListViewId));
	return ETrue;
	}
void CSettingListView::HandleLBSelect()
	{
	TInt i=iSettingList->ListBox()->CurrentItemIndex();
	if (i==0)
		{
		//access point
		((CTweakSAppUi*)AppUi())->iSettings[0]=SelectIAP();
		}
	else if (i==1)
		{
		//autostart
		
		if (((CTweakSAppUi*)AppUi())->iSettings[1]==1){((CTweakSAppUi*)AppUi())->iSettings[1]=0;CEikonEnv::Static()->ReadResource(iAutoStartName,R_OFF);}
		else if (((CTweakSAppUi*)AppUi())->iSettings[1]==0){((CTweakSAppUi*)AppUi())->iSettings[1]=1;CEikonEnv::Static()->ReadResource(iAutoStartName,R_ON);}
		}
	iChanged=ETrue;
	Update();
	TInt err;
	//((CTweakSAppUi*)AppUi())->WriteSettings();
	TRAP(err,{((CTweakSAppUi*)AppUi())->WriteSettings();});
	if (err!=KErrNone)
		{
		TBuf<255> header(_L("TweakS"));
		TBuf<255> text;
		CEikonEnv::Static()->ReadResource(text,R_SETTING_UNVAILABLE_NEED_RESTART);
		((CTweakSAppUi*)AppUi())->GlobalMsgQuery(text,header);
		}
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSettingListView::Handle_MenuItemSelectedL( TInt aCommand )
	{
	HandleLBSelect();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSettingListView::Handle_MenuItem1SelectedL( TInt aCommand )
	{
	//save
	((CTweakSAppUi*)AppUi())->WriteSettings();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSettingListView::Handle_MenuItem2SelectedL( TInt aCommand )
	{
	//back
	AppUi()->ActivateLocalViewL(TUid::Uid(EPluginsListViewId));
	return ETrue;
	}
TInt CSettingListView::SelectIAP()
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
	TBuf<255> buf;
	CEikonEnv::Static()->ReadResource(buf,R_SELECT_IAP_DIALOG_TITLE);
	popupList->SetTitleL(buf);
	list->SetListBoxObserver(popupList);
	TInt popupOk = popupList->ExecuteLD();
	CleanupStack::Pop();    
	TInt iap=0;
	if (popupOk)
	{	
		TInt index = list->CurrentItemIndex();
		iap=(*iEApList)[index].iIap;
		iIAPName=(*iEApList)[index].iName;
	}
	else {CEikonEnv::Static()->ReadResource(iIAPName,R_EMPTY_IAP); return -1;}
	CleanupStack::PopAndDestroy();  
	iEApList->Reset();
	delete iEApList;
	return iap;
}
void CSettingListView::Update()
	{
	ChangeItemSubtitle(0,iIAPName);
	ChangeItemSubtitle(1,iAutoStartName);
	}
void CSettingListView::ChangeItemSubtitle(TInt aIndex,TDes16& aText)
	{
	TBuf<255> prev = iSettingList->ListBox()->Model()->ItemText(aIndex);
	TChar a = '\t'; 
	TInt pos = prev.LocateReverse(a); 
	if (pos != KErrNotFound) 
		{	 
    TInt replace_length = prev.Length() - pos;
    prev.Delete(pos+1, replace_length); 
    prev.Insert(pos+1, aText); 
		}
	CDesCArray* itemArray = static_cast<CDesCArray*> (iSettingList->ListBox()->Model()->ItemTextArray());
	itemArray->Delete(aIndex);
	itemArray->InsertL(aIndex,prev);
	iSettingList->ListBox()->DrawNow();
	}

void CSettingListView::Init()
	{
	if (((CTweakSAppUi*)AppUi())->iSettings[1]==1){CEikonEnv::Static()->ReadResource(iAutoStartName,R_ON);}
	else if (((CTweakSAppUi*)AppUi())->iSettings[1]==0){CEikonEnv::Static()->ReadResource(iAutoStartName,R_OFF);}
	
	
	iIAPName=NameByIAP(((CTweakSAppUi*)AppUi())->iSettings[0]);
	Update();
	}

TBuf<128> CSettingListView::NameByIAP(TInt aIap)
{
	CArrayFixFlat<TIapData>* iEApList=new (ELeave) CArrayFixFlat<TIapData>(2) ;
	TInt stack=0;
 
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
		if (id==aIap)
			{
			TBuf<128> result;
			result.Copy(iapfromtable);
			CleanupStack::PopAndDestroy(2); stack--; 
			iEApList->Reset();
			delete iEApList;
			return result;
			}
		err = gprsTable->GotoNextRecord();
		i++;
	}
	while (err == KErrNone);
	CleanupStack::PopAndDestroy(2); stack--;  
	iEApList->Reset();
	delete iEApList;
	TBuf<128> empty;
	CEikonEnv::Static()->ReadResource(empty,R_EMPTY_IAP);
	return empty;
}
