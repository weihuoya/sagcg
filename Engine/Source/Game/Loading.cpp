//
//  Created by Andrey Sidorov on 03.02.2012.
//  Copyright 2012 Andrey Sidorov. All rights reserved.
//

#include "StdAfx.h"
#include "Loading.h"
#include "Game/Game.h"
Loading *Loading ::m_Loading=NULL;
Loading::Loading()
{
	m_visibleLoading=false;
	m_loadingIGUIImage=false;
	isLoadingInit=false;
}


void Loading::Init()
{
	m_isGame = Game::getInstance();

	if ( !m_isGame )
	{
		return;
	}

	video::ITexture *image=m_isGame->getVideoDriver()->getTexture ( "data/loading.png" );
	m_loadingIGUIImage = m_isGame->getGUIEnvironment()->addImage ( image,
	                     core::position2d<s32> ( 10, 10 ) );
	// lock the logo's edges to the bottom left corner of the screen
	m_loadingIGUIImage->setAlignment ( EGUIA_UPPERLEFT, EGUIA_UPPERLEFT,
	                                   EGUIA_LOWERRIGHT, EGUIA_LOWERRIGHT );
	isLoadingInit=true;
}
void Loading::Run()
{
	if ( !isLoadingInit )
	{
		return;
	}

	m_isGame = Game::getInstance();

	if ( !m_isGame )
	{
		return;
	}

	/*	m_isGame->getIrrlichtDevice()->getCursorControl()->setVisible ( !m_visibleLoading );*/
	m_isGame->getVideoDriver()->beginScene ( true, true, SColor ( 255,0,0,0 ) );

	if ( m_loadingIGUIImage )
	{
		m_loadingIGUIImage->setVisible ( m_visibleLoading );
	}

	m_isGame->getGUIEnvironment()->drawAll();
	m_isGame->getSceneManager()->drawAll();
	m_isGame->getVideoDriver()->endScene();
}

void Loading::LoadingOn()
{
	if ( m_visibleLoading )
	{
		return;
	}

	m_visibleLoading=true;

	if ( !isLoadingInit )
	{
		Init();
	}

	Run();
}

void Loading::LoadingOff()
{
	if ( !m_visibleLoading )
	{
		return;
	}

	m_visibleLoading=false;
	Run();
}

