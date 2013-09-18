/*
========================================================================
 Name        : ListOfSettings.h
 Author      : Kolay
 Copyright   : Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef LISTOFSETTINGS_H
#define LISTOFSETTINGS_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <coecntrl.h>		
// ]]] end generated region [Generated Includes]

#include <SettingData.h>
// [[[ begin [Event Handler Includes]
#include <eiklbo.h>
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;		
class CAknDoubleStyleListBox;
class CEikTextListBox;
// ]]] end generated region [Generated Forward Declarations]
class CAknSettingStyleListBox;
/**
 * Container class for ListOfSettings
 * 
 * @class	CListOfSettings ListOfSettings.h
 */
class CListOfSettings : public CCoeControl
	,MEikListBoxObserver	{
public:
	// constructors and destructor
	CListOfSettings();
	static CListOfSettings* NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	static CListOfSettings* NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	void ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	virtual ~CListOfSettings();
	void Update(TInt aIndex=-1);
	void CreateLBBufferForSetting(TSettingData aData,TDes& LBBuffer);
	void UpDownEvent();
	TInt iTop, iBottom;
public:
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl( TInt aIndex ) const;
	TKeyResponse OfferKeyEventL( 
			const TKeyEvent& aKeyEvent, 
			TEventCode aType );
	void HandleResourceChange( TInt aType );
	
protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	// from base class CCoeControl
	void Draw( const TRect& aRect ) const;

private:
	void InitializeControlsL();
	void LayoutControls();
	CCoeControl* iFocusControl;
	MEikCommandObserver* iCommandObserver;
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	static void AddListBoxItemL( 
			CEikTextListBox* aListBox,
			const TDesC& aString );
	static RArray< TInt >* GetSelectedListBoxItemsLC( CEikTextListBox* aListBox );
	static void DeleteSelectedListBoxItemsL( CEikTextListBox* aListBox );
	CAknSettingStyleListBox* ListBox();
	static void CreateListBoxItemL( TDes& aBuffer, 
			const TDesC& aMainText,
			const TDesC& aSecondaryText );
	void AddListBoxResourceArrayItemL( TInt aResourceId );
	void SetupListBoxIconsL();
	TBool HandleMarkableListCommandL( TInt aCommand );
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Type Declarations]
public: 
	// ]]] end generated region [Generated Type Declarations]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CAknSettingStyleListBox* iListBox;
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [Overridden Methods]
protected: 
	void HandleListBoxEventL( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );
	// ]]] end [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
protected: 
	void HandleListBoxItemClickedL( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );
	void HandleListBoxEnterKeyPressedL( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );
	// ]]] end [User Handlers]
	
public: 
	enum TControls
		{
		// [[[ begin generated region: do not modify [Generated Contents]
		EListBox,
		
		// ]]] end generated region [Generated Contents]
		
		// add any user-defined entries here...
		
		ELastControl
		};
	enum TListBoxImages
		{
		// [[[ begin generated region: do not modify [Generated Enums]
		EListBoxFirstUserImageIndex
		
		// ]]] end generated region [Generated Enums]
		
		};
	
	// [[[ begin [MEikListBoxObserver support]
private: 
	typedef void ( CListOfSettings::*ListBoxEventHandler )( 
			CEikListBox* aListBox, 
			TListBoxEvent anEvent );
	
	void AddListBoxEventHandlerL( 
			CEikListBox* aListBox, 
			TListBoxEvent anEvent, 
			ListBoxEventHandler aHandler );
	
	struct TListBoxEventDispatch 
		{ 
		CEikListBox* src; 
		TListBoxEvent event; 
		ListBoxEventHandler handler;
		};
		
	RArray< TListBoxEventDispatch > iListBoxEventDispatch;
	// ]]] end [MEikListBoxObserver support]
	
	};
				
#endif // LISTOFSETTINGS_H
