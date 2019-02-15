

typedef struct {
			uint16_t vlen;
			uint8_t operation;
			uint8_t dml_key;
			
        } ReqHeader;
typedef struct {
			uint16_t vlen;
            uint8_t operation;
			uint8_t err;
        } ResHeader;

//dictionary[pos][len][bin]
//"table1 bin, total"///"
 //((((word_stat_did//pos, wlen, bin, total)))))//not used any more






struct Dictionary
{
	int *****dict;
	char **name;
	int *npos;
	int *nlen;
	int *nalp;
	int ndict
};
typedef struct Dictionary Dictionary;

/*void add_dict(char* name, int npos, int nlen, int nalp)
{
	//add dic in mysql first.
	
	int n = dictionary->ndict+1;
	realloc(dictionary->dict, n*sizeof(int***));
	realloc(dictionary->name, n*sizeof(char*));
	realloc(dictionary->npos, n*sizeof(int));
	realloc(dictionary->nlen, n*sizeof(int));
	realloc(dictionary->alph, n*sizeof(int));
	n--;
	dictionary->name[n] = name;//name//it is also nth dictionary of dic array
	dictionary->npos[n] = npos;//second subscript of dic array
	dictionary->nlen[n] = nlen;//third subscript of dic array
	dictionary->nalp[n] = nalp;//4th subscript of dic array
	
	int*** dict = dictionary->dict[n];
	for(int p=0; p<npos; p++){
		dict[i] = malloc(nlen*sizeof(int**));
		for(int l=0; l<nlen;l++){
			dict[i][l] = malloc(nalp*sizeof(int*));
			for(int a=0; a<nalp; a++)
				dict[i][l][a] = calloc(1, sizeof(int));			
		}		
	}
	
	dictionary->ndict++;
}*/
static inline void add_db_word(int len, int pos, ibin, int wid)
{
	widAr = dict[len][pos][ibin];
	ele = &dic_ele[pos][len][ibin];
	if(*widAr == *ele){
		*ele <<= 1;
		widAr = dict[len][pos][ibin] = realloc(*ele);
	}
	widAr[*widAr-1] = wid;
}


add_or_del_dict_word(char* w, int wid, uint16_t len, char add_flg)
{
	int**** dict = dictionary->dict[did];//_
	ei = len-1;//ending index
	sec_ei = len-2;
	if(sec_ei>TOTAL_CONTINUOUS_POSES)	sec_ei = TOTAL_CONTINUOUS_POSES;
	if(add_flg){
		for(int j=0; j<sec_ei; j++)
			adding_dict_word(dict[len][j+2][WORD_POS_IND(w,j)], wid);
		adding_dict_word(dict[len][0][WORD_POS_IND(w,sec_ei)], wid);
		adding_dict_word(dict[len][1]WORD_HT_IND(w,ei)], wid);
	}
	else
	{
		for(int j=0; j<sec_ei; j++)
			deleting_dict_word(dict[len][j+2][WORD_POS_IND(w,j)], wid);
		deleting_dict_word(dict[len][0][WORD_POS_IND(w,sec_ei)], wid);
		deleting_dict_word(dict[len][1]WORD_HT_IND(w,ei)],wid);
	}
}

deleting_dict_word(int* widAr, int id)
{
	int len = *widAr;
	for(int m=1; m<len; m++){
		DualItem *di = get_dual_item_by_int(dict_table, widAr[m]);
		if(di->id == widAr[m]) break;
	}
	
	if(widAr[m] != id) return;// not found
		
	int ub = *widAr-1;
	for(int i=m; i<ub; i++)//deleting
		widAr[i] = widAr[i+1];
	*widAr--;
	realloc(widAr, *widAr*sizeof(int));
}


adding_dict_word(int* widAr, int id)
{
	*widAr++;
	realloc(widAr, *widAr*sizeof(int));
	widAr[*widAr-1] = id;	
}

