#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#define IND_ANDING 3

#define LIMIT_OFF_BITS (0xFFFFFFFF^IND_ANDING)
#if	!(IND_ANDING >> 2)
	#define IND_SHIFTING 2
#elif	!(IND_ANDING >> 3)
	#define IND_SHIFTING 3
#elif !(IND_ANDING >> 4)
	#define IND_SHIFTING 4
#elif !(IND_ANDING >> 10)
	#define IND_SHIFTING 10
#elif !(IND_ANDING >>11)
	#define IND_SHIFTING 11
#elif !(IND_ANDING >> 12)
	#define IND_SHIFTING 12
#elif !(IND_ANDING >> 13)
	#define IND_SHIFTING 13
#elif !(IND_ANDING >> 14)
	#define IND_SHIFTING 14
#elif !(IND_ANDING >> 15)
	#define IND_SHIFTING 15
#elif !(IND_ANDING >> 16)
	#define IND_SHIFTING 16
#endif

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
struct DualNode{
	struct DualNode *_next;//next
	CHSIZE_T *str;//w
	int num;//wid
	char chlen;
	int n;//tot_and_frequently_missspelled.
	
};
typedef struct DualNode DualNode;

struct DualAssocArray{
	struct	DualItem	**intArs;//multipleAr
	short 				intArsLen;//intArsLen
	int					cur;
	
	struct	DualItem	***hArs;
	short 				hArsLen;//
	int					hTotalBuc;
	
	int					_biggestSimilarWords;
	////////
	WIDSIZE_T			top;
	WIDSIZE_T*			stack;
};
typedef struct DualAssocArray DualAssocArray;


void print_dual_item(DualNode *, int );
int str_hash(int , CHLEN_T*, CHLEN_T);
void resize_dtbl_int_array(DualAssocArray *);
void add_dual_item(DualAssocArray *, char *);
void delete_dual_item_by_str(DualAssocArray *, char* );
DualNode * get_ditem_by_num(DualAssocArray *, int );
DualNode * get_ditem_by_str(DualAssocArray *, char * );
unsigned int get_total_dual_items(DualAssocArray *);
void traverse_dual_tbl(DualAssocArray *);
DualAssocArray* create_dual_tbl(int );

void print_dual_item(DualNode *item, int i)
{
	printf("\nind=%d\t", i);
	printf("intID=%d\t", item->num);
	printf("strID=%s\t\t", item->str);
	printf("similar=%d", item->n);
}

int str_hash(int size, CHLEN_T *s, CHLEN_T chlen)// size must be N^2 - 1.
{
	char *key =  s;
	unsigned long int h = (unsigned long int)*s;
	for(int i=1; i<chlen; i++)
	h = (h << 5) - h + (unsigned long int)*s;
	//int temp = (int)h%size;
	//printf("\n%s  %lu  %d\n\n", key, h, temp);
	return h&size;//_ can be optimized if size is N^2 - 1.
}


void resize_dtbl_str_array(DualAssocArray *ht)
{
	//if(ht->delAddMode>-1) return;
	//ht->delAddMode = 1;
	int rhArsLen == ht->hArsLen<<1;
	ht->hArs = realloc(rhArsLen * sizeof(DualNode**));
	for(int j=hArsLen; j<rhArsLen; j++)
		ht->hArs[j] = calloc((IND_ANDING+1) * sizeof(DualNode*));
	///////////////////////////////////
	int len	 = IND_ANDING+1;
	int rSize = rhArsLen<<IND_SHIFTING;
	for(int j=0; j<ht->hArsLen; j++)
	{
		for(k=0; k<len; k++)
		{
			DualNode *item = hArs[j][k];
			hArs[j][k] = NULL;
			while(item)
			{
				DualNode *nitem = item->next;
				int i = str_hash(rSize, item->str, item->chlen);
				item->_next = hArs[i>>IND_SHIFTING][i&IND_ANDING];
				hArs[i>>IND_SHIFTING][i&IND_ANDING] = item;
				item = nitem;
			}
		}	
	}
	ht->hArsLen = rhArsLen;
	ht->hTotalBuc = rSize;
}

void resize_dtbl_int_array(DualAssocArray *ht)
{
	ht->intArs = realloc((ht->intArsLen+1) * sizeof(DualNode *));
	ht->intArs[ht->intArsLen++]=malloc((IND_ANDING)*sizeof(DualNode));
	ht->cur = 0;
}
void decrement_dual_item_by_num(DualAssocArray *ht, int i) {
	DualNode *it = ht->intArs[i>>IND_SHIFTING][i&IND_ANDING];
	it->total--;
}
void increment_dual_item_by_num(DualAssocArray *ht, int i) {
	DualNode *it = ht->intArs[i>>IND_SHIFTING][i&IND_ANDING];
	it->total++;
}

