

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

void add_dict(char* name, int npos, int nlen, int nalp)
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
}
static inline void add_db_word(int pos, int len, ibin, int wid)
{
	widAr = dict[pos][len][ibin];
	ele = &dic_ele[pos][len][ibin];
	if(*widAr == *ele){
		*ele <<= 1;
		widAr = dict[pos][len][ibin] = realloc(*ele);
	}
	widAr[*widAr-1] = wid;
}


add_or_del_dict_word(char* w, int wid, uint16_t n_parsing, char add_flg)
{
	int**** dict = dictionary->dict[did];
	ei = n_parsing--;//ending index	
	if(n_parsing>MAX_PARSING)	n_parsing = MAX_PARSING;
	if(add_flg){
		for(int j=2; j<n_parsing; j++)
			adding_dict_word(dict[j][len][WORD_POS_IND(w,j)], wid);
		adding_dict_word(dict[0][len][WORD_REV_IND(w,ei)], wid);
		adding_dict_word(dict[1][len]WORD_BEG_END_IND(w,ei)], wid);
	}
	else{
		for(int j=2; j<n_parsing; j++)
			deleting_dict_word(dict[j][len][WORD_POS_IND(w,j)], wid);
		deleting_dict_word(dict[0][len][WORD_REV_IND(w,ei)], wid);
		deleting_dict_word(dict[1][len]WORD_BEG_END_IND(w,ei)],wid);
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
{
	DicNode *nodeAr = malloc(MAX_NODES*sizeof(DicNode *));
	DicNode *root = NULL;
	DualDicNode *smallest = malloc(sizeof(DualDicNode));
	smallest->node = NULL;
	int total_nodes = 0;
	
	int*** dict = dictionary->dict[did];
	
	int parsed_ind = WORD_POS_IND(w, 0);
	Distance d = distance[len];
	
	int items_size = CHKED_ITEMS_SIZE;
	int n_items = 0;
	int *itemAr = malloc(CHKED_ITEMS_SIZE*sizeof(int));
	
	//cmpr_words_list(itemAr, &n_items, w, wlen);
	int max_parsing = cwlen;// means
	if(max_parsing>MAX_PARSING)	max_parsing = MAX_PARSING;
	int ei = cwlen-1;
	int sec_li = cwlen-2;
	for(int len=d.start; len<d.end; len++)
	{
		int* beginAr;
		for(int i=2; i<max_parsing; i++){
			beginAr = dictionary[i][len][PARSING_BEG_INDEX(w, i)];
			CMPR_WORDS_LIST()
		}
		
		if(cwlen<3){
			beginAr = dictionary[0][len][WORD_REV_IND(w, ei)];
			CMPR_WORDS_LIST()
		}
		else{
			//those whose last two characters are similar with this word.
			beginAr = dictionary[0][len][PARSING_BEG_INDEX(w, sec_li)];
			CMPR_WORDS_LIST()
			//compare the chunk of begining and ended character here.
			beginAr = dictionary[1][len][WORD_BEG_END_IND(w, li)];
			CMPR_WORDS_LIST()
			
			//reversing the first two and last two for three/four character words.
			if(cwlen<5)
			{
				beginAr = dictionary[2][len][WORD_REV_IND(w, 1)];
				CMPR_WORDS_LIST()			
				beginAr = dictionary[0][len][WORD_REV_IND(w, li)];
				CMPR_WORDS_LIST()
				if(cwlen == 4)
				{
					beginAr = dictionary[0][len][WORD_REV_IND(w, 2)];
					CMPR_WORDS_LIST()
				}
			}
		}		
	}
	while(root)
	{
		getGreatestNode (root, greatest);
		
		deleteGreatestNode(&root, greatest);		
	}
	
	me->nodeAr = nodeAr;
	me->total_nodes = total_nodes;
	//traverse root
}

#define CMPR_WORDS_LIST() \
{
	int total_parsed_ind = *beginAr;// LB belongs to length
	for(int j=1; j<total_parsed_ind; j++){
		CMPR_WORD_ITEM();
	}
			
}

#define CMPR_WORD_ITEM()
{
	//_....get hi here through beginAr
	//DualDicNode *smallest = malloc(sizeof(DualDicNode));
	char* hw = hi->key;
	CHLIMIT_T hwlen = hw->hwlen;
	long_ind = hi->id<<6;
	bit_ind = hi->id&63;
	bit_ind = 1<<bit_ind;
	if(flagsAr[long_ind] & bit_ind)	continue;
	if(!flagsAr[long_ind]){
		if(me->n_items == me->items_size){
				if(me->items_size)
					me->items_size <<= 1;
				else
					me->items_size = CMPR_ARRAY_SIZE;
				me->itemAr = realloc(me->items_size*sizeof(int));
			}
		me->itemAr[n_items++] = long_ind;
	}
	flagsAr[long_ind] |= bit_ind;
	
	//if(flagsAr[hi->id] & me->on_flag) continue;//already checke
	
	int ed = apply_edition(w, wlen, hw, hwlen, d.ed);
	//record dist if less than the recorded
	
	
	DicNode *node;
	if(total_nodes<MAX_NODES)
		node = nodeAr[total_nodes++] = malloc(sizeof(DicNode));
	else
	{	
		if(!greatest->node->ed)
			getSmallestNode(root, smallest);
		
		if(ed >= greatest->node->ed)	continue;
		deleteSmallestNode(&root, greatest);
		node = greatest->node;
		greatest->node = NULL;
	}
		
	node->ed = ed;
	node->di = hi;
	node->left = NULL;
	node->right = NULL;
	insert(&root, node);
	
	
	//record id, so that we will not check it again.
	
	
	
}

void reset_srch_flags(me)
{
	int nitem = me->nitem;
	int *itemAr = me->itemAr;
	for(int i=0; i<nitem; i++)
		flagsAr[itemAr[i]] &= 0ull;
	free(me->itemAr);
	me->itemAr = NULL;
	me->nitem = me->items_size = 0;
	
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

/*struct thread_eve
{
	me->itemAr = NULL;
	me->nitem = me->items_size = 0;
	
	me->nodeAr = nodeAr;
	me->total_nodes = total_nodes;
}*/