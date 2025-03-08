#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>

// 定义最大数量常量
#define MAX_CARS 50
#define MAX_BOOKINGS 100
#define MAX_USERS 50
#define MAX_LOGS 200

// 定义车辆结构体，用于存储每辆车的基本信息
struct Car {
    char plate[20];      // 车牌号，唯一标识车辆
    int is_vip;          // 是否为VIP：1是，0否
    int in_garage;       // 是否在库：1在，0不在
    int car_type;        // 车辆类型：0小车，1货车
    char entry_time[20]; // 入库时间
    char exit_time[20];  // 出库时间
};

// 定义预约结构体，用于管理停车预约
struct Booking {
    char plate[20];      // 车牌号
    int time;            // 预约时间（小时）
};

// 定义用户结构体，用于区分管理员和普通用户
struct User {
    char username[20];   // 用户名
    char password[20];   // 密码
    int is_admin;        // 是否为管理员：1是，0否
};

// 定义日志结构体，用于记录系统操作
struct Log {
    char action[50];     // 操作内容
    char timestamp[20];  // 时间戳
};

// 全局变量声明
struct Car cars[MAX_CARS];
struct Booking bookings[MAX_BOOKINGS];
struct User users[MAX_USERS];
struct Log logs[MAX_LOGS];
int car_count = 0;
int booking_count = 0;
int user_count = 0;
int log_count = 0;
int logged_in = 0; // 是否已登录
char current_user[20]; // 当前登录用户

// 函数声明
void print_menu();
void login(); // 登录
void register_user();
void add_car();
void query_cars(); // 查询在库车辆
void delete_car();
void book_time();
void query_bookings();
void exit_car();
void calculate_fee();
void add_log(const char* action);
void view_logs();
int validate_plate(const char* plate); // 验证车牌
int validate_time(int time); // 验证时间
void get_current_time(char* buffer); // 格式化时间
void print_welcome(); // 欢迎信息
void print_divider(); // 分割线
void query_fee_rates(); // 计费查询功能
void save_cars_to_file(); // 保存车辆信息到文件
void load_cars_from_file(); // 从文件加载车辆信息

int main() {
    // 初始化一个默认管理员账户
    strcpy(users[0].username, "admin");
    strcpy(users[0].password, "admin123");
    users[0].is_admin = 1;
    user_count = 1;

    int choice;
    print_welcome(); // 显示欢迎信息
    load_cars_from_file(); // 程序启动时加载车辆信息
    while (1) {
        print_menu();
        printf("请选择：");
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
            save_cars_to_file(); // 退出时保存车辆信息
            printf("退出系统，谢谢使用！\n");
            return 0;
        default: printf("无效选择，请重新输入！\n");
        }
        print_divider(); // 每次操作后打印分割线
    }
    return 0;
}

// 打印主菜单，展示所有功能选项
void print_menu() {
    printf("\n========================================\n");
    printf("       停车场信息管理系统\n");
    printf("========================================\n");
    printf("1. 用户登录\n");
    printf("2. 注册新用户\n");
    if (logged_in) {
        printf("3. 录入车辆信息\n");
        printf("4. 查询所有在库车辆信息\n");
        printf("5. 删除车辆信息\n");
        printf("6. 时间预约\n");
        printf("7. 时间预约查询\n");
        printf("8. 车辆出库\n");
        printf("9. 计算停车费用\n");
        printf("10. 查看操作日志\n");
        printf("11. 查询计费标准\n");
    }
    printf("0. 退出系统\n");
    printf("========================================\n");
}

// 用户登录，验证用户名和密码
void login() {
    char username[20], password[20];
    printf("请输入用户名：");
    scanf("%s", username);
    printf("请输入密码：");
    scanf("%s", password);
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            logged_in = 1;
            strcpy(current_user, username);
            printf("登录成功！欢迎 %s\n", username);
            add_log("用户登录");
            return;
        }
    }
    printf("用户名或密码错误，登录失败！\n");
}

// 注册新用户，添加至用户列表
void register_user() {
    if (user_count >= MAX_USERS) {
        printf("用户数量已达上限，无法注册！\n");
        return;
    }
    printf("请输入新用户名：");
    scanf("%s", users[user_count].username);
    printf("请输入密码：");
    scanf("%s", users[user_count].password);
    users[user_count].is_admin = 0; // 默认非管理员
    user_count++;
    printf("用户注册成功！\n");
    add_log("新用户注册");
}

