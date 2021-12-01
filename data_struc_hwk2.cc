#include<iostream>
#include <cstdlib>
#include<ctime>
#include <fstream>
using namespace std;
  
struct TreapNod  { //node declaration
   int data;
   int priority;
   TreapNod* l, *r;
   TreapNod(int d) { //constructor
      this->data = d;
      this->priority = rand() % 100;
      this->l= this->r = nullptr;
   }
};
void rotLeft(TreapNod* &root) { //left rotation
   TreapNod* R = root->r;
   TreapNod* X = root->r->l;
   R->l = root;
   root->r= X;
   root = R;
}
void rotRight(TreapNod* &root) { //right rotation
   TreapNod* L = root->l;
   TreapNod* Y = root->l->r;
   L->r = root;
   root->l= Y;
   root = L;
}
void insertNod(TreapNod* &root, int d) { //insertion
   if (root == nullptr) {
      root = new TreapNod(d);
      return;
   }
   if (d < root->data) {
      insertNod(root->l, d);
      if (root->l != nullptr && root->l->priority > root->priority)
      rotRight(root);
   } else {
      insertNod(root->r, d);
      if (root->r!= nullptr && root->r->priority > root->priority)
      rotLeft(root);
   }
}
bool searchNod(TreapNod* root, int key) {
   if (root == nullptr)
      return false;
   if (root->data == key)
      return true;
   if (key < root->data)
      return searchNod(root->l, key);
      return searchNod(root->r, key);
}
void deleteNod(TreapNod* &root, int key) {
   //node to be deleted which is a leaf node
   if (root == nullptr)
      return;
   if (key < root->data)
      deleteNod(root->l, key);
   else if (key > root->data)
      deleteNod(root->r, key);
      //node to be deleted which has two children
   else {
      if (root->l ==nullptr && root->r == nullptr) {
         delete root;
         root = nullptr;
      }
      else if (root->l && root->r) {
         if (root->l->priority < root->r->priority) {
            rotLeft(root);
            deleteNod(root->l, key);
         } else {
            rotRight(root);
            deleteNod(root->r, key);
         }
      }
      //node to be deleted has only one child
      else {
         TreapNod* child = (root->l)? root->l: root->r;
         TreapNod* curr = root;
         root = child;
         delete curr;
      }
   }
}
void displayTreap(TreapNod *root, int space = 0, int height =10) { //display treap
   if (root == nullptr)
      return;
   space += height;
   displayTreap(root->l, space);
   cout << endl;
   for (int i = height; i < space; i++)
      cout << ' ';
      cout << root->data << "(" << root->priority << ")\n";
      cout << endl;
   displayTreap(root->r, space);
}
// Class to implement node
// Inserts a key in arr[] of given capacity. n is current
// size of arr[]. This function returns n+1 if insertion
// is successful, else n.
int insertSorted(int arr[], int n, int key, int capacity)
{
    // Cannot insert more elements if n is already
    // more than or equal to capacity
    if (n >= capacity)
        return n;
 
    int i;
    for (i = n - 1; (i >= 0 && arr[i] > key); i--)
        arr[i + 1] = arr[i];
    arr[i + 1] = key;
 
    return (n + 1);
}

int binarySearch(int arr[], int low, int high, int key)
{
    if (high < low)
        return -1;
    int mid = (low + high) / 2;
    if (key == arr[mid])
        return mid;
    if (key > arr[mid])
        return binarySearch(arr, (mid + 1), high, key);
    return binarySearch(arr, low, (mid - 1), key);
}

class Node
{
public:
    int key;
  
    // Array to hold pointers to node of different level
    Node **forward;
    Node(int, int);
};
  
Node::Node(int key, int level)
{
    this->key = key;
  
    // Allocate memory to forward
    forward = new Node*[level+1];
  
    // Fill forward array with 0(NULL)
    memset(forward, 0, sizeof(Node*)*(level+1));
};

int list_num=0;
int add=0;
// Class for Skip list
class SkipList
{
    // Maximum level for this skip list
    int MAXLVL;
  
    // P is the fraction of the nodes with level
    // i pointers also having level i+1 pointers
    float P;
  
    // current level of skip list
    int level;
  
    // pointer to header node
    Node *header;
public:
    SkipList(int, float);
    int randomLevel();
    Node* createNode(int, int);
    void insertElement(int);
    void searchElement(int);
    void displayList();
};
  
SkipList::SkipList(int MAXLVL, float P)
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;
  
    // create header node and initialize key to -1
    header = new Node(-1, MAXLVL);
};
  
// create random level for node
int SkipList::randomLevel()
{
    float r = (float)rand()/RAND_MAX;
    int lvl = 0;
    while (r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand()/RAND_MAX;
    }
    return lvl;
};
  
// create new node
Node* SkipList::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
};
  
