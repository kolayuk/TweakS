/*
 ============================================================================
 Name		: SliderDialog.cpp
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CSliderDialog implementation
 ============================================================================
 */

#include <logger.h>

#include "SliderDialog.h"
#include <aknsutils.h>
#include <aknutils.h>
#include <akniconutils.h>
#include <TweakS_ui.mbg>
#include <BARSREAD.H>
#include <TweakS.rsg>
#include "ListOfSettings.hrh"
#include <e32math.h>
#include <aknsdrawutils.h>
#include <aknsbasicbackgroundcontrolcontext.h>
#include <ImageConversion.h>
CSliderDialog::CSliderDialog(TDes& aLabel,TInt& aVal,TInt aMinVal,TInt aMaxVal): CAknDialog(),iVal(aVal), iMaxVal(aMaxVal),iMinVal(aMinVal), iLabel(aLabel)
	{
	// No implementation required
	}

TInt CSliderDialog::RunDlgLD(TDes& aLabel,TInt& aVal,TInt aMinVal,TInt aMaxVal)
    {
	CSliderDialog* dlg = new (ELeave) CSliderDialog(aLabel,aVal,aMinVal,aMaxVal);
	return dlg->ExecuteLD(R_SLIDER_DIALOG);
    }
 
void CSliderDialog::PostLayoutDynInitL()
	{
	
	CSliderControl* control = (CSliderControl*)Control(KMyCustomCtlId);
    control->SetVal(iVal);
    control->SetMax(iMaxVal);
    control->SetMin(iMinVal);
    control->SetLabel(iLabel);
	TInt scrX=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
	TInt scrY=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;    
	TRect r=TRect(TPoint(0,scrY/3),TSize(scrX,scrY/3));
	control->ShrinkRects(r,EDirectionVertical);
	control->MakeVisible(ETrue);
	}

SEikControlInfo CSliderDialog::CreateCustomControlL(TInt aControlType)
    {
    SEikControlInfo controlInfo;
    controlInfo.iControl = NULL ;
    controlInfo.iTrailerTextId = 0 ;
    controlInfo.iFlags = 0 ;
 
    switch (aControlType)
        {
        // CMyControl custom control type (defined in multiviews.hrh)
        case KMyCustomCtl:
            {
            controlInfo.iControl = new (ELeave)CSliderControl();
            break;
            }
        default:
            break;
        }
    return controlInfo;
    }
TBool CSliderDialog::OkToExitL(TInt aButtonID)
	{
	CSliderControl* control = (CSliderControl*)Control(KMyCustomCtlId);
	if (aButtonID=EAknSoftkeyOk)
		{
		iVal=control->GetVal();
		}
	//TRAPD(err,CEikonEnv::Static()->AppUi()->RemoveFromStack(control));
	return ETrue; //breakpoint - ok
	}



CSliderControl::CSliderControl(): CCoeControl()
	{
	// No implementation required
	}

CSliderControl::~CSliderControl()
	{
	Components().ResetAndDestroy();
	delete iIcon;
	delete iBgContext;
	}
void CSliderControl::SetMax(TInt aMax)
	{iSlider->iMaxVal=aMax;}
void CSliderControl::SetMin(TInt aMin)
	{iSlider->iMinVal=aMin;}
void CSliderControl::SetLabel(TPtrC aText)
	{iLabel->SetTextL(aText); DrawNow();}

void CSliderControl::HandlePointerEventL(const TPointerEvent& aEvent)
{
	TRawEvent ev;
	TInt x,y,middle,key;
	TRect cba;
	
	x=Position().iX+aEvent.iPosition.iX;
	y=Position().iY+aEvent.iPosition.iY;
	AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EControlPane,cba);
	middle=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth/2;
	if (cba.Contains(TPoint(x,y))&&(aEvent.iType==aEvent.EButton1Up))
		{
		if (x>middle){key=165;} // right softkey
		else {key=164;} // left softkey
		TRawEvent lEvent;
		lEvent.Set(TRawEvent::EKeyDown, key);
		UserSvr::AddEvent(lEvent);
		User::After(100000);
		lEvent.Set(TRawEvent::EKeyUp, key);
		UserSvr::AddEvent(lEvent);
		}
	CCoeControl::HandlePointerEventL(aEvent);
}
CSliderControl* CSliderControl::NewLC(CCoeControl* aParent,TInt aResId)
	{
	CSliderControl* self = new (ELeave) CSliderControl();
	CleanupStack::PushL(self);
	self->ConstructL(aParent,aResId);
	return self;
	}