uint32_t increment_dual_item_by_str(DualAssocArray *ht, uint64_t grp, char *key,CHLEN_T chlen)
{
	DualNode *it = get_ditem_by_str(ht, key);
	WIDSIZE_T wid = 0;
	if(it){
		it->total++;
		it->grp |= grp;
		wid = it->wid;
	}
	return wid;
}
uint32_t add_vacact_item(DualAssocArray *ht, uint64_t grp, char *key,CHLEN_T chlen)
{
	WIDSIZE_T wid = 0;
	if(setting.dml_server)
		wid = add_ditem_with_wid(ht, key, chlen);
	return wid;
}
uint32_t add_dual_item(DualAssocArray *ht, uint64_t grp, char *key, CHLEN_T chlen)
{
	//int total, i=0, j=0;

	
	DualNode  ***hArs = ht->hArs;
	
	int i = str_hash(ht->hTotalBuc, key, chlen);//_ strSize 
	
	

	int ar_ind = ht->intArsLen-1;
	DualNode *adding_item = &ht->intArs[ar_ind][ht->cur++];
	adding_item->wid = (ar_ind<<IND_SHIFTING) + ht->cur-1;
	//printf("\n%d",(ar_ind<<IND_SHIFTING));
	//printf("\nintid=%d<::: cur_index=%d  ::::>strid=%s   totalArs=%d",adding_item->num, ht->cur-1,key, ht->intArsLen);
	if(ht->cur > IND_ANDING)
		resize_dtbl_int_array(ht);
	
	
	adding_item->str = key;
	adding_item->chlen = chlen;
	adding_item->_next = hArs[i>>IND_SHIFTING][i&IND_ANDING];
	hArs[i>>IND_SHIFTING][i&IND_ANDING] = adding_item;
	
	return adding_item->num;
}

DualNode* delete_dual_item_by_str(DualAssocArray *ht, char* strKey,CHLEN_T chlen)
{
	int i = str_hash(ht->hTotalBuc, strKey, chlen);
	DualNode *last_item = NULL;
	DualNode  ***hArs = ht->hArs;
	DualNode *item = hArs[i>>IND_SHIFTING][i&IND_ANDING];
	
	while(item)
	{
		if(item->chlen == chlen  &&  !strncmp(strKey, item->str, chlen ))	break;
		last_item = item;
		item = item->_next;
	}
	
	if(!item) return 0;
	item->total--;
	if(item->total) return 1;
	
	
	
	int last_wid = ((ht->intArsLen-1)<<IND_SHIFTING) + ht->cur-1;
	if(last_wid==item->wid)
	{
		if(ht->cur)	ht->cur--;
		else
		{
			ht->cur = IND_ANDING;
			ht->intArsLen--;
			free(ht->intArs[intArsLen]);
			ht->intArs = realloc(ht->intArsLen * sizeof(DualNode*));
		}
	}
	
	*del_wid = item->wid;
	ht->intArs[i>>IND_SHIFTING][i&IND_ANDING]
	push_empty_index(ht->stack, &ht->top, item->wid);
		
	if(last_item) last_item->_next = item->_next;
	else hArs[i>>IND_SHIFTING][i&IND_ANDING] = item->_next;
	free(item->str);
	item->str = NULL;
	return 2;
}




/* Retrieve a key-value pair from a hash table. */

DualNode* get_ditem_by_num(DualAssocArray *ht, int i) {
	return &ht->intArs[i>>IND_SHIFTING][i&IND_ANDING];
}

DualNode* get_ditem_by_str(DualAssocArray *ht, char *strKey,CHLEN_T chlen)
{
	int i = str_hash(ht->hTotalBuc, strKey, chlen);
	DualNode *item = ht->hArs[i>>IND_SHIFTING][i&IND_ANDING];
	while(item)
	{
		if(item->chlen == chlen && !strncmp( strKey, item->str, chlen))		break;
		item = item->_next;
	}
	return item;
}

unsigned int get_total_dual_items(DualAssocArray *ht)
{
	return ht->cur + ((ht->intArsLen-1)<<IND_SHIFTING);
}

