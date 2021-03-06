/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#include <QtGui>

#include "_findfile.h"
#include "_mainwindow.h"
#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"

#include "_findfilelist.h"
#include "../kbshared/typedef.h"

extern _mainwindow *EXTERN_my_mainwindow;
extern _findfilelist *EXTERN_findfilelist;

extern QDockWidget *EXTERN_FileFind;

QStringList findfile_list;
bool bFindFile_MatchCase = false;

QString sFindText;

_findfile::_findfile(QWidget *_parent) : QDialog(_parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);
  
  setObjectName("FindFile");

  my_mainwindow = (_mainwindow *) _parent;

  setWindowTitle(tr("Find In File"));
#ifdef LINUX
  setModal(true);
#else
  setModal(false);
#endif

  QGridLayout *grid = new QGridLayout();
  setLayout(grid);

  QHBoxLayout *_tt = new QHBoxLayout();  
  grid->addLayout(_tt, 0, 0);
  


  QLabel *l;
  l = new QLabel(tr("Search for:")); _tt->addWidget(l);

  
  search = new QComboBox(); 
  search->addItem("");
  search->setMinimumWidth(200);
  search->setEditable(true);
  search->setInsertPolicy(QComboBox::NoInsert);

  if (!sFindText.isEmpty() && !sFindText.contains(QString(QChar(0x2029)))){
    search->lineEdit()->setText(sFindText);
  }

  _tt->addWidget(search);

  _tt->setStretchFactor(search, 10);

  for ( QStringList::Iterator it = findfile_list.begin(); it != findfile_list.end(); ++it ) {
     search->addItem(*it);      
  }

  setFocusProxy(search);


  QVBoxLayout *_tab1 = new QVBoxLayout();


  matchCase = new QCheckBox(tr("Match case")); _tab1->addWidget(matchCase);
  matchCase->setChecked(bFindFile_MatchCase);

  grid->addLayout(_tab1, 1, 0);

  QPushButton *p;
  p = new QPushButton(tr("&Find In File"));
  grid->addWidget(p, 0, 2);
  connect(p, SIGNAL( clicked() ), this, SLOT(findNext()) );

  p = new QPushButton(tr("&Close"));
  grid->addWidget(p, 1, 2);//, AlignTop);
  connect(p, SIGNAL( clicked() ), this, SLOT(close()) );

  move(QApplication::desktop()->width() / 2 - sizeHint().width() / 2, QApplication::desktop()->height() / 2 - sizeHint().height() / 2);
  show();
//qApp->processEvents();

  this->activateWindow();
  this->setFocus();
//search->setFocus();


}

_findfile::~_findfile()
{
  bFindFile_MatchCase = matchCase->isChecked();
}

void _findfile::findNext()
{
  static bool bLock = false;

  if (bLock) return;
  bLock = true;


  QString s = search->currentText();
  bool bMatchCase = matchCase->isChecked();

  search->setFocus();


  if (s.simplified().length() == 0){
    bLock = false;
    return;
  }
  s = search->currentText();


  QStringList::Iterator it = findfile_list.begin();
  if (findfile_list.count() == 0 || *it != s){
    if (s.trimmed().length()){
      search->insertItem(0, s);
      search->setCurrentIndex(0);
      findfile_list.prepend(s);
    }
  }
  EXTERN_findfilelist->clear();
  EXTERN_FileFind->setHidden(false);  


  EXTERN_findfilelist->addItem(tr("Searching..."));  ;  

  int nHits = 0;
  int nFileHits = 0;
  int nSearchFiles = 0;

  QDir thisDir( EXTERN_my_mainwindow->getProjectPath() );	
  QFileInfoList files = thisDir.entryInfoList();

  QString k = "";
  if ( files.size() ) {
      
     QFileInfo fi;
	    for (int i = 0; i < files.size(); ++i) {
	      fi = files.at(i);

        if (fi.fileName() == "." || fi.fileName() == "..")
		        ; // nothing
		    else if ( fi.isSymLink()) {  }
        else if ( fi.isDir() ){ } 
        else {

          EXTERN_my_mainwindow->processGUI(100);

          QString z = fi.absoluteFilePath();

          if (!(z.endsWith(".kbasic", Qt::CaseInsensitive) || z.endsWith(".kbasic_form", Qt::CaseInsensitive) || z.endsWith(".kbasic_report", Qt::CaseInsensitive)
            || z.endsWith(".kbasic_class", Qt::CaseInsensitive) || z.endsWith(".kbasic_module", Qt::CaseInsensitive)
             || z.endsWith(".kbasic_menubar", Qt::CaseInsensitive) || z.endsWith(".kbasic_toolbar", Qt::CaseInsensitive))) continue;

          QFile f(z);
          if (!f.open(QFile::ReadOnly)){
             continue;
         }
         nSearchFiles++;

	       QTextStream t(&f);
         
         t.setCodec("UTF-8");
         t.setAutoDetectUnicode(true);
         t.setGenerateByteOrderMark(true);

         QString sText = t.readAll();
         sText = sText.replace("\r", "");
	       f.close();

         int yy = 0;
         // ignore property entries
         /*
          if (!(z.endsWith(".kbasic", Qt::CaseInsensitive)
            || z.endsWith(".kbasic_class", Qt::CaseInsensitive) || z.endsWith(".kbasic_module", Qt::CaseInsensitive)
         //   || z.endsWith(".kbasic_menubar", Qt::CaseInsensitive) || z.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)
            ))*/
          {
            int n = -1;
            if (z.endsWith(".kbasic_form", Qt::CaseInsensitive)) n = sText.indexOf("\nEnd Form"); 
            else if (z.endsWith(".kbasic_menubar", Qt::CaseInsensitive)) n = sText.indexOf("\nEnd MenuBar"); 
            else if (z.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)) n = sText.indexOf("\nEnd ToolBar"); 

            if (n >= 0){
            //  n = sText.lastIndexOf("End", n); 
              n = sText.indexOf("\n", n);
              yy = (sText.left(n)).count(s, bMatchCase ? Qt::CaseSensitive : Qt::CaseInsensitive) + 1;
              sText = sText.mid(n + 1);
            }  
          }

         int y = sText.count(s, bMatchCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
         nHits += y;

         int h = 0;
         int h2 = 0;
         int h3 = 0;

         for (int i = 0; i < y; i++){
           EXTERN_my_mainwindow->processGUI(100);

           if (i == 0){
             nFileHits++;
           } else {
             h++;
           }

          int nLine = 0;
          QString sHit = "";

           h = sText.indexOf(s, h, bMatchCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
           h2 = sText.lastIndexOf("\n", h);
           if (h2 == -1) h2 = 0;
           h3 = sText.indexOf("\n", h);
           if (h3 == -1) h3 = sText.length();

           QString d = sText.left(h2);
           if (!d.isEmpty()) nLine = d.count("\n") + 1 - yy;
           sHit = sText.mid(h2 + 1, h3 - h2);

            k = k.sprintf("(%d): ", nLine + 1);
            k = k.prepend(z);
            k += sHit;

            EXTERN_findfilelist->addItem(k);  

         }
        }
      }
  }
	   

  QString ss = "";

  ss = tr("Completed Search!   Hits: %1       File Hits: %2        Searched Files: %3").arg(nHits).arg(nSearchFiles).arg(nFileHits);
  EXTERN_findfilelist->addItem(ss); 

  accept();  

  bLock = false;


}

void _findfile::close()
{
  accept();
}




