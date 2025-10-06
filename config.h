
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
//static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
//static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
//static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
//static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const unsigned int gappih    = 0;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 0;       /* vert inner gap between windows */
static const unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int user_bh            = 10;        /* 2 is the default spacing around the bar's font */
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;     /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "JetBrains Mono Nerd Font:size=10" };
static const char dmenufont[]       = "JetBrains Mono Nerd Font:size=10";

static char col_base00[]      = "#222222";
static char col_base01[]      = "#444444";
static char col_base02[]      = "#bbbbbb";
static char col_base03[]      = "#bbbbbb";
static char col_base04[]      = "#eeeeee";
static char col_base05[]      = "#eeeeee";
static char col_base06[]      = "#eeeeee";
static char col_base07[]      = "#eeeeee";
static char col_base08[]      = "#eeeeee";
static char col_base09[]      = "#eeeeee";
static char col_base10[]      = "#eeeeee";
static char col_base11[]      = "#eeeeee";
static char col_base12[]      = "#eeeeee";
static char col_base13[]      = "#eeeeee";
static char col_base14[]      = "#eeeeee";
static char col_base15[]      = "#eeeeee";

static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       //[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       //[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
       [SchemeNorm] = { col_base07, col_base00, col_base00 },
       [SchemeSel]  = { col_base07, col_base09, col_base09 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle }, // really nice
	{ "[@]",      spiral },
	{ "[\\]",     dwindle }, // same as spiral
	{ "H[]",      deck }, // tabbed on right, master normal
	{ "TTT",      bstack },
	{ "===",      bstackhoriz }, // bad
	{ "HHH",      grid },
	{ "###",      nrowgrid }, 
	{ "---",      horizgrid }, // best grid
	{ ":::",      gaplessgrid }, // pointless
	{ "|M|",      centeredmaster }, // not that useful
	{ ">M>",      centeredfloatingmaster }, // just no
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
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

// Programs
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_base00, "-nf", col_base07, "-sb", col_base09, "-sf", col_base07, NULL };
static const char *dmenuswitchcmd[] = {"dwmswitch", NULL};
static const char *dmenusyscmd[] = {"dwmsys", NULL};
static const char *dmenuvpncmd[] = {"dwmvpn", NULL};
static const char *dmenutimercmd[] = {"dwmtimer", NULL};

static const char *termcmd[]  = { "alacritty", NULL };
static const char *browsercmd[]  = { "librewolf", NULL };
static const char *screenshotcmd[]  = { "flameshot", "gui", NULL };
static const char *pdfcmd[]  = { "sioyek", "--new-window", NULL };
static const char *notescmd[] = { "obsidian", NULL };
static const char *pavucontrolcmd[] = {"pavucontrol", NULL};
static const char *darktablecmd[] = {"darktable", NULL};

static const char *notifhist[] = {"dunstctl", "history-pop", NULL};
static const char *notifclear[] = {"dunstctl", "close-all", NULL};

// Startup programs
static const char *nmappletcmd[]  = { "nm-applet", NULL };
static const char *bluemanappletcmd[]  = { "blueman-applet", NULL };
static const char *dwmblockscmd[]  = { "dwmblocks", NULL };
static const char *volumereset[] = { "pamixer", "--set-volume", "0", NULL };
static const char *dwmblocksvolume[] = { "pkill", "-RTMIN+10", "dwmblocks", NULL };
static const char *dwmblocksmaster[] = { "pkill", "-RTMIN+11", "dwmblocks", NULL };
static const char *signaldesktop[] = { "signal-desktop", "--start-in-tray", NULL };
static const char **startup_programs[] = {
    nmappletcmd,
    bluemanappletcmd,
    dwmblockscmd,
    dwmblocksvolume,
    dwmblocksmaster,
    volumereset,
    signaldesktop
};

#include <X11/XF86keysym.h>

