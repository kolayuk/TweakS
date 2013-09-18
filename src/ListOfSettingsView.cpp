/*
========================================================================
 Name        : ListOfSettingsView.cpp
 Author      : Kolay
 Copyright   : Contacts:
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
#include <eikbtgpc.h>
#include <TweakS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]

#include "TweakS.hrh"
#include "ListOfSettingsView.h"
#include "PluginsList.hrh"
#include "ListOfSettings.hrh"
#include "PluginsManager.hrh"
#include "SettingList.hrh"
#include "AddingPlugin.hrh"
#include "ListOfSettings.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

#include <logger.h>

#include <akntitle.h>
#include <eikspane.h>
#include <eikaufty.h>
#include <centralrepository.h>
#include <SettingData.h>
#include <TweakSAppUi.h>
#include <aknlists.h> //CAknSinglePopupMenuStyleListBox 
#include <aknpopup.h> //CAknPopupList
#include <aknquerydialog.h> // NumberQuery
#include <const.h>
#include <bautils.h> 
#include <APGCLI.H>
#include <eiklbv.h>
#include <aknselectionlist.h>
#include <akncommondialogs.h>
#include <caknfileselectiondialog.h> 
#include <caknmemoryselectiondialog.h> 
#include <FileSelectDialog.h>
#include <SliderDialog.h>
#include <e32property.h>
#include <AddingPluginView.h>
/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */


/*

CMyMultiSelectionDialog::CMyMultiSelectionDialog( TInt &aOpenedItem,
	                                     CArrayFix<TInt> *aSelectedItems,
	                                     MDesCArray *aArray,
	                                     TInt aMenuBarResourceId,
	                                     TInt aOkMenuBarResourceId,
	                                     MEikCommandObserver *aObserver ): CAknMarkableListDialog(aOpenedItem,aSelectedItems,aArray,aMenuBarResourceId,aOkMenuBarResourceId,aObserver)
	{
	
	}

CMyMultiSelectionDialog* CMyMultiSelectionDialog::NewL( TInt &aValue, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, TInt aOkMenuBarId, MEikCommandObserver *aCommand)
	{
	CMyMultiSelectionDialog* self = CMyMultiSelectionDialog::NewLC(aValue, aSelectedItems, aArray, aMenuBarResourceId, aOkMenuBarId, aCommand);
	CleanupStack::Pop( self );
	return self;
	}
CMyMultiSelectionDialog* CMyMultiSelectionDialog::NewLC(TInt &aValue, CArrayFix<TInt> *aSelectedItems, MDesCArray *aArray, TInt aMenuBarResourceId, TInt aOkMenuBarId, MEikCommandObserver *aCommand)
	{
	CMyMultiSelectionDialog* self = new ( ELeave ) CMyMultiSelectionDialog(aValue,aSelectedItems, aArray, aMenuBarResourceId, aOkMenuBarId, aCommand);
	CleanupStack::PushL( self );
	self->ConstructL(aMenuBarResourceId);
	return self;
	}

TBool CMyMultiSelectionDialog::OkToExitL(TInt aButton)
	{
	   TBool b =ETrue;
	   
	   if (iSelectionIndexArray) 
	   { 
	   const CArrayFix<TInt> *array = ListBox()->SelectionIndexes(); 
	   TInt countarr=array->Count();
	   TInt count=STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->SelectionIndexes()->Count();
	   if (FindBox()) 
	       { 
	       STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->UpdateSelectionIndexesL(); 
	       array = STATIC_CAST(CAknFilteredTextListBoxModel*,ListBox()->Model())->Filter()->SelectionIndexes(); 
	       } 
	   TInt numberOfItems(array->Count()); 
	   iSelectionIndexArray->Reset(); 
	   for(TInt i(0); i<numberOfItems; i++) 
	       {iSelectionIndexArray->AppendL(array->At(i));} 
	   }
	   return b; 
	}
*/

CListOfSettingsView::CListOfSettingsView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iListOfSettings = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CListOfSettingsView::~CListOfSettingsView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iListOfSettings;
	iListOfSettings = NULL;
	// ]]] end generated region [Generated Contents]
	if (iSettingsData){delete iSettingsData;}
	if (iInfoCR){delete iInfoCR;}
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CListOfSettingsView
 */
