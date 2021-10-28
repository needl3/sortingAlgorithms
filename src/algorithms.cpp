#include <iostream>
#include "visualize.hpp"
#include <SFML/Graphics.hpp>

class BubbleSort: public VisualizeSort{
	public:
		BubbleSort(){
			setTitle(typeid(this).name()+3);
		}
		void sort(bool debug = false){
			renderChanges(changedIndexes,true);
			bool swapped = true;;
			while(swapped){
				swapped = false;
				for (int i=0;i<DATA_BITS;i++){
					if(data_array[i] > data_array[i+1]){
						swap(i,i+1);
						changedIndexes[0] = i;
						changedIndexes[1] = i+1;
						if(!debug)
							renderChanges(changedIndexes);
						swapped = true;
					}
//					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			}
			isSorted = true;
			renderChanges(changedIndexes,false,true);
		}
};

class InsertionSort:public VisualizeSort{
	public:
		InsertionSort(){
			setTitle(typeid(this).name()+2);
		}
		void sort(bool debug = false){
			int temp;
			for (int i=1;i<DATA_BITS;i++){
				temp = i;
				for(int j=i-1;j>=0;j--){
					if (data_array[temp] < data_array[j]){
						swap(temp,j);
						changedIndexes[0] = temp;
						changedIndexes[1] = j;
						if(!debug)
							renderChanges(changedIndexes);
						temp = j;
					}else
						break;
				}
			}
			isSorted = true;
			renderChanges(changedIndexes, false,true);
		}
};

class MergeSort:public VisualizeSort{
	private:
		void merge(const int left, const int right, const int mid){
			int tempArr[right-left+1];
			int lptr=left, rptr = mid+1, count=0;
			tempArr[right-left] = 1;
			while(tempArr[right-left] == 1){
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
				changedIndexes[0] = i;
				changedIndexes[1] = i;
				renderChanges(changedIndexes);
				count++;
			}
		}
		int mergeSort(const int left, const int right){
			if (left>=right)
				return 0;
			const int mid = (left+right)/2;
			mergeSort(left,mid);
			mergeSort(mid+1,right);
			merge(left,right, mid);
			isSorted = true;
			return 0;
		}
	public:
		MergeSort(){
			setTitle(typeid(this).name()+2);
		}
		void sort(bool debug=false){

			//Start sort
			mergeSort(0,DATA_BITS-1);

			//Last animation
			renderChanges(changedIndexes,false,true);
		}
};

class QuickSort:public VisualizeSort{
	private:
		int computePivot(const int left, const int right, bool debug){
			int pivot = right;
			int j = left-1;
			for(int i=left;i<right;i++){
				if(data_array[i] < data_array[pivot]){
					j++;
					swap(i,j);
					changedIndexes[0] = i;
					changedIndexes[1] = j;
					if (!debug)
						renderChanges(changedIndexes);
				}
			}
			swap(j+1,right);
			changedIndexes[0] = j+1;
			changedIndexes[1] = right;
			if(!debug)
				renderChanges(changedIndexes);
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
			if(!debug)
				renderChanges(changedIndexes,true);
			quickSort(0,DATA_BITS-1, debug);
			if (!debug)
	 			renderChanges(changedIndexes,false,true);
	 		isSorted = true;
		}
};