static const Key keys[] = {
	/* modifier                     key        function        argument */

    // Media and control
	{ 0,                    XF86XK_MonBrightnessUp,    spawn,          SHCMD("brightnessctl set 10%+") },
	{ 0,                    XF86XK_MonBrightnessDown,  spawn,          SHCMD("brightnessctl set 10%-")},
	{ 0,                    XF86XK_AudioRaiseVolume,   spawn,          SHCMD("pamixer -i 5 && pkill -RTMIN+10 dwmblocks") },
	{ 0,                    XF86XK_AudioLowerVolume,   spawn,          SHCMD("pamixer -d 5 && pkill -RTMIN+10 dwmblocks") },
	{ 0,                    XF86XK_AudioMute,          spawn,          SHCMD("pamixer -t   && pkill -RTMIN+10 dwmblocks") },
	{ 0,                    XF86XK_AudioPlay,          spawn,          SHCMD("playerctl play-pause") },
	{ 0,                    XF86XK_AudioNext,          spawn,          SHCMD("playerctl next") },
	{ 0,                    XF86XK_AudioPrev,          spawn,          SHCMD("playerctl prev") },

    // Programs
    { MODKEY,               XK_v,                      spawn,          {.v = notifclear }},
    { MODKEY,               XK_z,                      spawn,          {.v = notifhist }},
    { MODKEY,               XK_c,                      spawn,          {.v = dmenuswitchcmd }},
	{ MODKEY,               XK_s,                      spawn,          {.v = pdfcmd } },
	{ MODKEY,               XK_p,                      spawn,          {.v = dmenusyscmd } },
	{ MODKEY,               XK_space,                  spawn,          {.v = dmenucmd } },
	{ MODKEY,               XK_w,                      spawn,          {.v = notescmd } },
	{ MODKEY,               XK_u,                      spawn,          {.v = dmenuvpncmd } },
	{ MODKEY,               XK_q,                      spawn,          {.v = dmenutimercmd } },
	{ MODKEY,               XK_Return,                 spawn,          {.v = termcmd } },
    { MODKEY,               XK_b,                      spawn,          {.v = browsercmd }},
    { MODKEY,               XK_r,                      spawn,          {.v = darktablecmd }},
    { MODKEY,               XK_a,                      spawn,          {.v = pavucontrolcmd }},
	{ MODKEY|ShiftMask,     XK_s,                      spawn,          {.v = screenshotcmd } },

    // Navigation and rearranging
	{ MODKEY,               XK_j,                      focusstackvis,  {.i = +1 } },
	{ MODKEY,               XK_k,                      focusstackvis,  {.i = -1 } },
	{ MODKEY,               XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY,               XK_d,                      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_Return,                 zoom,           {0} },
	{ MODKEY,               XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,               XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     XK_period,                 tagmon,         {.i = +1 } },

    // Resizing
	{ MODKEY,               XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,     XK_h,                      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,     XK_l,                      setcfact,       {.f = -0.25} },

    // Quick
	{ MODKEY,               XK_Tab,                    view,           {0} },

    // Choosing layouts
	{ MODKEY,               XK_t,                      setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY,               XK_m,                      setlayout,      {.v = &layouts[1]} }, // monocle
	{ MODKEY,               XK_g,                      setlayout,      {.v = &layouts[9]} }, // horizgrid
	{ MODKEY,               XK_x,                      setlayout,      {.v = &layouts[4]} }, // deck
	{ MODKEY,               XK_f,                      togglefullscr,  {0} },

	{ MODKEY,               XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,                      tag,            {.ui = ~0 } },

    // Tags
	TAGKEYS(                XK_1,                                      0)
	TAGKEYS(                XK_2,                                      1)
	TAGKEYS(                XK_3,                                      2)
	TAGKEYS(                XK_4,                                      3)
	TAGKEYS(                XK_5,                                      4)
	TAGKEYS(                XK_6,                                      5)
	TAGKEYS(                XK_7,                                      6)
	TAGKEYS(                XK_8,                                      7)
	TAGKEYS(                XK_9,                                      8)

	{ MODKEY|ShiftMask,     XK_q,                      killclient,     {0} },
	{ MODKEY|ShiftMask,     XK_p,                      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,      {.i = +1} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },

	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

