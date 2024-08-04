/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=8", "JoyPixels:pixelsize=8:antialias=true:autohint=true"};
static const char dmenufont[]       = "JetBrains Mono:size=9";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "TelegramDesktop",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "obs",                NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Lutris",             NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "firefox",   		NULL,     NULL,           1 << 2,    0,          0,          -1,        -1 },
	{ "St",                 NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,                 NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachbelow = 1;    /* 1 means attach after the currently active window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_q,     ACTION##stack, {.i = 0 } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *termcmd[]  = { "st", NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *kittycmd[] = { "kitty", NULL };


#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_period,      setmfact,       {.f = +0.05} },
	/* { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },*/
	/*{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },*/
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_comma,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_g,      togglebar,      {0} },
	{ MODKEY,                       XK_f,	   zoom,           {0} },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_s,      incnmaster,     {.i = +1 } },
	{ MODKEY,		                    XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_t,  	   togglefloating, {0} },
	{ MODKEY,                       XK_space,  	   setlayout,      {0} },
	{ MODKEY,                       XK_p,      spawn,          {.v = roficmd } },
	{ MODKEY,                 			XK_Return,                   spawn,          {.v = kittycmd } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_h,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_l, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l, tagmon,         {.i = +1 } },
	{ MODKEY,			XK_minus,  setgaps,	   {.i = -1 } },
	{ MODKEY,			XK_equal,  setgaps,	   {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_equal,  setgaps,	   {.i =  0 } },
	{ MODKEY,                       XK_F5,     xrdb,           {.v = NULL } },
  { MODKEY,                       XK_Right,  shiftview,      {.i = +1 } },
  { MODKEY,                       XK_Left,   shiftview,      {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,		XK_BackSpace,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

