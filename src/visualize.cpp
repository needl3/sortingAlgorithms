#include <iostream>
#include "visualize.hpp"
VisualizeSort::VisualizeSort(){
	//Fill the array
	window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT),"Sort Visualizer");
	events = new sf::Event;
	window->setFramerateLimit(FRAMERATE);

	//Prepare sound after loading to buffer
	sbuf->loadFromFile("assets/beep.wav");
	sound->setBuffer(*sbuf);

	//Prepare data
	data_array = new int[DATA_BITS];

	for (int i=0;i<DATA_BITS;i++){
		data_array[i] = i;
	}
	shuffle(data_array);
}
VisualizeSort::~VisualizeSort(){
	delete window;
	delete events;
	delete sound;
	delete sbuf;
	delete sort_thread;
}
void VisualizeSort::shuffle(int *arr){
	int random_position,temp_var;
	for(int i=0;i<DATA_BITS;i++){
		random_position =rand()%DATA_BITS;
		temp_var = arr[i];
		arr[i] = arr[random_position];
		arr[random_position] = temp_var;
	}
}
void VisualizeSort::setTitle(std::string title){
	window->setTitle(title);
}
void VisualizeSort::playBeep(int index){
	sound->setPitch(1.0f+(float)data_array[index]/DATA_BITS);
	sound->play();
}
void VisualizeSort::stopBeep(){
	sound->stop();
}

void VisualizeSort::displayData(){
	for (int i=0;i<DATA_BITS;i++){
		std::cout << data_array[i] << " ";
	}
	std::cout << std::endl;
}

int* VisualizeSort::giveData(){
	return data_array;
}

void VisualizeSort::swap(int l_index, int r_index,
							void (*fptr)(std::chrono::milliseconds const&/* = std::this_thread::sleep_for*/)){
	int temp = data_array[r_index];
	data_array[r_index] = data_array[l_index];
	data_array[l_index] = temp;
	playBeep(r_index);
	playBeep(l_index);
	fptr(std::chrono::milliseconds(THREAD_DELAY));
}

void VisualizeSort::renderChanges(bool last_animation /*=false*/,
								  void (*fptr)(std::chrono::milliseconds const&) /* = std::this_thread::sleep_for*/)
{
	float rect_height;

	if(!last_animation){
		//First Display at once
		for(int i=0;i<DATA_BITS;i++){
			rect_height = -(float)data_array[i]/DATA_BITS*HEIGHT;
			rect_shape.setSize(sf::Vector2f(rect_width,rect_height));
			rect_shape.setFillColor(sf::Color(50
									,(float)i/WIDTH*255*rect_width
									,(float)data_array[i]/HEIGHT*255
									));
			rect_shape.setPosition(i*(rect_width+POSITION_OFFSET),HEIGHT);
			window->draw(rect_shape);
		}
	}else if(last_animation){
		//Last display animation
		for(int i=0;i<DATA_BITS;i++){
			rect_height = -(float)data_array[i]/DATA_BITS*HEIGHT;
			playBeep(i);
			rect_shape.setFillColor(sf::Color::Cyan);
			rect_shape.setSize(sf::Vector2f(rect_width,rect_height));
			rect_shape.setPosition(i*(rect_width+POSITION_OFFSET),HEIGHT);
			window->draw(rect_shape);
			window->display();
			fptr(std::chrono::milliseconds(THREAD_DELAY));
		}
	}
}
void VisualizeSort::handleInputs(){
	window->pollEvent(*events);
		switch (events->type){
	        case sf::Event::Closed:
	        	kill_signal = true;
	            window->close();
	            break;
	        case sf::Event::KeyPressed:
	            if (events->key.code == sf::Keyboard::Q){
	            	kill_signal = true;
	                window->close();
		        }
				else{
					if (!is_sorted && !is_sorting)
						sort_thread = new std::thread(&VisualizeSort::sort, this,false);
		        }
	            break;
    	}
}
void VisualizeSort::run(){
	//Draw initial shuffled states
	while(window->isOpen() && !is_sorted){
		handleInputs();
		window->clear();
		renderChanges(false,nullptr);
		window->display();
	}
	sort_thread->join();

//	Vice city Cheat to disable main thread exit after last animation... lul
	while(window->isOpen()){handleInputs();}
}