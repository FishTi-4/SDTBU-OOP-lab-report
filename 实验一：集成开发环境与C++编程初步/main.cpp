#include "SY1.h"
#include <limits>

using namespace std;

void cleanBuffer()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitEnter()
{
    cout << "\n按回车键继续...";
    cin.get();
}

void displayContact(const COMMS::Comms* c, int index)
{
    cout << "  " << index << ".\t姓名: " << c->name
         << "\t电话: " << c->phone
         << "\t邮箱: " << c->email << '\n';
}

int main()
{
    COMMENTRY::CommEntry entry;

    if (filesystem::exists("contacts.txt"))
        entry.load("contacts.txt");

    int choice;

    do {
        system("clear");
        cout << "┌──────────────────────────────────────────────┐\n"
                "│               通讯录管理系统                  │\n"
                "├──────────────────────────────────────────────┤\n"
                "│  1. 添加联系人                               │\n"
                "│  2. 查找联系人                               │\n"
                "│  3. 显示所有联系人                            │\n"
                "│  4. 编辑联系人                               │\n"
                "│  5. 删除联系人                               │\n"
                "│  6. 导出联系人                               │\n"
                "│  7. 导入联系人                               │\n"
                "│  8. 退出                                     │\n"
                "└──────────────────────────────────────────────┘\n";
        cout << "请输入选项: ";
        cin >> choice;
        cleanBuffer();

        switch (choice)
        {
            case 1:
            {
                string name, email, phone;
                cout << "\n请输入姓名: ";
                getline(cin, name);
                cout << "请输入邮箱: ";
                getline(cin, email);
                cout << "请输入手机号: ";
                getline(cin, phone);
                entry.add(name, email, phone);
                break;
            }
            case 2:
            {
                string keyword;
                cout << "\n请输入关键词(姓名/邮箱/手机号): ";
                getline(cin, keyword);
                auto results = entry.search(keyword);
                if (results.empty())
                {
                    cout << "未找到匹配的联系人\n";
                }
                else
                {
                    bool exactFound = false;
                    for (auto c : results)
                        if (c->name == keyword || c->email == keyword || c->phone == keyword)
                        { exactFound = true; break; }

                    if (!exactFound)
                        cout << "\n未找到目标联系人，查询到 " << results.size() << " 个可能的联系人:\n";
                    else
                        cout << "\n找到 " << results.size() << " 个匹配的联系人:\n";

                    for (size_t i = 0; i < results.size(); ++i)
                        displayContact(results[i], i + 1);
                }
                break;
            }
            case 3:
            {
                auto all = entry.getAll();
                if (all.empty())
                    cout << "\n通讯录为空\n";
                else
                {
                    cout << "\n共有 " << all.size() << " 个联系人:\n";
                    for (size_t i = 0; i < all.size(); ++i)
                        displayContact(all[i], i + 1);
                }
                break;
            }
            case 4:
            {
                string keyword;
                cout << "\n请输入要编辑的联系人的关键词: ";
                getline(cin, keyword);
                auto results = entry.search(keyword);
                if (results.empty())
                {
                    cout << "未找到匹配的联系人\n";
                    break;
                }

                cout << "\n查找到 " << results.size() << " 个联系人:\n";
                for (size_t i = 0; i < results.size(); ++i)
                    displayContact(results[i], i + 1);

                int idx;
                cout << "请输入要修改的联系人编号: ";
                cin >> idx;
                cleanBuffer();
                if (idx < 1 || idx > static_cast<int>(results.size()))
                {
                    cout << "无效的编号\n";
                    break;
                }
                COMMS::Comms* target = results[idx - 1];

                string newName, newEmail, newPhone;
                cout << "输入新的姓名 (留空不修改): ";
                getline(cin, newName);
                cout << "输入新的邮箱 (留空不修改): ";
                getline(cin, newEmail);
                cout << "输入新的手机号 (留空不修改): ";
                getline(cin, newPhone);

                if (newName.empty())  newName = target->name;
                if (newEmail.empty()) newEmail = target->email;
                if (newPhone.empty()) newPhone = target->phone;

                COMMS::Comms* validated = COMMS::build(newName, newEmail, newPhone);
                if (validated)
                {
                    target->name = validated->name;
                    target->email = validated->email;
                    target->phone = validated->phone;
                    delete validated;
                    cout << "修改成功\n";
                }
                else
                    cout << "邮箱或者手机号格式不正确\n";
                break;
            }
            case 5:
            {
                string keyword;
                cout << "\n请输入要删除的联系人的关键词: ";
                getline(cin, keyword);
                auto results = entry.search(keyword);
                if (results.empty())
                {
                    cout << "未找到匹配的联系人\n";
                    break;
                }

                cout << "\n查找到 " << results.size() << " 个联系人:\n";
                for (size_t i = 0; i < results.size(); ++i)
                    displayContact(results[i], i + 1);

                int idx;
                cout << "请输入要删除的联系人编号: ";
                cin >> idx;
                cleanBuffer();
                if (idx < 1 || idx > static_cast<int>(results.size()))
                {
                    cout << "无效的编号\n";
                    break;
                }
                entry.remove(results[idx - 1]);
                break;
            }
            case 6:
            {
                string filename;
                cout << "\n请输入导出文件名: ";
                getline(cin, filename);
                if (entry.save(filename))
                    cout << "导出成功\n";
                else
                    cout << "导出失败\n";
                break;
            }
            case 7:
            {
                string filename;
                cout << "\n请输入导入文件名: ";
                getline(cin, filename);
                if (entry.load(filename))
                    cout << "导入成功\n";
                else
                    cout << "导入失败\n";
                break;
            }
            case 8:
            {
                if (entry.save("contacts.txt"))
                    cout << "数据已保存\n";
                cout << "\n感谢使用通讯录管理系统！\n";
                break;
            }
            default:
                cout << "\n无效选项，请重新输入\n";
        }

        if (choice != 8) waitEnter();

    } while (choice != 8);

    return 0;
}
