AM_CPPFLAGS = @CFLAGS@
AM_CPPFLAGS = -I$(top_srcdir)/src/libsqlite/include \
AM_CPPFLAGS += -I$(top_srcdir)/src/libsimmetrics/include 
	
lib_LTLIBRARIES = libstringmetrics.la

libstringmetrics_la_SOURCES = stringmetrics.c \
			wrapper_functions.c \
			libsimmetrics/simmetrics/util.c \
			libsimmetrics/simmetrics/cost.c \
			libsimmetrics/simmetrics/tokenizer.c \
			libsimmetrics/simmetrics/simmetrics.c \
			libsimmetrics/simmetrics/soundex.c \
			libsimmetrics/simmetrics/metaphone.c \
			libsimmetrics/simmetrics/double_metaphone.c \
			libsimmetrics/simmetrics/jaro.c \
			libsimmetrics/simmetrics/levenshtein.c \
			libsimmetrics/simmetrics/jaro_winkler.c \
			libsimmetrics/simmetrics/smith_waterman.c \
			libsimmetrics/simmetrics/smith_waterman_gotoh.c \
			libsimmetrics/simmetrics/needleman_wunch.c \
			libsimmetrics/simmetrics/monge_elkan.c \
			libsimmetrics/simmetrics/block_distance.c \
			libsimmetrics/simmetrics/euclidean_distance.c \
			libsimmetrics/simmetrics/cosine_similarity.c \
			libsimmetrics/simmetrics/dice_similarity.c \
			libsimmetrics/simmetrics/jaccard_similarity.c \
			libsimmetrics/simmetrics/matching_coefficient.c \
			libsimmetrics/simmetrics/overlap_coefficient.c \
			libsimmetrics/simmetrics/qgrams_distance.c


libspatialite_la_LIBADD = ./libstringmetrics.la

if MINGW
libstringmetrics_la_LDFLAGS = -version-info 0:1:1 -no-undefined
endif

# to avoid boring messages for not gnu files organization
AUTOMAKE_OPTIONS = foreign

AM_CFLAGS = --pedantic -Wall -std=c99 -O2 -s
# AM_LDFLAGS = 

# the program to build (the names of the final binaries)
# lib_LTLIBRARIES = libstringmetrics.la

# libstringmetrics_la_SOURCE = 	
# Linker options libTestProgram
# libstringmetrics_la_LDFLAGS = 

# Compiler options. Here we are adding the include directory
# to be searched for headers included in the source code.
# libstringmetrics_la_CPPFLAGS = -I$(top_srcdir)/include

# ACLOCAL_AMFLAGS = -I m4
