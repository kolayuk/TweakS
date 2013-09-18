/*
========================================================================
 Name        : ListOfSettings.cpp
 Author      : Kolay
 Copyright   : Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <aknviewappui.h>
#include <eikappui.h>
#include <TweakS.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "ListOfSettings.h"
#include "ListOfSettingsView.h"
#include "TweakS.hrh"
#include "PluginsList.hrh"
#include "ListOfSettings.hrh"
#include "PluginsManager.hrh"
#include "SettingList.hrh"
#include "AddingPlugin.hrh"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]


#include <SettingData.h>
#include <APGCLI.H>
#include <e32property.h>
#include <logger.h>
/**
 * First phase of Symbian two-phase construction. Should not 
 * contain any code that could leave.
 */
CListOfSettings::CListOfSettings()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iListBox = NULL;
	// ]]] end generated region [Generated Contents]
	
	}
/** 
 * Destroy child controls.
 */
CListOfSettings::~CListOfSettings()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iListBox;
	iListBox = NULL;
	iListBoxEventDispatch.Close();		
	// ]]] end generated region [Generated Contents]
	
	}
				
/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is not left on cleanup stack.
 * @param aRect bounding rectangle
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return initialized instance of CListOfSettings
 */
CListOfSettings* CListOfSettings::NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	CListOfSettings* self = CListOfSettings::NewLC( 
			aRect, 
			aParent, 
			aCommandObserver );
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is left on cleanup stack.
 * @param aRect The rectangle for this window
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return new instance of CListOfSettings
 */
CListOfSettings* CListOfSettings::NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	CListOfSettings* self = new ( ELeave ) CListOfSettings();
	CleanupStack::PushL( self );
	self->ConstructL( aRect, aParent, aCommandObserver );
	return self;
	}
			
/**
 * Construct the control (second phase).
 *  Creates a window to contain the controls and activates it.
 * @param aRect bounding rectangle
 * @param aCommandObserver command observer
 * @param aParent owning parent, or NULL
 */ 
void CListOfSettings::ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	if ( aParent == NULL )
	    {
		CreateWindowL();
	    }
	else
	    {
	    SetContainerWindowL( *aParent );
	    }
	
	
	iFocusControl = NULL;
	iCommandObserver = aCommandObserver;
	InitializeControlsL();
	SetRect( aRect );
	iListBox->ItemDrawer()->ColumnData()->EnableMarqueeL( ETrue );
	iListBox->CreateScrollBarFrameL( ETrue );
	iListBox->ScrollBarFrame()->SetScrollBarVisibilityL( CEikScrollBarFrame::EOn, CEikScrollBarFrame::EAuto );
	iListBox->UpdateScrollBarsL();
	TBuf<255> txt;
	CEikonEnv::Static()->ReadResource(txt,R_LISTBOX_EMPTY);
	//iListBox->View()->SetListEmptyTextL(txt);
	ActivateL();
	// [[[ begin generated region: do not modify [Post-ActivateL initializations]
	// ]]] end generated region [Post-ActivateL initializations]
	}
			
/**
* Return the number of controls in the container (override)
* @return count
*/
TInt CListOfSettings::CountComponentControls() const
	{
	return ( int ) ELastControl;
	}
				
/**
* Get the control with the given index (override)
* @param aIndex Control index [0...n) (limited by #CountComponentControls)
* @return Pointer to control
*/
CCoeControl* CListOfSettings::ComponentControl( TInt aIndex ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	switch ( aIndex )
		{
	case EListBox:
		return iListBox;
		}
	// ]]] end generated region [Generated Contents]
	
	// handle any user controls here...
	
	return NULL;
	}
				
/**
 *	Handle resizing of the container. This implementation will lay out
 *  full-sized controls like list boxes for any screen size, and will layout
 *  labels, editors, etc. to the size they were given in the UI designer.
 *  This code will need to be modified to adjust arbitrary controls to
 *  any screen size.
 */				
void CListOfSettings::SizeChanged()
	{
	CCoeControl::SizeChanged();
	LayoutControls();
	// [[[ begin generated region: do not modify [Generated Contents]
			
	// ]]] end generated region [Generated Contents]
	
	}
