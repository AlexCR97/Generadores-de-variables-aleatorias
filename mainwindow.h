#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_NumerosAleatorios_Agregar_clicked();
    void on_lineEdit_NumerosAleatorios_returnPressed();
    void on_tabWidget_Metodo_currentChanged(int index);
    void on_tabWidget_Metodo_Transformada_currentChanged(int index);
    void on_tabWidget_Metodo_Convolucion_currentChanged(int index);
    void on_tabWidget_Metodo_Composicion_currentChanged(int index);
    void on_pushButton_Calcular_clicked();

    void on_pushButton_BorrarTabla_clicked();

    void on_pushButton_NumerosAleatorios_Borrar_clicked();

    void on_pushButton_NumerosAleatorios_Quitar_clicked();

private:
    Ui::MainWindow *ui;

    // Tab Method names
    const QString TAB_METHOD_TRANS = "Transformada inversa";
    const QString TAB_METHOD_CONVO = "Convolucion";
    const QString TAB_METHOD_COMPO = "Composicion";

    // Tab names
    const QString TAB_TRANS_UNIFORME = "Distribucion Uniforme";
    const QString TAB_TRANS_EXPONENCIAL = "Distribucion Exponencial";
    const QString TAB_CONVO_BINOMIAL = "Distribucion Binomial";
    const QString TAB_CONVO_ERLANG = "Distribucion K-Erlang";
    const QString TAB_CONVO_NORMAL = "Distribucion Normal";
    const QString TAB_COMPO_TRIANGULAR = "Distribucion Triangular";

    // Current tab controller
    QString currentTab = TAB_TRANS_UNIFORME;

private:
    // METHODS
    void solve_Convolucion_Binomial();
    void solve_Convolucion_Erlang();
    void solve_Convolucion_Normal();
    void solve_Composicion_Triangular();
    void solve_Transformada_Uniforme();
    void solve_Transformada_Exponencial();
};

#endif // MAINWINDOW_H
