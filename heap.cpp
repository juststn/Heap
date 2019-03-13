#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
using namespace std;


/*Heap program- Creates a binary tree (max heap) of up to 100 numbers
from an input or a file. The heap will then remove each element in order from
the heap, and output all deleted numbers from largest to smallest.
*/
void insertHeap(int &heap_size, int* heap, int input);
void printHeap(int* heap, int heap_size);
void deleteHeap(int &heap_size, int* heap);
int main(){

  int heap[101];
  int heap_size = 0;
  int input = 0;
  
  cout<<"Heap: choose whether to read from file or input [F, I]"<<endl;

  
  string in;
  cin>>in;

  //inputting from file
  if (in == "F"){
    cout<<"Input file name"<<endl;
    cin>>in;
    
     std::ifstream myfile(in);
     if (myfile.is_open()) {
       if (!myfile.eof())
       {
          while (myfile >> input) {
           insertHeap(heap_size, heap, input); 
            }
       }
       myfile.close();
      }
     else {
        cout << "Can not open input file" << endl;
        return 0;
       }
   }
  //inputting from input
  else if (in == "I"){
    cout<<"Input numbers to add (separated with spaces, such as 1 4 3 34 2)"<<endl;
    while ( cin >> input) {
    
      // insert the number into heap
      insertHeap(heap_size, heap, input);
      
      if ( cin.get() == '\n' ) break;
     }
  }
  else{
      cout<<"invalid input"<<endl;
      return 0;
  }
  
  // print the heap
  printHeap(heap, heap_size);

  cout << "Removed from heap: " << endl; 
  while (heap_size>0) {
    cout << heap[1] << " ";
    deleteHeap(heap_size, heap);
  }
  cout << endl;

  //printHeap(heap, heap_size);
}

//inserting a number, adding to the end of the heap and swapping if greater
//than parent
void insertHeap(int &heap_size, int* heap, int input){

  // if heap is empty, then add the first value to heap
  if(heap_size == 0){
    heap_size = 1;
    heap[heap_size] = input;
    return;
  }

  // add to end of heap, and move up the child if it is larger than its parent
  int pos = heap_size+1;
  heap[pos] = input;
  heap_size++;

  int parent = (pos)/2;

  // check if the child is larger than the parent, then switch with parent

  while (pos > 1 && heap[pos]>heap[parent]){
    int temp = heap[pos];
    heap[pos] = heap[parent];
    heap[parent] = temp;
    pos = parent;
    parent = (pos)/2;
  }
  
}

//delete the root of the heap
void deleteHeap(int &heap_size, int* heap){
  if(heap_size==0){
    return;
  }
  
  if(heap_size==1){
    heap_size = 0;
    return;
  }
  int heap_pos = 1;
  
  heap[1] = heap[heap_size];
  heap[heap_size] = 0;
  heap_size = heap_size - 1;

  int maxChild=0;
  int goDown=1;
  while (goDown==1)  {
    if(heap_pos*2>heap_size){
      maxChild = 0;
      break;  // end the loop
    }
    //if only has left child
    else if(2*heap_pos <= heap_size && 2*heap_pos + 1 > heap_size){
        maxChild = 2*heap_pos;
      }
    //if left child greater 
    else if (heap[heap_pos*2]>heap[heap_pos*2+1]){
      maxChild=heap_pos*2;
    }
    //if right child greater
    else if (heap[heap_pos*2]<heap[heap_pos*2+1]){
      maxChild= heap_pos*2+1;
    }
    else{
      maxChild = heap_pos*2+1;
    }
    
    //swapping child and parent
    if(maxChild != 0 && heap[heap_pos] < heap[maxChild]){
      int temp;
      temp = heap[maxChild];
      heap[maxChild] = heap[heap_pos];
      heap[heap_pos] = temp;

      heap_pos = maxChild;
    }
    else{
      goDown = 0;
    }
  }
  
  /* if(heap_pos*2+1<=heap_size){

    while(heap[heap_pos]>heap[heap_pos*2]&&heap[heap_pos]>heap[heap_pos*2+1]){
       
      heap_pos = pow(2,heap_pos+1);

    }
    }*/

}
//print heap
void printHeap(int* heap, int heap_size){

  cout<<"tree list:"<<endl;
  int x = 1;

  //switch to a new line when it encounters 2^x
  for(int i = 1; i<=heap_size; i++){
    // cout<<" "<<i<<"  1111 "<<x<<endl;
    if(i == pow(2,x)){
      cout<<endl;
	x++;
      }
      
    
    cout<<heap[i]<<" ";
  }
  cout<<endl;
 
  return;

}
