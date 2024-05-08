#include "Pch.h"
#define FILE "data.txt"

struct LoginUser
{
	std::string _username;
	std::string _password;
};
class LoginSystem
{
public:
	
	LoginSystem()
	{
		users.emplace_back("user01", "12345");
		users.emplace_back("user02", "00000");
	}
	~LoginSystem() {}
	
	bool LoginSys(const std::string_view username, const std::string_view password)
	{
		for (const auto& user : users)
		{
			if (user._username == username and user._password == password)
			{
				return true;
			}
		}
		return false;
	}
private:
	std::vector<LoginUser> users;
};

class Manger
{
public:
	Manger() {}
	~Manger() {}

	void ExitSystem()
	{
		std::cin.get();
		std::cout << "退出系統\n";
		std::cin.get();
		system("cls");
		exit(0);
	}
};

class Worker
{
public:
	int WorkerID;
	int WorkerNum;
	std::string WorkerName;

	Worker(int ID, std::string Name, int Num) {}

	Worker() = default;

	virtual void ShowInfo() = 0;

	virtual std::string JobTitle() = 0;
};

class Employee : public Worker
{
public:

	Employee(int ID, std::string Name, int Num)
		:Worker(ID, Name, Num) {}

	virtual void ShowInfo()
	{
		std::cout << "員工編號: " << this->WorkerID << "\t";
		std::cout << "員工姓名: " << this->WorkerName << "\t";
		std::cout << "員工職位: " << this->JobTitle() << "\t";
	}
	virtual std::string JobTitle()
	{
		return std::string("員工");
	}
};

class Manager : public Worker
{
public:
	Manager(int ID, std::string Name, int Num)
		:Worker(ID, Name, Num) {}

	virtual void ShowInfo()
	{
		std::cout << "員工編號: " << this->WorkerID << "\t";
		std::cout << "員工姓名: " << this->WorkerName << "\t";
		std::cout << "員工職位: " << this->JobTitle() << "\t";
	}

	virtual std::string JobTitle()
	{
		return std::string("經理");
	}
};

class Boss : public Worker
{
public:
	Boss(int ID, std::string Name, int Num)
		:Worker(ID, Name, Num) {}

	virtual void ShowInfo()
	{
		std::cout << "員工編號: " << this->WorkerID << "\t";
		std::cout << "員工姓名: " << this->WorkerName << "\t";
		std::cout << "員工職位: " << this->JobTitle() << "\t";
	}

	virtual std::string JobTitle()
	{
		return std::string("老闆");
	}
};

class DataManagement
{
public:
	int id;
	std::string name;
	int Did;

	std::vector<DataManagement> WorkerVector;

	int TargetId;

	bool IsEmployeeIdDuplicate(const std::vector<DataManagement>& workers, int id)
	{
		for (const DataManagement& worker : workers)
		{
			if (worker.id == id)
			{
				return true;
			}
		}
		return false;
	}

	void AddEmployeeData(std::vector<DataManagement>& workers)
	{
		DataManagement worker(id, name, Did);
		workers.emplace_back(worker);
	}

	void AddEmployee()
	{
		std::cout << "新增員工數量: " << std::endl;
		int AddNum = 0;

		std::cin >> AddNum;

		if (AddNum > 0)
		{
			for (int i = 0; i < AddNum; i++)
			{
				std::cout << "員工編號: " << std::endl;
				std::cin >> id;

				if (IsEmployeeIdDuplicate(WorkerVector, id))
				{
					std::cout << "員工編號重複\n";
					std::cin.get();
					continue;
				}
				std::cout << "員工姓名: " << std::endl;
				std::cin >> name;

				std::cout << "員工職位 (1: Employee, 2: Manager, 3: Boss): " << std::endl;
				std::cin >> Did;
				if (Did != 1 && Did != 2 && Did != 3)
				{
					std::cout << "輸入錯誤\n";
					std::cin.get();
					continue;
				}

				AddEmployeeData(WorkerVector);
				std::cout << "成功添加一位員工。" << std::endl;
				std::cin.get();

				SaveData();
			}
		}
		else
		{
			std::cout << "輸入錯誤" << std::endl;
			std::cin.get();
		}
	}

	void SaveData()
	{
		DataManagement DM;

		std::ofstream ofs;
		ofs.open(FILE, std::ios::out);

		for (const DataManagement& worker : WorkerVector)
		{
			ofs << "員工編號: " << worker.id << std::endl;
			ofs << "員工姓名: " << worker.name << std::endl;
			ofs << "員工職位: " << worker.Did << std::endl;
			ofs << std::endl;
		}
		ofs.close();
	}