void push_empty_index(WIDSIZE_T* stack,WIDSIZE_T* top, WIDSIZE_T wid)
{
	stack = realloc(stack, (*top+1)*sizeof(WIDSIZE_T));
	stack[*top++] = wid;
}
WIDSIZE_T pop_empty_index(WIDSIZE_T* stack,WIDSIZE_T* top)
{
	WIDSIZE_T index = 0;
	if(*top)
	{
		index = stack[--*top];
		if(*top)
			stack = realloc(stack, *top*sizeof(WIDSIZE_T));
		else
		{
			free(stack);
			stack = NULL;
		}
	} 
	return index;
}

WIDSIZE_T add_ditem_with_wid(DualAssocArray* ht, char* w, CHLEN_T chlen)
{
	

	WIDSIZE_T wid = pop_empty_index(ht->stack, &ht->top);
	if(wid){
		DualNode *hitem = get_ditem_by_num(ht, wid);
		hitem->num = wid;
		hitem->str = w;
		hitem->_tolal = 1;
		WIDSIZE_T i = str_hash(ht->hTotalBuc, key, chlen);
		WIDSIZE_T x = i>>IND_SHIFTING;
		WIDSIZE_T y = i&IND_ANDING;
		hitem->_next = ht->hArs[x][y];
		ht->hArs[x][y] = hitem;
	}
	return wid;
}
//increment_ditem_counter
//add_ditem_with_wid
//get_from_vacant_list
//add_to_vacant_list
void traverse_dual_tbl(DualAssocArray *ht)
{//
	printf("\n************************************* **************");
	
	
	printf("\ntotal************************************ **************%d", ht->hTotalBuc);
}


DualAssocArray* create_dual_tbl(int size)
{
	DualAssocArray *ht = malloc(sizeof(DualAssocArray));
	ht->hArs =  malloc(size * sizeof(DualNode**));
	ht->hArsLen = size;
	for(int j=0; j<size; j++)
		ht->hArs[j] = malloc((IND_ANDING+1) * sizeof(DualNode*));
	
	ht->intArs =  malloc(sizeof(DualNode*));
	ht->intArs[0] = malloc(size*sizeof(DualNode));
	
	
	
	ht->intArsLen = 1;
	ht->cur = 0;
 
	ht->hTotalBuc = size<<IND_SHIFTING;
	ht->_biggestSimilarWords = 0;
	
	ht->top = 0;
	ht->stack = NULL;
	
	
	return ht;
}




int main( int argc, char **argv ) {

	DualAssocArray *hashtable = create_dual_tbl(7);
	

	
char **strings;
strings = malloc(15*sizeof(char *));
strings[0] = malloc(20);
strings[1] = malloc(20);
strings[2] = malloc(20);
strings[3] = malloc(20);
strings[4] = malloc(20);
strings[5] = malloc(20);
strings[6] = malloc(20);
strings[7] = malloc(20);
strings[8] = malloc(20);
strings[9] = malloc(20);
strings[10] = malloc(20);
strings[11] = malloc(20);
strings[12] = malloc(20);
strings[13] = malloc(20);
strings[14] = malloc(20);


strcpy(strings[0],"0bslam");
strcpy(strings[1],"1bslam");
strcpy(strings[2], "2cslam");
strcpy(strings[3], "3dslam");
strcpy(strings[4], "4eslam");
strcpy(strings[5], "5fslam");
strcpy(strings[6], "6gslam");
strcpy(strings[7], "7hslam");
strcpy(strings[8], "8aslam");
strcpy(strings[9], "9aslam");
strcpy(strings[10], "A-fslam");
strcpy(strings[11], "B-6gslam");
strcpy(strings[12], "C-hslam");
strcpy(strings[13], "D-aslam");
strcpy(strings[14], "E-aslam");

	
	DualNode *item;
	int i;

	for( i=0; i<15; i++)
	{	
		printf("\n%d<-----kk-->%s",i, strings[i]);
		add_dual_item(hashtable, strings[i]);
		
	}
	
	printf("\nTraversal******************%d", get_total_dual_items(hashtable));
	traverse_dual_tbl(hashtable);
	printf("\nResized******************");
	//hashtable = resize_DualTable(hashtable, hashtable->_singleLen*2 );
	//traverse_dual_tbl(hashtable);
	printf("\nDeleted*****************");
	delete_dual_item_by_str(hashtable, "C-hslam");

	traverse_dual_tbl(hashtable);
	
	printf("\nGot************************%d", get_total_dual_items(hashtable));
	item = get_ditem_by_num(hashtable, 2);
	
	if(item)
		print_dual_item(item, 0);	
}
