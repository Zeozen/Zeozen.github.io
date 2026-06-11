void page_open(struct note *note)
{
	note_puts(note, STR("<!doctype html>\n"));
	note_puts(note, STR("<html lang=\"en\">\n"));
}

void page_close(struct note *note)
{
	note_puts(note, STR("</html>"));
}

void page_header_open(struct note *note, char *title)
{
	note_puts(note, STR(
		"<head>\n"
		"<meta charset=\"UTF-8\">\n"
		"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
		"<link rel=\"icon\" type=\"image/x-icon\" href=\"/res/favicon.ico\">"
		"<title>\n"
	));

	note_puts(note, CSTR(title));

	note_puts(note, STR(
	"</title>\n"
	"<link href=\"style.css\" rel=\"stylesheet\">"
	));
}

void page_header_close(struct note *note)
{
	note_puts(note, STR(
		"</head>\n\n"
	));
}

void div_open(struct note *note, struct str name)
{
	note_puts(note, STR("<div class=\""));
	note_puts(note, name);
	note_puts(note, STR("\">\n"));
}

void div_close(struct note *note)
{
	note_puts(note, STR("</div>\n"));
}

void add_button(struct note *note, struct str href, struct str text)
{
    note_puts(note, STR("<a class=\"link_button\" href=\""));
    note_puts(note, href);
    note_puts(note, STR("\">"));
    note_puts(note, text);
    note_puts(note, STR("</a>\n"));
}

void nav_open(struct note* n)
{
    note_puts(n, STR("<nav class=\"nav\">\n"));
}

void nav_close(struct note* n)
{
    note_puts(n, STR("</nav>\n"));
}

void nav_link(struct note* n, struct str link, struct str name)
{
    note_puts(n, STR("<a class=\"nav-link\" href=\""));
    note_puts(n, link);
    note_puts(n, STR("\">"));
    note_puts(n, name);
    note_puts(n, STR("</a>\n"));
}

void add_nav(struct note* n)
{
    nav_open(n);
    nav_link(n, STR("index.html"),   STR("garden"));
    nav_link(n, STR("gallery.html"), STR("gallery"));
    nav_link(n, STR("journal.html"), STR("journal"));
    nav_link(n, STR("library.html"), STR("library"));
    nav_close(n);
}






// todo footer with socials
// steam, github, twitter, instagram, artstation, tiktok, ko-fi, twitch, discord, itch