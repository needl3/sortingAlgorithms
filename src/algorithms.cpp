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
		void sort(bool debug=false){
			
		}
};
class QuickSort:public VisualizeSort{
	public:
		int computePivot(int left, int right){
			int pivot = right;
//			std::cout << "Initial Pivot Element: " << rects[pivot].getSize().y << "  Initial Index: " << pivot << std::endl;
			for(int i=left;i<pivot-1;i++){
				if(rects[i].getSize().y > rects[i+1].getSize().y){
					swap(rects[i],rects[i+1]);
					changedIndexes[0] = i;
					changedIndexes[1] = i+1;
					renderChanges(changedIndexes);
				}
				if(rects[i].getSize().y > rects[pivot].getSize().y){
					swap(rects[i],rects[pivot]);
					pivot = i;
					changedIndexes[0] = i;
					changedIndexes[1] = pivot;
					renderChanges(changedIndexes);	
				}
			}
//			std::cout << "Final Pivot Element: " << rects[pivot].getSize().y << "  Final Index: " << pivot << std::endl << std::endl;
			return pivot;
		}
		int quickSort(const int left, const int right){
			if (left == right)
				return true;
			int pivot = computePivot(left,right);
			quickSort(left, pivot-1);
			quickSort(pivot+1,right);
			return true;
		}
		void sort(bool debug=false){
			quickSort(0,rects.size());
 			renderChanges(changedIndexes,false,true);
		}
};