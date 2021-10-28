#include <iostream>
#include "visualize.hpp"

class BubbleSort: public VisualizeSort{
	public:
		BubbleSort(){
			setTitle(typeid(this).name()+3);
		}
		void sort(bool debug = false){
			bool swapped = true;;
			is_sorting = true;
			while(swapped && !kill_signal){
				swapped = false;
				for (int i=0;i<DATA_BITS;i++){
					if(data_array[i] > data_array[i+1]){
						swap(i,i+1);
						swapped = true;
					}
				}
			}
			is_sorted = true;
			renderChanges(true);
			is_sorting = false;
		}
};

class InsertionSort:public VisualizeSort{
	public:
		InsertionSort(){
			setTitle(typeid(this).name()+2);
		}
		void sort(bool debug = false){
			is_sorting = true;
			int temp;
			for (int i=1;i<DATA_BITS && !kill_signal;i++){
				temp = i;
				for(int j=i-1;j>=0;j--){
					if (data_array[temp] < data_array[j]){
						swap(temp,j);
						temp = j;
					}else
						break;
				}
			}
			is_sorted = true;
			renderChanges(true);
			is_sorting = false;
		}
};

class MergeSort:public VisualizeSort{
	private:
		void merge(const int left, const int right, const int mid){
			int tempArr[right-left+1];
			int lptr=left, rptr = mid+1, count=0;
			tempArr[right-left] = 1;
			while(tempArr[right-left] == 1 && !kill_signal){
				if(rptr>right){
					tempArr[count] = data_array[lptr];
					lptr++;
				}else if(lptr > mid){
					tempArr[count] = data_array[rptr];
					rptr++;
				}else if( data_array[lptr] < data_array[rptr]){
					tempArr[count] = data_array[lptr];
					lptr++;
				}else if (data_array[lptr] > data_array[rptr]){
					tempArr[count] = data_array[rptr];
					rptr++;
				}
				count++;
			}
			count = 0;
			for (int i=left;i<=right;i++){
				data_array[i] = tempArr[count];
				swap(i,i);
				count++;
			}
		}
		int mergeSort(const int left, const int right){
			if (left>=right && !kill_signal)
				return 0;
			const int mid = (left+right)/2;
			mergeSort(left,mid);
			mergeSort(mid+1,right);
			merge(left,right, mid);
			return 0;
		}
	public:
		MergeSort(){
			setTitle(typeid(this).name()+2);
		}
		void sort(bool debug=false){
			is_sorting = true;
			//Start sort
			mergeSort(0,DATA_BITS-1);
			is_sorted = true;
			renderChanges(true);
			is_sorting = false;
		}
};

class QuickSort:public VisualizeSort{
	private:
		int computePivot(const int left, const int right, bool debug){
			int pivot = right;
			int j = left-1;
			for(int i=left;i<right && !kill_signal;i++){
				if(data_array[i] < data_array[pivot]){
					j++;
					swap(i,j);
				}
			}
			swap(j+1,right);
			return j+1;
		}
		int quickSort(const int left, const int right, bool debug){
			if (right <= left)
				return true;
			int pivot = computePivot(left,right, debug);
			quickSort(left, pivot-1, debug);
			quickSort(pivot+1,right, debug);
			return true;
		}
	public:
		QuickSort(){
			setTitle(typeid(this).name()+2);
		}
		void sort(bool debug=false){
			is_sorting = true;
			quickSort(0,DATA_BITS-1, debug);
	 		is_sorted = true;
	 		is_sorting = false;
			renderChanges(true);
		}
};