/*
 ============================================================================
 Name		: CallBackDialog.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CCallBackDialog implementation
 ============================================================================
 */

#include "CallBackDialog.h"
#include <eikedwin.h>
#include "PluginsList.hrh"
#include <eikenv.h>
#include <aknutils.h>
#include <TweakSAppUi.h>

CCallBackDialog::CCallBackDialog()
	{
	// No implementation required
	}

CCallBackDialog::~CCallBackDialog()
	{
	}

CCallBackDialog* CCallBackDialog::NewLC(TInt aResource,HBufC* aText)
	{
	CCallBackDialog* self = new (ELeave) CCallBackDialog();
	CleanupStack::PushL(self);
	self->ConstructL(aResource,aText);
	return self;
	}

CCallBackDialog* CCallBackDialog::NewL(TInt aResource,HBufC* aText)
	{
	CCallBackDialog* self = CCallBackDialog::NewLC(aResource,aText);
	CleanupStack::Pop(); // self;
	return self;
	}

void CCallBackDialog::ConstructL(TInt aResource,HBufC* aText)
	{
	iText=aText;
	}
void CCallBackDialog::PostLayoutDynInitL()
	{
	TRect scr; TRect cba;
	AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EScreen,scr);
	AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EControlPane,cba);
	//SetExtentToWholeScreen();
	scr.Shrink(0,cba.Height());
	Control(EEditor)->SetRect(scr);
	TInt h=Control(ELabel)->Size().iHeight;
	TRect edrect=Control(EEditor)->Rect();
	edrect.Move(0,h);
	edrect.Shrink(0,h);
	//edrect.Shrink(0,cba.Height());
	Control(EEditor)->SetRect(edrect);
	((CEikLabel*)Control(ELabel))->SetBrushStyle(CGraphicsContext::ESolidBrush);
	}
TBool CCallBackDialog::OkToExitL(TInt aCommand)
	{
	if (aCommand==EAknSoftkeyOk)
		{
		CTweakSAppUi* AppUi= static_cast<CTweakSAppUi*>(CEikonEnv::Static()->AppUi());
		TPtr ptr=AppUi->iCBText->Des();
		CEikEdwin* Ed=static_cast<CEikEdwin*>(Control(EEditor));
		Ed->GetText(ptr);
		//((CTap2ScreenAppUi*)CEikonEnv::Static()->AppUi())->iCBText->Des().Copy();
		}
	return ETrue;
	}
