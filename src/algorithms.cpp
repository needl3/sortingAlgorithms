#include <iostream>
#include "visualize.hpp"
#include <SFML/Graphics.hpp>

class BubbleSort: public VisualizeSort{
	public:
		void sort(bool debug = false){
			renderChanges(changedIndexes,true);
			bool swapped = true;
			while(swapped){
				swapped = false;
				for (int i=0;i<rects.size()-1;i++){
					if(rects[i].getSize().y <  rects[i+1].getSize().y){
						swap(rects[i],rects[i+1]);
						changedIndexes[0] = i;
						changedIndexes[1] = i+1;
						if(!debug)
							renderChanges(changedIndexes);
						swapped = true;
					}
				}
			}
			isSorted = true;
			renderChanges(changedIndexes,false,true);
		}
};

class InsertionSort:public VisualizeSort{
	public:
		void sort(bool debug = false){
			for (int i=1;i<rects.size();i++){
				std::vector<sf::RectangleShape> temp;
				temp.push_back(rects[i]);
				int j = i-1;
				while(j>=0 && rects[j].getSize().y < temp[0].getSize().y){
					swap(rects[j],rects[j+1]);
					changedIndexes[0] = j;
					changedIndexes[1] = j+1;
					if (!debug)
						renderChanges(changedIndexes);
					j--;
				}
				swap(temp[0],rects[j+1]);
			}
			isSorted = true;
			renderChanges(changedIndexes,false, true);
		}
};
class MergeSort:public VisualizeSort{
	private:
		void merge(const int left, const int right, const int mid){
			float tempArr[right-left+1];
			sf::Color col[right-left+1];
			int lptr=left, rptr = mid+1, count=0;
			tempArr[right-left] = 1;
			while(tempArr[right-left] == 1){
				if(rptr>right){
					tempArr[count] = rects[lptr].getSize().y;
					col[count] = rects[lptr].getFillColor();
					lptr++;
				}else if(lptr > mid){
					tempArr[count] = rects[rptr].getSize().y;
					col[count] = rects[rptr].getFillColor();
					rptr++;
				}else if (rects[lptr].getSize().y > rects[rptr].getSize().y){
					tempArr[count] = rects[lptr].getSize().y;
					col[count] = rects[lptr].getFillColor();
					lptr++;
				}else if (rects[lptr].getSize().y < rects[rptr].getSize().y){
					tempArr[count] = rects[rptr].getSize().y;
					col[count] = rects[rptr].getFillColor();
					rptr++;
				}
				count++;
			}
			count = 0;
			for (int i=left;i<=right;i++){
				rects[i].setSize(sf::Vector2f(rects[i].getSize().x, tempArr[count]));
				rects[i].setFillColor(col[count]);
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
			return 0;
		}
	public:
		void sort(bool debug=false){
//			renderChanges(changedIndexes,true);
			mergeSort(0,rects.size()-1);
			renderChanges(changedIndexes,false,true);
		}
};
class QuickSort:public VisualizeSort{
	public:
		int computePivot(const int left, const int right, bool debug){
			int pivot = right;
			int j = left-1;
			for(int i=left;i<right;i++){
				if(rects[i].getSize().y > rects[pivot].getSize().y){
					j++;
					swap(rects[i],rects[j]);
					changedIndexes[0] = i;
					changedIndexes[1] = j;
					if (!debug)
						renderChanges(changedIndexes);
				}
			}
			swap(rects[j+1],rects[right]);
			rects[j+1].setFillColor(sf::Color::Red);
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
		void sort(bool debug=false){
			renderChanges(changedIndexes,true);
			quickSort(0,rects.size()-1, debug);
			if (!debug)
	 			renderChanges(changedIndexes,false,true);
	 		isSorted = true;
		}
};