/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka Term:pixelsize=14:antialias=true:autohint=true" };
static const char dmenufont[]       = "Iosevka Term:pixelsize=14:antialias=true:autohint=true";

static const char col_base00[]	    = "#282c34";
static const char col_base01[]	    = "#353b45";
static const char col_base02[]	    = "#3e4451";
static const char col_base03[]	    = "#545862";
static const char col_base04[]	    = "#565c64";
static const char col_base05[]	    = "#abb2bf";
static const char col_base06[]	    = "#b6bdca";
static const char col_base07[]	    = "#c8ccd4";
static const char col_base08[]	    = "#e06c75";
static const char col_base09[]	    = "#d19a66";
static const char col_base0A[]	    = "#e5c07b";
static const char col_base0B[]	    = "#98c379";
static const char col_base0C[]	    = "#56b6c2";
static const char col_base0D[]	    = "#61afef";
static const char col_base0E[]	    = "#c678dd";
static const char col_base0F[]	    = "#be5046";

static const char *colors[][3]	    = {
	/*               fg          bg          border   */
	[SchemeNorm] = { col_base05, col_base00, col_base00 },
	[SchemeSel]  = { col_base05, col_base02, col_base02 },
};

/* scratchpad */
static const char scratchpadname[] = "spterm";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class		  instance    title       tags mask     isfloating   monitor */
	{ "qutebrowser",	  NULL,       NULL,       1 << 0,       0,           -1 },
	{ "Spotify",		  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "TelegramDesktop",      NULL,       NULL,       1 << 7,       0,           -1 },
	{ "Signal",	          NULL,       NULL,       1 << 7,       0,           -1 },
	{ "discord",		  NULL,       NULL,       1 << 7,       0,           -1 },
	{ "Thunderbird",	  NULL,       NULL,       1 << 6,       0,           -1 },
	{ NULL,			  NULL,       "WhatsApp", 1 << 7,       0,           -1 },
	{ NULL,			  NULL,       "DISPATCH", 1 << 2,       0,           -1 },
	{ NULL,			  "spterm",   NULL,       1 << 10,	1,	     -1 },
	{ NULL,			  NULL,	      "flterm",   1 << 10,	1,	     -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_base00, "-nf", col_base05, "-sb", col_base02, "-sf", col_base05, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *fltermcmd[] = { "st", "-t", "flterm", "-g", "120x34", NULL };
static const char *browsercmd[]  = { "qutebrowser", NULL };
static const char *musiccmd[]  = { "spotify", NULL };
static const char *lockcmd[]  = { "slock", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,         	XK_Return, spawn,          {.v = fltermcmd } },
	{ MODKEY|ShiftMask,        	XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,        	XK_s,      spawn,          {.v = musiccmd } },
	{ MODKEY|ShiftMask,        	XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,        	XK_space,  togglescratch,  {.v = scratchpadcmd } },

	{ MODKEY|ShiftMask,      	XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             		XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
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
