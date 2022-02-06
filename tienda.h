#ifndef TIENDA_H
#define TIENDA_H

#include <QMainWindow>
#include "producto.h"
#include "factura.h"

#define IVA 12

QT_BEGIN_NAMESPACE
namespace Ui { class Tienda; }
QT_END_NAMESPACE

class Tienda : public QMainWindow
{
    Q_OBJECT

public:
    Tienda(QWidget *parent = nullptr);
    ~Tienda();

private slots:
    void on_inProducto_currentIndexChanged(int index);

    void on_btnAgregar_released();

    void on_btnFacturar_pressed();


private:
    Ui::Tienda *ui;
    QList<Producto*> m_productos;
    QString m_detalles;

    void cargarProductos();
    float m_subtotal;
    float iva;
    float total;
    int contador=0;
    bool checkVacio();
    bool verificarCedula(QString as);
    void enviarDatosdeCompra();
    void calcular(float stProducto);
    void limpiar();



};
#endif // TIENDA_H
