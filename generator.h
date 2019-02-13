#include <chrono>

class SeqIdGenerator {
  public:
        SeqIdGenerator() = default;
        ~SeqIdGenerator() = default;

        void set_epoch(uint64_t epoch){
                epoch_ = epoch;
        }
        void set_worker_id(int32_t woker_id){
                woker_id_ = woker_id;
        }
        int64_t NextId(){
                        int64_t value = 0;
                        uint64_t time = get_time() - epoch_;
                        value = time << 22;
                        value |= (woker_id_ & 0x3FF) << 12;
                        value |= sequence_++ & 0xFFF;
                        if (sequence_ == 0x1000){
                                        sequence_ = 0;
                        }
                        return value;   
        }
  
  private:
        uint64_t get_time(){
                return static_cast<uint64_t>((std::chrono::duration_cast<std::chrono::milliseconds>
                                                (std::chrono::system_clock::now().time_since_epoch())).count());
        }
        uint64_t epoch_ = 1420041600000L;
        uint64_t time_ = 0;
        uint64_t woker_id_ = 0;
        int32_t sequence_ = 0;
};
