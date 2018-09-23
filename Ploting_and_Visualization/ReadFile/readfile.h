#ifndef READFILE_H
#define READFILE_H
#include<QString>
#include<string>
using namespace std;
class ReadFIle
{
public:
    ReadFIle();
    void howtodeletefile();
    void openFile(const QString& fileName);
    double *dData();
    QString*sString();
    QString*Catigory();
private:
    QString *sdata;
    double  *ddata;
    QString *catigory;
};

#endif // READFILE_H
