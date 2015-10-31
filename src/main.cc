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
#include <getopt.h>
#include "../include/parameters.h"
#include "../include/game_old.h"
#include "../include/game_simann.h"
#include "../include/game_mixed.h"

bool isSaneXY( int val )
{
	if ( val >=0 && val<=BLOCKSIZE ) return( true );
	return( false );
}

int load_initial_state( game_base & mygame, const std::string& fname )
{
	std::ifstream inp( fname.c_str() );
	
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
		bx = rx / BLOCKSIZE;
		by = ry / BLOCKSIZE;
		x = rx % BLOCKSIZE;
		y = ry % BLOCKSIZE;
		if ( !isSaneXY( bx ) || !isSaneXY( by ) || 
			  !isSaneXY( x ) || !isSaneXY( y ) ||
			  val < 1 || val > BLOCKSIZE*BLOCKSIZE )
		{
			std::cerr << "Invalid line in " << fname << " with contents " << line << std::endl;
			return( 1 );
		}
		mygame.setFixedVal( bx, by, x, y, val );
	} while ( !inp.eof() );
	return( 0 );
}

int main( int argc, const char ** argv )
{
	game_base * mygame;
	time_t t;
	time( &t );
	srandom( t );
	parameters param( argc, argv );
	if ( !param.isOk() || param.getShowHelp() )
	{
		std::cout << argv[0] << ": Usage" << std::endl;
		param.showHelp( std::cout );
		std::cout << std::endl;
		return( !param.isOk() );
	}
	
	switch ( param.getSearchType() )
	{
		case parameters::search_old:
			mygame = new game_old();
			break;
		case parameters::search_simann:
			mygame = new game_simann();
			break;
		case parameters::search_mixed:
			mygame = new game_mixed();
			break;
		default:
			std::cerr << argv[0] << ": Unknown search engine specified" << std::endl;
			return( 1 );
	}
	if ( !mygame || !mygame->isOk() )
	{
		std::cerr << argv[0] << ": Error initializing search engine" << std::endl;
		return( 1 );
	}
	if ( param.getShouldLoadInitialState() )
	{
		int result = load_initial_state( *mygame, param.getLoadInitialStatePath() );
		if ( result )
		{
			delete mygame;
			std::cerr << argv[0] << ": Error loading initial state" << std::endl;
			return( 1 );
		}
    	mygame->dump_state( std::cout );
	}
	
//	std::cout << "Seeding" << std::endl;
	mygame->seed();
	
	mygame->dump_state( std::cout );
	if ( param.getShouldLoadInitialState() )
	{
		std::cout << "Press ENTER to start" << std::endl << std::flush;
		getchar();
	}	
	time( &t );
	int cost, round;
	round = 0;
	cost = mygame->calculate_cost();
	do 
	{
		cost = mygame->rotate( cost );
		round+=1;
		if ( ( round %10000 ) == 0 ) 
		{
			std::cout << "COST: round = " << round << ", cost = " << cost;
			mygame->dump_rotate_state( std::cout );
			std::cout << std::endl;
		}
		if ( ( round % 100000 ) == 0 ) 
		{
			mygame->dump_state( std::cout );
//			return( 1 );
		}
//		getchar();
	} while ( cost );
	time_t endt;
	time( &endt );
	mygame->dump_state( std::cout );
	std::cout << "Solution took " << difftime( endt, t ) << " seconds and " << round << " rounds at " << round/difftime( endt, t ) << " rounds/second" << std::endl;
	delete mygame;
	return 0;
}
