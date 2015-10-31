/***************************************************************************
 *            game_base.cc
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
 #include "../include/game_base.h"
 
 //#define USES_RANDOM_XY
 
 game_base::game_base()
 {
	 installed = true;
	 mostx = random()  % BLOCKSIZE;
	 mosty = random() % BLOCKSIZE;
	 notchanged = 0;
 }
 
game_base::~game_base()
{
}
 
void game_base::setFixedVal( int bx, int by, int x, int y, int val )
{
	 blocks[bx][by].setFixedVal( x, y, val );
}
 
int game_base::calculate_cost()
{
	 bool used[BLOCKSIZE*BLOCKSIZE+1];
	 int cost;
#ifndef USES_RANDOM_XY
	 int most_cost, last_cost;
#endif	
	 // do all x and calculate cost
	 
	 cost = 0;
#ifndef USES_RANDOM_XY
	 last_cost = 0;
#endif	
	 for ( int cnty = 0; cnty < BLOCKSIZE*BLOCKSIZE; cnty++ )
	 {
		 	int blocky = cnty / BLOCKSIZE;
		 	int itemy = cnty % BLOCKSIZE;
		 
		    memset( used, 0 , sizeof(bool)*(BLOCKSIZE*BLOCKSIZE+1) );
#ifndef USES_RANDOM_XY
		 	most_cost = 0;
#endif		 
		 	for ( int cntx = 0; cntx<BLOCKSIZE*BLOCKSIZE; cntx++ )
			{
				int val = blocks[ cntx / BLOCKSIZE ][ blocky ].val( cntx % BLOCKSIZE, itemy );
				if ( used[val] ) 
				{
					cost+=1;
#ifndef USES_RANDOM_XY
					most_cost+=1;
#endif					
				}
				used[val] = true;
			}
#ifndef USES_RANDOM_XY
			if ( ( most_cost > last_cost ) || ( most_cost == last_cost && random()%2 ) ) 
			{
				mosty = blocky;
				last_cost = most_cost;
			} 
#endif			
	 }
	 // do all y and calculate cost
#ifndef USES_RANDOM_XY
	 last_cost = 0;
#endif	 
	 for ( int cntx = 0; cntx < BLOCKSIZE*BLOCKSIZE; cntx++ )
	 {
		 	int blockx = cntx / BLOCKSIZE;
		 	int itemx = cntx % BLOCKSIZE;
		 
		    memset( used, 0 , sizeof(bool)*( BLOCKSIZE * BLOCKSIZE +1) );
#ifndef USES_RANDOM_XY
		 	most_cost = 0;		 
#endif		 
		 	for ( int cnty = 0; cnty < (BLOCKSIZE*BLOCKSIZE); cnty++ )
			{
				int val = blocks[ blockx ][ cnty / BLOCKSIZE ].val( itemx, cnty % BLOCKSIZE );
				if ( used[val] ) 
				{
					cost+=1;
#ifndef USES_RANDOM_XY
					most_cost+=1;
#endif					
				}
				used[val] = true;
			}
#ifndef USES_RANDOM_XY
			if ( ( most_cost > last_cost ) || ( most_cost == last_cost && random()%2 ) ) 
			{
				mostx = blockx;
				last_cost = most_cost;
			}
#endif
	}
#ifdef USES_RANDOM_XY
	mostx = random() % BLOCKSIZE;
	mosty = random() % BLOCKSIZE;
#endif	
	 return( cost );
}
 
void game_base::seed()
{
	 	// do seeding of blocks
	 for ( int cnt = 0; cnt < BLOCKSIZE*BLOCKSIZE; cnt++ )
	 {
		 blocks[ cnt / BLOCKSIZE ][ cnt % BLOCKSIZE ].seed();
	 }
}
  
void game_base::dump_state( std::ostream& ostr )
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

bool game_base::copy( const game_base & other )
{
	int cntx, cnty;
	
	if ( !isOk() || !other.isOk() ) return( false );
	
	for (cntx = 0; cntx < BLOCKSIZE; cntx++ )
	{
		for (cnty = 0; cnty < BLOCKSIZE; cnty++ )
		{
			blocks[ cntx ][ cnty ] = other.blocks[ cntx ][ cnty ];
		}
	}		
	mostx = other.mostx;
	mosty = other.mosty;
	installed = true;
	return( true );
}
