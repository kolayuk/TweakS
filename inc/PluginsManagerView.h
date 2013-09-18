/*
========================================================================
 Name        : PluginsManagerView.h
 Author      : Usanov-Kornilov Nikolay (aka Kolay)
 Copyright   : 
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef PLUGINSMANAGERVIEW_H
#define PLUGINSMANAGERVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CPluginsManager;
// ]]] end generated region [Generated Forward Declarations]
#include <ClientEngine.h>
#include <aknwaitdialog.h>
struct TPluginInfo
	{
	TBuf<255> iName;
	TBuf<255> iDescription;
	TUint iUid;
	TBuf<255> iType;
	TBuf<255> iCREPath;
	TBuf<255> iPLGPath;
	TInt iSize;
	TInt iTypeInt;
	TBuf<255> iPlgName;
	TBuf<255> iCreName;
	TBuf<255> iCreUrl;
	TBuf<255> iPlgUrl;
	RArray<TUint> iUids;
	};
const TInt EPluginActive=1;
const TInt EPluginDisabled=2;
const TInt EPluginNotInstalled=3;
const TInt EPluginUpdateAvailable=4;
/**
 * Avkon view class for PluginsManagerView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CPluginsManagerView PluginsManagerView.h
 */						
			
class CPluginsManagerView : public CAknView, public MProgressDialogCallback
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CPluginsManagerView();
	static CPluginsManagerView* NewL();
	static CPluginsManagerView* NewLC();        
	void ConstructL();
	virtual ~CPluginsManagerView();
	void ReadInstalledPlugins();
	void ReadDisabledPlugins();
	void ReadUninstalledPlugins();
	static TInt Downloaded(TAny*);
	static TInt CREDownloaded(TAny*);
	static TInt PLGDownloaded(TAny*);
	HBufC8* iPage;
	CHTTPDownloader* iHTTP;
	CArrayFixSeg<TPluginInfo>* iPlugins;
	CAknWaitDialog* iWait;
	TBool isDialogActive;
	void DialogDismissedL( TInt aButtonId );
	void HandleLBSelect();
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
	// [[[ begin generated region: do not modify [Generated Methods]
	CPluginsManager* CreateContainerL();
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
	TBool Handle_MenuItem3SelectedL( TInt aCommand );
	TBool Handle_MenuItem4SelectedL( TInt aCommand );
	TBool Handle_MenuItem5SelectedL( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CPluginsManager* iPluginsManager;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // PLUGINSMANAGERVIEW_H
