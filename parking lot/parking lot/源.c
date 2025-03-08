#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>

// ���������������
#define MAX_CARS 50
#define MAX_BOOKINGS 100
#define MAX_USERS 50
#define MAX_LOGS 200

// ���峵���ṹ�壬���ڴ洢ÿ�����Ļ�����Ϣ
struct Car {
    char plate[20];      // ���ƺţ�Ψһ��ʶ����
    int is_vip;          // �Ƿ�ΪVIP��1�ǣ�0��
    int in_garage;       // �Ƿ��ڿ⣺1�ڣ�0����
    int car_type;        // �������ͣ�0С����1����
    char entry_time[20]; // ���ʱ��
    char exit_time[20];  // ����ʱ��
};

// ����ԤԼ�ṹ�壬���ڹ���ͣ��ԤԼ
struct Booking {
    char plate[20];      // ���ƺ�
    int time;            // ԤԼʱ�䣨Сʱ��
};

// �����û��ṹ�壬�������ֹ���Ա����ͨ�û�
struct User {
    char username[20];   // �û���
    char password[20];   // ����
    int is_admin;        // �Ƿ�Ϊ����Ա��1�ǣ�0��
};

// ������־�ṹ�壬���ڼ�¼ϵͳ����
struct Log {
    char action[50];     // ��������
    char timestamp[20];  // ʱ���
};

// ȫ�ֱ�������
struct Car cars[MAX_CARS];
struct Booking bookings[MAX_BOOKINGS];
struct User users[MAX_USERS];
struct Log logs[MAX_LOGS];
int car_count = 0;
int booking_count = 0;
int user_count = 0;
int log_count = 0;
int logged_in = 0; // �Ƿ��ѵ�¼
char current_user[20]; // ��ǰ��¼�û�

// ��������
void print_menu();
void login(); // ��¼
void register_user();
void add_car();
void query_cars(); // ��ѯ�ڿ⳵��
void delete_car();
void book_time();
void query_bookings();
void exit_car();
void calculate_fee();
void add_log(const char* action);
void view_logs();
int validate_plate(const char* plate); // ��֤����
int validate_time(int time); // ��֤ʱ��
void get_current_time(char* buffer); // ��ʽ��ʱ��
void print_welcome(); // ��ӭ��Ϣ
void print_divider(); // �ָ���
void query_fee_rates(); // �ƷѲ�ѯ����
void save_cars_to_file(); // ���泵����Ϣ���ļ�
void load_cars_from_file(); // ���ļ����س�����Ϣ

int main() {
    // ��ʼ��һ��Ĭ�Ϲ���Ա�˻�
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "admin123");
    users[0].is_admin = 1;
    user_count = 1;

    int choice;
    print_welcome(); // ��ʾ��ӭ��Ϣ
    load_cars_from_file(); // ��������ʱ���س�����Ϣ
    while (1) {
        print_menu();
        printf("��ѡ��");
        scanf("%d", &choice);
        switch (choice) {
        case 1: login(); break;
        case 2: register_user(); break;
        case 3: add_car(); break;
        case 4: query_cars(); break;
        case 5: delete_car(); break;
        case 6: book_time(); break;
        case 7: query_bookings(); break;
        case 8: exit_car(); break;
        case 9: calculate_fee(); break;
        case 10: view_logs(); break;
        case 11: query_fee_rates(); break;
        case 0:
            save_cars_to_file(); // �˳�ʱ���泵����Ϣ
            printf("�˳�ϵͳ��ллʹ�ã�\n");
            return 0;
        default: printf("��Чѡ�����������룡\n");
        }
        print_divider(); // ÿ�β������ӡ�ָ���
    }
    return 0;
}

// ��ӡ���˵���չʾ���й���ѡ��
void print_menu() {
    printf("\n========================================\n");
    printf("       ͣ������Ϣ����ϵͳ\n");
    printf("========================================\n");
    printf("1. �û���¼\n");
    printf("2. ע�����û�\n");
    if (logged_in) {
        printf("3. ¼�복����Ϣ\n");
        printf("4. ��ѯ�����ڿ⳵����Ϣ\n");
        printf("5. ɾ��������Ϣ\n");
        printf("6. ʱ��ԤԼ\n");
        printf("7. ʱ��ԤԼ��ѯ\n");
        printf("8. ��������\n");
        printf("9. ����ͣ������\n");
        printf("10. �鿴������־\n");
        printf("11. ��ѯ�Ʒѱ�׼\n");
    }
    printf("0. �˳�ϵͳ\n");
    printf("========================================\n");
}