// Insert given key in skip list
void SkipList::insertElement(int key)
{
    Node *current = header;
    // create update array and initialize it
    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));
  
    /*    start from highest level of skip list
        move the current pointer forward while key
        is greater than key of node next to current
        Otherwise inserted current in update and
        move one level down and continue search
    */
    for (int i = level; i >= 0; i--)
    {
        while (current->forward[i] != NULL &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
  
    /* reached level 0 and forward pointer to
       right, which is desired position to
       insert key.
    */
    current = current->forward[0];
  
    /* if current is NULL that means we have reached
       to end of the level or current's key is not equal
       to key to insert that means we have to insert
       node between update[0] and current node */
    if (current == NULL || current->key != key)
    {
        // Generate a random level for node
        int rlevel = randomLevel();
  if(rlevel>list_num)
list_num=rlevel;
add+=rlevel;
        // If random level is greater than list's current
        // level (node with highest level inserted in
        // list so far), initialize update value with pointer
        // to header for further use
        if (rlevel > level)
        {
            for (int i=level+1;i<rlevel+1;i++)
                update[i] = header;
  
            // Update the list current level
            level = rlevel;
        }
  
        // create new node with random level generated
        Node* n = createNode(key, rlevel);
  
        // insert node by rearranging pointers
        for (int i=0;i<=rlevel;i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
//        cout << "Successfully Inserted key " << key << "\n";
    }
};

// Search for element in skip list
void SkipList::searchElement(int key)
{
    Node *current = header;
  
    /*    start from highest level of skip list
        move the current pointer forward while key
        is greater than key of node next to current
        Otherwise inserted current in update and
        move one level down and continue search
    */
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] &&
               current->forward[i]->key < key)
            current = current->forward[i];
  
    }
  
    /* reached level 0 and advance pointer to
       right, which is possibly our desired node*/
    current = current->forward[0];
  
    // If current node have key equal to
    // search key, we have found our target node
//    if(current and current->key == key)
  //      cout<<"Found key: "<<key<<"\n";
};
 
// Display skip list level wise
void SkipList::displayList()
{
    cout<<"\n*****Skip List*****"<<"\n";
    for (int i=0;i<=level;i++)
    {
        Node *node = header->forward[i];
        cout << "Level " << i << ": ";
        while (node != NULL)
        {
            cout << node->key<<" ";
            node = node->forward[i];
        }
        cout << "\n";
    }
};

