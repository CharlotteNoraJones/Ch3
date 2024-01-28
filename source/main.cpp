

// //Ch. 3 Notes

// // 3.1 Introduction
// // declaration species all thats needed to use a function or type

// double sqrt(double); // the square root function takes a double and returns a double

// class Vector { // what is needed to use a Vector
//     public:
//         Vector(int s);
//         double& operator[](int i);
//         int size();
//     private:
//         double* elem;
//         int sz;
// };

// // in function definitions can be elsewhere from function declarations. 

// double sqrt(double d) // definition of sqrt()
// {
//     // ..algorithim found in math textbook
// }

// // Vector definition
// Vector::Vector(int s) //definition of the constructor
//     : elem {new double[s]}, sz{2} // initialize members
//     {
//     }

// double& Vector::operator[](int i) // definition of subscripting
// {
//     return elem[i];
// }

// int Vector::size() { //definition of size();
//     return sz;
// }

// // an entity can have many declarations, but only one definition

//3.2 Seperate Compilation
// seperate compilation: user code sees only declarations of the types and functions used. 
    // header files: places declarations in seperate files, #include them
    // modules: define module files, compile them seperatly, import them where needed. 
        // only explicitly imported declarations are seens by code importing the module

// headers go back to very early c++, modules are new in 20

// 3.2.1 Header Files

// Vector.h
// class Vector {
//     public: 
//         Vector(int s);
//         double& operator[](int i);
//         int size();
//     private:
//         double* elem; // elem points to an array of sz doubles
//         int sz;
// };

// then include the header file to access the interface

// #include "Vector.h" // get Vector's interface
// #include <cmath> // get the standard-library math function interface inclusding sqrt()

// double sqrt_sum(Vector& v)
// {
//     double sum = 0;
//     for (int i = 0; i!=v.size(); ++i)
//         sum+=std::sqrt(v[i]); // sum of square roots
//     return sum;
// }

// the .cpp file including Vector should also include the .h file with the interface. 

//Vector.cpp
// #include "Vector.h" //get Vector's interface

// Vector::Vector(int s)
//     :elem{new double[s]}, sz{s} // initialize members
// {
// }

// double& Vector::operator[](int i)
// {
//     return elem[i];
// }

// int Vector::size() {
//     return sz;
// }

// organize programs as sets of modules will well-defined dependencies

// disadvantages of header files
// compilation time: if you #include header.h 101 times, the compiler processes it 101 times
// order dependencies: the order in which headers are included can affect the meaning of the code
// in other headers
// inconsistencies: defining an entity slightly differently in two different files can result in errors. 
// transitivity: all code needed to express a definition has to be included in a header file. This
// can result in a header file becoming dependant on implementation details. 

// // 3.2.2 Modules

// // this will result in errors, gcc doesn't really support modules right now

// // file Vector.CPP

// export module Vector; // defining the module called "Vector"

// export class Vector {
//     public:
//         Vector(int s);
//         double& operator[](int i);
//         int size();
//     private: 
//         double * elem; // elem points to an array of sz doubles
//         int sz;
// };

// Vector::Vector(int s) 
//     :elem{new double[s]}, sz{s} //initialize members
// {
// }

// double& Vector::operator[](int i)
// {
//     return elem[i];
// }

// int Vector::size()
// {
//     return sz;
// }

// export bool operator==(const Vector& v1, const Vector& v2)
// {
//     if (v1.size()!=v2.size())
//         return false;
//     for (int i=0; i<v1.size();++i)
//         if(v1[i]!=vs[i])
//             return false;
//     return true;
// }

// // file user.CPP
// import Vector; //get Vector's interface
// #include <cmath> //get the standard-library math function interface including sqrt()

// double sqrt_sum(Vector& v)
// {
//     double sum = 0;
//     for (int i=0;i!=v.size();++i)
//         sum+=std::sqrt(v[i]); // sum of square roots
//     return sum;
// }

// //Advantages of modules
// // modules are only compiled once
// // modules can be imported in any order without changing their meaning
// // import is not transitive

// // Vector with declarations and definitions in the same file. 
// export module Vector; //defining the moduel "Vector"

// export class Vector {
//     //..
// };

// export bool operator==(const Vector& v1, const Vector& v2)
// {
//     // 
// }

// // example of how it's easy to hide implementation details with modules

// export module vector_printer;

// import std;

// export
// template<typename T> // parameterizing a function with a type
// void print(std::vector<T>& v) // this is the (only) function seen by users
// {
//     std::cout << "{\n";
//     for (constt& val: v)
//         std::cout << " " << val << "\n";
//     std::cout << '}';
// }

// // this means we don't gain access to all of the standard library

// // 3.3 Namespaces
// // namespaces express that some names belong together

// namespace My_code {
//     class complex {
//         //
//     };

//     complex sqrt(complex);
//     //

//     int main();
// }

// int My_code::main()
// {
//     complex z {1, 2};
//     auto z2 = sqrt(z);
//     std::cout << '{' << z2.real() << ',' << z2.imag() << "}\n";
//     //
// }

// int main()
// {
//     return My_code::main();
// }

// // use namespace_name:: to access namespace members
// // using declaration can bring all namespace members into scope

