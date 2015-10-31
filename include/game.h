/***************************************************************************
 *            game.h
 *
 *  Sat Aug  6 08:47:46 2005
 *  Copyright  2005  Copyright  2005  Robert Sandilands
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
 
#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include "../include/block3x3.h"

class game
{
public:
	game();
	virtual ~game();
	bool isOk() const { return( installed ); };
	
	void setFixedVal( int bx, int by, int x, int y, int val );
	void seed();
	int calculate_cost();
	int rotate( int initial_cost );
	void dump_state( std::ostream& ostr );
protected:
	block3x3 blocks[BLOCKSIZE][BLOCKSIZE];
	int mostx, mosty;
	int notchanged;
private:
	bool installed;
};

#endif /* _GAME_H */
