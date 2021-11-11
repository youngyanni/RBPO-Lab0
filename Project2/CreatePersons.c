#include "Header.h"
struct Person* GetPersons(int argc, char* argv[], int* count) {
    /*Кол - во аргументов командной строки*/
    for (int i = 1; i < argc; i++) {
        if (CompareStrings(argv[i], "-person") == 0) {
            *count = *count + 1;
        }
    }
    if (*count < 1) {
        printf("Аргументы не найдены");
        return 0;
    }

    /*Выделение памяти для структуры*/
    struct Person* persons = (struct Person*)malloc(sizeof(struct Person) * *count);/*Размер массива будет равен кол-ву аргументов -pesron командной строки*/
    //инициализация полей для аргументов командной строки 
    for (int i = 0; i < *count; i++) {
        persons[i].firstName = (char*)malloc(1 * strlen("Без имени"));
        strcpy(persons[i].firstName, "Без имени");
        persons[i].surName = (char*)malloc(1 * strlen("Без фамилии "));
        strcpy(persons[i].surName, "Без фамилии");
        persons[i].lastName = (char*)malloc(1 * strlen("Без отчества"));
        strcpy(persons[i].lastName, "Без отчества");
        persons[i].age = 0;
    }


    int indexOfPersons = 0;
    /*
    * Цикл заполнения структуры
    */
    for (int i = 0; i < argc; i++) {/*Проходимся по каждому параметру командой строки*/
        if (CompareStrings(argv[i], "-person") == 0) {/*Если встречается -person, то запускается цикл фильтрации строки */
            for (int j = i + 1; j < argc && CompareStrings(argv[j], "-person") != 0; j++) {
                /**Если встречается --fN, то задаём новую величину памяти для firstName и копируем в него значение следующего параметра
                То же самое делаем и с --sN и -lN**/
                if (CompareStrings(argv[j], "--fN") == 0) {
                    persons[indexOfPersons].firstName = (char*)realloc(persons[indexOfPersons].firstName, 1 * strlen(argv[j + 1]));
                    strcpy(persons[indexOfPersons].firstName, argv[j + 1]);
                }
                if (CompareStrings(argv[j], "--sN") == 0) {
                    persons[indexOfPersons].surName = (char*)realloc(persons[indexOfPersons].surName, 1 * strlen(argv[j + 1]));
                    strcpy(persons[indexOfPersons].surName, argv[j + 1]);
                }
                if (CompareStrings(argv[j], "--lN") == 0) {
                    persons[indexOfPersons].lastName = (char*)realloc(persons[indexOfPersons].lastName, 1 * strlen(argv[j + 1]));
                    strcpy(persons[indexOfPersons].lastName, argv[j + 1]);
                }
                if (CompareStrings(argv[j], "--age") == 0) {
                    int age = atoi(argv[j + 1]);
                    persons[indexOfPersons].age = age;
                }
            }
            indexOfPersons++;
        }
    }
    return persons;/*Возвращаем полученную структуру*/
}