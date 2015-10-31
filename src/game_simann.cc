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
 #include "../include/game_simann.h"
 
 game_simann::game_simann()
 {
	min_temp = 1.0;
	bounce_limit = 2.0;
	beta = 1.1;
	alpha = 0.99;
	beta_limit = 2000;
    alpha_limit = 1000;

    temperature = 50.0;
	temp_rounds = 0;
 }
 
int game_simann::rotate(  int initial_cost  )
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

	 bool useNew = false;
	 float delta = initial_cost - new_cost;
	 
	 if ( delta > 0 ) 
	 {
		 useNew = true;
	 }
	 else
	 {
		 float test = (float)rand()/(float)RAND_MAX;
		 float calc = exp( 20*(delta+0.1)/temperature );
		 
		 if ( calc > test )
		 {
			 useNew = true;
//			 std::cout << "new_cost " << new_cost << " initial_cost " << initial_cost << " test = " << test << " delta = " << delta << " calc = " << calc << " temperature = " << temperature << std::endl;
		 }
	 }
	 
	 if ( !useNew )
	 {
		 blocks[ tx ][ ty ] = storage;
		 new_cost = initial_cost;
		 notchanged+=1;
	 }
	 else
	 {
		 notchanged = 0;
	 }
  	 temp_rounds += 1;
	 if ( temp_rounds > alpha_limit && temperature > min_temp )
	 {
		temp_rounds = 0;
	 	temperature *= alpha;
	 }
	 if ( notchanged > beta_limit )
	 {
		 if ( temperature < bounce_limit ) temperature *= beta;
		 notchanged = 0;
	 }
	 if ( temperature == 0 ) temperature += 1;
	 return( new_cost );
 }

void game_simann::dump_rotate_state( std::ostream & ostr ) const
{
	ostr << " temperature = " << temperature << " notchanged = " << notchanged;
}

bool game_simann::setStartTemperature( float start )
{
	if ( !isOk() ) return( false );
	if ( start < min_temp || start < bounce_limit ) return( false );
	temperature = start;
	return( true );
}

bool game_simann::setMinTempertature( float min )
{
	if ( !isOk() ) return( false );
	if ( min > bounce_limit || min > temperature || min < 0 ) return( false );
	min_temp = min;
	return( true );	
}

bool game_simann::setBounceTemperature( float bounce )
{
	if ( !isOk() ) return( false );
	if ( bounce < min_temp ) return( false );
	bounce_limit = bounce;
	return( true );
}

bool game_simann::setAlphaTemperature( float alphat )
{
	if ( !isOk() ) return( false );
	if ( alphat <= 0 ) return( false );
	alpha = alphat;
	return( true );	
}

bool game_simann::setBetaTemperature( float betat )
{
	if ( !isOk() ) return( false );
	if ( betat <= 0 ) return( false );
	beta = betat;
	return( true );
}

bool game_simann::setAlphaLimit( int alimit )
{
	if ( !isOk() ) return( false );
	if ( alimit <= 0 ) return( false );
	alpha_limit = alimit;
	return( true );
}

bool game_simann::setBetaLimit( int blimit )
{
	if ( !isOk() ) return( false );
	if ( blimit <= 0 ) return( false );
	beta_limit = blimit;
	return( true );
}
