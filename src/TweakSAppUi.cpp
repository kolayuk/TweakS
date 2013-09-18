/*
========================================================================
 Name        : TweakSAppUi.cpp
 Author      : Kolay
 Copyright   : TweakS - it is a tweaker for Symbian OS
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "TweakSAppUi.h"
#include "TweakS.hrh"
#include "PluginsList.hrh"
#include "PluginsManager.hrh"
#include "SettingList.hrh"
#include "AddingPlugin.hrh"
#include "PluginsListView.h"
#include "ListOfSettingsView.h"
#include "PluginsManagerView.h"
#include "SettingListView.h"
#include "AddingPluginView.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

#include <aknglobalmsgquery.h>
#include <ListOfSettings.hrh>
#include <ListOfSettings.h>
#include <aknlists.h>
#include <hlplch.h>
#include <centralrepository.h>
#include <TweakSApplication.h>
#include <const.h>
#include <bautils.h>
#include <ZipFileMember.h>
#include <ZipFile.h>
#include <CallBackDialog.h>
#include <logger.h>
#include <rsendas.h>
#include <rsendasmessage.h>
#include <smut.h>
#include <sms.h>
#include <TweakS.RSG>
#include <senduiconsts.h>

/**
 * Construct the CTweakSAppUi instance
 */ 
CTweakSAppUi::CTweakSAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CTweakSAppUi::~CTweakSAppUi()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

// [[[ begin generated function: do not modify
void CTweakSAppUi::InitializeContainersL()
	{
	iPluginsListView = CPluginsListView::NewL();
	AddViewL( iPluginsListView );
	SetDefaultViewL( *iPluginsListView );
	iListOfSettingsView = CListOfSettingsView::NewL();
	AddViewL( iListOfSettingsView );
	iPluginsManagerView = CPluginsManagerView::NewL();
	AddViewL( iPluginsManagerView );
	iSettingListView = CSettingListView::NewL();
	AddViewL( iSettingListView );
	iAddingPluginView = CAddingPluginView::NewL();
	AddViewL( iAddingPluginView );
	}
// ]]] end generated function

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CTweakSAppUi::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	// ]]] end generated region [Generated Code]
	
	}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CTweakSAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknViewAppUi::HandleResourceChangeL( aType );
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CTweakSAppUi::HandleKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode aType )
	{
	// The inherited HandleKeyEventL is private and cannot be called
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	return EKeyWasNotConsumed;
	}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CTweakSAppUi::HandleViewDeactivation( 
		const TVwsViewId& aViewIdToBeDeactivated, 
		const TVwsViewId& aNewlyActivatedViewId )
	{
	CAknViewAppUi::HandleViewDeactivation( 
			aViewIdToBeDeactivated, 
			aNewlyActivatedViewId );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CTweakSAppUi::ConstructL()
	{
	_LOG(_L("Application Started"));
	
	TBool ex=BaflUtils::FileExists(CEikonEnv::Static()->FsSession(),KSettingsPath);
	if (ex)
		{
		BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),KSettingsPath,KCREPath);
		BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(),KSettingsPath);
		}
	TInt err=0;
	//ReadSettings();
	TRAP(err,ReadSettings());
	if (err!=KErrNone)
		{
		iNeedRestart=ETrue;
		iSettings.Reset();
		iSettings.Append(-1);
		iSettings.Append(0);
		}
	// [[[ begin generated region: do not modify [Generated Contents]
	
	BaseConstructL( EAknEnableSkin ); 
	InitializeContainersL();
	// ]]] end generated region [Generated Contents]

	}
CArrayFix <TCoeHelpContext>* CTweakSAppUi::HelpContextL() const
	{
	CArrayFixFlat <TCoeHelpContext>* array = new (ELeave) CArrayFixFlat <TCoeHelpContext>(1);
	CleanupStack::PushL(array);
	TUid uid={0x2002E906};
	array->AppendL(TCoeHelpContext(uid, _L("Main")));
	CleanupStack::Pop(array);
	return array;
	} 
CArrayFix <TCoeHelpContext>* CTweakSAppUi::Help() const
		{
		return HelpContextL();
		}