void CListOfSettings::Update(TInt aIndex)
	{
	_LOG(_L("Update"));
	TInt i=0;
	TInt d=0;
	TInt currItem=-1;
	CDesCArray* itemArray = static_cast< CDesCArray* > ( iListBox->Model()->ItemTextArray() );
	if (ListBox()->Model()->NumberOfItems()!=0)
		{
			currItem=ListBox()->CurrentItemIndex();
			if (aIndex==-1)
				{itemArray->Reset();}
		}
	_LOGDATA(_L("Current item (stage 1): %d"),currItem);
	if (aIndex==-1)
		{
		for (i=0;i<((CListOfSettingsView*)iCommandObserver)->iSettingsData->Count();i++)
			{
			TBuf<1024> LBBuffer;
			TSettingData Data=((CListOfSettingsView*)iCommandObserver)->iSettingsData->At(i);
			CreateLBBufferForSetting(Data,LBBuffer);
			AddListBoxItemL(iListBox,LBBuffer);
			_LOGDATA(_L("Adding listbox, iteration %d"),i)
			}
		}
	else
		{
		TBuf<1024> LBBuffer;
		TSettingData Data=((CListOfSettingsView*)iCommandObserver)->iSettingsData->At(aIndex);
		CreateLBBufferForSetting(Data,LBBuffer);
		TInt b=ListBox()->Model()->NumberOfItems();
		TBuf<1024> prev = ListBox()->Model()->ItemText(aIndex);
		CDesCArray* itemArray = static_cast<CDesCArray*> (ListBox()->Model()->ItemTextArray());
		itemArray->Delete(aIndex);
		itemArray->InsertL(aIndex,LBBuffer);
		}
	_LOG(_L("Cases end"));
	_LOGDATA(_L("Current item: %d"),currItem);
	_LOGDATA(_L("iTop: %d"),iTop);
	_LOGDATA(_L("iBottom: %d"),iBottom);
	TInt scrX=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
	TInt scrY=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;	

	if (currItem>=0) {ListBox()->SetCurrentItemIndex(currItem);}
	if (iTop>0&&(scrY>scrX))
		{
		TInt between=ListBox()->BottomItemIndex()-ListBox()->TopItemIndex();
		_LOGDATA(_L("Between: %d"),between);
		if (between==7) // N8
			{ListBox()->SetTopItemIndex(iTop+2);}
		else if (between==8) //5800
			{ListBox()->SetTopItemIndex(iTop+1);}
		else
			{ListBox()->SetTopItemIndex(iTop);}
		}
	else if (iTop>0&&(scrX>scrY))
		{
		ListBox()->SetTopItemIndex(iTop);
		}

	_LOGDATA(_L("Top Index: %d"),ListBox()->TopItemIndex());
	ListBox()->DrawNow();
	_LOG(_L("Exit update"));
	}

