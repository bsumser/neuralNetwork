#include <iostream> 
#include <sqlite3.h>

static int callback(void* data, int argc, char** argv, char** azColName) {
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for(i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

void returnWhites(sqlite3* DB)
{
	std::string data("CALLBACK FUNCTION"); 
	std::string sql("SELECT * FROM WINE WHERE Varietal = 'Pinot Grigio'");	
	
	int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);

	if(rc != SQLITE_OK)
			std::cerr << "error SELECT" << std::endl;
	else
			std::cout << "Operation OK!" << std::endl;
}

void returnPrice(sqlite3* DB)
{
	std::string data("CALLBACK FUNCTION"); 
	std::string sql("SELECT * FROM WINE WHERE Varietal = 'Pinot Grigio'");	
	
	int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);

	if(rc != SQLITE_OK)
			std::cerr << "error SELECT" << std::endl;
	else
			std::cout << "Operation OK!" << std::endl;
}

void returnReds(sqlite3* DB)
{
	std::string data("CALLBACK FUNCTION"); 
	std::string sql("SELECT * FROM WINE WHERE Varietal = 'Pinot Noir'");	
	
	int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);

	if(rc != SQLITE_OK)
			std::cerr << "error SELECT" << std::endl;
	else
			std::cout << "Operation OK!" << std::endl;
}

static int redCallBack(void* data, int argc, char** argv, char** azColName) {
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for(i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

int main(int argc, char **argv)
{
	sqlite3* DB;
	int exit = 0;
	exit = sqlite3_open("wine.db::memory:", &DB);
   	
	returnWhites(DB);
	returnReds(DB);
	if (exit) {
			std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
			return (-1);
	}

	else 
			std::cout << "opened database successfully" << std::endl;
	sqlite3_close(DB);
	return(0);
}


/*--------------------Citation for Data used--------------------------------
P. Cortez, A. Cerdeira, F. Almeida, T. Matos and J. Reis. 
  Modeling wine preferences by data mining from physicochemical properties.
  In Decision Support Systems, Elsevier, 47(4):547-553. ISSN: 0167-9236.

  Available at: [@Elsevier] http://dx.doi.org/10.1016/j.dss.2009.05.016
                [Pre-press (pdf)] http://www3.dsi.uminho.pt/pcortez/winequality09.pdf
                [bib] http://www3.dsi.uminho.pt/pcortez/dss09.bib
--------------------Citation for Data used--------------------------------*/


/*--------------------Citation for Data used--------------------------------*/
