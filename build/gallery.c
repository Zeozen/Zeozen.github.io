struct gallery_image
{
    char path[512];
};

struct gallery_book
{
    const char *id;
    const char *title;
    const char *desc;

    struct gallery_image *images;
    int count;
    int cap;
};

static struct gallery_book gallery_books[] =
{
	{
		"inked",
		"Watercolor and Ink",
		"Ink and watercolor pieces from Inktobers and more",
	},
	{
		"riven",
		"Riven Journal",
		"Notes and sketches from Riven playthrough",
	},
	{
		"myst3",
		"Myst 3 Journal",
		"Notes and sketches from Myst 3: Exile playthrough",
	},
	{
		"myst4",
		"Myst 4 Journal",
		"Notes and sketches from Myst 4: Revelation playthrough",
	},
	{
		"vintagestory",
		"Vintage Story Journal",
		"Sketches from adventures in Vintage Story",
	},
	{
		"outward2",
		"Outward2 Story Journal",
		"Sketches from adventures in Outward 2",
	},
};

static int gallery_book_count = sizeof(gallery_books) / sizeof(gallery_books[0]);



static int gallery_is_image(const char *name)
{
    const char *dot = strrchr(name, '.');
    if (!dot) return 0;

    dot++;

    return
        _stricmp(dot, "jpg")  == 0 ||
        _stricmp(dot, "jpeg") == 0 ||
        _stricmp(dot, "png")  == 0;
}

static int gallery_image_cmp(const void *a, const void *b)
{
    const struct gallery_image *ia = a;
    const struct gallery_image *ib = b;

    return strcmp(ia->path, ib->path);
}

static void gallery_book_push_image(struct gallery_book *book, const char *path)
{
    if (book->count >= book->cap)
    {
        int new_cap = book->cap ? book->cap * 2 : 16;

        book->images = realloc(book->images, new_cap * sizeof(book->images[0]));
        book->cap = new_cap;
    }

    snprintf(book->images[book->count].path,
             sizeof(book->images[book->count].path),
             "%s",
             path);

    book->count++;
}

static void gallery_scan_book(struct gallery_book *book)
{
#ifdef _WIN32
    char dir[512];
    char pattern[512];

    snprintf(dir,     sizeof(dir),     "../docs/res/gallery/%s", book->id);
    snprintf(pattern, sizeof(pattern), "%s/*", dir);

    WIN32_FIND_DATAA find;
    HANDLE handle = FindFirstFileA(pattern, &find);

    if (handle == INVALID_HANDLE_VALUE)
    {
        printf("gallery: could not open dir: %s\n", pattern);
        return;
    }

    do
    {
        if (find.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            continue;

        if (!gallery_is_image(find.cFileName))
            continue;

        char path[512];

        // IMPORTANT:
        // This is the path written into HTML, not the filesystem search path.
        snprintf(path, sizeof(path),
                 "res/gallery/%s/%s",
                 book->id,
                 find.cFileName);

        gallery_book_push_image(book, path);

    } while (FindNextFileA(handle, &find));

    FindClose(handle);

    qsort(book->images, book->count, sizeof(book->images[0]), gallery_image_cmp);
#else
    #error gallery_scan_book needs non-Windows implementation
#endif
}

static void gallery_scan_all(void)
{
    for (int i = 0; i < gallery_book_count; i++)
    {
        gallery_scan_book(gallery_books + i);
    }
}




void add_gallery(struct note *page)
{
    note_puts(page, STR("<section class=\"gallery-list\">\n"));
    note_puts(page, STR("<h1>Gallery</h1>\n"));
    note_puts(page, STR("<ul class=\"book-list\">\n"));

    for (int i = 0; i < gallery_book_count; i++)
    {
        const struct gallery_book *book = gallery_books + i;

        note_puts(page, STR("<li class=\"book-item\">\n"));

        note_puts(page, STR("<a class=\"book-spine\" href=\"gallery_"));
        note_puts(page, UCSTR(book->id));
        note_puts(page, STR(".html\">\n"));

        note_puts(page, STR("<span class=\"book-title\">"));
        note_puts(page, UCSTR(book->title));
        note_puts(page, STR("</span>\n"));

        if (book->desc)
        {
            note_puts(page, STR("<span class=\"book-desc\">"));
            note_puts(page, UCSTR(book->desc));
            note_puts(page, STR("</span>\n"));
        }

        note_puts(page, STR("</a>\n"));
        note_puts(page, STR("</li>\n"));
    }

    note_puts(page, STR("</ul>\n"));
    note_puts(page, STR("</section>\n"));
}


static void add_gallery_book(struct note *page, const struct gallery_book *book)
{
    note_puts(page, STR("<div class=\"sketchbook-shell\">\n"));
    note_puts(page, STR("<main class=\"sketchbook-box\">\n"));

    note_puts(page, STR("<header class=\"sketchbook-head\">\n"));

    note_puts(page, STR("<h1>"));
    note_puts(page, UCSTR(book->title));
    note_puts(page, STR("</h1>\n"));

    if (book->desc)
    {
        note_puts(page, STR("<p>"));
        note_puts(page, UCSTR(book->desc));
        note_puts(page, STR("</p>\n"));
    }

    note_puts(page, STR("</header>\n"));

    note_puts(page, STR("<section class=\"sketch-strip\">\n"));

    for (int i = 0; i < book->count; i++)
    {
        note_puts(page, STR("<figure class=\"sketch-page\">\n"));

        note_puts(page, STR("<img src=\""));
        note_puts(page, UCSTR(book->images[i].path));
        note_puts(page, STR("\" alt=\"\">\n"));

        note_puts(page, STR("</figure>\n"));
    }

    note_puts(page, STR("</section>\n"));

    note_puts(page, STR("</main>\n"));
    note_puts(page, STR("</div>\n"));
}


void emit_gallery_books(void)
{
    struct note page = {0};
    note_grow(&page, 1024);

    for (int i = 0; i < gallery_book_count; i++)
    {
        struct gallery_book *book = (struct gallery_book *)(gallery_books + i);

        SCOPE(page_open(&page), page_close(&page)) {
        SCOPE(page_header_open(&page, "zeozen.garden.gallery"), page_header_close(&page)) {}

        SCOPE(note_puts(&page, STR("<body>\n")), note_puts(&page, STR("</body>\n")))
        {
            SCOPE(div_open(&page, STR("root")), div_close(&page)) {
                add_nav(&page);
                add_gallery_book(&page, book);
            }
        }

        }

        note_puts(&page, STR(""));

        char filename[256];
        snprintf(filename, sizeof(filename), "gallery_%s.html", book->id);

        note_save(&page, filename);
        note_wipe(&page);
    }
}