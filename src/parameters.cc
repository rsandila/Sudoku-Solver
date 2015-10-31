/***************************************************************************
 *            parameters.cc
 *
 *  Created on: Sat May 27 02:47:01 2006
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
 *///


#include "../include/parameters.h"

parameters::parameters( const int argc, const char ** argv )
{
	stype = search_old;
	hasInitialState = false;
	hasShowHelp = false;
	installed = parseParam( argc, argv );
}

parameters::~parameters()
{
	// nothing to do
}
	
bool parameters::getShouldLoadInitialState() const
{
	if ( !isOk() ) throw "Class not initialized";
	return( hasInitialState );
}

const std::string & parameters::getLoadInitialStatePath() const
{
	if ( !isOk() ) throw "Class not initialized";
	return( initialStatePath );
}
	
parameters::search_type parameters::getSearchType() const
{
	if ( !isOk() ) throw "Class not initialized";
	return( stype );
}

bool parameters::parseParam( const int argc, const char ** argv )
{ // called from constructor
	for ( int cnt = 1; cnt < argc; cnt++ )
	{	
		std::string work = argv[cnt];
		
		if ( work.find( "-i" ) != work.npos && argv[cnt+1] )
		{
			initialStatePath = argv[cnt+1];
			hasInitialState = true;
			cnt+=1;
			continue;
		}
		if ( work.find( "-h" ) != work.npos || work.find( "-?" ) != work.npos )
		{
			hasShowHelp = true;
			return( true ); // no point in continueing ... people want help
		}
		if ( work.find( "-s" ) != work.npos && argv[cnt+1] )
		{
			std::string sstype = argv[cnt+1];
			stype = search_notdefined;
			
			if ( sstype == "old" ) stype = search_old;
			if ( sstype == "simann" ) stype = search_simann;
			if ( sstype == "mixed" ) stype = search_mixed;
			if ( stype == search_notdefined )
			{ // unknown search type
				hasShowHelp = true;
				return( false );
			}
			cnt+=1;
			continue;
		}
		hasShowHelp = true;
		return( false ); // bad parameter
	}
	return( true );
}

bool parameters::getShowHelp() const
{ // no point in testing isOk... have to assume stuff is not okay when we get here
	return( hasShowHelp );
}

void parameters::showHelp( std::ostream & instream )
{
	instream << "\t-i filename - File to load initial state from" << std::endl;
	instream << "\t-h/-? - Show help" << std::endl;
	instream << "\t-s type - Search type, can be \"old\", \"mixed\" or \"simann\"" << std::endl;
}
