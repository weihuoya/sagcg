// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Created by Andrey Sidorov on 07.04.2012.
//  Copyright 2012 Andrey Sidorov. All rights reserved.
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StringManager
//
//
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "StringManager.h"
#include "localization.h"
#include "../../Game/Game.h"



StringManager *StringManager :: m_StringManager=NULL;
StringManager::StringManager()
{
	m_lang=0;
}

const wchar_t *StringManager::getTextByID ( wchar_t *idname )
{
	m_lang=Game::getInstance()->getLanguage();

	for ( int i=0; i<76; i++ )
	{
		wchar_t *tempwchar=wlocalization[i][0];

		if ( wcscmp ( idname, tempwchar ) ==0 )
		{
			return wlocalization[i][m_lang+1];
		}
	}

	return L"ERROR StringManager";
}

const char *StringManager::getTextByID ( char *idname )
{
	m_lang=Game::getInstance()->getLanguage();

	for ( int i=0; i<76; i++ )
	{
		if ( strcmp ( idname, localization[i][0] ) ==0 )
		{
			return localization[i][m_lang+1];
		}
	}

	return "";
}
//