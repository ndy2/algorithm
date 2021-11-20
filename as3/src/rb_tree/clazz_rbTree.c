#include "clazz_rbTree.h"
#include "stdio.h"
#define NILID 987654321

/**
 * print
 **/

/*private*/
int _print_clazzTree(node_clazz * tree, int is_left, int offset, int depth, char s[20][400])
{
    char b[20];
    int width = 5;

    if (tree->data.id == NILID) return 0;

    sprintf(b, " %03d%c", tree->data.id,tree->color);

    int left  = _print_clazzTree(tree->left,  1, offset,                depth + 1, s);
    int right = _print_clazzTree(tree->right, 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    //한글자 쓰기
    for(int i = 0 ; i < 4 ; i++){
        s[2*depth][offset+left+width+i] = tree->data.course_id[i];
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

bool isEmptyLine_clazz(char * line){
    for(int i = 0 ; i < 120 ; i++){
        if(line[i]!=' ')
            return false;
    }
    return true;         
}

/*public*/
void printTree_clazzTree(node_clazz * tree)
{
    char s[20][400];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%120s", " ");

    _print_clazzTree(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++){
        if(!isEmptyLine_clazz(s[i]))
            printf("%s\n", s[i]);
    }
    printf("\n");
}


/**
* constructor
**/

/* private */
node_clazz * createNode_clazz(clazz data, node_clazz*nilRef){
    node_clazz * n = (node_clazz*)malloc(sizeof(node_clazz));
    n->data = data;
    n->color = 'r';
    n->parent = NULL;
    n->left = nilRef;
    n->right = nilRef;
    return n;
}

node_clazz * createNil_clazz(){
    node_clazz * nil = (node_clazz*)malloc(sizeof(node_clazz));
    nil->color = 'b';
    nil->data.id = NILID;
    return nil;
}

/* public */
tree_clazz create_clazzTree(int size){
    tree_clazz t;
    t.root = NULL;
    t.nil = createNil_clazz();
    t.size = size;
    t.exist = (bool*)malloc(sizeof(bool)*size);
    memset(t.exist,false,size*sizeof(bool));
    return t;
}



/**
* helper
**/
/* private */
bool isRoot_clazz(node_clazz * n, tree_clazz t){
    return n->parent==t.nil;
}
bool isNil_clazz(node_clazz * n, tree_clazz t){
    return n==t.nil;
}
bool isEmpty_clazz(tree_clazz t){
    return t.root==NULL;
}

/**
* rotates
**/
/* private */
void leftRotate_clazz(tree_clazz * in, node_clazz * x){
    tree_clazz t = *in;
    node_clazz * y = x->right;
    x->right = y->left;

    if(!isNil_clazz(y->left,t))
        y->left->parent=x;
    
    y->parent=x->parent;

    if(isNil_clazz(x->parent,t))
        t.root=y;
    else if(x==x->parent->left)
        x->parent->left=y;
    else
        x->parent->right=y;

    y->left = x;
    x->parent=y;
    *in = t;
}
void rightRotate_clazz(tree_clazz *in, node_clazz * y){
    tree_clazz t = *in;
    node_clazz * x = y->left;
    y->left = x->right;
    if(!isNil_clazz(x->right,t))
        x->right->parent=y;
    
    x->parent = y->parent;
    if(isNil_clazz(y->parent,t))
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
void insertFixUp_clazz(tree_clazz * in, node_clazz * z){
    tree_clazz t = *in;        
    while(z->parent->color=='r')
        {
            if(z->parent==z->parent->parent->left){
                node_clazz * y = z->parent->parent->right; //uncle
                if(y->color=='r'){                   //push blackness down from grandparent
                    z->parent->color='b';
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->right){        // angle shape (<) => make linear shape
                        z = z->parent;
                        leftRotate_clazz(&t,z);
                    }
                    z->parent->color='b';           // linear shape (/)
                    z->parent->parent->color='r';
                    rightRotate_clazz(&t,z->parent->parent);
                }
            }
            else{
                node_clazz * y = z->parent->parent->left; //uncle
                if(y->color=='r'){                  //push blackness down from grandparent
                    z->parent->color='b';       
                    y->color='b';
                    z->parent->parent->color='r';
                    z=z->parent->parent;
                }
                else{ 
                    if(z==z->parent->left){         // angle shape (>) => make linear shape
                        z = z->parent;
                        rightRotate_clazz(&t,z);
                    }
                    z->parent->color='b';           // linear shape (\)
                    z->parent->parent->color='r';
                    leftRotate_clazz(&t,z->parent->parent);
                    
                }
            }
        }

    t.root->color ='b';
    *in = t;
}
void insert_clazzNode(tree_clazz * in, node_clazz* z){
    tree_clazz t = *in;
    if(isEmpty_clazz(t))
        {
            z->color = 'b';
            z->parent = t.nil;
            t.root = z;
        }
    else{
            node_clazz * y = t.nil;
            node_clazz * x = t.root;

            while(!isNil_clazz(x,t)){
                y = x;
                if(z->data.id < x->data.id)
                    x = x->left;
                else x = x->right;
            }
            z->parent=y;

            if(isNil_clazz(y,t))
                t.root = z;
            else if(z->data.id<y->data.id)
                y->left = z;
            else y->right = z;

            insertFixUp_clazz(&t, z);
        }
    *in = t;
}

/*public*/
bool insertOne_clazzTree(tree_clazz * in, clazz data){
    if(in->exist[data.id]) {
        return false;
    }
    tree_clazz t = *in;
    node_clazz* z = createNode_clazz(data,t.nil);
    insert_clazzNode(&t,z);
    t.exist[data.id] = true;
    *in = t;
    return true;
}


/**
* select
**/
/* private */
node_clazz * findById_clazzNode(tree_clazz t, int id){
    node_clazz * z = NULL;

    node_clazz * cur = t.root;
    while(!isNil_clazz(cur,t)){
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
clazz findById_clazzTree(tree_clazz t, int id){

    if(!t.exist[id]){
        return create_dummyClazz();
    }
    return findById_clazzNode(t,id)->data;
}

int count_clazzTree(tree_clazz t){
    int count = 0;
    for(int i =0; i <t.size; i++){
        if(t.exist[i]){
            count+=1;
        }
    }
    return count;
}


/*private*/
clazzDto dto;
clazz * temp;
int idx;

void dfs_clazz_withYearandSemester(node_clazz * cur,int year, short semester){
    if(cur->data.id==NILID){
        return;
    }else if(cur->data.year==year && cur->data.semester==semester){
        temp[idx] = cur->data;
        idx++;
    }
    dfs_clazz_withYearandSemester(cur->left,year,semester);
    dfs_clazz_withYearandSemester(cur->right,year,semester);
}


/*public*/
clazzDto findAllClazzWhereYearAndSemesterGiven_clazzTree(tree_clazz t, int year, short semester){
    temp = (clazz*)malloc(sizeof(clazz)*count_clazzTree(t));
    idx = 0;
    dfs_clazz_withYearandSemester(t.root, year, semester);

    int count = idx;
    dto.size =count;
    dto.data = (clazz*)malloc(sizeof(clazz)*count);
    for(int i = 0 ; i < count; i++){
        dto.data[i] = temp[i];
    }
    free(temp);
    return dto;
}

    

/**
* delete
**/
/*private*/
void transplant_clazz (tree_clazz * in, node_clazz * u, node_clazz *v){
    tree_clazz t = *in;
    if(isNil_clazz(u->parent,t))
        t.root = v;
    else if(u==u->parent->left)
        u->parent->left=v;
    else
        u->parent->right=v;
    v->parent=u->parent;
    *in = t;    
}
node_clazz * getMinNode_clazz(node_clazz * root){
    while (root->left->data.id!=NILID) {
    root = root->left;
  }
  return root;
}
void deleteFixUp_clazz(tree_clazz * in, node_clazz *x){
    tree_clazz t = *in;

    while(!isRoot_clazz(x,t) && x->color=='b'){
        if(x==x->parent->left){
            node_clazz * w = x->parent->right;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                leftRotate_clazz(&t,x->parent);
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
                    rightRotate_clazz(&t,w);
                    w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->right->color='b';
                leftRotate_clazz(&t,x->parent);
                x=t.root;
            }
        }
        else{
            node_clazz * w = x->parent->left;
            if(w->color=='r'){
                w->color='b';
                x->parent->color='r';
                rightRotate_clazz(&t,x->parent);
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
                    leftRotate_clazz(&t,w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                x->parent->color='b';
                w->left->color='b';
                rightRotate_clazz(&t,x->parent);
                x=t.root;
            }
        }
    }
    x->color = 'b';
    *in = t;
}
void delete_clazzNode(tree_clazz * in, node_clazz * z){
    tree_clazz t = *in;
    node_clazz * y = z;
    node_clazz * x;
    char yOrigColer= y->color;
    if(isNil_clazz(z->left,t)){
        x = z->right;
        transplant_clazz(&t,z,z->right);
    }
    else if(isNil_clazz(z->right,t)){
        x = z->left;
        transplant_clazz(&t,z,z->left);
    }
    else{
        y = getMinNode_clazz(z->right);
        yOrigColer=y->color;
        x = y->right;
        
        if(y->parent==z){
            x->parent = y->right;
        }
        // else{
            transplant_clazz(&t,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        // }
        transplant_clazz(&t,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(yOrigColer == 'b'){
        deleteFixUp_clazz(&t, x);
    }

    *in = t;    
}

/*public*/
bool deleteById_clazzTree(tree_clazz *in, int id){
    tree_clazz t = *in;
    if(!t.exist[id]){
        return false;
    }
    node_clazz * z = findById_clazzNode(t, id);
    if(z==NULL){
        return false;
    }
    delete_clazzNode(&t,z);
    
    t.exist[z->data.id] = false;
    *in = t;
    return true;
}


