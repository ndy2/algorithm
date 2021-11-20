#include "stdio.h"
#include "course_rbTree.h"

#define NILID 987654321

/**
 * print
 **/

/*private*/
int _print_courseTree(node_course * tree, int is_left, int offset, int depth, char s[20][400])
{
    char b[20];
    int width = 5;

    if (tree->data.id == NILID) return 0;

    sprintf(b, " %03d%c", tree->data.id,tree->color);

    int left  = _print_courseTree(tree->left,  1, offset,                depth + 1, s);
    int right = _print_courseTree(tree->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    //한글자 쓰기
    for(int i = 0 ; i < 4 ; i++){
        s[2*depth][offset+left+width+i] = tree->data.name[i];
    }
    
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

bool isEmptyLine_course(char * line){
    for(int i = 0 ; i < 120 ; i++){
        if(line[i]!=' ')
            return false;
    }
    return true;         
}

/*public*/
void printTree_courseTree(node_course * tree)
{
    char s[20][400];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%120s", " ");

    _print_courseTree(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++){
        if(!isEmptyLine_course(s[i]))
            printf("%s\n", s[i]);
    }
    printf("\n");
}


/**
* constructor
**/

/* private */
node_course * createNode_course(course data, node_course*nilRef){
    node_course * n = (node_course*)malloc(sizeof(node_course));
    n->data = data;
    n->color = 'r';
    n->parent = NULL;
    n->left = nilRef;
    n->right = nilRef;
    return n;
}

node_course * createNil_course(){
    node_course * nil = (node_course*)malloc(sizeof(node_course));
    nil->color = 'b';
    nil->data.id = NILID;
    return nil;
}

/* public */
tree_course create_courseTree(int size){
    tree_course t;
    t.root = NULL;
    t.nil = createNil_course();
    t.size = size;
    t.exist = (bool*)malloc(sizeof(bool)*size);
    memset(t.exist,false,size*sizeof(bool));
    return t;
}



/**
* helper
**/
/* private */
bool isRoot_course(node_course * n, tree_course t){
    return n->parent==t.nil;
}
bool isNil_course(node_course * n, tree_course t){
    return n==t.nil;
}
bool isEmpty_course(tree_course t){
    return t.root==NULL;
}

/**
* rotates
**/
/* private */
void leftRotate_course(tree_course * in, node_course * x){
    tree_course t = *in;
    node_course * y = x->right;
    x->right = y->left;

    if(!isNil_course(y->left,t))
        y->left->parent=x;
    
    y->parent=x->parent;

    if(isNil_course(x->parent,t))
        t.root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;

    y->left = x;
    x->parent=y;
    *in = t;
}
void rightRotate_course(tree_course *in, node_course * y){
    tree_course t = *in;
    node_course * x = y->left;
    y->left = x->right;
    if(!isNil_course(x->right,t))
        x->right->parent=y;
    
    x->parent = y->parent;
    if(isNil_course(y->parent,t))
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
void insertFixUp_course(tree_course * in, node_course * z){
    tree_course t = *in;        
    while(z->parent->color=='r')
        {
            if(z->parent==z->parent->parent->left){
                node_course * y = z->parent->parent->right; //uncle
                if(y->color=='r'){                   //push blackness down from grandparent
                    z->parent->color='b';
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->right){        // angle shape (<) => make linear shape
                        z = z->parent;
                        leftRotate_course(&t,z);
                    }
                    z->parent->color='b';           // linear shape (/)
                    z->parent->parent->color='r';
                    rightRotate_course(&t,z->parent->parent);
                }
            }
            else{
                node_course * y = z->parent->parent->left; //uncle
                if(y->color=='r'){                  //push blackness down from grandparent
                    z->parent->color='b';       
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->left){         // angle shape (>) => make linear shape
                        z = z->parent;
                        rightRotate_course(&t,z);
                    }
                    z->parent->color='b';           // linear shape (\)
                    z->parent->parent->color='r';
                    leftRotate_course(&t,z->parent->parent);
                    
                }
            }
        }

    t.root->color ='b';
    *in = t;
}
void insert_courseNode(tree_course * in, node_course* z){
    tree_course t = *in;
    if(isEmpty_course(t))
        {
            z->color = 'b';
            z->parent = t.nil;
            t.root = z;
        }
    else{
            node_course * y = t.nil;
            node_course * x = t.root;

            while(!isNil_course(x,t)){
                y = x;
                if(z->data.id < x->data.id)
                    x = x->left;
                else x = x->right;
            }
            z->parent=y;

            if(isNil_course(y,t))
                t.root = z;
            else if(z->data.id<y->data.id)
                y->left = z;
            else y->right = z;

            insertFixUp_course(&t, z);
        }
    *in = t;
}

/*public*/
bool insertOne_courseTree(tree_course * in, course data){
    if(in->exist[data.id]) {
        return false;
    }
    tree_course t = *in;
    node_course* z = createNode_course(data,t.nil);
    insert_courseNode(&t,z);
    t.exist[data.id] = true;
    *in = t;
    return true;
}


/**
* select
**/
/* private */
node_course * findById_courseNode(tree_course t, int id){
    node_course * z = NULL;

    node_course * cur = t.root;
    while(!isNil_course(cur,t)){
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
course findById_courseTree(tree_course t, int id){

    if(!t.exist[id]){
        return create_course("dummyCourse","dummyCourse","dummyCourse",0);
    }
    return findById_courseNode(t,id)->data;
}

int count_courseTree(tree_course t){
    int count = 0;
    for(int i =0; i <t.size; i++){
        if(t.exist[i]){
            count+=1;
        }
    }
    return count;
}

/*private*/
bool found;
node_course * z;

void dfs_findByCourseId_course(node_course* cur, char * target){
    if(!strcmp(cur->data.course_id,target)){
        found = true;
        z = cur;
        return; 
    }else{
        if(cur->left->data.id!=NILID && !found)
            dfs_findByCourseId_course(cur->left, target);

        if(cur->right->data.id!=NILID && !found)
            dfs_findByCourseId_course(cur->right, target);
    }
}

/*public*/
course findByCourseId_courseTree(tree_course t,char * course_id){
    found = false;
    dfs_findByCourseId_course(t.root,course_id);
    return z->data;
}


/**
* delete
**/
/*private*/
void transplant_course (tree_course * in, node_course * u, node_course *v){
    tree_course t = *in;
    if(isNil_course(u->parent,t))
        t.root = v;
    else if(u==u->parent->left)
        u->parent->left=v;
    else
        u->parent->right=v;
    v->parent=u->parent;
    *in = t;    
}
node_course * getMinNode_course(node_course * root){
    while (root->left->data.id!=NILID) {
    root = root->left;
  }
  return root;
}
void deleteFixUp_course(tree_course * in, node_course *x){
    tree_course t = *in;

    while(!isRoot_course(x,t) && x->color=='b'){
        if(x==x->parent->left){
            node_course * w = x->parent->right;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                leftRotate_course(&t,x->parent);
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
                    rightRotate_course(&t,w);
                    w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->right->color='b';
                leftRotate_course(&t,x->parent);
                x=t.root;
            }
        }
        else{
            node_course * w = x->parent->left;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                rightRotate_course(&t,x->parent);
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
                    leftRotate_course(&t,w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->left->color='b';
                rightRotate_course(&t,x->parent);
                x=t.root;
            }
        }
    }
    x->color = 'b';
    *in = t;
}
void delete_courseNode(tree_course * in, node_course * z){
    tree_course t = *in;
    node_course * y = z;
    node_course * x;
    char yOrigColer= y->color;
    if(isNil_course(z->left,t)){
        x = z->right;
        transplant_course(&t,z,z->right);
    }
    else if(isNil_course(z->right,t)){
        x = z->left;
        transplant_course(&t,z,z->left);
    }
    else{
        y = getMinNode_course(z->right);
        yOrigColer=y->color;
        x = y->right;
        
        if(y->parent==z){
            x->parent = y->right;
        }
        // else{
            transplant_course(&t,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        // }
        transplant_course(&t,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yOrigColer == 'b'){
        deleteFixUp_course(&t, x);
    }

    *in = t;    
}

/*public*/
bool deleteById_courseTree(tree_course *in, int id){
    tree_course t = *in;
    if(!t.exist[id]){
        return false;
    }
    node_course * z = findById_courseNode(t, id);
    if(z==NULL){
        return false;
    }
    delete_courseNode(&t,z);
    
    t.exist[z->data.id] = false;
    *in = t;
    return true;
}


//tree Info methods
/*private*/
int idx2;
int * temp2;

int tree_height_course(node_course* root) {
    if (root->data.id == NILID) 
        return -1;
    else {
        // Find the height of left, right subtrees
        int left_height = tree_height_course(root->left);
        int right_height = tree_height_course(root->right);
          
        // Find max(subtree_height) + 1 to get the height of the tree
        int maxHeight = left_height>right_height?left_height:right_height;
        return maxHeight + 1;
    }
}
bool isLeaf_course(node_course * n){
    return (n->data.id != NILID) && n->left->data.id ==NILID && n->right->data.id ==NILID;
}
void dfs_findLeaves_course(node_course * cur){
    if(isLeaf_course(cur)){
        temp2[idx2] = cur->data.id;
        idx2++;
    }else if(cur->data.id != NILID){
        dfs_findLeaves_course(cur->left);
        dfs_findLeaves_course(cur->right);
    }
}
void updateTreeInfo_courseTree(tree_course * t){
    treeInfo ti;
    ti.rootId = t->root->data.id;
    ti.numData = count_courseTree(*t);

    int height = tree_height_course(t->root);
    ti.height = height;

    node_course * cur = t->root;
    
    idx2 = 0 ;
    temp2 = (int*)malloc(sizeof(int)* (1<<height));
    
    dfs_findLeaves_course(cur);

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
void print_treeInfo_courseTree(tree_course t,char * title){
    print_treeInfo(t.ti,title);
}

