#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDesktopWidget>
#include <QStyle>

#include "Metodos/Composicion.h"
#include "Metodos/Convolucion.h"
#include "Metodos/TransformadaInversa.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Center window on screen
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

    // Fill table
    QHeaderView* header = ui->tableWidget_Datos->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * ADD RANDOM NUMBERS TO LIST
 */
void MainWindow::on_pushButton_NumerosAleatorios_Agregar_clicked()
{
    QString s = ui->lineEdit_NumerosAleatorios->text();

    // Get numbers
    if (s.contains(" ")) {
        QStringList numbers = s.split(" ");

        // Add to list
        for (int i = 0; i < numbers.count(); i++)
            ui->listWidget_NumerosAleatorios->addItem(numbers.at(i));
    } else {
        // Add to list
        ui->listWidget_NumerosAleatorios->addItem(s);
    }

    // Reset line edit
    ui->lineEdit_NumerosAleatorios->clear();
}
void MainWindow::on_lineEdit_NumerosAleatorios_returnPressed()
{
    QString s = ui->lineEdit_NumerosAleatorios->text();

    // Get number(s)
    if (s.contains(" ")) {
        QStringList numbers = s.split(" ");

        // Add to list
        for (int i = 0; i < numbers.count(); i++)
            ui->listWidget_NumerosAleatorios->addItem(numbers.at(i));
    } else {
        // Add to list
        ui->listWidget_NumerosAleatorios->addItem(s);
    }

    // Reset line edit
    ui->lineEdit_NumerosAleatorios->clear();
}

/*
 * CLEAR RANDOM NUMBERS
 */
void MainWindow::on_pushButton_NumerosAleatorios_Borrar_clicked()
{
    ui->listWidget_NumerosAleatorios->clear();
}
void MainWindow::on_pushButton_NumerosAleatorios_Quitar_clicked()
{
    foreach (QListWidgetItem* item, ui->listWidget_NumerosAleatorios->selectedItems())
        delete ui->listWidget_NumerosAleatorios->takeItem(ui->listWidget_NumerosAleatorios->row(item));
}

/*
 * TAB CHANGE
 */
void MainWindow::on_tabWidget_Metodo_currentChanged(int index)
{
    // Get method tab
    QString tab = ui->tabWidget_Metodo->tabText(index);

    // Switch on method tab
    if (tab == this->TAB_METHOD_COMPO) {
        index = ui->tabWidget_Metodo_Composicion->currentIndex();
        this->currentTab = ui->tabWidget_Metodo_Composicion->tabText(index);
        return;
    }

    if (tab == this->TAB_METHOD_CONVO) {
        index = ui->tabWidget_Metodo_Convolucion->currentIndex();
        this->currentTab = ui->tabWidget_Metodo_Convolucion->tabText(index);
        return;
    }

    if (tab == this->TAB_METHOD_TRANS) {
        index = ui->tabWidget_Metodo_Transformada->currentIndex();
        this->currentTab = ui->tabWidget_Metodo_Transformada->tabText(index);
    }
}

void MainWindow::on_tabWidget_Metodo_Transformada_currentChanged(int index)
{
    this->currentTab = ui->tabWidget_Metodo_Transformada->tabText(index);
}

void MainWindow::on_tabWidget_Metodo_Convolucion_currentChanged(int index)
{
    this->currentTab = ui->tabWidget_Metodo_Convolucion->tabText(index);
}

void MainWindow::on_tabWidget_Metodo_Composicion_currentChanged(int index)
{
    this->currentTab = ui->tabWidget_Metodo_Composicion->tabText(index);
}

/*
 * CLEAR TABLE
 */
void MainWindow::on_pushButton_BorrarTabla_clicked()
{
    ui->tableWidget_Datos->clear();
}

/*
 * CALCULATE
 */
void MainWindow::on_pushButton_Calcular_clicked()
{
    this->statusBar()->showMessage(this->currentTab, 2500);

    // Switch on method
    if (this->currentTab == this->TAB_COMPO_TRIANGULAR) {
        this->solve_Composicion_Triangular();
        return;
    }

    if (this->currentTab == this->TAB_CONVO_BINOMIAL) {
        this->solve_Convolucion_Binomial();
        return;
    }

    if (this->currentTab == this->TAB_CONVO_ERLANG) {
        this->solve_Convolucion_Erlang();
        return;
    }

    if (this->currentTab == this->TAB_CONVO_NORMAL) {
        this->solve_Convolucion_Normal();
        return;
    }

    if (this->currentTab == this->TAB_TRANS_EXPONENCIAL) {
        this->solve_Transformada_Exponencial();
        return;
    }

    if (this->currentTab == this->TAB_TRANS_UNIFORME) {
        this->solve_Transformada_Uniforme();
    }
}

