#include "algorithms.cpp"
#include <iostream>
int main(){
	MergeSort s;
	s.run();
}


/*void function3(char a)  
{  
    std::cout<<"Function 3 called with character " << a << std::endl;
}  
void function2(void (*rtp) (char)){
	std::cout << "Function 2 called." << std::endl;
    rtp('a');
}
void function1(void (*funcptr)(void (*rtp) (char))) 
{  
	std::cout << "Function 1 called" << std::endl;
    funcptr(function3);  
}  
int main()  
{  
  function1(function2);  
  return 0;  
}*/