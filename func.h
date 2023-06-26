#include <QDebug>
#include <QRandomGenerator>
#include "SingletonDB.h"
#include "mytcpserver.h"


void auth(MyTcpServer& server, const QString login, const QString pass, const int connection_id){

    QString result = SingletonDB::getInstance()->authUser(login, pass, connection_id);
    if (result  == "auth&error")
    {
        server.server_answer(connection_id, "0", "0");
    }

    else if (result == "auth&stud")
    {
        server.server_answer(connection_id, "1", "0");
        qDebug() << "Welcome Student!";
    }
    else if (result == "auth&teach")
    {
        server.server_answer(connection_id, "2", "0");
        qDebug() << "Welcome Teacher!";
    }

}

void registration(const QString login, const QString name,const QString surname,const QString patronymic, const QString pass, const QString role, int connection_id)
{

    qDebug() << "Inser user result: " << SingletonDB::getInstance()->insertUser(login, name, surname, patronymic, pass, role, connection_id);
    SingletonDB::getInstance()->fetchAllUsers();

    //SingletonDB::getInstance()->fetchAllUsers();

}

void logout(int connection_id)
{
    SingletonDB::getInstance()->logout(connection_id);
}

bool findPerfectMatching(int node, QVector<QPair<int, int>>& edges, QVector<bool>& used) {
    // Если вершина уже использована, возвращаем false
    if (used[node]) return false;
    // Отмечаем вершину как использованную
    used[node] = true;

    // Проходим по всем ребрам
    for (auto edge : edges) {
        // Если текущее ребро не начинается с нашей вершины, переходим к следующему ребру
        if (edge.first != node) continue;
        int to = edge.second; // вершина, с которой мы хотим связать текущую вершину
        // Если вершина 'to' еще не использована или если мы можем найти паросочетание для вершины 'to',
        // то мы нашли паросочетание для текущей вершины
        if (!used[to] || findPerfectMatching(to, edges, used)) {
            return true;
        }
    }

    // Если не удалось найти паросочетание для текущей вершины, возвращаем false
    return false;
}

bool answer_checker(QVector<QPair<int, int>> edges, int x)
{
    for (int i = 1; i <= x; ++i) {
            QVector<bool> used(x, false); // Вектор для отслеживания использованных вершин
            // Если для текущей вершины можно найти паросочетание, выводим сообщение и завершаем программу
            if (findPerfectMatching(i, edges, used)) {
                qDebug() << "Perfect matching found!";
                return false;
            }
    }
    qDebug() << "No perfect matching found.";
    return true;
}