CListOfSettingsView* CListOfSettingsView::NewL()
	{
	CListOfSettingsView* self = CListOfSettingsView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CListOfSettingsView
 */
CListOfSettingsView* CListOfSettingsView::NewLC()
	{
	CListOfSettingsView* self = new ( ELeave ) CListOfSettingsView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CListOfSettingsView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_LIST_OF_SETTINGS_LIST_OF_SETTINGS_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	iSettingsData = new (ELeave) CArrayFixSeg<TSettingData>(1);
	}
void CListOfSettingsView::Active(TUint aUid, TDes& aTitle)
	{
#ifdef _DEBUG
	TBuf<255> a;
	a.Append(_L("Parameters passed: "));
	a.AppendNum(aUid);
	a.Append(_L(", "));
	a.Append(aTitle);
	RDebug::Print(a);

#endif
	iUid=aUid;
	iTitle=aTitle;
	}

void CListOfSettingsView::ReadData()
	{

	_LOG(_L("Reading data..."));
	TInt NumOfSettings;
	iInfoCR->Get(0x1,NumOfSettings);
	
	TInt i=0;
	TInt Current=0;
	TInt Unlocked=0;
	for (i=1; i<NumOfSettings+1; i++)
		{
		TSettingData Data;
		Current=i*100;
		
		iInfoCR->Get(Current,Data.iName);
		iInfoCR->Get(Current+1,Data.iDescription);
		iInfoCR->Get(Current+2,Data.iUid);
		iInfoCR->Get(Current+3,Data.iKey);
		iInfoCR->Get(Current+4,Data.iType);
		iInfoCR->Get(Current+5,Data.iViewType);
		iInfoCR->Get(Current+6,Data.iMinValue);
		iInfoCR->Get(Current+7,Data.iMaxValue);
		if (Data.iType!=EPropertyInt&&Data.iType!=EPropertyString16&&Data.iType!=EPropertyString8)
			{
			
			if (Data.iKey!=-1)
				{
				Data.iExists=Exists(Data.iUid,Data.iKey,Data.iType);
				if (Data.iExists==-1){continue;}
				}
			_LOG(_L("Will test to unlock now"));
			Unlocked+=TestUnlock(Data.iUid);
			_LOGDATA(_L("Unlocked after: %d"),Unlocked);
			}
		TInt NumOfCombo;
		iInfoCR->Get(Current+8,NumOfCombo);
		Data.iNumOfCombo=NumOfCombo;
		TInt j=0;
		TInt Curr=Current+9;
		Data.iComboElements = new (ELeave) CArrayFixSeg<TComboElement>(1); 
		for (j=0; j<NumOfCombo*2;j++)
			{
			TComboElement element;
			iInfoCR->Get(Curr+j,element.iDescription);
			element.iType=Data.iType;
			if (element.iType==EInt){iInfoCR->Get(Curr+j+1,element.iIntValue);}
			else if (element.iType==EString){iInfoCR->Get(Curr+j+1,element.iDesValue);}
			else {CEikonEnv::Static()->InfoMsg(_L("Wrong Type!"));}
			Data.iComboElements->AppendL(element);
			j++;
			}
		if (Data.iKey==EKeyTypeAdd)
			{
			_LOG(_L("Plugin is add-plugin"));
			((CAddingPluginView*)(((CTweakSAppUi*)AppUi())->View(TUid::Uid(EAddingPluginViewId))))->Active(Data);
			AppUi()->ActivateLocalViewL(TUid::Uid(EAddingPluginViewId));
			}
		iSettingsData->AppendL(Data);
		_LOGDATA(_L("Iteration %d - ok"),i);
		}
	if (Unlocked>0)
		{ 
		TBuf<500> header;
		TBuf<500> text;
		CEikonEnv::Static()->ReadResource(text,R_RESTART_NEEDED_TEXT);
		CEikonEnv::Static()->ReadResource(header,R_RESTART_NEEDED_HEADER);
		if (((CTweakSAppUi*)AppUi())->GlobalMsgQuery(text,header))
			{
			Restart();
			}
		}
}
void CListOfSettingsView::Restart()
	{
	
	RProperty::Set(TUid::Uid(0x101F8766), 0x421, 0x100);
	RProperty::Set(TUid::Uid(0x101F8766), 1056, 2);
	

		TRAPD(err2,
		{
		TBuf<255> a;
		a.Append(_L("*"));
		a.Append(KSysApProcessUID);
		a.Append(_L("*"));
		TFindProcess processFinder(a); // by name, case-sensitive
		TFullName result;
		RProcess processHandle;
		while ( processFinder.Next(result) == KErrNone) 
		{
		   User::LeaveIfError(processHandle.Open ( processFinder, EOwnerThread));
		   processHandle.Kill(KErrNone);
		   processHandle.Close();
		}
		});
		TBuf<2> a;
		a.Num(err2);
		CEikonEnv::Static()->InfoMsg(a);
	}

void CListOfSettingsView::Output()
	{
	TInt i=0;
	TBuf<255> a;
	for (i=0;i<iSettingsData->Count();i++)
		{
		a.Copy(_L("=============="));
		a.AppendNum(i);
		a.Append(_L("============"));
		RDebug::Print(a);
		
		TSettingData data=iSettingsData->At(i);

		a.Copy(_L("Name: "));
		a.Append(data.iName);
		RDebug::Print(a);
	

		a.Copy(_L("Descr: "));
		a.Append(data.iDescription);
		RDebug::Print(a);

		a.Copy(_L("Uid: "));
		a.AppendNum(data.iUid);
		RDebug::Print(a);
		
		a.Copy(_L("Key: "));
		a.AppendNum(data.iKey);
		RDebug::Print(a);
		
		a.Copy(_L("Type: "));
		a.AppendNum((TInt)data.iType);
		RDebug::Print(a);

		
		a.Copy(_L("Min: "));
		a.AppendNum(data.iMinValue);
		RDebug::Print(a);
		
		
		a.Copy(_L("Max: "));
		a.AppendNum(data.iMaxValue);
		RDebug::Print(a);
		 
		
		a.Copy(_L("Elements in combo: "));
		a.AppendNum(data.iNumOfCombo);
		RDebug::Print(a);
		 
		
		a.Copy(_L("NeedUnlock: "));
		a.AppendNum(data.iExists);
		RDebug::Print(a);
		 
		
		TInt j=0;
		for (j=0;j<data.iNumOfCombo;j++)
			{
			TComboElement element(data.iComboElements->At(j));
			
			a.Copy(_L("Combo "));
			a.AppendNum(j);
			a.Append(_L(": "));
			a.Append(element.iDescription);
			a.Append(_L(" - description, "));
			a.AppendNum((TInt)element.iType);
			a.Append(_L(" - type, "));
			a.Append(element.iDesValue);
			a.Append(_L(" - DesVal, "));
			a.AppendNum(element.iIntValue);
			a.Append(_L(" - IntVal"));
			RDebug::Print(a);
			 
			}
		}
	}
TInt CListOfSettingsView::Exists(TInt aUid, TInt aKey,TInt aType)
	{
	TRAPD(err,{
		CRepository* testCR=CRepository::NewL(TUid::Uid(aUid));
		RArray<TUint32> arr;
		testCR->FindL(0,0,arr);
		delete testCR;
		return arr.Find((TUint32)aKey);
	};);
	if (err!=KErrNone)
		{return err;}
	}

TInt CListOfSettingsView::TestUnlock(TInt aUid)
	{
	RArray<TInt> ArrToBeReplaced;
	RArray<TInt> ArrToReplace;
	TBuf8<255> TextToBeReplaced;
	TBuf8<255> TextToReplace;
	TInt Unlocked=0;
	TBuf<255> path;
	path.Append(KCREPath);
	path.AppendNum((TUint)aUid,EHex);
	path.Append(KCREExtension);
	TBool ex=BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),path);
	//TBool ex=EFalse;
	if (ex)
		{
#ifdef _DEBUG
	RDebug::Print(_L("exists"));
	RDebug::Print(path);
#endif
		path.Copy(KCREPath);
		path.AppendNum(aUid,EHex);
		path.Append(KCREExtension);
		//2200FFFFFFFFFFFFFF
		ArrToBeReplaced.Append(0x22);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0xff);
		ArrToBeReplaced.Append(0xff);
		ArrToBeReplaced.Append(0xff);
		ArrToBeReplaced.Append(0xff);
		ArrToBeReplaced.Append(0xff);
		ArrToBeReplaced.Append(0xff);
		ArrToBeReplaced.Append(0xff);
		//2201FFFFFFFFFFFFFF
		ArrToReplace.Append(0x22);
		ArrToReplace.Append(0x01);
		ArrToReplace.Append(0xff);
		ArrToReplace.Append(0xff);
		ArrToReplace.Append(0xff);
		ArrToReplace.Append(0xff);
		ArrToReplace.Append(0xff);
		ArrToReplace.Append(0xff);
		ArrToReplace.Append(0xff);		
		}
	else
		{
#ifdef _DEBUG
	RDebug::Print(_L("not exists"));
	RDebug::Print(path);
#endif
		path.Copy(KTXTPath);
		path.AppendNum((TUint)aUid,EHex);
		path.Append(KTXTExtension);
		//616c776179736661696c - alwaysfail
		ArrToBeReplaced.Append(0x61);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0x6c);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0x77);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0x61);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0x79);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0x73);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0x66);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0x61);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0x69);
		ArrToBeReplaced.Append(0x00);
		ArrToBeReplaced.Append(0x6c);
		ArrToBeReplaced.Append(0x00);
		//616c7761797370617373 - alwayspass
		ArrToReplace.Append(0x61);
		ArrToReplace.Append(0x00);
		ArrToReplace.Append(0x6c);
		ArrToReplace.Append(0x00);
		ArrToReplace.Append(0x77);
		ArrToReplace.Append(0x00);
		ArrToReplace.Append(0x61);
		ArrToReplace.Append(0x00);
		ArrToReplace.Append(0x79);
		ArrToReplace.Append(0x00);
		ArrToReplace.Append(0x73);
		ArrToReplace.Append(0x00);
		ArrToReplace.Append(0x70);
		ArrToReplace.Append(0x00);
		ArrToReplace.Append(0x61);
		ArrToReplace.Append(0x00);
		ArrToReplace.Append(0x73);
		ArrToReplace.Append(0x00);
		ArrToReplace.Append(0x73);
		ArrToReplace.Append(0x00);
		}
	
	RFile File;
	TInt Size;
	TBool ex2=BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),path);
	
	if (!ex2){return 0;}
	_LOG(path);
	File.Open(CEikonEnv::Static()->FsSession(),path,EFileRead);
	File.Size(Size);
	
	HBufC8* FileData = HBufC8::NewL(Size);
	TPtr8 ptr= FileData->Des();
	File.Read(ptr);
	File.Close();
	
	TInt i=0;
	TChar c;
	for (i=0; i<ArrToReplace.Count();i++)
		{
		c=TChar(ArrToReplace[i]);
		TextToReplace.Append(c);
		c=TChar(ArrToBeReplaced[i]);
		TextToBeReplaced.Append(c);
		}
	
	if (!ex)
		{
		path.Copy(KTXTPathC);
		path.AppendNum((TUint)aUid,EHex);
		path.Append(KTXTExtension);
		}
	if (ex) 
		{
		TBuf<255> pathtxt;
		pathtxt.Copy(KTXTPathC);
		pathtxt.AppendNum((TUint)aUid,EHex);
		pathtxt.Append(KTXTExtension);
		if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),pathtxt))
			{BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),pathtxt);}
		}
	if (FileData->Des().Find(TextToBeReplaced)!=KErrNotFound){Unlocked=UnLock(path,FileData,TextToBeReplaced,TextToReplace);}
	delete FileData;
	return Unlocked;
	}

