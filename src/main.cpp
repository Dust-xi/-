#include <QApplication>
#include <MyWindow.h>
int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    
    MyWindow mywindow;

    mywindow.show();

    return app.exec();
}