void CListOfSettings::CreateLBBufferForSetting(TSettingData aData,TDes& LBBuffer)
	{
	TBuf<500> TDesValue;
	CRepository* CR=NULL;
	TSettingData Data=aData;
	if (Data.iType!=EPropertyInt&&Data.iType!=EPropertyString16&&Data.iType!=EPropertyString8)
	{CR=CRepository::NewL(TUid::Uid(Data.iUid));}
	_LOG(_L("CR Initialized"));
	if (Data.iType==EInt)
		{
		if (Data.iViewType!=EViewUidNum&&Data.iViewType!=EViewBitMask)
		{
		TInt val;
		CR->Get(Data.iKey,val);
		if (Data.iNumOfCombo!=0&&Data.iViewType!=EViewBitMask)
			{
			TInt j=0;
			TDesValue.Num(val);
			for (j=0;j<Data.iNumOfCombo;j++)
				{
				if (val==Data.iComboElements->At(j).iIntValue){TDesValue.Copy(Data.iComboElements->At(j).iDescription);}
				
				}
			}
		else {TDesValue.AppendNum(val);}
		}
		else if (Data.iViewType==EViewUidNum) //UidNum
			{
			TInt val;
			TBuf<255> UidTxt;
			CR->Get(Data.iKey,val);
			RApaLsSession AppSession;
			AppSession.Connect();
			TApaAppInfo info;
			TUid uid=TUid::Uid(val);
			UidTxt.Num((TUint)val,EHex);
			AppSession.GetAppInfo(info,uid);
			TDesValue.Copy(info.iCaption);
			TDesValue.Append(_L(" ["));
			TDesValue.Append(UidTxt);
			TDesValue.Append(_L("]"));
			AppSession.Close();
			}
		else if (Data.iViewType==EViewBitMask)
			{
			CEikonEnv::Static()->ReadResource(TDesValue,R_BINARY_ITEM_TXT);
			}
		}
	else if (Data.iType==EReal)
		{
		TReal val;
		CR->Get(Data.iKey,val);
		TDesValue.AppendNum(val);
		}
	else if (Data.iType==EString)
		{
		_LOG(_L("Adding text item..."));
		TBuf<512> val;
		CR->Get(Data.iKey,val);
		if (Data.iNumOfCombo!=0)
			{
			TInt j=0;
			for (j=0;j<Data.iNumOfCombo;j++)
				{
				if (val==Data.iComboElements->At(j).iDesValue){TDesValue.Append(Data.iComboElements->At(j).iDescription);}
				}
			}
		TDesValue.Append(val);
		}
	else if (Data.iType==EPropertyInt)
		{
		TInt val;
		RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
		TDesValue.AppendNum(val);
		}
	else if (Data.iType==EPropertyString16)
		{
		TBuf<512> val;
		RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
		TDesValue.Append(val);
		}
	else if (Data.iType==EPropertyString8)
		{
		TBuf8<512> val;
		RProperty::Get(TUid::Uid(Data.iUid),Data.iKey,val);
		TDesValue.Copy(val);
		}
	if(CR){delete CR;}
	CreateListBoxItemL(LBBuffer,Data.iName,TDesValue);
	_LOG(_L("CreateListBoxItemL done"));
	_LOGDATA(_L("LBBuffer: %S"),&LBBuffer);
	}

// [[[ f begin generated function: do not modify
/**
 * Layout components as specified in the UI Designer
 */
void CListOfSettings::LayoutControls()
	{
	iListBox->SetExtent( TPoint( 0, 0 ), iListBox->MinimumSize() );
	}
// ]]] end generated function

/**
 *	Handle key events.
 */				
TKeyResponse CListOfSettings::OfferKeyEventL( 
		const TKeyEvent& aKeyEvent, 
		TEventCode aType )
	{
	
	// [[[ begin generated region: do not modify [Generated Contents]
	if ( aKeyEvent.iCode == EKeyLeftArrow 
		|| aKeyEvent.iCode == EKeyRightArrow )
		{
		// Listbox takes all events even if it doesn't use them
		return EKeyWasNotConsumed;
		}
	
	// ]]] end generated region [Generated Contents]
	
	if ( iFocusControl != NULL
		&& iFocusControl->OfferKeyEventL( aKeyEvent, aType ) == EKeyWasConsumed )
		{
		return EKeyWasConsumed;
		}
	return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
	}
				
// [[[ begin generated function: do not modify
/**
 *	Initialize each control upon creation.
 */				
void CListOfSettings::InitializeControlsL()
	{
	iListBox = new ( ELeave ) CAknSettingStyleListBox;
	iListBox->SetContainerWindowL( *this );
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_LIST_OF_SETTINGS_LIST_BOX );
		iListBox->ConstructFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
	// the listbox owns the items in the list and will free them
	iListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
	
	// setup the icon array so graphics-style boxes work
	SetupListBoxIconsL();
	
	iListBox->SetListBoxObserver( this );
	AddListBoxEventHandlerL( 
			iListBox, 
			EEventEnterKeyPressed, 
			&CListOfSettings::HandleListBoxEnterKeyPressedL );
	AddListBoxEventHandlerL( 
			iListBox, 
			EEventItemSingleClicked, 
			&CListOfSettings::HandleListBoxItemClickedL );
	
	// add list items
	
	iListBox->SetFocus( ETrue );
	iFocusControl = iListBox;
	
	}
