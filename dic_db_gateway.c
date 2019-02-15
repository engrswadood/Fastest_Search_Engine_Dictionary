#include "db_gateway.h"
MYSQL * get_connection()
{
	MYSQL *con = mysql_init(NULL);
	if (con == NULL)
	{
	  fprintf(stderr, "mysql_init() failed\n");
	  exit(1);
	}

	if (mysql_real_connect(con, HOST, USER, PASSWORD, 
	DATA_BASE, 0, NULL, 0) == NULL)
	{
	  finish_with_error(con);
	  con = NULL;	  
	}
	if (mysql_autocommit(mysql, FALSE))
	{
	  finish_with_error(con);
	  con = NULL;	  
	}
	return con;
}

void close_connection(MYSQL *con){
  mysql_close(con);
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  //exit(1); /// should not have an exit in case of more than one threads.      
}

int mysql_select_address(MYSQL *con, char *q)
{
	int rc = mysql_query(con, q);
	if (rc)	{ finish_with_error(con); return rc; }
}
int mysql_del_modify_words(MYSQL *con, char *q1, char *q2)
{
	int rc = mysql_query(con, q1);
	if(!rc) rc = mysql_query(con, q2);
	if (rc)	mysql_rollback(con);
	else	rc = mysql_commit(con);
	if (rc)	finish_with_error(con); 
	return rc;
}
int mysql_add_words(MYSQL *con, char *q)
{
	int rc = mysql_query(con, q);
	if (rc)	mysql_rollback(con);
	else	rc = mysql_commit(con);
	if (rc)	finish_with_error(con); 
	return rc;
}
/*void mysql_update_words(MYSQL *con, char *q)
{
	if (mysql_query(con, q))      finish_with_error(con);
}*/


//int rc = mysql_insert_words(query_data->sqlcon, q_str);
//int rc = mysql_del_modify_words(query_data->sqlcon, q_str1, q_str2);
load_dictionary_db(n_pos, n_len, n_alpha)
{
	
	loop through dic_tbl
	{
		//add_dict(char* name, int npos, int nlen, int nalp);
		//loop through word_stat_did_tbl
		{
			
		}
		//dic[pos][len][ibin][wid]
		nbin = nalp*nalp+nalp+1;
		dictionary[ndic] = malloc(npos*sizeof(WIDSIZE_T***));
		for(int p=0; p<npos; p++){
			dic_ele[ndic][p] = malloc(nlen*sizeof(WIDSIZE_T**));
			for(int l=0; l<nlen;l++){
				dic_ele[ndic][p][l] = calloc(nbin*sizeof(WIDSIZE_T*));		
			}		
		}
	
		//loop from sql_record-set
		{
			//add to dual_table
			int n_parsing = strlen(w);
			ei = n_parsing--;//ending index	
			if(n_parsing>MAX_PARSING)	n_parsing = MAX_PARSING;
			
			int ibin; int* widAr; int *ele;
			for(int j=2; j<n_parsing; j++)
				add_db_word(len, j, WORD_POS_IND(w,j), wid);
			add_db_word(len, 0, WORD_REV_IND(w,ei), wid);
			add_db_word(len, 1, WORD_BEG_END_IND(w,ei), wid);
		}
	}
}

void load_address_db()
{
	MYSQL *con = get_connection();
	
	mysql_select_address(con, "select count(*) total from address_tbl;");	
	MYSQL_RES *result = mysql_store_result(con);
	if (result == NULL)   finish_with_error(con);
	//int num_fields = mysql_num_fields(result);
	MYSQL_ROW row;
	row = mysql_fetch_row(result);
	
	unsigned int total_records = row[0];
	unsigned int rem_records = total_records;
	
	unsigned offset = 0;
	char *sel_query =  malloc(140);
	char *limit_str = malloc(21);
	char *offset_str = malloc(21);
	
	strcpy(sel_query, "SELECT id, keys, pos, len FROM address_tbl");
	total_record_sets = 4;
	//accumulative_size = (total_queries*(total_queries+1))/2;
	
	int q_size = strlen(sel_query);
	for(int i=0; i<total_record_sets; i++)
	{
		if(offset >= total_records)	break;
		
		int csize = q_size;
		unsigned int limit	= rem_records>>1;
		rem_records		>>=	1;
		
		if(rem_records)
		{
			strcpy(q+csize, " LIMIT ");		csize += 7;
			limit_str = itoa(limit, limit_str, 10);
			strcpy(q+csize, limit_str);	csize += strlen(limit_str);	
		}
		strcpy(q+csize, " OFFSET ");		csize += 8;
		offset_str = itoa(offset, offset_str, 10);
		strcpy(q+csize, offset_str);	csize += strlen(offset_str);
		
		offset += limit;
		
		mysql_select_address(sq->qry_rply);	
		MYSQL_RES *result = mysql_store_result(con);
		if (result == NULL)   finish_with_error(con);
		int num_fields = mysql_num_fields(result);
		MYSQL_ROW row;
		
		while ((row = mysql_fetch_row(result))) 
		{
			//unsigned int b =READ_LE4(q_val);
			//unsigned long long int id = READ_LE4(q_val);
			//id = id<<32|b;
			//order of columns id, keys, pos, len
			ad_add_address(address_tbl, atoll(row[0]), row[1], row[2], atoi(row[3]));
		  //for(int i = 0; i < num_fields; i++) 
			 // printf("%s ", row[i] ? row[i] : "NULL");
		  strcat(reply, row[0]);//
		  strcat("\n");
		}
		mysql_free_result(result);
	}
	
	free(sel_query);
	free(limit_str);
	free(offset_str);
	
	
	mysql_close(con);
}
