#include "widgetfilemodecalibration.h"
#include "ui_widgetfilemodecalibration.h"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <string>
using namespace  std;


WidgetFilemodeCalibration::WidgetFilemodeCalibration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetFilemodeCalibration)
{
    ui->setupUi(this);
}

WidgetFilemodeCalibration::~WidgetFilemodeCalibration()
{
    delete ui;
}

//select pics from folder
void WidgetFilemodeCalibration::on_b_selectDirectory_released()
{

    m_path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                         "/home",QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);


    QDir directory(m_path);
    //m_files is QstringList
    //m_pairedFiles is vector-string
    m_files = directory.entryList(QStringList() << "*.jpg" << "*.JPG" <<"*.png"<<"*.bmp",QDir::Files);
    if (m_files.size()%2 != 0){
        QMessageBox msgBox;
        msgBox.setText("Error! The number of files in directory is odd. Please use even amount of images.");
        msgBox.exec();
    }
    else {
    int j = 1;

    m_filesSorted = m_files;
    for (int i = 0; i<m_files.size(); i++){
        if (i < m_files.size()/2){
            m_filesSorted[i+i] = m_files[i];
        }
        else{
            m_filesSorted[j] = m_files[i];
            j += 2;
        }
    }

    for (int i = 0; i <m_filesSorted.size(); i++){
        m_filesSorted[i] = m_path +  "/" + m_filesSorted[i];
    }
    // push back to vector<string>
    foreach( QString str, m_filesSorted) {
      m_pairs.push_back(str.toLocal8Bit().constData());
    }

    }



//    for (int i = 0; i < m_files.size(); i++){
//        .toLocal8Bit().constData();
//    }
   // qDebug() << "vector of strings " << m_pairs[0];

    for (int x = 0; x != m_pairs.size(); ++x)
    {
         //cout << m_pairs[x] << "- subscripting" << endl;
//         cout << m_pairs.at(x) << "- calling at member" << endl;
    }


    emit sendVectorString(m_pairs);
}


//select specified files
void WidgetFilemodeCalibration::on_b_selectFiles_released()
{
   //stringlist of full paths
   m_files = QFileDialog::getOpenFileNames(this,
                                                    tr("Open Image"), ".",
                                                    tr("Image Files (*.png *.bmp *.jpg)"));
   //chosen filenames
//   QStringList sorted;
//   foreach (QString path, m_files) {
//       QFile f(path);
//       QFileInfo fileInfo(f.fileName());
//       QString filename(fileInfo.fileName());
//       sorted.append(filename);
//   }

   if (m_files.size()%2 != 0){
       QMessageBox msgBox;
       msgBox.setText("Error! The number of files is odd. Please use even amount of images.");
       msgBox.exec();
   }
   else {
       int j = 1;

       m_filesSorted = m_files;
       for (int i = 0; i<m_files.size(); i++){
           if (i < m_files.size()/2){
               m_filesSorted[i+i] = m_files[i];
           }
           else{
               m_filesSorted[j] = m_files[i];
               j += 2;
           }
       }

       foreach( QString str, m_filesSorted) {
         m_pairs.push_back(str.toLocal8Bit().constData());
       }

   }
//   qDebug() << "just a chosen files" << sorted;

   for (int x = 0; x != m_pairs.size(); ++x)
   {
        cout << m_pairs[x] << "- subscripting" << endl;
//         cout << m_pairs.at(x) << "- calling at member" << endl;
   }


   emit sendVectorString(m_pairs);
}