// �û���¼����֤�û���������
void login() {
    char username[20], password[20];
    printf("�������û�����");
    scanf("%s", username);
    printf("���������룺");
    scanf("%s", password);
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            logged_in = 1;
            strcpy(current_user, username);
            printf("��¼�ɹ�����ӭ %s\n", username);
            add_log("�û���¼");
            return;
        }
    }
    printf("�û�����������󣬵�¼ʧ�ܣ�\n");
}

// ע�����û���������û��б�
void register_user() {
    if (user_count >= MAX_USERS) {
        printf("�û������Ѵ����ޣ��޷�ע�ᣡ\n");
        return;
    }
    printf("���������û�����");
    scanf("%s", users[user_count].username);
    printf("���������룺");
    scanf("%s", users[user_count].password);
    users[user_count].is_admin = 0; // Ĭ�Ϸǹ���Ա
    user_count++;
    printf("�û�ע��ɹ���\n");
    add_log("���û�ע��");
}

// ¼�복����Ϣ���Զ���¼���ʱ��
void add_car() {
    if (!logged_in) {
        printf("���ȵ�¼��\n");
        return;
    }
    if (car_count >= MAX_CARS) {
        printf("ͣ�����������޷�¼�룡\n");
        return;
    }
    printf("�����복�ƺţ�");
    scanf("%s", cars[car_count].plate);
    if (!validate_plate(cars[car_count].plate)) {
        printf("���ƺŸ�ʽ����\n");
        return;
    }
    printf("�Ƿ�ΪVIP��1Ϊ�ǣ�0Ϊ�񣩣�");
    scanf("%d", &cars[car_count].is_vip);
    printf("�������ͣ�0ΪС����1Ϊ��������");
    scanf("%d", &cars[car_count].car_type);

    // �Զ���¼��ǰʱ����Ϊ���ʱ��
    get_current_time(cars[car_count].entry_time);
    printf("���ʱ���Ѽ�¼Ϊ��%s\n", cars[car_count].entry_time);

    cars[car_count].in_garage = 1;
    strcpy(cars[car_count].exit_time, "δ����"); // ��ʼ������ʱ��
    car_count++;
    printf("������Ϣ¼��ɹ���\n");
    add_log("¼�복����Ϣ");
    save_cars_to_file(); // ÿ��¼��󱣴浽�ļ�
}

// ��ѯ�����ڿ⳵����Ϣ����ʾ��ϸ��Ϣ
void query_cars() {
    if (!logged_in) {
        printf("���ȵ�¼��\n");
        return;
    }
    printf("\n=== �ڿ⳵����Ϣ ===\n");
    for (int i = 0; i < car_count; i++) {
        if (cars[i].in_garage) {
            printf("���ƺţ�%s, VIP��%d, ���ͣ�%s, ���ʱ�䣺%s\n",
                cars[i].plate, cars[i].is_vip,
                cars[i].car_type == 0 ? "С��" : "����",
                cars[i].entry_time);
        }
    }
    if (car_count == 0) {
        printf("��ǰ�޳�����Ϣ��\n");
    }
    add_log("��ѯ������Ϣ");
}

// ɾ��������Ϣ�����������Ƴ�
void delete_car() {
    if (!logged_in) {
        printf("���ȵ�¼��\n");
        return;
    }
    char plate[20];
    printf("������Ҫɾ���ĳ��ƺţ�");
    scanf("%s", plate);
    for (int i = 0; i < car_count; i++) {
        if (strcmp(cars[i].plate, plate) == 0) {
            for (int j = i; j < car_count - 1; j++) {
                cars[j] = cars[j + 1];
            }
            car_count--;
            printf("������Ϣɾ���ɹ���\n");
            add_log("ɾ��������Ϣ");
            save_cars_to_file(); // ɾ���󱣴浽�ļ�
            return;
        }
    }
    printf("δ�ҵ��ó��ƺţ�\n");
}

