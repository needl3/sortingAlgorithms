#include <iostream>
#include "visualize.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

class BubbleSort: public VisualizeSort{
	public:
		void sort(std::vector<sf::RectangleShape>& rects, bool debug = false){
			renderChanges(1,true);
			bool swapped = true;
			while(swapped){
				swapped = false;
				for (int i=0;i<rects.size()-1;i++){
					if(rects[i].getSize().y <  rects[i+1].getSize().y){
						swap(rects[i],rects[i+1]);
						renderChanges(i);
						swapped = true;
					}
				}
			}
			isSorted = true;
			renderChanges(0,true);
		}
};


class InsertionSort:public VisualizeSort{
	public:
		void sort(std::vector<sf::RectangleShape>&rects, bool debug = false){
			renderChanges(1,true);
			for (int i=1;i<rects.size();i++){
				std::vector<sf::RectangleShape> temp;
				temp.push_back(rects[i]);
				int j = i-1;
				while(j>=0 && rects[j].getSize().y < temp[0].getSize().y){
					swap(rects[j],rects[j+1]);
					renderChanges(j);
					j--;
				}
				swap(temp[0],rects[j+1]);
			}
			renderChanges(0,true);
		}
};
class MergeSort:public VisualizeSort{
	public:
		void sort(std::vector<sf::RectangleShape>&rects, bool debug=false){

		}
};
class QuickSort:public VisualizeSort{
	public:
		void sort(std::vector<sf::RectangleShape>&rects, bool debug=false){
			
		}
};
int main(){
//	BubbleSort vs;
	InsertionSort vs;
	vs.run();
	return 0;
}