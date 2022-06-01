#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    c_fraktS = new QCheckBox("S - уязвимые");
    c_fraktE = new QCheckBox("E - латентное заражение");
    c_fraktI = new QCheckBox("I - инфицированные");
    c_fraktM = new QCheckBox("М - иммунизированные");
    c_fraktD = new QCheckBox("D - инфекция обнаружена");
    c_fraktR = new QCheckBox("R - блокированные");

    c_fraktS->setChecked(true);
    c_fraktI->setChecked(true);

    rb_randscan = new QRadioButton("Случайное");
    rb_topscan = new QRadioButton("Топологическое");
    rb_topscan->setChecked(true);

    gb_fraktal = new QGroupBox("Микрофрактал", this);
    gb_fraktal->setVisible(false);
    gb_scantype = new QGroupBox("Тип сканирования", this);
    gb_scantype->setVisible(false);

    lbl_matfrakt = new QLabel("Матрица переходов");
    lbl_network = new QLabel("Начальные параметры");

    pb_plot = new QPushButton("Рассчитать");
    pb_plot->setFixedWidth(150);
    pb_clear = new QPushButton("Очистить");
    pb_clear->setFixedWidth(150);
    pb_load  = new QPushButton("Загрузить сеть");
    pb_load->setFixedWidth(150);

    table_fraktal = new QTableView(this);
    mdl_fraktal = new QStandardItemModel(6, 6);
    table_fraktal->setModel(mdl_fraktal);
    createTableFraktal();

    table_network = new QTableView(this);
    mdl_network = new QStandardItemModel();
    table_network->setModel(mdl_network);
    createTableNetwork();

    plot = new QwtPlot(this);
    plot->setAxisScale( QwtPlot::yLeft, 0.0, 100.00 );
    plot->setAxisScale( QwtPlot::xBottom, 0.0, 100.00 );
    plot->setTitle("График распространения эпидемии");
    plot->setAxisTitle(QwtPlot::yLeft,QString::fromUtf8("Количество зараженных I(t)"));
    plot->setAxisTitle(QwtPlot::xBottom,QString::fromUtf8("Шаг моделирования t"));
    plot->setCanvasBackground( Qt::white );

    // клавиша, активирующая приближение/удаление
    //    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(plot->canvas());
    //    magnifier->setMouseButton(Qt::MidButton);

    grid = new QwtPlotGrid();
    grid->attach(plot);

    QGridLayout* gl1 = new QGridLayout;
    gl1->addWidget(c_fraktS, 0, 0);
    gl1->addWidget(c_fraktM, 0, 1);
    gl1->addWidget(c_fraktI, 1, 0);
    gl1->addWidget(c_fraktD, 1, 1);
    gl1->addWidget(c_fraktE, 2, 0);
    gl1->addWidget(c_fraktR, 2, 1);
    gb_fraktal->setLayout(gl1);

    QVBoxLayout* vl1 = new QVBoxLayout;
    vl1->addWidget(rb_randscan);
    vl1->addWidget(rb_topscan);
    vl1->addStretch(1);
    gb_scantype->setLayout(vl1);

    QHBoxLayout* hl1 = new QHBoxLayout;
    hl1->addWidget(gb_fraktal);
    hl1->addWidget(gb_scantype);

    QHBoxLayout* hl2 = new QHBoxLayout;
    hl2->addWidget(lbl_matfrakt);
    hl2->addStretch(1);

    QVBoxLayout* vl2 = new QVBoxLayout;
    vl2->addLayout(hl2);
    vl2->addWidget(table_fraktal);

    QHBoxLayout* hl5 = new QHBoxLayout;
    hl5->addWidget(lbl_network);
    hl5->addStretch(1);

    QVBoxLayout* vl4 = new QVBoxLayout;
    vl4->addLayout(hl5);
    vl4->addWidget(table_network);

    QHBoxLayout* hl3 = new QHBoxLayout;
    hl3->addWidget(pb_load);
    hl3->addStretch(1);
    //hl3->addWidget(pb_plot);
    //hl3->addWidget(pb_clear);

    //Панель Расчета
    QHBoxLayout* hl_raschet = new QHBoxLayout;
    QLabel* lbl_step=new QLabel("Шаг 100");
    hl_raschet->addWidget(pb_plot);
    hl_raschet->addWidget(lbl_step);

    QHBoxLayout* hl_clear = new QHBoxLayout;
    hl_clear->addWidget(pb_clear);
    hl_clear->addStretch(1);

    QVBoxLayout* vbl_raschet=new QVBoxLayout;
    vbl_raschet->addLayout(hl_raschet);
   // vbl_raschet->addWidget(pb_clear);


    //панель Способ моделирования
    QGroupBox* gbx_WayModeling=new QGroupBox("Способ моделирования");
    QRadioButton* rb_manually=new QRadioButton("Вручную");
    QRadioButton* rb_automat=new QRadioButton("Автоматически");
    rb_automat->setChecked(true);

    QVBoxLayout* vblw=new QVBoxLayout;
    vblw->addWidget(rb_manually);
    vblw->addWidget(rb_automat);
    gbx_WayModeling->setLayout(vblw);

    //панель настройки
    QGroupBox* gbx_Settings=new QGroupBox("Настройки");
    QLabel* lbl_CountStep=new QLabel("Количество шагов моделирования");
    QLabel* lbl_SizeGrafik=new QLabel("Размерность графика");
    QLineEdit* lned_CountStep=new QLineEdit("100");
    QLineEdit* lned_SizeGrafik=new QLineEdit("100");
    QLineEdit* lned_SizeGrafik1=new QLineEdit("100");

    QHBoxLayout* hls1= new QHBoxLayout;
    hls1->addWidget(lbl_CountStep);
    hls1->addWidget(lned_CountStep);

    QHBoxLayout* hls2= new QHBoxLayout;
    hls2->addWidget(lbl_SizeGrafik);
    hls2->addWidget(lned_SizeGrafik);
    hls2->addWidget(lned_SizeGrafik1);

    QVBoxLayout* vbls=new QVBoxLayout;
    vbls->addLayout(hls1);
    vbls->addLayout(hls2);

    gbx_Settings->setLayout(vbls);

    QVBoxLayout* vl3 = new QVBoxLayout;
    vl3->addLayout(hl1);
    vl3->addLayout(vl2);
    vl3->addLayout(vl4);
    vl3->addLayout(hl3);
    vl3->addWidget(gbx_WayModeling);
    vl3->addWidget(gbx_Settings);
    vl3->addLayout(vbl_raschet);
    vl3->addLayout(hl_clear);
    vl3->addStretch(1);
    vl3->setStretchFactor(vl2, 1);
    vl3->setStretchFactor(vl4, 1);

    QHBoxLayout* hl4 = new QHBoxLayout;
    hl4->addLayout(vl3);
    hl4->addWidget(plot);
    hl4->setStretchFactor(vl3, 2);
    hl4->setStretchFactor(plot, 5);

    this->setLayout(hl4);
    this->cur_color = 0;

    this->setFont(QFont("Times",14));

    connect (pb_load, SIGNAL(clicked()), SLOT(loadNetwork()));
    connect (pb_plot, SIGNAL(clicked()), SLOT(onPlotClicked()));
}

