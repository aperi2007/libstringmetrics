gcc -std=c99 -w -g -shared \
	-I src \
	-I src/libsimmetrics/include \
	-I src/libsqlite/include \
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
	src/libsqlite/sqlite/sqlite3.c \
	-o libstringmetrics.dll

	