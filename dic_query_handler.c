//keys_len, keys, id_bool, id, total_suggesting arrays, suggesting arrays (each array ends with NULL/0 Integer, threshold in case of web search//select
// id should come first.

srv --- sent there keys only.

//*********INPUT*****************//
//Search-> words only.
//Add-> 
//*********OUTPUT****************//
//Search-> id_index, total_group_arrays, group_ars, id, keys_len, keys, total_sugg, sug_ids
//Added->int
//Deleted-> int

void init_query_handler(Thread* thr)
{ 

	switch(thr->op_mode) {
    case SEARCH_QUERY:
		search_dic_words(thr);
		break;
    case ADD_QUERY:
		add_dic_words(thr);
		break;
    case DELETE_QUERY:
		del_dic_words(thr);
		break;
    case UPDATE_QUERY:
		update_dic_words(thr);
        break;
    default:
        fprintf(stderr, "Can not handle operation.%d\n", thr->op_mode);
        //assert(0);
    }
	//thr->search_page is the search page.
}





//0
WIDSIZT_T add_dic_words(Thread* thr)
{//For addation and deletion there should be another layer of authentication.
	
	char**	keyAr = malloc(MAX_WORDS*sizeof(char*));
	CHLIMIT_T*	lenAr = malloc(MAX_WORDS*sizeof(CHLIMIT_T));
	int wlen = get_words_list(thr->usr_q, thr->usr_bytes_n, keyAr, lenAr);//(keyAr, dicAr, words);
	WIDSIZE_T* widAr = malloc(wlen*sizeof(WIDSIZE_T));
	
	//uint64_t grp = get_grp_from_db(thr->grp, thr->grp_len);//!grp belong only to dic

	size_t size = 200;
	char *q_str = malloc(size);
	strcpy(q_str, "INSERT INTO wid_tbl (wid, grp) values");
	uint32_t csize = strlen(q_str);

	char* wid_str = malloc(22);
	
	//char* grp_str = malloc(22);//!grp belong only to dic
	//char* wid_str = malloc(22);//!grp belong only to dic
	//grp_str = itoa(grp, grp_str, 10);//!grp belong only to dic
	//uint32_t grp_len = strlen(grp_str);//!grp belong only to dic
	
	
	for(int i=0; i<wlen; i++)
	{
		WIDSIZT_T	wid = 0;
		uint32_t rsize;
		uint32_t dml_type;
		wid = increment_dual_item_by_str(dtable, grp, keyAr[i], lenAr[i]);
		if(!wid)// if dual-item does not exist then check for vacant wid.
		{
			wid = add_vacact_item(dtable, grp, keyAr[i], lenAr[i]);
			if(!wid)// if vacant wid(dual-item) does not exist then create new one.
				wid = add_dual_item(dtable, grp, keyAr[i], lenAr[i]);
			add_or_del_dict_word(keyAr[i], wid_deleted, lenAr[i], 0);//Re-entry of wid or 1st time wid entry.
		}
		widAr[i] = wid;
		wid_str = itoa(wid, wid_str, 10);
		uint32_t wid_len = strlen(wid_str);
		
		rsize = csize+grp_len+wid_len+6+41;//+6 for "(",  ",",  ")",  ";",  "\0"
		INC_MEM_IF_REQ(q_str, size, rsize);
		strcpy(q_str+csize, "(");			csize++;
		strcpy(q_str+csize, wid_str);		csize += wid_len;
		strcpy(q_str+csize, ",");			csize++;
		//strcpy(q_str+csize, grp_str, grp_len);		csize += grp_len;//!grp belong only to dic
		strcpy(q_str+csize, "),");			csize += 2;
	}
	char* endstr = q_str+csize-1;
	strcpy(endstr, " ON DUPLICATE KEY UPDATE total = total+1;")
	
	int rc = mysql_insert_words(query_data->sqlcon, q_str);
	if(rc){
		for(int i=0; i<wlen; i++)
			increment_dual_item_by_num(dtable, widAr[i]);
	}
	thr->adding_keyAr	= keyAr;//these 3 stmts for search enging cache only as these words are need for cache.
	thr->adding_lenAr	= lenAr;
	thr->adding_len		= wlen;
	//free(keyAr);// these 2 should be uncommented in case if dic becomes independent.
	//free(lenAr);
	free(q_str);
	free(wid_str);
	//free(grp_str);
	thr->widAr = widAr;
	
	/*char** buf =  &thr->buf;
	*buf = wids_to_bytes(widAr, wlen);
	//buf += wlen*sizeof(WIDSIZE_T);
	memcpy(buf, qval,4*wlen);*/
}

