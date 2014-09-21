
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stddef.h>
#include "simmetrics.h"

	const int SIMMETC = 35;

	const char *SIMMETS[35] = {	"block",
								"block_distance",
								"cos",
								"cosine",
								"dice",
								"eucli",
								"euclidean_distance",
								"jac",
								"jaccard",
								"jar",
								"jaro",
								"wink",
								"jaro_winkler",
								"leven",
								"levenshtein",
								"match",
								"matching_coefficient",
								"monge",
								"monge_elkan",
								"need",
								"needleman_wunch",
								"ol",
								"overlap_coefficient",
								"qg",
								"qgrams_distance",
								"smith",
								"smith_waterman",
								"gotoh",
								"smith_waterman_gotoh",
								"snd",
								"soundex",
        						"meta",
        						"metaphone",
        						"dmeta",
        						"double_metaphone"
        						};

	int which_type(char *simtype)
	{
	    int i;
	    for (i=0; i < SIMMETC; i++) {
	        if (strcmp(SIMMETS[i], simtype) == 0)
 	           return (i);
	    }
	    return (-1);
	}

void stringmetricsFunc(sqlite3_context *context, int argc, sqlite3_value **argv)
{
	int result;
	char *sm_name=NULL, *mex=NULL, str[80], metrics[250];
	const char messaggio[] = "usage: \n\t$ stringmetrics(\"<algoritm>\",\"<kind of output>\",\"<string1>\",\"<string2>\")\n" \
							"\nWhere <kind of output> is one of (\"similarity\", \"metric\", \"phrase\")\n" \
							"\nWhere <algoritm> is one of:\n";
    if ( (argc != 4) || (sqlite3_value_type( argv[0] ) == SQLITE_NULL) || (sqlite3_value_type( argv[1] ) == SQLITE_NULL) || (sqlite3_value_type( argv[2] ) == SQLITE_NULL) || (sqlite3_value_type( argv[3] ) == SQLITE_NULL) ) {
			mex = malloc(strlen(messaggio)+1);
			strcpy(mex,messaggio);
	        int i;
	        for (i=0; i < SIMMETC; i++) {
	            if (i > 0) {
	                sprintf(str,"   %s", SIMMETS[i]);
	            	mex = realloc(mex,strlen(mex)+strlen(str)+1);
	            	strcat(mex,str);
				}
	        }
            sprintf(str,"\n");
          	mex = realloc(mex,strlen(mex)+strlen(str)+1);
           	strcat(mex,str);
	} else {
        float similarity = 0;
		char *par0 = strdup(sqlite3_value_text(argv[0]));
		char *par1 = strdup(sqlite3_value_text(argv[2]));
		char *par2 = strdup(sqlite3_value_text(argv[3]));
		char *kindofoutput = strdup(sqlite3_value_text(argv[1]));

        switch (which_type(par0)) {
            case 0:
            case 1:
                sm_name = "Block Distance";
                sprintf(metrics, "%d", block_distance(par1,par2));
                similarity = block_distance_similarity(par1, par2 );
                break;
            case 2:
            case 3:
                sm_name = "Cosine Similarity";
                similarity = cosine_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 4:
                sm_name = "Dice Similarity";
                similarity = dice_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 5:
            case 6:
                sm_name = "Euclidean Distance";
                sprintf(metrics, "%3.2f", euclidean_distance(par1, par2));
                similarity = euclidean_distance_similarity(par1, par2);
                break;
            case 7:
            case 8:
                sm_name = "Jaccard Similarity";
                similarity = jaccard_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 9:
            case 10:
                sm_name = "Jaro Similarity";
                similarity = jaro_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 11:
            case 12:
                sm_name = "Jaro Winkler Similarity";
                similarity = jaro_winkler_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 13:
            case 14:
                sm_name = "Levenshtein Distance";
                sprintf(metrics, "%d", levenshtein(par1, par2));
                similarity = levenshtein_similarity(par1, par2);
                break;
            case 15:
            case 16:
                sm_name = "Matching Coefficient SimMetrics";
                sprintf(metrics, "%3.2f", matching_coefficient(par1, par2));
                similarity = matching_coefficient_similarity(par1, par2);
                break;
            case 17:
            case 18:
                sm_name = "Monge Elkan Similarity";
                similarity = monge_elkan_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 19:
            case 20:
                sm_name = "Needleman Wunch SimMetrics";
                sprintf(metrics, "%3.2f", needleman_wunch(par1, par2));
                similarity = needleman_wunch_similarity(par1, par2);
                break;
            case 21:
            case 22:
                sm_name = "Overlap Coefficient Similarity";
                similarity = overlap_coefficient_similarity(par1, par2);
                sprintf(metrics, "%f", similarity);
                break;
            case 23:
            case 24:
                sm_name = "QGrams Distance";
                sprintf(metrics, "%d", qgrams_distance(par1, par2));
                similarity = qgrams_distance_similarity(par1, par2);
                break;
            case 25:
            case 26:
                sm_name = "Smith Waterman SimMetrics";
                sprintf(metrics, "%3.2f", smith_waterman(par1, par2));
                similarity = smith_waterman_similarity(par1, par2);
                break;
            case 27:
            case 28:
                sm_name = "Smith Waterman Gotoh SimMetrics";
                sprintf(metrics, "%3.2f", smith_waterman_gotoh(par1, par2));
                similarity = smith_waterman_gotoh_similarity(par1, par2);
                break;
            case 29:
            case 30:
                sm_name = "Soundex Phonetics";
                char *s1 = soundex(par1);
                char *s2 = soundex(par2);
                sprintf(metrics, "%s & %s", s1, s2);
                free(s1);
                free(s2);
                similarity = soundex_similarity(par1, par2);
                break;
            case 31:
            case 32:
                sm_name = "Metaphone Phonetics";
                char *m1 = metaphone(par1);
                char *m2 = metaphone(par2);
                sprintf(metrics, "%s & %s", m1, m2);
                free(m1);
                free(m2);
                similarity = metaphone_similarity(par1, par2);
                break;
            case 33:
            case 34:
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
               return (1);
		}
		if(kindofoutput!=NULL) {
			if(strcmp(tolower(kindofoutput),"similarity")==0) {
				sqlite3_result_double(context, similarity);
			} else if(strcmp(tolower(kindofoutput),"metric")==0) {
				sqlite3_result_text(context, metrics, strlen(metrics)+1, NULL);
			} else {
				mex = malloc(strlen(sm_name) + 200 + strlen(metrics)+1);
				sprintf(mex,"%s between \"%s\" & \"%s\" is \"%s\" and yields a %3.0f%% similarity",sm_name,par1,par2,metrics,similarity*100);
				sqlite3_result_text(context, mex, strlen(mex)+1, NULL);
			}
		} else {
			mex = malloc(strlen(sm_name) + 200 + strlen(metrics)+1);
			sprintf(mex,"%s between \"%s\" & \"%s\" is \"%s\" and yields a %3.0f%% similarity",sm_name,par1,par2,metrics,similarity*100);
			sqlite3_result_text(context, mex, strlen(mex)+1, NULL);
		}
    }

	return;
}
