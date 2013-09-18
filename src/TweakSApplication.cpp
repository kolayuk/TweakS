/*
========================================================================
 Name        : TweakSApplication.cpp
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
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated Includes]
#include "TweakSApplication.h"
#include "TweakSDocument.h"
#ifdef EKA2
#include <eikstart.h>
#endif
// ]]] end generated region [Generated Includes]

/**
 * @brief Returns the application's UID (override from CApaApplication::AppDllUid())
 * @return UID for this application (KUidTweakSApplication)
 */
TUid CTweakSApplication::AppDllUid() const
	{
	return KUidTweakSApplication;
	}

/**
 * @brief Creates the application's document (override from CApaApplication::CreateDocumentL())
 * @return Pointer to the created document object (CTweakSDocument)
 */
CApaDocument* CTweakSApplication::CreateDocumentL()
	{
	return CTweakSDocument::NewL( *this );
	}

#ifdef EKA2

/**
 *	@brief Called by the application framework to construct the application object
 *  @return The application (CTweakSApplication)
 */	
LOCAL_C CApaApplication* NewApplication()
	{
	return new CTweakSApplication;
	}

/**
* @brief This standard export is the entry point for all Series 60 applications
* @return error code
 */	
GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}
	
#else 	// Series 60 2.x main DLL program code

/**
* @brief This standard export constructs the application object.
* @return The application (CTweakSApplication)
*/
EXPORT_C CApaApplication* NewApplication()
	{
	return new CTweakSApplication;
	}

/**
* @brief This standard export is the entry point for all Series 60 applications
* @return error code
*/
GLDEF_C TInt E32Dll(TDllReason /*reason*/)
	{
	return KErrNone;
	}

#endif // EKA2
