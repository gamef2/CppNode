#include <iostream>
#include <ctime>
#include <random>

using namespace std;

int main(){
    std::default_random_engine e(time(0));
    std::uniform_int_distribution<unsigned> u(1, 10);

    int n = 11;
    vector<int> ivec(n);
    int i, x = 0;
    cout << "打印内容:" << endl;
    for (i = 0; i < n - 1; ++i)
        ivec[i] = i + 1;
    ivec[i] = u(e); // 末尾为随机数

    for (auto i : ivec)
        cout << i << " ";
    cout << "\n";

    int cnt = 0;
    for (i = 1; i < n; ++i){
        if (cnt++ & 3 == 3){
            cout << endl;
            cnt = 0;
        }
        cout << x << " ^ " << i << " = ";
        x ^= i;
        cout << x << "  ";
    }
    cnt = 0;
    cout << "\n\n";
    for (auto i : ivec) {
        if (cnt++ & 3 == 3){
            cout << endl;
            cnt = 0;
        }
        cout << x << " ^ " << i << " = ";
        x ^= i;
        cout << x << "  ";
    } // 异或原理不同出1。剩下的就是多出来成对的数
    cout << "\n结果 x= " << x << "\t ivec[" << n - 1 << "] = " << ivec[n - 1] << endl;
}
