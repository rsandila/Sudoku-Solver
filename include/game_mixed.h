/***************************************************************************
 *            game_mixed.h
 *
 *  Sat May 27 13:12:40 EDT 2006
 *  Copyright  2006  Copyright  2006  Robert Sandilands
 *  Email rsandila@netscape.net
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 #ifndef __GAME_MIXED_H__
 #define __GAME_MIXED_H__
 
 #include "../include/game_old.h"
 #include "../include/game_simann.h"
 #include "../include/parameters.h"
 
 class game_mixed: public game_base
 {
	 public:
	 	game_mixed();
	 	int rotate( int initial_cost );
		virtual void dump_rotate_state( std::ostream & ostr ) const;
		virtual void setFixedVal( int bx, int by, int x, int y, int val );
		virtual void seed();	 
		virtual void dump_state( std::ostream& ostr );	 
		virtual int calculate_cost();	 
	 protected:
		parameters::search_type stype;
	 	game_simann simann;
	 	game_old old;
 };
 #endif
