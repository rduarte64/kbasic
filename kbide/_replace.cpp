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

#include "_replace.h"
#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"
#include "../kbshared/typedef.h"

class _mainwindow;

extern _mainwindow *EXTERN_my_mainwindow;

QStringList replace_list;
QStringList replace_list2;

bool bReplace_MatchCase = false;
bool bReplace_MatchWhole = false;
bool bReplace_SearchUp = false;
bool bReplace_SelectionOnly = false;
bool bReplace_RegEx = false;

_replace::_replace(_sourcecodeeditor *_my_sourcecodeeditor) : QDialog((QWidget *) EXTERN_my_mainwindow)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);

  setObjectName("Replace");

  my_sourcecodeeditor = _my_sourcecodeeditor;

  setWindowTitle(tr("Replace"));
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
 
  search = new QComboBox(); _tt->addWidget(search);
  
  search->setMinimumWidth(200);
  search->setEditable(true);
  search->setInsertPolicy(QComboBox::NoInsert);
  _tt->setStretchFactor(search, 10);

  QTextCursor f = my_sourcecodeeditor->my_sourcecodeeditor_editor->textCursor(); 
  QString r = f.selectedText();
  if (!r.contains(QString(QChar(0x2029)))) search->setEditText(r);

  for ( QStringList::Iterator it = replace_list.begin(); it != replace_list.end(); ++it ) {
     search->addItem(*it);      
  }
  setFocusProxy(search);


  QHBoxLayout *_tt2 = new QHBoxLayout();  
  grid->addLayout(_tt2, 1, 0);

  QLabel *l2;
  l2 = new QLabel(tr("Replace with:")); _tt2->addWidget(l2);
 
  search2 = new QComboBox(); _tt2->addWidget(search2);
  
  search2->setMinimumWidth(200);
  search2->setEditable(true);
  search2->setInsertPolicy(QComboBox::NoInsert);
  _tt2->setStretchFactor(search2, 10);
  
  for ( QStringList::Iterator it = replace_list2.begin(); it != replace_list2.end(); ++it ) {
     search2->addItem(*it);      
  }
  
  QVBoxLayout *_tab1 = new QVBoxLayout();



  matchCase = new QCheckBox(tr("Match case")); _tab1->addWidget(matchCase); matchCase->setChecked(bReplace_MatchCase);
  matchWhole = new QCheckBox(tr("Match whole word only")); _tab1->addWidget(matchWhole); matchWhole->setChecked(bReplace_MatchWhole);
  searchUp = new QCheckBox(tr("Search up")); _tab1->addWidget(searchUp); searchUp->setChecked(bReplace_SearchUp);
  selectionOnly = new QCheckBox(tr("Selection only")); _tab1->addWidget(selectionOnly);
  regex = new QCheckBox(tr("Regular Expression")); _tab1->addWidget(regex); regex->setChecked(bReplace_RegEx);


  grid->addLayout(_tab1, 2, 0);


  QPushButton *p;
  p = pFindNext = new QPushButton(tr("&Find next"));
  grid->addWidget(p, 0, 2);
  connect(p, SIGNAL( clicked() ), this, SLOT(findNext()) );

  p = pReplace = new QPushButton(tr("&Replace"));
  grid->addWidget(p, 1, 2);
  connect(p, SIGNAL( clicked() ), this, SLOT(replace()) );

  p = new QPushButton(tr("Replace &All"));
  
  grid->addWidget(p, 2, 2);
  connect(p, SIGNAL( clicked() ), this, SLOT(replaceAll()) );

  p = new QPushButton(tr("&Close"));
  grid->addWidget(p, 3, 2);
  connect(p, SIGNAL( clicked() ), this, SLOT(close()) );

  connect(selectionOnly, SIGNAL(toggled(bool)), this, SLOT(toggled(bool)));
  selectionOnly->setChecked(bReplace_SelectionOnly);

  if (r.contains(QString(QChar(0x2029)))){
    selectionOnly->setChecked(true);
  }

  if (QApplication::desktop()->width() > 800){
    move(500, 30);
  } else {
    move(300, 30);
  }

  show();

  this->activateWindow();
  this->setFocus();

}

