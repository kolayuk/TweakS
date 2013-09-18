// INCLUDES
#include <apmrec.h>

// CONSTANTS
const TInt KRecognizerExImplementationUid = 0xE9066A15;

/**
*  CApaSampleRecognizer.
*  Recognizer plug-in for .py.
*/
class CApaRecognizerEx: public CApaDataRecognizerType
    {
    public:
        // constructor and destructor
        CApaRecognizerEx();
        virtual ~CApaRecognizerEx();

        // creates and returns recognizer
        static CApaDataRecognizerType* CreateRecognizerL();

        // returns preferred buffer size
        TUint PreferredBufSize();

        // returns supported mime type
        TDataType SupportedDataTypeL(TInt aIndex) const;

    private:
        // recognises the file by name and/or buffer
        void DoRecognizeL(const TDesC& aName, const TDesC8& aBuffer);
    };