TBool CTweakSAppUi::GlobalMsgQuery(TPtrC aText,TPtrC aHeader)
	{
	
	    TInt queryAnswer = 1;
	    char* querystr = NULL;
	    int querystr_l = 0;
	    char* headerstr = NULL;
	    int headerstr_l = 0;
	    TRequestStatus msgQueryStatus = KRequestPending;
	    TRequestStatus timerStatus = KRequestPending;
	    int delayInSeconds = 0;
	    TInt timeout = 0;
	    
	    TTimeIntervalMicroSeconds32 timeoutValue = TTimeIntervalMicroSeconds32(timeout);

	    CAknGlobalMsgQuery *msgQueryDialog = NULL;
	    
	    TRAPD(err,
	        {
	            msgQueryDialog = CAknGlobalMsgQuery::NewL();
	        });
	    CleanupStack::PushL(msgQueryDialog);
	    TRAPD(err1,
	        {
	            msgQueryDialog->ShowMsgQueryL(msgQueryStatus,aText,R_AVKON_SOFTKEYS_OK_CANCEL,aHeader, KNullDesC);
	        });
	    if(err1 != KErrNone||err!=KErrNone){
	       CleanupStack::PopAndDestroy(msgQueryDialog);
	    } 
		User::WaitForRequest(msgQueryStatus);
	    
	    CleanupStack::PopAndDestroy(msgQueryDialog);
	    return msgQueryStatus.Int() == EAknSoftkeyOk ? 1 : 0;		
	}

void CTweakSAppUi::ReadSettings()
	{
	TInt iap;
	TInt update;
	
	CRepository* CR=CRepository::NewL(KUidTweakSApplication);
	
	User::LeaveIfError(CR->Get(KDefaultIAPSettingKey,iap));
	
	iSettings.Append(iap);
	User::LeaveIfError(CR->Get(KAutoUpdateSettingKey,update));
	iSettings.Append(update);
	delete CR;
	}
void CTweakSAppUi::WriteSettings()
	{
	CRepository* CR=CRepository::NewL(KUidTweakSApplication);
	User::LeaveIfError(CR->Set(KDefaultIAPSettingKey,iSettings[0]));
	User::LeaveIfError(CR->Set(KAutoUpdateSettingKey,iSettings[1]));
	delete CR;
	}

void CTweakSAppUi::FileOpened(TDes& aFileName)
	{
	
	CEikonEnv::Static()->InfoMsg(aFileName);
	ExtractZip(aFileName);
	TBuf<255> text;
	TBuf<255> header(_L("TweakS"));
	CEikonEnv::Static()->ReadResource(text,R_NEW_PLUGIN_INSTALLED);
	GlobalMsgQuery(text,header);
	User::Exit(0);
	}
TBool CTweakSAppUi::ProcessCommandParametersL(CApaCommandLine &aCommandLine)
	{
	
	TBuf<255> file;
	file.Copy(aCommandLine.DocumentName());
	_LOG(_L("ProcessCommandParametersL"));
	_LOGDATA(_L("File: %S"),&aCommandLine.DocumentName());
	_LOGDATA(_L("Exe name: %S"),&aCommandLine.ExecutableName());
	_LOGDATA(_L("opaque data: %S"),&aCommandLine.OpaqueData());
	if (file.Length()>3)
		{FileOpened(file);}
	return CEikAppUi::ProcessCommandParametersL( aCommandLine );
	}

void CTweakSAppUi::ExtractZip(const TDesC& aCompressedFile) {
  RFs fileSession=CEikonEnv::Static()->FsSession();
  // Creating a new instance of CZipFile.
  // The first parameter of the two-phase constructor is a session of File Server.
  // The second parameter is the file name of the ZIP file.
  CZipFile* zipFile = CZipFile::NewL(fileSession, aCompressedFile);
  if (zipFile != NULL) {
    CleanupStack::PushL(zipFile);
 
    // Getting the list of all files inside the ZIP.
    // The ownership of CZipFileMemberIterator will be passed to the caller,
    // thus we have to delete it after we are done reading the ZIP.
    CZipFileMemberIterator* members = zipFile->GetMembersL();
    if (members != NULL) {
      CleanupStack::PushL(members);
 
      // Iterating through all the files.
      // We have to call CZipFileMemberIterator::NextL() over and over
      // until it returns 0.
      CZipFileMember* member;
      while ((member = members->NextL()) != 0) {
        // Print the name of the extracted file, the compressed file size
        // and the uncompressed file size.  
        const TDesC* fileName = member->Name();
        TInt compressedSize = member->CompressedSize();
        TInt uncompressedSize = member->UncompressedSize();
        if (fileName != NULL) {
          ExtractFileFromZip(fileSession, aCompressedFile, *zipFile, *member);
        }
        delete member;
      }
      CleanupStack::PopAndDestroy(); // members
    }
    CleanupStack::PopAndDestroy(); // zipFile
  }
}

