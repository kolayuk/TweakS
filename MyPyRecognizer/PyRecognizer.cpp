// INCLUDE FILES
#include <apmrec.h>
#include <apmstd.h>
#include <ImplementationProxy.h>
#include "PyRecognizer.h"

// CONSTANTS
const TUid KUidRecognizerEx={0xE9066A15};
const TInt KMaxBufferLength=4;                  // maximum amount of buffer space we will ever use
const TInt KRecRtFileExtensionsMightBeValid=4;  // If the file name length > 4, the file extension might be valid

_LIT(KExtension1, ".twk");
_LIT8(KDataType,"application/tweaks");

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// RecognizerEx::RecognizerEx()
// constructs the object
// ---------------------------------------------------------
//
CApaRecognizerEx::CApaRecognizerEx()
    : CApaDataRecognizerType(KUidRecognizerEx, CApaDataRecognizerType::ENormal)
    {
    iCountDataTypes=1;
    }

// ---------------------------------------------------------
// RecognizerEx::~RecognizerEx()
// Destroys the object
// ---------------------------------------------------------
//
CApaRecognizerEx::~CApaRecognizerEx()
    {
    // Do nothing
    }

// ---------------------------------------------------------
// RecognizerEx::PreferredBufSize()
// Returns preferred buffer size
// ---------------------------------------------------------
//
TUint CApaRecognizerEx::PreferredBufSize()
    {
    return KMaxBufferLength;
    }

// ---------------------------------------------------------
// RecognizerEx::SupportedDataTypeL()
// Returns supported mime type
// ---------------------------------------------------------
//
TDataType CApaRecognizerEx::SupportedDataTypeL(TInt /*aIndex*/) const
    {
    return TDataType(KDataType);
    }

// ---------------------------------------------------------
// RecognizerEx::DoRecognizeL()
// Recognizes the file by name and/or head buffer
// ---------------------------------------------------------
//
void CApaRecognizerEx::DoRecognizeL(const TDesC& aName, const TDesC8& /*aBuffer*/)
    {
    // To keep code simple, we only check file name extension
    if (aName.Length()>KRecRtFileExtensionsMightBeValid)
    {
        if (aName.Right(KRecRtFileExtensionsMightBeValid).CompareF(KExtension1)==0)
        {
            iConfidence=ECertain;   // is certainly something totally new
            iDataType=TDataType(KDataType);
            return;
        }
    }
    }

// ================= OTHER EXPORTED FUNCTIONS ==============

#ifdef __SERIES60_3X__

// ---------------------------------------------------------
// RecognizerEx::CreateRecognizerL()
// Returns pointer to the new object
// ---------------------------------------------------------
//
CApaDataRecognizerType* CApaRecognizerEx::CreateRecognizerL()
    {
    return new (ELeave) CApaRecognizerEx();
    }

const TImplementationProxy ImplementationTable[] =
    {
    IMPLEMENTATION_PROXY_ENTRY(KRecognizerExImplementationUid, CApaRecognizerEx::CreateRecognizerL)
    };

// ---------------------------------------------------------
// ImplementationGroupProxy
// Provides access to the implementationtable
// ---------------------------------------------------------
//
EXPORT_C const TImplementationProxy* ImplementationGroupProxy(TInt& aTableCount)
    {
    aTableCount = sizeof(ImplementationTable) / sizeof(TImplementationProxy);
    return ImplementationTable;
    }

#else
EXPORT_C CApaDataRecognizerType* CreateRecognizer()
    {
    CApaDataRecognizerType* thing=new CApaRecognizerEx();
    return thing; // NULL if new failed
    }

GLDEF_C TInt E32Dll(TDllReason /*aReason*/)
    {
    return KErrNone;
    }
#endif
