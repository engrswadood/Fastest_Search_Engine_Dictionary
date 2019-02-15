#include "dic_initializer.h"
void init_address_app(uint32_t nthreads)
{
	ctbl = createCtTables();
	query_data = malloc(nthreads * sizeof(QUERY_DATA));
	address_table = create_address_tbl(TOTAL_INITIAL_ADDRESSES);
	container_table	= create_container_tbl(TOTAL_INITIAL_CONTAINERS);
	
	
	load_address_db();
	init_query_obj();
}	
void init_query_obj()
{
	
	//srchQuery has not been coded yet.
	int i;
	query_data->_remaingkeysAr = malloc(USER_WORDS_LEN*sizeof(char));
	query_data->_keys = malloc(USER_WORDS_LEN*sizeof(int *));
	query_data->suggestedAr = malloc(TOTAL_MISS_SPFELLED*sizeof(int *));
	for(i=0; i<TOTAL_MISS_SPFELLED; i++)
		query_data->suggestedAr[i] = malloc(TOTAL_SUGGESTIONS*sizeof(int *))	
	
	query_data->_result = malloc(TOTAL_NODES*sizeof(TupleNode *));
	for(i=0; i<TOTAL_NODES; i++)
		query_data->_result[i] = malloc(sizeof(TupleNode));
	
	query_data->qry_rply = malloc(QRY_RPLY_SIZE);
	query_data->con = get_connection();
}
//dic[l][p][b][i] = 
void create_dictionary()
{
	nbin = nalp*nalp+nalp+1;
	dictionary = malloc(nlen*sizeof(WIDSIZE_T***));
	for(int l=3; l<=MAX_WORD_LEN; l++){
		dictionary[l] = malloc(npos*sizeof(WIDSIZE_T**));
		for(p=0; p<=l; p++){
			dictionary[l][p] = malloc(nbin*sizeof(WIDSIZE_T*));
			for(uint32_t b=0; b<nbin; b++){
				dictionary[l][p][b] = malloc(sizeof(WIDSIZE_T));
				dictionary[l][p][b][0] = 1;
			}
				
		}
	}
}
