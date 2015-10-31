/***************************************************************************
 *            block3x3.cc
 *
 *  Sat Aug  6 08:51:53 2005
 *  Copyright  2005  Robert Sandilands
 *  Email rsandila@netscape.net
 ***************************************************************************/
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
#include <stdlib.h>
#include <memory.h> 
#include "../include/block3x3.h"

block3x3::block3x3()
{
	memset( used, 0, sizeof(bool)*9 );
	memset( fixed, 0, sizeof(bool)*9 );
	memset( block, -1, sizeof( int )*9 );
	installed = true;
}

block3x3::~block3x3()
{
}

int block3x3::val( int x, int y )
{
		return( block[x][y] );
}

void block3x3::setFixedVal( int x, int y, int val )
{
		used[val-1] = true;
		block[x][y] = val;
		fixed[x * 3 + y] = true;
}

void block3x3::rotate()
{
	bool lused[9];
	int x, y;
	
	memcpy( lused, used, 9*sizeof(bool) );
	x = y = 0;
	for ( int cnt = 0; cnt < 9; cnt++ )
	{
		int tmpval;
		
		if ( !fixed[cnt] )
		{
			do
			{
				tmpval = random() % 9;
			} while ( lused[tmpval] );
			lused[tmpval] = true;
			block[ x ][ y ] = tmpval + 1;
		}
		y++;
		if ( y > 2 )
		{
			x += 1;
			y = 0;
		}
	}
}