TInt CListOfSettingsView::UnLock(TDes& aPath,HBufC8* aText,TDes8& aTextToBeReplaced ,TDes8& aTextToReplace)
	{
	TInt i=0;
	TInt unlocked_count=0;
	
	while (aText->Find(aTextToBeReplaced)!=KErrNotFound)
		{
	
		aText->Des().Replace(aText->Find(aTextToBeReplaced),aTextToBeReplaced.Length(),aTextToReplace);
		unlocked_count++;
		}
	
	i=0;
	RFile File;
	File.Replace(CEikonEnv::Static()->FsSession(),aPath,EFileWrite);
	File.Write(aText->Des());
	File.Close();
	return unlocked_count;
	}
TInt CListOfSettingsView::Count(TPtr8 aText, TPtrC8 aTextToFind)
	{
	TInt count=0;
	TInt f=0;
	HBufC8* Text=HBufC8::NewL(aText.Length());
	Text->Des().Copy(aText);
	while (ETrue)
		{
		f=Text->Des().Find(aTextToFind);
		if (f==KErrNotFound){break;}
		Text->Des().Copy(Text->Right(f+aTextToFind.Length()));
		count++;
		}
	
	delete Text;
	return count;
	}

void CListOfSettingsView::SetTitle(TDes& aTitle)
	{
	TUid titlePaneUid;
	titlePaneUid.iUid = EEikStatusPaneUidTitle;
	CEikStatusPane* statusPane = CEikonEnv::Static()->AppUiFactory()->StatusPane();
	CEikStatusPaneBase::TPaneCapabilities subPane = statusPane->PaneCapabilities(titlePaneUid);
	if ( subPane.IsPresent() && subPane.IsAppOwned() )
		{
		CAknTitlePane* titlePane =(CAknTitlePane*) statusPane->ControlL(titlePaneUid);
		titlePane->SetTextL(aTitle);
		}
	else
		{CEikonEnv::Static()->InfoMsg(_L("Cannot change title"));}
	}

/**
 * @return The UID for this view
 */
TUid CListOfSettingsView::Id() const
	{
	return TUid::Uid( EListOfSettingsViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CListOfSettingsView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
	
		case EAknSoftkeyExit:
			commandHandled = HandleControlPaneRightSoftKeyPressedL( aCommand );
			break;
		case EListOfSettingsView_MenuItemCommand:
			commandHandled = Handle_MenuItemSelectedL( aCommand );
			break;
		case EListOfSettingsView_MenuItem1Command:
			commandHandled = Handle_MenuItem1SelectedL( aCommand );
			break;
		case EListOfSettingsView_MenuItem5Command:
			commandHandled = Handle_MenuItem5SelectedL( aCommand );
			break;
		case EListOfSettingsView_MenuItem4Command:
			commandHandled = Handle_MenuItem4SelectedL( aCommand );
			break;
		case EListOfSettingsView_MenuItem2Command:
			commandHandled = Handle_MenuItem2SelectedL( aCommand );
			break;
		case EListOfSettingsView_MenuItem3Command:
			commandHandled = Handle_MenuItem3SelectedL( aCommand );
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
	
	if (aCommand==EAllToDefault)
		{
		Handle_MenuItem4SelectedL(EAllToDefault);
		}
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CListOfSettingsView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iListOfSettings == NULL )
		{
		iListOfSettings = CreateContainerL();
		iListOfSettings->SetMopParent( this );
		AppUi()->AddToStackL( *this, iListOfSettings );
		} 
	// ]]] end generated region [Generated Contents]
	
	TUid uid=TUid::Uid(iUid);
	TInt err=0;
	iInfoCR=NULL;
	TRAP(err,
			{
			iInfoCR=CRepository::NewL(uid);
			TInt val;
			User::LeaveIfError(iInfoCR->Get(0x1,val));
			});
	if (err!=KErrNone)
		{
			TBuf<255> header(_L("TweakS"));
			TBuf<255> text;
			CEikonEnv::Static()->ReadResource(text,R_PLUGIN_NOT_WORK);
			((CTweakSAppUi*)AppUi())->GlobalMsgQuery(text,header);
			AppUi()->ActivateLocalViewL(TUid::Uid(EPluginsListViewId));
			return;
		}
	
	iSettingsData->Reset();
	ReadData();
	_LOG(_L("Data read - ok"));
	#ifdef _DEBUG
		Output();
	#endif
	SetTitle(iTitle);
	_LOG(_L("Will update"));
	iListOfSettings->Update();
	
	}

