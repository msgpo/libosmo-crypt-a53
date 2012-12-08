# This is _NOT_ the library release version, it's an API version.
# Please read Chapter 6 "Library interface versions" of the libtool documentation before making any modification
LIBVERSION=0:0:0

INCLUDES = $(all_includes) -I$(top_srcdir)/include
AM_CFLAGS = -fPIC -Wall $(LIBOSMOCORE_CFLAGS)
AM_LDFLAGS = $(LIBOSMOCORE_LIBS)

lib_LTLIBRARIES = libosmo-crypto-a53.la

libosmo_crypto_a53_la_SOURCES = a53f.c kgcore.c kasumi.c osmocom.c
libosmo_crypto_a53_la_LDFLAGS = -shared