void Widget::createTableFraktal() {

    mdl_fraktal->setHeaderData(0, Qt::Horizontal, "S");
    mdl_fraktal->setHeaderData(1, Qt::Horizontal, "I");
    mdl_fraktal->setHeaderData(2, Qt::Horizontal, "E");
    mdl_fraktal->setHeaderData(3, Qt::Horizontal, "M");
    mdl_fraktal->setHeaderData(4, Qt::Horizontal, "D");
    mdl_fraktal->setHeaderData(5, Qt::Horizontal, "R");

    mdl_fraktal->setHeaderData(0, Qt::Vertical, "S");
    mdl_fraktal->setHeaderData(1, Qt::Vertical, "I");
    mdl_fraktal->setHeaderData(2, Qt::Vertical, "E");
    mdl_fraktal->setHeaderData(3, Qt::Vertical, "M");
    mdl_fraktal->setHeaderData(4, Qt::Vertical, "D");
    mdl_fraktal->setHeaderData(5, Qt::Vertical, "R");

    for (int i = 0; i < mdl_fraktal->columnCount(); i++)
        table_fraktal->setColumnWidth(i, 65);

    for (int i = 0; i < mdl_fraktal->rowCount(); i++) {
        for (int j = 0; j < mdl_fraktal->columnCount(); j++){
            QModelIndex index = mdl_fraktal->index(i, j);
            mdl_fraktal->setData(index, 0.0 , Qt::DisplayRole);
        }
    }

}


