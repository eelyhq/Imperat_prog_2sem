#define FIND_ANCESTOR(num_el) (num_el % 2 == 1 ? num_el / 2 : num_el / 2 - 1 )
void sift_up(int* heap, int num_el)
{
    int el = heap[num_el];

    while (el < heap[FIND_ANCESTOR(num_el)])
    {
        int index = FIND_ANCESTOR(num_el);
        int tmp = heap[index];
        heap[index] = heap[num_el];
        heap[num_el] = tmp;
        num_el = index;
    }
}

void sift_down(int* heap, int num_el)
{
    int el = heap[0];
    int i = 0;

    int min_son;

    while (1)
    {
        if (2*i+1 < num_el && 2*i+2 < num_el)
        {
            if (el < heap[2*i+1] && el < heap[2*i+2]) break;

            if (heap[2*i+1] > heap[2*i+2])
            {
                min_son = 2*i+2;
            }
            else if (heap[2*i+1] < heap[2*i+2])
            {
                min_son = 2*i+1;
            }
            else break;
        }
        else break;

        int tmp = heap[min_son];
        heap[min_son] = el;
        heap[i] = tmp;
        i = min_son;

    }
}


void insert(int* heap, int val, int* num_elements)
{
    heap[*num_elements] = val;
    *num_elements += 1;
    sift_up(heap, *num_elements - 1);
}

int extract_min(int* heap, int* num_elements)
{
    int res = heap[0];

    heap[0] = heap[*num_elements - 1];

    *num_elements -= 1;

    sift_down(heap, *num_elements);
    return res;
}


int** adj_matrix = (int**)malloc((n+1) * sizeof(int));
int** sons_matrix = (int**)malloc((n+1) * sizeof(int));

for (int i = 1; i <= n; i++)
{
    adj_matrix[i] = (int*)malloc((n+1) *  sizeof(int));
    for (int j = 1; j <=n; j++)
    {
        adj_matrix[i][j] = 9000001;
    }

    sons_matrix[i] = (int*)malloc((n+1) * sizeof(int));
    memset(sons_matrix[i], -1, (n+1) * sizeof(int));

    adj_matrix[i][i] = 0;
}

for (int i = 0; i < m; i++)
{
    int from, to, weight;
    fscanf(f_in, "%d %d %d", &from, &to, &weight);

    adj_matrix[from][to] = weight; // graph - oriented
    sons_matrix[from][to] = to;
}

int* visited = (int*)calloc(n+1, sizeof(int));

visited[1] = 1;