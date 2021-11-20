#include "reg_rbTree.h"
#include "stdio.h"
#define NILID 987654321

/**
 * print
 **/

/*private*/
int _print_regTree(node_reg * tree, int is_left, int offset, int depth, char s[20][400])
{
    char b[20];
    int width = 5;

    if (tree->data.id == NILID) return 0;

    sprintf(b, " %03d%c", tree->data.id,tree->color);

    int left  = _print_regTree(tree->left,  1, offset,                depth + 1, s);
    int right = _print_regTree(tree->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];
    
    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }

    return left + width + right;
}

bool isEmptyLine_reg(char * line){
    for(int i = 0 ; i < 120 ; i++){
        if(line[i]!=' ')
            return false;
    }
    return true;         
}

/*public*/
void printTree_regTree(node_reg * tree)
{
    char s[20][400];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%120s", " ");

    _print_regTree(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++){
        if(!isEmptyLine_reg(s[i]))
            printf("%s\n", s[i]);
    }
    printf("\n");
}


/**
* constructor
**/

/* private */
node_reg * createNode_reg(reg data, node_reg*nilRef){
    node_reg * n = (node_reg*)malloc(sizeof(node_reg));
    n->data = data;
    n->color = 'r';
    n->parent = NULL;
    n->left = nilRef;
    n->right = nilRef;
    return n;
}

node_reg * createNil_reg(){
    node_reg * nil = (node_reg*)malloc(sizeof(node_reg));
    nil->color = 'b';
    nil->data.id = NILID;
    return nil;
}

/* public */
tree_reg create_regTree(int size){
    tree_reg t;
    t.root = NULL;
    t.nil = createNil_reg();
    t.size = size;
    t.exist = (bool*)malloc(sizeof(bool)*size);
    memset(t.exist,false,size*sizeof(bool));
    return t;
}



/**
* helper
**/
/* private */
bool isRoot_reg(node_reg * n, tree_reg t){
    return n->parent==t.nil;
}
bool isNil_reg(node_reg * n, tree_reg t){
    return n==t.nil;
}
bool isEmpty_reg(tree_reg t){
    return t.root==NULL;
}

/**
* rotates
**/
/* private */
void leftRotate_reg(tree_reg * in, node_reg * x){
    tree_reg t = *in;
    node_reg * y = x->right;
    x->right = y->left;

    if(!isNil_reg(y->left,t))
        y->left->parent=x;
    
    y->parent=x->parent;

    if(isNil_reg(x->parent,t))
        t.root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;

    y->left = x;
    x->parent=y;
    *in = t;
}
void rightRotate_reg(tree_reg *in, node_reg * y){
    tree_reg t = *in;
    node_reg * x = y->left;
    y->left = x->right;
    if(!isNil_reg(x->right,t))
        x->right->parent=y;
    
    x->parent = y->parent;
    if(isNil_reg(y->parent,t))
        t.root = x;
    else if(y==y->parent->left)
        y->parent->left = x;
    else
        y->parent->right =x;

    x->right = y;
    y->parent = x;

    *in = t;
}


/**
* insert
**/
/* private */
void insertFixUp_reg(tree_reg * in, node_reg * z){
    tree_reg t = *in;        
    while(z->parent->color=='r')
        {
            if(z->parent==z->parent->parent->left){
                node_reg * y = z->parent->parent->right; //uncle
                if(y->color=='r'){                   //push blackness down from grandparent
                    z->parent->color='b';
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->right){        // angle shape (<) => make linear shape
                        z = z->parent;
                        leftRotate_reg(&t,z);
                    }
                    z->parent->color='b';           // linear shape (/)
                    z->parent->parent->color='r';
                    rightRotate_reg(&t,z->parent->parent);
                }
            }
            else{
                node_reg * y = z->parent->parent->left; //uncle
                if(y->color=='r'){                  //push blackness down from grandparent
                    z->parent->color='b';       
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->left){         // angle shape (>) => make linear shape
                        z = z->parent;
                        rightRotate_reg(&t,z);
                    }
                    z->parent->color='b';           // linear shape (\)
                    z->parent->parent->color='r';
                    leftRotate_reg(&t,z->parent->parent);
                    
                }
            }
        }

    t.root->color ='b';
    *in = t;
}
void insert_regNode(tree_reg * in, node_reg* z){
    tree_reg t = *in;
    if(isEmpty_reg(t))
        {
            z->color = 'b';
            z->parent = t.nil;
            t.root = z;
        }
    else{
            node_reg * y = t.nil;
            node_reg * x = t.root;

            while(!isNil_reg(x,t)){
                y = x;
                if(z->data.id < x->data.id)
                    x = x->left;
                else x = x->right;
            }
            z->parent=y;

            if(isNil_reg(y,t))
                t.root = z;
            else if(z->data.id<y->data.id)
                y->left = z;
            else y->right = z;

            insertFixUp_reg(&t, z);
        }
    *in = t;
}

/*public*/
bool insertOne_regTree(tree_reg * in, reg data){
    if(in->exist[data.id]) {
        return false;
    }
    tree_reg t = *in;
    node_reg* z = createNode_reg(data,t.nil);
    insert_regNode(&t,z);
    t.exist[data.id] = true;
    *in = t;
    return true;
}


