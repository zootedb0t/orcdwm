/* appearance */

/* border pixel of windows */
static const unsigned int borderpx = 0;

/* horiz inner gap between windows */
static const unsigned int gappih = 20;

 /* vert inner gap between windows */
static const unsigned int gappiv = 10;

/* horiz outer gap between windows and screen edge */
static const unsigned int gappoh = 10;

/* vert outer gap between windows and screen edge */
static const unsigned int gappov = 30;

/* 1 means no outer gap when there is only one window */
static int smartgaps = 0;

/* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systraypinning = 0;

/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayonleft = 0;

/* systray spacing */
static const unsigned int systrayspacing = 3;

/* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int systraypinningfailfirst = 1;

/* 0 means no systray */
static const int showsystray = 1;

/* 0 means no bar */
static const int showbar = 1;

/* 0 means bottom bar */
static const int topbar = 1;

static const int horizpadbar = 10;        /* horizontal padding for statusbar */
static const int vertpadbar = 10;        /* vertical padding for statusbar */

/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes {
  showtab_never,
  showtab_auto,
  showtab_nmodes,
  showtab_always
};
static const int showtab = showtab_auto; /* Default tab bar show mode */
static const int toptab = False;         /* False means bottom tab bar */

static const Bool viewontag = True; /* Switch view on tag switch */
/* 0 master (default), 1 = above, 2 = aside, 3 = below, 4 = bottom */
static const int attachmode = 3;
static const char *fonts[] = {"Monofur Nerd Font:style:Book:size=9",
                              "Material Design Icons Desktop:size=9", "JoyPixels:size:9"};
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

/* tagging */
static char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
/* xprop(1):
 * WM_CLASS(STRING) = instance, class
 * WM_NAME(STRING) = title
*/
    /* class      instance    title       tags mask     iscentered   isfloating   monitor */
    {"firefox-nightly", "Toolkit", NULL, 0, 1, 1, -1},
    {"firefox-nightly", "Browser", NULL, 0, 1, 1, -1},
    {"mpv", "gl", NULL, 0, 1, 1, -1},
    {"firefox-nightly", "Places", NULL, 0, 1, 1, -1},
    {"Virt-manager", "virt-manager", NULL, 1 << 8, 1, 1, -1},
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 1; /* 1 means respect size hints in tiled resizals */
// static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen
// window */

#define FORCE_VSPLIT 1 /* nrowgrid layout: force two clients to always split vertically */
/* various layouts to use on the config */
#include "vanitygaps.c"

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=", tile}, /* first entry is default */
  { "[M]", monocle},
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "D[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */
// static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in
// spawn() */ static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon,
// "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_dark, "-sf",
// col_gray4, NULL };
static const char *termcmd[] = {"st", NULL};

#include "movestack.c"
static const Key keys[] = {
  /* modifier                     key        function        argument */
  // Show/hide bar
  {MODKEY, XK_b, togglebar, {0}},
  {MODKEY, XK_w, tabmode, {-1}},

  // Master Stack motion
  {MODKEY, XK_j, focusstack, {.i = +1}},
  {MODKEY, XK_k, focusstack, {.i = -1}},
  {MODKEY, XK_i, incnmaster, {.i = +1}},
  {MODKEY, XK_d, incnmaster, {.i = -1}},
  {MODKEY | ShiftMask, XK_h, setmfact, {.f = -0.05}},
  {MODKEY | ShiftMask, XK_l, setmfact, {.f = +0.05}},
	{ MODKEY,                       XK_backslash,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_backslash,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
  {MODKEY | ShiftMask, XK_j, movestack, {.i = +1}},
  {MODKEY | ShiftMask, XK_k, movestack, {.i = -1}},
  {MODKEY, XK_Return, zoom, {0}},
  // Reset window size
  {Mod1Mask, XK_0, reset_mfact, {0}},

  // Gaps
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
  
  // clients
  {MODKEY, XK_grave, view, {0}},
  {MODKEY, XK_x, killclient, {0}},
  { MODKEY|ShiftMask, XK_x, killunsel, {0} },

  // Layouts
  {MODKEY | ControlMask, XK_t, setlayout, {.v = &layouts[0]}},
  {MODKEY | ControlMask, XK_m, setlayout, {.v = &layouts[1]}},
  {MODKEY | ControlMask, XK_b, setlayout, {.v = &layouts[2]}},
  {MODKEY | ControlMask, XK_n, setlayout, {.v = &layouts[3]}},
  {MODKEY | ControlMask, XK_g, setlayout, {.v = &layouts[4]}},
  {MODKEY | ControlMask, XK_c, setlayout, {.v = &layouts[5]}},
  {Mod1Mask, XK_Tab, cyclelayout, {.i = +1}},
  {Mod1Mask | ShiftMask, XK_Tab, cyclelayout, {.i = -1}},

  // Switch to last layout
  {MODKEY, XK_space, setlayout, {0}},

  // floating and fullscreen
  {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
  {MODKEY | ControlMask, XK_Down, moveresize, {.v = "0x 25y 0w 0h"}},
  {MODKEY | ControlMask, XK_Up, moveresize, {.v = "0x -25y 0w 0h"}},
  {MODKEY | ControlMask, XK_Right, moveresize, {.v = "25x 0y 0w 0h"}},
  {MODKEY | ControlMask, XK_Left, moveresize, {.v = "-25x 0y 0w 0h"}},
  {MODKEY | ControlMask | ShiftMask,
     XK_Down,
     moveresize,
     {.v = "0x 0y 0w 25h"}},
    {MODKEY | ControlMask | ShiftMask,
     XK_Up,
     moveresize,
     {.v = "0x 0y 0w -25h"}},
    {MODKEY | ControlMask | ShiftMask,
     XK_Right,
     moveresize,
     {.v = "0x 0y 25w 0h"}},
    {MODKEY | ControlMask | ShiftMask,
     XK_Left,
     moveresize,
     {.v = "0x 0y -25w 0h"}},
    {MODKEY, XK_f, togglefullscreen, {0}},
    {MODKEY | ShiftMask, XK_f, togglefakefullscreen, {0}},
    // Maximize window vertically
    // {MODKEY, XK_v, toggleverticalmax, {0}},
    // Sticky window
    {MODKEY, XK_s, togglesticky, {0}},
    // Tags
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_r, reorganizetags, {0}},
    {MODKEY | ShiftMask, XK_d, distributetags, {0}},
    // xrdb
    {MODKEY, XK_F5, xrdb, {.v = NULL}},
    // scratchpad
    {MODKEY, XK_minus, scratchpad_show, {0}},
    {MODKEY | ShiftMask, XK_minus, scratchpad_hide, {0}},
    {MODKEY, XK_equal, scratchpad_remove, {0}},
    // Quit dwm
    {MODKEY | ShiftMask, XK_q, quit, {0}},
    // Tagkeys
    TAGKEYS(XK_1, 0)
    TAGKEYS(XK_2, 1)
    TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4)
    TAGKEYS(XK_6, 5)
    TAGKEYS(XK_7, 6)
    TAGKEYS(XK_8, 7)
    TAGKEYS(XK_9, 8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function argument */
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
    {ClkTabBar, 0, Button1, focuswin, {0}},
};
