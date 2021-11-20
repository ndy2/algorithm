#include "student_rbTree.h"
#include "stdio.h"
#define NILID 987654321

/**
 * print
 **/

/*private*/
int _print_studentTree(node_student * tree, int is_left, int offset, int depth, char s[20][400])
{
    char b[20];
    int width = 5;

    if (tree->data.id == NILID) return 0;

    sprintf(b, " %03d%c", tree->data.id,tree->color);

    int left  = _print_studentTree(tree->left,  1, offset,                depth + 1, s);
    int right = _print_studentTree(tree->right, 0, offset + left + width, depth + 1, s);

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

bool isEmptyLine_student(char * line){
    for(int i = 0 ; i < 120 ; i++){
        if(line[i]!=' ')
            return false;
    }
    return true;         
}

/*public*/
void printTree_studentTree(node_student * tree)
{
    char s[20][400];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%120s", " ");

    _print_studentTree(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++){
        if(!isEmptyLine_student(s[i]))
            printf("%s\n", s[i]);
    }
    printf("\n");
}


/**
* constructor
**/

/* private */
node_student * createNode_student(student data, node_student*nilRef){
    node_student * n = (node_student*)malloc(sizeof(node_student));
    n->data = data;
    n->color = 'r';
    n->parent = NULL;
    n->left = nilRef;
    n->right = nilRef;
    return n;
}

node_student * createNil_student(){
    node_student * nil = (node_student*)malloc(sizeof(node_student));
    nil->color = 'b';
    nil->data.id = NILID;
    nil->data.student_id = NILID;
    return nil;
}

/* public */
tree_student create_studentTree(int size){
    tree_student t;
    t.root = NULL;
    t.nil = createNil_student();
    t.size = size;
    t.exist = (bool*)malloc(sizeof(bool)*size);
    memset(t.exist,false,size*sizeof(bool));
    return t;
}



/**
* helper
**/
/* private */
bool isRoot_student(node_student * n, tree_student t){
    return n->parent==t.nil;
}
bool isNil_student(node_student * n, tree_student t){
    return n==t.nil;
}
bool isEmpty_student(tree_student t){
    return t.root==NULL;
}

/**
* rotates
**/
/* private */
void leftRotate_student(tree_student * in, node_student * x){
    tree_student t = *in;
    node_student * y = x->right;
    x->right = y->left;

    if(!isNil_student(y->left,t))
        y->left->parent=x;
    
    y->parent=x->parent;

    if(isNil_student(x->parent,t))
        t.root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;

    y->left = x;
    x->parent=y;
    *in = t;
}
void rightRotate_student(tree_student *in, node_student * y){
    tree_student t = *in;
    node_student * x = y->left;
    y->left = x->right;
    if(!isNil_student(x->right,t))
        x->right->parent=y;
    
    x->parent = y->parent;
    if(isNil_student(y->parent,t))
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
void insertFixUp(tree_student * in, node_student * z){
    tree_student t = *in;        
    while(z->parent->color=='r')
        {
            if(z->parent==z->parent->parent->left){
                node_student * y = z->parent->parent->right; //uncle
                if(y->color=='r'){                   //push blackness down from grandparent
                    z->parent->color='b';
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->right){        // angle shape (<) => make linear shape
                        z = z->parent;
                        leftRotate_student(&t,z);
                    }
                    z->parent->color='b';           // linear shape (/)
                    z->parent->parent->color='r';
                    rightRotate_student(&t,z->parent->parent);
                }
            }
            else{
                node_student * y = z->parent->parent->left; //uncle
                if(y->color=='r'){                  //push blackness down from grandparent
                    z->parent->color='b';       
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->left){         // angle shape (>) => make linear shape
                        z = z->parent;
                        rightRotate_student(&t,z);
                    }
                    z->parent->color='b';           // linear shape (\)
                    z->parent->parent->color='r';
                    leftRotate_student(&t,z->parent->parent);
                    
                }
            }
        }

    t.root->color ='b';
    *in = t;
}
void insert_studentNode(tree_student * in, node_student* z){
    tree_student t = *in;
    if(isEmpty_student(t))
        {
            z->color = 'b';
            z->parent = t.nil;
            t.root = z;
        }
    else{
            node_student * y = t.nil;
            node_student * x = t.root;

            while(!isNil_student(x,t)){
                y = x;
                if(z->data.id < x->data.id)
                    x = x->left;
                else x = x->right;
            }
            z->parent=y;

            if(isNil_student(y,t))
                t.root = z;
            else if(z->data.id<y->data.id)
                y->left = z;
            else y->right = z;

            insertFixUp(&t, z);
        }
    *in = t;
}

/*public*/
bool insertOne_studentTree(tree_student * in, student data){
    if(in->exist[data.id]) {
        return false;
    }
    tree_student t = *in;
    node_student* z = createNode_student(data,t.nil);
    insert_studentNode(&t,z);
    t.exist[data.id] = true;
    *in = t;
    return true;
}


