#include "algorithms/fcfs/fcfs_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

/*
    Here is where you should define the logic for the FCFS algorithm.
*/

FCFSScheduler::FCFSScheduler(int slice) {
    if (slice != -1) {
        throw("FCFS must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> FCFSScheduler::get_next_thread() {
        auto next_thread = std::make_shared<SchedulingDecision>();
        if(this->size() == 0){
            next_thread->explanation = "No threads avaialbe for scheduling.";
            return next_thread;
        }
        next_thread->thread = fcfs_queue.front();
        next_thread->explanation = "Selected from " +std::to_string(this->size()) + " threads. Will run to completion of burst.";
        fcfs_queue.pop();
        return next_thread;
}

void FCFSScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
        fcfs_queue.push(thread);
}

size_t FCFSScheduler::size() const {
        // TODO: implement me!
        return fcfs_queue.size();
}