void Widget::createTableNetwork() {

    mdl_network->insertColumns(0, 4);

    mdl_network->setHeaderData(0, Qt::Horizontal, "Слой");
    mdl_network->setHeaderData(1, Qt::Horizontal, "Общее число\nузлов");
    mdl_network->setHeaderData(2, Qt::Horizontal, "Заражено");
    mdl_network->setHeaderData(3, Qt::Horizontal, "Иммунизировано");

    table_network->setColumnWidth(0, 70);
    table_network->setColumnWidth(1, 90);
    table_network->setColumnWidth(2, 100);
    table_network->setColumnWidth(3, 120);

    table_network->verticalHeader()->hide();

}


void Widget::loadNetwork() {

    QString network =
            QFileDialog::getOpenFileName(0, "Загрузить сеть" ,"" , "*.txt");

    QFile file(network);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug()<<1;

    QTextStream in(&file);
    QString line = in.readAll();
    QStringList lst;
    lst=line.split("");
    file.close();


    int N = 100, max = 0;

    int m[N][N],i=0,j=0,ii,jj,s[N],sum=0,ms[N+1][N+1],x,k=0,prmas[N];

    //Здесь мы получили массив в нужном виде. Матрица связности m[i][j]
    foreach(QString str,lst)
        if(str=="1" || str=="0")
        {
        m[i][j]=str.toInt();

        j++;

        if(j==N)
        {
            j=0;
            i++;
        }
    }

    //Посчитал сумму по строкам и записал все это в массив s[i]
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
        {
        sum+=m[i][j];
        if(j==N-1)
        {
            s[i]=sum;
            if (max < sum)
                max = sum;
            sum=0;
        }
    }

    qDebug() << "Максимум равен " << max; // Это выводит инфу в консольку, нужна для проверки правильности работы проги

    //Находим количество вершин каждого слоя

    int mysl[max];
    for (int i = 0; i < max; i++)
        mysl[i] = 0;

    for (int i = 0; i < max; i++){
        for (int j = 0; j < N; j++) {
            if (s[j] == i+1)
                mysl[i] ++;
        }
    }


    //Заносим данные в таблицу стартовых параметров эпидемии
    int pos = 0;
    for (int i = 0; i < max; i++) {

        if (mysl[i] != 0) {
            QStandardItem* item = new QStandardItem();
            item->setData(i+1, Qt::DisplayRole);
            mdl_network->insertRow(pos);
            mdl_network->setItem(pos, 0, item);

            QStandardItem* item1 = new QStandardItem();
            item1->setData(mysl[i], Qt::DisplayRole);
            mdl_network->setItem(pos, 1, item1);

            QStandardItem* item2 = new QStandardItem();
            item2->setData(0, Qt::DisplayRole);
            mdl_network->setItem(pos, 2, item2);

            QStandardItem* item3 = new QStandardItem();
            item3->setData(0, Qt::DisplayRole);
            mdl_network->setItem(pos, 3, item3);
            pos++;
        }
        this->n_sloi = pos; //Запомнили во внутренней переменной класса число слоев
    }

    //Создал матрицу, в которой в первой строке и столбце записаны суммы MS
    for(i=1,ii=0;i<N+1;i++,ii++)
    {
        ms[0][i]=s[ii];
        ms[i][0]=s[ii];
    }
    ms[0][0]=0;
    for(i=0,ii=1;i<N;i++,ii++)
        for(j=0,jj=1;j<N;j++,jj++)
            ms[ii][jj]=m[i][j];

    //Здесь будем хранить матрицу связности с существующими слоями
    matrix = new double*[this->n_sloi];
    for (int i = 0; i < this->n_sloi; i++)
        matrix[i] = new double[this->n_sloi];

    // Это промежуточный массив для вычислений. Проблема в том, что у нас существуют не все слои с макс. значения степени и до минимального.
    // Поэтому, если их убрать, сдвинутся индексы в массиве, и мы не сможем записывать в массив значения по номеру степени.
    // Придется искать соотв. степени индекс, что еще больше все запутает и усложнит.
    // Лучше потратим лишнюю память
    double array[max][max];

    for (int i = 0; i < max; i++)
        for (int j = 0; j<max; j++)
            array[i][j] = 0;

    //Считаем число связей между слоями
    for (int i = 1; i<N+1; i++){
        for (int j=1; j< N+1; j++) {
            if(ms[i][j] == 1 && i!=j){
                int ind_row = ms[i][0] - 1;
                int ind_col = ms[0][j] - 1;
                array[ind_row][ind_col] ++;
            }
        }
    }

    //В матрицу связности заносим коэффициент Ps = число связей между слоями / общее число связей слоя

    for (int i = 0; i < this->n_sloi; i++){
        QModelIndex index = mdl_network->index(i, 0);
        int cur_row = mdl_network->data(index, Qt::DisplayRole).toInt(); //Текущий слой, для которого мы считаем связность

        index = mdl_network->index(i, 1);
        int n_versh = mdl_network->data(index, Qt::DisplayRole).toInt(); //Общее число вершин в слое


        double n_sv = cur_row * n_versh; // Общее число связей в слое - степень * число вершин в слое


        for (int j = 0; j < this->n_sloi; j++) {
            index = mdl_network->index(j, 0);
            int cur_col = mdl_network->data(index, Qt::DisplayRole).toInt();
            matrix[i][j] = (array[cur_row-1][cur_col-1])/n_sv;
        }
    }


}

