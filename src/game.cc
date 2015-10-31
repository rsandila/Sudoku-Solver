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
	 mostx = random()  % BLOCKSIZE;
	 mosty = random() % BLOCKSIZE;
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
	 bool used[BLOCKSIZE*BLOCKSIZE+1];
	 int cost;
	 int most_cost, last_cost;
	 // do all x and calculate cost
	 
	 cost = 0;
	 last_cost = 0;
	 for ( int cnty = 0; cnty < BLOCKSIZE*BLOCKSIZE; cnty++ )
	 {
		 	int blocky = cnty / BLOCKSIZE;
		 	int itemy = cnty % BLOCKSIZE;
		 
		    memset( used, 0 , sizeof(bool)*(BLOCKSIZE*BLOCKSIZE+1) );
		 	most_cost = 0;
		 	for ( int cntx = 0; cntx<BLOCKSIZE*BLOCKSIZE; cntx++ )
			{
				int val = blocks[ cntx / BLOCKSIZE ][ blocky ].val( cntx % BLOCKSIZE, itemy );
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
	 for ( int cntx = 0; cntx < BLOCKSIZE*BLOCKSIZE; cntx++ )
	 {
		 	int blockx = cntx / BLOCKSIZE;
		 	int itemx = cntx % BLOCKSIZE;
		 
		    memset( used, 0 , sizeof(bool)*( BLOCKSIZE * BLOCKSIZE +1) );
		 	most_cost = 0;		 
		 	for ( int cnty = 0; cnty < (BLOCKSIZE*BLOCKSIZE); cnty++ )
			{
				int val = blocks[ blockx ][ cnty / BLOCKSIZE ].val( itemx, cnty % BLOCKSIZE );
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
	 for ( int cnt = 0; cnt < BLOCKSIZE*BLOCKSIZE; cnt++ )
	 {
		 blocks[ cnt / BLOCKSIZE ][ cnt % BLOCKSIZE ].seed();
	 }
 }
 
int game::rotate(  int initial_cost  )
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
 
void game::dump_state( std::ostream& ostr )
 {
	 for ( int y =0; y < BLOCKSIZE*BLOCKSIZE ; y++ )
	 {
		 for ( int x = 0; x < BLOCKSIZE*BLOCKSIZE; x++ )
		 {
        	 ostr.width( 4 );
			 ostr << blocks[ x / BLOCKSIZE ][ y / BLOCKSIZE ].val( x % BLOCKSIZE, y % BLOCKSIZE );
		 }
		 ostr << std::endl;
	 }
	 ostr /*<< "mostx = " << mostx << ", mosty = " << mosty*/ << std::endl;
 }
