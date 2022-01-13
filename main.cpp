#include <QCoreApplication>
#include <future>
#include <iostream>
using namespace std;

template < typename T >
class TD; // TD == Type Displayer

template < typename T >
void deduct( T&& param )
{
    TD< T > tType;
    TD< decltype( param ) > paramType;
}

struct sample
{
    int v;
};

sample foo()
{
    return { 333 };
}

// принимает только rvalue reference
void baz( sample&& ) {}

int&& func()
{
    return 42;
}

struct _A
{
    _A& operator=( const _A& ) { return *this; }
};
void func( _A& ) {}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    sample&& reference = foo();

    int&& var = func();

    int res = var + 3;
    var = 10;

    sample() = sample();

    func( _A() = _A() );

    class Moveable
    {
    public:
        Moveable( Moveable&& other )
        {
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }
        Moveable& operator=( Moveable&& other );

        void setName( std::string st ) { str = std::move( st ); }

    private:
        int* ptr;
        std::string str;
    };

    std::future< void > f, f2;
    f = std::move( f2 );

    return a.exec();
}
