/***************************************************************************
 *            game_simann.h
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
 
#ifndef _GAME_SIMANN_H
#define _GAME_SIMANN_H

#include "game_base.h"

//#define USE_SIM_ANEALING

class game_simann: public game_base
{
public:
	game_simann();

	int rotate( int initial_cost );
	virtual void dump_rotate_state( std::ostream & ostr ) const;
    virtual bool setStartTemperature( float start );
	virtual bool setMinTempertature( float min );
	virtual bool setBounceTemperature( float bounce );
	virtual bool setAlphaTemperature( float alphat );
	virtual bool setBetaTemperature( float betat );
	virtual bool setAlphaLimit( int alimit );
	virtual bool setBetaLimit( int blimit );
protected:
	float temperature;
	float min_temp;
	float bounce_limit;
	float beta;
	float alpha;
	int beta_limit;
    int alpha_limit;
    int temp_rounds;
};

#endif /* _GAME_SIMANN_H */
