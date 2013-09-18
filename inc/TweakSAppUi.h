/*
========================================================================
 Name        : TweakSAppUi.h
 Author      : Kolay
 Copyright   : TweakS - it is a tweaker for Symbian OS
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef TWEAKSAPPUI_H
#define TWEAKSAPPUI_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknviewappui.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CPluginsListView;
class CListOfSettingsView;
class CPluginsManagerView;
class CSettingListView;
class CAddingPluginView;
// ]]] end generated region [Generated Forward Declarations]


#include <ZipFileMember.h>
#include <ZipFile.h>
/**
 * @class	CTweakSAppUi TweakSAppUi.h
 * @brief The AppUi class handles application-wide aspects of the user interface, including
 *        view management and the default menu, control pane, and status pane.
 */
class CTweakSAppUi : public CAknViewAppUi
	{
public: 
	// constructor and destructor
	CTweakSAppUi();
	virtual ~CTweakSAppUi();
	void ConstructL();
	TBool GlobalMsgQuery(TPtrC aText,TPtrC aHeader);
	//void DynInitMenuPaneL(TInt aMenuId, CEikMenuPane* aMenuPane);
	CArrayFix<TCoeHelpContext>* Help() const;
	void ReadSettings();
	void WriteSettings();
	RArray<TInt> iSettings;
	TBool iNeedRestart;
	void FileOpened(TDes& aFileName);
	TBool ProcessCommandParametersL(CApaCommandLine &aCommandLine);
	void ExtractZip(const TDesC& aCompressedFile);
	HBufC* iCBText;
	HBufC8* iPage;
	static TInt Downloaded(TAny* aObj);
	void Down();
	void CallBackDialog();
	void ExtractFileFromZip(RFs& aFs, const TDesC& aZipFileName, CZipFile& aZipFile, CZipFileMember& aMember);
	void WriteToFile(RFs& aFs, const TDesC& aZipFileName, TBool aCreateNewFile, const TDesC8& aData, CZipFileMember& aMember);
private:
	CArrayFix<TCoeHelpContext>* HelpContextL() const;
public:
	// from CCoeAppUi
	TKeyResponse HandleKeyEventL(
				const TKeyEvent& aKeyEvent,
				TEventCode aType );

	// from CEikAppUi
	void HandleCommandL( TInt aCommand );
	void HandleResourceChangeL( TInt aType );

	// from CAknAppUi
	void HandleViewDeactivation( 
			const TVwsViewId& aViewIdToBeDeactivated, 
			const TVwsViewId& aNewlyActivatedViewId );

private:
	void InitializeContainersL();
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CPluginsListView* iPluginsListView;
	CListOfSettingsView* iListOfSettingsView;
	CPluginsManagerView* iPluginsManagerView;
	CSettingListView* iSettingListView;
	CAddingPluginView* iAddingPluginView;
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [User Handlers]
protected: 
	// ]]] end [User Handlers]
	
	};

#endif // TWEAKSAPPUI_H			
