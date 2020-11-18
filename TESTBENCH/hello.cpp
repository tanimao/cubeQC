#include <boost/python.hpp>
#include <stdio.h>

char greet(int x){
    printf("printHELLOdfa!!\n");
    return '0' + x + 1;
}

char const* fine(){
    return "How are you?";
}

BOOST_PYTHON_MODULE(hello){
  using namespace boost::python;
    def("greet", greet);
    def("fine", fine);
}

