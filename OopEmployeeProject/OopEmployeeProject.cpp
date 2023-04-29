#include <iostream>
#include <string>

using namespace std;

class Matrix
{
    int rows;
    int cols;
    int** items;
public:
    Matrix(int rows, int cols)
        : rows{ rows }, cols{ cols } 
    {
        items = new int* [rows];
        for (int i = 0; i < rows; i++)
            items[i] = new int[cols];
    }

    int& operator()(int row, int col)
    {
        return items[row][col];
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; i++)
            delete[] items[i];
        delete[] items;
    }
};

class Employee
{
    string name;
    string phone;
    string email;
    int age;
public:
    // string& Name() { return name; }
    string& operator[](string key)
    {
        if (key == "name")
            return name;
        if (key == "phone")
            return phone;
        if (key == "email")
            return email;
    }

    int& Age() { return age; }

    string ToString()
    {
        return name + " " + phone + " " + email + to_string(age);
    }
};

class ComparerEmployee
{
public:
    bool operator()(Employee left, Employee right)
    {
        return left.Age() < right.Age();
    }
};



template <typename T>
void Sort(T* array, int size)
{
    for (int i = 0; i < size; i++)
    {
        for(int j = size - 1; j > i; j--)
            if (array[j] < array[j - 1])
            {
                T temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
    }
}

template <typename T>
void Sort(T* array, int size, ComparerEmployee comparer)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j > i; j--)
            if (comparer(array[j], array[j - 1]))
            {
                T temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
    }
}


int main()
{
    Employee employee;
    employee["name"] = "Bob";
    employee["phone"] = "+7 999 123-45-67";
    employee["email"] = "bob@gmail.com";
    employee.Age() = 34;

    int* arrayInt = new int[5] { 7, 2, 9, 3, 6 };
    Sort(arrayInt, 5);
    for (int i = 0; i < 5; i++)
        cout << arrayInt[i] << " ";
    cout << "\n";

    Employee* employees = new Employee[3];
    employees[0]["name"] = "Sam";
    employees[0].Age() = 35;
    employees[1]["name"] = "Joe";
    employees[1].Age() = 22;
    employees[2]["name"] = "Leo";
    employees[2].Age() = 41;

    Sort(employees, 3, ComparerEmployee());

    for (int i = 0; i < 3; i++)
        cout << employees[i]["name"] << " " << employees[i].Age() << "\n";
}
