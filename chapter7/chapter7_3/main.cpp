#include <iostream>
#include <vector>

using namespace std;

class X;
class Y
{
	X *Xptr;
};

class X
{
	Y *Yptr;
};

class Screen;

//Screen::Screen(pos ht, pos wd, char c);

class Window_mgr
{
	public:
		using ScreenIndex = std::vector<Screen>::size_type;

		void clear(ScreenIndex);
	private:
		std::vector<Screen> screens;
		//std::vector<Screen> screens{Screen(23, 80, ' ')};
};

class Screen
{
	//friend class Window_mgr;
	friend void Window_mgr::clear(ScreenIndex);
	public:
		using pos = std::string::size_type;
		Screen() = default;
		Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht * wd, c){};
		char get() const
		{
			return contents[cursor];
		}
		inline char get(pos ht, pos wd)const;
		Screen &move(pos r, pos c);
		void some_member() const;
		size_t getmutable();
		Screen &set(char c);
		// add display function
		Screen &display(std::ostream &os){do_display(os); return *this;}
		const Screen &display(std::ostream &os) const {do_display(os); return *this;}
		pos size() const ;
	private:
		void do_display(std::ostream &os) const {os << contents;}
		mutable size_t access_ctr = 0;
		pos cursor =0;
		pos height = 0, width = 0;
		std::string contents;
};

Screen::pos Screen::size() const
{
	return height * width;
}

inline
Screen &Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

inline 
Screen &Screen::move(pos r, pos c)
{
	pos row = r*width;
	cursor = row + c;
	return *this;
}

void Screen::some_member() const
{
	access_ctr++;
}

inline size_t Screen::getmutable()
{
	return access_ctr;
}


void Window_mgr::clear(ScreenIndex i)
{
	Screen &s = screens[i];
	s.contents = string(s.height * s.width, ' ');
}

int main(void)
{
	Screen test;

	cout << "before fixed ..." << endl;
	cout << test.getmutable() << endl;
	test.some_member();
	cout << "after fixed ..." << endl;
	cout << test.getmutable() << endl;

	Screen myScreen(5, 5, 'X');
	myScreen.move(4, 0).set('#').display(cout);
	cout << endl;
	myScreen.display(cout);
	cout << endl;

	return 0;
}
