/*
 ============================================================================
 Name		: FileSelectDialog.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CFileSelectDialog implementation
 ============================================================================
 */

#include "FileSelectDialog.h"
#include <aknlists.h> //CAknSinglePopupMenuStyleListBox 
#include <aknpopup.h> //CAknPopupList

#include <akntitle.h> // title
#include <eikspane.h>
#include <eikaufty.h>

#include <aknappui.h>
#include <aknviewappui.h>
#include <aknview.h>
#include <eikenv.h>

#include <f32file.h>
#include <bautils.h>
#include <aknselectionlist.h>

#include <TweakS.rsg>
#include <avkon.mbg>
#include <AknIconUtils.h>
#include <logger.h>
#include <eiklbv.h>
#include <aknlists.h>
#include <eikclbd.h> 
#include <aknlistquerydialog.h>
#include <akniconarray.h>

CFileSelectDialog::CFileSelectDialog(TDes& aDefault): CAknListQueryDialog(&iSelectedItem),iResult(aDefault)
	{
	// No implementation required
	}

CFileSelectDialog::~CFileSelectDialog()
	{
	delete iArray;
	}


void CFileSelectDialog::HandleListBoxEventL(CEikListBox* aLB,enum TListBoxEvent aEventType)
	 {
	        switch(aEventType)
	    		{
	    		case EEventEnterKeyPressed:
	    			{
	    			iEnterKeyPressed = ETrue;
	    			 ListBox()->SetCurrentItemIndex(-1);
	    			break;
	    			}
	    		default:
	    			{
	    			break;
	    			}
	    		}
	    }
void CFileSelectDialog::PostLayoutDynInitL()
	{
	CAknListQueryDialog::PostLayoutDynInitL();
	CArrayPtr<CGulIcon>* icons;
	icons=new (ELeave) CAknIconArray(1);
    CGulIcon* icon = AknsUtils::CreateGulIconL(AknsUtils::SkinInstance(),KAknsIIDQgnPropEmpty, AknIconUtils::AvkonIconFileName(),EMbmAvkonQgn_prop_empty,EMbmAvkonQgn_prop_empty_mask);	
	icon->SetBitmapsOwnedExternally(EFalse);
	icons->AppendL(icon);
	SetIconArrayL(icons);
	Update();
	Show();
	}
void CFileSelectDialog::ConstructL(TDes& aTitle,TTypeOfSelect aType, TDes& aStartFilePath,TDes& aMask)
	{
	
	EViewId=999;
	iTitle.Copy(aTitle);
	iType=aType;
	iStartPath.Copy(aStartFilePath);
	iMask.Copy(aMask);
	
	iFs.Connect();
	iArray = new (ELeave) CDesCArrayFlat(3);
	
	iCurrentPath.Copy(iStartPath);
	
	/*
    CFbsBitmap* bitmapFile = NULL;
	CFbsBitmap* maskFile = NULL;
	AknIconUtils::CreateIconL(bitmapFile,maskFile, KIconsFileName,0,1);
	iFileIcon=CGulIcon::NewL(bitmapFile,maskFile);
	CFbsBitmap* bitmapFolder = NULL;
	CFbsBitmap* maskFolder = NULL;
	AknIconUtils::CreateIconL(bitmapFolder,maskFolder, KIconsFileName,0,1);
	iFolderIcon=CGulIcon::NewL(bitmapFolder,maskFolder);
	CFbsBitmap* bitmapDisk = NULL;
	CFbsBitmap* maskDisk = NULL;
	AknIconUtils::CreateIconL (bitmapFolder,maskFolder, KDiskIconFileName,EMbmAvkonQgn_note_empty);
	iFolderIcon=CGulIcon::NewL(bitmapFolder,maskFolder);
	*/
	}
TInt CFileSelectDialog::RunDlgLD(TDes& aTitle,TTypeOfSelect aType,TDes& aRoot,TDes& aMask,TDes& aDefault)
	{
	CFileSelectDialog* dlg=new (ELeave) CFileSelectDialog(aDefault);
	dlg->ConstructL(aTitle,aType,aRoot,aMask);
	dlg->PrepareLC(R_FILE_DIALOG);
	dlg->SetDefault(aDefault);
	TInt ok=dlg->RunLD();
	return ok;
	}
