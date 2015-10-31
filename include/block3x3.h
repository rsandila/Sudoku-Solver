/***************************************************************************
 *            block3x3.h
 *
 *  Sat Aug  6 08:28:32 2005
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
 
#ifndef _BLOCK3X3_H
#define _BLOCK3X3_H

class block3x3
{
public:
	block3x3();
	virtual ~block3x3();
	bool isOk() { return( installed ); };
	
	int val( int x, int y );
	void setFixedVal( int x, int y, int val );
	void rotate();
protected:
	int block[3][3];
	bool used[9];
	bool fixed[9];
private:
	bool installed;
};

#endif /* _BLOCK3X3_H */
