#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>


using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <string>
using namespace std;

#define TRACE(msg)            wcout << msg

void display_json(
    json::value const& jvalue,
    utility::string_t const& prefix)
{
    wcout << prefix << jvalue.serialize() << endl;
}

struct Employee
{
    string mname, mmonth, mcategory, mtask;
    int meffort;

    Employee() = default;
    Employee(string name, string month, string category, string task, int effort) :mname(name), mmonth(month), mcategory(category),
        mtask(task), meffort(effort)
    {

    }

};

class MysqlDB
{
private:
    sql::Driver* mDriver = nullptr;
    sql::Connection* mConnection = nullptr;
    static MysqlDB* mDBinstance;
public:
    MysqlDB()
    {
        mDriver = get_driver_instance();
        mConnection = mDriver->connect("tcp://127.0.0.1:3306", "root", "12345678");
        mConnection->setSchema("employeeDb");
    }

    static MysqlDB* getInstance()
    {
        if (mDBinstance == nullptr)
            mDBinstance = new MysqlDB();
        return mDBinstance;
    }

    sql::Connection* getConnection()
    {
        return mConnection;
    }
};


MysqlDB* MysqlDB::mDBinstance=nullptr;

void insertIntoDB(Employee& emp)
{
    sql::PreparedStatement* prep_stmt;
    //get DB connection
    sql::Connection* con = MysqlDB::getInstance()->getConnection();

    prep_stmt=con->prepareStatement("INSERT INTO employee(name,month,category,task, efforts) VALUES(?,?,?,?,?)");
    prep_stmt->setString(1, emp.mname.c_str());
    prep_stmt->setString(2, emp.mmonth.c_str());
    prep_stmt->setString(3, emp.mcategory.c_str());
    prep_stmt->setString(4, emp.mtask.c_str());
    prep_stmt->setInt(5, emp.meffort);

    prep_stmt->execute();
}

void handle_get(http_request request)
{
    TRACE(L"\nhandle GET\n");
    request
        .extract_json()
        .then([request](pplx::task<json::value> task) {
        try
        {
            //parsing data from json Post request
            auto const jvalue = task.get();
            display_json(jvalue, L"R: ");

            sql::Statement* stmt;
            sql::ResultSet* res;

            //get DB connection
            sql::Connection* con = MysqlDB::getInstance()->getConnection();
            sql::PreparedStatement* prep_stmt;

            auto tableName = jvalue.at(U("tableName")).as_string();
            auto array = jvalue.at(U("tableRecords")).as_array();
            auto month = array[0].at(U("month")).as_string();
            auto name = array[0].at(U("name")).as_string();

            prep_stmt = con->prepareStatement("SELECT Name, Month, Category, Task, Efforts  from employee where name =? and month=?");
            
            string myname = utility::conversions::to_utf8string(name);
            string mymonth = utility::conversions::to_utf8string(month);
            cout << myname << mymonth << endl;
            prep_stmt->setString(1, myname.c_str());
            prep_stmt->setString(2, mymonth.c_str());
            res = prep_stmt->executeQuery();

            json::value jsonResponseFinal;
            std::vector<json::value> arrayResponse;
            while (res->next()) 
            {
                json::value jsonResponse;
                cout << " Name = " << res->getString("Name").c_str() << endl;
                cout << ", Month = '" << res->getString("Month").c_str() << "'" << endl;
                cout << ", Category = '" << res->getString("Category").c_str() << "'" << endl;
                cout << ", Task = '" << res->getString("Task").c_str() << "'" << endl;
                cout << ", Efforts = '" << res->getInt("Efforts") << "'" << endl;
                string name=res->getString("Name").c_str();
                string month=res->getString("Month").c_str();
                string category=res->getString("Category").c_str();
                string task=res->getString("Task").c_str();
                int effort=res->getInt("Efforts");
                jsonResponse[U("name")] = json::value::string(utility::conversions::to_string_t(name));
                jsonResponse[U("month")] = json::value::string(utility::conversions::to_string_t(month));
                jsonResponse[U("category")] = json::value::string(utility::conversions::to_string_t(category));
                jsonResponse[U("task")] = json::value::string(utility::conversions::to_string_t(task));
                jsonResponse[U("efforts")] = json::value::number(effort);
                arrayResponse.push_back(jsonResponse);
            }

            jsonResponseFinal[U("employee")] = json::value::array(arrayResponse);
            display_json(jsonResponseFinal, L"R");
            request.reply(status_codes::OK, jsonResponseFinal);
            return;
        }
        catch (http_exception const& e)
        {
            cout << e.what() << endl;
            json::value jsonResponse;
            jsonResponse[U("error")] = json::value::string(U("Got some error"));
            request.reply(status_codes::OK, jsonResponse);
        }
        }).wait();

}

void handle_post(http_request request)
{
    TRACE("\nhandle POST\n");
    wcout << endl;

    request
        .extract_json()
        .then([request](pplx::task<json::value> task) {
        try
        {
            //parsing data from json Post request
            auto const jvalue = task.get();
            display_json(jvalue, L"R: ");

            auto tableName = jvalue.at(U("tableName")).as_string();
            auto array = jvalue.at(U("tableRecords")).as_array();
            auto name = array[0].at(U("name")).as_string();
            auto month = array[0].at(U("month")).as_string();
            auto category = array[0].at(U("category")).as_string();
            auto taskName = array[0].at(U("taskName")).as_string(); 
            auto efforts = array[0].at(U("efforts")).as_string();
            auto effort = stoi(efforts);
            wcout << "Following is the parsed detail of POST request from client" << endl;
            wcout << "tableName " << tableName<<endl;
            wcout << "Name " << name << endl;
            wcout << "month " << month << endl;
            wcout << "Category " << category << endl;
            wcout << "tableName " << taskName << endl;
            wcout << "effort " << effort << endl;

            //Intialize it in Employee structure
            Employee emp(utility::conversions::to_utf8string(name), utility::conversions::to_utf8string(month),
                utility::conversions::to_utf8string(category), utility::conversions::to_utf8string(taskName), effort);

            insertIntoDB(emp);

            json::value jsonResponse;

            jsonResponse[U("name")] = json::value::string(name);
            request.reply(status_codes::OK, jsonResponse);

            display_json(jsonResponse, L"R");
            return;
        }
        catch (http_exception const& e)
        {
            cout << e.what() << endl;
            json::value jsonResponse;
            jsonResponse[U("error")] = json::value::string(U("Got some error"));
            request.reply(status_codes::OK, jsonResponse);
        }
        }).wait();
}

void handle_put(http_request request)
{
    TRACE("\nhandle PUT\n");
}

void handle_del(http_request request)
{
    TRACE("\nhandle DEL\n");

}

int main()
{
    http_listener listener(L"http://127.0.0.1:39249");

    listener.support(methods::GET, handle_get);
    listener.support(methods::POST, handle_post);
    listener.support(methods::PUT, handle_put);
    listener.support(methods::DEL, handle_del);

    try
    {
        listener
            .open()
            .then([&listener]() {TRACE(L"\nstarting to listen\n"); })
            .wait();

        while (true);
    }
    catch (exception const& e)
    {
        wcout << e.what() << endl;
    }

    return 0;
}