#include<stdlib.h>
#include "dic_priority_tree.h"

DicNode * createNode(int value){
    DicNode * newNode =  (DicNode *)malloc(sizeof(DicNode));
    newNode->value = value;
    newNode->right= NULL;
    newNode->left = NULL;
    return newNode;
}

void insert_node(DicNode **sr, DicNode *new_node)
{
	int m = new_node->marks;
	while (*sr)
	{
	   if (m < (*sr)->entry)
		   sr = &(*sr)->left;
	   else
		   sr = &(*sr)->right;
	}
	*sr = new_node;
	new_node->left = new_node->right = NULL;
}

void get_smallest_node(DicNode *root,  TwinDicNode *smallest)
{
		TwinDicNode *small = smallest;
		DicNode *x, *p;
		p = x = root;
		while(x -> left != NULL) {p = x; x = x -> left; }
		small->par = p;
		small->node = x;
}

void del_smallest_node(DicNode **root,  TwinDicNode *smallest)
{
		DicNode *x, *p;
		TwinDicNode *small = smallest;	
		p = small->par;
		x = small->node;		
		
		if(p->left ) {
			if(x->right)	p->leftchild = x->right;
			else p -> left = NULL;
			 }
		else *root = p->right;		
		//free(x);		
}

///////////////////////////////////////////////////
///////////////////////////////////////////////
	
/*void inorder_write_asc(thr)
{
	DicNode *root = thr->root;
	char *sgb = thr->cur_sgb;//sugg group	bytes
	char *swb = thr->cur_swb;//sugg wid 	bytes
	char *smb = thr->cur_swb;//sugg marks	bytes
	
	
	
	DicNode *stack[STACK_SIZE];	int top = -1;
	DicNode *curNode  = root;
	while(top > -1 || curNode ){
		if(curNode){
			stack[++top] = curNode;
			curNode = curNode->left;
		}
		else {
			curNode =  stack[top--];
			WRITE_LE8(sgb, curNode->grp);
			WRITE_LE4(swb, curNode->wid);
			WRITE_LE2(smb, curNode->marks);
			//printf("%d  ", curNode->value);
			curNode = curNode->right;
		}
	}
}*/

void inorder_dic_desc(thr)
{
	int i=1;// because the first element contains the length.
	DicNode *root = thr->root;
	
	size_t ub		= thr->n_msw-1;
	
	WIDSIZE_T* swAr	= thr->swArs[ub] = malloc(sizeof(WIDSIZE_T) * thr->n_dic_pri_nodes);
	uint16_t* smAr	= thr->smArs[ub] = malloc(sizeof(WIDSIZE_T) * thr->n_dic_pri_nodes);
	//uint64_t* sgAr	= thr->sgArs[ub];
	
	DicNode *stack[STACK_SIZE];	int top = -1;
	DicNode *curNode  = root;
	while(top > -1 || curNode ){
		if(curNode){
			stack[++top] = curNode;
			curNode = curNode->right;
		}
		else {
			curNode	= stack[ top--];
			sgAr[i]		= curNode->grp;
			swAr[i]		= curNode->wid;
			swAr[i++]	= curNode->scr;
			
			//printf("%d  ", curNode->value);
			curNode = curNode->left;
		}
	}
}


void clear_marks_array()
{
	for(int i=0; i<total_nodes; i++){
		WIDSIZE_T wid = dic_nodesAr[i]->wid;
		marksAr[wid&AI_BITS][wid&EI_BITS] = 0;
	}
}