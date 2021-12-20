#include "Timer.hpp"
#include <thread>
#include<iostream>
Timer::Timer()
{

}
void Timer::sleep(unsigned int time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));  
}
void Timer::start()
{
    m_Start = std::chrono::high_resolution_clock::now();
}
double Timer::elapsedSeconds()
{
    m_End = std::chrono::high_resolution_clock::now();

    auto difference = m_End-m_Start;
    auto elapsedTime= std::chrono::duration<double>(difference);
    m_Start=m_End;
    return elapsedTime.count();
}