int main (void)
{
clock_t begin, end, start, stop;
srand(time(NULL));
SkipList goal(1000, 0.5);
int random;
ofstream result_1, result_2, result_3, result_4;
result_1.open("result_1.csv", ios::app);
result_2.open("result_2.csv", ios::app);
result_3.open("skiplist_AdditionalCopy.csv", ios::app);
result_4.open("skiplist_LvL.csv", ios::app);
/*
cout << "SkipList(p=0.5)" << endl;
result_1 << "SkipList(p=0.5)," << ',' << endl;
result_2 << "SkipList(p=0.5)," << ',' << endl;
result_3 << "SkipList(p=0.5)," << ',' << endl;
result_4 << "SkipList(p=0.5)," << ',' << endl;
for(int k=10;k<=30;++k)
{
double diff;
cout << "   k=" << k << ",";
result_1 << "k=" << k << ":,";
result_2 << "k=" << k << ":,";
result_3 << "k=" << k << ":,";
result_4 << "k=" << k << ":,";
start=clock();
for(int i=0;i<(1<<k);++i)
{
random = rand()%(1<<30)+1;
goal.insertElement(random);
}
stop=clock();
diff=double(stop-start)/CLOCKS_PER_SEC;
result_1 << ",Insert time:," << diff << ',' << endl;
begin=clock();
for(int i=0;i<(1<<k);++i)
{
random = rand()%(1<<30)+1;
goal.searchElement(random);
}
end=clock();
diff=double(end-begin)/CLOCKS_PER_SEC;
result_2 << ",Search time:," << diff << ','  << endl;
int aver;
aver=add/(1<<k);
result_3 << ",Additional copy:," << aver << ',' << endl;
result_4 << ",Number of list:," << list_num << ',' << endl;
cout << " Done " << endl;
}

// change the prob to 0.1
SkipList goalgoal(1000,0.1);
cout << "SkipList(p=0.1)" << endl;
result_1 << "SkipList(p=0.1)," << ',' << endl;
result_2 << "SkipList(p=0.1)," << ',' << endl;
result_3 << "SkipList(p=0.1)," << ',' << endl;
result_4 << "SkipList(p=0.1)," << ',' << endl;
for(int k=10;k<=30;++k)
{
double diff;
cout << "   k=" << k << ",";
result_1 << "k=" << k << ":,";
result_2 << "k=" << k << ":,";
result_3 << "k=" << k << ":,";
result_4 << "k=" << k << ":,";
start=clock();
for(int i=0;i<(1<<k);++i)
{
random = rand()%(1<<30)+1;
goalgoal.insertElement(random);
}
stop=clock();
diff=double(stop-start)/CLOCKS_PER_SEC;
result_1 << ",Insert time:," << diff << ',' << endl;
begin=clock();
for(int i=0;i<(1<<k);++i)
{
random = rand()%(1<<30)+1;
goalgoal.searchElement(random);
}
end=clock();
diff=double(end-begin)/CLOCKS_PER_SEC;
result_2 << ",Search time:," << diff << ','  << endl;
int aver;
aver=add/(1<<k);
result_3 << ",Additional copy:," << aver << ',' << endl;
result_4 << ",Number of list:," << list_num << ',' << endl;
cout << " Done " << endl;
}

//change the prob to 0.9
SkipList gogo(1000,0.9);
cout << "SkipList(p=0.9)" << endl;
result_1 << "SkipList(p=0.9)," << ',' << endl;
result_2 << "SkipList(p=0.9)," << ',' << endl;
result_3 << "SkipList(p=0.9)," << ',' << endl;
result_4 << "Skip list which p=0.9," << ',' << endl;
for(int k=10;k<=30;++k)
{
double diff;
cout << "   k=" << k << ",";
result_1 << "k=" << k << ":,";
result_2 << "k=" << k << ":,";
result_3 << "k=" << k << ":,";
result_4 << "k=" << k << ":,";
start=clock();
for(int i=0;i<(1<<k);++i)
{
random = rand()%(1<<30)+1;
gogo.insertElement(random);
}
stop=clock();
diff=double(stop-start)/CLOCKS_PER_SEC;
result_1 << ",Insert time:," << diff << ',' << endl;
begin=clock();
for(int i=0;i<(1<<k);++i)
{
random = rand()%(1<<30)+1;
gogo.searchElement(random);
}
end=clock();
diff=double(end-begin)/CLOCKS_PER_SEC;
result_2 << ",Search time:," << diff << ','  << endl;
int aver;
aver=add/(1<<k);
result_3 << ",Additional copy:," << aver << ',' << endl;
result_4 << ",Number of list:," << list_num << ',' << endl;
cout << " Done " << endl;
}


cout << "Sorted array" << endl;
result_1 << "Sorted array," << ',' << endl;
result_2 << "Sorted array," << ',' << endl;
result_3 << "Sorted array," << ',' << endl;
result_4 << "Sorted array," << ',' << endl;
for(int k=10;k<=30;++k)
{
double diff;
cout << "   k=" << k << ",";
result_1 << "k=" << k << ":,";
result_2 << "k=" << k << ":,";
result_3 << "k=" << k << ":,";
result_4 << "k=" << k << ":,";
int *arr=new int[(1<<k)+100]();
start=clock();
for(int i=1;i<=(1<<k);++i)
{
random = rand()%(1<<k)+1;
insertSorted(arr, i, random, (1<<k));
}
stop=clock();
diff=double(stop-start)/CLOCKS_PER_SEC;
result_1 << ",Insert time:," << diff << ',' << endl;
begin=clock();
for(int i=1;i<=(1<<k);++i)
{
random = rand()%(1<<k)+1;
binarySearch(arr, 1, (1<<k), random);
}
end=clock();
diff=double(end-begin)/CLOCKS_PER_SEC;
result_2 << ",Search time:," << diff << ','  << endl;
cout << " Done " << endl;
}
*/
TreapNod* root = nullptr;
cout << "Treap" << endl;
result_1 << "Treap," << ',' << endl;
result_2 << "Treap," << ',' << endl;
result_3 << "Treap," << ',' << endl;
result_4 << "Treap," << ',' << endl;
for (int k=10;k<=30;++k)
    {
double diff;
cout << "   k=" << k << ",";
result_1 << "k=" << k << ":,";
result_2 << "k=" << k << ":,";
result_3 << "k=" << k << ":,";
result_4 << "k=" << k << ":,";
start=clock();
for(int i=0;i<(1<<k);++i)
{
random = rand()%(1<<30)+1;
insertNod(root, random);
}
stop=clock();
diff = double(stop-start)/CLOCKS_PER_SEC;
result_1 << ",Insert time:," << diff << ',' << endl;
begin=clock();
for(int i=0;i<(1<<k);++i)
{
random = rand()%(1<<30)+1;
searchNod(root, random);
}
stop=clock();
diff = double(stop-begin)/CLOCKS_PER_SEC;
result_2 << ",Search time:," << diff << ','  << endl; 
cout << " Done " << endl;
   }
result_1.close();
result_2.close();
result_3.close();
result_4.close();
return 0;
}

