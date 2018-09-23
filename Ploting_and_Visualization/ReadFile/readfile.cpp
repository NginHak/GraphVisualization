#include "readfile.h"
#include<QDebug>
#include<iostream>
#include<QAxObject>
ReadFIle::ReadFIle()
{
    ddata=new double[10];
    catigory=new QString[2];
    sdata=new QString[10];
}
void ReadFIle::openFile(const QString& fileName )
{
    QAxObject* excel = new QAxObject( "Excel.Application", 0 );
    QAxObject* workbooks = excel->querySubObject( "Workbooks" );
    QAxObject* workbook = workbooks->querySubObject( "Open(const QString&)", fileName );
        QAxObject*cell;
        for (int row=1; row <=1; row++)
        {
            for (int column=1; column <=3; column++)
            {
                cell = excel->querySubObject("Cells(Int, Int)", row, column );
                QVariant val = cell->dynamicCall("value");
                qDebug()<<val;
            }
        }
    workbook->dynamicCall("Close()");
    excel->dynamicCall("Quit()");
}

double *ReadFIle::dData()
{
    return ddata;
}

QString *ReadFIle::sString()
{
    return sdata;
}

QString *ReadFIle::Catigory()
{
    return catigory;
}