_replace::~_replace()
{
  bReplace_MatchCase = matchCase->isChecked();
  bReplace_MatchWhole = matchWhole->isChecked();
  bReplace_SearchUp = searchUp->isChecked();
  bReplace_SelectionOnly = selectionOnly->isChecked();
  bReplace_RegEx = regex->isChecked();
  
}

void _replace::toggled(bool bChecked)
{
  if (bChecked){
    pFindNext->setDisabled(true);
    pReplace->setDisabled(true);
  } else {
    pFindNext->setDisabled(false);
    pReplace->setDisabled(false);
  }
}

bool _replace::findNext(bool bReplaceAll, int *nSelectionLength)
{
  bool bNotFoundAtAll = false;
  static QString sLastSearch = "";
  if (nSelectionLength) *nSelectionLength = 0;
goo:
  qApp->processEvents();
  QString s = search->currentText();
  bool bMatchCase = matchCase->isChecked();
  bool bMatchWhole = matchWhole->isChecked();
  bool bSearchUp = searchUp->isChecked() & !bReplaceAll;
  bool bSelectionOnly = selectionOnly->isChecked();
  bool bRegEx = regex->isChecked();

  QTextDocument *d = my_sourcecodeeditor->my_sourcecodeeditor_editor->document();

  QTextCursor c = my_sourcecodeeditor->my_sourcecodeeditor_editor->textCursor();

  int nFlag = 0;
  if (bMatchCase) nFlag |= QTextDocument::FindCaseSensitively;
  if (bMatchWhole) nFlag |= QTextDocument::FindWholeWords;
  if (bSearchUp) nFlag |= QTextDocument::FindBackward;

  if (bSearchUp){
    int k = c.selectedText().length();
    c.clearSelection();
    c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, k);
  } 

  //QString ss = c.selectedText();
  int nSelectionStart = c.selectionStart();
  int nSelectionEnd = c.selectionEnd();

  if (bSelectionOnly){
    if (nSelectionStart == nSelectionEnd) return false;
    if (bRegEx){    
      c = d->find(QRegExp(s), nSelectionStart, (QTextDocument::FindFlag) nFlag);
    } else {
      c = d->find(s, nSelectionStart, (QTextDocument::FindFlag) nFlag);
    }  
  } else {
    if (bRegEx){    
      c = d->find(QRegExp(s), c, (QTextDocument::FindFlag) nFlag);
    } else {
      c = d->find(s, c, (QTextDocument::FindFlag) nFlag);
    }  

  }

  if (c.hasSelection() && (!bSelectionOnly || (c.position() >= nSelectionStart && c.position() <= nSelectionEnd))){
    
    if (bSelectionOnly){
      if (nSelectionLength) *nSelectionLength = c.selectedText().length();
    }

    sLastSearch = s;

    if (bSearchUp){
      int k = c.selectedText().length();
      c.clearSelection();
      c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, k);
    } 
    my_sourcecodeeditor->my_sourcecodeeditor_editor->setTextCursor(c);

    QStringList::Iterator it = replace_list.begin();
    if (replace_list.count() == 0 || *it != s){
      if (s.trimmed().length()){
        search->insertItem(0, s);
        search->setCurrentIndex(0);
        replace_list.prepend(s);
      }
    }
  } else {

    if (bReplaceAll){
    } else {
      if (!bNotFoundAtAll && !bReplaceAll && QMessageBox::question(this, tr("Replace"), 
        bSearchUp ?
        tr("Search for '%1' reached beginning of file.\nWould you like to start search from the end of the document?").arg(s)
        : 
        tr("Search for '%1' reached end of file.\nWould you like to start search from the beginning of the document?").arg(s),
  //      tr("'%1' has not been found till end of file.\nWould you like to start search from the beginning?").arg(s), 
        
        QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
        QTextCursor c = my_sourcecodeeditor->my_sourcecodeeditor_editor->textCursor();
        if (bSearchUp){
          c.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
          c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
        } else {
          c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
          c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
        }
        my_sourcecodeeditor->my_sourcecodeeditor_editor->setTextCursor(c);

        bNotFoundAtAll = true;

        goto goo;
      } else {
        if (sLastSearch != s && !bReplaceAll) QMessageBox::information(this, tr("Replace"), 
          bSearchUp ?
          tr("'%1' has not been found until beginning of file.").arg(s)
          :
          tr("'%1' has not been found until end of file.").arg(s), 
          QMessageBox::Close);
      }    
    }

    activateWindow();
 //   my_sourcecodeeditor->my_sourcecodeeditor_editor->setFocusPolicy(Qt::WheelFocus);


/*

    */
  }

/*
  if (c.hasSelection() == false){

    if (bReplaceAll){
    } else {
      QMessageBox::information(this, tr("Replace"), tr("'%1' has not been found until end of file.").arg(s), QMessageBox::Close);
      activateWindow();
    }

  } else {

    my_sourcecodeeditor->my_sourcecodeeditor_editor->setTextCursor(c);

    QStringList::Iterator it = replace_list.begin();
    if (replace_list.count() == 0 || *it != s){
      if (s.trimmed().length()){
        search->insertItem(0, s);
        search->setCurrentIndex(0);
        replace_list.prepend(s);
      }
    }
    
    QStringList::Iterator it = replace_list2.begin();
    if (replace_list2.count() == 0 || *it != s){
      if (s.trimmed().length()){
        search2->insertItem(0, s);
        search2->setCurrentIndex(0);
        list2.prepend(s);
      }
    }
  }
*/
  search->setFocus();
  my_sourcecodeeditor->activateWindow();

  return c.hasSelection();
}

