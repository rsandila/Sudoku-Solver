/***************************************************************************
 *            game.cc
 *
 *  Sat Aug  6 08:51:53 2005
 *  Copyright  2005  Robert Sandilands
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
 #include "../include/game_old.h"
 
 
int game_old::rotate(  int initial_cost  )
 {
	 // pick a block at random and rotate it 
	 int tx, ty;
	 if ( random()%2 )
	 {
		 tx = random() % BLOCKSIZE;
		 ty = random() % BLOCKSIZE;
	 }
	 else
	 {
		 tx = mostx;
		 ty = mosty;
	 }
//	 std::cout << "mostx = " << mostx << ", mosty = " << mosty << std::endl;
	 block3x3 storage = blocks[ tx ][ ty ];
	 
	 blocks[ tx ][ ty ].rotate();
	 // if cost goes down, repeat
	 int new_cost = calculate_cost();

	 // if cost goes up, restore block to previous state
	 if ( notchanged < 10000 && new_cost > initial_cost )
	 {
		 	blocks[ tx ][ ty ] = storage;
		 	new_cost = initial_cost;
		 	notchanged += 1;
	 }
	 else
	 {	
		 notchanged = 0;
	 }
	 return( new_cost );
 }