// ]]] end generated function

/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CListOfSettings::HandleResourceChange( TInt aType )
	{
	CCoeControl::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( EListOfSettingsViewId ) )->ClientRect() );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}
				
/**
 *	Draw container contents.
 */				
void CListOfSettings::Draw( const TRect& aRect ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );
	
	// ]]] end generated region [Generated Contents]
	
	}
				
// [[[ begin generated function: do not modify
/**
 *	Add a list box item to a list.
 */
void CListOfSettings::AddListBoxItemL( 
		CEikTextListBox* aListBox,
		const TDesC& aString )
	{
	CTextListBoxModel* model = aListBox->Model();
	CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
	itemArray->AppendL( aString );
	aListBox->HandleItemAdditionL();
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Get the array of selected item indices, with respect to the list model.
 * The array is sorted in ascending order.
 * The array should be destroyed with two calls to CleanupStack::PopAndDestroy(),
 * the first with no argument (referring to the internal resource) and the
 * second with the array pointer.
 * @return newly allocated array, which is left on the cleanup stack;
 *	or NULL for empty list. 
 */
RArray< TInt >* CListOfSettings::GetSelectedListBoxItemsLC( CEikTextListBox* aListBox )
	{
	CAknFilteredTextListBoxModel* model = 
		static_cast< CAknFilteredTextListBoxModel *> ( aListBox->Model() );
	if ( model->NumberOfItems() == 0 )
		return NULL;
		
	// get currently selected indices
	const CListBoxView::CSelectionIndexArray* selectionIndexes =
		aListBox->SelectionIndexes();
	TInt selectedIndexesCount = selectionIndexes->Count();
	if ( selectedIndexesCount == 0 )
		return NULL;
		
	// copy the indices and sort numerically
	RArray<TInt>* orderedSelectedIndices = 
		new (ELeave) RArray< TInt >( selectedIndexesCount );
	
	// push the allocated array
	CleanupStack::PushL( orderedSelectedIndices );
	
	// dispose the array resource
	CleanupClosePushL( *orderedSelectedIndices );
	
	// see if the search field is enabled
	CAknListBoxFilterItems* filter = model->Filter();
	if ( filter != NULL )
		{
		// when filtering enabled, translate indices back to underlying model
		for ( TInt idx = 0; idx < selectedIndexesCount; idx++ )
			{
			TInt filteredItem = ( *selectionIndexes ) [ idx ];
			TInt actualItem = filter->FilteredItemIndex ( filteredItem );
			orderedSelectedIndices->InsertInOrder( actualItem );
			}
		}
	else
		{
		// the selection indices refer directly to the model
		for ( TInt idx = 0; idx < selectedIndexesCount; idx++ )
			orderedSelectedIndices->InsertInOrder( ( *selectionIndexes ) [ idx ] );
		}	
		
	return orderedSelectedIndices;
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Delete the selected item or items from the list box.
 */
void CListOfSettings::DeleteSelectedListBoxItemsL( CEikTextListBox* aListBox )
	{
	CAknFilteredTextListBoxModel* model = 
		static_cast< CAknFilteredTextListBoxModel *> ( aListBox->Model() );
	if ( model->NumberOfItems() == 0 )
		return;
	
	RArray< TInt >* orderedSelectedIndices = GetSelectedListBoxItemsLC( aListBox );		
	if ( !orderedSelectedIndices )
		return;
		
	// Delete selected items from bottom up so indices don't change on us
	CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
	TInt currentItem = 0;
	
	for ( TInt idx = orderedSelectedIndices->Count(); idx-- > 0; ) 
		{
		currentItem = ( *orderedSelectedIndices )[ idx ];
		itemArray->Delete ( currentItem );
		}
	
	// dispose the array resources
	CleanupStack::PopAndDestroy();
	
	// dispose the array pointer
	CleanupStack::PopAndDestroy( orderedSelectedIndices );
	
	// refresh listbox's cursor now that items are deleted
	AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(
		aListBox, currentItem, ETrue );
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Get the listbox.
 */
CAknSettingStyleListBox* CListOfSettings::ListBox()
	{
	return iListBox;
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Create a list box item with the given column values.
 */
void CListOfSettings::CreateListBoxItemL( TDes& aBuffer, 
		const TDesC& aMainText,
		const TDesC& aSecondaryText )
	{
	_LIT ( KStringHeader, "\t%S\t\t%S" );
	
	aBuffer.Format( KStringHeader(), &aMainText, &aSecondaryText );
	} 
				
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Add an item to the list by reading the text items from the array resource
 *	and setting a single image property (if available) from an index
 *	in the list box's icon array.
 *	@param aResourceId id of an ARRAY resource containing the textual
 *	items in the columns
 *	
 */
void CListOfSettings::AddListBoxResourceArrayItemL( TInt aResourceId )
	{
	CDesCArray* array = iCoeEnv->ReadDesCArrayResourceL( aResourceId );
	CleanupStack::PushL( array );
	// This is intended to be large enough, but if you get 
	// a USER 11 panic, consider reducing string sizes.
	TBuf<512> listString; 
	CreateListBoxItemL( listString, ( *array ) [ 0 ], ( *array ) [ 1 ] );
	AddListBoxItemL( iListBox, listString );
	CleanupStack::PopAndDestroy( array );
	} 
				
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Set up the list's icon array.
 */
void CListOfSettings::SetupListBoxIconsL()
	{
	CArrayPtr< CGulIcon >* icons = NULL;		
	
	if ( icons != NULL )
		{
		iListBox->ItemDrawer()->ColumnData()->SetIconArray( icons );
		}
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/** 
 *	Handle commands relating to markable lists.
 */
TBool CListOfSettings::HandleMarkableListCommandL( TInt aCommand )
	{
	return EFalse;
	}

// ]]] end generated function

/** 
 * Override of the HandleListBoxEventL virtual function
 */
void CListOfSettings::HandleListBoxEventL( 
		CEikListBox* aListBox,
		TListBoxEvent anEventType )
	{
	for (int i = 0; i < iListBoxEventDispatch.Count(); i++)
		{
		const TListBoxEventDispatch& currEntry = iListBoxEventDispatch[i];
		if ( currEntry.src == aListBox && currEntry.event == anEventType )
			{
			( this->*currEntry.handler )( aListBox, anEventType );
			break;
			}
		}
	}

/** 
 * Helper function to register MEikListBoxObserver event handlers
 */
void CListOfSettings::AddListBoxEventHandlerL( 
		CEikListBox* aListBox,
		TListBoxEvent anEvent,
		ListBoxEventHandler aHandler )
	{
	TListBoxEventDispatch entry;
	entry.src = aListBox;
	entry.event = anEvent;
	entry.handler = aHandler;
	TInt err = iListBoxEventDispatch.Append( entry );
	User::LeaveIfError( err );
	}

/**
 *	Handle the itemClicked event
 */
void CListOfSettings::HandleListBoxItemClickedL( 
		CEikListBox* aListBox,
		TListBoxEvent anEventType )
	{
	iTop=ListBox()->TopItemIndex();
	TInt c=iListBox->CurrentItemIndex();
	_LOGDATA(_L("iTop (item clicked): %d"),iTop);
	((CListOfSettingsView*)iCommandObserver)->HandleLBEvent(-1);	
	Update(c);
	}

/**
 *	Handle the enterKeyPressed event
 */
void CListOfSettings::HandleListBoxEnterKeyPressedL( 
		CEikListBox* aListBox,
		TListBoxEvent anEventType )
	{
	iTop=ListBox()->TopItemIndex();
	TInt c=iListBox->CurrentItemIndex();
	_LOGDATA(_L("iTop (enter pressed): %d"),iTop);
	((CListOfSettingsView*)iCommandObserver)->HandleLBEvent(-1);	
	Update(c);
	}
void CListOfSettings::UpDownEvent()
	{
	}