	void ShowEmployee()
	{
		if (WorkerVector.empty())
		{
			std::cout << "查無資料\n";
			std::cin.get();
		}
		else
		{
			for (const DataManagement& worker : WorkerVector)
			{
				std::cout << "員工編號: " << worker.id << std::endl;
				std::cout << "員工姓名: " << worker.name << std::endl;
				std::cout << "員工職位: " << worker.Did << std::endl;
				std::cin.get();
			}
		}
	}

	bool B_FindData(const DataManagement& worker, int TargetId)
	{
		return worker.id == TargetId;
	}

	void FindEmployeeNum()
	{
		std::cout << "輸入員工編號: \n";
		std::cin >> TargetId;
		std::vector<DataManagement>::iterator it = std::find_if(WorkerVector.begin(), WorkerVector.end(), [&](const DataManagement& worker) {return worker.id == TargetId; });

		if (it != WorkerVector.end())
		{
			std::cout << "找到了員工編號為 " << TargetId << " 的資料。" << std::endl;
			std::cout << "員工姓名: " << it->name << std::endl;
			std::cout << "員工職位: " << it->Did << std::endl;
			std::cin.get();
		}
		else
		{
			std::cout << "未找到員工編號為 " << TargetId << " 的資料。" << std::endl;
			std::cin.get();
		}
	}

	void FindEmployeeName()
	{
		std::string FindName;

		std::cout << "輸入員工姓名: \n";
		std::cin >> FindName;
		std::vector<DataManagement>::iterator it = std::find_if(WorkerVector.begin(), WorkerVector.end(), [&](const DataManagement& worker) {return worker.name == FindName; });

		if (it != WorkerVector.end())
		{
			std::cout << "找到了姓名為 " << FindName << " 的員工。" << std::endl;
			std::cout << "員工編號: " << it->id << std::endl;
			std::cout << "員工職位: " << it->Did << std::endl;
			std::cin.get();
		}
		else
		{
			std::cout << "未找到姓名為 " << FindName << " 的員工。" << std::endl;
			std::cin.get();
		}
	}

	void FindEmployeeData()
	{
		int InputSelect;
		std::string FindName;

		std::cout << "請選擇以員工編號或姓名的方式查詢(0: 員工編號 1: 姓名)\n";
		std::cin >> InputSelect;
		if (InputSelect == 0)
		{
			FindEmployeeNum();
		}
		else if (InputSelect == 1)
		{
			FindEmployeeName();
		}
	}

	void DeleteEmployee()
	{
		std::cout << "輸入要刪除員工編號: " << std::endl;
		std::cin >> TargetId;
		bool found = false;

		for (auto it = WorkerVector.begin(); it != WorkerVector.end();)
		{
			if (it->id == TargetId)
			{
				std::cout << "找到了員工編號為 " << TargetId << " 的資料。" << std::endl;
				std::cout << "員工姓名: " << it->name << std::endl;
				std::cout << "員工職位: " << it->Did << std::endl;

				it = WorkerVector.erase(it);
				std::cout << "已刪除員工編號為 " << TargetId << " 的資料。" << std::endl;
				std::cin.get();

				found = true;
			}
			else
			{
				++it;
			}
		}

		if (!found)
		{
			std::cout << "未找到員工編號為 " << TargetId << " 的資料。" << std::endl;
			std::cin.get();
		}
	}

	void ChangeWorker()
	{
		int InputSelect;
		std::string NewName;
		int NewDid;

		std::cout << "輸入要修改的員工編號: \n";
		std::cin >> TargetId;
		std::vector<DataManagement>::iterator it = std::find_if(WorkerVector.begin(), WorkerVector.end(), [&](const DataManagement& worker) {return worker.id == TargetId; });

		if (it != WorkerVector.end())
		{
			std::cout << "找到了員工編號為 " << TargetId << " 的資料。" << std::endl;
			std::cout << "員工姓名: " << it->name << std::endl;
			std::cout << "員工職位: " << it->Did << std::endl;
			std::cin.get();

			std::cout << "是否要修改員工姓?(0:不修改 1:修改)\n";
			std::cin >> InputSelect;
			if (InputSelect == 1)
			{
				std::cout << "請輸入新的員工姓名: \n";
				std::cin >> NewName;

				it->name = NewName;

				std::cout << "是否要修改員工職位?((0:不修改 1:修改)" << std::endl;
				std::cin >> InputSelect;
				if (InputSelect == 1)
				{
					std::cout << "請輸入新的員工職位: \n";
					std::cin >> NewDid;

					it->Did = NewDid;
				}

				std::cout << "已修改員工編號為 " << TargetId << " 的資料。" << std::endl;
				std::cin.get();
			}
			else
			{
				std::cout << "輸入錯誤，請重新輸入 \n";
			}
		}
		else
		{
			std::cout << "未找到員工編號為 " << TargetId << " 的資料。" << std::endl;
			std::cin.get();
		}
	}
};

