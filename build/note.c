struct str
{
	char  *dat;
	size_t len;
};

struct note
{
	char  *dat;
	size_t len;
	size_t cap;
};

#define STR(s) ((struct str){ (char *)(s), sizeof(s) - 1 })

#define CSTR(s) ((struct str){ (s), strlen(s) })
#define UCSTR(s) ((struct str){ ((char *)s), strlen(s) })

#define ARRAY_COUNT(a) ((int)(sizeof(a) / sizeof((a)[0])))

void note_grow(struct note *note, size_t desired)
{
	size_t required = note->len + desired;
	if (note->cap > required) return;

	size_t cap = note->cap ? note->cap : required;
	while (cap < required) cap *= 2;
	note->cap = cap;
	note->dat = realloc(note->dat, note->cap * sizeof(*note->dat));
}

void note_puts(struct note *note, struct str s)
{
	note_grow(note, s.len);
	memcpy(note->dat + note->len, s.dat, s.len);
	note->len += s.len;
}

void note_save(struct note *note, char *path)
{
	char output_path[256];
	snprintf(output_path, sizeof(output_path), "%s/%s", "../docs", path);
	FILE *f = fopen(output_path, "wb");
	fwrite(note->dat, 1, note->len, f);
	fclose(f);
}

void note_wipe(struct note *note)
{
	note->len = 0;
}