CSliderControl* CSliderControl::NewL(CCoeControl* aParent,TInt aResId)
	{
	CSliderControl* self = CSliderControl::NewLC(aParent,aResId);
	CleanupStack::Pop(); // self;
	return self;
	}
void CSliderControl::SetVal(TInt aVal)
	{
	iVal=aVal;
	TBuf<3> txt;
	txt.Num(iVal);
	iSlider->SetValue(aVal);
	DrawNow();
	}
TInt CSliderControl::GetVal()
	{
	iVal=iSlider->Value();
	return iVal;
	}
void CSliderControl::ConstructL(CCoeControl* aParent,TInt aResId)
	{
	TResourceReader reader;
	CEikonEnv::Static()->CreateResourceReaderLC(reader,aResId);
	CleanupStack::Pop(1); //reader
	ConstructFromResourceL(reader);
	}

void CSliderControl::LoadPicture()
	{
	
	CFbsBitmap* BitMap = new (ELeave) CFbsBitmap();
	BitMap->Create(Size(),EColor16M);
	CAknsBasicBackgroundControlContext* iContext = 
			CAknsBasicBackgroundControlContext::NewL(KAknsIIDQsnBgAreaMain,Rect(),ETrue);
	CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL(BitMap);
	CBitmapContext* bitGc = NULL;
	bitmapDevice->CreateBitmapContext(bitGc);
	///
	CleanupStack::PushL(iContext);
	CleanupStack::PushL(bitmapDevice);
	CleanupStack::PushL(bitGc);
	AknsDrawUtils::DrawBackground(AknsUtils::SkinInstance(),iContext,NULL,*bitGc,TPoint(0,0),Rect(),0);
	CleanupStack::PopAndDestroy(3);
	iIcon=BitMap;
	
	/*
	CFbsBitmap* mask;
	CFbsBitmap* icon;
	_LIT(KPath,"\\resource\\apps\\TweakS_ui.mif");
	AknIconUtils::CreateIconL(icon,mask,KPath,EMbmTweaks_uiButton_dlg_bg,EMbmTweaks_uiButton_dlg_bg_mask);
	AknIconUtils::SetSize(icon,Size(),EAspectRatioNotPreserved);
	AknIconUtils::SetSize(mask,Size(),EAspectRatioNotPreserved);
	iIcon=CGulIcon::NewL(icon,mask);
	*/
	}
void CSliderControl::Draw(const TRect& aRect) const
	{
	// Get the standard graphics context
	 CWindowGc& gc = SystemGc();
	 
	 // Redraw the background using the default skin
	 MAknsSkinInstance* skin = AknsUtils::SkinInstance();
	 MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
	 AknsDrawUtils::Background( skin, cc, this, gc, aRect );
	}

void CSliderControl::ShrinkRects(TRect aRect,TInt aDir)
	{
	SetExtent(aRect.iTl,aRect.Size());
	CCoeControlArray::TCursor cursor = Components().Begin();
	CCoeControl* ctrl = NULL;
	TInt i=0;
	TRect r;
	while ((ctrl = cursor.Control<CCoeControl>()) != NULL)
	    {
		if (aDir==EDirectionHorizontal)
			{
			TInt w=aRect.Size().iWidth/Components().Count();
			TInt h=aRect.Size().iHeight;
			r=TRect(i*w,0,(i+1)*w,aRect.Height());
			}
		else if (aDir==EDirectionVertical)
			{
			TInt w=aRect.Size().iWidth;
			TInt h=aRect.Size().iHeight/Components().Count();
			r=TRect(0,h*i,aRect.Width(),h*(i+1));
			}		
		ctrl->SetRect(r);
	    cursor.Next();
	    i++;
	    }
	}

TKeyResponse CSliderControl::OfferKeyEventL(const TKeyEvent& aKeyEvent, enum TEventCode aType)
	{
	if (iSlider)
		{iSlider->OfferKeyEventL(aKeyEvent,aType);}
	return CCoeControl::OfferKeyEventL(aKeyEvent,aType);
	DrawNow();
	}

void CSliderControl::SizeChanged()
	{
	 if (iBgContext)
		 {
		 iBgContext->SetRect(Rect());
		 if ( &Window() )
			 {iBgContext->SetParentPos( PositionRelativeToScreen() );}
		 }	
	 
    TInt scrX=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iWidth;
    TInt scrY=CEikonEnv::Static()->ScreenDevice()->SizeInPixels().iHeight;    
    TRect r=TRect(TPoint(0,scrY/3),TSize(scrX,scrY/3));
    if (Position().iY!=r.iTl.iY){ShrinkRects(r,EDirectionVertical);}
	CCoeControl::SizeChanged();
	}

