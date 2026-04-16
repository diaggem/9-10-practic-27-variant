#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;

const int N = 20;

struct ocean {
    char name[25];
};

enum type { razlom, hrebet, zhelob };

struct vpad {
    char name[25];
    int depth;
    ocean o;
    type t;
    int num;
};

const char* tip(type t) {
    if (t == razlom) return "Разломная";
    if (t == hrebet) return "Хребет";
    return "Желоб";
}

vpad* init() {
    vpad* vpads = new vpad[N];

    vpads[0] = { "Марианская", 11034, {"Тихий"}, zhelob, 0 };
    vpads[1] = { "Тонга", 10882, {"Тихий"}, zhelob, 0 };
    vpads[2] = { "Филиппинская", 10540, {"Тихий"}, zhelob, 0 };
    vpads[3] = { "Кермадек", 10047, {"Тихий"}, zhelob, 0 };
    vpads[4] = { "Идзу-Бонин", 9810, {"Тихий"}, zhelob, 0 };
    vpads[5] = { "Курило-Камчатская", 9604, {"Тихий"}, zhelob, 0 };
    vpads[6] = { "Пуэрто-Рико", 8648, {"Атлантический"}, zhelob, 0 };
    vpads[7] = { "Южно-Сандвичева", 8428, {"Атлантический"}, zhelob, 0 };
    vpads[8] = { "Перуанско-Чилийская", 8065, {"Тихий"}, zhelob, 0 };
    vpads[9] = { "Алеутская", 7679, {"Тихий"}, zhelob, 0 };
    vpads[10] = { "Яванская", 7729, {"Индийский"}, zhelob, 0 };
    vpads[11] = { "Романш", 7760, {"Атлантический"}, razlom, 0 };
    vpads[12] = { "Среднеокеанский хребет", 4500, {"Атлантический"}, hrebet, 0 };
    vpads[13] = { "Челенджер", 10920, {"Тихий"}, zhelob, 0 };
    vpads[14] = { "Гавайский хребет", 5200, {"Тихий"}, hrebet, 0 };
    vpads[15] = { "Красное море разлом", 3040, {"Индийский"}, razlom, 0 };
    vpads[16] = { "Лорд-Хау", 9500, {"Тихий"}, zhelob, 0 };
    vpads[17] = { "Балтимор", 4400, {"Атлантический"}, hrebet, 0 };
    vpads[18] = { "Африканский разлом", 3800, {"Индийский"}, razlom, 0 };
    vpads[19] = { "Зондский желоб", 7729, {"Индийский"}, zhelob, 0 };

    return vpads;
}

int deep(vpad* a, int n) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].depth > 6000) cnt++;
    }

    return cnt;
}

int filt(vpad* a, int n, vpad* zhel) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].t == zhelob) zhel[cnt++] = a[i];
    }
    return cnt;
}

void sort(vpad* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j].depth < a[j + 1].depth) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void top3(vpad* a, int n) {
    cout << "\nОкеаны трех глубочайших:\n";
    for (int i = 0; i < 3 && i < n; i++) {
        cout << i + 1 << ". " << a[i].name << " - " << a[i].o.name << endl;
    }
}

bool change(vpad* a, int n, int d, const char* nm, const char* oc, type tp) {
    for (int i = 0; i < n; i++) {
        if (a[i].depth == d) {
            strcpy_s(a[i].name, nm);
            strcpy_s(a[i].o.name, oc);
            a[i].t = tp;
            return true;
        }
    }
    return false;
}

int filter(vpad* a, int n, vpad* nw, const char* oc) {
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (!strcmp(a[i].o.name, oc)) {
            nw[j++] = a[i];
        }
    }
    return j;
}

void readnum(vpad* arr, int n, const char* filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Не удалось открыть файл " << filename << endl;
        return;
    }
    char name[25];
    int value;
    while (fin >> name >> value) {
        for (int i = 0; i < n; i++) {
            if (strcmp(arr[i].name, name) == 0) {
                arr[i].num = value;
                cout << "Установлено: " << name << " -> num = " << value << endl;
                break;
            }
        }
    }
    fin.close();
}


void savebin(vpad* arr, int n, const char* filename) {
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) return;
    fout.write((char*)arr, sizeof(vpad) * n);
    fout.close();
}


vpad* loadbin(int& n, const char* filename) {
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) return nullptr;
    fin.seekg(0, ios::end);
    long size = fin.tellg();
    fin.seekg(0, ios::beg);
    n = size / sizeof(vpad);
    vpad* arr = new vpad[n];
    fin.read((char*)arr, size);
    fin.close();
    return arr;
}

void print(vpad* a, int n, const char* msg) {
    cout << endl << msg << endl;
    if (n == 0) { cout << "Нет данных" << endl; return; }
    for (int i = 0; i < n; i++) {
        cout << a[i].name << ", глуб.=" << a[i].depth
            << ", океан=" << a[i].o.name
            << ", тип=" << tip(a[i].t)
            << ", num=" << a[i].num << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    vpad* all = init();

    cout << "\n=== ЗАДАНИЕ 10 ===\n";

    cout << "Чтение data.txt..." << endl;
    readnum(all, N, "data.txt");

    cout << "Сохранение в vpad.bin..." << endl;
    savebin(all, N, "vpad.bin");

    cout << "Чтение из vpad.bin..." << endl;
    int loadedN = 0;
    vpad* loaded = loadbin(loadedN, "vpad.bin");
    if (loaded) {
        cout << "Загружено " << loadedN << " записей\n";
        print(loaded, loadedN, "СОДЕРЖИМОЕ БИНАРНОГО ФАЙЛА");
        delete[] loaded;
    }
    else {
        cout << "ОШИБКА: не удалось прочитать vpad.bin" << endl;
    }

    cout << "\n=== ЗАДАНИЕ 9 ===\n";

    vpad* allsort = init();

    cout << "Количество впадин глубиной >6000: " << deep(all, N) << endl;

    vpad* zheloby = new vpad[N];
    int cnt = filt(all, N, zheloby);
    sort(zheloby, cnt);
    sort(allsort, N);

    print(zheloby, cnt, "Все желобные впадины (по убыванию глубины)");
    top3(allsort, N);

    change(all, N, 8428, "НОВОЕ ИМЯ", "НОВЫЙ ОКЕАН", razlom);

    int oc_num;
    cout << "\nВыберите океан:\n1 - Тихий\n2 - Атлантический\n3 - Индийский\n";
    cin >> oc_num;

    const char* oc = "";
    if (oc_num == 1) oc = "Тихий";
    else if (oc_num == 2) oc = "Атлантический";
    else oc = "Индийский";

    vpad* result = new vpad[N];
    int rc = filter(all, N, result, oc);
    print(result, rc, "Результат фильтрации по океану");

    delete[] all;
    delete[] allsort;
    delete[] zheloby;
    delete[] result;

    system("pause");

    return 0;
}
