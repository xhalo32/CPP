#include <iostream>
#include <string>
using namespace std;


class Foo
{
	public:

		void Bar()
		{
			cout << "Cow" << endl;
			PrivBar();
		}

		void SetSentence(string s)
		{
			sentence = s;
		}

	private:

		string sentence = "Cats";

		void PrivBar()
		{
			cout << sentence << endl;
		}


};


int main()
{
	Foo FooObject;

	FooObject.Bar();

	FooObject.SetSentence("Dogs");
	
	FooObject.Bar();

	return 1;
}