#ifndef PRIORITY_TREE_FILE
#define PRIORITY_TREE_FILE

typedef struct
{
    struct DicNode *left;
	uint32_t wid;
	uint64_t group;
	short marks;
    struct DicNode *right;
};
typedef struct DicNode;
typedef struct
{
	DicNode *par;
	DicNode *node;
} TwinDicNode;

void		insert_dn( DicNode **, DicNode *);
void		get_smallest_dn( DicNode *,  TwinDicNode *);
void		del_smallest_dn ( DicNode **,  TwinDicNode *);
void		inorder_write_dt(DicNode *, char* , char*);
DicNode * createNode(int); //not sure used or not.
#endif