/*
 * SOLVE
 */
void MainWindow::solve_Convolucion_Binomial()
{
    // Get data
    double p = ui->doubleSpinBox_Convolucion_Binomial_Probabilidad->text().toDouble();
    int n = ui->listWidget_NumerosAleatorios->count();

    QStringList numbers[n];
    for (int i = 0; i < n; i++)
        numbers[i] = ui->listWidget_NumerosAleatorios->item(i)->text().split(",");

    double** r = new double*[n];
    int m = numbers[0].count();

    for (int i = 0; i < n; i++) {
        r[i] = new double[m];
        for (int j = 0; j < m; j++)
            r[i][j] = numbers[i].at(j).toDouble();
    }

    // Create data table
    double** table = sim::Convolucion::distribucionBinomial(p, r, n, m);

    // Add data to table widget
    ui->tableWidget_Datos->setRowCount(0);
    ui->tableWidget_Datos->setColumnCount((m * 2) + 2);

    for (int i = 0; i < n; i++) {

        // Add row
        ui->tableWidget_Datos->insertRow(i);

        // Fill row with data
        ui->tableWidget_Datos->setItem(i, 0, new QTableWidgetItem(QString::number(table[i][0])));

        for (int j = 1; j <= m * 2; j++)
            ui->tableWidget_Datos->setItem(i, j, new QTableWidgetItem(QString::number(table[i][j])));

        ui->tableWidget_Datos->setItem(i, (m * 2) + 1, new QTableWidgetItem(QString::number(table[i][(m * 2) + 1])));
    }
}

void MainWindow::solve_Convolucion_Erlang()
{
    // Get data
    int n = ui->listWidget_NumerosAleatorios->count();
    int k = ui->spinBox_Convolucion_Erlang_K->text().toInt();
    double media = ui->doubleSpinBox_Convolucion_Erlang_Media->text().toDouble();

    QStringList numbers[n];
    for (int i = 0; i < n; i++)
        numbers[i] = ui->listWidget_NumerosAleatorios->item(i)->text().split(",");

    double** r = new double*[n];

    for (int i = 0; i < n; i++) {
        r[i] = new double[k];
        for (int j = 0; j < k; j++)
            r[i][j] = numbers[i].at(j).toDouble();
    }

    // Create table
    double** table = sim::Convolucion::distribucionErlang(k, media, r, n);

    // Add data to table widget
    ui->tableWidget_Datos->setRowCount(0);
    ui->tableWidget_Datos->setColumnCount(k + 3);

    for (int i = 0; i < n; i++) {

        // Add row
        ui->tableWidget_Datos->insertRow(i);

        // Fill row with data
        ui->tableWidget_Datos->setItem(i, 0, new QTableWidgetItem(QString::number(table[i][0])));

        for (int j = 1; j <= k; j++)
            ui->tableWidget_Datos->setItem(i, j, new QTableWidgetItem(QString::number(table[i][j])));

        ui->tableWidget_Datos->setItem(i, k + 1, new QTableWidgetItem(QString::number(table[i][k + 1])));
        ui->tableWidget_Datos->setItem(i, k + 2, new QTableWidgetItem(QString::number(table[i][k + 2])));
    }
}

void MainWindow::solve_Convolucion_Normal()
{
    // Get data
    double media = ui->doubleSpinBox_Convolucion_Normal_Media->text().toDouble();
    double desviacion = ui->doubleSpinBox_Convolucion_Normal_Desviacion->text().toDouble();

    // Get random numbers (sumatorias)
    int n = ui->listWidget_NumerosAleatorios->count();
    double sumatorias[n];

    for (int i = 0; i < n; i++)
        sumatorias[i] = ui->listWidget_NumerosAleatorios->item(i)->text().toDouble();

    // Create data table
    double** table = sim::Convolucion::distribucionNormal(media, desviacion, sumatorias, n);

    // Add data to table widget
    ui->tableWidget_Datos->setRowCount(0);
    ui->tableWidget_Datos->setColumnCount(4);

    for (int i = 0; i < n; i++) {

        // Add row
        ui->tableWidget_Datos->insertRow(i);

        // Fill row with data
        ui->tableWidget_Datos->setItem(i, 0, new QTableWidgetItem(QString::number(table[i][0])));
        ui->tableWidget_Datos->setItem(i, 1, new QTableWidgetItem(QString::number(table[i][1])));
        ui->tableWidget_Datos->setItem(i, 2, new QTableWidgetItem(QString::number(table[i][2])));
        ui->tableWidget_Datos->setItem(i, 3, new QTableWidgetItem(QString::number(table[i][3])));
    }
}

