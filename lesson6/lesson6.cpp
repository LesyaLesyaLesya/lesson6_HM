// Lesson6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <deque>
#include <map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <string_view>
#include <mutex>
#include <thread>


using namespace std;
mutex m;

class pcout
{
private:
    lock_guard<mutex> lg;
public:
    pcout():lg(lock_guard<mutex>(m))
    {
     
    }
    ~pcout() = default;

    template <typename T>
    pcout& operator<< (const T& outputData)
    {
        cout << outputData;

        return *this;
    }

    pcout& operator<< (ostream& (*f)(ostream&))
    {
        cout << f;

        return *this;
    }

    
};

bool simpleMumber(int n)
{
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0) return false;

        
    }
    return true;
}

void someFunction(int threadNumber)
{
    pcout() << "start thread " << threadNumber << endl;

}
void Zadanie1()
{
    /*--------------------------------------------------
    Создайте потокобезопасную оболочку для объекта cout. Назовите ее pcout. 
    Необходимо, чтобы несколько потоков могли обращаться к pcout и информация выводилась в консоль. 
    Продемонстрируйте работу pcout.

    ----------------------------------------------------*/
    

    thread t1{ someFunction,1 };
    thread t2{ someFunction,2 };
    thread t3{ someFunction,3 };
    t1.join();
    t2.join();
    t3.join();


};


void Zadanie2()
{
    /*--------------------------------------------------
    Реализовать функцию, возвращающую i-ое простое число (например, миллионное простое число равно 15485863).
    Вычисления реализовать во вторичном потоке. В консоли отображать прогресс вычисления (в основном потоке)
    ----------------------------------------------------*/
   
    cout << "Input i" << endl;
    int i;
    int currIt{ 1 };
    int startNumber{ 2 };
    cin >> i;

    

    while (true)
    {
        if (currIt < i)
        {
            thread th([=, &currIt, &startNumber]()
                {
                    if (simpleMumber(startNumber))
                    {
                        currIt++;
                    }

                    startNumber++;
                });
            th.join();
        }
        else
            break;

       
    } 
    cout << --startNumber;


};



void addNum(vector<int>& v)
{
    srand(time(NULL));
    lock_guard lg(m);
    cout << "Start Adding"<<endl;
    v.push_back(rand()%100);
    this_thread::sleep_for(1s);
    copy(v.begin(), v.end(),ostream_iterator<int>(cout, " "));
    cout << endl << "Stop Adding";
}

void thief(vector<int>& v)
{
    cout << "Start robbery" << endl;
    lock_guard lg(m);
    sort(v.begin(), v.end());
    if (!v.empty())
    {
        v.pop_back();
    } 
    this_thread::sleep_for(0.5s);
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl << "Stop robbery";
}

void Zadanie3()
{
    /*--------------------------------------------------
    Промоделировать следующую ситуацию. Есть два человека (2 потока): хозяин и вор.
    Хозяин приносит домой вещи (функция добавляющая случайное число в вектор с периодичностью 1 раз в секунду).
    При этом у каждой вещи есть своя ценность.
    Вор забирает вещи (функция, которая находит наибольшее число и удаляет из вектора с периодичностью 1 раз в 0.5 секунд),
    каждый раз забирает вещь с наибольшей ценностью.
    ----------------------------------------------------*/
    mutex m;
    vector<int> v{500,5,99,11,120,30};
    while (true)
    {
        thread th1(addNum, ref(v));
        thread th2(thief, ref(v));
        th1.join();
        th2.join();
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");

    std::cout << "Введите номер задания цифрой" << std::endl;
    unsigned short nomerZadania;

    std::cin >> nomerZadania;

    switch (nomerZadania)
    {
    case 1:Zadanie1(); break;

    case 2:Zadanie2(); break;

    case 3:Zadanie3(); break;

    default: break;
    }


    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
