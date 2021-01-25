#include <iostream>
 
using namespace std;

class BaseClass
{
    public:
        virtual void show()=0;
};
class DerivedClass:public BaseClass
{
    public: 
        int x;
        int y;
        void show(){
            cout<<x<<endl;
            cout<<y<<endl;
        };
};

int main()
{
    BaseClass* pBaseObject = NULL;
    DerivedClass DerivedObject;
    pBaseObject = &DerivedObject;
    pBaseObject->show();
    return 0;
}