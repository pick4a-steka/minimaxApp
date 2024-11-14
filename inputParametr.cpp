#include <inputParametr.h>

inputParametr_window::inputParametr_window(int w, int h, QWidget *parent) : QWidget(parent) {
    QCheckBox *leftToRigth_checkbox = new QCheckBox(this);
    QCheckBox *maxOrMin_checkbox = new QCheckBox(this);
    QCheckBox *AlphaBeta_checkbox = new QCheckBox(this);
    QCheckBox *TreeGeneration_checkbox = new QCheckBox(this);

    QSpinBox *Depth_spinbox = new QSpinBox(this);
    QSpinBox *Branching_spinbox = new QSpinBox(this);
    QSpinBox *Timer_spinbox = new QSpinBox(this);

    QFormLayout *layout_depth = new QFormLayout();
    QFormLayout *layout_branching = new QFormLayout();
    QFormLayout *layout_timer = new QFormLayout();

    QPushButton *btn_start = new QPushButton(this);

    depth = 1;
    branching = 2;
    timer = 1000;
    isLeftToRight = false;
    isMax = false;
    isAlphaBeta = false;
    isTreeGeneration = false;

    resize(w, h);
    setWindowTitle("Вводные для алгоритма");
    Timer_spinbox->setRange(500, 3000); // диапазон значений для Таймера
    Timer_spinbox->setValue(timer);
    Depth_spinbox->setRange(1, 6);
    Branching_spinbox->setRange(2, 4);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    leftToRigth_checkbox->setText(QString("Слева-направо"));
    maxOrMin_checkbox->setText(QString("MAX"));
    AlphaBeta_checkbox->setText(QString("Альфа-бета отсечение"));
    TreeGeneration_checkbox->setText(QString("Авто-генерация дерева"));

    layout_depth->addRow("Глубина: ", Depth_spinbox);
    layout_branching->addRow("Ветвление: ", Branching_spinbox);
    layout_timer->addRow("мс/узел: ", Timer_spinbox);

    btn_start->setText("Начать");

    mainLayout->addWidget(leftToRigth_checkbox);
    mainLayout->addWidget(maxOrMin_checkbox);
    mainLayout->addWidget(AlphaBeta_checkbox);
    mainLayout->addWidget(TreeGeneration_checkbox);
    mainLayout->addLayout(layout_depth);
    mainLayout->addLayout(layout_branching);
    mainLayout->addLayout(layout_timer);
    mainLayout->addWidget(btn_start);

    connect(leftToRigth_checkbox, &QCheckBox::stateChanged, this, [this](int state) {
        isLeftToRight = (state == Qt::Checked);
        qDebug() << "Слева-направо: " << isLeftToRight;
    });
    connect(maxOrMin_checkbox, &QCheckBox::stateChanged, this, [this](int state) {
        isMax = (state == Qt::Checked);
        qDebug() << "Игрок MAX: " << isMax;
    });
    connect(AlphaBeta_checkbox, &QCheckBox::stateChanged, this, [this](int state) {
        isAlphaBeta = (state == Qt::Checked);
        qDebug() << "Альфа-Бета отсечение: " << isAlphaBeta;
    });
    connect(TreeGeneration_checkbox, &QCheckBox::stateChanged, this, [this](int state) {
        isTreeGeneration = (state == Qt::Checked);
        qDebug() << "Авто-генерация отсечения: " << isTreeGeneration;
    });
    connect(Depth_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
        depth = value;
        qDebug() << "Глубина: " << depth;
    });
    connect(Branching_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
        branching = value;
        qDebug() << "Ветвление: " << branching;
    });
    connect(Timer_spinbox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
        if (value >= 500 && value <= 3000) {
            timer = value;
        }
        qDebug() << "мс/узел: " << timer;
    });

    connect(btn_start, &QPushButton::clicked, this, &inputParametr_window::closeParametrWindow);
}

inputParametr_window::~inputParametr_window() {

}

void inputParametr_window::closeParametrWindow() {
    close();
    emit getParameters();
}