bool check_task1_2_3(const QString task, const QString answer, const QString variant)
{
    if (variant == "task1")
    {
        QString edgesStr = task.mid(1, task.length() - 2);  // Удаляем внешние скобки
        qDebug() << edgesStr << "Без внешних скобок";
        QStringList pairs = edgesStr.split("),(", Qt::SkipEmptyParts);
        qDebug() << pairs << "Только цифры";
        QVector<QPair<int,int>> edges;

        for(const QString& pair : pairs) {
            QStringList parts = pair.split(",");
            edges.append(qMakePair(parts[0].toInt(), parts[1].toInt()));
        }

        QStringList parts = answer.split(",", Qt::SkipEmptyParts);
        QVector<int> SRP;

        for(const QString& part : parts) {
            SRP.append(part.toInt());
        }
        qDebug() << "SRP size: " << SRP.size();

        QSet<int> unique_y;
        QSet<int> unique_x;

        for(const auto& edge : edges) {
            unique_x.insert(edge.first);
            unique_y.insert(edge.second);
        }

        int x = unique_x.size();
        qDebug() << "Size x: "<< x;
        int y = unique_y.size();
        qDebug() << "Size y: "<< y;

        QSet<int> set;
        if (SRP[0] != 0)
        {
            for (const auto& element : SRP) {
                set.insert(element);
            }
            qDebug() << "Set size: " << set.size();
            if (set.size() == SRP.size() && SRP.length() == x)
            {
                for (int i = 0; i < SRP.length(); i++)
                {
                    //qDebug() << "i= " << i+1 << "|" << SRP[i];
                    QPair<int,int> contain = qMakePair(i+1,SRP[i]);
                    qDebug() << contain;
                    qDebug() << edges.contains(contain) << "Contains check";
                    if (!edges.contains(contain))
                    {
                        qDebug() << "Incorrect (Нет такого сочетания)";
                        return false;
                    }
                }
                    qDebug() << "Correct (Все указанные пукнты сработали)";
                    return true;
            }
            else
            {
            qDebug() << "Incorrec (Или есть одинаковые вершины или длинна меньше чем x";
            return false;
            }
        }
        else if (SRP[0] == 0)
        {
            if (y < x)
            {
                qDebug() << "Correct (y < x)";
                return true;
            }
            else //Рекурсия
            {
                if(!answer_checker(edges,x))
                {
                    qDebug() << "Incorrect answer";
                    return false;
                }

                else
                {
                    qDebug() << "Correct answer";
                    return true;
                }
            }
        }
    }
    if (variant == "task3")
    {
        QString edgesStr = task.mid(1, task.length() - 2);  // Удаляем внешние скобки
        qDebug() << edgesStr << "Без внешних скобок";
        QStringList pairs = edgesStr.split("),(", Qt::SkipEmptyParts);
        qDebug() << pairs << "Только цифры";
        QVector<QPair<int,int>> edges;

        for(const QString& pair : pairs) {
            QStringList parts = pair.split(",");
            edges.append(qMakePair(parts[0].toInt(), parts[1].toInt()));
        }

        qDebug() << "edges: " << edges;

        int maxFirst = edges[0].first;
        int maxSecond = edges[0].second;

        for(const auto& edge : edges) { // определения количества вершин в каждой доле
            if(edge.first > maxFirst)
                maxFirst = edge.first;
            if(edge.second > maxSecond)
                maxSecond = edge.second;
        }
        qDebug() << "maxFisrt= " << maxFirst;
        qDebug() << "maxSecond= " << maxSecond;

        QVector <QString> M_Pair = answer.split("|"); // Обработка ответа
        qDebug() << "M_Pair= " << M_Pair;

        if (M_Pair[0].size() != M_Pair[1].size()) // Проверяем, чтобы множества был одинаковы
        {
            qDebug() << "Incorrect: X != Y";
            return false;
        }

        QSet<int> unique_y;
        QSet<int> unique_x;

        for(int i = 0; i < M_Pair.size(); ++i) { // Заполнение set x и set y
            QStringList numbers = M_Pair[i].split(',');

            if(i == 0) {
                for(const auto& number : numbers)
                    unique_x.insert(number.toInt());
            } else if(i == 1) {
                for(const auto& number : numbers)
                    unique_y.insert(number.toInt());
            }
        }
        qDebug() << "unique_x= " << unique_x;
        qDebug() << "unique_y= " << unique_y;

        QStringList numbers1 = M_Pair[0].split(',');
        QStringList numbers2 = M_Pair[1].split(',');

        qDebug() << "numbers1= " << numbers1;
        qDebug() << "numbers2= " << numbers2;

        if (!(unique_x.size() == numbers1.length() && unique_y.size() == numbers2.length())) // Проверка, чтобы уникальных = доли из ответа
        {
            qDebug() << "Incorrect: Есть повторения";
            return false;
        }

        for (int i = 0; i < numbers1.length(); i++)
        {
            QPair<int,int> contain = qMakePair(numbers1[i].toInt(),numbers2[i].toInt());
            qDebug() << contain;
            qDebug() << edges.contains(contain) << "Contains check";
            if (!edges.contains(contain))
            {
                qDebug() << "Incorrect (Нет такого сочетания)";
                return false;
            }
        }

        if (!(maxFirst == numbers1.length() || maxSecond == numbers2.length()))
        {
            QVector<int> x_not_used;
            QVector<int> y_used;
            QVector<int> numbers1Int;
            QVector<int> numbers2Int;

            // Переводим строковые значения из numbers1 в числовые и добавляем их в numbersInt
            for(const auto& number : numbers1)
                numbers1Int.append(number.toInt());
            for(const auto& number : numbers2)
                numbers2Int.append(number.toInt());

            // Проверяем, какие значения x не использованы
            for(int i = 1; i <= maxFirst; i++)
                if(!numbers1Int.contains(i))
                    x_not_used.append(i);
            qDebug() << "x_not_used: " << x_not_used;

            // Находим все использованные пользователем значения y
            for(const auto& edge : edges)
                if(numbers1Int.contains(edge.first) && numbers2Int.contains(edge.second))
                    y_used.append(edge.second);
            qDebug() << "y_used: " << y_used;

            // Проверяем, есть ли пары (x, y), где x из x_not_used и y не в y_used
            for(const auto& x : x_not_used)
                for(const auto& edge : edges)
                    if(edge.first == x && !y_used.contains(edge.second))
                    {
                        qDebug() << "Есть неспользованная пара x и y";
                        qDebug() << edge.first << "|" << edge.second;
                        return false;
                    }
            qDebug() << "Correct: Нет максимальных долей и ответ верный";
            return true;
        }
        else
        {
            qDebug() << "Correct: Есть максимальная доля";
            return true;
        }

    }
    if (variant == "task2")
    {
        QVector<int> dolys; // Вектор(int) для того чтобы записать туда ответ пользователя

        QStringList list = answer.split(','); // Записываем в list ответ пользователя

        for (QString s : list) {
            dolys.append(s.toInt());
        } // То что мы получили в list пихаем в dolys

        bool flag = true; // Для того чтобы понимать граф двудольный или нет
        QSet<int> redVertices; // Множество для вершин красного цвета
        QSet<int> greenVertices; // Множество для вершин зеленого цвета

        QString edgesStr = task.mid(1, task.length() - 2);  // Удаляем внешние скобки
        qDebug() << edgesStr << "Без внешних скобок";
        QStringList pairs = edgesStr.split("),(", Qt::SkipEmptyParts);
        qDebug() << pairs << "Только цифры";
        QVector<QPair<int,int>> edges;

        for(const QString &pair : pairs) {
            QStringList vertices = pair.split(",");
            edges.append(QPair<int, int>(vertices[0].toInt(), vertices[1].toInt()));
        }

        // Сортировка ребер по первому элементу
        std::sort(edges.begin(), edges.end());

        qDebug() << edges;

        for (auto edge : edges) {
            int first = edge.first;
            int second = edge.second;

            // Если встречается новая вершина, раскрасим ее в противоположный цвет, если она соединена с уже раскрашенной вершиной
            if (redVertices.contains(first) && !greenVertices.contains(second) && !redVertices.contains(second)) {
                greenVertices.insert(second);
                qDebug() << second << "Green";
            }
            else if(!greenVertices.contains(first) && !redVertices.contains(first) && redVertices.contains(second)) {
                greenVertices.insert(first);
                qDebug() << first << "Green";
            }
            else if (!redVertices.contains(first) && !greenVertices.contains(first) && greenVertices.contains(second)) {
                redVertices.insert(first);
                qDebug() << first << "Red";
            }
            else if (greenVertices.contains(first) && !redVertices.contains(second) && !greenVertices.contains(second)) {
                redVertices.insert(second);
                qDebug() << second << "Red";
            }
            else if ((!redVertices.contains(first) && !greenVertices.contains(second)) && (!redVertices.contains(second) && !greenVertices.contains(first))) {
                // Если обе вершины новые, окрасим первую вершину в красный
                redVertices.insert(first);
                greenVertices.insert(second);
                qDebug() << first << "Red";
                qDebug() << second << "Green";
            } else if ((redVertices.contains(first) == redVertices.contains(second)) || (greenVertices.contains(second) == greenVertices.contains(first))) {
                // Если обе вершины окрашены в одинаковый цвет, это не двудольный граф
                qDebug() << "Not a bipartite graph: (" << first << "," << second << ")";
                flag = false;
                break;
            }
        }

        QVector<int> redVector = QVector<int>::fromList(redVertices.values());
        QVector<int> greenVector = QVector<int>::fromList(greenVertices.values());
        std::sort(redVector.begin(), redVector.end());
        std::sort(greenVector.begin(), greenVector.end());
        std::sort(dolys.begin(), dolys.end());
        qDebug() << redVector << " -RedVectror";
        qDebug() << greenVector << " -GreenVectror";
        qDebug() << dolys << " -answer";

        if (answer == "0" && !flag)
        {
            return true;
        }
        else if (answer != "0" && !flag)
        {
            return false;
        }
        else if (answer != "0" && ((redVector == dolys) || (greenVector == dolys)))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (variant == "task4")
    {
        return true;
    }
}

QVector<QPair<int,int>> generator1_2_3(QString task_number)
{
    QVector<QPair<int, int>> edges;
    if (task_number == "1" || task_number == "3")
    {
        int x = QRandomGenerator::global()->bounded(3, 9); // Случайное количество вершин в 1 доли от 3 до 8
        int y = QRandomGenerator::global()->bounded(3, 9); // Случайное количество вершин во 2 доли от 3 до 8
        QVector<bool> used(y, false); // Вектор для отслеживания использованных вершин во второй доле
        qDebug() << x << "|" << y;

        for (int i = 0; i < x; ++i) {
            // Гарантированно добавляем одно ребро для каждой вершины
            int j = QRandomGenerator::global()->bounded(y);
            edges.append(qMakePair(i+1, j+1));
            used[j] = true;

            // Добавляем остальные ребра со случайным шансом
            for (int k = 0; k < y; ++k) {
                if (k != j && QRandomGenerator::global()->bounded(4) == 0) { // Случайно решаем, будет ли ребро между i и j
                    edges.append(qMakePair(i+1, k+1));
                    used[k] = true;
                }
            }
        }
        // Добавляем ребра для неиспользованных вершин во второй доле
            for (int j = 0; j < y; ++j) {
                if (!used[j]) {
                    int i = QRandomGenerator::global()->bounded(x);
                    edges.append(qMakePair(i+1, j+1));
                }
            }
        return edges;
    }
    if (task_number == "2")
    {
        int minVertices = 4;
        int maxVertices = 7;
        int numVertices = QRandomGenerator::global()->bounded(maxVertices - minVertices + 1) + minVertices; // Генерация случайного количества вершин

        QVector<QPair<int, int>> edges; // Вектор для хранения пар вершин

        qDebug() << "Graf s  " << numVertices << " vershinami:\n";

        // Создание вектора вершин
        QVector<int> vertices;
        for (int i = 1; i <= numVertices; ++i) {
            vertices.push_back(i);
        }

        // Перемешивание вектора вершин (алгоритм Фишера-Йетса)
        for (int i = vertices.size() - 1; i > 0; --i) {
            int j = QRandomGenerator::global()->bounded(i + 1); // Генерация случайного индекса
            vertices.swapItemsAt(i, j); // Меняем местами элементы
        }

        // Создание ребер, соединяющих каждую вершину с следующей
        for (int i = 0; i < numVertices - 1; ++i) {
            QPair<int, int> newEdge = qMakePair(vertices[i], vertices[i+1]);
            if (!edges.contains(newEdge)) {
                edges.push_back(newEdge);
            }
        }

        // Создание дополнительных ребер
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 2; j < numVertices; ++j) {
                if (QRandomGenerator::global()->bounded(3) == 0) {
                    QPair<int, int> newEdge = qMakePair(vertices[i], vertices[j]);
                    if (!edges.contains(newEdge) && !edges.contains(qMakePair(vertices[j], vertices[i]))) {
                        edges.push_back(newEdge);
                    }
                }
            }
        }

        return edges;
    }
}

