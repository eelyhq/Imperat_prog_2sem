typedef struct IntegerSet_s IntegerSet;


IntegerSet* CreateSet(const int* arr, int n);

void DeleteSet(IntegerSet* set);

int IsInSet(IntegerSet* set, int value);