#include <QCoreApplication>
#include <QRandomGenerator>
#include <iostream>
#include <QDebug>
#include <QVector>
#include <QPair>
#include <QString>



void generator(QVector<QPair<int,int>> edges)  {
    int n = 10; // Количество вершин в каждой доли

    for (int i = 0; i < n; ++i) {
        // Гарантированно добавляем одно ребро для каждой вершины
        int j = QRandomGenerator::global()->bounded(n);
        edges.append(qMakePair(i, j));

        // Добавляем остальные ребра со случайным шансом
        for (int k = 0; k < n; ++j) {
            if (i != j && QRandomGenerator::global()->generate() % 2) { // Случайно решаем, будет ли ребро между i и j
                edges.append(qMakePair(i, k));
            }
        }
    }
    // Теперь в 'edges' у нас есть список ребер двудольного графа
    for (const auto &edge : edges) {
            qDebug() << "(" << edge.first << "," << edge.second << ")";
        }
 }




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QVector<QPair<int, int>> edges;
    generator(edges);
    return a.exec();
}
