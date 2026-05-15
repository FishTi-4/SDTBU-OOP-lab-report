#include "SY1.h"

namespace COMMENTRY
{
    class CommEntry{
        std::unordered_multiset<std::unique_ptr<COMMS::Comms>> commsList;
        public:
        bool add(std::string name, std::string email, std::string phone);
        std::unordered_multiset<std::unique_ptr<COMMS::Comms>>::iterator find(std::string keyword);
        std::vector<COMMS::Comms*> search(std::string keyword);
        std::vector<COMMS::Comms*> getAll() const;
        bool remove(const COMMS::Comms* target);
        bool dt(std::string keyword);
        bool save(const std::string& filename) const;
        bool load(const std::string& filename);
    };
    
}