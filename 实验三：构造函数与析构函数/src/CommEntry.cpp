#include "SY2.h"

namespace COMMENTRY
{
    bool CommEntry::add(std::string name, std::string email, std::string phone)
    {
        if (COMMS::build(name, email, phone) != nullptr)
        {
            commsList.insert(std::make_unique<COMMS::Comms>(name, phone, email));
            std::cout << "添加成功" << std::endl;
            return true;
        }
        else
        {
            std::cout << "邮箱或者手机号格式不正确" << std::endl;
            return false;
        }
    }
    

    std::unordered_multiset<std::unique_ptr<COMMS::Comms>>::iterator CommEntry::find(std::string keyword)
    {
        std::regex mail(R"(@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
        std::regex ph(R"(^1)");

        if (std::regex_match(keyword, mail))
        {
            auto fuzzy = commsList.end();
            for (auto it = commsList.begin(); it != commsList.end(); ++it)
            {
                if ((*it)->email == keyword) return it;
                if (fuzzy == commsList.end() && (*it)->email.find(keyword) != std::string::npos)
                    fuzzy = it;
            }
            return fuzzy;
        }
        else if (std::regex_match(keyword, ph))
        {
            auto fuzzy = commsList.end();
            for (auto it = commsList.begin(); it != commsList.end(); ++it)
            {           
                if ((*it)->phone == keyword) return it;
                if (fuzzy == commsList.end() && (*it)->phone.find(keyword) != std::string::npos)
                    fuzzy = it;
            }
            return fuzzy;
        }
        else if (!keyword.empty())
        {
            auto fuzzy = commsList.end();
            for (auto it = commsList.begin(); it != commsList.end(); ++it)
            {
                if ((*it)->name == keyword) return it;
                if (fuzzy == commsList.end() && (*it)->name.find(keyword) != std::string::npos)
                    fuzzy = it;
            }
            return fuzzy;
        }

        return commsList.end();
    }


    std::vector<COMMS::Comms*> CommEntry::search(std::string keyword)
    {
        if (keyword.empty()) return {};

        std::vector<COMMS::Comms*> exactMatches;
        std::vector<COMMS::Comms*> fuzzyMatches;

        for (auto it = commsList.begin(); it != commsList.end(); ++it)
        {
            bool exact = ((*it)->name == keyword ||
                          (*it)->email == keyword ||
                          (*it)->phone == keyword);
            bool fuzzy = (!exact &&
                         ((*it)->name.find(keyword) != std::string::npos ||
                          (*it)->email.find(keyword) != std::string::npos ||
                          (*it)->phone.find(keyword) != std::string::npos));

            if (exact)
                exactMatches.push_back(it->get());
            else if (fuzzy)
                fuzzyMatches.push_back(it->get());
        }

        if (!exactMatches.empty()) return exactMatches;
        return fuzzyMatches;
    }


    std::vector<COMMS::Comms*> CommEntry::getAll() const
    {
        std::vector<COMMS::Comms*> result;
        for (auto& ptr : commsList)
            result.push_back(ptr.get());
        return result;
    }

    bool CommEntry::remove(const COMMS::Comms* target)
    {
        for (auto it = commsList.begin(); it != commsList.end(); ++it)
        {
            if (it->get() == target)
            {
                commsList.erase(it);
                std::cout << "删除成功" << std::endl;
                return true;
            }
        }
        std::cout << "未找到该联系人" << std::endl;
        return false;
    }

    //-------------------------------------------------
    bool CommEntry::save(const std::string& filename) const
    {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        for (auto& ptr : commsList)
            file << ptr->name << '|' << ptr->phone << '|' << ptr->email << '\n';

        return true;
    }

    bool CommEntry::load(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::string line;
        int count = 0;
        while (std::getline(file, line))
        {
            if (line.empty()) continue;

            auto pos1 = line.find('|');
            if (pos1 == std::string::npos) continue;
            auto pos2 = line.find('|', pos1 + 1);
            if (pos2 == std::string::npos) continue;

            std::string name  = line.substr(0, pos1);
            std::string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string email = line.substr(pos2 + 1);

            COMMS::Comms* c = COMMS::build(name, email, phone);
            if (c)
            {
                commsList.insert(std::unique_ptr<COMMS::Comms>(c));
                count++;
            }
        }

        if (count > 0)
            std::cout << "成功导入 " << count << " 个联系人" << std::endl;
        return true;
    }

    //-------------------------------------------

    bool CommEntry::dt(std::string keyword)
    {
        auto it = find(keyword);
        if (it != commsList.end())
        {
            commsList.erase(it);
            std::cout << "删除成功" << std::endl;
            return true;
        }
        std::cout << "未找到该联系人" << std::endl;
        return false;
    }

}