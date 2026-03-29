#define CONCAT1(a,b) a##_##b
#define CONCAT(a,b) CONCAT1(a,b)

#define INIT CONCAT(NAME, init)
#define DESTROY CONCAT(NAME, destroy)
#define PUSH    CONCAT(NAME, push)
#define POP CONCAT(NAME, pop)
#define RESERVE CONCAT(NAME, reserve)
#define RESIZE  CONCAT(NAME, resize)
#define INSERT CONCAT(NAME, insert)
#define ERASE CONCAT(NAME, erase)



typedef struct NAME {
    TYPE* arr ;
    int n ;
    int capacity;
    } NAME ;

//initializes members of [vec] structure for empty array
void INIT(NAME* vec);
//makes array [vec] empty and frees its array buffer [vec->arr]
//note: this function can be called many times
void DESTROY( NAME* vec );
//adds element [value] to the end of array [vec]
//returns index of the added element
int PUSH( NAME* vec , TYPE value );
//removes the last element from array [vec]
//returns removed element
TYPE POP( NAME* vec );
//ensures that array [vec] has enough storage for [capacity] elements
//note: address of elements surely won’t change before [vec->n] exceeds capacity
void RESERVE( NAME* vec , int capacity );
//changes number of elements in array [vec] to [newCnt]
//if the number increases, new elements get value [fill]
//if the number decreases, some elements at the end are removed
void RESIZE( NAME* vec , int newCnt , TYPE fill );
//inserts elements [arr[0]], [arr[1]], [arr[2]], ..., [arr[num-1]]
//in-between elements [vec->arr[where-1]] and [vec->arr[where]]
//note: the whole array [arr] cannot be part of array [vec]
//[where] may vary from 0 to [vec->n], [num] can also be zero
void INSERT( NAME* vec , int where , TYPE* arr , int num );
//removes elements [vec->arr[k]] for k = [where], [where+1], ..., [where+num-1]
//all the elements starting from [where+num]-th are shifted left by [num] positions
void ERASE( NAME* vec , int where, int num);