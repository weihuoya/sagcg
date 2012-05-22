#include "StdAfx.h"
#include "Logs.h"

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Members
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Logs::s_newSession = true;


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Methods
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Logs::error ( const char *msg )
{
	DBG ( "ERROR: %s\n", msg );
	std::cin.get();
}

void Logs::warning ( const char *msg )
{
	DBG ( "WARNING: %s\n", msg );
}

void Logs::info ( const char *msg )
{
	DBG ( "%s\n", msg );
}

void Logs::debug ( const char *msg )
{
#if LOG_DEBUG
	DBG ( "DEBUG: %s\n", msg );
#endif
}

void Logs::trace ( const char *header, const char *msg )
{
#if LOG_DEBUG
	DBG ( "TRACE: <%s> %s\n", header, msg );
#endif
}


void Logs::newPointer ( void *ptr, const char *clsname, const char *filename, int lineNumber )
{
#if defined(WIN32)
	FILE *f;
	fopen_s ( &f, "__new.log", s_newSession ? "w" : "a" );
	fprintf ( f, " @ %08x : %s (%s:%d)\n", ptr, clsname, filename, lineNumber );
	fclose ( f );
	s_newSession = false;
#endif
}