/**
 */
void CListOfSettingsView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iListOfSettings != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iListOfSettings );
		delete iListOfSettings;
		iListOfSettings = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CListOfSettingsView::HandleStatusPaneSizeChange()
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
void CListOfSettingsView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_LIST_OF_SETTINGS_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CListOfSettingsView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CListOfSettings::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CListOfSettings
 */
CListOfSettings* CListOfSettingsView::CreateContainerL()
	{
	return CListOfSettings::NewL( ClientRect(), NULL, this );
	}

/** 
 * Handle the rightSoftKeyPressed event.
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CListOfSettingsView::HandleControlPaneRightSoftKeyPressedL( TInt aCommand )
	{
	AppUi()->ActivateLocalViewL(TUid::Uid(EPluginsListViewId));
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CListOfSettingsView::Handle_MenuItemSelectedL( TInt aCommand )
	{
	//change
	if (iListOfSettings->ListBox()->Model()->NumberOfItems()==0){return ETrue;}
	iListOfSettings->iTop=iListOfSettings->ListBox()->TopItemIndex();
	iListOfSettings->iBottom=iListOfSettings->ListBox()->BottomItemIndex();
	TInt c=iListOfSettings->ListBox()->CurrentItemIndex(); 
	HandleLBEvent(-1); 
	iListOfSettings->Update(c);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CListOfSettingsView::Handle_MenuItem1SelectedL( TInt aCommand )
	{
	// about setting
	if (iListOfSettings->ListBox()->Model()->NumberOfItems()==0){return ETrue;}
	TInt i=iListOfSettings->ListBox()->CurrentItemIndex();
	TSettingData Data=iSettingsData->At(i);
	((CTweakSAppUi*)AppUi())->GlobalMsgQuery(Data.iDescription,Data.iName);
	return ETrue;
	}
				
TInt CListOfSettingsView::HandleLBEvent(TInt aTest)
	{
	TInt i=iListOfSettings->ListBox()->CurrentItemIndex();
	TSettingData Data=iSettingsData->At(i);
	if (Data.iNumOfCombo!=0 && Data.iViewType!=EViewBitMask && aTest == -1)
		{
		//combo
		if (Data.iType==EInt)
			{
			TInt combo_val;
			TInt curr=PopupMenu(Data);
			if (curr==-1){return 0;}
			combo_val=Data.iComboElements->At(curr).iIntValue;
			CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
			CR->Set(Data.iKey,combo_val);
			delete CR;
			}
		else if (Data.iType=EString)
			{
			TBuf<512> combo_val;
			TInt curr=PopupMenu(Data);
			if (curr==-1){return 0;}
			combo_val=Data.iComboElements->At(curr).iDesValue;		
			CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
			CR->Set(Data.iKey,combo_val);
			delete CR;
			}
		}
	else 
		{//not combo
			if (Data.iType==EInt)
				{
				if (aTest == 1)
					{
					if (Data.iViewType!=EViewUidNum)
						{
						TInt val;
						CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
						CR->Get(Data.iKey,val);
						if (!NumberQuery(Data,val)){return ETrue;}	
						CR->Set(Data.iKey,val);
						delete CR;
						}
					else
						{
						TBuf<255> Uid;
						TInt val;
						CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
						CR->Get(Data.iKey,val);
						Uid.Num((TUint)val, EHex);
						if (!TextQuery(Data,Uid)){return ETrue;}
						TLex conv(Uid);
						TUint Uval;
						conv.Val(Uval,EHex);
						TUid u=TUid::Uid(Uval);
						CR->Set(Data.iKey,(TInt)u.iUid);
						delete CR;
						}
					}
				else if (Data.iViewType==EViewNormal)
					{
					TInt val;
					CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
					CR->Get(Data.iKey,val);
					if (!NumberQuery(Data,val)){return 0;}
					CR->Set(Data.iKey,val);
					delete CR;
					}
				else if (Data.iViewType==EViewSlider)
					{
					TInt val;
					CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
					CR->Get(Data.iKey,val);
					val=SliderDialog(Data,val);	
					CR->Set(Data.iKey,val);
					delete CR;
					}
				else if (Data.iViewType==EViewBitMask)
					{
					TInt val;
					CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
					CR->Get(Data.iKey,val);
					val=BinaryDialog(Data,val);	
					CR->Set(Data.iKey,val);
					delete CR;
					}
				else if (Data.iViewType==EViewUidNum)
					{
					TInt val;
					CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
					CR->Get(Data.iKey,val);
					val=UIDNumSelect(Data,val);	
					CR->Set(Data.iKey,val);
					delete CR;
					}
				}
			else if (Data.iType=EString)
				{
				if (Data.iViewType==EViewNormal || aTest == 1)
					{
					TBuf<512> val;
					CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
					CR->Get(Data.iKey,val);
					if (!TextQuery(Data,val)){return 0;}	
					CR->Set(Data.iKey,val);
					delete CR;
					}
				else if (Data.iViewType==EViewUidTxt)
					{
					TBuf<512> val;
					CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
					CR->Get(Data.iKey,val);
					val=UIDTxtPopupMenu(Data,val);
					CR->Set(Data.iKey,val);
					delete CR;
					}
				else if (Data.iViewType==EViewFileName)
					{
					TBuf<512> val;
					CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
					CR->Get(Data.iKey,val);
					val=FileSelectDialog(Data,val);
					CR->Set(Data.iKey,val);
					delete CR;
					}
				else if (Data.iViewType==EViewMacAddress)
					{
					TBuf<512> val;
					CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
					CR->Get(Data.iKey,val);
					val=MacAddressDialog(Data,val);
					CR->Set(Data.iKey,val);
					delete CR;
					}
				}
			else if (Data.iType=EReal)
				{
				TReal val;
				CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
				CR->Get(Data.iKey,val);
				if (!FloatQuery(Data,val)){return 0;}	
				CR->Set(Data.iKey,val);
				delete CR;
				}
			
			//property
			else if (Data.iType==EPropertyInt)
				{
				CEikonEnv::Static()->InfoMsg(_L("property int"));
				if (Data.iViewType==EViewNormal)
					{
					TInt val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					if (!NumberQuery(Data,val)){return 0;}	
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				else if (Data.iViewType==EViewSlider)
					{
					TInt val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					val=SliderDialog(Data,val);	
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				else if (Data.iViewType==EViewBitMask)
					{
					TInt val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					val=BinaryDialog(Data,val);	
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				else if (Data.iViewType==EViewUidNum)
					{
					TInt val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					val=UIDNumSelect(Data,val);	
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				}
			else if (Data.iType=EPropertyString16)
				{
				CEikonEnv::Static()->InfoMsg(_L("property str16"));
				if (Data.iViewType==EViewUidTxt)
					{
					TBuf<255> val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					val=UIDTxtPopupMenu(Data,val);
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				else if (Data.iViewType==EViewNormal)
					{
					TBuf<255> val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					if (!TextQuery(Data,val)){return 0;}	
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				else if (Data.iViewType==EViewFileName)
					{
					TBuf<255> val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					val=FileSelectDialog(Data,val);
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				else if (Data.iViewType==EViewMacAddress)
					{
					TBuf<512> val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					val=MacAddressDialog(Data,val);
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				}
			else if (Data.iType=EPropertyString8)
				{
				CEikonEnv::Static()->InfoMsg(_L("property str8"));
				if (Data.iViewType==EViewUidTxt)
					{
					TBuf8<255> val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					TBuf<255> temp; temp.Copy(val);
					temp=UIDTxtPopupMenu(Data,temp);
					val.Copy(temp);
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				else if (Data.iViewType==EViewNormal)
					{
					TBuf8<255> val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					TBuf<255> temp; temp.Copy(val);
					if (!TextQuery(Data,temp)){return 0;}	
					val.Copy(temp);
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				else if (Data.iViewType==EViewFileName)
					{
					TBuf8<255> val;
					RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
					TBuf<255> temp; temp.Copy(val);
					temp=FileSelectDialog(Data,temp);
					val.Copy(temp);
					RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
					}
				}
		}
	return 1;
	}




void CListOfSettingsView::HandleUpDownLBEvent()
	{
#ifdef _DEBUG
	RDebug::Print(_L("UpDownEvent"));
#endif
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */



