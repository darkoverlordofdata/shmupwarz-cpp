#include <map>
#include <string>
#include <iostream>

//https://stackoverflow.com/questions/6234295/dynamically-creating-an-instance-of-a-class-from-a-string-containing-the-class-n

// also https://blog.noctua-software.com/object-factory-c++.html

namespace frodo 
{

  class Component{ public: virtual ~Component() {} }; // base type for all objects

  class ComponentFactory {
    public:
    static Component* create(const std::string& id) { // creates an object from a string
          const Creators_t::const_iterator iter = static_creators().find(id);
          return iter == static_creators().end() ? 0 : (*iter->second)(); // if found, execute the creator function pointer
      }

  private:
    typedef Component* Creator_t(); // function pointer to create Component
    typedef std::map<std::string, Creator_t*> Creators_t; // map from id to creator
    static Creators_t& static_creators() {
      static Creators_t s_creators; 
          return s_creators; 
      } // static instance of map
    template<class T = int> class Register {
      static Component* create() { 
          return new T(); 
      };
      static Creator_t* init_creator(const std::string& id) { 
          return static_creators()[id] = create; 
      }
      static Creator_t* creator;
    };
  };

}

#define RegisterType(T) template<> frodo::ComponentFactory::Creator_t* frodo::ComponentFactory::Register<T>::creator = frodo::ComponentFactory::Register<T>::init_creator(#T)

namespace A {
    class DerivedA : public frodo::Component { 
      public:
        DerivedA() {
            std::cout << "A::DerivedA constructor\n"; 
        } 
    }; 
}
RegisterType(A::DerivedA);

namespace B { class DerivedB : public frodo::Component { public: DerivedB() { std::cout << "B::DerivedB constructor\n"; } }; }
RegisterType(B::DerivedB);

namespace C { class DerivedC : public frodo::Component { public: DerivedC() { std::cout << "C::DerivedC constructor\n"; } }; }
RegisterType(C::DerivedC);

namespace D { class DerivedD : public frodo::Component { public: DerivedD() { std::cout << "D::DerivedD constructor\n"; } }; }
RegisterType(D::DerivedD);

int main(void)
{

  delete frodo::ComponentFactory::create("A::DerivedA");
  delete frodo::ComponentFactory::create("B::DerivedB");
  delete frodo::ComponentFactory::create("C::DerivedC");
  delete frodo::ComponentFactory::create("D::DerivedD");
  return 0;
}