TTypeUid::Ptr CSliderControl::MopSupplyObject(TTypeUid aId)
{
 if (iBgContext )
 {
   return MAknsControlContext::SupplyMopObject( aId, iBgContext );
 }
 return CCoeControl::MopSupplyObject(aId);
}
void CSliderControl::ConstructFromResourceL(TResourceReader& reader)
	{
	iVal=0;
		CreateWindowL();	
		InitComponentArrayL();
		iLabel = new (ELeave) CEikLabel;
		iLabel->SetContainerWindowL(*this);
		TRgb lbc; 
		MAknsSkinInstance* skin=AknsUtils::SkinInstance();
		AknsUtils::GetCachedColor(skin,lbc,KAknsIIDQsnTextColors,EAknsCIQsnTextColorsCG6 );
		iLabel->OverrideColorL(EColorLabelText,lbc);
		iLabel->SetAlignment(EHCenterVCenter);
		iLabel->SetBrushStyle(CGraphicsContext::ENullBrush);
		iLabel->MakeVisible(ETrue);
		iLabel->SetTextL(reader.ReadTPtrC16());
		Components().AppendLC(iLabel);
		CleanupStack::Pop(iLabel);
		_LIT(KDesCEmpty,"");
		iSlider = new (ELeave) CSliderForDialog(KDesCEmpty,0,255);
		iSlider->ConstructL(this);
		iSlider->SetContainerWindowL(*this);
		iSlider->MakeVisible(ETrue);
		Components().AppendLC(iSlider);
		CleanupStack::Pop(iSlider);
		
		//SetExtentToWholeScreen();
		
		iBgContext = CAknsBasicBackgroundControlContext::NewL( KAknsIIDQsnBgAreaMain,TRect(TPoint(0,0),CEikonEnv::Static()->ScreenDevice()->SizeInPixels()),ETrue);	
		ActivateL();
		_LOGDATA2(_L("Window pos: %d,%d"),Window().Position().iX,Window().Position().iY);
		_LOGDATA2(_L("Window size: %d,%d"),Window().Size().iWidth,Window().Size().iHeight);
		
		
	}



CSliderForDialog::CSliderForDialog( const TDesC& aLabel, TInt aValue,TInt aMaxVal) :
   iBvThickness( 1 ), iDelimiter( 2 ), iValue( aValue ), iMaxVal(aMaxVal)
{ 
	iLabel = aLabel; 
}
 
void CSliderForDialog :: ConstructL(CCoeControl* aParent )
{	   
	// ��� ����������� ����� ������������ ���� �� ��������� �������
    font = CEikonEnv::Static()->NormalFont();    
 iParent=aParent;
    // ������ ������������ ����� �������� ����� 
    TBuf<50> tmpLabel;		
    tmpLabel.Num(iMaxVal);
    iMaxLbWidth = font->TextWidthInPixels( tmpLabel);
    SetContainerWindowL(*aParent);
    SetPointerCapture(ETrue);
    EnableDragEvents();
    ActivateL();
    iBgColor=KRgbBlack;
    iBgColor.SetAlpha(255);
}

TKeyResponse CSliderForDialog::OfferKeyEventL(const TKeyEvent& aKeyEvent, enum TEventCode aType)
	{
	TKeyResponse answer=EKeyWasNotConsumed;
	if (aType==EEventKey)
		{
		if (aKeyEvent.iCode==EKeyLeftArrow)
			{TranslateValueL(-1,EFalse);answer=EKeyWasConsumed;}
		else if (aKeyEvent.iCode==EKeyRightArrow)
				{TranslateValueL(1,EFalse);answer=EKeyWasConsumed;}
		}
	DrawNow();
	return answer;
	}


