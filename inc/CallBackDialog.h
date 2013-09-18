/*
 ============================================================================
 Name		: CallBackDialog.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CCallBackDialog declaration
 ============================================================================
 */

#ifndef CALLBACKDIALOG_H
#define CALLBACKDIALOG_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <akndialog.h>
#include <eiklabel.h>
#include <eikedwin.h>

// CLASS DECLARATION
class CCallBackDialog : public CAknDialog
	{
public:
	~CCallBackDialog();
	static CCallBackDialog* NewL(TInt aResource,HBufC* aText);
	static CCallBackDialog* NewLC(TInt aResource,HBufC* aText);
	void PostLayoutDynInitL();
	TBool OkToExitL(TInt aCommand);
private:
	CCallBackDialog();
	void ConstructL(TInt aResource,HBufC* aText);
	CEikLabel* iLabel;
	CEikEdwin* iEdwin;
	HBufC* iText;
	};

#endif // CALLBACKDIALOG_H
