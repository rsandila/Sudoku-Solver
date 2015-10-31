/***************************************************************************
 *            parameters.h
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
 */
#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include <ostream>
#include <string>

class parameters
{
	public:
		typedef enum { search_notdefined, search_old, search_simann, search_mixed } search_type;
		
		parameters( const int argc, const char ** argv );
		virtual ~parameters();
		virtual bool isOk() const { return( installed ); };
		
		bool getShouldLoadInitialState() const;
		const std::string & getLoadInitialStatePath() const;
	
		search_type getSearchType() const;
		
		bool getShowHelp() const;		
		void showHelp( std::ostream & instream );
	protected:
		bool parseParam( const int argc, const char ** argv );

		bool installed;
		bool hasInitialState;
		bool hasShowHelp;
		std::string initialStatePath;
		search_type stype;	
};


#endif	//_PARAMETERS_H_
