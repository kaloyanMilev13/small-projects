#include <stdio.h>
#include "database.h"

int database_create(Database *db, char *databaseName){


	db->fp = fopen(databaseName, "wb");

	if(db->fp == NULL){
		return 1;

	}else {

		DatabaseHeader header = {0};

		if(fwrite(&header, sizeof(DatabaseHeader), 1, db->fp) != 0){

			fclose(db->fp);
			db->fp = NULL;
			return 0;

		}else {
			fclose(db->fp);
			db->fp = NULL;
			return 1;
		}

		return 0;

	}

}


int database_open(Database *db, char *databaseName){


	if(db->fp != NULL){
		return 1;
	}else{

		switch (db->mode) {


			case DB_READ: db->fp = fopen(databaseName, "rb"); break;

			case DB_WRITE: db->fp = fopen(databaseName, "wb"); break;

			case DB_READ_WRITE: db->fp = fopen(databaseName, "r+b"); break;

		}

		if(db->fp == NULL){
			return 1;
		}else{
			if(fread(&db->record_count, sizeof(unsigned int), 1, db->fp) != 0){

				return 0;

			}

		}
	}

	return 1;


}


int database_close(Database *db){

	if(db->fp == NULL){
		return 1;
	}else{
		fclose(db->fp);
		db->fp = NULL;
	}


	return 0;
}


int find_record(Database *db, int id, Record *result){

	Record rec;

	if(db->fp == NULL){
		return 1;
	}else{

		if(fseek(db->fp, sizeof(DatabaseHeader), SEEK_SET) == 0){

			for(int i = 0; i < db->record_count; i++){

				if(fread(&rec, sizeof(Record), 1, db->fp) != 0){

					if(rec.id == id){

						*result = rec;

						return 0;

					}


				}

			}

		}

	}

	return 1;

}



int database_add(Database *db, Record *rec_w){

	Record temp_rec;

	if(db->fp == NULL){
		return 1;
	}else {

		if(find_record(db, rec_w->id, &temp_rec) != 0){

			if(fseek(db->fp, 0, SEEK_END) == 0){

				if(fwrite(rec_w, sizeof(Record), 1, db->fp) != 0){

					db->record_count++;

					fseek(db->fp, 0, SEEK_SET);

					DatabaseHeader header = {db->record_count};

					if(fwrite(&header, sizeof header, 1, db->fp) != 0){
						fseek(db->fp, 0, SEEK_END);

						return 0;

					}else {

						return 1;
					}
				}



			}

		}

	}

	return 1;
}


int update_record(Database *db, int index, Record *new_rec){

	if(index < 0)
		return 1;

	if(index >= db->record_count)
		return 1;


	if(db->fp == NULL){
		return 1;
	}else{

		if(fseek(db->fp, sizeof(Record) * index + sizeof(DatabaseHeader), SEEK_SET) == 0){

			if(fwrite(new_rec, sizeof(Record), 1,  db->fp) != 0){

				return 0;

			}else {

				return 1;
			}

		}

	}

	return 1;




}


int read_record(Database *db, Record *rec_r, int index){

	if(index < 0)
		return 1;

	if(index >= db->record_count)
		return 1;

	if(db->fp == NULL){
		return 1;
	}else {

		if(fseek(db->fp, sizeof(Record) * index + sizeof(DatabaseHeader), SEEK_SET) == 0){

			if(fread(rec_r, sizeof(Record), 1, db->fp) != 0){
				return 0;
			}

		}
	}

	return 1;
}




int list_records(Database *db){

	Record rec;

	if(db->fp == NULL)
		return 1;

	if(fseek(db->fp, sizeof(DatabaseHeader), SEEK_SET) == 0){

		for(int i = 0; i < db->record_count; i++){

			if(fread(&rec, sizeof(Record), 1, db->fp) == 0){

				return 1;

			}else{

				printf("ID: %d\n", rec.id);
				printf("Name: %s\n", rec.name);
				printf("Age: %d\n", rec.age);
				printf("Score: %f\n", rec.score);

			}
		}


	}


	return 0;

}

int delete_record(Database *db, int index){


	if(index < 0)
		return 1;

	if(index >= db->record_count)
		return 1;


	Record temp;

	if(db->fp == NULL){
		return 1;
	}else {

		for (int i = index; i < (db->record_count - 1); i++) {

			if(read_record(db, &temp, i + 1) != 0){
				return 1;
			}else{
				if(update_record(db, i, &temp) != 0){
					return 1;
				}

			}

		}

	}

	db->record_count--;

	fseek(db->fp, 0, SEEK_SET);

	DatabaseHeader header = {db->record_count};

	if(fwrite(&header, sizeof header, 1, db->fp) != 0)
		fseek(db->fp, 0, SEEK_END);


	return 0;

}
