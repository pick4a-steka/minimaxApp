#include "mainApplication.h"

mainApplication::mainApplication(TreeNode *root, QGraphicsScene *scene, bool isLtoR, \
                             bool max_or_min, bool isA_B, bool isTreeGen, int depth, int branching, int timer, QObject *parent)
        : QObject(parent), root(root), scene(scene), isLeftToRight(isLtoR), isMax(max_or_min), \
        isAlphaBeta(isA_B), depth(depth), branching(branching), timer(timer) {
        unsigned int index = 0;

        isTreeGeneration = isTreeGen;

        if (!isTreeGeneration) {
            v_leaves = {4, 6, 3, 5, 1, 8, 0, 3, 6, 1, 3, 2, 1, 2, 1, 2, 0, 0, 1, -1, 0, -2, -1, -2, 3, 2, 2, 4, 3, 6, 7, 8, 5, 1, 8, 3};
            numChildren = {3, 2, 3, 2, 0, 0, 2, 0, 0, 3, 0, 0, 0, 3, 2, 0, 0, 3, 0, 0, 0, 2, 0, 0, 3, 1, 3, 0, 0, 0, 3,
                           2, 0, 0, 2, 0, 0, 3, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 2, 2, 2, 0, 0, 3, 0, 0, 0, 1, 3, 0, 0, 0};
            depth = 4;
        }
        else {
            generationLeaves(depth, branching);
        }

        for (unsigned int i = 0; i < v_leaves.size(); ++i) {
            leaves.push(v_leaves[i]);
        }

        minimax = new Minimax(root, leaves, numChildren, index, isLeftToRight, isMax, isAlphaBeta, isTreeGeneration, depth, branching, timer);
        visualizer = new Visualizer(root, scene, scene->width(), isMax, depth);
        if (!minimax || !visualizer) {
            qDebug() << "Ошибка: не удалось инициализировать minimax или visualizer";
            return;
        }
        thread = new QThread(this);

        minimax->moveToThread(thread);

        connect(thread, &QThread::started, minimax, &Minimax::runMinimax);
        connect(minimax, &Minimax::highlightPath, visualizer, &Visualizer::highlightPath);
        connect(minimax, &Minimax::resetHighlight, visualizer, &Visualizer::resetHighlight);
        connect(minimax, &Minimax::highlightPrunedSubtree, visualizer, &Visualizer::highligthPrunedSubtree);
        connect(minimax, &Minimax::minimaxFinished, this, &mainApplication::startProcessController);
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(thread, &QThread::finished, minimax, &QObject::deleteLater);
}

mainApplication::~mainApplication() {
    qDebug() << "mainApplication удален";
    delete visualizer;
}

void mainApplication::startMinimax() {
    qDebug() << "Запуск потока";
    thread->start();
}

void mainApplication::startProcessController() {
    qDebug() << "зашли в startProcessController";
    if (!window_process_controller) {
        qDebug() << "зашли в IF startProcessController";
        window_process_controller = new windowProcessController(200, 300);
        connect(window_process_controller->get_btnQuit(), &QPushButton::clicked, this, &mainApplication::onQuitButtonClicked, Qt::QueuedConnection);
        connect(window_process_controller->get_btnQuit(), &QPushButton::clicked, thread, &QThread::quit, Qt::QueuedConnection); // Qt::QueuedConnection для связи между потоками
        connect(window_process_controller->get_btnRestart(), &QPushButton::clicked, this, &mainApplication::restartMinimax, Qt::QueuedConnection);
        connect(window_process_controller->get_btnRestart(), &QPushButton::clicked, this, &mainApplication::onRestartButtonClicked, Qt::QueuedConnection);
        window_process_controller->show();
        qDebug() << "window_process_controller создан и показан";
    }
}

void mainApplication::onQuitButtonClicked() {
    qDebug() << "Кнопка 'Завершить' нажата. Завершаем поток.";

    // Завершаем поток, вызываем quit и ждем его завершения
    thread->quit();
    thread->wait();  // Ожидаем завершения потока перед удалением
    qDebug() << "Поток завершен";

    // Закрываем окно и удаляем его
    deleteController();
    emit endSignal();
}

void mainApplication::onRestartButtonClicked() {
    deleteController();
}

void mainApplication::restartMinimax() {
    qDebug() << "restartMinimax";

    for (unsigned int i = 0; i < v_leaves.size(); ++i) {
        leaves.push(v_leaves[i]);
    }

    // Удаление старого объекта minimax
    if (minimax) {
        minimax->deleteLater();
        minimax = nullptr;
    }

    delete root;
    root = new TreeNode();

    if (!isTreeGeneration) {
        depth = 4;
    }

    // Создание нового объекта minimax
    unsigned int index = 0;
    minimax = new Minimax(root, leaves, numChildren, index, isLeftToRight, isMax, isAlphaBeta, isTreeGeneration, depth, branching, timer);

    // Удаление старого объекта visualizer
    delete visualizer;
    visualizer = new Visualizer(root, scene, scene->width(), isMax, depth);

    // Удаление и пересоздание потока
    if (thread) {
        thread->quit();
        thread->wait();
        thread->deleteLater();
    }

    thread = new QThread(this);
    minimax->moveToThread(thread);

    // Повторное подключение сигналов и слотов
    connect(thread, &QThread::started, minimax, &Minimax::runMinimax);
    connect(minimax, &Minimax::highlightPath, visualizer, &Visualizer::highlightPath);
    connect(minimax, &Minimax::resetHighlight, visualizer, &Visualizer::resetHighlight);
    connect(minimax, &Minimax::highlightPrunedSubtree, visualizer, &Visualizer::highligthPrunedSubtree);
    connect(minimax, &Minimax::minimaxFinished, this, &mainApplication::startProcessController);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    // Запуск нового потока
    thread->start();
}

void mainApplication::deleteController() {
    if (window_process_controller) {
        window_process_controller->close();
        delete window_process_controller;
        window_process_controller = nullptr;
        qDebug() << "window_process_controller удален";
    }
}

void mainApplication::generationLeaves(int depth, int branching) {
    int countChildren = depth * branching;

        std::random_device rnd_device;

    std::mt19937 mersenne_engine { rnd_device() };
    std::uniform_int_distribution<int> dist {-10, 10};

    v_leaves.resize(countChildren);
    std::generate(v_leaves.begin(), v_leaves.end(), [&](){
        return dist(mersenne_engine);
    });
}
