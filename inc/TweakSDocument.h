/*
========================================================================
 Name        : TweakSDocument.h
 Author      : Kolay
 Copyright   : TweakS - it is a tweaker for Symbian OS
Contacts:
	kolayuk@mail.ru
	http://kolaysoft.ru

(c) KolaySoft, 2010

 Description : 
========================================================================
*/
#ifndef TWEAKSDOCUMENT_H
#define TWEAKSDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CTweakSDocument TweakSDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CTweakSDocument : public CAknDocument
	{
public: 
	// constructor
	static CTweakSDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CTweakSDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // TWEAKSDOCUMENT_H
