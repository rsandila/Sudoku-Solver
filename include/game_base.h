/***************************************************************************
 *            game.h
 *
 *  Sat May 27 2006
 *  Copyright  2006  Robert Sandilands
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
 
#ifndef _GAME_BASE_H
#define _GAME_BASE_H

#include <iostream>
#include "../include/block3x3.h"

class game_base
{
public:
	game_base();
	virtual ~game_base();
	virtual bool isOk() const { return( installed ); };
	
	virtual void setFixedVal( int bx, int by, int x, int y, int val );
	virtual void seed();
	virtual int calculate_cost();
	virtual int rotate( int initial_cost ) = 0;
	virtual void dump_state( std::ostream& ostr );
	virtual void dump_rotate_state( std::ostream & ostr ) const {;};
		
	bool copy( const game_base & other );
protected:
	block3x3 blocks[BLOCKSIZE][BLOCKSIZE];
	int mostx, mosty;
	int notchanged;
private:
	bool installed;
};

#endif /* _GAME_H */
