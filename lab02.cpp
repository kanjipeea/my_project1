#include "lab02.h"
//Time
Time::Time():seconds(0){}
Time::Time(int s) : seconds(s) {}
Time::Time(int h, int m, int s) {
    seconds = h * 3600 + m * 60 + s;
}
Time Time::operator+(const Time& other) const {
    return Time(seconds + other.seconds);
}
Time Time::operator-(const Time& other) const {
    return Time(seconds - other.seconds);
}
Time Time::operator*(int scalar) const {
    return Time(seconds * scalar);
}
Time::operator int() const {
    return seconds;
}
std::ostream &operator<<(std::ostream &str, const Time &rhs){
    int h = rhs.seconds / 3600;
    int m = (rhs.seconds % 3600) / 60;
    int s = rhs.seconds % 60;
    str << (h < 10 ? "0" : "") << h << ":"
        << (m < 10 ? "0" : "") << m << ":"
        << (s < 10 ? "0" : "") << s;
    return str;
}
std::istream &operator>>(std::istream &str, Time &rhs){
    int h, m, s;
    char ch;
    str >> h >> ch >> m >> ch >> s;
    rhs = Time(h, m, s);
    return str;}

// Invoice
Invoice::Invoice(long long seller_nip, long long buyer_nip): seller_nip(seller_nip), buyer_nip(buyer_nip) {}
void Invoice::add_item(const Item& item) {
    items.push_back(item);
}
double Invoice::get_net_price()const{
    double total = 0;
    for (auto& item : items) {
        total += item.get_net_price();
    }
    return total;
}
double Invoice::get_total_price()const{
    double total = 0;
    for (auto& item : items) {
        total += item.get_total_price();
    }
    return total;
}
std::ostream &operator<<(std::ostream &str, const Invoice &rhs){
    str<<"------------------VAT invoice------------------\n";
    str<<"===============================================\n";
    str<<"Seller:"<< rhs.seller_nip<<"\tBuyer:"<<rhs.buyer_nip<<std::endl;
    str<<"\t U.P  VAT  am.  net  total\n";
    int index = 1;
    for (auto& item : rhs.items) {
        str << index++ << ". " << item << "\n";
    }
    str << "------------------------------------ TOTAL ----\n";
    str << "Net Price: " << rhs.get_net_price()
    << " | Total Price: " << rhs.get_total_price() << "\n";
    return str;
};

//Item
Item::Item(const std::string& name, double unit_price, char vat, int amount)
        : name(name), unit_price(unit_price), vat(vat), amount(amount) {}

std::string Item::get_name()const  { return name; }
double Item::get_unit_price() const { return unit_price; }
char Item::get_vat() const { return vat; }
int Item::get_amount() const{ return amount; }
double Item::get_net_price()const{
        return unit_price*amount;
}
double Item::get_total_price()const{
        double i=0;
        if(vat=='A'){i=0.23;}
        else if(vat=='B'){i=0.08;}
        else if(vat=='C'){i=0;}
        return get_net_price()*(1+i);
}
std::ostream &operator<<(std::ostream &str, const Item &rhs){
    str<<rhs.get_name()<< " | " << rhs.get_unit_price()<< "  " << rhs.get_vat()
    << " | " << rhs.get_amount()<< " | " << rhs.get_net_price() << " | " << rhs.get_total_price();
    return str;
}