class File
{
public:
	void FileFind()
	{
		std::ifstream ifs;
		ifs.open(FILE, std::ios::in);

		bool FileIsEmpty;

		if (!ifs.is_open())
		{
			std::cout << "文件不存在\n";

			FileIsEmpty = true;

			ifs.close();
			return;
		}
		else
		{
			std::cout << "文件儲存成功\n";
		}
	}
	void FileFind1()
	{
		std::ifstream ifs;
		ifs.open(FILE, std::ios::in);

		bool FileIsEmpty;

		char Ch;
		ifs >> Ch;
		if (ifs.eof())
		{
			std::cout << "文件為空\n";

			FileIsEmpty = true;

			ifs.close();
			return;
		}
		else
		{
			FileIsEmpty = false;
		}
	}
};

void DeleteDataFile(std::vector<DataManagement>& workers)
{
	std::cout << "是否刪除文件?(0:刪除 1:返回)\n";
	int Input;
	std::cin >> Input;

	DataManagement DM;

	if (Input == 0)
	{
		std::ofstream ofs(FILE, std::ios::trunc);
		ofs.close();
		DM.WorkerVector.clear();
		DM.WorkerVector.swap(workers);
		std::cout << "刪除完成\n";
		std::cin.get();
	}
	//std::cin.get();
	//system("cls");
}

int GetNum()
{
	std::ifstream ifs;
	ifs.open(FILE, std::ios::in);

	int id;
	std::string name;
	int Did;

	int Num = 0;

	while (ifs >> id && ifs >> name && ifs >> Did)
	{
		Num++;
	}
	return Num;

	std::cout << "員工人數: " << Num << std::endl;
}

void ShowMenu()
{
	std::cout << "目錄" << std::endl;
	std::cout << "0. 退出系統" << std::endl;
	std::cout << "1. 增加成員" << std::endl;
	std::cout << "2. 顯示所有成員" << std::endl;
	std::cout << "3. 刪除成員" << std::endl;
	std::cout << "4. 修改成員" << std::endl;
	std::cout << "5. 搜尋成員" << std::endl;
	std::cout << "6. 清空所有資料" << std::endl;
}

void Fun_Final()
{
	std::cin.get();
	system("cls");
}

int main()
{
	Manger M1;

	DataManagement DM;

	LoginSystem login;

	std::string username, password;
	bool success = false;
	while (!success) 
	{
		std::cout << "請輸入帳號: ";
		std::cin >> username;

		std::cout << "請輸入密碼: ";
		std::cin >> password;
		if (login.LoginSys(username, password))
		{
			std::cin.get();
			std::cout << "登入成功" << std::endl;
			std::cin.get();
			success = true;
		}
		else 
		{
			std::cin.get();
			std::cout << "登入失敗" << std::endl;
			std::cin.get();
			system("cls");
		}
	}

	//File 

	DM.WorkerVector.emplace_back(DataManagement(1, "olivia", 3));

	int InputChoice = 0;

	while (true)
	{
		ShowMenu();
		std::cout << "Choice Number For Function\n";
		std::cin >> InputChoice;

		switch (InputChoice)
		{
		case 0:  //退出
			M1.ExitSystem();
			break;
		case 1:
			DM.AddEmployee();
			Fun_Final();
			break;
		case 2:
			DM.ShowEmployee();
			Fun_Final();
			break;
		case 3:
			DM.DeleteEmployee();
			Fun_Final();
			break;
		case 4:
			DM.ChangeWorker();
			Fun_Final();
			break;
		case 5:
			DM.FindEmployeeData();
			Fun_Final();
			break;
		case 6:
			DeleteDataFile(DM.WorkerVector);
			Fun_Final();
			break;
		default:
			system("cls");
			break;
		}
	}

	DM.WorkerVector.clear();

	std::cin.get();
};
