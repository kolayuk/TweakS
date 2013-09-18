/*
========================================================================
 Name        : ListOfSettingsView.h
 Author      : Kolay
 Copyright   : Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef LISTOFSETTINGSVIEW_H
#define LISTOFSETTINGSVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CListOfSettings;
// ]]] end generated region [Generated Forward Declarations]

#include <centralrepository.h>
#include <SettingData.h>
#include <aknselectionlist.h>

/*
class CMyMultiSelectionDialog: public CAknMarkableListDialog
	{
public:
	static CMyMultiSelectionDialog* NewL( TInt &aOpenedItem,
	                                                  CArrayFix<TInt> *aSelectedItems,
	                                                  MDesCArray *aArray,
	                                                  TInt aMenuBarResourceId,
	                                                  TInt aOkMenuBarId,
	                                                  MEikCommandObserver *aObserver =0 );
	
	static CMyMultiSelectionDialog* NewLC( TInt &aOpenedItem,
	                                                   CArrayFix<TInt> *aSelectedItems,
	                                                   MDesCArray *aArray,
	                                                   TInt aMenuBarResourceId,
	                                                   TInt aOkMenuBarId,
	                                                   MEikCommandObserver *aObserver =0 );
	
	CMyMultiSelectionDialog( TInt &aOpenedItem,
	                                     CArrayFix<TInt> *aSelectedItems,
	                                     MDesCArray *aArray,
	                                     TInt aMenuBarResourceId,
	                                     TInt aOkMenuBarResourceId,
	                                     MEikCommandObserver *aObserver );
	TBool OkToExitL(TInt aButtonId);
	};
*/

/**
 * Avkon view class for ListOfSettingsView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CListOfSettingsView ListOfSettingsView.h
 */						
			
class CListOfSettingsView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CListOfSettingsView();
	static CListOfSettingsView* NewL();
	static CListOfSettingsView* NewLC();        
	void ConstructL();
	virtual ~CListOfSettingsView();
	static void SetTitle(TDes&);
	void Active(TUint aUid, TDes&);
	CRepository* iInfoCR;					
	// from base class CAknView
	TUid Id() const;
	
	void HandleCommandL( TInt aCommand );
	void ReadData();
	CArrayFixSeg<TSettingData>* iSettingsData;
	static TInt TestUnlock(TInt aUid);
	void Output();
	TInt HandleLBEvent(TInt aTest);
	void HandleUpDownLBEvent();
	void GetS60PlatformVersionL( RFs& aFs, TInt& aMajor, TInt& aMinor );
	//void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
	static TInt PopupMenu(TSettingData aData);
	TInt NumberQuery(TSettingData aData,TInt& aNumber);
	TInt TextQuery(TSettingData aData, TDes& aBuffer);
	TInt FloatQuery(TSettingData aData, TReal& aNumber);
	TBuf<255> UIDTxtPopupMenu(TSettingData,TDes&);
	static TInt UIDNumSelect(TSettingData,TInt);
	TDes& MacAddressDialog(TSettingData, TDes& aDefault);
	static TDes& FileSelectDialog(TSettingData, TDes& aDefault);
	TInt SliderDialog(TSettingData aData, TInt val);
	TInt BinaryDialog(TSettingData aData, TInt val);
	CListOfSettings* GetContainer();
	TInt Exists(TInt, TInt,TInt);
	static TInt UnLock(TDes& aPath, HBufC8* aText,TDes8& aTextToBeReplaced ,TDes8& aTextToReplace);
	TInt Count (TPtr8 aDes, TPtrC8 aDesToFind);
	static void Restart();
	TUint iUid;
	TBuf<255> iTitle;
	// [[[ begin generated region: do not modify [Generated Methods]
	CListOfSettings* CreateContainerL();
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	
	
	// [[[ begin [Protected Section]
protected:
	// from base class CAknView
	void DoActivateL(
		const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId,
		const TDesC8& aCustomMessage );
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
	
	// [[[ begin generated region: do not modify [Overridden Methods]
	// ]]] end generated region [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
	TBool HandleControlPaneRightSoftKeyPressedL( TInt aCommand );
	TBool Handle_MenuItemSelectedL( TInt aCommand );
	TBool Handle_MenuItem1SelectedL( TInt aCommand );
	TBool Handle_MenuItem3SelectedL( TInt aCommand );
	TBool Handle_MenuItem4SelectedL( TInt aCommand );
	TBool Handle_MenuItem2SelectedL( TInt aCommand );
	TBool Handle_MenuItem5SelectedL( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CListOfSettings* iListOfSettings;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // LISTOFSETTINGSVIEW_H
