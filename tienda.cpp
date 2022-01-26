#include "tienda.h"
#include "ui_tienda.h"

#include <QDebug>

Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);
    // Lista de productos
    cargarProductos();
    // Mostrar los productos en el combo
    foreach (Producto *p, m_productos){
        ui->inProducto->addItem(p->nombre());
    }
    // Configurar cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "P. Unitario", "Subtotal"};
    ui->outDetalle->setColumnCount(4);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    // Establecer el subtotal a 0
    m_subtotal = 0;
}

Tienda::~Tienda()
{
    delete ui;
}

/**
 * @brief Tienda::cargarProductos Carga la lista de productos de la tienda
 */
void Tienda::cargarProductos()
{
    //crear productos quemados en el codigo
    m_productos.append(new Producto(1,"Leche", 0.80));
    m_productos.append(new Producto(2,"Pan",   0.10));
    m_productos.append(new Producto(3,"Queso", 2.50));
    m_productos.append(new Producto(4,"Mortadela", 1.00));
    m_productos.append(new Producto(5,"Jamon", 3.50));
    //podria leerse de una base de datos, de un archivo o incluso de internet
}

bool Tienda::checkVacio()
{
    if(ui->inCedula->text()==""){
        ui->inCedula->setStyleSheet("QLineEdit{ background-color: red}");
    }else{
        ui->inCedula->setStyleSheet("QLineEdit{ background-color: yellow}");
    }
    if(ui->inNombre->text()==""){
        ui->inNombre->setStyleSheet("QLineEdit{ background-color: red}");
    }else{
        ui->inNombre->setStyleSheet("QLineEdit{ background-color: yellow}");
    }
    if(ui->inTelefono->text()==""){
        ui->inTelefono->setStyleSheet("QLineEdit{ background-color: red}");
    }else{
        ui->inTelefono->setStyleSheet("QLineEdit{ background-color: yellow}");
    }
    if(ui->inEmail->text()==""){
        ui->inEmail->setStyleSheet("QLineEdit{ background-color: red}");
    }else{
        ui->inEmail->setStyleSheet("QLineEdit{ background-color: yellow}");
    }
    if(ui->inDireccion->toPlainText()==""){
        ui->inDireccion->setStyleSheet("QPlainTextEdit {background-color: red}");
    }else{
        ui->inDireccion->setStyleSheet("QPlainTextEdit {background-color: yellow}");
    }
    if(ui->inCedula->text()=="" || ui->inNombre->text()=="" || ui->inTelefono->text()=="" || ui->inEmail->text()==""||ui->inDireccion->toPlainText()==""){
        return false;
    }else{
        return true;
    }

}

void Tienda::enviarDatosdeCompra()
{
    int filas=ui->outDetalle->rowCount();
    QString detalles="";
    while(contador!=filas){
        detalles+="\t"+ui->outDetalle->item(contador,0)->text()+"\t   "+
                ui->outDetalle->item(contador,1)->text()+"\t          "+
                ui->outDetalle->item(contador,2)->text()+"\t          "+
                ui->outDetalle->item(contador,3)->text()+"\t\t\n";

        contador++;
    }
    m_detalles=detalles;
}

void Tienda::calcular(float stProducto)
{
    // Calcular valores
    m_subtotal+=stProducto;
    iva=m_subtotal * IVA / 100;
    total =m_subtotal + iva;
    // mostrar valores en GUI
    ui->outSubtotal->setText("$" + QString::number(m_subtotal,'f',2));
    ui->outIva->setText("$" + QString::number(iva,'f',2));
    ui->outTotal->setText("$" + QString::number(total,'f',2));
}

void Tienda::limpiar()
{
    ui->inCedula->setText("");
    ui->inNombre->setText("");
    ui->inTelefono->setText("");
    ui->inEmail->setText("");
    ui->inDireccion->setPlainText("");
    ui->outDetalle->removeRow(0);
    ui->outDetalle->removeRow(0);
    ui->outDetalle->removeRow(0);
    ui->outSubtotal->setText("$ 0.00");
    ui->outIva->setText("$ 0.00");
    ui->outTotal->setText("$ 0.00");
    ui->inCedula->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inNombre->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inTelefono->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inEmail->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inDireccion->setStyleSheet("QPlainTextEdit {background-color: white}");



}


void Tienda::on_inProducto_currentIndexChanged(int index)
{
    // Obtener el precio del producto actual seleccionado
    float precio=m_productos.at(index)->precio();
    // Mostrar el precio del producto en la etiqueta
    ui->outPrecio->setText("$" + QString::number(precio,'f',2));
    //Resetear el spinbox de cantidad
    ui->inCantidad->setValue(0);

}


void Tienda::on_btnAgregar_released()
{
    // Validar que no se agregen productos con 0 cantidad
    int cantidad=ui->inCantidad->value();
    if(cantidad==0){
        return;
    }
    // Obtener los datos de la GUI
    int i=ui->inProducto->currentIndex();
    Producto *p=m_productos.at(i);
    // Calcular el subtotal del producto
    float subtotal=p->precio()*cantidad;
    // Agregar los datos a la tabla
    int fila=ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(fila);
    ui->outDetalle->setItem(fila,0,new QTableWidgetItem(QString::number(cantidad)));
    ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(fila,2,new QTableWidgetItem(QString::number(p->precio(),'f',2)));
    ui->outDetalle->setItem(fila,3,new QTableWidgetItem(QString::number(subtotal,'f',2)));
    //limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();
    // actualizar subtotoales
    calcular(subtotal);


}


void Tienda::on_btnFacturar_pressed()
{
    if(checkVacio()==true){
    Factura *factura=new Factura(this);
        enviarDatosdeCompra();
        factura->datosFactura(ui->inCedula->text(),ui->inNombre->text(),
                              ui->inTelefono->text(),ui->inEmail->text(),
                              ui->inDireccion->toPlainText(),m_detalles);
        factura->ValoresFactura(m_subtotal,iva,total);
    if(contador !=0){
     factura->cargarDatos();
    factura->exec();
    limpiar();
}
}

}