void Widget::onPlotClicked() {
    if (rb_randscan->isChecked())
        myplot();
    else
        myplot2();
}

void Widget::myplot() {

    int n = this->n_sloi; // Число слоев в сети
    qDebug() << "SS" << n;
    double mass[n][6];
    double mass2[n][6];

    QColor color;

    switch(this->cur_color) {
    case 0:
        color = Qt::blue;
        break;
    case 1:
        color = Qt::green;
        break;
    case 2:
        color = Qt::red;
        break;
    case 3:
        color = Qt::yellow;
        break;
    default:
        color = Qt::black;
    }

    this->cur_color ++;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            mass[i][j] = 0;
            mass2[i][j] = 0;
        }
    }

    double s = 0.002; // Интенсивность сканирования (число атакованных в единицу времени одной зараженной вершиной)

    QPolygonF points;

    //Заносим в первый массив начальные условия (число зараженных, иммунизированых и уязвимых по всем слоям)
    for (int i = 0; i < n; i++) {

        QModelIndex index = mdl_network->index(i, 2);
        double inf = mdl_network->data(index, Qt::DisplayRole).toDouble();

        index = mdl_network->index(i, 3);
        double imm = mdl_network->data(index, Qt::DisplayRole).toDouble();

        index = mdl_network->index(i, 1);
        double susp = mdl_network->data(index, Qt::DisplayRole).toDouble() - inf - imm;

        mass2[i][0] = susp;
        mass2[i][2] = inf;
        mass2[i][3] = imm;

    }

    //Заполняем из таблицы матрицу вероятностей

    double p[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            QModelIndex index = mdl_fraktal->index(i, j);
            p[i][j] = mdl_fraktal->data(index, Qt::DisplayRole).toDouble();
        }
    }


    int count = 0; // Число шагов эпидемии, которые мы посчитали

    while (count < 100) {

        //Переписали в матрицу с текущим количеством вершин разных состояний по слоям значения из матрицы для расчетов
        // В mass[] хранятся параметры для i-ого шага, а в mass2[] - для i+1 ого

        for (int i =0; i < n; i++){
            for (int j = 0; j < 6; j++) {
                mass[i][j] = mass2[i][j];
            }
        }

        //Расчет текущего числа источников эпидемии
        double cur_i = 0;
        for (int i =0; i < n; i++)
            cur_i = cur_i + mass[i][2];

        points << QPointF(count, cur_i);

        //Общая интенсивность сканирования
        double v = s * cur_i;

        //Расчет переходов
        for (int i = 0; i<n; i++) {
            /////////////////////////////////////////////////

            //S->E
            mass2[i][1] = mass2[i][1] + mass[i][0]*p[0][2]*v;
            mass2[i][0] = mass2[i][0] - mass[i][0]*p[0][2]*v;

            //S->I
            mass2[i][2] = mass2[i][2] + mass[i][0]*p[0][1]*v;
            mass2[i][0] = mass2[i][0] - mass[i][0]*p[0][1]*v;
            //qDebug() << "SHAG " << count << " SLOI  " << i << " mass2 " << mass2[i][2];

            //S->M
            mass2[i][3] = mass2[i][3] + mass[i][0]*p[0][3];
            mass2[i][0] = mass2[i][0] - mass[i][0]*p[0][3];

            //S->D
            mass2[i][4] = mass2[i][4] + mass[i][0]*p[0][4];
            mass2[i][0] = mass2[i][0] - mass[i][0]*p[0][4];

            //S->R
            mass2[i][5] = mass2[i][5] + mass[i][0]*p[0][5];
            mass2[i][0] = mass2[i][0] - mass[i][0]*p[0][5];

            //            ////////////////////////////////////////////////

            //E->S
            mass2[i][0] = mass2[i][0] + mass[i][1]*p[2][0];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][0];

            //E->I
            mass2[i][2] = mass2[i][2] + mass[i][1]*p[2][1];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][1];

            //E->M
            mass2[i][3] = mass2[i][3] + mass[i][1]*p[2][3];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][3];

            //E->D
            mass2[i][4] = mass2[i][4] + mass[i][1]*p[2][4];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][4];

            //E->R
            mass2[i][5] = mass2[i][5] + mass[i][1]*p[2][5];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][5];

            //            ////////////////////////////////////////////////

            //I->S
            mass2[i][0] = mass2[i][0] + mass[i][2]*p[1][0];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][0];

            //I->E
            mass2[i][1] = mass2[i][1] + mass[i][2]*p[1][2];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][2];

            //I->M
            mass2[i][3] = mass2[i][3] + mass[i][2]*p[1][3];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][3];

            //I->D
            mass2[i][4] = mass2[i][4] + mass[i][2]*p[1][4];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][4];

            //I->R
            mass2[i][5] = mass2[i][5] + mass[i][2]*p[1][5];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][5];

            //            ////////////////////////////////////////////////

            //M->S
            mass2[i][0] = mass2[i][0] + mass[i][3]*p[3][0];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][0];

            //M->E
            mass2[i][1] = mass2[i][1] + mass[i][3]*p[3][2];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][2];

            //M->I
            mass2[i][2] = mass2[i][2] + mass[i][3]*p[3][1];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][1];

            //M->D
            mass2[i][4] = mass2[i][4] + mass[i][3]*p[3][4];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][4];

            //M->R
            mass2[i][5] = mass2[i][5] + mass[i][3]*p[3][5];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][5];

            //            ////////////////////////////////////////////////

            //D->S
            mass2[i][0] = mass2[i][0] + mass[i][4]*p[4][0];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][0];

            //D->E
            mass2[i][1] = mass2[i][1] + mass[i][4]*p[4][2];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][2];

            //D->I
            mass2[i][2] = mass2[i][2] + mass[i][4]*p[4][1];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][1];

            //D->M
            mass2[i][3] = mass2[i][3] + mass[i][4]*p[4][3];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][3];

            //D->R
            mass2[i][5] = mass2[i][5] + mass[i][4]*p[4][5];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][5];

            //            ////////////////////////////////////////////////

            //R->S
            mass2[i][0] = mass2[i][0] + mass[i][5]*p[5][0];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][0];

            //R->E
            mass2[i][1] = mass2[i][1] + mass[i][5]*p[5][2];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][2];

            //R->I
            mass2[i][2] = mass2[i][2] + mass[i][5]*p[5][1];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][1];

            //R->M
            mass2[i][3] = mass2[i][3] + mass[i][5]*p[5][3];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][3];

            //R->D
            mass2[i][4] = mass2[i][4] + mass[i][5]*p[5][4];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][4];

            //            ////////////////////////////////////////////////
        }

        count++;

    }

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle("X");
    curve->setPen( color, 2),
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    curve->setSamples(points);
    curve->attach(plot);
    plot->replot();
}

