
// Polymorphism: Method Overriding (Runtime Polymorphism)
// A virtual function in Object-Oriented Programming (OOP) is a function that is defined in the base class and is meant to be overridden in derived classes.

#include <bits/stdc++.h>
using namespace std;

// Base class
class Shape {
    public:
        // Virtual function
        virtual void draw() {
            cout << "Drawing a Shape" << endl;
        }
};

// Derived class
class Circle : public Shape {
    public:
        // Overriding the virtual function in the derived class
        void draw() override{
            cout<<"Drawing a circle"<<endl;
        }
};

// Derived class
class Rectangle : public Shape {
    public:
        // Overriding the virtual function in the derived class
        void draw() override{
            cout<<"Drawing a rectangle"<<endl;
        }
};

int main(){
    // Creating base class pointers
    Shape* shape1;
    Shape* shape2;

    // Creating derived class objects
    Circle circle;
    Rectangle rectangle;

    // Pointing base class pointer to derived class objects
    shape1 = &circle;
    shape2 = &rectangle;

    //or we can do like
    // Shape* shape1 = new Circle;
    // Shape* shape2 = new Rectangle;

    // Calling the draw function
    // Since 'draw' is virtual, it calls the derived class's version of the function
    shape1->draw();  // Output: Drawing a Circle
    shape2->draw();  // Output: Drawing a Rectangle

    return 0;
}