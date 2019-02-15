//*******************************************
//*******************************************
#define HANDLE_DUPLICATED_CHUNKS_SCORE();
	for(int X=st_pos; X<wind; X++)\
	{\
		WIDSIZE_T* widAr = binAr[X];\
		int nbin = *widAr;\
		int marks = marksAr[X];\
		for(int Y=1; Y<nbin; Y++)\
		{\
			WIDSIZE_T wid = widAr[Y];\
			if(pos_marksAr[wid&AI_BITS][wid&EI_BITS]<marks)\
				pos_marksAr[wid&AI_BITS][wid&EI_BITS] = marks;\
		}\
	}
//*******************************************
#define APPEND_WORD_POS_MARKS()
	for(int X=st_pos; X<wind; X++)
	{
		WIDSIZE_T* widAr = binAr[X];
		int nbin = *widAr;
		int marks = marksAr[X];
		for(int Y=1; Y<nbin; Y++)
		{
			WIDSIZE_T wid = widAr[Y];
						
			scoreAr[wid&AI_BITS][wid&EI_BITS] += pos_marksAr[wid&AI_BITS][wid&EI_BITS];
			pos_marksAr[wid&AI_BITS][wid&EI_BITS] = 0;
				
		}
	}
//*******************************************
//*******************************************
			

// Tt, tT, Hh, hH, TH.... illustrated below.
//Begining chunk Hh.//"H" is 1st and "h" is 2nd 1st character for mw.
#define APPEND_HEADER_FORWARDING_SCORE()
	binAr[wInd] = widAr = dictionary[dwlen][2][WORD_REV_IND(w, 0)];\
	int nbin = *widAr;\
	for(int X=1; X<nbin; X++)\
		scoreAr[widAr[X]&AI_BITS][widAr[X]&EI_BITS] += fm+Hh_bouns;

#define APPEND_HEADER_BACKWARDING_SCORE()
	if(w[0] != w[1])\
	{\
		binAr[wInd++] = widAr = dictionary[dwlen][2][WORD_REV_IND(w, 1)];\
		int nbin = *widAr;\
		for(int X=1; X<nbin; X++)\
			scoreAr[widAr[X]&AI_BITS][widAr[X]&EI_BITS] += bm-hH_penalty;\
	}
//****************************************
//****************************************
//Ending chunk tT.// "T" is last and "t" is 2nd last character for mw.
#define APPEND_TAIL_FORWARDING_SCORE()
	binAr[wInd++] = widAr = dictionary[dwlen][0][WORD_BEG_IND(w, k)];\
	int nbin = *widAr;\
	for(int X=1; X<nbin; X++)\
		scoreAr[widAr[X]&AI_BITS][widAr[X]&EI_BITS] += fm+tT_bonus;

//Ending chunk Tt.
#define APPEND_TAIL_BACKWARDING_SCORE()
	if(w[cwlen-1] != w[cwlen-2])\
	{\
		binAr[wInd++] = widAr = dictionary[dwlen][0][WORD_REV_IND(w, k)];\
		int nbin = *widAr;\
		for(int X=1; X<nbin; X++)\
			scoreAr[widAr[X]&AI_BITS][widAr[X]&EI_BITS] += bm-Tt_penalty;\
	}
//****************************************
//****************************************		
#define APPEND_HEADER_AND_TAIL_SCORE()
	binAr[wInd++] = widAr = dictionary[dwlen][1][WORD_HT_IND(w, k)];\
	int nbin = *widAr;\
	for(int X=1; X<nbin; X++)\
		scoreAr[widAr[X]&AI_BITS][widAr[X]&EI_BITS] += fm+Hh_bouns;//HT and Hh bouns are same.
		