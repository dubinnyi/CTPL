#include <ctpl.h>
#include <iostream>
#include <string>



void first(int id) {
    std::cout << "hello from " << id << ", function\n";
}

void aga(int id, int par) {
    std::cout << "hello from " << id << ", function with parameter " << par <<'\n';
}

struct Third {
    Third(int v) { this->v = v; std::cout << "Third ctor " << this->v << '\n'; }
    Third(Third && c) { this->v = c.v; std::cout<<"Third move ctor\n"; }
    Third(const Third & c) { this->v = c.v; std::cout<<"Third copy ctor\n"; }
    ~Third() { std::cout << "Third dtor\n"; }
    int v;
};

void mmm(int id, const std::string & s) {
    std::cout << "mmm function " << id << ' ' << s << '\n';
}

void ugu(int id, Third & t) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "hello from " << id << ", function with parameter Third " << t.v <<'\n';
}

int main(int argc, char **argv) {
    ctpl::thread_pool p(2 /* two threads in the pool */);


    // change the number of treads in the pool

    int p_size = 3;
    p.resize(p_size);

    std::string s2 = "result test";
    auto f1 = p.push([s2](int){
        return s2;
    });

    std::vector<decltype(f1)> result_vector;

    for(int i = 0; i< 3 ; i++){
      std::string s2 = "result "+std::to_string(i);
      result_vector.push_back(p.push([s2](int){
          return s2;
      }) );
    }
    // other code here
    //...
    p.stop(true);

    for(int i = 0; i< 3 ; i++){
       auto res_get = result_vector[i].get();
       std::cout << "returned \'" << res_get << "\'\n";
    }
 
    return 0;
}
