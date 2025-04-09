#include "algorithms/spn/spn_algorithm.hpp"

#include <cassert>
#include <stdexcept>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

/*
    Here is where you should define the logic for the SPN algorithm.
*/

SPNScheduler::SPNScheduler(int slice) {
    if (slice != -1) {
        throw("SPN must have a timeslice of -1");
    }
}

std::shared_ptr<SchedulingDecision> SPNScheduler::get_next_thread() {
        auto next_thread = std::make_shared<SchedulingDecision>();
        if(this->size() == 0){
            next_thread->explanation = "No threads avaialbe for scheduling.";
            return next_thread;
        }
        
        next_thread->thread = spn_queue.front();
        next_thread->explanation = "Selected from " +std::to_string(this->size()) + " threads. Will run to completion of burst.";
        spn_queue.pop_front();
        return next_thread;
}

void SPNScheduler::add_to_ready_queue(std::shared_ptr<Thread> thread) {
    auto loop_through = spn_queue.begin();
    while (loop_through != spn_queue.end() && (*loop_through)->get_next_burst(BurstType::CPU)->length <=((*thread).get_next_burst(BurstType::CPU)->length)){
        ++loop_through;
    }
    spn_queue.insert(loop_through, thread);
}

size_t SPNScheduler::size() const {
    return spn_queue.size();
}
