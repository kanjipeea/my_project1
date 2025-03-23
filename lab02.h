#ifndef LAB02_H
#define LAB02_H
#include<iostream>
#include<vector>
class Time{
private:
    int seconds;
public:
    Time();
    Time(int s);
    Time(int h, int m, int s);
    Time operator+(const Time& other) const;
    Time operator-(const Time& other) const;
    Time operator*(int scalar) const;
    operator int() const;
    friend std::ostream &operator<<(std::ostream &str, const Time &rhs);
    friend std::istream &operator>>(std::istream &str, Time &rhs);
};

class Item{
private:
    std::string name;
    double unit_price;
    char vat;
    int amount;
public:
    Item(const std::string& name, double unit_price, char vat, int amount);
    std::string get_name() const;
    double get_unit_price() const;
    char get_vat()const;
    int get_amount()const;
    double get_net_price()const;
    double get_total_price()const;
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
};

class Invoice{
private:
    long long seller_nip;
    long long buyer_nip;
    std::vector<Item> items;
public:
    Invoice(long long seller_nip, long long buyer_nip);
    void add_item(const Item& item);
    double get_net_price()const;
    double get_total_price()const;
    friend std::ostream &operator<<(std::ostream &str, const Invoice &rhs);
};

#endif // LAB02_H
