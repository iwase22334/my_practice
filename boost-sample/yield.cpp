#include <boost/asio.hpp>
#include <boost/asio/yield.hpp>
#include <iostream>

struct functor {
    int operator()()
    {
        reenter(coro_) {
            yield printf("a\n");
            yield return 1;
            yield return 2;
        }
        return 3;
    }

    private:
    boost::asio::coroutine coro_;
};

int main()
{

    functor f;
    std::cout << f() << std::endl;
    std::cout << f() << std::endl;
    std::cout << f() << std::endl;
    std::cout << f() << std::endl;
    std::cout << f() << std::endl;

}