void MainWindow::solve_Composicion_Triangular()
{
    // Get data
    double boundLower = ui->doubleSpinBox_Composicion_Triangular_Inferior->text().toDouble();
    double boundUpper = ui->doubleSpinBox_Composicion_Triangular_Superior->text().toDouble();
    double moda = ui->doubleSpinBox_Composicion_Triangular_Media->text().toDouble();

    // Get random numbers
    QStringList listRi = ui->listWidget_NumerosAleatorios->item(0)->text().split(",");
    QStringList listRj = ui->listWidget_NumerosAleatorios->item(1)->text().split(",");

    int n = listRi.count();
    double ri[n];
    double rj[n];

    for (int i = 0; i < n; i++) {
        ri[i] = listRi.at(i).toDouble();
        rj[i] = listRj.at(i).toDouble();
    }

    // Create data table
    double** table = sim::Composicion::distribucionTriangular(boundLower, boundUpper, moda, ri, rj, n);

    // Add data to table widget
    ui->tableWidget_Datos->setRowCount(0);
    ui->tableWidget_Datos->setColumnCount(5);

    for (int i = 0; i < n; i++) {

        // Add row
        ui->tableWidget_Datos->insertRow(i);

        // Fill row with data
        ui->tableWidget_Datos->setItem(i, 0, new QTableWidgetItem(QString::number(table[i][0])));
        ui->tableWidget_Datos->setItem(i, 1, new QTableWidgetItem(QString::number(table[i][1])));
        ui->tableWidget_Datos->setItem(i, 2, new QTableWidgetItem(QString::number(table[i][2])));
        ui->tableWidget_Datos->setItem(i, 3, new QTableWidgetItem(QString::number(table[i][3])));
        ui->tableWidget_Datos->setItem(i, 4, new QTableWidgetItem(QString::number(table[i][4])));
    }
}

void MainWindow::solve_Transformada_Uniforme()
{
    // Get bounds
    double boundLower = ui->doubleSpinBox_TransformadaInversa_Uniforme_Inferior->text().toDouble();
    double boundUpper = ui->doubleSpinBox_TransformadaInversa_Uniforme_Superior->text().toDouble();

    // Get random numbers
    int n = ui->listWidget_NumerosAleatorios->count();
    double r[n];

    for (int i = 0; i < n; i++)
        r[i] = ui->listWidget_NumerosAleatorios->item(i)->text().toDouble();

    // Create data table
    double** table = sim::TransformadaInversa::distribucionUniforme(boundLower, boundUpper, r, n);

    // Add data to table widget
    ui->tableWidget_Datos->setRowCount(0);
    ui->tableWidget_Datos->setColumnCount(3);

    for (int i = 0; i < n; i++) {

        // Add row
        ui->tableWidget_Datos->insertRow(i);

        // Fill row with data
        ui->tableWidget_Datos->setItem(i, 0, new QTableWidgetItem(QString::number(table[i][0])));
        ui->tableWidget_Datos->setItem(i, 1, new QTableWidgetItem(QString::number(table[i][1])));
        ui->tableWidget_Datos->setItem(i, 2, new QTableWidgetItem(QString::number(table[i][2])));
    }
}

void MainWindow::solve_Transformada_Exponencial()
{
    // Get media
    double media = ui->doubleSpinBox_TransformadaInversa_Exponencial_Media->text().toDouble();

    // Get random numbers
    int n = ui->listWidget_NumerosAleatorios->count();
    double r[n];

    for (int i = 0; i < n; i++)
        r[i] = ui->listWidget_NumerosAleatorios->item(i)->text().toDouble();

    // Create data table
    double** table = sim::TransformadaInversa::distribucionExponencial(media, r, n);

    // Add data to table widget
    ui->tableWidget_Datos->setRowCount(0);
    ui->tableWidget_Datos->setColumnCount(3);

    for (int i = 0; i < n; i++) {

        // Add row
        ui->tableWidget_Datos->insertRow(i);

        // Fill row with data
        ui->tableWidget_Datos->setItem(i, 0, new QTableWidgetItem(QString::number(table[i][0])));
        ui->tableWidget_Datos->setItem(i, 1, new QTableWidgetItem(QString::number(table[i][1])));
        ui->tableWidget_Datos->setItem(i, 2, new QTableWidgetItem(QString::number(table[i][2])));
    }
}
