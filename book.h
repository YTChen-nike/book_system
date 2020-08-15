#pragma once
#define NUM1 128 //图书名称和Isbn编号最大长度
#define NUM2 50  //图书价格及作者最大长度

class CBook{
	public:
		CBook(){};
		CBook(char *cName, char *cIsbn, char *cPrice, char *cAuthor);
		~CBook(){};
		char* GetName();
		void SetName(char *cName);
		char* GetIsbn();
		void SetIsbn(char *cIsbn);
		char* GetPrice();
		void SetPrice(char *cPrice);
		char* GetAuthor();
		void SetAuthor(char *cAuthor);
		void WriteData();
		void DeleteData(int iCount);
		void GetBookFromFile(int iCount);
	protected:
		char m_cName[NUM1];
		char m_cIsbn[NUM1];
		char m_cPrice[NUM2];
		char m_cAuthor[NUM2];
};
