// qsort
void exchange(double *data, int *index, int i, int j);
int partition(int p, int r, double *data, int *index);
void seq_qsort(int p, int r, double *data, int *index);
void q_sort(int p, int r, double *data, int *index, int low_limit);
int *quickargsort(double *data, int length, int low_limit);
void test_quickargsort();

// isort
int *insertionargsort(double *data, int length);
void test_insertionargsort();

// msort 
void merge(double *data, int *index, int l, int m, int r);
void mergesort(double *data, int *index, int l, int r);
int *mergeargsort(double *data, int length);
void test_mergeargsort();

// distance
double euclidean_distance(double *pointA, double *pointB, int dims);
double manhattan_distance(double *pointA, double *pointB, int dims);
double *one_to_many_distances(double *one_point, double **many_points, int many_length, int dims, char *dist_func);
double **many_to_many_distances(double **points_A, double **points_B, int length_A, int length_B, int dims, char *dist_func);
double **many_to_many_distances_omp(double **points_A, double **points_B, int length_A, int length_B, int dims, char *dist_func);
void test_euclidean_distances();
void test_manhattan_distances();

// knn functions 
void knn_serial(int n, int m, int dims, int k, char *filename, char *distance_function, char *sort_function);
void knn_parallel(int n, int m, int dims, int k, char *filename, char *distance_function, char *sort_function);

