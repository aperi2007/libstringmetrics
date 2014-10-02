/*
 * * Copyright (C) 2014 Andrea Peri et al. All rights reserved.
 *
 * This file is part of libstringmetrics
 *
 * libstringmetrics is a SQLite Extension for the Library libsimmetrics. A C port
 * of the Java project called Simmetrics,
 *
 * The C libsimmetrics can be found here: https://github.com/jokillsya/libsimmetrics
 * The Java code can be found here: https://github.com/Simmetrics/simmetrics
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * wrapper_functions.c
 *
 *  Created on: 15 Sept 2014
 *      Author: Andrea Peri <aperi2007@gmail.com>
 */

/*
	the algorithm with the option to custom tokenizer are:
		jaccard
		euclidean
		dice_similarity
		cosine
		block_distance
		qgrams_distance
		overlap_coefficient
		monge_elkan
		matching_coefficient

	the algorithm that don't use the tokenizer are:
		jaro
		double_metaphone
		cost
		soundex
		smith_waterman_gotoh
		smith_waterman
		needleman_wunch
		metaphone
		levenshtein
		jaro_winkler
*/

#include "sqlite3ext.h"
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stddef.h>
#include "simmetrics.h"

SQLITE_EXTENSION_INIT3

	const int SIMMETC = 27;

	const char *SIMMETS[27] = {	"block_distance",
								"block_distance_custom",
								"cosine",
								"cosine_custom",
								"dice",
								"dice_custom",
								"euclidean_distance",
								"euclidean_distance_custom",
								"jaccard",
								"jaccard_custom",
								"jaro",
								"jaro_winkler",
								"levenshtein",
								"matching_coefficient",
								"matching_coefficient_custom",
								"monge_elkan",
								"monge_elkan_custom",
								"needleman_wunch",
								"overlap_coefficient",
								"overlap_coefficient_custom",
								"qgrams_distance",
								"qgrams_distance_custom",
								"smith_waterman",
								"smith_waterman_gotoh",
								"soundex_phonetics",
        						"metaphone_phonetics",
       							"double_metaphone_phonetics"
        						};

	int which_type(char *simtype)
	{
	    int i;
	    for (i=0; i < SIMMETC; i++) {
	        if (strcmp(SIMMETS[i], simtype) == 0) {
 	           return (i);
			}
	    }
	    return (-1);
	}