// void my_code(vector<int>& x, vector<int>& y)
// {
//     using std::swap; //make the standard-library swap available locally
//     //
//     swap(x,y); // std::swap()
//     other::swap(x,y); // some other swap()
// }

// // using namespace std; // grants access to standard library namespace

// // example

// export module vector_printer;

// import std;
// using namespace std;

// export
// template<typename<T>
// void print(vector<T>&v) // this is the (only) function seen by users
// {
//     cout << "{\n";
//     for(const T& val: v)
//         cout << " " << val << '\n';
//     cout << '}';
// }

// // 3.4 Function arguements and return values. 

// // the best way to pass data from different parts of a program are functions

// int sum(const vector<int>& v) // passing an immutable reference
// {
//     int s = 0;
//     for (const int i : v)
//         s += i;
//     return s;
// }

// vector fib = {1, 2, 3, 5, 8, 13, 21};

// int x = sum(fib); // x becomes 53

// // global variables are gross and stinky :(

// // state can also be used to transfer information
// // state should only be shared between members of a shared well-defined abstraction (like a class)

// // concerns when passing info in/out of functions
// // is an object copied or shared?
// // if an object is shared, is it mutable?
// // is an object moved, leaving an "empty object" behind

// // 3.4.1 Arguement Passing

// void test(vector<int> v, vector<int>& rv) // v is passed by value; rv is passed by reference
// {
//     v[1] = 99; // modify v (a local variable)
//     rv[2] = 66; // modify whatever rv refers to 
// }

// int main()
// {
//     vector fib = {1, 2, 3, 5, 8, 13, 21};
//     test(fib, fib);
//     std::cout << fib[1] << '' << fib[2] << "\n" // prints 2 66
// }

// // if performance matters, pass small variables by value and big ones by reference
// // small usually means "size of two or three pointers or less"

// // default function arguement example

// void print(int value, int base=10); // print value in base "base"

// print(x,16) // hexadecimal
// print(x, 60); // sexagesimal (Sumerian)
// print(x); // use the default: decimal

// // this a notationally simpler alternatie to overloading:
// void print(int value, int base) // print value in base "base"

// void print(int value) // print value in base 10
// {
//     print(value, 10)
// }

// // using default arguements means you only have to define the function once. 

//3.4.2 Value Return
// default for a return value is to copy-that's fine for small objects
// return "by reference" only when we need to grant the caller access to something
// that's not local to the function. 

class Vector {
    public:
    //
        double& operator[](int i) {return elem[i];} // return reference to the ith element
    private:
        double* elem; // elem points to an array of sz
        // 
};

int& bad()
{
    int x;
    //
    return x; // bad: return a reference to the local variable x
}

int& bad()
{
    int x;
    //
    return x; // bad: return a reference to the local variable x
}

// don't return a reference to a local variable
// they die when the function ends

int& bad()
{
    int x;
    //
    return x; // bad: return a reference to the local variable x
    // x ceases to exists when the function ends
}

// how to pass large info out of a function
Maxtrix operator+(const Matrix& x, const Matrix& y)
{
    Matrix res;
    // for all res[i,j], res[i,j] = x[i,j]+y[i,j]] ...
    return res;
}

Matrix m1, m2;
Matrix m3 = m1+m2; // no copy

// matrixes are large and expensive to copy. 
// use a move constructor instead of copying it. 

// copy elison: when a compiler optimizes the copying of a large value to use a move constructor automatically

// don't refress to manual memory management:

Matrix* add(const Maxtrix&x, const Matrix& y) // complicated and error-prone 20th century style
{
    Matrix* p = new Matrix;
    // for all *p[i,j], *p[i,j] = x[i,j]+y[i,j]...
    return p;
}

Matrix m1, m2;
// ..
Matrix* m2 = add(m1, m2); // just copy a pointer
// ..
delete m3; // easily forgotten

// this is common in older code and creators hard-to-find errors

// 3.4.3 Return Type Deduction
// return type of a function be be decuded from its return value

auto mul(int i, double d) {return i*d} //here, "auto" means "deduce the return type"

//this can be useful, but doens't offer a stable interface

// 3.4.4 Suffix Return Type
// it's possible to add the return type after the arguement list
// this lets us be explicit about return type

auto mul(int i, double d) -> double {return i*d;} // the return type is "double"

// more examples
auto next_elem() -> Elem*;
auto exit(int) -> void;
auto sqrt(double) -> double;

// 3.4.5 structured binding
// functions can return classes

struct Entry {
    string name;
    int value;
}

Entry read_entry(istream& is) // naive read function
{
    string s;
    int i;
    is >> s >> i;
    return {s, i};
}

auto e = read_entry(cin);

std::cout << "{" << e.name << " , " << e.value << "}\n";

// Entry members can be unpacked into local variables

auto[n, v] = read_entry(is); // structured binding example
cout << "{" << n << " , " << v << " }\n";

// structured binding: giving local names to members of a class object

map<string, int> m;
// ... fill m ...
for (const auto [key, value] : m)
    std::cout << "{" << key << "," << value << "}\n";

// auto can be decorated with const and &

void incr(map<string,int>& m) // increment the value of each element of m
{
    for (auto& [key, value] : m)
        ++value;
}

// it's also possible to handle classes where access is through member functions
complex<double> z = {1, 2};
auto[re, im] = z+2; //re=3; im=2
