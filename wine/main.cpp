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
	std::string sql("SELECT * FROM WINE Varietal = 'Pinot Noir'");	
	
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
	exit = sqlite3_open("wine.db", &DB);
	std::string data("CALLBACK FUNCTION");
   	
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
