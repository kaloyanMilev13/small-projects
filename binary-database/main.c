#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* 	add
	get
	update
	delete
	list
	find
	*/

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




int database_create(Database *db, char databaseName[32]){

	
	db->fp = fopen(databaseName, "wb");

	if(db->fp == NULL){
		return 1;

	}else {

		DatabaseHeader header = {0};

		if(fwrite(&header, sizeof(DatabaseHeader), 1, db->fp) == 0){

			return 0;

		}else {
			fclose(db->fp);
			return 1;
		}

		return 0;

	}

}


int database_open(Database *db, char databaseName[32]){


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
				
				return 1;

			}

		}
	}

	return 0;


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



int database_add(Database *db, Record *rec_w){

	if(db->fp == NULL){
		return 1;
	}else {
	
		if(fwrite(rec_w, sizeof(Record), 1, db->fp) == 0){

			FILE *temp = db->fp;

			fseek(temp, 0, SEEK_SET);
			
			DatabaseHeader header = {db->record_count};

			if(fwrite(&header, sizeof header, 1, temp) == 0){
				db->record_count++;
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

			if(fread(rec_r, sizeof(Record), 1, db->fp) == 0){

				return 0;

			}

		}else{
			return 1;
		}

	}

	
	return 0;
	
}


int find_record(){



}

int update_record(){


}


int list_records(){

}

int delete_record(){


}

/*
 * Include your database header here when you split the project:
 *
 * #include "database.h"
 */

/* ---------------------------------------------------------
 * Test helpers
 * --------------------------------------------------------- */

static int failures = 0;
static int tests = 0;

#define TEST(condition, description)                 \
    do {                                             \
        tests++;                                    \
        if (condition) {                            \
            printf("[PASS] %s\n", description);     \
        } else {                                     \
            printf("[FAIL] %s\n", description);     \
            failures++;                             \
        }                                            \
    } while (0)


static int records_equal(const Record *a, const Record *b)
{
    return a->id == b->id &&
           strcmp(a->name, b->name) == 0 &&
           a->age == b->age &&
           a->score == b->score;
}


/* ---------------------------------------------------------
 * Main
 * --------------------------------------------------------- */

int main(void)
{
    const char *filename = "test_database.bin";

    Database db = {
        .fp = NULL,
        .record_count = 0,
        .mode = DB_READ_WRITE
    };

    Record record;
    Record result;


    /* -----------------------------------------------------
     * 1. CREATE
     * ----------------------------------------------------- */

    printf("\n=== CREATE ===\n");

    remove(filename);

    TEST(
        database_create(&db, (char *)filename) == 0,
        "Create database"
    );

    TEST(
        db.fp == NULL,
        "Database is closed after creation"
    );


    /* -----------------------------------------------------
     * 2. OPEN
     * ----------------------------------------------------- */

    printf("\n=== OPEN ===\n");

    TEST(
        database_open(&db, (char *)filename) == 0,
        "Open database"
    );

    TEST(
        db.fp != NULL,
        "File handle is valid"
    );

    TEST(
        db.record_count == 0,
        "New database contains zero records"
    );


    /* -----------------------------------------------------
     * 3. ADD RECORDS
     * ----------------------------------------------------- */

    printf("\n=== ADD ===\n");

    record = (Record){
        .id = 1,
        .name = "Alice",
        .age = 20,
        .score = 85.5f
    };

    TEST(
        database_add(&db, &record) == 0,
        "Add first record"
    );

    TEST(
        db.record_count == 1,
        "Record count becomes 1"
    );


    record = (Record){
        .id = 2,
        .name = "Bob",
        .age = 21,
        .score = 91.2f
    };

    TEST(
        database_add(&db, &record) == 0,
        "Add second record"
    );

    TEST(
        db.record_count == 2,
        "Record count becomes 2"
    );


    record = (Record){
        .id = 3,
        .name = "Charlie",
        .age = 22,
        .score = 77.7f
    };

    TEST(
        database_add(&db, &record) == 0,
        "Add third record"
    );

    TEST(
        db.record_count == 3,
        "Record count becomes 3"
    );


    /* -----------------------------------------------------
     * 4. GET / READ
     * ----------------------------------------------------- */

    printf("\n=== READ ===\n");

    TEST(
        read_record(&db, &result, 0) == 0,
        "Read record 0"
    );

    TEST(
        result.id == 1 &&
        strcmp(result.name, "Alice") == 0 &&
        result.age == 20 &&
        result.score == 85.5f,
        "Record 0 contains correct data"
    );


    TEST(
        read_record(&db, &result, 1) == 0,
        "Read record 1"
    );

    TEST(
        result.id == 2 &&
        strcmp(result.name, "Bob") == 0,
        "Record 1 contains correct data"
    );


    TEST(
        read_record(&db, &result, 2) == 0,
        "Read record 2"
    );

    TEST(
        result.id == 3 &&
        strcmp(result.name, "Charlie") == 0,
        "Record 2 contains correct data"
    );


    /* Invalid indexes */

    TEST(
        read_record(&db, &result, -1) != 0,
        "Reject negative index"
    );

    TEST(
        read_record(&db, &result, 3) != 0,
        "Reject index equal to record_count"
    );

    TEST(
        read_record(&db, &result, 100) != 0,
        "Reject index beyond record_count"
    );


    /* -----------------------------------------------------
     * 5. FIND
     * ----------------------------------------------------- */

    printf("\n=== FIND ===\n");

    TEST(
        find_record(&db, 2, &result) == 0,
        "Find existing ID"
    );

    TEST(
        result.id == 2 &&
        strcmp(result.name, "Bob") == 0,
        "Find returns correct record"
    );


    TEST(
        find_record(&db, 999, &result) != 0,
        "Finding nonexistent ID fails"
    );


    /* -----------------------------------------------------
     * 6. DUPLICATE ID
     * ----------------------------------------------------- */

    printf("\n=== DUPLICATE ID ===\n");

    record = (Record){
        .id = 2,
        .name = "Duplicate",
        .age = 99,
        .score = 0.0f
    };

    TEST(
        database_add(&db, &record) != 0,
        "Reject duplicate ID"
    );

    TEST(
        db.record_count == 3,
        "Duplicate ID does not increase record count"
    );


    /* -----------------------------------------------------
     * 7. UPDATE
     * ----------------------------------------------------- */

    printf("\n=== UPDATE ===\n");

    record = (Record){
        .id = 2,
        .name = "BobUpdated",
        .age = 30,
        .score = 99.9f
    };

    TEST(
        update_record(&db, 1, &record) == 0,
        "Update record 1"
    );


    TEST(
        read_record(&db, &result, 1) == 0,
        "Read updated record"
    );

    TEST(
        records_equal(&result, &record),
        "Updated record contains correct data"
    );


    /* -----------------------------------------------------
     * 8. UPDATE INVALID INDEX
     * ----------------------------------------------------- */

    TEST(
        update_record(&db, -1, &record) != 0,
        "Reject update with negative index"
    );

    TEST(
        update_record(&db, 100, &record) != 0,
        "Reject update beyond record count"
    );


    /* -----------------------------------------------------
     * 9. LIST
     * ----------------------------------------------------- */

    printf("\n=== LIST ===\n");

    printf("\nDatabase contents:\n");

    TEST(
        list_records(&db) == 0,
        "List all records"
    );


    /* -----------------------------------------------------
     * 10. CLOSE
     * ----------------------------------------------------- */

    printf("\n=== CLOSE ===\n");

    TEST(
        database_close(&db) == 0,
        "Close database"
    );

    TEST(
        db.fp == NULL,
        "File pointer is NULL after close"
    );


    /* -----------------------------------------------------
     * 11. REOPEN / PERSISTENCE
     * ----------------------------------------------------- */

    printf("\n=== PERSISTENCE ===\n");

    db.mode = DB_READ_WRITE;

    TEST(
        database_open(&db, (char *)filename) == 0,
        "Reopen database"
    );

    TEST(
        db.record_count == 3,
        "Record count persisted"
    );


    TEST(
        find_record(&db, 1, &result) == 0,
        "Original record still exists"
    );

    TEST(
        find_record(&db, 2, &result) == 0 &&
        strcmp(result.name, "BobUpdated") == 0,
        "Updated record persisted"
    );

    TEST(
        find_record(&db, 3, &result) == 0,
        "Third record still exists"
    );


    /* -----------------------------------------------------
     * 12. DELETE
     * ----------------------------------------------------- */

    printf("\n=== DELETE ===\n");

    TEST(
        delete_record(&db, 1) == 0,
        "Delete record at index 1"
    );

    TEST(
        db.record_count == 2,
        "Record count decreases after deletion"
    );


    TEST(
        find_record(&db, 2, &result) != 0,
        "Deleted record no longer exists"
    );


    /* Make sure other records survived */

    TEST(
        find_record(&db, 1, &result) == 0,
        "First record survives deletion"
    );

    TEST(
        find_record(&db, 3, &result) == 0,
        "Third record survives deletion"
    );


    /* -----------------------------------------------------
     * 13. DELETE INVALID INDEX
     * ----------------------------------------------------- */

    TEST(
        delete_record(&db, -1) != 0,
        "Reject delete with negative index"
    );

    TEST(
        delete_record(&db, 100) != 0,
        "Reject delete beyond record count"
    );


    /* -----------------------------------------------------
     * 14. FINAL LIST
     * ----------------------------------------------------- */

    printf("\n=== FINAL DATABASE ===\n");

    TEST(
        list_records(&db) == 0,
        "List final database"
    );


    /* -----------------------------------------------------
     * 15. FINAL CLOSE
     * ----------------------------------------------------- */

    printf("\n=== FINAL CLOSE ===\n");

    TEST(
        database_close(&db) == 0,
        "Final database close"
    );

    TEST(
        db.fp == NULL,
        "File pointer is NULL after final close"
    );


    /* -----------------------------------------------------
     * RESULT
     * ----------------------------------------------------- */

    printf("\n====================================\n");
    printf("Tests:    %d\n", tests);
    printf("Failures: %d\n", failures);
    printf("====================================\n");

    if (failures == 0) {
        printf("ALL TESTS PASSED\n");
    } else {
        printf("SOME TESTS FAILED\n");
    }


    /* Clean up test database */
    remove(filename);

    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
