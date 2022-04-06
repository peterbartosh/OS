#ifndef BUFFERED_CHANNEL_H_
#define BUFFERED_CHANNEL_H_

#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

template<class T>
class BufferedChannel {
public:
    explicit BufferedChannel(int size_) {size = size_;}

    void Send(T value) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, !closed && queue.size() != size);
        if (closed) throw std::runtime_error("Зачынена");
        queue.emplace(value);
        mtx.unlock();
        cv.notify_one();
    }

    std::pair<T, bool> Recv() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, !closed && !queue.empty());
        T value = std::move(queue.front());
        queue.pop();
        mtx.unlock();
        cv.notify_one();
        return std::make_pair(value, !closed);
    }

    void Close() {
        mtx.lock();
        closed = true;
        mtx.unlock();
        cv.notify_all();
    }

private:
    size_t size;
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool closed =  false;
};

#endif // BUFFERED_CHANNEL_H_
