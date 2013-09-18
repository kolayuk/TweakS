/*
 ============================================================================
 Name		: SliderDialog.h
 Author	  : Usanov-Kornilov Nikolay (aka Kolay)
 Version	 : 1.0
 Copyright   : 
 Contacts:
 kolayuk@mail.ru
 http://kolaysoft.ru

 (c) KolaySoft, 2010

 Description : CSliderDialog declaration
 ============================================================================
 */

#ifndef SLIDERDIALOG_H
#define SLIDERDIALOG_H

// INCLUDES


// CLASS DECLARATION
const TInt KSteps=20;




#include <e32std.h>
#include <e32base.h>
#include <coecntrl.h>
#include <gulicon.h>
#include <eiklabel.h>
#include <akndialog.h>
#include <aknsbasicbackgroundcontrolcontext.h>

const TInt EDirectionHorizontal=0;
const TInt EDirectionVertical=1;
class CSliderDialog : public CAknDialog
    {
    public:
    	CSliderDialog(TDes& aLabel,TInt& aVal,TInt aMinVal,TInt aMaxVal);
        static TInt RunDlgLD(TDes& aLabel,TInt& aVal,TInt aMinVal,TInt aMaxVal);
        void PostLayoutDynInitL();
        TBool OkToExitL(TInt aButtonID);
        void ButtonPressed();
        TInt& iVal;
        TInt iMaxVal;
        TInt iMinVal;
        TPtrC iLabel;
    private:
        SEikControlInfo CreateCustomControlL(TInt aControlType);
    };


class CSliderForDialog : public CAknControl
{
   public:
	  void TranslateValueL( TInt aDelta, TBool aFeedback );
	  CSliderForDialog( const TDesC& aLabel, TInt aValue, TInt aMaxVal);
      void ConstructL(CCoeControl* aParent );
      TSize MinimumSize();
      CCoeControl* iParent;
      TInt Value() const;
      void HandlePointerEventL(const TPointerEvent& aEvent);
      TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, enum TEventCode aType);
      TPoint iPenDownPos;
      TBool iDragged;
      TRect iRunner_rect;
      TRgb iBgColor;
      void SetValue(TInt aVal);
      TInt iMaxVal;
      TInt iMinVal;
      TRect iRunnerRect;
   private:
      void Draw( const TRect& aRect ) const;	
 
   private:
 
       TBuf<50> iLabel;
       TInt iValue;
       const CFont* font;	   
       TInt iBvThickness, iDelimiter, iMaxLbWidth;
};



// CLASS DECLARATION
class CSliderControl : public CCoeControl
	{
public:
	~CSliderControl();
	static CSliderControl* NewL(CCoeControl* aParent,TInt aResId);
	static CSliderControl* NewLC(CCoeControl* aParent,TInt aResId);
	void SetVal(TInt aVal);
	TInt GetVal();
	void SetMax(TInt aMax);
	void SetMin(TInt aMin);
	void SetLabel(TPtrC aText);
	void ShrinkRects(TRect aRect,TInt aDir);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, enum TEventCode aType);
	void SizeChanged();
	void ConstructFromResourceL(TResourceReader& reader);
	CSliderControl();
	CAknsBasicBackgroundControlContext* iBgContext;
	TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
	void HandlePointerEventL(const TPointerEvent& aEvent);
private:
	void ConstructL(CCoeControl* aParent,TInt aResId);
	void LoadPicture();
	CFbsBitmap* iIcon;
	void Draw(const TRect& aRect) const;
	CEikLabel* iLabel;
	CSliderForDialog* iSlider;
	TInt iVal;
	};
#endif // SLIDERDIALOG_H