void stringmetricsFunc(sqlite3_context *context, int argc, sqlite3_value **argv)
{
	int result;
	char *sm_name=NULL, *mex=NULL, str[80], metrics[250], *tokenlist=NULL;
	const char messaggio[] = "usage: \n\t$ stringmetrics(\"<algoritm>\",\"<kind of output>\",\"<string1>\",\"<string2>\",\"<tokenlist>\")\n" \
							"\nWhere <kind of output> is one of (\"similarity\", \"metric\", \"phrase\")\n" \
							"\nWhere <tokenlist> is the list of char used as token. It is not used by all the algoritms. The algorithms that use it are postfixed with \"custom\". If it is omitted the list used is \n\t\t\"carriage return\" \n\t\t\"newline (line feed)\" \n\t\t\"horizontal tab\" \n\t\t\"null character\" \n\t\t\"no-break space\" \n\t\t\"space\"" \
							"example:\nselect stringmetrics(\"block_distance\",\"phrase\",\"via giuseppe-garibaldi\",\"via giuseppe garibaldi\",NULL);" \
							"\nvs\nselect stringmetrics(\"block_distance_custom\",\"phrase\",\"via giuseppe-garibaldi\",\"via giuseppe garibaldi\",\"-\");" \
							"\n\nWhere <algoritm> is one of:\n";

    if ( (argc != 5) || (sqlite3_value_type( argv[0] ) == SQLITE_NULL) || (sqlite3_value_type( argv[1] ) == SQLITE_NULL) ) {
			mex = sqlite3_mprintf("%s",messaggio);
	        int i;
	        for (i=0; i < SIMMETC; i++) {
	            if (i > 0) {
					sprintf(str," \t\t%s\n", SIMMETS[i]);
	            	//mex = sqlite3_realloc(mex,strlen(mex)+strlen(str)+1);
	            	mex = sqlite3_mprintf("%s%s",mex,str);
				}
	        }
          	//mex = sqlite3_realloc(mex,strlen(mex)+strlen("\n")+1);
			mex = sqlite3_mprintf("%s%\n",mex);
			sqlite3_result_text(context, mex, strlen(mex)+1, sqlite3_free);
	} else {
        float similarity = 0;
		char *par0 = (char *)sqlite3_value_text(argv[0]);
		char *par1 = NULL;
		char *par2 = NULL;
		if( sqlite3_value_type( argv[2] ) == SQLITE_NULL) {
			par1 = sqlite3_mprintf("");
		} else {
			par1 = (char *)sqlite3_value_text(argv[2]);
		}
		if( sqlite3_value_type( argv[3] ) == SQLITE_NULL) {
			par2 = sqlite3_mprintf("");
		} else {
			par2 = (char *)sqlite3_value_text(argv[3]);
		}
		char *kindofoutput = (char *)sqlite3_value_text(argv[1]);
		char *par4 = NULL, *tokenlist = NULL;
		if(sqlite3_value_type( argv[4] ) != SQLITE_NULL) {
			par4 =  (char *)sqlite3_value_text(argv[4]);
			tokenlist = sqlite3_mprintf("%s%s",WHITESPACE_DELIMITERS,par4);
			//sqlite3_free(par4);
		}
        switch (which_type(par0)) {
            case 0:
                sm_name = "Block Distance";
                sprintf(metrics, "%d", block_distance(par1,par2));
                similarity = block_distance_similarity(par1, par2 );
                break;
            case 1:
                {
					std_tokenizer_t tokenizer = {
						.delimiters = tokenlist,
						.tok_utarr_func = &tokenize_to_utarray,
						.tok_uq_hash_func = &uq_tokenize_to_hash
					};
	                sm_name = "Block Distance customized";
					sprintf(metrics, "%d", block_distance_custom(par1,par2,&tokenizer));
	                similarity = block_distance_similarity_custom(par1, par2, &tokenizer );
				}
                break;
            case 2:
                sm_name = "Cosine Similarity";
                similarity = cosine_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 3:
                {
					std_tokenizer_t tokenizer = {
						.delimiters = tokenlist,
						.tok_utarr_func = &tokenize_to_utarray,
						.tok_uq_hash_func = &uq_tokenize_to_hash
					};
	                sm_name = "Cosine Similarity customized";
	                similarity = cosine_similarity_custom(par1, par2, &tokenizer );
					sprintf(metrics, "%f", similarity);
				}
                break;
            case 4:
                sm_name = "Dice Similarity";
                similarity = dice_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 5:
                {
					std_tokenizer_t tokenizer = {
						.delimiters = tokenlist,
						.tok_utarr_func = &tokenize_to_utarray,
						.tok_uq_hash_func = &uq_tokenize_to_hash
					};
	                sm_name = "Dice Similarity customized";
	                similarity = dice_similarity_custom(par1, par2, &tokenizer );
					sprintf(metrics, "%f", similarity);
				}
                break;
            case 6:
                sm_name = "Euclidean Distance";
                sprintf(metrics, "%3.2f", euclidean_distance(par1, par2));
                similarity = euclidean_distance_similarity(par1, par2);
                break;
            case 7:
                {
					std_tokenizer_t tokenizer = {
						.delimiters = tokenlist,
						.tok_utarr_func = &tokenize_to_utarray,
						.tok_uq_hash_func = &uq_tokenize_to_hash
					};
	                sm_name = "Euclidean Distance customized";
	                similarity = euclidean_distance_similarity_custom(par1, par2, &tokenizer);;
					sprintf(metrics, "%d", euclidean_distance_custom(par1, par2, &tokenizer ));
				}
                break;
            case 8:
                sm_name = "Jaccard Similarity";
                similarity = jaccard_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 9:
                {
					std_tokenizer_t tokenizer = {
						.delimiters = tokenlist,
						.tok_utarr_func = &tokenize_to_utarray,
						.tok_uq_hash_func = &uq_tokenize_to_hash
					};
	                sm_name = "Jaccard Similarity customized";
	                similarity = jaccard_similarity_custom(par1, par2, &tokenizer);;
					sprintf(metrics, "%f", similarity);
				}
                break;
            case 10:
                sm_name = "Jaro Similarity";
                similarity = jaro_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 11:
                sm_name = "Jaro Winkler Similarity";
                similarity = jaro_winkler_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 12:
                sm_name = "Levenshtein Distance";
                sprintf(metrics, "%d", levenshtein(par1, par2));
                similarity = levenshtein_similarity(par1, par2);
                break;
            case 13:
                sm_name = "Matching Coefficient SimMetrics";
                sprintf(metrics, "%3.2f", matching_coefficient(par1, par2));
                similarity = matching_coefficient_similarity(par1, par2);
                break;
            case 14:
                {
					std_tokenizer_t tokenizer = {
						.delimiters = tokenlist,
						.tok_utarr_func = &tokenize_to_utarray,
						.tok_uq_hash_func = &uq_tokenize_to_hash
					};
	                sm_name = "Matching Coefficient SimMetrics customized";
	                similarity = matching_coefficient_similarity_custom(par1, par2, &tokenizer);
					sprintf(metrics, "%3.2f", matching_coefficient_custom(par1, par2, &tokenizer));
				}
                break;
            case 15:
                sm_name = "Monge Elkan Similarity";
                similarity = monge_elkan_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 16:
                {
	                sm_name = "Matching Coefficient SimMetrics customized STILL NOT IMPLEMENTED";
	                similarity = 0;
					sprintf(metrics, "still not implemented");
				}
                break;
            case 17:
                sm_name = "Needleman Wunch SimMetrics";
                sprintf(metrics, "%3.2f", needleman_wunch(par1, par2));
                similarity = needleman_wunch_similarity(par1, par2);
                break;
            case 18:
                sm_name = "Overlap Coefficient Similarity";
                similarity = overlap_coefficient_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 19:
                {
					std_tokenizer_t tokenizer = {
						.delimiters = tokenlist,
						.tok_utarr_func = &tokenize_to_utarray,
						.tok_uq_hash_func = &uq_tokenize_to_hash
					};
	                sm_name = "Overlap Coefficient Similarity customized";
	                similarity = overlap_coefficient_similarity_custom(par1, par2, &tokenizer);
					sprintf(metrics, "%f", similarity);
				}
                break;
            case 20:
                sm_name = "QGrams Distance";
                sprintf(metrics, "%d", qgrams_distance(par1, par2));
                similarity = qgrams_distance_similarity(par1, par2);
                break;
            case 21:
                {
					std_tokenizer_t tokenizer = {
						.delimiters = tokenlist,
						.tok_utarr_func = &tokenize_to_utarray,
						.tok_uq_hash_func = &uq_tokenize_to_hash
					};
	                sm_name = "QGrams Distance customized";
	                similarity = qgrams_distance_similarity_custom(par1, par2, &tokenizer);
					sprintf(metrics, "%d", qgrams_distance_custom(par1, par2,&tokenizer));
				}
                break;
            case 22:
                sm_name = "Smith Waterman SimMetrics";
                sprintf(metrics, "%3.2f", smith_waterman(par1, par2));
                similarity = smith_waterman_similarity(par1, par2);
                break;
            case 23:
                sm_name = "Smith Waterman Gotoh SimMetrics";
                sprintf(metrics, "%3.2f", smith_waterman_gotoh(par1, par2));
                similarity = smith_waterman_gotoh_similarity(par1, par2);
                break;
            case 24:
                sm_name = "Soundex Phonetics";
                char *s1 = soundex(par1);
                char *s2 = soundex(par2);
                sprintf(metrics, "%s & %s", s1, s2);
                free(s1);
                free(s2);
                similarity = soundex_similarity(par1, par2);
                break;
            case 25:
                sm_name = "Metaphone Phonetics";
                char *m1 = metaphone(par1);
                char *m2 = metaphone(par2);
                sprintf(metrics, "%s & %s", m1, m2);
                free(m1);
                free(m2);
                similarity = metaphone_similarity(par1, par2);
                break;
            case 26:
                sm_name = "Double Metaphone Phonetics";
                char *dm1 = double_metaphone(par1);
                char *dm2 = double_metaphone(par2);
                sprintf(metrics, "%s & %s", dm1, dm2);
                free(dm1);
                free(dm2);
                similarity = double_metaphone_similarity(par1, par2);
                break;
            default:
               sprintf(metrics,"Unknown SimMetric %s, not found.\n", par0);
               sqlite3_result_error(context, metrics, -1);
               return;
		}
		if(kindofoutput!=NULL) {
			if(stricmp(kindofoutput,"similarity")==0) {
				sqlite3_result_double(context, similarity);
			} else if(stricmp(kindofoutput,"metric")==0) {
				sqlite3_result_text(context, metrics, strlen(metrics)+1, SQLITE_STATIC);
			} else {
				mex = sqlite3_mprintf("%s between \"%s\" & \"%s\" is \"%s\" and yields a %3.0f%% similarity",sm_name,par1,par2,metrics,similarity*100);
				sqlite3_result_text(context, mex, strlen(mex)+1, sqlite3_free);
			}
		} else {
			mex = sqlite3_mprintf("%s between \"%s\" & \"%s\" is \"%s\" and yields a %3.0f%% similarity",sm_name,par1,par2,metrics,similarity*100);
			sqlite3_result_text(context, mex, strlen(mex)+1, sqlite3_free);
		}
			//sqlite3_free(par0);
			//sqlite3_free(par1);
			//sqlite3_free(par2);
			//sqlite3_free(kindofoutput);
			if(tokenlist != NULL) {
				sqlite3_free(tokenlist);
			}
    }

	return;
}
