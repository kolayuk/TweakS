/*
========================================================================
 Name        : TweakSDocument.cpp
 Author      : Kolay
 Copyright   : TweakS - it is a tweaker for Symbian OS
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "TweakSDocument.h"
#include "TweakSAppUi.h"
// ]]] end generated region [Generated User Includes]

/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CTweakSDocument::CTweakSDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CTweakSDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CTweakSDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CTweakSDocument
 */
CTweakSDocument* CTweakSDocument::NewL( CEikApplication& aApp )
	{
	CTweakSDocument* self = new ( ELeave ) CTweakSDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CTweakSDocument::CreateAppUiL()
	{
	return new ( ELeave ) CTweakSAppUi;
	}

				