TSize CSliderForDialog :: MinimumSize()
{
	// ����������� ������� �������� ������� �� ������ � ����. ����� �����
    return TSize( iBvThickness * 4 + iDelimiter * 4 + iMaxLbWidth,
    	          iBvThickness * 4 + iDelimiter * 5 + font->HeightInPixels() );    
}

 
void CSliderForDialog :: Draw( const TRect& /*aRect*/ ) const
{
   // ��������� ��������
   TRect rect = Rect();
   TInt runner_w = iMaxLbWidth + 2 * iDelimiter + 2 * iBvThickness;
   TInt runner_h = font->HeightInPixels() + 2 * iDelimiter + 2 * iBvThickness;
   TInt x_offs = rect.iTl.iX + iBvThickness + runner_w / 2;
 
   TPoint line_A( x_offs + 2, rect.iTl.iY + rect.Height() / 2 ),
          line_B( rect.iBr.iX - runner_w / 2 - 2, line_A.iY );
 
   TInt  runner_c = line_A.iX + iValue * ( line_B.iX - line_A.iX ) / iMaxVal;
   TRect iRunner_rect=TRect( runner_c  - runner_w / 2,
                      line_A.iY - runner_h / 2,
                      runner_c  + runner_w / 2,
                      line_A.iY + runner_h / 2 );
 
   TBufC<50> tmpLabel;	
   TPtr tmpPtr = tmpLabel.Des();
   tmpPtr.Append( iLabel );
   tmpPtr.AppendNum( iValue );
 
   TRgb penColor, brushColor;
   if( IsFocused() )
   { 
      penColor = KRgbBlack;
      brushColor = KRgbRed;
   }
   else
   {
      penColor = KRgbWhite;
      brushColor = KRgbGray;
   }
   CWindowGc& gc = SystemGc();
   //Window().SetTransparencyAlphaChannel();
   //TRgb c(0,0,0,0);
   //Window().SetBackgroundColor(c);
   //gc.Clear();
   
   gc.SetPenSize( TSize( iBvThickness, iBvThickness ) );   
   gc.SetPenStyle( CGraphicsContext :: ENullPen );
   gc.SetPenColor( penColor );   
   gc.SetBrushStyle( CGraphicsContext :: ESolidBrush );
   gc.SetPenStyle( CGraphicsContext :: ESolidPen );
 
   gc.DrawLine( line_A, line_B );
 
   gc.SetBrushColor( brushColor );
   gc.DrawRoundRect( iRunner_rect, TSize( 4, 4 ) );   
 
   gc.UseFont( font );   
   gc.DrawText( tmpLabel, TPoint( iRunner_rect.iTl.iX + iDelimiter + iBvThickness, 
	                          iRunner_rect.iBr.iY - iDelimiter - iBvThickness ) );   
}
void CSliderForDialog::HandlePointerEventL(const TPointerEvent& aEvent)
	{
	TInt offset=0;
	_LOG(_L("PointerEvent"));
	if (aEvent.iType==aEvent.EButton1Down)
		{
		_LOG(_L("PointerEventDown"));
		iPenDownPos=aEvent.iPosition;
		}
	else if (aEvent.iType==aEvent.EDrag)
		{
		_LOG(_L("PointerEventMove"));
		iDragged=ETrue;
		}
	else if (aEvent.iType==aEvent.EButton1Up)
		{
		_LOG(_L("PointerEventUp"));
		}
	
	TReal percent=(TReal)aEvent.iPosition.iX/((TReal)(Size().iWidth-40));
	TReal r_new_val=percent*(iMaxVal-iMinVal);
	TReal rval;
	Math::Round(rval,r_new_val,0);
	TInt i_new_val=(TInt)rval;
	offset=i_new_val-iValue;
	
	TBuf<255> a;
	TRealFormat rf;
	a.Num(percent,rf);
	a.Append(_L(", "));
	a.AppendNum(r_new_val,rf);
	a.Append(_L(", "));
	a.AppendNum(offset);
	_LOGDATA(_L("percent,r_newval,offset %S"),&a);
	if (iDragged)
		{
		iValue+=offset;
		if(iValue>iMaxVal){iValue =iMaxVal;}
		if(iValue<iMinVal){iValue = iMinVal;}
		DrawNow();
		iPenDownPos=aEvent.iPosition;
		}
	iDragged=EFalse;
	CCoeControl::HandlePointerEventL(aEvent);
	}
TInt CSliderForDialog::Value() const
	{
	return iValue;
	}
void CSliderForDialog::SetValue(TInt aVal)
	{
	iValue=aVal;
	DrawNow();
	}
void CSliderForDialog::TranslateValueL( TInt aDelta, TBool aFeedback )
    {
    TInt sliderValue = Value();

    sliderValue += aDelta;
    
    // calculate how many pixels was clicked between steps
    TInt betweenSteps = sliderValue % 1;
        
    if ( betweenSteps != 0 )
        {
        sliderValue = sliderValue - betweenSteps;

        // if click was nearer or middle of values, then move it to
        // next possible value
        if ( betweenSteps > ( 1 / 2 ) )
            {
            sliderValue = sliderValue + 1;
            }
        }
    
    if ( sliderValue > iMaxVal )
        {
        sliderValue = iMaxVal;
        }
    else if ( sliderValue < iMinVal )
        {
        sliderValue = iMinVal;
        }
    

    TInt oldSliderValue = Value();
    iValue=sliderValue;

    // start the timer if we tried to move the slider but the slider did
    // not move (in either maximum or minimum already).

        Window().Invalidate( Rect() );
        
    }
