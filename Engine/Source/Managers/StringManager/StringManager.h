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
#ifndef CORE_StringManager_H
#define CORE_StringManager_H

class StringManager
{
	protected:
		static StringManager		*m_StringManager;
		StringManager();

	public:
		static  StringManager *getInstance()
		{
			if ( !m_StringManager )
			{
				m_StringManager = new StringManager();
			}

			return m_StringManager;
		}
		int	m_lang;
		const char *getTextByID ( char *idname );
		const wchar_t *getTextByID ( wchar_t *idname );

};

#endif // CORE_StringManager_H
