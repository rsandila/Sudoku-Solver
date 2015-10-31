/***************************************************************************
 *            game_mixed.cc
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
 #include "../include/game_mixed.h"
 
game_mixed::game_mixed()
{
	stype = parameters::search_old;
}
 
int game_mixed::rotate( int initial_cost )
{
	int result;

	switch ( stype )
	{
		case parameters::search_simann:
			result = simann.rotate( initial_cost );
			break;
		case parameters::search_old:
			result = old.rotate( initial_cost );
			if ( result < 40 )
			{
				stype = parameters::search_simann;
				simann.copy( old );
				simann.setStartTemperature( 3.0 );
				simann.setBounceTemperature( 2.5 );
			}
			break;
		default:
			throw "Invalid state for game_mixed";			
	};
	return( result );
}
 
void game_mixed::dump_rotate_state( std::ostream & ostr ) const
{
	switch ( stype )
	{
		case parameters::search_simann:
			simann.dump_rotate_state( ostr );
			break;
		case parameters::search_old:
			old.dump_rotate_state( ostr );
			break;
		default:
			throw "Invalid state for game_mixed";			
	};
}

void game_mixed::setFixedVal( int bx, int by, int x, int y, int val )
{
	switch ( stype )
	{
		case parameters::search_simann:
			simann.setFixedVal( bx, by, x, y, val );
			break;
		case parameters::search_old:
			old.setFixedVal( bx, by, x, y, val );
			break;
		default:
			throw "Invalid state for game_mixed";			
	};
}

void game_mixed::seed()
{
	switch ( stype )
	{
		case parameters::search_simann:
			simann.seed();
			break;
		case parameters::search_old:
			old.seed();
			break;
		default:
			throw "Invalid state for game_mixed";			
	};
}

void game_mixed::dump_state( std::ostream& ostr )
{
	switch ( stype )
	{
		case parameters::search_simann:
			simann.dump_state( ostr );
			break;
		case parameters::search_old:
			old.dump_state( ostr );
			break;
		default:
			throw "Invalid state for game_mixed";			
	};
}

int game_mixed::calculate_cost()
{
	switch ( stype )
	{
		case parameters::search_simann:
			return( simann.calculate_cost() );
		case parameters::search_old:
			return( old.calculate_cost() );
		default:
			throw "Invalid state for game_mixed";			
	};
}
