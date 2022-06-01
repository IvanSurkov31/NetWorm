#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QHeaderView>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>

class Widget : public QWidget
{
    Q_OBJECT

private:
    QCheckBox* c_fraktS;
    QCheckBox* c_fraktE;
    QCheckBox* c_fraktI;
    QCheckBox* c_fraktM;
    QCheckBox* c_fraktD;
    QCheckBox* c_fraktR;

    QRadioButton* rb_randscan;
    QRadioButton* rb_topscan;

    QGroupBox* gb_fraktal;
    QGroupBox* gb_scantype;

    QLabel* lbl_matfrakt;
    QLabel* lbl_network;

    QPushButton* pb_plot;
    QPushButton* pb_clear;
    QPushButton* pb_load;

    QTableView* table_fraktal;
    QTableView* table_network;

    QStandardItemModel* mdl_fraktal;
    QStandardItemModel* mdl_network;

    QwtPlot* plot;
    QwtPlotGrid* grid;

    //Параметры, необходимые для расчета эпидемии
    int n_sloi; // Размерность послойной матрицы (количество слоев в сети)
    int cur_color; //Идентификатор текущего цвета графика
    double **matrix; // Двумерный динамический массив для хранения матрицы межслойной связности

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void createTableFraktal();
    void createTableNetwork();
public slots:
    void loadNetwork();
    void onPlotClicked();
    void myplot(); // рассчитывает эпидемию при случайной атаке
    void myplot2(); // рассчитывает эпидемию при топологической атаке
};

#endif // WIDGET_H
