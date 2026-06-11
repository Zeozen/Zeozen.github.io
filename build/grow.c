#include <windows.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCOPE(open, close) \
    for (int _once = ((open), 0); !_once; _once = 1, (close))


#include "note.c"
#include "page.c"
#include "library.c"
#include "gallery.c"

struct note page = {0};

#define PUSH(s)  (note_puts(&page, STR(s)))

#define KVP(k, v) (css_kvp(&page, STR(k),STR(v)))


#define SCOPE_CSS(sel) SCOPE(css_obj_start(&page, STR(sel)), css_obj_close(&page))

#define SCOPE_DIV(name) SCOPE(div_open(&page, STR(name)), div_close(&page))

#define BUTTON(link, name) add_button(&page, STR(link), STR(name))

int main(void)
{
	note_grow(&page, 1024);
	int i = 0;

// GARDEN
	SCOPE(page_open(&page), page_close(&page)) {
	SCOPE(page_header_open(&page, "zeozen.garden"), page_header_close(&page)) {}

	SCOPE(PUSH("<body>\n"), PUSH("</body>\n"))
	{
		SCOPE_DIV("root") {
		add_nav(&page);
		SCOPE_DIV("contents") {
		SCOPE_DIV("main") {
			PUSH("<p>Welcome<br> to my garden!<br><br>Enjoy your stay.</p>");
		}
		}

		}

	}

	} // page
	note_save(&page, "index.html");
	note_wipe(&page);

// GALLERY
	gallery_scan_all();
	SCOPE(page_open(&page), page_close(&page)) {
	SCOPE(page_header_open(&page, "zeozen.garden.gallery"), page_header_close(&page)) {}

	SCOPE(PUSH("<body>\n"), PUSH("</body>\n"))
	{
		SCOPE_DIV("root") {
		    add_nav(&page);

		    SCOPE_DIV("contents") {
			    SCOPE_DIV("main") {
			        add_gallery(&page);
			    }
		    }
		}
	}

	}
	note_save(&page, "gallery.html");
	note_wipe(&page);

	emit_gallery_books();

// JOURNAL
	SCOPE(page_open(&page), page_close(&page)) {
	SCOPE(page_header_open(&page, "zeozen.garden.gallery"), page_header_close(&page)) {}

	SCOPE(PUSH("<body>\n"), PUSH("</body>\n"))
	{
		SCOPE_DIV("root") {
		add_nav(&page);
		SCOPE_DIV("contents") {
		SCOPE_DIV("main") {
			PUSH("<p>JOURNAL</p>");
			PUSH("<p>!under construction!</p>");
		}
		}
		}

	}

	} // page
	note_save(&page, "journal.html");
	note_wipe(&page);

// LIBRARY
	SCOPE(page_open(&page), page_close(&page)) {
	SCOPE(page_header_open(&page, "zeozen.garden.gallery"), page_header_close(&page)) {}

	SCOPE(PUSH("<body>\n"), PUSH("</body>\n"))
	{
		SCOPE_DIV("root") {
			add_nav(&page);

			SCOPE_DIV("library-shell") {
		        PUSH("<main class=\"library-box\">\n");
		        add_library(&page);
		        PUSH("</main>\n");
		    }
		}

	}

	} // page
	note_save(&page, "library.html");
	note_wipe(&page);

	return 0;
}