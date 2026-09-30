#include <complex.h>
#include <stdio.h>
#include <string.h>

/* 	add
	get
	update
	delete
	list
	find
	*/

typedef struct{

	unsigned int id;
	char name[32];
	int age;
	float score;

} Record;


typedef struct{

	FILE *fp;
	unsigned int record_count;
	char name[32];


} Database;


int database_create(Database *db){


	db->fp = fopen(db->name, "wb");

	if(db->fp == NULL){

		return 1;

	}else {

		if(fwrite(db, sizeof(Database), 1, db->fp)){

			return 0;

		}else {

			fclose(db->fp);
			return 1;
		}

		fclose(db->fp);
		return 0;

	}


}



int write_record(Database *db, Record *rec_w){

	if(db->fp == NULL){
		return 1;
	}else {
	
		fwrite(&rec_w, sizeof(Record), 1, db->fp);
	}

	return 0;
}


int read_record(Database *db, Record *rec_r, int index){


	if(index < 0)
		return 1;

	if(index >= db->record_count)
		return 1;


	db->fp = fopen("database.bin", "rb");

	if(db->fp == NULL){

		return 1;

	}else {

		if(fseek(db->fp, sizeof(Record) * index, SEEK_SET) == 0){

			if(fread(rec_r, sizeof(Record), 1, db->fp)){

				fclose(db->fp);

			}else {
				fclose(db->fp);
				return 1;
			}


		}else{
			fclose(db->fp);
			return 1;
		}

	}

	
	return 0;
	
}



int main(void){

	Database db = {NULL, 5, "database.bin"}; 

	if(database_create(&db) == 0){

		printf("Database and Header created");

	}

	int n = 5;
	Record rec[n];
	Record rec_r[n];


	for(int i = 0; i < n; i++){

		rec[i].id = i;
		strcpy(rec[i].name, "kala");
		rec[i].age = 17 + i;
		rec[i].score = i + 10.123;


	}

	
	for(int i =0; i < n; i++){
	
		write_record(&db, &rec[i]);

	}


	fclose(db.fp);
	printf("writer closed\n");


	for(int i =0 ;i < n; i++){

		if(read_record(&db, &rec_r[i], i) == 0){

			printf("ID: %u\n", rec_r[i].id);
			printf("Name: %s\n", rec_r[i].name);
			printf("Age: %d\n", rec_r[i].age);
			printf("Score: %f\n", rec_r[i].score);

			printf("\n");



		}

	}



/*	file = fopen("database.bin", "rb");

	if(file == NULL){

		printf("error reading\n");
	}else {

		printf("Opened!\n");
	}


	if(fread(rec_r, sizeof(Record), n, file)){


		for(int i =0; i < n; i++){

			printf("ID: %u\n", rec_r[i].id);
			printf("Name: %s\n", rec_r[i].name);
			printf("Age: %d\n", rec_r[i].age);
			printf("Score: %f\n", rec_r[i].score);

			printf("\n");

		}

	}

	fclose(file);
	printf("reader closed");

	return 0;



*/



}