//Рассчитывает эпидемию по модели из методички

void Widget::myplot2() {

    int n = this->n_sloi; // Число слоев в сети
    double mass[n][6];
    double mass2[n][6];

    QColor color;

    switch(this->cur_color) {
    case 0:
        color = Qt::blue;
        break;
    case 1:
        color = Qt::green;
        break;
    case 2:
        color = Qt::red;
        break;
    case 3:
        color = Qt::yellow;
        break;
    default:
        color = Qt::black;
    }

    this->cur_color ++;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 6; j++) {
            mass[i][j] = 0;
            mass2[i][j] = 0;
        }
    }

    QPolygonF points;

    //Заносим в первый массив начальные условия (число зараженных, иммунизированых и уязвимых по всем слоям)
    for (int i = 0; i < n; i++) {

        QModelIndex index = mdl_network->index(i, 2);
        double inf = mdl_network->data(index, Qt::DisplayRole).toDouble();

        index = mdl_network->index(i, 3);
        double imm = mdl_network->data(index, Qt::DisplayRole).toDouble();

        index = mdl_network->index(i, 1);
        double susp = mdl_network->data(index, Qt::DisplayRole).toDouble() - inf - imm;

        mass2[i][0] = susp;
        mass2[i][2] = inf;
        mass2[i][3] = imm;

    }

    //Заполняем из таблицы матрицу вероятностей

    double p[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            QModelIndex index = mdl_fraktal->index(i, j);
            p[i][j] = mdl_fraktal->data(index, Qt::DisplayRole).toDouble();
        }
    }


    int count = 0; // Число шагов эпидемии, которые мы посчитали

    while (count < 100) {

        //Переписали в матрицу с текущим количеством вершин разных состояний по слоям значения из матрицы для расчетов
        // В mass[] хранятся параметры для i-ого шага, а в mass2[] - для i+1 ого

        for (int i =0; i < n; i++){
            for (int j = 0; j < 6; j++) {
                mass[i][j] = mass2[i][j];
            }
        }

        //Расчет текущего числа источников эпидемии
        double cur_i = 0;

        for (int i =0; i < n; i++)
            cur_i = cur_i + mass[i][2];

        int cur_i_int=static_cast<int>(cur_i);

        points << QPointF(count, cur_i_int);

        //Рассчитываем общее число атакованных вершин в слое
        // v = Сумма по всем слоям (Число источников в атакующем слое * степень атакующего слоя  * вероятность связности
        // * доля зараженных в текущем слое
        double v; //Количество атак на вершины рассчитываемого слоя
        double is; // Источников инфекции в атакующем слое
        double s;   //Степень атакующего слоя
        double ps;  // Вероятность связности из матрицы
        double ks;  // Доля уязвимых вершин в текущем слое



        qDebug() << "SHAG " << count;
        qDebug() << "==============================================";

        //Расчет переходов
        for (int i = 0; i<n; i++) {

            v = 0;
            double n_vers =  mdl_network->data(mdl_network->index(i, 1), Qt::DisplayRole).toDouble();
            ks = mass[i][0]/n_vers;
            qDebug() << "UYAZVIMIH " << mass[i][0];
            qDebug() << " VERSHIN V SLOE " << n_vers;
            qDebug() << "KS " << ks;
            qDebug() << "";

            for (int j = 0; j < n; j++) {
                qDebug() << "+++++ SLOI " << j << "++++++++";
                is = mass[j][2];
                qDebug() << "IS " << mass[j][2];
                s = mdl_network->data(mdl_network->index(j, 0), Qt::DisplayRole).toDouble();
                qDebug() << "S " << s;
                ps = matrix[j][i];
                qDebug() << "PS "<< ps;
                v = v + is*(s-1)*ps*ks*ks;
            }

            qDebug() << "VSEGO ATAK " << v;
            qDebug() << " ///////////////////////////////";

            /////////////////////////////////////////////////

            //S->E
            mass2[i][1] = mass2[i][1] + p[0][2]*v;
            mass2[i][0] = mass2[i][0] - p[0][2]*v;

            //S->I
            mass2[i][2] = mass2[i][2] + p[0][1]*v;
            mass2[i][0] = mass2[i][0] - p[0][1]*v;
            qDebug() << "SHAG " << count << " SLOI  " << i << " mass2 " << mass2[i][2];

            //S->M
            mass2[i][3] = mass2[i][3] + mass[i][0]*p[0][3];
            mass2[i][0] = mass2[i][0] - mass[i][0]*p[0][3];

            //S->D
            mass2[i][4] = mass2[i][4] + mass[i][0]*p[0][4];
            mass2[i][0] = mass2[i][0] - mass[i][0]*p[0][4];

            //S->R
            mass2[i][5] = mass2[i][5] + mass[i][0]*p[0][5];
            mass2[i][0] = mass2[i][0] - mass[i][0]*p[0][5];

            //            ////////////////////////////////////////////////

            //E->S
            mass2[i][0] = mass2[i][0] + mass[i][1]*p[2][0];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][0];

            //E->I
            mass2[i][2] = mass2[i][2] + mass[i][1]*p[2][1];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][1];

            //E->M
            mass2[i][3] = mass2[i][3] + mass[i][1]*p[2][3];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][3];

            //E->D
            mass2[i][4] = mass2[i][4] + mass[i][1]*p[2][4];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][4];

            //E->R
            mass2[i][5] = mass2[i][5] + mass[i][1]*p[2][5];
            mass2[i][1] = mass2[i][1] - mass[i][1]*p[2][5];

            //            ////////////////////////////////////////////////

            //I->S
            mass2[i][0] = mass2[i][0] + mass[i][2]*p[1][0];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][0];

            //I->E
            mass2[i][1] = mass2[i][1] + mass[i][2]*p[1][2];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][2];

            //I->M
            mass2[i][3] = mass2[i][3] + mass[i][2]*p[1][3];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][3];

            //I->D
            mass2[i][4] = mass2[i][4] + mass[i][2]*p[1][4];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][4];

            //I->R
            mass2[i][5] = mass2[i][5] + mass[i][2]*p[1][5];
            mass2[i][2] = mass2[i][2] - mass[i][2]*p[1][5];

            //            ////////////////////////////////////////////////

            //M->S
            mass2[i][0] = mass2[i][0] + mass[i][3]*p[3][0];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][0];

            //M->E
            mass2[i][1] = mass2[i][1] + mass[i][3]*p[3][2];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][2];

            //M->I
            mass2[i][2] = mass2[i][2] + mass[i][3]*p[3][1];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][1];

            //M->D
            mass2[i][4] = mass2[i][4] + mass[i][3]*p[3][4];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][4];

            //M->R
            mass2[i][5] = mass2[i][5] + mass[i][3]*p[3][5];
            mass2[i][3] = mass2[i][3] - mass[i][3]*p[3][5];

            //            ////////////////////////////////////////////////

            //D->S
            mass2[i][0] = mass2[i][0] + mass[i][4]*p[4][0];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][0];

            //D->E
            mass2[i][1] = mass2[i][1] + mass[i][4]*p[4][2];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][2];

            //D->I
            mass2[i][2] = mass2[i][2] + mass[i][4]*p[4][1];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][1];

            //D->M
            mass2[i][3] = mass2[i][3] + mass[i][4]*p[4][3];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][3];

            //D->R
            mass2[i][5] = mass2[i][5] + mass[i][4]*p[4][5];
            mass2[i][4] = mass2[i][4] - mass[i][4]*p[4][5];

            //            ////////////////////////////////////////////////

            //R->S
            mass2[i][0] = mass2[i][0] + mass[i][5]*p[5][0];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][0];

            //R->E
            mass2[i][1] = mass2[i][1] + mass[i][5]*p[5][2];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][2];

            //R->I
            mass2[i][2] = mass2[i][2] + mass[i][5]*p[5][1];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][1];

            //R->M
            mass2[i][3] = mass2[i][3] + mass[i][5]*p[5][3];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][3];

            //R->D
            mass2[i][4] = mass2[i][4] + mass[i][5]*p[5][4];
            mass2[i][5] = mass2[i][5] - mass[i][5]*p[5][4];

            //            ////////////////////////////////////////////////
            double n_obs = mass[i][0]+mass[i][1]+mass[i][2]+mass[i][3]+mass[i][4]+mass[i][5];
            if (n_obs > n_vers) {
                mass[i][0] = 0;
                mass[i][2] = n_vers - (mass[i][1]+mass[i][3]+mass[i][4]+mass[i][5]);
            }

        }

        count++;

    }

    QwtPlotCurve *curve = new QwtPlotCurve();
    curve->setTitle("X");
    curve->setPen( color, 2),
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

    curve->setSamples(points);
    curve->attach(plot);
    plot->replot();
}


Widget::~Widget()
{

}