void Parsing(int connection_id, QString message,MyTcpServer& server){
    QList<QString> parts = message.split('&');
    qDebug() << parts[0];
    if(parts[0] == "auth"){
        if (parts.length() != 3){
            qDebug() << "error";
        }
        else{
        QString login = parts[1];
        QString pass = parts[2];
        auth(server, login, pass, connection_id);
        }
    }
    else if(parts[0] == "register"){
        if (parts.length() != 7)
        {
            qDebug() << "error";
        }
        else
        {
        QString login = parts[1];
        QString name = parts[2];
        QString surname = parts[3];
        QString patromynic = parts[4];
        QString pass = parts[5];
        QString role = parts[6];
        registration(login, name, surname, patromynic, pass, role, connection_id);
        }
    }

    else if(parts[0] == "mystat"){
        QString results = SingletonDB::getInstance()->stat(connection_id);
        server.server_answer(connection_id, results, "0");
    }
    else if(parts[0] == "stat"){
        QString results = SingletonDB::getInstance()->stat();
        server.server_answer(connection_id, results, "1");
    }
    else if(parts[0] == "check_answer"){
        bool flag;
        QString task = parts[1];
        QString answer = parts[2];
        QString variant;
        if (parts[3].contains("1:"))
            variant = "task1";
        else if (parts[3].contains("2:"))
            variant = "task2";
        else if (parts[3].contains("3:"))
            variant = "task3";
        else if (parts[3].contains("4:"))
            variant = "task4";

        flag = check_task1_2_3(task, answer, variant);

        if (flag == true)
        {
            SingletonDB::getInstance()->task_result(connection_id, variant, true);
        }
        else if (flag == false)
        {
            SingletonDB::getInstance()->task_result(connection_id, variant, false);
        }

    }
    else if(parts[0] == "generator")
    {
        if (parts[1] == "1" || parts[1] == "3" || parts[1] == "2")
        {
            QVector<QPair<int,int>> edges = generator1_2_3(parts[1]);
            QStringList edgeList;
            for(const auto& edge : edges)
                edgeList << QString("(%1,%2)").arg(edge.first).arg(edge.second);
            QString edgeStr = edgeList.join(",");
            qDebug() << edgeStr;
            edgeStr = "task&" + parts[1] + "&" + edgeStr;
            server.server_answer(connection_id, edgeStr, "2");
        }
        else if(parts[1] == "4")
        {
            QString edgeStr;
            edgeStr = "task&" + parts[1] + "&Coming_Soon";
            server.server_answer(connection_id, edgeStr, "2");
        }

    }
    else if(parts[0] == "Filter_1")
    {
        QString results = SingletonDB::getInstance()->Filter_1();
        server.server_answer(connection_id, results, "1");
    }

}
