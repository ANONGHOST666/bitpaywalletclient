ACLOCAL_AMFLAGS = -I build-aux/m4
.PHONY: gen
.INTERMEDIATE: $(GENBIN)

DIST_SUBDIRS = src/secp256k1

LIBSECP256K1=src/secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard src/secp256k1/src/*) $(wildcard src/secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

lib_LTLIBRARIES = libbtc.la
include_HEADERS = \
    include/btc/aes.h \
    include/btc/base58.h \
    include/btc/bip32.h \
    include/btc/block.h \
    include/btc/btc.h \
    include/btc/buffer.h \
    include/btc/chain.h \
    include/btc/cstr.h \
    include/btc/ecc_key.h \
    include/btc/ecc.h \
    include/btc/hash.h \
    include/btc/portable_endian.h \
    include/btc/random.h \
    include/btc/script.h \
    include/btc/serialize.h \
    include/btc/sha2.h \
    include/btc/tool.h \
    include/btc/tx.h \
    include/btc/utils.h \
    include/btc/vector.h

noinst_HEADERS = \
	src/ripemd160.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libbtc.pc

libbtc_la_SOURCES = \
    src/aes.c \
    src/base58.c \
    src/bip32.c \
    src/block.c \
    src/buffer.c \
    src/cstr.c \
    src/ecc_key.c \
    src/ecc_libsecp256k1.c \
    src/random.c \
    src/ripemd160.c \
    src/script.c \
    src/serialize.c \
    src/sha2.c \
    src/toolfunc.c \
    src/tx.c \
    src/utils.c \
    src/vector.c

libbtc_la_CFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src/logdb/include
libbtc_la_LIBADD = $(LIBSECP256K1)

if USE_TESTS
noinst_PROGRAMS = tests
tests_LDADD = libbtc.la
tests_SOURCES = \
    test/aes_tests.c \
    test/base58check_tests.c \
    test/bip32_tests.c \
    test/block_tests.c \
    test/buffer_tests.c \
    test/cstr_tests.c \
    test/ecc_tests.c \
    test/eckey_tests.c \
    test/hash_tests.c \
    test/random_tests.c \
    test/serialize_tests.c \
    test/sha2_tests.c \
    test/utest.h \
    test/unittester.c \
    test/tx_tests.c \
    test/utils_tests.c \
    test/vector_tests.c

tests_CFLAGS = $(libbtc_la_CFLAGS)
tests_CPPFLAGS = -I$(top_srcdir)/src
tests_LDFLAGS = -static
TESTS = tests
endif

if WITH_WALLET

libbtc_la_SOURCES += \
    src/logdb/logdb_core.c \
    src/logdb/logdb_memdb_llist.c \
    src/logdb/logdb_memdb_rbtree.c \
    src/logdb/logdb_rec.c \
    src/logdb/red_black_tree.c

include_HEADERS += \
    src/logdb/include/logdb/logdb_base.h \
    src/logdb/include/logdb/logdb_core.h \
    src/logdb/include/logdb/logdb_memdb_llist.h \
    src/logdb/include/logdb/logdb_memdb_rbtree.h \
    src/logdb/include/logdb/logdb_rec.h \
    src/logdb/include/logdb/logdb.h \
    src/logdb/include/logdb/red_black_tree.h

include_HEADERS += \
    include/btc/wallet.h

libbtc_la_SOURCES += \
    src/wallet.c

if USE_TESTS
tests_SOURCES += \
    test/wallet_tests.c \
    src/logdb/test/logdb_tests.c \
    src/logdb/test/tests_red_black_tree.c
endif
endif

if WITH_TOOLS
if USE_TESTS
tests_SOURCES += \
    test/tool_tests.c
endif
instdir=$(prefix)/bin
inst_PROGRAMS = bitcointool
bitcointool_LDADD = libbtc.la
bitcointool_SOURCES = \
    src/bitcointool.c
bitcointool_CFLAGS = $(libbtc_la_CFLAGS)
bitcointool_CPPFLAGS = -I$(top_srcdir)/src
bitcointool_LDFLAGS = -static
endif

clean-local:
	-$(MAKE) -C src/secp256k1 clean
