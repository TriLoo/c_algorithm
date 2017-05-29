#include <iostream>

class Quote
{
	public:
		Quote() = default;
		Quote(const std::string &book, double sales_price):bookNo(book), price(sales_price){}
		std::string isbn(){return bookNo;}
		virtual double net_price(std::size_t n) const{std::cout << "in basic" << std::endl;return n * price;}
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
		Disc_quote(const std::string &book, double price, std::size_t qty, double disc):Quote(book, price), quantity(qty), discount(disc){}
		double net_price(std::size_t) const = 0;
	private:
		std::size_t quantity = 0;
		double discount = 0;
};

/*
class BulkQuote:public Quote    // must be public, otherwise, the bulkquote cannot bind to the quote's reference or pointer
{
	public:
		BulkQuote() = default;
		BulkQuote(const std::string& book, double q, std::size_t qty, double disc):Quote(book, q), min_qty(qty), discount(disc){} 
		double net_price(std::size_t n);
	private:
		std::size_t min_qty = 0;
		double discount = 0.0;
};
*/
class BulkQuote:public Disc_quote
{
	public:
		using Disc_quote::Disc_quote;
		BulkQuote() = default;
		BulkQuote(std::string &book, double price, std::size_t qty, double disc):Disc_quote(book, price, qty, disc){}
		double net_price(std::size_t) const override;
};

double BulkQuote::net_price(std::size_t n) const
{
	std::cout << "in new" << std::endl;
	/*
	if(n > 10)
		return n * discount * price;
	else
		return n * price;
		*/
}