// ʱ��ԤԼ����¼������ͣ��ԤԼ
void book_time() {
    if (!logged_in) {
        printf("���ȵ�¼��\n");
        return;
    }
    if (booking_count >= MAX_BOOKINGS) {
        printf("ԤԼ�������޷�������\n");
        return;
    }
    printf("������ԤԼ���ƺţ�");
    scanf("%s", bookings[booking_count].plate);
    printf("������ԤԼʱ�䣨Сʱ��0-23����");
    scanf("%d", &bookings[booking_count].time);
    if (!validate_time(bookings[booking_count].time)) {
        printf("ʱ���������\n");
        return;
    }
    booking_count++;
    printf("ԤԼ�ɹ���\n");
    add_log("ʱ��ԤԼ");
}

// ��ѯԤԼ��Ϣ����ʾ����ԤԼ��¼
void query_bookings() {
    if (!logged_in) {
        printf("���ȵ�¼��\n");
        return;
    }
    printf("\n=== ԤԼ��Ϣ ===\n");
    for (int i = 0; i < booking_count; i++) {
        printf("���ƺţ�%s, ԤԼʱ�䣺%dʱ\n",
            bookings[i].plate, bookings[i].time);
    }
    if (booking_count == 0) {
        printf("��ǰ��ԤԼ��Ϣ��\n");
    }
    add_log("��ѯԤԼ��Ϣ");
}

// �������⣬��¼����ʱ��
void exit_car() {
    if (!logged_in) {
        printf("���ȵ�¼��\n");
        return;
    }
    char plate[20];
    printf("��������⳵�ƺţ�");
    scanf("%s", plate);
    for (int i = 0; i < car_count; i++) {
        if (strcmp(cars[i].plate, plate) == 0 && cars[i].in_garage) {
            get_current_time(cars[i].exit_time);
            cars[i].in_garage = 0;
            printf("��������ɹ�������ʱ�䣺%s\n", cars[i].exit_time);
            add_log("��������");
            save_cars_to_file(); // ����󱣴浽�ļ�
            return;
        }
    }
    printf("δ�ҵ��ó��ƺŻ������ڿ⣡\n");
}

// ����ͣ�����ã��������ͳ���ʱ��
void calculate_fee() {
    if (!logged_in) {
        printf("���ȵ�¼��\n");
        return;
    }
    char plate[20];
    printf("�����복�ƺţ�");
    scanf("%s", plate);
    for (int i = 0; i < car_count; i++) {
        if (strcmp(cars[i].plate, plate) == 0 && !cars[i].in_garage) {
            struct tm entry_tm = { 0 }, exit_tm = { 0 };
            sscanf(cars[i].entry_time, "%d-%d-%d %d:%d",
                &entry_tm.tm_mon, &entry_tm.tm_mday, &entry_tm.tm_year,
                &entry_tm.tm_hour, &entry_tm.tm_min);
            sscanf(cars[i].exit_time, "%d-%d-%d %d:%d",
                &exit_tm.tm_mon, &exit_tm.tm_mday, &exit_tm.tm_year,
                &exit_tm.tm_hour, &exit_tm.tm_min);
            entry_tm.tm_year -= 1900;
            exit_tm.tm_year -= 1900;
            entry_tm.tm_mon -= 1;
            exit_tm.tm_mon -= 1;

            time_t entry_time = mktime(&entry_tm);
            time_t exit_time = mktime(&exit_tm);
            int minutes = (int)(difftime(exit_time, entry_time) / 60);
            float fee = (cars[i].is_vip ? 0.5 : 1.0) * minutes;
            if (cars[i].car_type == 1) fee *= 1.5;
            printf("���ƺţ�%s, ͣ��ʱ����%d����, ���ã�%.2fԪ\n",
                cars[i].plate, minutes, fee);
            add_log("����ͣ������");
            return;
        }
    }
    printf("δ�ҵ��ó��ƺŻ���δ���⣡\n");
}

// �����־����¼ϵͳ����
void add_log(const char* action) {
    if (log_count >= MAX_LOGS) return;
    strcpy(logs[log_count].action, action);
    get_current_time(logs[log_count].timestamp);
    log_count++;
}

