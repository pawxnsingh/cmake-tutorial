#include <iostream>
// headers files must be included
#include "sum.hh"
// how to create library and link them with cmake
#include  <Eigen/Dense>


int main(){
    std::cout << "im in src/hello.cc\n";
    std::cout << "Sum of 2.2 and 3.3: " << sum(2.2f,3.3) << std::endl;
    Eigen::Vector2d v2 {1.0,2.0};
    std::cout << v2.norm() << std::endl;

}