TInt CListOfSettingsView::PopupMenu(TSettingData aData)
	{
	_LIT(KListItemFormat, "%S");
	CAknSinglePopupMenuStyleListBox* list = new(ELeave) CAknSinglePopupMenuStyleListBox;
	CleanupStack::PushL(list);
	CAknPopupList* popupList = CAknPopupList::NewL(list, R_AVKON_SOFTKEYS_OK_BACK, AknPopupLayouts::EMenuWindow);
	CleanupStack::PushL(popupList);    
	list->ConstructL(popupList, CEikListBox::ELeftDownInViewRect);
	list->CreateScrollBarFrameL(ETrue);
	list->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff, CEikScrollBarFrame::EAuto);
	CDesCArray *itemList = new (ELeave) CDesCArrayFlat(3);
	TInt i=0;
	for (i=0;i<aData.iComboElements->Count();i++)
		{
		TComboElement element=aData.iComboElements->At(i);
		itemList->AppendL(element.iDescription);
		}
	list->Model()->SetItemTextArray(itemList);
	list->Model()->SetOwnershipType(ELbmOwnsItemArray);
	list->ItemDrawer()->FormattedCellData()->EnableMarqueeL( ETrue );
	popupList->SetTitleL(aData.iName);    
	CleanupStack::Pop();            // popuplist
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


TBuf<255> CListOfSettingsView::UIDTxtPopupMenu(TSettingData aData,TDes& aUids)
	{
	TInt sel=0;
	aUids.UpperCase();
		TInt def=0;
		TBuf<255> result;
		CDesCArray* itemList = new (ELeave) CDesCArrayFlat(3);
		CArrayFixFlat<TInt>* DefaultSelectedItemsList=new (ELeave) CArrayFixFlat<TInt>(3);
		TInt i=0;
		RApaLsSession AppSession;
		AppSession.Connect();
		RArray<TApplicationInfo> apps;
		TApaAppInfo appInfo;
		AppSession.GetAllApps();
		TBuf<255> UidTxt;
		while (AppSession.GetNextApp(appInfo)==KErrNone)
			{
			if (appInfo.iCaption.Length()<2){continue;}
			TApplicationInfo info;
			info.iCaption=appInfo.iCaption;
			info.iUid=appInfo.iUid;
			apps.Append(info);
			}
		AppSession.Close();
		TLinearOrder<TApplicationInfo> sortOrder(TApplicationInfo::Compare); 
		apps.Sort(sortOrder);
		for (TInt i=0;i<apps.Count();i++)
			{
			TBuf<255> item;
			item.Copy(_L("\t"));
			item.Append(apps[i].iCaption);
			item.Append(_L(" ["));
			UidTxt.Num((TUint)apps[i].iUid.iUid,EHex);
			UidTxt.UpperCase();
			item.Append(UidTxt);
			item.Append(_L("]"));
			item.Append(_L("\t"));
			itemList->AppendL(item);
			if (aUids.Find(UidTxt)!=KErrNotFound){DefaultSelectedItemsList->AppendL(i);}
			}
#ifdef __S60_50__
		CAknListQueryDialog* dlg = new ( ELeave ) CAknListQueryDialog( DefaultSelectedItemsList);
		dlg->PrepareLC( R_SISXUI_OPTIONS_QUERY );
		dlg->SetItemTextArray( itemList );
		dlg->SetTitleL(aData.iName);
		dlg->ListBox()->SetSelectionIndexesL(DefaultSelectedItemsList);    
	    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
	    ((CEikFormattedCellListBox*)(dlg->ListBox()))->ItemDrawer()->FormattedCellData()->EnableMarqueeL( ETrue );
#else
	    CAknMarkableListDialog* dlg=CAknMarkableListDialog::NewL(sel,DefaultSelectedItemsList,itemList,R_AVKON_DIALOG_EMPTY_MENUBAR,0,0);
	    dlg->PrepareLC(R_TXT_UID_SELECTION_LIST);
	    dlg->SetTitleL(aData.iName);
	    ((CEikListBox*)dlg->Control(ESelectionListControl))->SetSelectionIndexesL(DefaultSelectedItemsList);
	    ((CAknSingleStyleListBox*)dlg->Control(ESelectionListControl))->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);