// 录入车辆信息，自动记录入库时间
void add_car() {
    if (!logged_in) {
        printf("请先登录！\n");
        return;
    }
    if (car_count >= MAX_CARS) {
        printf("停车场已满，无法录入！\n");
        return;
    }
    printf("请输入车牌号：");
    scanf("%s", cars[car_count].plate);
    if (!validate_plate(cars[car_count].plate)) {
        printf("车牌号格式错误！\n");
        return;
    }
    printf("是否为VIP（1为是，0为否）：");
    scanf("%d", &cars[car_count].is_vip);
    printf("车辆类型（0为小车，1为货车）：");
    scanf("%d", &cars[car_count].car_type);

    // 自动记录当前时间作为入库时间
    get_current_time(cars[car_count].entry_time);
    printf("入库时间已记录为：%s\n", cars[car_count].entry_time);

    cars[car_count].in_garage = 1;
    strcpy(cars[car_count].exit_time, "未出库"); // 初始化出库时间
    car_count++;
    printf("车辆信息录入成功！\n");
    add_log("录入车辆信息");
    save_cars_to_file(); // 每次录入后保存到文件
}

// 查询所有在库车辆信息，显示详细信息
void query_cars() {
    if (!logged_in) {
        printf("请先登录！\n");
        return;
    }
    printf("\n=== 在库车辆信息 ===\n");
    for (int i = 0; i < car_count; i++) {
        if (cars[i].in_garage) {
            printf("车牌号：%s, VIP：%d, 类型：%s, 入库时间：%s\n",
                cars[i].plate, cars[i].is_vip,
                cars[i].car_type == 0 ? "小车" : "货车",
                cars[i].entry_time);
        }
    }
    if (car_count == 0) {
        printf("当前无车辆信息！\n");
    }
    add_log("查询车辆信息");
}

// 删除车辆信息，从数组中移除
void delete_car() {
    if (!logged_in) {
        printf("请先登录！\n");
        return;
    }
    char plate[20];
    printf("请输入要删除的车牌号：");
    scanf("%s", plate);
    for (int i = 0; i < car_count; i++) {
        if (strcmp(cars[i].plate, plate) == 0) {
            for (int j = i; j < car_count - 1; j++) {
                cars[j] = cars[j + 1];
            }
            car_count--;
            printf("车辆信息删除成功！\n");
            add_log("删除车辆信息");
            save_cars_to_file(); // 删除后保存到文件
            return;
        }
    }
    printf("未找到该车牌号！\n");
}

// 时间预约，记录车辆的停车预约
void book_time() {
    if (!logged_in) {
        printf("请先登录！\n");
        return;
    }
    if (booking_count >= MAX_BOOKINGS) {
        printf("预约已满，无法新增！\n");
        return;
    }
    printf("请输入预约车牌号：");
    scanf("%s", bookings[booking_count].plate);
    printf("请输入预约时间（小时，0-23）：");
    scanf("%d", &bookings[booking_count].time);
    if (!validate_time(bookings[booking_count].time)) {
        printf("时间输入错误！\n");
        return;
    }
    booking_count++;
    printf("预约成功！\n");
    add_log("时间预约");
}

// 查询预约信息，显示所有预约记录
void query_bookings() {
    if (!logged_in) {
        printf("请先登录！\n");
        return;
    }
    printf("\n=== 预约信息 ===\n");
    for (int i = 0; i < booking_count; i++) {
        printf("车牌号：%s, 预约时间：%d时\n",
            bookings[i].plate, bookings[i].time);
    }
    if (booking_count == 0) {
        printf("当前无预约信息！\n");
    }
    add_log("查询预约信息");
}

// 车辆出库，记录出库时间
void exit_car() {
    if (!logged_in) {
        printf("请先登录！\n");
        return;
    }
    char plate[20];
    printf("请输入出库车牌号：");
    scanf("%s", plate);
    for (int i = 0; i < car_count; i++) {
        if (strcmp(cars[i].plate, plate) == 0 && cars[i].in_garage) {
            get_current_time(cars[i].exit_time);
            cars[i].in_garage = 0;
            printf("车辆出库成功！出库时间：%s\n", cars[i].exit_time);
            add_log("车辆出库");
            save_cars_to_file(); // 出库后保存到文件
            return;
        }
    }
    printf("未找到该车牌号或车辆不在库！\n");
}

