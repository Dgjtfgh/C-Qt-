## C和C++中的struct的区别
    c中的struct不可以含有成员函数，而c++中的struct可以。
    c++中struct和class的主要区别在于默认的存取权限不同，struct默认为public，而class默认为private。

## 数组和链表的区别
    数组：数据顺序存储，固定大小
    连表：数据可以随机存储，大小可动态改变

## C++中为什么用模板类。
    (1) 可用来创建动态增长和减小的数据结构
    (2) 类型无关的，具有很高的可复用性。
    (3) 在编译时检查数据类型，保证了类型安全
    (4) 平台无关的，可移植性
    (5) 可用于基本数据类型

## 变量的声明和定义的区别
  - 为变量分配地址和存储空间的称为定义，不分配地址的称为声明。
  - 一个变量可以在多个地方声明，只在一个地方定义。
  - 加入extern修饰的是变量的声明，说明此变量将在文件以外或在文件后面部分定义。
  
## sizeof和strlen的区别。
    (1)sizeof是一个操作符，strlen是库函数。
    (2)sizeof的参数可以是数据的类型，也可以是变量，而strlen只能以结尾为‘\0‘的字符串作参数。
    (3)编译器在编译时就计算出了sizeof的结果。而strlen函数必须在运行时才能计算出来。并且sizeof计算的是数据类型占内存的大小，而strlen计算的是字符串实际的长度。
    (4)数组做sizeof的参数不退化，传递给strlen就退化为指针了。
 
## C语言的关键字static 和C++ 的关键字static 有什么区别
  - 在C中static用来修饰局部静态变量和外部静态变量、函数。
  - C++中除了上述功能外，还用来定义类的成员变量和函数。即静态成员和静态成员函数。

## C中的malloc和C＋＋中的new的区别 
    (1) new、delete 是操作符，可以重载，只能在C++中使用。 
    (2) malloc、free是函数，可以覆盖，C、C++中都可以使用。 
    (3) new 可以调用对象的构造函数，对应的delete调用相应的析构函数。 
    (4) malloc仅仅分配内存，free仅仅回收内存，并不执行构造和析构函数
    (5) new、delete返回的是某种数据类型指针，malloc、free返回的是void指针。