//
//  Created by Andrey Sidorov on 03.02.2012.
//  Copyright 2012 Andrey Sidorov. All rights reserved.
//

#ifndef Loading_H
#define Loading_H

namespace irr
{
	namespace gui
	{
		class IGUIImage;
	}
}

class Game;
class Loading
{
	protected:
		static Loading		*m_Loading;
		bool	m_visibleLoading;
		Loading();

	public:
		static  Loading *getInstance()
		{
			if ( !m_Loading )
			{
				m_Loading = new Loading();
			}

			return m_Loading;
		}

		void LoadingOn();
		void LoadingOff();
		void Run();
		void Init();
		Game 				*m_isGame;
		irr::gui::IGUIImage *m_loadingIGUIImage;
		bool isLoadingInit;

};

#endif // Loading_H
