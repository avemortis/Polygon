#include <iostream>
#include <cmath>
#include <queue>
#include <string>
#include <fstream>
#include <conio.h>

using namespace std;

class Polygon {
private:
    int ac = 0; //Количество углов
    int** points; //Координаты точек
public:

    Polygon(int angles) {
        int** temp = new int* [2];
        for (int i = 0; i < angles; i++) {
            temp[i] = new int[2];
        }
        ac = angles;
        points = temp;
    }

    void setPoints(int** pointsToSet) {
        points = pointsToSet;
    }

    void getPoints() {
        for (int i = 0; i < ac; i++) {
            for (int j = 0; j < 2; j++) {
                cout << points[i][j] << " ";
            }
            cout << endl;
        }
    }
     
    double getArea() {
        double sum1 = 0, sum2 = 0;
        for (int i = 0; i < ac - 1; i++) {
            sum1 = sum1 + (points[i][0] * points[i + 1][1]);
            sum2 = sum2 + (points[i][1] * points[i + 1][0]);
        }
        return (abs(sum1 - sum2)/2);
    }

    string getName() {
        switch (ac)
        {
        case (3):
            return "Треугольник";
            break;
        case (4):
            return "Четырехугольник";
            break;
        case (5):
            return "Пятиугольник";
            break;
        case (6):
            return "Шестиугольник";
            break;
        default:
            break;
        }
        return " " + to_string(ac) + "-угольник";
    }
};

void readPolygonsFromFileAndSetIntoQueue(queue<Polygon>& myQueue, string filename) {
    int angles = 0;
    int** points = new int* [2];

    ifstream file(filename);

    if (file.is_open()) {

        while (file >> angles) {

             int** points = new int* [2];

             for (int i = 0; i < angles; i++) {
                 points[i] = new int[2];
             }

             for (int i = 0; i < angles; i++) {
                 for (int j = 0; j < 2; j++) {
                     file >> points[i][j];
                 }
             }
             
             Polygon newPolygon(angles);
             newPolygon.setPoints(points);
             myQueue.push(newPolygon);
        }
    }
    else {
        cout << "Не удалось открыть указанный файл" << endl;
    }
    file.close();
}

void showQueue(queue<Polygon>& myQueue) {
    queue <Polygon> temp = myQueue;
    cout << "В очереди находятся " << temp.size() << " фигур: " << endl;
    while (temp.size() != 0) {
        Polygon poly = temp.front();
        cout << poly.getName() << " с площадью: " << poly.getArea() << endl;
        temp.pop();
    }
}

void showUI() {
    system("cls");
    cout << "Нажмите 1 чтобы показать очередь" << endl;
    cout << "Нажмите 2 чтобы считать фигуры из файла по-умолчанию" << endl;
    cout << "Нажмите 3 чтобы считать фигуры из другого файла" << endl;
    cout << "Нажмите 4 чтобы завершить работу с программой" << endl;
}

bool switcher(queue<Polygon>& myQueue, int key) {
    string filename;
    switch (key)
    {
    case (1):
        showQueue(myQueue);
        system("pause");
        break;
    case (2):
        readPolygonsFromFileAndSetIntoQueue(myQueue, "test.txt");
        system("pause");
        break;
    case (3):
        cout << endl << "Введите имя файла: ";
        cin >> filename;
        readPolygonsFromFileAndSetIntoQueue(myQueue, filename);
        system("pause");
        break;
    default:
        break;
    }

    return true;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    queue <Polygon> Polygons;
    int key = 0;
    while (key != 4) {
        showUI();
        cin >> key;
        switcher(Polygons, key);
    }
    
    return 0;
}

