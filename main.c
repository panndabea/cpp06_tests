#include <iostream>

class Base {
public:
    virtual ~Base() = default;  // Wichtig für dynamic_cast
    virtual void print() const { std::cout << "Base class\n"; }
};

class Derived : public Base {
public:
    void print() const override { std::cout << "Derived class\n"; }
    void derivedMethod() { std::cout << "Method only in Derived class\n"; }
};

void test_static_cast() {
    std::cout << "\nTesting static_cast:\n";
    
    Base* base = new Derived(); // Base pointer to Derived object
    
    // Downcast von Base* zu Derived*
    Derived* derived = static_cast<Derived*>(base);
    derived->print(); // Gibt "Derived class" aus
    derived->derivedMethod(); // Gibt "Method only in Derived class" aus

    delete base;
}

void test_dynamic_cast() {
    std::cout << "\nTesting dynamic_cast:\n";
    
    Base* base = new Derived(); // Base pointer to Derived object
    Derived* derived = dynamic_cast<Derived*>(base);
    
    if (derived) {
        derived->print();  // Gibt "Derived class" aus
        derived->derivedMethod();  // Gibt "Method only in Derived class" aus
    } else {
        std::cout << "Casting failed!\n";
    }

    delete base;

    // Teste den Fall eines fehlgeschlagenen Casts
    Base* base2 = new Base();
    Derived* derived2 = dynamic_cast<Derived*>(base2);
    
    if (derived2) {
        std::cout << "Casting succeeded!\n";
    } else {
        std::cout << "Casting failed!\n";  // Wird hier ausgegeben
    }

    delete base2;
}

void test_const_cast() {
    std::cout << "\nTesting const_cast:\n";
    
    const int x = 10;
    const int* ptr = &x;
    
    // Verwenden von const_cast, um einen nicht-konstanten Zeiger zu erhalten
    int* non_const_ptr = const_cast<int*>(ptr);
    *non_const_ptr = 20;  // Kein Fehler, aber dies kann gefährlich sein, da x als 'const' definiert ist
    
    std::cout << "Value after const_cast: " << x << std::endl;  // x bleibt unverändert, da const_cast nur den Zeiger verändert, nicht den Wert
}

void test_reinterpret_cast() {
    std::cout << "\nTesting reinterpret_cast:\n";
    
    int x = 42;
    char* ptr = reinterpret_cast<char*>(&x);  // reinterpret_cast zwischen int und char*

    // Dereferenzieren des char* Zeigers
    std::cout << "Reinterpreted value as char*: " << *ptr << std::endl;  // Gibt den ersten byte-Wert von x aus

    // Beispiel: Konvertierung von Pointern
    int* originalPtr = &x;
    char* charPtr = reinterpret_cast<char*>(originalPtr);
    std::cout << "Original pointer: " << originalPtr << " | Reinterpreted pointer: " << (void*)charPtr << std::endl;
}

int main() {
    std::cout << "C++06 Casting Tests\n====================\n";

    test_static_cast();
    test_dynamic_cast();
    test_const_cast();
    test_reinterpret_cast();

    std::cout << "\nAll tests completed!\n";
    return 0;
}
