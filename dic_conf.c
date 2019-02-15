#define WIDSIZT_T	short
#define GRPSIZE_T	uint64_t

//***********************
#define CHBYTES		1
#if(CHBYTES == 1)
	#define CHSIZE_T	uint8_t
#elif (CHBYTES == 2)
	#define CHSIZE_T	uint16_t
#endif
//************************
#define CHLIMIT_T	uint8_t
//************************
#define WLIMIT_T	uint8_t
//***************************************
//***********************************
#define MAX_WORD_LEN 12
//v for vector.


///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
/////////////////////////*******SUBTLE*******//////////////////////////

static const vstartAr[MAX_WORD_LEN+1]={1,2,1,2,2,3, 3, 4, 4, 4, 5, 5, 6};
static const vendAr[MAX_WORD_LEN+1]  ={3,4,5,6,7,9,11,12,14,16,17,19,20};

static const pos_startAr[MAX_WORD_LEN+1]	= {0, 0, 1, 2, 2, 3, 3,  4,  4,  5,  6,  6,  7,  8,  8};
static const pos_endAr[MAX_WORD_LEN+1]		= {1, 2, 3, 4, 6, 7, 9, 10, 11, 12, 13, 15, 16, 17, 19};

#define FORWARD_SMALL_LENGTH_MARKS		1040
#define BACKWARD_SMALL_LENGTH_MARKS		 525
#define FORWARD_BIG_LENGTH_MARKS		1000
#define BACKWARD_BIG_LENGTH_MARKS		 500
#define FORWARD_EQUAL_LENGTH_MARKS		1100
#define BACKWARD_EQUAL_LENGTH_MARKS		 550
#define Hh_BONUS_MARKS					 300
#define hH_PENALTY_MARKS				-300
#define tT_BONUS_MARKS					 100
#define Tt_PENALTY_MARKS				-100
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


/*Hh_bouns			= marksAr[2];
			hH_penalty			= marksAr[3];
			tT_bonus			= marksAr[4];
			Tt_penalty			= marksAr[5];*/ 
			
#define TOTAL_FW_MARKS 44000
#define TOTAL_BW_MARKS 22000

#define APPLY_POSITION_MARKS(CWLEN, FW_CHUNKS, BW_CHUNKS)\
conf.marksAr[CWLEN][0] = TOTAL_FW_MARKS/FW_CHUNKS;\
conf.marksAr[CWLEN][1] = TOTAL_BW_MARKS/BW_CHUNKS;\
 
		
//********************************
//********************************
#define REALLOC_MEM(STR, SIZE, RSIZE)\
	if(RSIZE<SIZE){\
		SIZE = RSIZE * 2;\
		STR = realloc(STR, SIZE);\
	}

#define WORD_POS_IND(W, J, N_ALPH)			W[J]+N_ALPH*W[J+1]
#define WORD_REV_IND(W, E, N_ALPH)			W[E]+N_ALPH*W[E-1]
#define WORD_BEG_END_IND(W, E, N_ALPH)		W[0]+N_ALPH * W[E]