#include <iostream>
#include <sstream>
#include <stdexcept>
#include <assert.h>

using namespace std;

class Phone
{
    public:
        string model;
        string brand;
        int y;
        double price;

        static int counter;
        int id;

    public:
        //constructors
        Phone(string model, string brand, int y, double price)
        {
            createPhone(model, brand, y, price);
        }

        Phone (string model, string brand)
        {
            createPhone(model, brand, 0, 0);
        }
        //destructor
        ~Phone()
        {
            --counter;
        }

    private:
        void createPhone(string model, string brand, int y, double price)
        {
            setModel(model);
            setBrand(brand);
            setYear(y);
            setPrice(price);

            id = ++counter;
        }

    public:
        //setters
        void setModel (string model)
        {
            this->model = model;
        }

        void setBrand (string brand)
        {
            this->brand = brand;
        }

        void setYear(int y)
        {
            if (y < 0)
            throw invalid_argument("The year cannot be negative.");

            this->y = y;
        }

        void setPrice(double price)
        {
            if (price < 0)
            throw invalid_argument("The price cannot be negative.");

            this->price = price;
        }

        //getters
        string getModel()
        {
            return model;
        }

        string getBrand()
        {
            return brand;
        }

        int getYear()
        {
            return y;
        }

        double getPrice()
        {
            return price;
        }

        int getId()
        {
            return id;
        }

        static int getCounter()
        {
            return counter;
        }


        string toString()
        {
            return model + " " + brand + " " + to_string(y) + " " + to_string(price);
        }
};
int Phone::counter = 0;

int main()
{
    assert (Phone::getCounter() == 0);
    {
        //1st test
        Phone p1("iPhone 17", "Apple", 2025, 799.99);
        assert(p1.getModel() == "iPhone 17");
        assert(p1.getBrand() == "Apple");
        assert(p1.getYear() == 2025);
        assert(p1.getPrice() == 799.99);

        string phone1 = p1.toString();
        assert(!phone1.empty());

        //2nd test
        p1.setModel("Samsung Galaxy Z Fold 6");
        p1.setBrand("Samsung");
        p1.setYear(2024);
        p1.setPrice(1899.99);

        assert(p1.getModel() == "Samsung Galaxy Z Fold 6");
        assert(p1.getBrand() == "Samsung");
        assert(p1.getYear() == 2024);
        assert(p1.getPrice() == 1899.99);

        //3rd test
        int exception = 0;
        try
        {
            p1.setPrice(-248);
        }
        catch (const invalid_argument&)
        {
            exception = 1;
        }
        assert(exception);

        //4th test
        Phone p2("HUAWEI Mate 50 Pro", "HUAWEI", 2022, 895.48);
        assert(p2.getId() > p1.getId());


        //5th test
        Phone* p = new Phone[2]
        {
            Phone("Nokia C110", "Nokia", 2023, 99.99),
            Phone("Amazon Fire HD 10", "Amazon", 2017, 169.99)
        };

        assert(Phone::getCounter() == 4);
        delete[] p;
        assert(Phone::getCounter() == 2);
    }

    assert(Phone::getCounter() == 0);

    cout << "All tests have been successful";
}
