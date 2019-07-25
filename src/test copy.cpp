#include <map>
#include <string>
#include <iostream>

//https://stackoverflow.com/questions/6234295/dynamically-creating-an-instance-of-a-class-from-a-string-containing-the-class-n

// also https://blog.noctua-software.com/object-factory-c++.html
class Object{ public: virtual ~Object() {} }; // base type for all objects

class ObjectFactory {
  public:
  static Object* create(const std::string& id) { // creates an object from a string
        const Creators_t::const_iterator iter = static_creators().find(id);
        return iter == static_creators().end() ? 0 : (*iter->second)(); // if found, execute the creator function pointer
    }

 private:
  typedef Object* Creator_t(); // function pointer to create Object
  typedef std::map<std::string, Creator_t*> Creators_t; // map from id to creator
  static Creators_t& static_creators() {
    static Creators_t s_creators; 
        return s_creators; 
    } // static instance of map
  template<class T = int> class Register {
    static Object* create() { 
        return new T(); 
    };
    static Creator_t* init_creator(const std::string& id) { 
        return static_creators()[id] = create; 
    }
    static Creator_t* creator;
  };
};

#define REGISTER_TYPE(T, STR) template<> ObjectFactory::Creator_t* ObjectFactory::Register<T>::creator = ObjectFactory::Register<T>::init_creator(STR)

namespace A {
    class DerivedA : public Object { 
      public:
        DerivedA() {
            std::cout << "A::DerivedA constructor\n"; 
        } 
    }; 
}
REGISTER_TYPE(A::DerivedA, "A");

namespace B { class DerivedB : public Object { public: DerivedB() { std::cout << "B::DerivedB constructor\n"; } }; }
REGISTER_TYPE(B::DerivedB, "Bee");

namespace C { class DerivedC : public Object { public: DerivedC() { std::cout << "C::DerivedC constructor\n"; } }; }
REGISTER_TYPE(C::DerivedC, "sea");

namespace D { class DerivedD : public Object { public: DerivedD() { std::cout << "D::DerivedD constructor\n"; } }; }
REGISTER_TYPE(D::DerivedD, "DEE");

int main(void)
{

  delete ObjectFactory::create("A");
  delete ObjectFactory::create("Bee");
  delete ObjectFactory::create("sea");
  delete ObjectFactory::create("DEE");
  return 0;
}