srch_msw_in_dict(CHSIZE_T* w, uint16_t cwlen)
{// for 2 letter word, ab,ba/ab,ba,bc,cb,ac

	
	fw_marks	= FORWARD_SMALL_LENGTH_MARKS-10<<;
	bw_marks	= BACKWARD_SMALL_LENGTH_MARKS; 

	/////////////////////////////////////
	if(cwlen>MAX_WORD_LEN){
		w[MAX_WORD_LEN-2] = w[cwlen-2];
		w[MAX_WORD_LEN-1] = w[cwlen-1];
		cwlen = MAX_WORD_LEN;
	}
	
	//////////////////////////////////	
	uint16_t len_start	= vstartA[cwlen];
	uint16_t len_end	= vendAr [cwlen];

	int n_poses = cwlen-2;// means
	if(!n_poses)	n_poses = 1;
	////////////////////////////////////

	WIDSIZE_T wInd = 0;
	for(int dwlen=len_start; dwlen<len_end; dwlen++)
	{
		dif = dwlen - cwlen;
		dif = ABS_FOR_INT(dif);
		fw_marks	= FORWARD_LENGTH_MARKS-(dif<<3);
		bw_marks	= BACKWARD_LENGTH_MARKS-(dif<<2);
		/*if(dwlen == cwlen)
		{
			fw_marks	= FORWARD_BIG_LENGTH_MARKS;
			bw_marks	= BACKWARD_BIG_LENGTH_MARKS;
		}
		else if(dwlen > cwlen)
		{
			fw_marks	= FORWARD_EQUAL_LENGTH_MARKS;
			bw_marks	= BACKWARD_EQUAL_LENGTH_MARKS;
		}*/
		
			
		for(int i=0; i<n_poses; i++)
		{
			CHLIMIT_T pos_end = pos_endAr[i];
			if(pos_end>dwlen-2)	pos_end = dwlen-2;
			
			
			int j = i+1;
			//*************
			CHLIMIT_T k=pos_startAr[i];//it was pos_startAr[i]-1
			//binAr[len][i] = malloc((pos_end - k) * sizeof(WIDSIZE_T*));
			st_pos = wInd;
			while(k<pos_end)//binAr[pos][wind]// check for repeation.
			{
				//int pos_dif = (i>k)? i-k : k-i;//__
				binAr[wInd] = dictionary[dwlen][k+2][WORD_BEG_IND(w, i)];
				marksAr[wind++] = fw_marks;
				
				k++;
				binAr[wInd++] = dictionary[dwlen][k+2][WORD_REV_IND(w, j)];
				marksAr[wind++] = bw_marks;
			}
			//********************
			HANDLE_DUPLICATED_CHUNKS_MARKS()
			APPEND_WORD_POS_SCORE()
			//**********************	
		}
		
		APPEND_HEADER_FORWARDING_SCORE()	//chunk of firs two chars.
		APPEND_HEADER_BACKWARDING_SCORE() //Transposed chunk of 1st two chars.
		if(dwlen<3)	continue;
		//*******************************************//
		k=cwlen-2;//k is now 2nd last index.
		APPEND_TAIL_FORWARDING_SCORE() //chunk of last two chars.
		k++;//k is now ending index.
		APPEND_TAIL_BACKWARDING_SCORE() //Transposed chunk of last two chars.
		//*******************************************
		//Begining and Ending chunk HT.
		APPEND_HEADER_AND_TAIL_SCORE() // chunk of 1st and last char.
	}
	get_prioritized_wids(binAr, emptyAr);
	//apply_ed_to_wids(root);
	
}


void get_prioritized_wids(WIDSIZE_T** binAr, n_bins)
{
	DicNode *nodeAr = malloc(MAX_NODES*sizeof(DicNode *));
	TwinDicNode *smallest = NULL;
	uint32_t marks_limit1 = LOWER_LIMIT*larger;
	uint32_t marks_limit2 = UPPER_LIMIT*larger;
	int nodes_n = 0;
	
	for(WIDSIZE_T i=0; i<n_bins; i++)
	{
		WIDSIZE_T* widAr = binAr[i];
		WIDSIZE_T total = *widAr;
		for(WIDSIZE_T j=1; j< total; j++){
			WIDSIZE_T wid = widAr[j];
			marks = scoreAr[wid&AI_BITS][wid&EI_BITS];
			if(marks)
			{
				scoreAr[wid&AI_BITS][wid&EI_BITS] = 0;
				if(marks>marks_limit1)
				{//
					DicNode* node;
					if(nodes_n<max_nodes)
						node = nodeAr[nodes_n++]=malloc(sizeof(DicNode));
					else
					{
						if(marks>marks_limit2)
						{
						  max_nodes++;// <<= 1;//*=2;
						  nodeAr=realloc(max_nodes*(sizeof(DicNode*)));
						  node=nodeAr[nodes_n++]=malloc(sizeof(DicNode));
						}
						else
						{
							
							if(!smallest)
							{
								smallest = malloc(sizeof(TwinDicNode));
								get_smallest_node(root, smallest);
							}
							else if(marks<smallest->node->marks)
								continue;
							del_smallest_node(&root, smallest);
							node = smallest->node;
							get_smallest_node(root, smallest);
						}		
					}
					node->marks = marks;
					node->wid 	= wid;
					node->group = group;
					node->left = NULL;
					node->right = NULL;
					insert(&root, node);
				}
			}
		}
	}
	thr->dic_tree_size = nodes_n;
}

void apply_ed_to_wids(DicNode* root)
{
	
}
	
bool set_group_bit(char *word, char group)
{
	for (size_t i = 0; i<maxdic; ++i)
	{
		struct hentry* he = pHMgr[i]->lookup(word);
		if(he)
		{
			he->group |= (1<<group);// group range is 0-63
			return true;
		}
	}
	return false;
}
bool unset_group_bit(char *word, char group)
{
	for (size_t i = 0; i<maxdic; ++i)
	{
		struct hentry* he = pHMgr[i]->lookup(word);
		if(he)
		{
			he->group &= ~(1ull <<group);
			return true;
		}
	}
	return false;
}
