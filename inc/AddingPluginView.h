/*
========================================================================
 Name        : AddingPluginView.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef ADDINGPLUGINVIEW_H
#define ADDINGPLUGINVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CAddingPlugin;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for AddingPluginView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CAddingPluginView AddingPluginView.h
 */						
		

#include "SettingData.h"
#include <centralrepository.h>

struct TApplicationInfo
{
	TFileName iCaption;
	TUid iUid;
	static TInt Compare(const TApplicationInfo& aInfo1, const TApplicationInfo& aInfo2)
	{
		return aInfo1.iCaption.CompareC(aInfo2.iCaption);
	}
};

class CAddingPluginView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CAddingPluginView();
	static CAddingPluginView* NewL();
	static CAddingPluginView* NewLC();        
	void ConstructL();
	virtual ~CAddingPluginView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	TSettingData iData;
	void Active(TSettingData aData);
	CRepository* iCR;
	void Update();
	TInt PopupMenu(TDes& aTxt,CDesCArray* itemList);
	void HandleLBSelect();
	TUint32 ApplicationDialog(TDes& aTitle);
	// [[[ begin generated region: do not modify [Generated Methods]
	CAddingPlugin* CreateContainerL();
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	
	// [[[ begin [Protected Section]
public:
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
	TBool Back( TInt aCommand );
	TBool Add( TInt aCommand );
	TBool Edit( TInt aCommand );
	TBool Remove( TInt aCommand );
	TBool Info( TInt aCommand );
	TBool Reset( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CAddingPlugin* iAddingPlugin;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // ADDINGPLUGINVIEW_H
