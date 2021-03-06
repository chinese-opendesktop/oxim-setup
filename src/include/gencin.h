/*
    Copyright (C) 1999 by  XCIN TEAM

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/      

#ifndef _GENCIN_H
#define _GENCIN_H

#include <stdlib.h>
#include "module.h"

#define GENCIN_VERSION  "20040102"
/* Size of module ID in .tab file. */
#define MODULE_ID_SIZE		20
typedef struct
{
    char prefix[7]; /* Always "gencin\0" */
    unsigned char version;
    char dummy[12];
} table_prefix_t;


/* For input-code char definition. */
typedef unsigned int	icode_t;
typedef unsigned int	ichar_t;

/* if ichar_t & WORD_MASK == true, the ichar_t is offset */
#define WORD_MASK	(1L << 31)

#define VERLEN			20	/* Version buffer size */
#define ENCLEN			15	/* Encoding name buffer size */
#define CIN_ENAME_LENGTH	20      /* English name buffer size */
#define CIN_CNAME_LENGTH	20      /* Chinese name buffer size */

#define ICODE_MODE1		1	/* one icode & one icode_idx */
#define ICODE_MODE2		2	/* two icode & one icode_idx */

#define  INP_CODE_LENGTH        10	/* max # of keys in a keystroke */
#define  END_KEY_LENGTH         10      /* max # of end keys */


/* Tab file header for general cin */
typedef struct {
    char version[VERLEN];		/* version number. */
    char encoding[ENCLEN];		/* table encoding. */
    char ename[CIN_ENAME_LENGTH];	/* English name. */
    char cname[CIN_CNAME_LENGTH];	/* Chinese name. */

    uch_t keyname[N_KEYCODE];		/* key name define. */
    char selkey[SELECT_KEY_LENGTH + 1];	/* select keys. */
    char endkey[END_KEY_LENGTH + 1];	/* end keys. */

    union
    {
	unsigned int n_ichar;		/* # of total chars. */
	unsigned int n_word;
    };
    unsigned int n_icode;		/* # of total keystroke code */
    unsigned char n_keyname;		/* # of keyname needed. */
    unsigned char n_selkey;		/* # of select keys. */
    unsigned char n_endkey;		/* # of end keys. */
    unsigned char n_max_keystroke;	/* max # of keystroke for each char */
    char icode_mode;
} cintab_head_t;
 

/* Table version 1*/

#define AutoCompose	  "AutoCompose"
#define AutoUpChar	  "AutoUpChar"
#define AutoFullUp	  "AutoFullUp"
#define SpaceAutoUp	  "SpaceAutoUp"
#define SelectKeyShift	  "SelectKeyShift"
#define SpaceIgnore	  "SpaceIgnore"
#define SpaceReset	  "SpaceReset"
#define WildEnable	  "WildEnable"
#define EndKey		  "EndKey"
#define DisableSelectList "DisableSelectList"

#define N_KEYS 128	/* ???????????? */
#define N_LOCALE_LENGTH 16  /* ???????????????????????? */
#define N_NAME_LENGTH	256 /* ??????????????????????????? */

#define N_SETTING_NAME_LENGTH	64 /* ???????????? */
#define N_SETTING_VALUE_LENGTH	128 /* ???????????? */
typedef struct
{
    unsigned int n_locale;  /* ????????????????????????????????? */
    unsigned int locale_table_offset;

    unsigned int n_setting; /* ???????????????????????????????????? */
    unsigned int setting_table_offset;

    unsigned int n_input_content; /* ???????????????????????? */
    unsigned int offset_table_offset;

    unsigned int n_char;	/* ???????????????(UCS4) */
    unsigned int char_offset;

    unsigned int input_content_offset;

    unsigned char n_max_keystroke; /* ????????????????????? */
    unsigned char keep_key_case; /* ????????????????????? */

    char orig_name[N_NAME_LENGTH]; /* English Name */
    char cname[N_NAME_LENGTH]; /* ????????????(??????????????? cin ??????) */

    unsigned char n_key_name; /* ???????????? */
    uch_t keyname[N_KEYS]; /* ?????????, ??????????????? */

    unsigned char n_selection_key; /* ??????????????? */
    char selection_keys[N_KEYS];  /* ?????????????????? */

    unsigned char n_end_key; /* ??????????????? */
    char end_keys[N_KEYS]; /* ????????? */
    unsigned int chksum;
} cintab_head_v1_t;

typedef struct
{
    char locale[N_LOCALE_LENGTH]; /* ?????????????????? */
    char name[N_NAME_LENGTH];	  /* ???????????? */
} cintab_locale_table;

typedef struct
{
    char key[N_SETTING_NAME_LENGTH];    /* ?????????????????? */
    char value[N_SETTING_VALUE_LENGTH]; /* ???????????? */
} cintab_setting_table;

typedef struct
{
    unsigned int ucs4;   /* UCS4 ?????? */
    unsigned int offset; /* ????????????????????????????????? */
} cintab_char_index;

typedef struct
{
    unsigned char n_keystroke;  /* ???????????? */
    char *keystroke;
    unsigned char n_char;	/* ????????? */
    unsigned int *content; /* ?????????UCS4 */
} cintab_input_content;
#endif
