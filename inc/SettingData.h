/*
 * SettingData.h
 *
 *  Created on: 08.07.2010
 *      Author: mvideo
 */

#ifndef SETTINGDATA_H_
#define SETTINGDATA_H_



const TInt EReal=0xfd;
const TInt EString=0xfe;
const TInt EInt=0xff;

const TInt EPropertyInt=0x1;
const TInt EPropertyString8=0x2;
const TInt EPropertyString16=0x3;

const TInt EViewNormal=1;
const TInt EViewUidTxt=2;
const TInt EViewFileName=3;
const TInt EViewBitMask=4;
const TInt EViewUidNum=5;
const TInt EViewSlider=6;
const TInt EViewMacAddress=7;

//for adding plugins
const TInt EKeyTypeAdd=-1;

const TInt EViewAddUidCombo=8;
const TInt EViewAddUid=9;
const TInt EViewAddFolder=10;


struct TComboElement
	{
	TBuf<512> iDescription; // first
	TInt iType;
	TInt iIntValue;  //second
	TBuf<255> iDesValue; // second
	};

struct TSettingData
	{
	TBuf<255> iName; //100
	TBuf<512> iDescription; //101
	TInt iUid;//102
	TInt iKey;//103
	TInt iType; // 104
	TInt iViewType; //105
	TInt iMinValue;  //106
	TInt iMaxValue; //107
	TInt iNumOfCombo;  //108
	CArrayFixSeg<TComboElement>* iComboElements; //109...
	TInt iExists; 
	};

#endif /* SETTINGDATA_H_ */
