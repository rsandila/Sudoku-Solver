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

#define BLOCKSIZE  (7)

class block3x3
{
public:
	block3x3();
	virtual ~block3x3();
	bool isOk() { return( installed ); };
	
	int val( int x, int y );
	void setFixedVal( int x, int y, int val );
	inline void rotate()
	{
		int x1, y1, x2, y2;
		int temp;
		
		do
		{
			x1 = random() % BLOCKSIZE;
			y1 = random() % BLOCKSIZE;
		} while ( used[ x1 * BLOCKSIZE + y1 ] );
		do
		{
			x2 = random() % BLOCKSIZE;
			y2 = random() % BLOCKSIZE;
		} while ( ( x1 == x2 && y1 == y2 ) || used[ x2 * BLOCKSIZE + y2 ] );
		
		temp = block[ x1 ][ y1 ];
		block[ x1 ][ y1 ] = block[ x2 ][ y2 ];
		block[ x2 ][ y2 ] = temp;	
	}
	void seed();
protected:
	int block[BLOCKSIZE][BLOCKSIZE];
	bool used[BLOCKSIZE*BLOCKSIZE];
	bool fixed[BLOCKSIZE*BLOCKSIZE];
private:
	bool installed;
};

#endif /* _BLOCK3X3_H */