void CFileSelectDialog::SetDefault(TDes& aFile)
	{
	iResult=aFile;
	}
void CFileSelectDialog::Update()
	{
	iArray->Reset();
	_LOG(_L("Update"));
	_LOGDATA(_L("CurrDir at enter: %S"),&iCurrentPath);
	if( iCurrentPath.Compare(_L(""))==0)
		{
		_LOG(_L("( iCurrentPath.Compare(_L(""))==0)"));
		_LOG(_L("Will load drive list"));
		LoadDriveList();
		}
	else 
		{_LOG(_L("Will scan dir"));ScanDir();}
	}
void CFileSelectDialog::ScanDir()
	{
	_LOG(_L("0"));
	TInt i=0;
	CDir* results=NULL;
	TFindFile findFiles(iFs);
	findFiles.FindWildByDir(iMask,iCurrentPath,results);
	if (results==NULL){return;}
	_LOG(_L("2"));
	for (i=0;i<results->Count();i++)
		{
		_LOGDATA(_L("3 %d"),i);
		if (((TEntry)(*results)[i]).IsDir())
		{
		TBuf<255> buf;
		buf.Copy(_L("["));
		buf.Append(((TEntry)(*results)[i]).iName);
		buf.Append(_L("]"));
		iArray->AppendL(buf);}
		}
	if (iType!=EFolder)
	{
	for (i=0;i<results->Count();i++)
		{
		_LOGDATA(_L("4 %d"),i);
		if (!((TEntry)(*results)[i]).IsDir())
			{iArray->AppendL(((TEntry)(*results)[i]).iName);}
		}
	}
	_LOG(_L("Exit from ScanDir"));
}
TInt CFileSelectDialog::Show()
	{
	_LOG(_L("CFileSelectDialog::Show()"));
	TInt sel=0;
	CDesCArray* itemList = new (ELeave) CDesCArrayFlat(3);
	TBuf<255> t; CEikonEnv::Static()->ReadResource(t,R_FILE_SELECTER_FOLDER_SELECT);
	if (iCurrentPath.Compare(_L(""))!=0){if (iType==EFolder){iArray->InsertL(0,t);}iArray->InsertL(0,_L("..."));}
	_LOGDATA(_L("Length of array: %d"),iArray->Count());
	
	for (TInt i=0;i<iArray->Count();i++)
		{
		TBuf<255> ItemTxt;
		ItemTxt.Copy(_L("0\t"));
		ItemTxt.Append(iArray->MdcaPoint(i));
		ItemTxt.Append(_L("\t\t"));
		itemList->AppendL(ItemTxt);
		_LOGDATA(_L("Item: %S"),&iArray->MdcaPoint(i));
		}
	_LOG(_L("Will create dialog"));
	SetItemTextArray(itemList);
    ListBox()->HandleItemAdditionL();
    Layout();
    ListBox()->SetCurrentItemIndex(0);
    ListBox()->DrawNow();
    DrawDeferred();
	}
void CFileSelectDialog::LoadDriveList()
	{
	TInt i=0;
	BaflUtils::GetDiskListL(iFs,*iArray);
	for (i=0; i<iArray->Count();i++)
		{
		TBuf<255> a(iArray->MdcaPoint(i));
		a.Append(_L(":"));
		iArray->Delete(i);
		iArray->InsertL(i,a); 
		}
	}
TKeyResponse CFileSelectDialog::OfferKeyEventL(const TKeyEvent& aEvent, enum TEventCode aType)
	{
	if (aEvent.iCode==EKeyEnter||aEvent.iCode==EKeyOK)
		{
		TryExitL(EAknSoftkeyOk);
		return EKeyWasConsumed;
		}
	return CAknListQueryDialog::OfferKeyEventL(aEvent,aType);
	}
