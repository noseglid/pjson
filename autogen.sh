#!/bin/sh

if [ -x "$(which autoreconf 2>/dev/null)" ]; then
	exec autoreconf -ivf
fi

LIBTOOLIZE=libtoolize
[ "Darwin" = "$(uname)" ] && LIBTOOLIZE=glibtoolize

aclocal -I m4 && \
	$LIBTOOLIZE && \
	autoconf && \
	automake --add-missing --force-missing --copy
