struct library_link
{
    const char *link;
    const char *text;
};

struct library_group
{
    const char *title;
    const struct library_link *links;
    int count;
};


const struct library_link links_software[] = {
    { "https://strlen.com/treesheets/", "TreeSheets - organize like excel, but recursively" },
    { "https://www.pureref.com/",       "PureRef - great for images and collages" },
    { "https://www.miltonpaint.com/",   "Milton Paint - fast and lightweight infinite canvas" },
    { "https://filepilot.tech/",        "FilePilot - file manager for Windows that is really really good" },
    { "https://remedybg.handmade.network/", "RemedyBG - great and tiny debugger" },
    { "https://github.com/EpicGamesExt/raddebugger/", "RAD Debugger - greater and bigger debugger" },
    { "https://github.com/focus-editor/focus", "Focus - my text editor of choice" },
    { "https://azmr.itch.io/whitebox",  "Whitebox - seems neat" },
    { "https://www.screentogif.com/",   "ScreenToGif - good for making gifs from screen capture" },
    { "https://www.aseprite.org/",      "Aseprite - my pick for pushing pixels" },
};

const struct library_link links_programming[] = {
    { "https://github.com/mattiasgustavsson/template_project/releases/tag/tiny-c-compiler", "Tiny C Compiler" },
    { "https://github.com/nothings/stb", "stb single-header libraries" },
    { "https://www.libsdl.org/",         "SDL - now with the number 3" },
    { "https://hexed.it/",               "HexEd - hex editor" },
    { "https://hg.sr.ht/~duangle/oui-blendish", "Oui Blendish - single-header UI library for Blender-style UI" },
    { "https://github.com/grug-lang/grug", "Grug - scripting language that seems fun" },
};

const struct library_link links_game_making[] = {
    { "https://www.swordofmoonlight.com/", "Sword of Moonlight - King's Field game engine" },
    { "https://github.com/mattiasgustavsson/template_project", "Mattias Gustavsson's lightweight C engine" },
    { "https://ioquake3.org/", "ioquake3 - Quake 3, maintained" },
    { "https://milanote.com/inspiration/game-designers", "Milanote - whiteboard thingy" },
};

const struct library_link links_fun[] = {
    { "https://www.fourmilab.ch/cellab/manual/", "Cellular automata page" },
    { "https://silverspaceship.com/promesst/", "Promesst" },
};

const struct library_link links_audio[] = {
    { "https://github.com/jpcima/ADLplug", "ADLplug" },
    { "https://www.huygens-fokker.org/scala/", "Scala - some weird music shit" },
    { "https://imitone.com/", "Imitone - toy synth, maybe fun" },
};

const struct library_link links_art[] = {
    { "https://www.tldraw.com/", "tldraw - cool drawing tool" },
    { "https://lesterbanks.com/2014/03/verve-painter-fluid-dynamics-paint/", "Verve Painter - particle painting program" },
    { "https://speedypainter.altervista.org/", "Speedy Painter" },
    { "https://www.pencil2d.org/", "Pencil2D" },
    { "https://www.pixaflux.com/index.html", "PixaFlux" },
    { "https://opentoonz.github.io/e/", "OpenToonz" },
    { "https://excalidraw.com/", "Excalidraw - in-browser collab drawing" },
    { "https://www5.lunapic.com/editor/", "LunaPic - online photo editing" },
    { "https://key2mesh.github.io/", "Key2Mesh - turn pictures into animation?" },
};

const struct library_link links_misc[] = {
    { "https://apps.kde.org//", "KDE apps - including Krita" },
};


const struct library_group library_groups[] = {
    { "software that sparks joy"  , links_software   , ARRAY_COUNT(links_software)    },
    { "programming"               , links_programming, ARRAY_COUNT(links_programming) },
    { "game making things"        , links_game_making, ARRAY_COUNT(links_game_making) },
    { "fun things, games and toys", links_fun        , ARRAY_COUNT(links_fun)         },
    { "audio"                     , links_audio      , ARRAY_COUNT(links_audio)       },
    { "painting and animation"    , links_art        , ARRAY_COUNT(links_art)         },
    { "misc stuff I guess"        , links_misc       , ARRAY_COUNT(links_misc)        },
};


// building
void add_library_link(struct note *page, const struct library_link *link)
{
    note_puts(page, STR("<li><a href=\""));
    note_puts(page, CSTR((char *)link->link));
    note_puts(page, STR("\">"));
    note_puts(page, CSTR((char *)link->text));
    note_puts(page, STR("</a></li>\n"));
}

void add_library_group(struct note *page, const struct library_group *group)
{
    note_puts(page, STR("<section class=\"library-group\">\n"));

    note_puts(page, STR("<h2>"));
    note_puts(page, CSTR((char *)group->title));
    note_puts(page, STR("</h2>\n"));

    note_puts(page, STR("<ul class=\"library-links\">\n"));

    for (int i = 0; i < group->count; i++) {
        add_library_link(page, &group->links[i]);
    }

    note_puts(page, STR("</ul>\n"));
    note_puts(page, STR("</section>\n"));
}

void add_library(struct note *page)
{
    note_puts(page, STR("<p class=\"library-intro\">"));
    note_puts(page, STR("cool and random links from random times, some old, some new! "
                        "I don't take responsibility for any of the things I link, "
                        "it's just a bunch of random bookmarks, some cooler than others!"));
    note_puts(page, STR("</p>\n"));

    for (int i = 0; i < ARRAY_COUNT(library_groups); i++) {
        add_library_group(page, &library_groups[i]);
    }
}