void CFileSelectDialog::SetTitle()
	{
	
		TUid titlePaneUid;
		titlePaneUid.iUid = EEikStatusPaneUidTitle;
		TVwsViewId ViewID;CEikonEnv::Static()->AppUi()->GetActiveViewId(ViewID);
		CEikStatusPane* statusPane =((CAknAppUi*)CEikonEnv::Static()->AppUi())->StatusPane();		CEikStatusPaneBase::TPaneCapabilities subPane = statusPane->PaneCapabilities(titlePaneUid);
		if ( subPane.IsPresent() && subPane.IsAppOwned() )
			{
			CAknTitlePane* titlePane =(CAknTitlePane*) statusPane->ControlL(titlePaneUid);
			iOldTitle = *titlePane->Text();
			titlePane->SetTextL(iTitle);
			}
		
	}
TBool CFileSelectDialog::OkToExitL(TInt aButton)
	{
	TInt selected=ListBox()->CurrentItemIndex();
	_LOGDATA(_L("Selected: %d"),selected);
	if (aButton==EAknSoftkeyCancel){return ETrue;}
	if (iCurrentPath.Compare(_L(""))==0)
		{
		_LOG(_L("(iCurrentPath.Compare(_L(""))==0)"));
		_LOG(iCurrentPath);
		iCurrentPath.Append(iArray->MdcaPoint(selected));
		iCurrentPath.Append(_L("\\"));
		if (BaflUtils::PathExists(iFs,iCurrentPath)){Update();Show();return EFalse;}
		//Update();
		}
	else if ((selected>1&&iType==EFolder)||(selected>0&&iType==EFile))
		{
		_LOG(_L("((selected>1)&&(iCurrentPath.Compare(_L(""))!=0))"));
		_LOG(iCurrentPath);
		TBuf<255> temp(iArray->MdcaPoint(selected));
		TChar c1='[',c2=']';
		if (temp[0]==c1&&temp[temp.Length()-1]==c2) {temp.Copy(temp.Left(temp.Length()-1));temp.Copy(temp.Right(temp.Length()-1));}
		_LOGDATA(_L("Temp: %S"),&temp);
		iCurrentPath.Append(temp);
		iCurrentPath.Append(_L("\\"));
		_LOGDATA(_L("CurrPath after append: %S"),&iCurrentPath);
		CEikonEnv::Static()->InfoMsg(iCurrentPath);
		User::After(500000);
		if (BaflUtils::PathExists(iFs,iCurrentPath)){Update();Show();return EFalse;}
		else if (BaflUtils::FileExists(iFs,iCurrentPath.Left(iCurrentPath.Length()-1)))
			{
			iResult.Copy(iCurrentPath.Left(iCurrentPath.Length()-1));
			return ETrue;
			}
		}
	else if (selected==0)
		{
		_LOG(_L("(selected==0&&(iCurrentPath.Compare(_L(""))!=0))"));
		_LOG(iCurrentPath);
		TParse p;
		iFs.Parse(iCurrentPath, p);
		_LOG(_L("Will pop now"))
		TInt err=p.PopDir();
		if (err!=KErrNone||iCurrentPath.Compare(p.FullName())==0){iCurrentPath.Copy(_L(""));}
		else {iCurrentPath.Copy(p.FullName());}
		//if (iCurrentPath.Compare(_L(""))!=0)
		Update();Show();return EFalse;
		}
	else if (selected==1&&iType==EFolder&&(iCurrentPath.Compare(_L(""))!=0))
		{
		_LOG(_L("Will update result"));
		iResult.Copy(iCurrentPath);
		return ETrue;
		}
	Update();Show();return EFalse;
	}
/*
CGulIcon* CFileSelectDialog::LoadIconL()
    {
    _LIT(KIconsFile, "C:\\resource\\apps\\FileManIcons.mif");
    // Create icon from SVG
    AknIconUtils::CreateIconL(aBitmap, aMask, KIconsFile, aIndex, aIndex + 1);
    // Give size
    AknIconUtils::SetSize(aBitmap, aSize);
    AknIconUtils::SetSize(aMask, aSize);
    }
    */