void _replace::replace()
{
  QString s = search2->currentText();

  my_sourcecodeeditor->replace(s);
  if (findNext()){
    QStringList::Iterator it2 = replace_list2.begin();
    if (replace_list2.count() == 0 || *it2 != s){
      if (s.trimmed().length()){
        search2->insertItem(0, s);
        search2->setCurrentIndex(0);
        replace_list2.prepend(s);
      }
    }
  }
}

void _replace::replaceAll()
{
  QString s = search2->currentText();
  int nLength = s.length();

  QTextCursor c;

  int nSelectionLength = 0;
  int n = 0;
  bool bFirst = true;
  int nSelectionStart = 0;
  int nSelectionEnd = 0;

  do {

    c = my_sourcecodeeditor->my_sourcecodeeditor_editor->textCursor();

    if (my_sourcecodeeditor->replace(s)){
      n++;
 
      int m = nSelectionLength - nLength;

      c = my_sourcecodeeditor->my_sourcecodeeditor_editor->textCursor();
      c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, nSelectionStart);
      c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, nSelectionEnd - nSelectionStart - m);
      my_sourcecodeeditor->my_sourcecodeeditor_editor->setTextCursor(c);
     

    }
    bFirst = false;
    nSelectionStart = c.selectionStart();
    nSelectionEnd = c.selectionEnd();

  } while (findNext(true, &nSelectionLength));  

  if (n > 0){
    QStringList::Iterator it2 = replace_list2.begin();
    if (replace_list2.count() == 0 || *it2 != s){
      if (s.trimmed().length()){
        search2->insertItem(0, s);
        search2->setCurrentIndex(0);
        replace_list2.prepend(s);
      }
    }

    QMessageBox::information(this, tr("Replace"), tr("'%1' has been replaced %2 times.").arg(search->currentText()).arg(n), QMessageBox::Close);
    activateWindow();
  }


}

void _replace::close()
{
  accept();
}




