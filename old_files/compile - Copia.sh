# gcc -std=c99 -w -g -mwindows -static-libgcc -no-undefined \
#	-mwin32 \
#    	-Wl,-Bstatic \
#    	-nostdlib \
#    	-nodefaultlibs \
#    	-static \
#	-s \
#	-m32 \
#	-I C:/my-programs/MinGW/lib \
#	-I C:/my-programs/MinGW/lib/gcc/mingw32/4.8.1 \
#	-lmingw32 \
#	-lgcc \
#	-lstdc++ \
#    	-mthreads \
#	-march=i686 \
#	-mtune=i686 \
#    	-Wl,--subsystem,windows,--output-def,libstringmetrics.def,--out-implib,libstringmetrics.a \

gcc 	-std=c99 \
	-w \
	-O0 \
    	-static-libstdc++ \
    	-static-libgcc \
    	-I src \
	-I src/libsimmetrics/include \
	-I src/libsqlite/include \
	-o libstringmetrics.dll \
	src/stringmetrics.c \
	src/wrapper_functions.c \
	src/libsimmetrics/simmetrics/block_distance.c \
	src/libsimmetrics/simmetrics/cosine_similarity.c \
	src/libsimmetrics/simmetrics/cost.c \
	src/libsimmetrics/simmetrics/dice_similarity.c \
	src/libsimmetrics/simmetrics/double_metaphone.c \
	src/libsimmetrics/simmetrics/euclidean_distance.c \
	src/libsimmetrics/simmetrics/jaccard_similarity.c \
	src/libsimmetrics/simmetrics/jaro.c \
	src/libsimmetrics/simmetrics/jaro_winkler.c \
	src/libsimmetrics/simmetrics/levenshtein.c \
	src/libsimmetrics/simmetrics/matching_coefficient.c \
	src/libsimmetrics/simmetrics/metaphone.c \
	src/libsimmetrics/simmetrics/monge_elkan.c \
	src/libsimmetrics/simmetrics/needleman_wunch.c \
	src/libsimmetrics/simmetrics/overlap_coefficient.c \
	src/libsimmetrics/simmetrics/qgrams_distance.c \
	src/libsimmetrics/simmetrics/simmetrics.c \
	src/libsimmetrics/simmetrics/smith_waterman.c \
	src/libsimmetrics/simmetrics/smith_waterman_gotoh.c \
	src/libsimmetrics/simmetrics/soundex.c \
	src/libsimmetrics/simmetrics/tokenizer.c \
	src/libsimmetrics/simmetrics/util.c \
	src/libsqlite/sqlite/sqlite3.c

	