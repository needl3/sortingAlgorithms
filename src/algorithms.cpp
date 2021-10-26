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
	public:

		void mergeSort(const int left, const int right){
		}
		void sort(bool debug=false){

		}
};
class QuickSort:public VisualizeSort{
	public:
		int computePivot(int left, int right, bool debug){
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