void CTweakSAppUi::ExtractFileFromZip(RFs& aFs, const TDesC& aZipFileName, CZipFile& aZipFile, CZipFileMember& aMember) {
  // Use input stream to extract the file.
  // The input stream of a file inside ZIP file is RZipFileMemberReaderStream.
  // The method used to get the input stream is CZipFile::GetInputStreamL().
  RZipFileMemberReaderStream* stream;
  aZipFile.GetInputStreamL(&aMember, stream);
  CleanupStack::PushL(stream);
 
  // Read the file using input stream.
  // Before reading the file, the code allocates a buffer to store with
  // the size of member->UncompressesedSize().
  //
  // If the file is quite huge, do not use "one-shot" Read().
  // Instead, read using a small block of buffer and do it inside an
  // active object.
  const TInt KBufferSize = 1024;
  TInt uncompressedSize = aMember.UncompressedSize();
  RBuf8 buffer;
  buffer.CreateL(KBufferSize);
  CleanupClosePushL(buffer);
  TInt readBytes = 0;
  TBool createNewFile;
  while (readBytes < uncompressedSize) {
    TInt toRead = (uncompressedSize - readBytes) > buffer.MaxSize() ? buffer.MaxSize() : (uncompressedSize - readBytes);
    TInt err = stream->Read(buffer, toRead);
    User::LeaveIfError(err);
    if (readBytes == 0) {
      createNewFile = ETrue;
    }
    else {
      createNewFile = EFalse; 
    }
    WriteToFile(aFs, aZipFileName, createNewFile, buffer, aMember);
    readBytes += buffer.Length();
  }
 
  // Finally, do not forget to release all the allocated resources.
  CleanupStack::PopAndDestroy(2, stream); // stream, expandedMember
}
 
void CTweakSAppUi::WriteToFile(RFs& aFs, const TDesC& aZipFileName, TBool aCreateNewFile, const TDesC8& aData, CZipFileMember& aMember)
	{
	TBuf<255> fileName;
  fileName.Copy(KPluginsDir);
  fileName.Append(*aMember.Name());
  TInt err = 0;
  RFile expandedMember;
  CleanupClosePushL(expandedMember);
  if (!BaflUtils::FileExists(aFs, fileName)) {
    err = expandedMember.Replace(aFs, fileName, EFileShareAny|EFileWrite);
  }
  else if (aCreateNewFile) {
    err = expandedMember.Replace(aFs, fileName, EFileShareAny|EFileWrite);
  }
  else {
    TInt pos = 0;
    err = expandedMember.Open(aFs, fileName, EFileShareAny|EFileWrite);
    err = expandedMember.Seek(ESeekEnd, pos);
  } 
 
  if (err == KErrNone) {
    expandedMember.Write(aData);
  }
  expandedMember.Close();
  CleanupStack::PopAndDestroy(&expandedMember);
}

void CTweakSAppUi::CallBackDialog()
	{
	iCBText=HBufC::NewL(4096*2);
	HBufC* url=HBufC::NewL(4768);
	url->Des().Copy(KCallBackUrl);
	CCallBackDialog* dlg= CCallBackDialog::NewL(R_CALLBACK_DLG,iCBText);
	dlg->PrepareLC(R_CALLBACK_DLG);
	TInt result=dlg->RunLD();
	url->Des().Append(*iCBText);
	delete iCBText;
	if (result)
		{
		CHTTPDownloader* downloader=CHTTPDownloader::NewL();
		iPage=HBufC8::NewL(1024);
		TPtr ptr=url->Des();
		downloader->GetPage(ptr,iPage,TCallBack(Downloaded,this));
		}
	delete url;
	}
TInt CTweakSAppUi::Downloaded(TAny* aObj)
	{
	((CTweakSAppUi*)aObj)->Down();
	}
void CTweakSAppUi::Down()
	{
	delete iPage;
	}