#endif
	    TInt popupOk = dlg->RunLD();

		if (!popupOk)
			{
			return aUids;
			}
		else 
			{
		i=0;
		for (i=0; i<DefaultSelectedItemsList->Count(); i++)
			{
			
				_LOGDATA(_L("In select: %d"),DefaultSelectedItemsList->At(i));
				TInt uid=apps[DefaultSelectedItemsList->At(i)].iUid.iUid;
				TBuf<255> buf;
				buf.AppendNum((TUint)uid, EHex);
				buf.UpperCase();
				result.Append(buf);
				TChar c(aData.iMinValue);
				result.Append(c);
				
			}
		}
	if (result.Length()!=0) {result.Copy(result.Left(result.Length()-1));return result;}
	else {result.Copy(_L("*"));return result;}	
	}

TInt CListOfSettingsView::UIDNumSelect(TSettingData aData,TInt aUid)
	{
	TInt sel=0;
	TInt def=0;
	TBuf<255> result;
	CDesCArray* itemList = new (ELeave) CDesCArrayFlat(3);
	TInt i=0;
	RApaLsSession AppSession;
	AppSession.Connect();
	RArray<TInt> Uids;
	TApaAppInfo appInfo;
	AppSession.GetAllApps();
	TBuf<255> UidTxt;
	while (AppSession.GetNextApp(appInfo)==KErrNone)
		{
		TBuf<255> ItemTxt;
		ItemTxt.Copy(_L("\t"));
		ItemTxt.Append(appInfo.iCaption);
		ItemTxt.Append(_L(" ["));
		UidTxt.Num((TUint)appInfo.iUid.iUid,EHex);
		ItemTxt.Append(UidTxt);
		ItemTxt.Append(_L("]"));
		ItemTxt.Append(_L("\t"));
		itemList->AppendL(ItemTxt);
		Uids.Append(appInfo.iUid.iUid);
		if (appInfo.iUid.iUid==aUid){def=i;}
		i++;
		}
	AppSession.Close();
	CAknSelectionListDialog* dlg=CAknSelectionListDialog::NewL(sel,itemList,R_AVKON_DIALOG_EMPTY_MENUBAR);
	dlg->PrepareLC(R_NUM_UID_SELECTION_LIST);
	dlg->SetTitleL(aData.iName);
	((CAknSingleStyleListBox*)dlg->Control(ESelectionListControl))->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);
	//((CEikListBox*)dlg->Control(ESelectionListControl))->SetCurrentItemIndex(def);
	TInt popupOk=dlg->RunLD();

	if (!popupOk)
		{
		return aUid;
		}
	else 
		{
		TInt Uid=Uids[sel];
		return Uid;
		}
	
	}

TDes& CListOfSettingsView::FileSelectDialog(TSettingData aData, TDes& aDefault)
	{
	TBuf<255> fn;
	TTypeOfSelect sel;
	if (aData.iMinValue==1){sel=EFolder;}
	else {sel=EFile;}
	TBuf<255> KMask(_L("*"));
	TBuf<255> root;
	if (aDefault.Compare(_L(""))!=0&&BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),aDefault))
		{
		TParse p;
		CEikonEnv::Static()->FsSession().Parse(aDefault,p);
		root.Copy(p.DriveAndPath());
		}
	TInt ok=CFileSelectDialog::RunDlgLD(aData.iName,sel,root,KMask,aDefault);
	fn.Copy(aDefault);
	if (aData.iMinValue==1&&fn.Length()>3&&ok)
		{
		fn.Copy(fn.Right(fn.Length()-3));
		}
	return fn;
	
	}
TDes& CListOfSettingsView::MacAddressDialog(TSettingData aData, TDes& aDefault)
	{
	TBuf<30> hex;
	TBuf<15> newdata;
	for (TInt i=0;i<aDefault.Length();i++)
		{
		hex.AppendNum(aDefault[i],EHex);
		}
	_LOGDATA(_L("Default: %S"),&aDefault);
	_LOGDATA(_L("Hex: %S"),&hex);
	if (!TextQuery(aData,hex)){return aDefault;}
	for (TInt i=0;i<hex.Length();i++)
		{
		TInt ii;
		TChar c1(hex[i]);
		TLex conv;conv.Assign(((TUint16*)&hex[i])); conv.Val((TUint&)ii,EHex);
		TChar c2(ii);
		newdata.Append(c2);
		}
	return newdata;
	}
TInt CListOfSettingsView::SliderDialog(TSettingData aData, TInt val)
	{
	TInt res=val;
	CSliderDialog::RunDlgLD(aData.iName,res,aData.iMinValue,aData.iMaxValue);
	return res;
	}

