/*
========================================================================
 Name        : PluginsListView.h
 Author      : Kolay
 Copyright   : TweakS - it is a tweaker for Symbian OS
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef PLUGINSLISTVIEW_H
#define PLUGINSLISTVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CPluginsList;
// ]]] end generated region [Generated Forward Declarations]
#include <ClientEngine.h>
#include <aknwaitdialog.h>
/**
 * Avkon view class for PluginsListView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CPluginsListView PluginsListView.h
 */						
struct TPluginDescription
	{
	TBuf<255> iName;
	TBuf<255> iDescription;
	TUint iUid;
	TBuf<255> iType;
	};
class CPluginsListView : public CAknView, public MProgressDialogCallback
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CPluginsListView();
	static CPluginsListView* NewL();
	static CPluginsListView* NewLC();        
	void ConstructL();
	virtual ~CPluginsListView();
	TBool iFirstActivation;			
	// from base class CAknView
	TUid Id() const;
	TInt iTop;
	void OpenBrowser(const TDesC& aUrl);
	void HandleCommandL( TInt aCommand );
	CHTTPDownloader* iHTTP;
	HBufC8* iVersion;
	HBufC8* iVersionInfo;
	CAknWaitDialog* iWait;
	TBool isDialogActive;
	void Download();
	static TInt CheckVersion(TAny*);
	static TInt CheckVersionAuto(TAny*);
	static TDateTime ParseDateTime(TDes& aDate,TDes& aTime);
	static TInt GetVersionInfo(TAny*);
	static TInt UpdateDownloaded(TAny*);
	void DialogDismissedL( TInt aButtonId );
	// [[[ begin generated region: do not modify [Generated Methods]
	CPluginsList* CreateContainerL();
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	CArrayFixSeg<TPluginDescription>* iPlugins;
	void ReadPlugins();
	void HandleLBSelect();
	TInt iPos;
	void StartExport(TInt aFullCR);
	RArray<TUid> iPluginsToExp;
	void ReadDataForExport(CArrayFixFlat<TInt>*);
	static TInt DoExportFull(TAny* aObj);
	static TInt DoExportPlugins(TAny* aObj);
	TBuf<255> iFolderToExp;
	CIdle* iIdle;
	CAknWaitDialog* iExportWait;
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
	TBool Handle_MenuItemSelectedL( TInt aCommand );
	TBool HandleMenuItemSelectedL( TInt aCommand );
	TBool Handle_MenuItem1SelectedL( TInt aCommand );
	TBool Handle_MenuItem2SelectedL( TInt aCommand );
	TBool Handle_MenuItem3SelectedL( TInt aCommand );
	TBool Handle_MenuItem4SelectedL( TInt aCommand );
	TBool Handle_MenuItem5SelectedL( TInt aCommand );
	TBool Handle_MenuItem6SelectedL( TInt aCommand );
	TBool ConnectToDev( TInt aCommand );
	TBool SendSMS( TInt aCommand );
	TBool UnlockAll( TInt aCommand );
	TBool Export( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CPluginsList* iPluginsList;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // PLUGINSLISTVIEW_H