/**
* select
**/
/* private */
node_reg * findById_regNode(tree_reg t, int id){
    node_reg * z = NULL;

    node_reg * cur = t.root;
    while(!isNil_reg(cur,t)){
        if(id == cur->data.id)
            return cur;
        else if(id<cur->data.id)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return z;
}

/* public */
reg findById_regTree(tree_reg t, int id){

    if(!t.exist[id]){
        return create_dummyReg();
    }
    return findById_regNode(t,id)->data;
}

int count_regTree(tree_reg t){
    int count = 0;
    for(int i =0; i <t.size; i++){
        if(t.exist[i]){
            count+=1;
        }
    }
    return count;
}

/*private*/
regApi api;
reg * temp;
int idx;

void dfs_reg_withStudentId(node_reg * cur,int student_id){
    if(cur->data.id==NILID){
        return;
    }else if(cur->data.student_id==student_id){
        temp[idx] = cur->data;
        idx++;
    }
    dfs_reg_withStudentId(cur->left,student_id);
    dfs_reg_withStudentId(cur->right,student_id);
}


regApi findAll_wherestudentIdIsGiven_regTree(tree_reg t, unsigned int student_id){
    idx=0;
    temp = (reg*)malloc(sizeof(reg)*10000);
    dfs_reg_withStudentId(t.root,student_id);

    int size = idx;
    api.size = idx;
    api.data = (reg*)malloc(sizeof(reg)*size);
    for(int i = 0 ; i <size; i++){
        api.data[i] = temp[i];
    }
    
    free(temp);
    return api;
}


/**
* delete
**/
/*private*/
void transplant_reg (tree_reg * in, node_reg * u, node_reg *v){
    tree_reg t = *in;
    if(isNil_reg(u->parent,t))
        t.root = v;
    else if(u==u->parent->left)
        u->parent->left=v;
    else
        u->parent->right=v;
    v->parent=u->parent;
    *in = t;    
}
node_reg * getMinNode_reg(node_reg * root){
    while (root->left->data.id!=NILID) {
    root = root->left;
  }
  return root;
}
void deleteFixUp_reg(tree_reg * in, node_reg *x){
    tree_reg t = *in;

    while(!isRoot_reg(x,t) && x->color=='b'){
        if(x==x->parent->left){
            node_reg * w = x->parent->right;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                leftRotate_reg(&t,x->parent);
                w=x->parent->right;
            }

            if(w->left->color=='b' && w->right->color=='b'){
                w->color='r';
                x=x->parent;
            }
            else{ 
                if(w->right->color =='b'){
                    w->left->color='b';
                    w->color='r';
                    rightRotate_reg(&t,w);
                    w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->right->color='b';
                leftRotate_reg(&t,x->parent);
                x=t.root;
            }
        }
        else{
            node_reg * w = x->parent->left;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                rightRotate_reg(&t,x->parent);
                w=x->parent->left;
            }

            if(w->right->color=='b' && w->left->color=='b'){
                w->color='r';
                x=x->parent;
            }
            else{ 
                if(w->left->color =='b'){
                    w->right->color='b';
                    w->color='r';
                    leftRotate_reg(&t,w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->left->color='b';
                rightRotate_reg(&t,x->parent);
                x=t.root;
            }
        }
    }
    x->color = 'b';
    *in = t;
}
void delete_regNode(tree_reg * in, node_reg * z){
    tree_reg t = *in;
    node_reg * y = z;
    node_reg * x;
    char yOrigColer= y->color;
    if(isNil_reg(z->left,t)){
        x = z->right;
        transplant_reg(&t,z,z->right);
    }
    else if(isNil_reg(z->right,t)){
        x = z->left;
        transplant_reg(&t,z,z->left);
    }
    else{
        y = getMinNode_reg(z->right);
        yOrigColer=y->color;
        x = y->right;
        
        if(y->parent==z){
            x->parent = y->right;
        }
        // else{
            transplant_reg(&t,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        // }
        transplant_reg(&t,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yOrigColer == 'b'){
        deleteFixUp_reg(&t, x);
    }

    *in = t;    
}

/*public*/
bool deleteById_regTree(tree_reg *in, int id){
    tree_reg t = *in;
    if(!t.exist[id]){
        return false;
    }
    node_reg * z = findById_regNode(t, id);
    if(z==NULL){
        return false;
    }
    delete_regNode(&t,z);
    
    t.exist[z->data.id] = false;
    *in = t;
    return true;
}


//tree Info methods
/*private*/
int idx2;
int * temp2;

int tree_height_reg(node_reg* root) {
    if (root->data.id == NILID) 
        return -1;
    else {
        // Find the height of left, right subtrees
        int left_height = tree_height_reg(root->left);
        int right_height = tree_height_reg(root->right);
          
        // Find max(subtree_height) + 1 to get the height of the tree
        int maxHeight = left_height>right_height?left_height:right_height;
        return maxHeight + 1;
    }
}
bool isLeaf_reg(node_reg * n){
    return (n->data.id != NILID) && n->left->data.id ==NILID && n->right->data.id ==NILID;
}
void dfs_findLeaves_reg(node_reg * cur){
    if(isLeaf_reg(cur)){
        temp2[idx2] = cur->data.id;
        idx2++;
    }else if(cur->data.id != NILID){
        dfs_findLeaves_reg(cur->left);
        dfs_findLeaves_reg(cur->right);
    }
}
void updateTreeInfo_regTree(tree_reg * t){
    treeInfo ti;
    ti.rootId = t->root->data.id;
    ti.numData = count_regTree(*t);
    int height = tree_height_reg(t->root);
    ti.height = height;

    node_reg * cur = t->root;
    
    idx2 = 0 ;
    temp2 = (int*)malloc(sizeof(int)* 10000);
    
    dfs_findLeaves_reg(cur);

    int leafCnt = idx2;
    ti.leafCnt = leafCnt;

    int * leafIds = (int *)malloc(sizeof(int) * leafCnt);
    for(int i = 0 ; i <leafCnt ; i++){
        leafIds[i] = temp2[i];
    }
    ti.leafIds = leafIds;
    free(temp2);

    t->ti=ti;
}

/*public*/
void print_treeInfo_regTree(tree_reg t,char * title){
    print_treeInfo(t.ti,title);
}



