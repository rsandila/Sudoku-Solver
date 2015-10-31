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
 #include "../include/game.h"
 
 game::game()
 {
	 installed = true;
	 mostx = random()  % 3;
	 mosty = random() % 3;
	 notchanged = 0;
 }
 
game::~game()
 {
 }
 
void game::setFixedVal( int bx, int by, int x, int y, int val )
 {
	 blocks[bx][by].setFixedVal( x, y, val );
 }
 
int game::calculate_cost()
 {
	 bool used[10];
	 int cost;
	 int most_cost, last_cost;
	 // do all x and calculate cost
	 
	 cost = 0;
	 last_cost = 0;
	 for ( int cnty = 0; cnty < 9; cnty++ )
	 {
		 	int blocky = cnty / 3;
		 	int itemy = cnty % 3;
		 
		    memset( used, 0 , sizeof(bool)*10 );
		 	most_cost = 0;
		 	for ( int cntx = 0; cntx<9; cntx++ )
			{
				int val = blocks[ cntx / 3 ][ blocky ].val( cntx % 3, itemy );
				if ( used[val] ) 
				{
					cost+=1;
					most_cost+=1;
				}
				used[val] = true;
			}
			if ( ( most_cost > last_cost ) || ( most_cost == last_cost && random()%2 ) ) 
			{
				mosty = blocky;
				last_cost = most_cost;
			} 
	 }
	 // do all y and calculate cost
	 last_cost = 0;
	 for ( int cntx = 0; cntx < 9; cntx++ )
	 {
		 	int blockx = cntx / 3;
		 	int itemx = cntx % 3;
		 
		    memset( used, 0 , sizeof(bool)*10 );
		 	most_cost = 0;		 
		 	for ( int cnty = 0; cnty < 9; cnty++ )
			{
				int val = blocks[ blockx ][ cnty / 3 ].val( itemx, cnty % 3 );
				if ( used[val] ) 
				{
					cost+=1;
					most_cost+=1;
				}
				used[val] = true;
			}
			if ( ( most_cost > last_cost ) || ( most_cost == last_cost && random()%2 ) ) 
			{
				mostx = blockx;
				last_cost = most_cost;
			}
	 }
	 return( cost );
 }
 
void game::seed()
 {
	 	// do seeding of blocks
	 for ( int cnt = 0; cnt < 9; cnt++ )
	 {
		 blocks[ cnt / 3 ][ cnt % 3 ].rotate();
	 }
 }
 
int game::rotate()
 {
	 // calculate cost
	 int initial_cost = calculate_cost();
	 // pick a block at random and rotate it 
	 int tx, ty;
	 if ( !( random()%10 ) )
	 {
		 tx = random() % 3;
		 ty = random() % 3;
	 }
	 else
	 {
		 tx = mostx;
		 ty = mosty;
	 }
	 block3x3 storage = blocks[ tx ][ ty ];
	 
	 blocks[ tx ][ ty ].rotate();
	 // if cost goes down, repeat
	 int new_cost = calculate_cost();
	 
	 // if cost goes up, restore block to previous state
	 if ( notchanged < 100000 && new_cost > initial_cost )
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
 
void game::dump_state( std::ostream& ostr )
 {
	 for ( int y =0; y < 9 ; y++ )
	 {
		 for ( int x = 0; x < 9; x++ )
		 {
			 ostr << blocks[ x / 3 ][ y / 3].val( x % 3, y %3 ) << "     ";
		 }
		 ostr << std::endl;
	 }
	 ostr /*<< "mostx = " << mostx << ", mosty = " << mosty*/ << std::endl;
 }
