#include <stdio.h>
typedef struct {
    int id;
    char name[50];
    int age;
} Student;

Student students[100];
int numStudents = 0;

void loadStudentsFromFile() {
    FILE *file = fopen("students.dat", "rb");
    if (file != NULL) {
        fread(&numStudents, sizeof(int), 1, file);
        fread(students, sizeof(Student), numStudents, file);
        fclose(file);
    }
}
void saveStudentsToFile() {
    FILE *file = fopen("students.dat", "wb");
    if (file != NULL) {
        fwrite(&numStudents, sizeof(int), 1, file);
        fwrite(students, sizeof(Student), numStudents, file);
        fclose(file);
    }
}

void printStudents() {
    printf("Danh sach sinh vien:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent() {
    if (numStudents < 100) {
        Student newStudent;
        printf("Nhap ID: ");
        scanf("%d", &newStudent.id);
        getchar();
        printf("Nhap ten: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
        printf("Nhap tuoi: ");
        scanf("%d", &newStudent.age);

        students[numStudents++] = newStudent;
        saveStudentsToFile();
    } else {
        printf("Khong the them sinh vien. Mang da day.\n");
    }
}

void editStudent() {
    int id;
    printf("Nhap ID cua sinh viên can sua: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            printf("Nhap ten moi: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);
            saveStudentsToFile();
            return;
        }
    }
    printf("Khong tim thay sinh viên voi ID %d.\n", id);
}

void deleteStudent() {
    int id;
    printf("Nhap ID cua sinh viên can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            for (int j = i; j < numStudents - 1; j++) {
                students[j] = students[j + 1];
            }
            numStudents--;
            saveStudentsToFile();
            return;
        }
    }
    printf("Khong tim thay sinh viên voi ID %d.\n", id);
}

void searchStudent() {
    char name[50];
    printf("Nhap ten sinh viên can tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Ket qua tim kiem:\n");
    for (int i = 0; i < numStudents; i++) {
        if (strstr(students[i].name, name) != NULL) {
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
        }
    }
}

void sortStudents() {
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = i + 1; j < numStudents; j++) {
            if (students[i].id > students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveStudentsToFile();
    printf("Danh sach sinh viên da duoc sap xep.\n");
}

int main() {
    loadStudentsFromFile();

    int choice;

    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh viên\n");
        printf("6. Sap xep danh sach sinh viên\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                editStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 7);

    return 0;
}

