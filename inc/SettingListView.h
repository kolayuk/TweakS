/*
========================================================================
 Name        : SettingListView.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef SETTINGLISTVIEW_H
#define SETTINGLISTVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CSettingList;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for SettingListView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CSettingListView SettingListView.h
 */						
	

class CSettingListView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CSettingListView();
	static CSettingListView* NewL();
	static CSettingListView* NewLC();        
	void ConstructL();
	virtual ~CSettingListView();
	void HandleLBSelect();	
	TInt SelectIAP();
	void Update();
	TBuf<128> iIAPName;
	TBuf<255> iAutoStartName;
	TBool iChanged;
	void ChangeItemSubtitle(TInt aIndex,TDes& aText);
	TBuf<128> NameByIAP(TInt aIap);
	void Init();
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	// [[[ begin generated region: do not modify [Generated Methods]
	CSettingList* CreateContainerL();
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
	TBool Handle_MenuItem2SelectedL( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CSettingList* iSettingList;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // SETTINGLISTVIEW_H
