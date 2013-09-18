/*
 * textutils.cpp
 *
 *  Created on: 01.08.2010
 *      Author: mvideo
 */

#include <textutils.h>
#include <utf.h>
#include <e32math.h>
#include <logger.h>
CDesCArray* CTextUtils::Split16(TDes& aText, TDes& aSeparator)
	{
	CDesCArray* arr = new (ELeave) CDesCArrayFlat(3);
	while (aText.Find(aSeparator)!=KErrNone)
		{
		TInt f=aText.Find(aSeparator);
		if (f==KErrNotFound){break;}
		arr->AppendL(aText.Left(f));
		aText.Copy(aText.Right(Abs(f-aText.Length()+aSeparator.Length())));
		}
	
	arr->AppendL(aText);
	return arr;
	}
HBufC* CTextUtils::Des8To16(HBufC8* aBytes)
	{
	HBufC* str1=HBufC::NewL(aBytes->Length()*2); 
	str1=CnvUtfConverter::ConvertToUnicodeFromUtf8L(*aBytes);
	return str1;
	}
