
#include <iostream>

#include <cstdlib>

#include <vector>




using namespace std;

int swap_count=0;

int comparison=0;

void shift_nodes( int *a, int k, int N);




void swap(int *m, int *n)

{

	int tmp;

	tmp = *m;

	*m = *n;

	*n = tmp;







}




void heap_sort( int a[], int N){




	for (int k = N/2; k >= 0; k--) {

		shift_nodes( a, k, N);

	}




	while (N-1 > 0) {




		swap_count+=1;

		//swap the root(maximum value) of the heap with the last element of the heap

		swap(a[N-1], a[0]);

		//put the heap back in maximum-heap order




		shift_nodes(a, 0, N-1);

		/* decrease the size of the heap by one

		so that the previous max value will

        	stay in its proper placement */

		N--;

	}

}




void shift_nodes( int *a, int k, int N){

	while ( k*2 + 1 < N ) {

		//For an element array, the children are 2*i+1 and 2*i+2

 		int child = 2*k + 1;




		// get bigger child if there are two children

		if ((child + 1 < N) && (a[child] < a[child+1])) {

			child++;

			comparison+=1;

		}




		if (a[k] < a[child]) {

			/* out of max-heap order */

			comparison+=1;

			swap( a[child], a[k] );

			k = child;

		}

		else

			return;

	}

}







int main() {

		int size;

		cout<<"Enter the size of the array: ";

		cin>>size;

		int array[size];

		for (int i=0; i< size; i++)

		{

			array[i] = rand() % (size+1);

            cout<<array[i]<<" ";

		}




		cout<<endl;

		cout<<"***********************************After Sort************************************************";

		cout<<endl;




		float start= clock();




			heap_sort(array, size);

			start = ( clock() - start) / CLOCKS_PER_SEC;

			cout<<"Total time taken to sort elements using heap sort: "<<start<<" secs"<<endl;




			cout << "No. of comparison: "<<comparison<<endl;

			cout << "No of swap: "<<swap_count<<endl;

	return 0;