void del_dic_words(Thread* thr)
{
	char**	keyAr = malloc(MAX_WORDS*sizeof(char*));
	CHLIMIT_T*	lenAr = malloc(MAX_WORDS*sizeof(CHLIMIT_T));
	
	int wlen = get_words_list(thr->usr_q, thr->usr_bytes_n, keyAr, lenAr);
	WIDSIZE_T* widAr = malloc(wlen*sizeof(WIDSIZE_T));
	
	//uint64_t grp = get_grp_from_db(thr->grp, thr->grp_len);//!grp belong only to dic
	
	uint32_t size1 = 200;
	char *q_str1 = malloc(size1);
	strcpy(q_str1, "UPDATE wid_tbl SET total=total+1 WHERE wid=");
	uint32_t csize1 = strlen(q_str);
	
	uint32_t size2 = 200;
	char *q_str2 = malloc(size2);
	strcpy(q_str2, "DELETE FROM wid_tbl WHERE wid IN (");
	uint32_t csize2 = strlen(q_str2);
	
	char* or_str = " OR wid=";
	uint8_t or_len = strlen(or_str);
	
	//char* grp_str = malloc(22);//!grp belong only to dic
	//char* wid_str = malloc(22);//!grp belong only to dic
	//grp_str = itoa(grp, grp_str, 10);//!grp belong only to dic
	//uint32_t grp_len = strlen(grp_str);//!grp belong only to dic
	
	for(int i=0; i<wlen; i++)
	{
		
		uint32_t rsize;
		//check that grp must exists other wise log the error.
		DualNode* dn = get_ditem_by_str(dtable, keyAr[i], lenAr[i]);
		if(!dn){
			// log the error and don't execute sql statement.
			break;// exit thread//_
		}
		WIDSIZT_T	wid = dn->wid;
		widAr[i] = wid;
		wid_str = itoa(wid, wid_str, 10);
		uint32_t wid_len = strlen(wid_str);
		
		if(dn->total>1)//decrement
		{//updating the wid group del_wid total with decrement.
			rsize = csize1+wid_len+11+grp_len+or_len;
			
			INC_MEM_IF_REQ(q_str1, size1, rsize);
			strcpy(q_str1+csize1, wid_str);			csize1 += wid_len;
			//strcpy(q_str1+csize1, " AND group=");	csize1 += 11;//!grp belong only to dic
			//strcpy(q_str1+csize1, grp_str);			csize1 += grp_len;//!grp belong only to dic
			strcpy(q_str1+csize1, or_str);			csize1 += or_len;
		}
		else//delete
		{
			rsize = csize2+wid_len+3;
			INC_MEM_IF_REQ(q_str2, size2, rsize);
			strcpy(q_str2+csize2, wid_str);			csize2 += wid_len;
			strcpy(q_str2+csize2, ", ");			csize2 += 2;
		}
	}
	
	strcpy(q_str1+csize1-or_len, ";");
	strcpy(q_str2+csize2-2, ");");
	
	
	int rc = mysql_del_modify_words(query_data->sqlcon, q_str1, q_str2);
	if(rc){
		for(int i=0; i<wlen; i++)
			decrement_dual_item_by_num(dtable, widAr[i]);
	}
	thr->deleting_keyAr	= keyAr;//these 3 stmts for search enging cache only as these words are need for cache.
	thr->deleting_lenAr	= lenAr;
	thr->deleting_len	= wlen;
	
	//free(keyAr);
	//free(lenAr);
	free(qstr1);
	free(qstr2);
	free(wid_str);
	//free(grp_str);
	
	thr->widAr = widAr;
}

