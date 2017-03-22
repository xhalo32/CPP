// you don't need to import stuff again


class Foo
{
	public:
		Foo(string s)
		{
			cout << sentence << endl;
			sentence = s;
		}

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