// 计算停车费用，基于入库和出库时间
void calculate_fee() {
    if (!logged_in) {
        printf("请先登录！\n");
        return;
    }
    char plate[20];
    printf("请输入车牌号：");
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
            printf("车牌号：%s, 停车时长：%d分钟, 费用：%.2f元\n",
                cars[i].plate, minutes, fee);
            add_log("计算停车费用");
            return;
        }
    }
    printf("未找到该车牌号或车辆未出库！\n");
}

// 添加日志，记录系统操作
void add_log(const char* action) {
    if (log_count >= MAX_LOGS) return;
    strcpy(logs[log_count].action, action);
    get_current_time(logs[log_count].timestamp);
    log_count++;
}

// 查看日志，显示所有操作记录
void view_logs() {
    if (!logged_in) {
        printf("请先登录！\n");
        return;
    }
    printf("\n=== 操作日志 ===\n");
    for (int i = 0; i < log_count; i++) {
        printf("时间：%s, 操作：%s\n", logs[i].timestamp, logs[i].action);
    }
    if (log_count == 0) {
        printf("暂无日志记录！\n");
    }
}

// 验证车牌号，确保输入有效
int validate_plate(const char* plate) {
    if (strlen(plate) < 3) return 0; // 假设车牌至少3位
    return 1;
}

// 验证时间，确保在合理范围内
int validate_time(int time) {
    return (time >= 0 && time <= 23);
}

// 获取当前时间，格式化为字符串
void get_current_time(char* buffer) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    sprintf(buffer, "%02d-%02d-%d %02d:%02d", t->tm_mon + 1, t->tm_mday,
        t->tm_year + 1900, t->tm_hour, t->tm_min);
}

// 打印欢迎信息
void print_welcome() {
    printf("\n========================================\n");
    printf("       欢迎使用停车场管理系统\n");
    printf("       当前日期：2025年2月27日\n");
    printf("========================================\n");
}

// 打印分割线
void print_divider() {
    printf("\n----------------------------------------\n");
}

// 查询计费标准
void query_fee_rates() {
    if (!logged_in) {
        printf("请先登录！\n");
        return;
    }
    printf("\n========================================\n");
    printf("       停车场计费标准\n");
    printf("========================================\n");
    printf("1. 小车（非VIP）：每小时 10 元\n");
    printf("2. 小车（VIP）：每小时 5 元\n");
    printf("3. 货车（非VIP）：每小时 15 元\n");
    printf("4. 货车（VIP）：每小时 7.5 元\n");
    printf("----------------------------------------\n");
    printf("说明：\n");
    printf("- 计费单位为小时，不足一小时按一小时计算。\n");
    printf("- VIP用户享受50%%折扣。\n");
    printf("- 最终费用将在出库时根据实际停车时长计算。\n");
    printf("========================================\n");
    add_log("查询计费标准");
}

// 保存车辆信息到文件
void save_cars_to_file() {
    FILE* fp = fopen("cars.txt", "w"); // 以写入模式打开文件
    if (fp == NULL) {
        printf("无法打开文件保存车辆信息！\n");
        return;
    }
    for (int i = 0; i < car_count; i++) {
        fprintf(fp, "%s,%d,%d,%d,%s,%s\n",
            cars[i].plate, cars[i].is_vip, cars[i].in_garage,
            cars[i].car_type, cars[i].entry_time, cars[i].exit_time);
    }
    fclose(fp);
    printf("车辆信息已保存到 cars.txt\n");
    add_log("保存车辆信息到文件");
}

// 从文件加载车辆信息
void load_cars_from_file() {
    FILE* fp = fopen("cars.txt", "r"); // 以读取模式打开文件
    if (fp == NULL) {
        printf("无法打开文件加载车辆信息，可能文件不存在。\n");
        return;
    }
    car_count = 0; // 重置车辆数量
    while (fscanf(fp, "%[^,],%d,%d,%d,%[^,],%[^\n]\n",
        cars[car_count].plate, &cars[car_count].is_vip,
        &cars[car_count].in_garage, &cars[car_count].car_type,
        cars[car_count].entry_time, cars[car_count].exit_time) == 6) {
        car_count++;
        if (car_count >= MAX_CARS) {
            printf("车辆数量超过上限，停止加载。\n");
            break;
        }
    }
    fclose(fp);
    printf("已从 cars.txt 加载 %d 条车辆信息\n", car_count);
    add_log("从文件加载车辆信息");
}