#include "StdAfx.h"
#include "Game/Game.h"
#include "GSTestedState.h"
#include "Managers/UIManager/UIObject.h"
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSTestedState::GSTestedState()
{
	Logs::debug ( "GSTestedState\n" );
	m_isGame = Game::getInstance();
	m_isEventManager = & ( EventManager::getInstance() );
	m_isStateMachine = & ( StateMachine::getInstance() );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GSTestedState::~GSTestedState()
{
	Logs::debug ( "~GSTestedState\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State CTOR (when added to the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTestedState::ctor	( const StateMachine *sm )
{
	Logs::debug ( "State GSTestedState::ctor\n" );
	//	camera =m_isGame->getSceneManager()->addCameraSceneNodeFPS();
	camera =m_isGame->getSceneManager()->addCameraSceneNode();
	camera->setFarValue ( 42000.0f );
#ifdef GAMESWF
	cUIObject *test;
	test=m_isGame->getUIManager()->CreateUIObject ( "data/swf/test.swf" );
	//test->SetBoolean("_root.b1._visible",false);
	/*
	target._x            = value; // The X position (in  pixels) of the target clip.
	target._y            = value; // Etc. as above.
	target._width        = value;
	target._height       = value;
	target._rotation     = value;
	target._target       = value;
	target._name         = value;
	target._xscale       = value;
	target._yscale       = value;
	target._alpha        = value;
	target._visible      = value;
	target._droptarget   = value;
	target._currentframe = value;
	target._totalframes  = value;
	target._framesloaded = value;
	*/
	//test->SetBoolean("_root.text1._alpha",50);
	test->SetString ( "_root.text1.text", L"55333322" );
#endif
	//////////////
	// считываем данные
	io::IXMLReader *xml =    m_isGame->getIrrlichtDevice()->getFileSystem()->createXMLReader ( "../data/content.xml" ); // объект для работы с XML
	const wchar_t *data;
	const wchar_t *name;

	while ( xml && xml->read() )
	{
		printf ( "EXN\n" );
		data=xml->getNodeData();
		/*
		if(strcmp("table:table-row", data))
		{
		printf("ddd\n");
		}
		*/
		/*switch(xml->getNodeType())
		{
		case EXN_NONE:
			data=xml->getNodeData();
			name=xml->getNodeName();
			printf("EXN_NONE\n");
			break;
		case EXN_ELEMENT:
			data=xml->getNodeData();
			name=xml->getNodeName();
			printf("EXN_ELEMENT\n");
			break;
		case EXN_ELEMENT_END:
			data=xml->getNodeData();
			name=xml->getNodeName();
			printf("EXN_ELEMENT_END\n");
			break;
		case EXN_TEXT:
			data=xml->getNodeData();
			name=xml->getNodeName();
			printf("EXN_TEXT\n");
			break;
		case EXN_COMMENT:
			data=xml->getNodeData();
			name=xml->getNodeName();
			printf("EXN_COMMENT\n");
			break;
		case EXN_CDATA:
			data=xml->getNodeData();
			name=xml->getNodeName();
			printf("EXN_CDATA\n");
			break;
		case EXN_UNKNOWN:
			data=xml->getNodeData();
			name=xml->getNodeName();
			printf("EXN_UNKNOWN\n");
			break;
			//if(strcmp("model", xml->getNodeName()));
		}*/
	}

	delete xml;
	/////////////
	m_isGame->getIrrlichtDevice()->getFileSystem()->addZipFileArchive ( "data/maps/level1.pxd" );
	scene::IAnimatedMesh *mesh = m_isGame->getSceneManager()->getMesh ( "level1.3ds" );
	mesh->setMaterialFlag ( EMF_LIGHTING, false );
	scene::ISceneNode *node = 0;

	if ( mesh )
	{
		node = m_isGame->getSceneManager()->addOctreeSceneNode ( mesh->getMesh ( 0 ), 0, -1, 1024 );
	}

	if ( node )
	{
		node->setPosition ( core::vector3df ( 0,0,0 ) );
	}

	renderSkyTexture=m_isGame->getVideoDriver()->addRenderTargetTexture ( core::dimension2d< u32 > ( 512,512 ), "RTT1" );
	scene::ISceneNode *skySceneNode=m_isGame->getSceneManager()->addSkyBoxSceneNode (
	                                    m_isGame->getVideoDriver()->getTexture ( "data/irrlicht2_up.jpg" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/irrlicht2_dn.jpg" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/irrlicht2_lf.jpg" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/irrlicht2_rt.jpg" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/irrlicht2_ft.jpg" ),
	                                    m_isGame->getVideoDriver()->getTexture ( "data/irrlicht2_bk.jpg" ),
	                                    camera );

	for ( int i=0; i<6; i++ )
	{
		skyMaterial[i]=&skySceneNode->getMaterial ( i );
	}

	scene::IAnimatedMeshSceneNode *crazyskymesh = m_isGame->getSceneManager()->addAnimatedMeshSceneNode ( m_isGame->getSceneManager()->getMesh ( "data/crazysky/sky2.x" ) );
	crazyskymesh->setMaterialFlag ( EMF_LIGHTING, false );
	crazyskymesh->setPosition ( core::vector3df ( 0,-50000,0 ) );
	crazyskymesh->setAnimationSpeed ( 0.3f );
	//IAnimatedMesh* crazyskymesh = m_isGame->getSceneManager()->getMesh("data/crazysky/sky.x");
	SkyCameraBone=0;
	cameraSky=m_isGame->getSceneManager()->addCameraSceneNode();
	SkyCameraBone=crazyskymesh->getJointNode ( "CameraBone" );

	if ( SkyCameraBone )
	{
		//SkyCameraBone->addChild(cameraSky);
		Logs::debug ( " JointNode Bip01_Spine \n" );
	}

	m_isGame->getSceneManager()->setActiveCamera ( camera );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State DTOR (when removed from the StateMachine stack)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTestedState::dtor	( const StateMachine *sm )
{
	Logs::debug ( "State GSTestedState::dtor\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State update (game update: update)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTestedState::update ( StateMachine *sm )
{
	Logs::debug ( "State GSTestedState::update\n" );
	//skyPlaneSceneNode->setRotation(m_isGame->getSceneManager()->getActiveCamera()->getRotation());
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State pause (when a new state is added atop)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTestedState::pause	( const StateMachine *sm )
{
	Logs::debug ( "State GSTestedState::pause\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State resume (when the state above is removed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTestedState::resume	( const StateMachine *sm )
{
	Logs::debug ( "State GSTestedState::resume\n" );
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw (game update: draw)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTestedState::draw	( const StateMachine *sm )
{
	//SkyCameraBone->setRotation(camera->getRotation());
	//cameraSky->setRotation(core::vector3df(SkyCameraBone->getRotation().X+300,SkyCameraBone->getRotation().Y,SkyCameraBone->getRotation().Z));
	//cameraSky->updateAbsolutePosition();
	if ( renderSkyTexture )
	{
		m_isGame->getVideoDriver()->setRenderTarget ( renderSkyTexture, true, true, video::SColor ( 0,0,0,255 ) );
		m_isGame->getSceneManager()->setActiveCamera ( cameraSky );
		cameraSky->setTarget ( core::vector3df
		                       (
		                           cameraSky->getPosition().X+ ( camera->getPosition().X-camera->getTarget().X ),
		                           cameraSky->getPosition().Y- ( camera->getPosition().Y-camera->getTarget().Y ),
		                           cameraSky->getPosition().Z+ ( camera->getPosition().Z-camera->getTarget().Z )
		                       ) );
		cameraSky->setPosition ( SkyCameraBone->getAbsolutePosition() );
		//						cameraSky->setTarget(camera->getRotation());
		//						printf("%f %f %f \n"camera->getRotation().X,camera->getRotation().Y,camera->getRotation().Z);
		m_isGame->getSceneManager()->drawAll();
		m_isGame->getVideoDriver()->setRenderTarget ( 0, true, true, 0 );
		m_isGame->getSceneManager()->setActiveCamera ( camera );

		for ( int i=0; i<6; i++ )
		{
			skyMaterial[i]->setTexture ( 0,renderSkyTexture );
		}
	}

	Logs::debug ( "State GSTestedState::draw\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State draw2d (draw 2d elements in front)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTestedState::draw2d	( const StateMachine *sm )
{
	Logs::debug ( "State GSTestedState::draw2d\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State sleep (application is interrupted)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTestedState::sleep	( const StateMachine *sm )
{
	Logs::debug ( "State GSTestedState::sleep\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// State wakeup (application is resumed)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GSTestedState::wakeup	( const StateMachine *sm )
{
	Logs::debug ( "State GSTestedState::wakeup\n" );
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Update and Draw(draw2d) regardless of pause)
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSTestedState::isWorkingInParallel()
{
return true;
}
*/

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configuration state (If this option is true the state Loding screen Disable. )
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
bool GSTestedState::isLoadingDisable()
{
return true;
}
*/


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EReceiver
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	GSTestedState::onEvent ( const EEvent *ev, const EventManager *evMgr )
{
	Logs::debug ( "State GSTestedState onEvent\n" );
}



