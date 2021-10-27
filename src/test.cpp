/*#include <iostream>

const int data = 5;
int arr[data];
void swap(int i,int j){
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

int computePivot(int low, int high){
	int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++; // increment index of smaller element 
            swap(i, j); 
        } 
    } 
    swap(i+1, high); 
    return (i + 1); 
}

void display(const int *arr){
	for (int i=0;i<data;i++){
		std::cout << arr[i] << "  ";
	}
	std::cout << std::endl;
}
int quickSort(int lptr,int rptr){
	if (lptr>=rptr)
		return 0;

	int pivot = computePivot(lptr,rptr);
	quickSort(lptr,pivot-1);
	quickSort(pivot+1,rptr);
	return 0;
}
void merge(const int left, const int right, const int mid){
	int tempArr[right-left+1], count=0;
	tempArr[right-left] = -1;
	int lptr=left, rptr = mid+1;
	while(tempArr[right-left] == -1){
		if(rptr>right){
			tempArr[count] = arr[lptr];
			lptr++;
		}else if(lptr > mid){
			tempArr[count] = arr[rptr];
			rptr++;
		}else if (arr[lptr] < arr[rptr]){
			tempArr[count] = arr[lptr];
			lptr++;
		}else if (arr[lptr] > arr[rptr]){
			tempArr[count] = arr[rptr];
			rptr++;
		}
		count++;
	}
	count = 0;
	for (int i=left;i<=right;i++){
		arr[i] = tempArr[count];
		count++;
	}
}
int mergeSort(const int left,const int right){
	if (left>=right)
		return 0;
	const int mid = (left+right)/2;
	mergeSort(left,mid);
	mergeSort(mid+1,right);
	merge(left,right, mid);
	return 0;
}
void sort(int *arr){
	//quickSort(0,data-1);
	mergeSort(0,data-1);
}

void shuffle(){
	int temp,ran; 
	for(int i=0;i<data;i++){
		ran = rand()%(data-1);
		temp = arr[i];
		arr[i] = arr[ran];
		arr[ran] = temp;
	}
}

int main(){
	for (int i=0;i<data;i++){
		arr[i] = i;
	}
	shuffle();

	display(arr);

	sort(arr);

	display(arr);

}*/