 /***************************************************************************
 *            main.cc
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

#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/game.h"

bool isSaneXY( int val )
{
	if ( val >=0 && val<=3 ) return( true );
	return( false );
}

int load_initial_state( game & mygame, const char * fname )
{
	std::ifstream inp( fname );
	
	if ( !inp.good() ) return( 1 );
	std::cout << "Loading initial state from " << fname << std::endl;
	//int linecount = 1;	
	do
	{
		std::string line;
		
		std::getline( inp, line );
		if ( inp.eof() ) break;
//		std::cout << "Parsing line: " << linecount++ << " " << line << std::endl;
		std::istringstream parse( line );
		
		int bx, by, x, y, val, rx, ry;
		
		parse >> rx;
		parse	>> ry;
		parse	>> val;
		bx = rx / 3;
		by = ry / 3;
		x = rx % 3;
		y = ry % 3;
		if ( !isSaneXY( bx ) || !isSaneXY( by ) || 
			  !isSaneXY( x ) || !isSaneXY( y ) ||
			  val < 1 || val > 9 )
		{
			std::cerr << "Invalid line in " << fname << " with contents " << line << std::endl;
			return( 1 );
		}
		mygame.setFixedVal( bx, by, x, y, val );
	} while ( !inp.eof() );
	return( 0 );
}

int main( int argc, char ** argv )
{
	game mygame;
	time_t t;
	time( &t );
	srandom( t );
	if ( argv[1] )
	{
		int result = load_initial_state( mygame, argv[1] );
		if ( result )
		{
			std::cerr << argv[0] << ": Error loading initial state" << std::endl;
			return( 1 );
		}
    	mygame.dump_state( std::cout );
	}
	
	std::cout << "Seeding" << std::endl;
	mygame.seed();
	
	mygame.dump_state( std::cout );
	std::cout << "Press ENTER to start" << std::endl << std::flush;
	getchar();
	int cost, round;
	round = 0;
	do 
	{
		cost = mygame.rotate();
		round+=1;
		if ( ( round %100 ) == 0 ) std::cout << "COST: round = " << round << ", cost = " << cost << std::endl;
//		if ( ( round % 100 ) == 0 ) mygame.dump_state( std::cout );
//		getchar();
	} while ( cost );
	time_t endt;
	time( &endt );
	mygame.dump_state( std::cout );
	std::cout << "Solution took " << difftime( endt, t ) << " seconds" << std::endl;
	return 0;
}
