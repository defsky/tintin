/******************************************************************************
*   TinTin++                                                                  *
*   Copyright (C) 2004 (See CREDITS file)                                     *
*                                                                             *
*   This program is protected under the GNU GPL (See COPYING)                 *
*                                                                             *
*   This program is free software; you can redistribute it and/or modify      *
*   it under the terms of the GNU General Public License as published by      *
*   the Free Software Foundation; either version 2 of the License, or         *
*   (at your option) any later version.                                       *
*                                                                             *
*   This program is distributed in the hope that it will be useful,           *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
*   GNU General Public License for more details.                              *
*                                                                             *
*   You should have received a copy of the GNU General Public License         *
*   along with this program; if not, write to the Free Software               *
*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA *
******************************************************************************/

/******************************************************************************
*                (T)he K(I)cki(N) (T)ickin D(I)kumud Clie(N)t                 *
*                                                                             *
*                      coded by Igor van den Hoven 2009                       *
******************************************************************************/

#include "tintin.h"

struct advertisement_type
{
	time_t                  start;
	time_t                  end;
	char                  * desc;
};

struct advertisement_type advertisement_table[] =
{
	{
		1260469590, /* 10 Dec 2009 */
		1323541590, /* 10 Dec 2011 */
		"\n"
		"<138>                                  Lowlands\n"
		"\n"
		"<078>Lowlands is an old school severely customized Merc derived Hack and Slash MUD\n"
		"<078>with an emphasis on exploration and solving challenging and immersive area\n"
		"<078>based quests.\n"
		"\n"
		"<078>A voluntary two faction player killing system is in place for the followers of\n"
		"<078>the two gods, Chaos and Order, combined with easy corpse retrieval, no corpse\n"
		"<078>looting, and a large 15,000 room world.\n"
		"\n"
		"<178>To connect to Lowlands enter: #session lo slackhalla.org 6969\n"
		"\n"
	},

	{
		1260469590, /* 10 Dec 2009 */
		1323541590, /* 10 Dec 2011 */
		"\n"
		"<138>                Maiden Desmodus  -  http://maidendesmodus.com\n"
		"\n"
		"<078>Maiden Desmodus is an immersive world of high adventure where your actions, or\n"
		"<078>inaction, will determine the fate of The Isle. Choose to be born unto one of\n"
		"<078>two opposing factions, join one of the six powerful guilds, and carve your\n"
		"<078>place in history through your cunning, your strategy, and your skill with magic\n"
		"<078>or a blade. At every turn are players who may ally themselves to you, or work\n"
		"<078>to destroy you. Shall you form your own cabal and command your peers, control\n"
		"<078>the politics of your city, or lead an army against those who oppose you?\n"
		"<078>Maiden Desmodus features a completely original world and a custom game engine.\n"
		"\n"
		"<178>To connect to Maiden Desmodus enter: #session md maidendesmodus.com 4000\n"
		"\n"
	},

	{
		1260469590, /* 10 Dec 2009 */
		1323541590, /* 10 Dec 2011 */
		"\n"
		"<138>                     Lost Souls  -  http://lostsouls.org\n"
		"\n"
		"<078>\"Our world is fallen, boy.  Aedaris is a ruin.  My grandfather, he told me\n"
		"<078>of days, not so long gone, when everything you see was part of a great empire.\n"
		"<078>Peaceful, he said.  Full of wonders.  They called it eternal.  Funny, eh, boy?\n"
		"<078>They thought it'd last forever, and it went crazy and tore itself apart.  But\n"
		"<078>they left behind a few things for us, didn't they?  Ha!  Yes, lots for us.  Now\n"
		"<078>give that wizard-stick here before you blow your fool horns off, and get to\n"
		"<078>work.  Daylight's soon, and these faeries aren't going to skin themselves.\"\n"
		"<078>Lost Souls: chaos in the wreckage of empire.  Be clever if you want to live.\n"
		"\n"
                "<178>To connect to Lost Souls enter: #session ls lostsouls.org 23\n"
                "\n"
		                
	},

	{
		1260469590, /* 10 Dec 2009 */
		1323541590, /* 10 Dec 2011 */
		"\n"
		"<138>                   Alter Aeon  -  http://www.alteraeon.com\n"
		"\n"
		"<078>Alter Aeon is a custom MUD written entirely from scratch. The story setting\n"
		"<078>is reminiscent of Dungeons and Dragons, but has elements of fantasy and a\n"
		"<078>unique spell and skill system.  Our world has hundreds of areas to explore,\n"
		"<078>quests to complete, and puzzles to solve.  There are always other players\n"
		"<078>available, whether for help, competition, or just to talk with.  The game\n"
		"<078>is also blind-friendly and has a blind player login on port 3010.\n"
		"\n"
		"<178>To connect to Alter Aeon enter: #session aa alteraeon.com 3002\n"
		"\n"
	},

	{
		0,
		0,
		""
	}
};

int valid_advertisement(int i)
{
	time_t current_time = time(NULL);

	if (advertisement_table[i].start > current_time)
	{
		return FALSE;
	}
	if (advertisement_table[i].end < current_time)
	{
		return FALSE;
	}
	return TRUE;
}

int total_advertisements()
{
	int i, count = 0;

	for (i = 0 ; *advertisement_table[i].desc ; i++)
	{
		count += valid_advertisement(i);
	}
	return count;
}

DO_COMMAND(do_advertise)
{
	int max, cnt;
	char buf[BUFFER_SIZE];

	max = total_advertisements();

	for (cnt = 0 ; *advertisement_table[cnt].desc ; cnt++)
	{
		if (!valid_advertisement(cnt))
		{
			continue;
		}

		if (lrand48() % max == 0)
		{
			char *pto, *ptf;

			substitute(ses, advertisement_table[cnt].desc, buf, SUB_COL);

			pto = buf;

			while (*pto)
			{
				ptf = strchr(pto, '\n');

				if (ptf == NULL)
				{
					break;
				}
				*ptf++ = 0;

				tintin_puts(ses, pto);

				pto = ptf;
			}
			break;
		}

		max--;
	}

//	tintin_printf2(ses, "#NO SESSION ACTIVE. USE: %csession {name} {host} {port} TO START ONE.", gtd->tintin_char);

	return ses;
}
