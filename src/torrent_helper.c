/**
 * torrent_helper.c - Part of Partclone project.
 *
 * Copyright (c) 2019~ Thomas Tsai <thomas at nchc org tw>
 *
 * function and structure used by main.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "torrent_helper.h"

/*
 * BitTorrent piece hashing is DISABLED in this fork.
 *
 *
 * Scope of the loss: `-t` (torrent_only) and `-T` (blockfile) mode.  Those
 * exist so a Clonezilla SERVER can seed disk images over BitTorrent to a lab
 * of PCs.  Nothing else changes -- in particular the image format and its
 * CRC32 integrity check (src/checksum.c) never touched OpenSSL and are
 * byte-for-byte identical to before.
 *
 * torrent_init() is the single entry point: main.c only reaches the other
 * torrent_* functions after calling it, and only under `opt.blockfile == 1`.
 * So failing here, loudly, makes the whole feature unreachable and makes it
 * impossible to emit a torrent.info full of wrong hashes.
 *
 * To restore it: drop in any public-domain SHA-1 (about 90 lines), point
 * these three functions at it, and leave configure.ac and Makefile.am alone.
 */
void torrent_init(torrent_generator *torrent, FILE *tinfo)
{
	(void)torrent;
	(void)tinfo;
	fprintf(stderr,
	        "partclone: BitTorrent mode (-t/-T) is not available in this build.\n"
	        "           SHA-1 came from OpenSSL, which was removed for licence\n"
	        "           reasons.  Ordinary clone/restore/chkimg are unaffected.\n");
	exit(1);
}

/* Unreachable: main.c only calls these after torrent_init(), which exits.
 * They remain as definitions purely so main.c still links. */
void torrent_update(torrent_generator *torrent, void *buffer, size_t length)
{
	(void)torrent;
	(void)buffer;
	(void)length;
}

void torrent_final(torrent_generator *torrent)
{
	(void)torrent;
}

void torrent_start_offset(torrent_generator *torrent, unsigned long long offset)
{
	fprintf(torrent->tinfo, "offset: %032llx\n", offset);
}

void torrent_end_length(torrent_generator *torrent, unsigned long long length)
{
	fprintf(torrent->tinfo, "length: %032llx\n", length);
}