// �鿴��־����ʾ���в�����¼
void view_logs() {
    if (!logged_in) {
        printf("���ȵ�¼��\n");
        return;
    }
    printf("\n=== ������־ ===\n");
    for (int i = 0; i < log_count; i++) {
        printf("ʱ�䣺%s, ������%s\n", logs[i].timestamp, logs[i].action);
    }
    if (log_count == 0) {
        printf("������־��¼��\n");
    }
}

// ��֤���ƺţ�ȷ��������Ч
int validate_plate(const char* plate) {
    if (strlen(plate) < 3) return 0; // ���賵������3λ
    return 1;
}

// ��֤ʱ�䣬ȷ���ں���Χ��
int validate_time(int time) {
    return (time >= 0 && time <= 23);
}

// ��ȡ��ǰʱ�䣬��ʽ��Ϊ�ַ���
void get_current_time(char* buffer) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    sprintf(buffer, "%02d-%02d-%d %02d:%02d", t->tm_mon + 1, t->tm_mday,
        t->tm_year + 1900, t->tm_hour, t->tm_min);
}

// ��ӡ��ӭ��Ϣ
void print_welcome() {
    printf("\n========================================\n");
    printf("       ��ӭʹ��ͣ��������ϵͳ\n");
    printf("       ��ǰ���ڣ�2025��2��27��\n");
    printf("========================================\n");
}

// ��ӡ�ָ���
void print_divider() {
    printf("\n----------------------------------------\n");
}

// ��ѯ�Ʒѱ�׼
void query_fee_rates() {
    if (!logged_in) {
        printf("���ȵ�¼��\n");
        return;
    }
    printf("\n========================================\n");
    printf("       ͣ�����Ʒѱ�׼\n");
    printf("========================================\n");
    printf("1. С������VIP����ÿСʱ 10 Ԫ\n");
    printf("2. С����VIP����ÿСʱ 5 Ԫ\n");
    printf("3. ��������VIP����ÿСʱ 15 Ԫ\n");
    printf("4. ������VIP����ÿСʱ 7.5 Ԫ\n");
    printf("----------------------------------------\n");
    printf("˵����\n");
    printf("- �Ʒѵ�λΪСʱ������һСʱ��һСʱ���㡣\n");
    printf("- VIP�û�����50%%�ۿۡ�\n");
    printf("- ���շ��ý��ڳ���ʱ����ʵ��ͣ��ʱ�����㡣\n");
    printf("========================================\n");
    add_log("��ѯ�Ʒѱ�׼");
}

// ���泵����Ϣ���ļ�
void save_cars_to_file() {
    FILE* fp = fopen("cars.txt", "w"); // ��д��ģʽ���ļ�
    if (fp == NULL) {
        printf("�޷����ļ����泵����Ϣ��\n");
        return;
    }
    for (int i = 0; i < car_count; i++) {
        fprintf(fp, "%s,%d,%d,%d,%s,%s\n",
            cars[i].plate, cars[i].is_vip, cars[i].in_garage,
            cars[i].car_type, cars[i].entry_time, cars[i].exit_time);
    }
    fclose(fp);
    printf("������Ϣ�ѱ��浽 cars.txt\n");
    add_log("���泵����Ϣ���ļ�");
}

// ���ļ����س�����Ϣ
void load_cars_from_file() {
    FILE* fp = fopen("cars.txt", "r"); // �Զ�ȡģʽ���ļ�
    if (fp == NULL) {
        printf("�޷����ļ����س�����Ϣ�������ļ������ڡ�\n");
        return;
    }
    car_count = 0; // ���ó�������
    while (fscanf(fp, "%[^,],%d,%d,%d,%[^,],%[^\n]\n",
        cars[car_count].plate, &cars[car_count].is_vip,
        &cars[car_count].in_garage, &cars[car_count].car_type,
        cars[car_count].entry_time, cars[car_count].exit_time) == 6) {
        car_count++;
        if (car_count >= MAX_CARS) {
            printf("���������������ޣ�ֹͣ���ء�\n");
            break;
        }
    }
    fclose(fp);
    printf("�Ѵ� cars.txt ���� %d ��������Ϣ\n", car_count);
    add_log("���ļ����س�����Ϣ");
}