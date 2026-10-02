#ifndef DATABASE_H 
#define DATABASE_H
#include <stdio.h>

typedef enum{

	DB_READ,
	DB_WRITE,
	DB_READ_WRITE

} DatabaseMode;

typedef struct{

	unsigned int id;
	char name[32];
	int age;
	float score;

} Record;


typedef struct{

	FILE *fp;
	unsigned int record_count;
	DatabaseMode mode;

} Database;


typedef struct {
       
	unsigned int record_count;

} DatabaseHeader;


int database_create(Database *db, char *databaseName);
int database_open(Database *db, char *databaseName);
int database_close(Database *db);
int find_record(Database *db, int id, Record *result);
int database_add(Database *db, Record *rec_w);
int update_record(Database *db, int index, Record *new_rec);
int read_record(Database *db, Record *rec_r, int index);
int list_records(Database *db);
int delete_record(Database *db, int index);



#endif
