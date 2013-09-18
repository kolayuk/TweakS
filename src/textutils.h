/*
 * textutils.h
 *
 *  Created on: 01.08.2010
 *      Author: mvideo
 */

#ifndef TEXTUTILS_H_
#define TEXTUTILS_H_

#include <e32base.h>
#include <BADESCA.H>

class CTextUtils
	{
public:
	static CDesCArray* Split16(TDes& aText,TDes& aSeparator);
	static HBufC* Des8To16(HBufC8* aData);
	};
#endif /* TEXTUTILS_H_ */
