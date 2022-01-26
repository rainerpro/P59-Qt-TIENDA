#ifndef FACTURA_H
#define FACTURA_H

#include <QDialog>
#include <QTextStream>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>

namespace Ui {
class Factura;
}

class Factura : public QDialog
{
    Q_OBJECT

public:
    explicit Factura(QWidget *parent = nullptr);
    ~Factura();

    void datosFactura(QString cedula,QString nombre,QString telefono,QString email,QString direccion,QString detalles);
    void ValoresFactura(float subtotal,float iva,float total);
    void cargarDatos();

private slots:
    void on_btnImprimir_clicked();

    void on_btnCerrar_clicked();

private:
    Ui::Factura *ui;
    QString fechahora;
    QString fecha;
    QString hora;
    QString c_detalles;
    QString c_cedula;
    QString c_nombre;
    QString c_telefono;
    QString c_email;
    QString c_direccion;
    float c_subtotal;
    float c_iva;
    float c_total;
};

#endif // FACTURA_H
