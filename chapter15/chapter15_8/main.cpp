#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Quote
{
	public:
		Quote() = default;
		Quote(const std::string &book, double sales_price):bookNo(book), price(sales_price){}
		string isbn(){return bookNo;}
		virtual double net_price(size_t n) const {cout << "in basic ..." << endl; return n * price;}
		virtual ~Quote() = default;
	private:
		std::string bookNo;
	protected:
		double price = 0.0;
};

class Disc_quote:public Quote
{
	public:
		Disc_quote() = default;
		Disc_quote(const string book, double price, size_t qty, double disc):Quote(book, price),quantity(qty), discount(disc){}
		double net_price(size_t n) const override = 0;
	protected:
		size_t quantity = 0;
		double discount = 0.0;
};

class Bulk_quote:public Disc_quote
{
	public:
		Bulk_quote() = default;
		Bulk_quote(const string book, double price, size_t qty, double disc):Disc_quote(book, price, qty, disc){}
		double net_price(size_t n) const override;
};

double Bulk_quote::net_price(size_t n) const    	// the const must be attached, or wrong!
{
	cout << "in Bulk Quote..." << endl;
	if(n > quantity)
		return n * (1 - discount) * price;
	else
		return n * price;
}

int main(void)
{
	Bulk_quote bulk("hello", 10, 10, 0.25);
	//bulk.quantity = 0;
	//vector<Quote> basket;
	vector<shared_ptr<Quote>> basket;
	basket.push_back(make_shared<Quote>("0-20", 50));
	basket.push_back(make_shared<Bulk_quote>("Hello", 50, 10, 0.25));

	cout << basket.back()->net_price(15) << endl;

	// test dynamic bind   WORK
	Quote *p = &bulk;
	cout << p->net_price(15) << endl;   // Output "in Bulk Quote..."
	Quote &ref = bulk;
	cout << ref.net_price(15) << endl;   // Output "in Bulk Quote..."

	return 0;
}

