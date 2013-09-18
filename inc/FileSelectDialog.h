/*
 ============================================================================
 Name		: FileSelectDialog.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CFileSelectDialog declaration
 ============================================================================
 */

#ifndef FILESELECTDIALOG_H
#define FILESELECTDIALOG_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <BADESCA.H>
#include <f32file.h>
#include <gulicon.h>
#include <aknlistquerydialog.h>
// CLASS DECLARATION

enum TTypeOfSelect
	{
	EFolder=1,
	EFile
	};

_LIT(KIconsFileName,"C:\\resource\\apps\\FileManIcons.mif");
_LIT(KDiskIconFileName,"Z:\\resource\\apps\\avkon2.mif");

class CFileSelectDialog : public CAknListQueryDialog
	{
public:
	CFileSelectDialog(TDes& aDefault);
	~CFileSelectDialog();
	void ConstructL(TDes& aTitle,TTypeOfSelect aType, TDes& aStartFileName,TDes& aMask);
	static TInt RunDlgLD(TDes& aTitle,TTypeOfSelect aType,TDes& aRoot,TDes& aMask,TDes& aDefault);
	TBool OkToExitL(TInt aButton);
	TInt iSelectedItem;
	void PostLayoutDynInitL();
	void SetDefault(TDes& aFile);
	void HandleListBoxEventL(CEikListBox* aLB,enum TListBoxEvent aEventType);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aEvent, enum TEventCode aType);
private:
	TBuf<255> iMask;
	TBuf<255> iStartPath;
	TTypeOfSelect iType;
	TBuf<255> iTitle;
	TBuf<255> iCurrentPath;
	RFs iFs;
	TInt EViewId;
	TDes& iResult;
	CDesCArrayFlat* iArray;
	TBuf<255> iOldTitle;
	void SetTitle();
	void LoadDriveList();
	void Update();
	void ScanDir();
	TInt Show();
	CGulIcon* iFileIcon;
	CGulIcon* iFolderIcon;
	CGulIcon* iDiskIcon;
	
	};

#endif // FILESELECTDIALOG_H
