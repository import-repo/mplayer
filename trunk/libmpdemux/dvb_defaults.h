/* dvb_defaults.h

   Provided by Tomi Ollila

   Copyright (C) Dave Chapman 2002

   Modified for use with MPlayer, for details see the changelog at
   http://svn.mplayerhq.hu/mplayer/trunk/
   $Id$

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
   Or, point your browser to http://www.gnu.org/copyleft/gpl.html

*/

#ifndef _DVB_DEFAULTS_H
#define _DVB_DEFAULTS_H

/* DVB-S */

// With a diseqc system you may need different values per LNB.  I hope
// no-one ever asks for that :-)

#define SLOF (11700*1000UL)
#define LOF1 (9750*1000UL)
#define LOF2 (10600*1000UL)

#endif
