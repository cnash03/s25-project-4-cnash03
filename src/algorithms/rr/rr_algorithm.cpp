#include "algorithms/rr/rr_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

/*
    Here is where you should define the logic for the round robin algorithm.
*/

RRScheduler::RRScheduler(int slice) {
    if(slice == -1){
        this->time_slice = 3;
    } else{
        this->time_slice=slice;
    }
}

std::shared_ptr<SchedulingDecision> RRScheduler::get_next_thread() {
    auto next_thread = std::make_shared<SchedulingDecision>();
        if(this->size() == 0){
            next_thread->explanation = "No threads avaialbe for scheduling.";
            return next_thread;
        }
        next_thread->thread = rr_queue.front();
        next_thread->explanation = "Selected from " +std::to_string(this->size()) + " threads. Will run for at most " + std::to_string(this->time_slice) + " ticks.";
        rr_queue.pop();
        return next_thread;
}


void RRScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
   rr_queue.push(thread);
}

size_t RRScheduler::size() const {
    return rr_queue.size();
}