/**
* select
**/
/* private */
node_student * findById_studentNode(tree_student t, int id){
    node_student * z = NULL;

    node_student * cur = t.root;
    while(!isNil_student(cur,t)){
        if(id == cur->data.id)
            return cur;
        else if(id<cur->data.id)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return z;
}

bool found;
node_student * z;

void dfs_findById_student(node_student* cur, unsigned int target){
    if(cur->data.student_id == target){
        found = true;
        z = cur;
        return; 
    }else{
        if(cur->left->data.id!=NILID && !found)
            dfs_findById_student(cur->left, target);

        if(cur->right->data.id!=NILID && !found)
            dfs_findById_student(cur->right, target);
    }
}

node_student * findByStudentId_studentNode(tree_student t, unsigned int student_id){
    z = createNode_student(create_dummyStudent(),createNil_student());
    found = false;
    
    dfs_findById_student(t.root,student_id);
    return z;
}

student * list;
int idx;
void dfs_findAll_student(node_student * cur){
    if(cur->data.id!=NILID){
        list[idx] = cur->data;
        idx+=1;
        dfs_findAll_student(cur->left);
        dfs_findAll_student(cur->right);
    }
}

/* public */
student findById_studentTree(tree_student t, int id){

    if(!t.exist[id]){
        return  create_dummyStudent();
    }
    return findById_studentNode(t,id)->data;
}

int count_studentTree(tree_student t){
    int count = 0;
    for(int i =0; i <t.size; i++){
        if(t.exist[i]){
            count+=1;
        }
    }
    return count;
}

student findByStudentId_tree(tree_student t, unsigned int student_id){
    return findByStudentId_studentNode(t,student_id)->data;
}
    
student * findAll_studentTree(tree_student t){
    list = (student*)malloc(sizeof(student)*count_studentTree(t));
    idx = 0;

    dfs_findAll_student(t.root);
    return list;
}
/**
* delete
**/
/*private*/
void transplant_student (tree_student * in, node_student * u, node_student *v){
    tree_student t = *in;
    if(isNil_student(u->parent,t))
        t.root = v;
    else if(u==u->parent->left)
        u->parent->left=v;
    else
        u->parent->right=v;
    v->parent=u->parent;
    *in = t;    
}
node_student * getMinNode_student(node_student * root){
    while (root->left->data.id!=NILID) {
    root = root->left;
  }
  return root;
}
void deleteFixUp_student(tree_student * in, node_student *x){
    tree_student t = *in;

    while(!isRoot_student(x,t) && x->color=='b'){
        if(x==x->parent->left){
            node_student * w = x->parent->right;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                leftRotate_student(&t,x->parent);
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
                    rightRotate_student(&t,w);
                    w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->right->color='b';
                leftRotate_student(&t,x->parent);
                x=t.root;
            }
        }
        else{
            node_student * w = x->parent->left;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                rightRotate_student(&t,x->parent);
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
                    leftRotate_student(&t,w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->left->color='b';
                rightRotate_student(&t,x->parent);
                x=t.root;
            }
        }
    }
    x->color = 'b';
    *in = t;
}
void delete_studentNode(tree_student * in, node_student * z){
    tree_student t = *in;
    node_student * y = z;
    node_student * x;
    char yOrigColer= y->color;
    if(isNil_student(z->left,t)){
        x = z->right;
        transplant_student(&t,z,z->right);
    }
    else if(isNil_student(z->right,t)){
        x = z->left;
        transplant_student(&t,z,z->left);
    }
    else{
        y = getMinNode_student(z->right);
        yOrigColer=y->color;
        x = y->right;
        
        if(y->parent==z){
            x->parent = y->right;
        }
        // else{
            transplant_student(&t,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        // }
        transplant_student(&t,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yOrigColer == 'b'){
        deleteFixUp_student(&t, x);
    }

    *in = t;    
}

/*public*/
bool deleteById_studentTree(tree_student *in, int id){
    tree_student t = *in;
    if(!t.exist[id]){
        return false;
    }
    node_student * z = findById_studentNode(t, id);
    if(z==NULL){
        return false;
    }
    delete_studentNode(&t,z);
    
    t.exist[z->data.id] = false;
    *in = t;
    return true;
}


//tree Info methods
/*private*/
int idx;
int * temp;

int tree_height_student(node_student* root) {
    if (root->data.id == NILID) 
        return -1;
    else {
        // Find the height of left, right subtrees
        int left_height = tree_height_student(root->left);
        int right_height = tree_height_student(root->right);
          
        // Find max(subtree_height) + 1 to get the height of the tree
        int maxHeight = left_height>right_height?left_height:right_height;
        return maxHeight + 1;
    }
}
bool isLeaf_student(node_student * n){
    return (n->data.id != NILID) && n->left->data.id ==NILID && n->right->data.id ==NILID;
}
void dfs_findLeaves_student(node_student * cur){
    if(isLeaf_student(cur)){
        temp[idx] = cur->data.id;
        idx++;
    }else if(cur->data.id != NILID){
        dfs_findLeaves_student(cur->left);
        dfs_findLeaves_student(cur->right);
    }
}
void updateTreeInfo_studentTree(tree_student * t){
    treeInfo ti;
    ti.rootId = t->root->data.id;
    ti.numData = count_studentTree(*t);

    int height = tree_height_student(t->root);
    ti.height = height;

    node_student * cur = t->root;
    
    idx = 0 ;
    temp = (int*)malloc(sizeof(int)* (1<<height));
    
    dfs_findLeaves_student(cur);

    int leafCnt = idx;
    ti.leafCnt = leafCnt;

    int * leafIds = (int *)malloc(sizeof(int) * leafCnt);
    for(int i = 0 ; i <leafCnt ; i++){
        leafIds[i] = temp[i];
    }
    ti.leafIds = leafIds;
    free(temp);

    t->ti=ti;
}

/*public*/
void print_treeInfo_studentTree(tree_student t,char * title){
    print_treeInfo(t.ti,title);
}
