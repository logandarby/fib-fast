#include <chrono>

class Timer {
public:
    Timer() = default;
    void start() {
        m_start = std::chrono::high_resolution_clock::now();
    }
    void stop() {
        m_end = std::chrono::high_resolution_clock::now();
    }
    void reset() {
        m_start = std::chrono::high_resolution_clock::now();
        m_end = std::chrono::high_resolution_clock::now();
    }
    double getElapsedSeconds() {
        return std::chrono::duration<double>(m_end - m_start).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
};