TInt CListOfSettingsView::BinaryDialog(TSettingData aData, TInt val)
	{
	TInt fixForHide=0;
		_LIT(KBinFormat,"%b");
		TBuf<255> txt1; TBuf<255> txt;
		txt1.Format(KBinFormat,val);
		TInt i=0;
		TInt j=0;
		
		for(i=txt1.Length()-1; i>=0 ; i--)
		{//reverse
		txt.Append(txt1[i]);
		j++;
		}
		
		const TInt l=txt1.Length();
		if (l<aData.iNumOfCombo&&(aData.iNumOfCombo-l>=0))
			{
			i=0;
			for (i=0; i<(aData.iNumOfCombo-l);i++)
				{
				txt.Append(_L("0"));
				}
			}
		_LOG(_L("Reading data binary dialog, txt:"));
		_LOG(txt);
		CEikonEnv::Static()->InfoMsg(txt);
		CDesCArray* itemList = new (ELeave) CDesCArrayFlat(3);
		CArrayFixFlat<TInt>* DefaultSelectedItemsList=new (ELeave) CArrayFixFlat<TInt>(3);
		i=0;
		for (i=0;i<txt.Length();i++)
			{
			TComboElement element=aData.iComboElements->At(i);
			TBuf<255> ItemTxt;
			ItemTxt.Append(_L("\t"));
			ItemTxt.Append(element.iDescription);
			ItemTxt.Append(_L("\t"));
			if (element.iIntValue!=1)
				{
				itemList->AppendL(ItemTxt);
				if (txt[i]=='1') {DefaultSelectedItemsList->AppendL(i+fixForHide);}
				}
			else 
				{fixForHide--;}
			}
		TInt pos;
		TInt sel=0;
#ifdef __S60_50__
		CAknListQueryDialog* dlg = new ( ELeave ) CAknListQueryDialog( DefaultSelectedItemsList);
		dlg->PrepareLC( R_SISXUI_OPTIONS_QUERY );
		dlg->SetItemTextArray( itemList );
		dlg->SetTitleL(aData.iName);
		dlg->ListBox()->SetSelectionIndexesL(DefaultSelectedItemsList);    
	    dlg->SetOwnershipType( ELbmDoesNotOwnItemArray );
	    ((CEikFormattedCellListBox*)(dlg->ListBox()))->ItemDrawer()->FormattedCellData()->EnableMarqueeL( ETrue );
#else
	    CAknMarkableListDialog* dlg=CAknMarkableListDialog::NewL(sel,DefaultSelectedItemsList,itemList,R_AVKON_DIALOG_EMPTY_MENUBAR,0,0);
	    dlg->PrepareLC(R_TXT_UID_SELECTION_LIST);
	    dlg->SetTitleL(aData.iName);
	    ((CEikListBox*)dlg->Control(ESelectionListControl))->SetSelectionIndexesL(DefaultSelectedItemsList);
	    ((CAknSingleStyleListBox*)dlg->Control(ESelectionListControl))->ItemDrawer()->ColumnData()->EnableMarqueeL(ETrue);
#endif
	    TInt popupOk = dlg->RunLD();


		if (!popupOk)
			{
			return val;
			}
		else 
			{
			/* old write
			i=0;
			TChar c='0';
			txt.Fill(c,txt.Length());
			for (i=0; i<DefaultSelectedItemsList->Count(); i++)
				{
				txt.Replace (DefaultSelectedItemsList->At(i),1,_L("1"));
				}
			*/
			
			//txt.Fill(c,txt.Length());    
			TBuf<512> temp;
			TInt log;
			for (log=0;log<DefaultSelectedItemsList->Count();log++)
				{temp.AppendNum(DefaultSelectedItemsList->At(log)); temp.Append(_L(", "));}
			_LOG(_L("writing data binary dialog, default selected items list:"));
			_LOG(temp);
			_LOG(_L("writing data binary dialog, txt:"));
			_LOG(txt);
			TKeyArrayFix key(0,ECmpNormal);
			TInt pos;
			fixForHide = 0;
			for (i=0; i<txt.Length(); i++)
				{
				TKeyArrayFix key(i,ECmpNormal);
				TComboElement element=aData.iComboElements->At(i);
				if (element.iIntValue==1) {fixForHide--;}
				else
					{
					TBool found=EFalse;
					for (TInt j=0; j<DefaultSelectedItemsList->Count();j++)
						{if (DefaultSelectedItemsList->At(j)==i+fixForHide){found=ETrue; break;} else {found=EFalse;}}
					if (found) 
						{
						txt.Replace (i ,1,_L("1"));
						}
					else 
						{
						txt.Replace (i ,1,_L("0"));
						}
					}
#ifdef _DEBUG
				TBuf<255> b;
				b.AppendNum(i);
				b.Append(_L(" "));
				b.Append(txt);
				_LOG(b);
#endif
				}
			}
	
		TBuf<255> txt2;
		j=0;
		for(i=txt.Length()-1; i>=0 ; i--)
		{
		txt2.Append(txt[i]);
		j++;
		}
		
		TLex lex=(txt2);
		TUint v;
		lex.Val(v,EBinary);
		return v;
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CListOfSettingsView::Handle_MenuItem3SelectedL( TInt aCommand )
	{
	//back
	AppUi()->ActivateLocalViewL(TUid::Uid(EPluginsListViewId));
	return ETrue;
	}
				
TInt CListOfSettingsView::NumberQuery(TSettingData aData,TInt& aNumber)
{
	CAknNumberQueryDialog* Dialog = CAknNumberQueryDialog::NewL(aNumber,CAknQueryDialog::ENoTone);
	Dialog->PrepareLC(R_NUMBER_QUERY);
	Dialog->SetPromptL(aData.iName);
	if (aData.iViewType!=EViewBitMask)
		{Dialog->SetMinimumAndMaximum(aData.iMinValue,aData.iMaxValue);}
	else {Dialog->SetMinimumAndMaximum(0,KMaxTInt);}
	
	return Dialog->RunLD();	
}

TInt CListOfSettingsView::TextQuery(TSettingData aData, TDes& aBuffer)
{
	CAknTextQueryDialog* Dialog =
CAknTextQueryDialog::NewL(aBuffer,CAknQueryDialog::ENoTone);
	Dialog->PrepareLC(R_TEXT_QUERY);
	Dialog->SetPromptL(aData.iName);
	Dialog->SetMaxLength(aData.iMaxValue);
	return Dialog->RunLD();
}

TInt CListOfSettingsView::FloatQuery(TSettingData aData,TReal& aNumber)
{
	CAknFloatingPointQueryDialog* Dialog = CAknFloatingPointQueryDialog::NewL(aNumber,CAknQueryDialog::ENoTone);
	Dialog->PrepareLC(R_FLOAT_QUERY);
	Dialog->SetPromptL(aData.iName);
	Dialog->SetMinimumAndMaximum(aData.iMinValue,aData.iMaxValue);
	return Dialog->RunLD();	
}
CListOfSettings* CListOfSettingsView::GetContainer()
	{
	return iListOfSettings;
	}
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CListOfSettingsView::Handle_MenuItem4SelectedL( TInt aCommand )
	{
	//reset to default
	if (iListOfSettings->ListBox()->Model()->NumberOfItems()==0){return ETrue;}
	if (aCommand!=EAllToDefault)
		{
		TInt i=iListOfSettings->ListBox()->CurrentItemIndex();
		
		TSettingData data=iSettingsData->At(i);
		if (data.iType==EPropertyInt||data.iType==EPropertyString8||data.iType==EPropertyString16)
			{
			TBuf<1> header(_L(""));
			TBuf<255> text;
			CEikonEnv::Static()->ReadResource(text,R_OPTION_UNVAILABLE);
			((CTweakSAppUi*)AppUi())->GlobalMsgQuery(text,header);
			return ETrue;
			}
		CRepository* CR=CRepository::NewL(TUid::Uid(data.iUid));
		CR->Reset(data.iKey);
		delete CR;
		}
	else
		{
		TBuf<255> txt,header;
		header.Copy(_L("TweakS"));
		CEikonEnv::Static()->ReadResource(txt,R_DELCRE);
		TBool del=((CTweakSAppUi*)AppUi())->GlobalMsgQuery(txt,header);
		for (TInt i=0;i<iSettingsData->Count();i++)
			{
			TSettingData data=iSettingsData->At(i);
			if (data.iType==EPropertyInt||data.iType==EPropertyString8||data.iType==EPropertyString16)
				{
				TBuf<1> header(_L(""));
				TBuf<255> text;
				CEikonEnv::Static()->ReadResource(text,R_OPTION_UNVAILABLE);
				((CTweakSAppUi*)AppUi())->GlobalMsgQuery(text,header);
				return ETrue;
				}
			CRepository* CR=CRepository::NewL(TUid::Uid(data.iUid));
			CR->Reset();
			delete CR;
			if (del)
				{
				TBuf<255> path;
				path.Copy(KCREPath);
				path.AppendNum((TUint)data.iUid,EHex);
				path.Append(KCREExtension);
				_LOGDATA(_L("Will delete %S"),&path);
				if (BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),path)){BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),path);}
				}
			}
		}
	iListOfSettings->iTop=iListOfSettings->ListBox()->TopItemIndex();
	iListOfSettings->iBottom=iListOfSettings->ListBox()->BottomItemIndex();
	iListOfSettings->Update();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CListOfSettingsView::Handle_MenuItem2SelectedL( TInt aCommand )
	{
	//clear
#ifdef _DEBUG
	RDebug::Print(_L("Clear"));
#endif
	if (iListOfSettings->ListBox()->Model()->NumberOfItems()==0){return ETrue;}
	TInt i=iListOfSettings->ListBox()->CurrentItemIndex();
	TSettingData Data=iSettingsData->At(i);
	CRepository* CR=NULL;
	if (Data.iType!=EPropertyInt&&Data.iType!=EPropertyString8&&Data.iType!=EPropertyString16)
		{CR=CRepository::NewL(TUid::Uid(Data.iUid));}
	if (Data.iType==EInt){TInt j=0; CR->Set(Data.iKey,j);}
	else if (Data.iType==EReal){TReal r=0.0; CR->Set(Data.iKey,r);}
	else if (Data.iType==EString){TBuf<255> a(_L("")); CR->Set(Data.iKey,a);}
	else if (Data.iType==EPropertyString16){TBuf<255> a(_L("")); RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,a);}
	else if (Data.iType==EPropertyString16){TBuf8<255> a(_L8("")); RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,a);}
	else if (Data.iType==EPropertyInt){TInt a=0; RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,a);}
	if (CR){delete CR;}
	iListOfSettings->iTop=iListOfSettings->ListBox()->TopItemIndex();
	iListOfSettings->iBottom=iListOfSettings->ListBox()->BottomItemIndex();
	iListOfSettings->Update(i);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CListOfSettingsView::Handle_MenuItem5SelectedL( TInt aCommand )
	{
	//handy input
	
	if (iListOfSettings->ListBox()->Model()->NumberOfItems()==0){return ETrue;}
	iListOfSettings->iTop=iListOfSettings->ListBox()->TopItemIndex();
	iListOfSettings->iBottom=iListOfSettings->ListBox()->BottomItemIndex();
	TInt c=iListOfSettings->ListBox()->CurrentItemIndex(); 
	HandleLBEvent(1); 
	iListOfSettings->Update(c);
	return ETrue;
	
	/*if (iListOfSettings->ListBox()->Model()->NumberOfItems()==0){return ETrue;}
	TInt i=iListOfSettings->ListBox()->CurrentItemIndex();
	_LOGDATA(_L("Current item (Handle_MenuItem5SelectedL): %d"),i);
	TSettingData Data=iSettingsData->At(i);
	if (Data.iType==EInt)
		{
		if (Data.iViewType!=EViewUidNum)
			{
			TInt val;
			CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
			CR->Get(Data.iKey,val);
			if (!NumberQuery(Data,val)){return ETrue;}	
			CR->Set(Data.iKey,val);
			delete CR;
			}
		else
			{
			TBuf<255> Uid;
			TInt val;
			CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
			CR->Get(Data.iKey,val);
			Uid.Num((TUint)val, EHex);
			if (!TextQuery(Data,Uid)){return ETrue;}
			TLex conv(Uid);
			TUint Uval;
			conv.Val(Uval,EHex);
			TUid u=TUid::Uid(Uval);
			CR->Set(Data.iKey,(TInt)u.iUid);
			delete CR;
			}
		}
	else if (Data.iType==EString)
		{
		TBuf<255> val;
		CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
		CR->Get(Data.iKey,val);
		if (!TextQuery(Data,val)){return ETrue;}	
		CR->Set(Data.iKey,val);
		delete CR;
		}
	else if (Data.iType=EReal)
		{
		TReal val;
		CRepository* CR=CRepository::NewL(TUid::Uid(Data.iUid));
		CR->Get(Data.iKey,val);
		if (!FloatQuery(Data,val)){return ETrue;}	
		CR->Set(Data.iKey,val);
		delete CR;
		}
	else if (Data.iType==EPropertyInt)
		{
		if (Data.iViewType!=EViewUidNum)
			{
			TInt val;
			RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
			if (!NumberQuery(Data,val)){return ETrue;}	
			RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
			}
		else
			{
			TBuf<255> Uid;
			TInt val;
			RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
			Uid.Num((TUint)val, EHex);
			if (!TextQuery(Data,Uid)){return ETrue;}
			TLex conv(Uid);
			TUint Uval;
			conv.Val(Uval,EHex);
			TUid u=TUid::Uid(Uval);
			RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,(TInt)u.iUid);
			}
		}
	else if (Data.iType==EPropertyString16)
		{
		TBuf<255> val;
		RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
		if (!TextQuery(Data,val)){return ETrue;}	
		RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
		}
	else if (Data.iType==EPropertyString8)
		{
		TBuf8<255> val;
		TBuf<255> temp;
		RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
		temp.Copy(val);
		if (!TextQuery(Data,temp)){return ETrue;}	
		val.Copy(temp);
		RProperty::Set(TUid::Uid(Data.iUid),Data.iKey,val);
		}
	iListOfSettings->iTop=iListOfSettings->ListBox()->TopItemIndex();
	iListOfSettings->Update();
	return ETrue;*/
	}
void CListOfSettingsView::GetS60PlatformVersionL( RFs& aFs, TInt& aMajor, TInt& aMinor )
    {
	_LIT(KS60ProductIDFile, "Series60v*.sis");
	_LIT(KROMInstallDir, "z:\\system\\install\\");
    TFindFile ff( aFs );
    CDir* result;
    User::LeaveIfError( ff.FindWildByDir( KS60ProductIDFile, KROMInstallDir, result ) );
    CleanupStack::PushL( result );
    User::LeaveIfError( result->Sort( ESortByName|EDescending ) );
    aMajor = (*result)[0].iName[9] - '0';
    aMinor = (*result)[0].iName[11] - '0';
    CleanupStack::PopAndDestroy(); // result
    }
				