void search_dic_words(Thread* thr)// this could be maximum.
{//id, id, keys_len, keys, n_sugg_ars, sug_idArs, threshold in case of web search//select
	//id_index, total_group_arrays, group_ars, id, keys_len, keys, n_sugg_ars, sug_idArs

	//uint64_t*	corgAr	= thr->corgAr;//!grp belong only to dic
	//size_t cgi = 0;//!grp belong only to dic
	
	char* usr_q = thr->usr_q;
	DualNode** srch_twinAr = DualNode* 
	
	size_t key_len = 0;
	wordAr[key_len] = usr_q;
	size_t usr_len = thr->usr_bytes_n;

	size_t ub = usr_len-1;
	for(int i=1; i<usr_len; i++)
	{
		if(usr_q[i] == CH_SEPERATOR)
		{
			W_CHLIM_T len = j*sizeof(CH_TYPE_T);
			
			DualNode* dn = get_ditem_by_str(htblAr[did], wordAr[key_len], len);
			if(dn)
			{
				//corgAr[cgi++] = dn->grp;//!grp belong only to dic
				srch_twinAr[key_len] = dn;
			}
			else
			{
				srch_twinAr[key_len] = NULL;
				msw_indAr[thr->n_msw++] = key_len;//_
				suggest_spell(wordAr[key_len], len, thr);
			}	
			if(i<ub) wordAr[++key_len] = usr_q+i;
			j=-1;
		}
		j++;
	}
	thr->key_len = key_len;
	
}
//srch_widAr, add_widAr, del_widAr
void update_dic_words(Thread* my)
{
	add_dic_words(my);
	
	thr->usr_q = thr->upd_q;//	THE WORDS TO BE INSERTED or DELETED.
	thr->usr_bytes_n = thr->->upd_bytes_n;
	thr->grp = thr->upd_grp;//	THE WORDS TO BE INSERTED or DELETED.
	thr->grp_len = thr->upd_grp_len;
	del_dic_words(my);
	convert_to_CorObj(my);
}
void suggest_spell(Thread* thr, char*w, uint16_t len)
{
	srch_msw_in_dict(w, len);
	size_t size = thr->dic_tree_size+1;// the first index will have the length of elements.
	
	swArs = realloc(thr->n_msw*sizeof(WIDSIZT_T*));
	smArs = realloc(thr->n_msw*sizeof(uint16_t*));
	//sgArs = realloc(thr->n_msw*sizeof(uint64_t));//!grp
	
	inorder_write_desc(me);
}
// 



void get_grp_from_db(char* grp, uint16_t grp_len)//!grp belong only to dic
{
	sql_q = //__
	strcpy(sql_q, "select * from group_tbl where group_word=\"")
	strncpy(sql_q, grp_str, grp_len);
	strcpy(sql_q, "\"");
}




////////////////////////////////////////////////
////////////////////////////////////////////////


/*uint16_t ifloor_of_2 (uint16_t x)
{
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
	//x = x | (x >> 16);// for uint32_t
    return x - (x >> 1);
}


 
void cl_generate_app_alph()
{
	alplen++;
	n = 7*alplen;
	n = ifloor_of_2(n)-1;
	ALPHA_T new_alphabets = malloc(sizeof(Alphabet)*(n+1));// one extra byte for terminator.
	for(int i=0; i<n; i++) new_alphabets[i].value = new_alphabets[i].cmp = CH_TYPE_MAX;
	
	for(int i=0; i<alplen; i++)
	{
		int value = READ_ALPH(q);
		int lvalue = convert_to_lower(value);
		
		new_alphabets[i].value	= lvalue;
		new_alphabets[i].cmp	= value;
	}
}
void usr_convert_to_app_alph()
{
	for(int i=0; i<len; i++)
	{
		int h = READ_ALPH(q);
		h = h&CH_TYPE_MAX;
		if(alphabets[h].byte_len != byte_len  ||  strncmp(alphabets[h].cmp, ch_bytes, byte_len ))
		{	while(alphabets[h].value != CH_TYPE_MAX && (alphabets[h].byte_len != byte_len  ||  strncmp(alphabets[h].cmp, ch_bytes, byte_len ))) h++;	}
		alpAr[i] = alphabets[h].value;
	}
}*/


