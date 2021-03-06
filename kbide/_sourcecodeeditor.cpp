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

#include "_sourcecodeeditor.h"
#include "_sourcecodeeditor_editor.h"
#include "_sourcecodeeditor_syntaxhighlighter.h"
#include "_inputtip_parser.h"
#include "_inputtip.h"
#include "_parserwindow.h"


#include "_propertywindow.h"

#include "_mainwindow.h"
#include "_parserwindow.h"

#include "../kbshared/_form.h"
#include "../kbshared/_report.h"
#include "../kbshared/_menubar.h"
#include "../kbshared/_toolbar.h"

#include "_find.h"
#include "_replace.h"

#include "_quickcode.h"
#include "_globallist.h"
#include "_stacklist.h"
#include "_locallist.h"

extern _parserwindow *EXTERN_my_parserwindow;

extern QString kbasicPath(QString sPath);
extern _mainwindow *EXTERN_my_mainwindow;

_sourcecodeeditor *EXTERN_my_sourcecodeeditor;



extern _form *EXTERN_my_form;
extern _report *EXTERN_my_report;
extern _menubar *EXTERN_my_menubar;
extern _toolbar *EXTERN_my_toolbar;
/*
extern QDockWidget *EXTERN_ParserWindow;
extern QDockWidget *EXTERN_HelpWindow;
extern QDockWidget *EXTERN_PropertyWindow;
extern QDockWidget *EXTERN_ProjectWindow;
extern QDockWidget *EXTERN_ToolboxForm;
extern QDockWidget *EXTERN_ToolboxMenuBar;
extern QDockWidget *EXTERN_ToolboxToolBar;
extern QDockWidget *EXTERN_ToolboxSql;
extern QDockWidget *EXTERN_ToolboxReport;
*/
extern _propertywindow *EXTERN_my_propertywindow;

extern _quickcode *EXTERN_quickcode;

extern _globallist *EXTERN_globallist;
extern QDockWidget *EXTERN_Global;

extern _stacklist *EXTERN_stacklist;
extern QDockWidget *EXTERN_Stack;

extern _locallist *EXTERN_locallist;
extern QDockWidget *EXTERN_Local;


extern QDockWidget *EXTERN_FileFind;
extern QDockWidget *EXTERN_FileReplace;

extern QDockWidget *EXTERN_Quickcode;

extern QDockWidget *EXTERN_Helpwindow_shortcut;

extern _parserwindow *EXTERN_my_parserwindow;

extern int nPropertyWindowForWhat;

extern const QIcon &kbasicIcon(QString s);

QMap <QString, QString> map;
QMap <QString, QString> map3;


_sourcecodeeditor::_sourcecodeeditor()
{
  filename = "";
  
  setAttribute(Qt::WA_DeleteOnClose);


  bClassForm = false;
  bOLDFORMAT = false;
  bClosing = false;

  
  setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")));

  browser = new QComboBox(this); 
  browser->setMaxVisibleItems(12);
#ifdef MAC
  //QFont f = browser->font(); f.setPixelSize(10); browser->setFont(f); 
#endif
  //browser->setFrame(false);

  nBrowserUpdated = 0;
 
  sScope = "";
  sScope2 = "";
  sDot = "";


  createMap();

  connect(browser, SIGNAL(activated(int)), this, SLOT(activated(int)));

  my_sourcecodeeditor_editor = new _sourcecodeeditor_editor(this, this);
  my_sourcecodeeditor_editor->setTabChangesFocus(false);
  my_sourcecodeeditor_editor->setLineWrapMode(QTextEdit::NoWrap);
  my_sourcecodeeditor_editor->document()->setModified(true);

  setFocusProxy(my_sourcecodeeditor_editor);
  //browser->setFocusProxy(my_sourcecodeeditor_editor);

  browser->setFocusProxy(my_sourcecodeeditor_editor);


  updateCaption("");

  info = new QLabel(this);
  info->setText("");
  info->setMaximumWidth(120);
#ifdef MAC
  QFont f = info->font(); f.setPixelSize(10); info->setFont(f); 
#endif
/*
  window_extend = new QPushButton("");
  window_extend->setFlat(true);
  window_extend->setToolTip(tr("Enlarge Editor"));
  window_extend->setIcon(kbasicIcon(kbasicPath("ide/VIEW_ENLARGEEDITOR.png")));
  window_extend->setFixedSize(16, 16);
  connect(window_extend, SIGNAL(clicked()), this, SLOT(setWindow_extend()));
*/

  bFullscreen = false;  
  window_nofullscreen = new QPushButton("");
  window_nofullscreen->setFlat(true);
  window_nofullscreen->setToolTip(tr("FullScreen Mode On"));
  window_nofullscreen->setIcon(kbasicIcon(kbasicPath("ide/VIEW_FULLSCREEN.png")));
  window_nofullscreen->setCursor(Qt::PointingHandCursor);
  //window_nofullscreen->setEnabled(false);
  window_nofullscreen->setFixedSize(16, 16);
  connect(window_nofullscreen, SIGNAL(clicked()), this, SLOT(setNoFullscreen2()));

  

  events = new QPushButton("");
  events->setFlat(true);
  events->setToolTip(tr("Controls With Events"));
  events->setIcon(kbasicIcon(kbasicPath("ide/VIEW_EVENTS.png")));
  events->setFixedSize(16, 16);
  connect(events, SIGNAL(clicked()), this, SLOT(showEvents()));

  QBoxLayout *l = new QBoxLayout(QBoxLayout::TopToBottom);
  l->addSpacing(2);
  QBoxLayout *j = new QBoxLayout(QBoxLayout::LeftToRight);
  j->addWidget(events);
  j->addWidget(browser);
  j->addWidget(info);
  //j->addWidget(window_extend);
#ifdef WINDOWS
  j->addWidget(window_nofullscreen);
#endif
  //j->addItem(QSpacerItem(4, 16));
  j->setMargin(2);
  j->setSpacing(2);
  //l->setSpacing(5);

  l->addLayout(j);
/*
  QBoxLayout *k = new QBoxLayout(QBoxLayout::LeftToRight);
  QWidget *w = new QWidget();
  w->setFixedWidth(10);
  QPalette p = w->palette();
  p.setColor(QPalette::Window, Qt::white);  
  w->setPalette(p);


  k->addWidget(w);  
  l->addLayout(k);*/
  l->addSpacing(2);
  QHBoxLayout *ll = new QHBoxLayout();
  _border *w = new _border(this);
  w->setFixedWidth(4);
  w->setAutoFillBackground(true);
  
  QPalette p = w->palette();
  p.setColor(QPalette::WindowText, Qt::white);
  p.setColor(QPalette::Window, Qt::white);  
  w->setPalette(p);

  ll->addWidget(w);
  ll->addWidget(my_sourcecodeeditor_editor);  
  l->addLayout(ll);

  
  l->setMargin(0);
  l->setSpacing(0);
  setLayout(l);

/*
  QFrame *ff = new QFrame(this);
  setLayout(fff);
  fff->setMargin(0);
  fff->setSpacing(0);
  setLayout(fff);*/
  setFrameShape(QFrame::StyledPanel);
  //setFrameShadow(QFrame::Sunken);
  //setLineWidth(2);

  highlighter = new _sourcecodeeditor_syntaxhighlighter(my_sourcecodeeditor_editor->document());

  bookmarkFormat.setBackground(Qt::yellow);
  breakpointFormat.setBackground(Qt::red);
  currentLineFormat.setBackground(Qt::lightGray);

  connect(my_sourcecodeeditor_editor, SIGNAL(copyAvailable(bool)), this, SLOT(copyAvailable(bool)));
  connect(my_sourcecodeeditor_editor, SIGNAL(redoAvailable(bool)), this, SLOT(redoAvailable(bool)));
  connect(my_sourcecodeeditor_editor, SIGNAL(undoAvailable(bool)), this, SLOT(undoAvailable(bool)));
  connect(my_sourcecodeeditor_editor, SIGNAL(textChanged()), this, SLOT(textChanged()));   

  bCanUndo = false;
  bCanRedo = false;
  bCanCopy = false;

  nOldBlock = -1;

  bBrowserNeedsUpdate = false;

  bCTRL = false;
  bSHIFT = false;

  nTimerBrowserNeedsUpdate = startTimer(3000);
  //move(10, 10);
  //if (parent()) ((QWidget *) parent())->
    resize(600, 450);  
}

_sourcecodeeditor::~_sourcecodeeditor()
{
  killTimer(nTimerBrowserNeedsUpdate);
}

void _sourcecodeeditor::setSyntaxHighlighting(bool b)
{
  bSyntaxHighlighting = b;
  highlighter->setSyntaxHighlighting(b);
}

void _sourcecodeeditor::updateBrowser()
{  
  killTimer(nTimerBrowserNeedsUpdate);
  nTimerBrowserNeedsUpdate = startTimer(3000);
}

void _sourcecodeeditor::cursorPositionChanged(void)
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  int nBlock = c.blockNumber() + 1;
  QString s = tr("     L %1         C %2").arg(nBlock).arg(c.columnNumber() + 1);
  info->setText(s);

  if (nOldBlock != nBlock) updateExtraSelections();
  nBlock = nOldBlock;

  
//  EXTERN_my_mainwindow->statusBar()->showMessage(getScope() + "." + getScope2());
}

void _sourcecodeeditor::activated(int index)
{
  QVariant v = browser->itemData(index);
  int n = v.toInt();
  int l = n / 1000;
  int c = n % 1000;

  if (l && n > 0){

    nBrowserUpdated = 1;
    setCurrentLineAndSelectLine(l);
    setFocus();
  }
}

void _sourcecodeeditor::setCurrentLineAndSelectLine(int line)
{  
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line - 5);
  c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);  
  my_sourcecodeeditor_editor->setTextCursor(c);

  c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line + 5);
  c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);  
  my_sourcecodeeditor_editor->setTextCursor(c);

  c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line - 1);
  //c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);  
  //c.select(QTextCursor::LineUnderCursor);
  c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
  my_sourcecodeeditor_editor->setTextCursor(c);  
//  setFocus();
  
}

void _sourcecodeeditor::updatingBrowser()
{
  if (bBrowserNeedsUpdate){
    static int nUpdateCounter = 0;
    static bool bLock = false;

    if (bLock){
      nUpdateCounter++;
      return;
    }
  re:
    bLock = true;

    EXTERN_my_mainwindow->ci_parse(getFilename(), my_sourcecodeeditor_editor->document()->toPlainText());
    if (bClosing){
      bLock = false;
      return;
    }

    bBrowserNeedsUpdate = false;

    QString sCurrentText = browser->currentText();
    
    browser->clear();
    browser->addItem ("", QVariant(-1)); 


    static QStringList l;
    
    if (l.count() == 0){
 //     l << "Public Static Sub" << "Static Function";
      
      l << "Public Property" << "Public Sub" << "Public Function" << "Public Signal" << "Public Slot" << "Public Event" << "Public Static Sub" << "Public Static Function" << "Public Sub Static" << "Public Function Static";
      l << "Protected Property" << "Protected Sub" << "Protected Function" << "Protected Signal" << "Protected Slot" << "Protected Event" << "Protected Static Sub" << "Protected Static Function" << "Protected Sub Static" << "Protected Function Static";
      l << "Private Property" << "Private Sub" << "Private Function" << "Private Signal" << "Private Slot" << "Private Event" << "Private Static Sub" << "Private Static Function" << "Private Sub Static" << "Private Function Static";
      l << "Property" << "Sub" << "Function" << "Signal" << "Slot" << "Event" << "Static Sub" << "Static Function" << "Sub Static" << "Function Static";
      l << "Constructor" << "Destructor";
      
      l << "PUBLIC PROPERTY" << "PUBLIC SUB" << "PUBLIC FUNCTION" << "PUBLIC SIGNAL" << "PUBLIC SLOT" << "PUBLIC EVENT" << "PUBLIC STATIC SUB" << "PUBLIC STATIC FUNCTION" << "PUBLIC SUB STATIC" << "PUBLIC FUNCTION STATIC";
      l << "PROTECTED PROPERTY" << "PROTECTED SUB" << "PROTECTED FUNCTION" << "PROTECTED SIGNAL" << "PROTECTED SLOT" << "PROTECTED EVENT" << "PROTECTED STATIC SUB" << "PROTECTED STATIC FUNCTION" << "PROTECTED SUB STATIC" << "PROTECTED FUNCTION STATIC";
      l << "PRIVATE PROPERTY" << "PRIVATE SUB" << "PRIVATE FUNCTION" << "PRIVATE SIGNAL" << "PRIVATE SLOT" << "PRIVATE EVENT" << "PRIVATE STATIC SUB" << "PRIVATE STATIC FUNCTION" << "PRIVATE SUB STATIC" << "PRIVATE FUNCTION STATIC";
      l << "PROPERTY" << "SUB" << "FUNCTION" << "SIGNAL" << "SLOT" << "EVENT" << "STATIC SUB" << "STATIC FUNCTION" << "SUB STATIC" << "FUNCTION STATIC";
      l << "CONSTRUCTOR" << "DESTRUCTOR";
      
    }
    
    foreach(QString s, l){
      if (bClosing){
        bLock = false;
        return;
      }

      qApp->processEvents(QEventLoop::AllEvents, 100);

     // s += " \\b[A-Za-z0-9_]+(?=\\()";
      s += " \\b[A-Za-z0-9_]*";
      QRegExp e(s);

      int n = 0;
      QTextCursor c;
      
      do {
        if (bClosing){
          bLock = false;
          return;
        }
        qApp->processEvents(QEventLoop::AllEvents, 100);

        QTextDocument *d = my_sourcecodeeditor_editor->document();
        c = d->find(e, n);
 
        if (!c.hasSelection()) break;
        n = c.position() + 1;
 
        QString s = tr("%1").arg(c.selectedText());
        QString k = "";

/*       
//        QTextCursor bbb = QTextCursor(textBlock);
        //QTextBlock textBlock2 = bbb.block();//d->findBlock(c.position());
        int ggg2 = c.blockNumber();
        QTextBlock textBlock = c.block();//d->findBlock(c.position());d->findBlock(ggg2);//
         

        int ggg = textBlock.blockFormatIndex();
        int mm = textBlock.userState();
        int mm444 = d->blockCount();
//        QString ss = textBlock.text(); // get the line to the selection
        //QTextCharFormat f = textBlock.charFormat();
        QTextCharFormat f = c.charFormat();
        QColor cc = f.foreground().color();
        int gg = f.foreground().color().green();
        if (f.foreground().color() == Qt::darkGreen) break; // match inside comment
       // f.setFontUnderline(true);
      //  f.setUnderlineStyle(QTextCharFormat::WaveUnderline);
      */  

        if (s.indexOf("Sub", 0, Qt::CaseInsensitive) >= 0){ 
          if (!s.startsWith("_") && s.contains("_On")){
            k = kbasicPath("ide/Event.png"); s.replace("Sub ", "", Qt::CaseInsensitive); 
          } else {
            k = kbasicPath("ide/Sub.png"); s.replace("Sub ", "", Qt::CaseInsensitive); 
          }
        }
        else if (s.indexOf("Function", 0, Qt::CaseInsensitive) >= 0){ k = kbasicPath("ide/Function.png"); s.replace("Function ", "", Qt::CaseInsensitive); }
        else if (s.indexOf("Signal", 0, Qt::CaseInsensitive) >= 0){ k = kbasicPath("ide/Signal.png"); s.replace("Signal ", "", Qt::CaseInsensitive); }
        else if (s.indexOf("Slot", 0, Qt::CaseInsensitive) >= 0){ k = kbasicPath("ide/Slot.png"); s.replace("Slot ", "", Qt::CaseInsensitive); }
        else if (s.indexOf("Event", 0, Qt::CaseInsensitive) >= 0){ k = kbasicPath("ide/Event.png"); s.replace("Event ", "", Qt::CaseInsensitive); }
        else if (s.indexOf("Constructor", 0, Qt::CaseInsensitive) >= 0){ k = kbasicPath("ide/Constructor.png"); s.replace("Constructor ", "", Qt::CaseInsensitive); }
        else if (s.indexOf("Destructor", 0, Qt::CaseInsensitive) >= 0){ k = kbasicPath("ide/Destructor.png"); s.replace("Destructor ", "", Qt::CaseInsensitive); }
        else if (s.indexOf("Property", 0, Qt::CaseInsensitive) >= 0){ k = kbasicPath("ide/Property.png"); s.replace("Property ", "", Qt::CaseInsensitive); }



        s.replace("Public ", "", Qt::CaseInsensitive);
        s.replace("Protected ", "", Qt::CaseInsensitive);
        s.replace("Private ", "", Qt::CaseInsensitive);
        s.replace("Static ", "", Qt::CaseInsensitive);

        s = s.trimmed();

        QVariant v((c.blockNumber() + 1) * 1000 + (c.columnNumber() + 1));

        if (browser->findData(v) == -1) browser->addItem (kbasicIcon(k), s, v); 
      } while (true);
    }


    static QStringList j;
    
    if (j.count() == 0){
      j << "Public Enum" << "Public Type";
      j << "Private Enum" << "Private Type";
      j << "Enum" << "Type";

      j << "PUBLIC ENUM" << "PUBLIC TYPE";
      j << "PRIVATE ENUM" << "PRIVATE TYPE";
      j << "ENUM" << "TYPE";
    }
    
    foreach(QString s, j){
      if (bClosing){
        bLock = false;
        return;
      }
      qApp->processEvents(QEventLoop::AllEvents, 100);

      s += " \\b[A-Za-z0-9_]+";
      QRegExp e(s);

      int n = 0;
      QTextCursor c;
      
      do {
        c = my_sourcecodeeditor_editor->document()->find(e, n);

        if (!c.hasSelection()) break;
        n = c.position() + 1;
      
        QString s = tr("%1").arg(c.selectedText());
        QString k = "";

        if (s.indexOf("Enum", 0, Qt::CaseInsensitive) >= 0){ k = kbasicPath("ide/Enum.png"); s.replace("Enum ", ""); }
        else if (s.indexOf("Type", 0, Qt::CaseInsensitive) >= 0){ k = kbasicPath("ide/Type.png"); s.replace("Type ", ""); }

        s.replace("Public ", "", Qt::CaseInsensitive);
        s.replace("Private ", "", Qt::CaseInsensitive);

        s = s.trimmed();

        browser->addItem (kbasicIcon(k), s, QVariant((c.blockNumber() + 1) * 1000 + (c.columnNumber() + 1))); 
      } while (true);
    }

    if (sCurrentText.length()){
      int nIndex = browser->findText(sCurrentText);;
      if (nIndex) browser->setCurrentIndex(nIndex);
    }

   // browser->setEnabled(browser->count());
    
    nPropertyWindowForWhat = 4; EXTERN_my_propertywindow->showProperties(true, getFilename()); // update tree view with parser info

    if (EXTERN_my_parserwindow) EXTERN_my_parserwindow->refreshProject();

    bLock = false;

    if (nUpdateCounter > 0){
      nUpdateCounter = 0;
      goto re;
    }

  }
}

void _sourcecodeeditor::timerEvent(QTimerEvent *event)
{
//return;
  if (bBrowserNeedsUpdate){ 
    updatingBrowser();
    createMap3();
    bBrowserNeedsUpdate = false;
  }
  if (event->timerId() == nTimerBrowserNeedsUpdate){
    updateBrowser();
  }
}

void _sourcecodeeditor::createMap3()
{
  static int nUpdateCounter = 0;
  static bool bLock = false;

  if (bLock){
    nUpdateCounter++;
    return;
  }
re:
  bLock = true;

  map3.clear();

  QList<_inputtip_info>l;
  int i;

  l = EXTERN_my_mainwindow->ci_getAsForFile(getFilename(), "999"); // 999 special keyword, getting all
  i = 0;
  foreach (_inputtip_info v, l){ 
    if (bClosing){
      bLock = false;
      return;
    }
    QString s = v.name;
    map3.insert(s, s);
    map3.insert(s.toLower(), s);
    map3.insert(s.toUpper(), s);

    if (i++ % 10 == 0) qApp->processEvents(QEventLoop::AllEvents, 100);
  }

  l = EXTERN_my_mainwindow->ci_getDotForFile(getFilename(), "", "", "999"); // 999 special keyword, getting all
  i = 0;
  foreach (_inputtip_info v, l){ 
    if (bClosing){
      bLock = false;
      return;
    }
    QString s = v.name;
    map3.insert(s, s);
    map3.insert(s.toLower(), s);
    map3.insert(s.toUpper(), s);

    if (i++ % 10 == 0) qApp->processEvents(QEventLoop::AllEvents, 100);
  }

  bLock = false;

  if (nUpdateCounter > 0){
    nUpdateCounter = 0;
    goto re;
  }

}

void _sourcecodeeditor::performUndo()
{
  my_sourcecodeeditor_editor->undo();
}

void _sourcecodeeditor::performRedo()
{
  my_sourcecodeeditor_editor->redo();
}

void _sourcecodeeditor::performCut()
{
  my_sourcecodeeditor_editor->cut();
}

void _sourcecodeeditor::performCopy()
{
  my_sourcecodeeditor_editor->copy();
}

void _sourcecodeeditor::performPaste()
{
  my_sourcecodeeditor_editor->paste();
}

void _sourcecodeeditor::performDelete()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  if (c.hasSelection()){

    c.beginEditBlock();

    c.insertText("");

    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

  } else {
  } 
}

void _sourcecodeeditor::performSelectAll()
{
  my_sourcecodeeditor_editor->selectAll();
}

void _sourcecodeeditor::performComment()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  if (c.hasSelection()){

    c.beginEditBlock();

    int a = c.selectionStart();
    int b = c.selectionEnd();

    int cpos = c.position();
    bool bAtStart = false;

    if (cpos == a){
      c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);

      c.clearSelection();
      if (c.blockNumber() == 0){
        bAtStart = true;
        c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
      } else {
        c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
        c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
      }
      c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, b - c.position());

    } else {
      c.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, b - a);
      c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);

      c.clearSelection();
      if (c.blockNumber() == 0){
        bAtStart = true;
        c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
      } else {
        c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
        c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
      }
      c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, b - c.position());

    }
    
    QString s = c.selectedText();

    QString cr = QString(QChar(0x2029));
    
    int n = s.count(cr);

    s.replace(cr, cr + "'");

    if (bAtStart){
      s = "'" + s;
    }
    c.insertText(s);

    c.clearSelection();

    // the following line didn't works, seems to be a bug in Qt4.2
    //c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, (c.position() - a - n));

    c.endEditBlock();
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

    my_sourcecodeeditor_editor->setTextCursor(c);

  } else {
  } 
}

void _sourcecodeeditor::performUncomment()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  if (c.hasSelection()){

    c.beginEditBlock();

    int a = c.selectionStart();
    int b = c.selectionEnd();
    
    c.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, b - a);
    c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    c.clearSelection();
    bool bAtStart = false;
    if (c.blockNumber() == 0){
      bAtStart = true;
      c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    } else {
      c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
    }
    c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, b - c.position());

    QString s = c.selectedText();

    QString cr = QString(QChar(0x2029));
    
    int n = s.count(cr);

    if (s.contains(cr + "'")) s.replace(cr + "'", cr);
    else if (s.contains(cr + " '")) s.replace(cr + " '", cr + " ");
    else if (s.contains(cr + "  '")) s.replace(cr + "  '", cr + "  ");
    else if (s.contains(cr + "   '")) s.replace(cr + "   '", cr + "   ");
    else if (s.contains(cr + "    '")) s.replace(cr + "    '", cr + "    ");
    else if (s.contains(cr + "     '")) s.replace(cr + "     '", cr + "     ");
    else if (s.contains(cr + "      '")) s.replace(cr + "      '", cr + "      ");
    else if (s.contains(cr + "       '")) s.replace(cr + "       '", cr + "       ");
    else if (s.contains(cr + "        '")) s.replace(cr + "        '", cr + "        ");
    else if (s.contains(cr + "         '")) s.replace(cr + "         '", cr + "         ");
    else if (s.contains(cr + "          '")) s.replace(cr + "          '", cr + "          ");
    else if (s.contains(cr + "           '")) s.replace(cr + "           '", cr + "           ");
    else if (s.contains(cr + "            '")) s.replace(cr + "            '", cr + "            ");
    else if (s.contains(cr + "             '")) s.replace(cr + "             '", cr + "             ");
    else if (s.contains(cr + "              '")) s.replace(cr + "              '", cr + "              ");
    else if (s.contains(cr + "               '")) s.replace(cr + "               '", cr + "               ");
    else if (s.contains(cr + "                '")) s.replace(cr + "                '", cr + "                ");
    else if (s.contains(cr + "                 '")) s.replace(cr + "                 '", cr + "                 ");
    else if (s.contains(cr + "                  '")) s.replace(cr + "                  '", cr + "                  ");

    else if (bAtStart){
      if (s.startsWith("' ")) s = s.mid(2);
    }

    c.insertText(s);

    c.clearSelection();

    // the following line didn't work, seems to be a bug in Qt4.2
    //c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, (c.position() - a - n));

    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

  } else {
  } 
}

void _sourcecodeeditor::performIndent()
{
  if (!this->hasFocus()) return;

  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  if (c.hasSelection()){


    int a = c.selectionStart();
    int b = c.selectionEnd();
    int nn = 0;

    int cpos = c.position();

    if (cpos == a){

      c.beginEditBlock();

      c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
      c.clearSelection();
      c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
      nn = b - c.position();
      c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, b - c.position());

    } else {
 
      c.beginEditBlock();

      c.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, b - a);
      c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
      c.clearSelection();
      c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
      nn = b - c.position();
      c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, nn);
      
    }
    
    QString s = c.selectedText();

    QString cr = QString(QChar(0x2029));
    
    int n = s.count(cr);

    s.replace(cr, cr + "  ");

    c.insertText(s);

    c.clearSelection();

    // the following line didn't works, seems to be a bug in Qt4.2
    //c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, (c.position() - a - n));

    c.endEditBlock();

    c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, nn);


    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

  } else {

    c.beginEditBlock();

    c.insertText("  ");

   // c.clearSelection();

    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually
  } 
}

void _sourcecodeeditor::performUnindent()
{
  if (!this->hasFocus()) return;

  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  if (c.hasSelection()){

    c.beginEditBlock();

    int a = c.selectionStart();
    int b = c.selectionEnd();

    int nn = 0;
    
    int cpos = c.position();

    if (cpos == a){

      c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
      c.clearSelection();
      c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
      nn = b - c.position();
      c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, b - c.position());

    } else {

      c.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, b - a);
      c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
      c.clearSelection();
      c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
      nn = b - c.position();
      c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, b - c.position());

    }

    QString s = c.selectedText();

    QString cr = QString(QChar(0x2029));
    
    int n = s.count(cr);

    s.replace(cr + "  ", cr);

    c.insertText(s);

    c.clearSelection();

    // the following line didn't work, seems to be a bug in Qt4.2
    //c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, (c.position() - a - n));

    c.endEditBlock();

    c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, nn - n * 2);

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

  } else {

    c.beginEditBlock();

    c.deletePreviousChar();
    c.deletePreviousChar();

   // c.clearSelection();

    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually
  } 
}

void _sourcecodeeditor::performMark()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  if (c.hasSelection()){

    c.beginEditBlock();

    int a = c.selectionStart();
    int b = c.selectionEnd();
    
    int cpos = c.position();

    if (cpos == a){

      //c.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, b - a);
      c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
      c.clearSelection();
      c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, b - c.position());

    } else {

      c.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, b - a);
      c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
      c.clearSelection();
      c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
      c.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, b - c.position());

    }

    QString s = c.selectedText();

    QString cr = QString(QChar(0x2029));
    
    int n = s.count(cr);

    s.replace(cr, cr + "~ ");

    c.insertText(s);

    //c.clearSelection();

    // the following line didn't works, seems to be a bug in Qt4.2
    //c.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, (c.position() - a - n));

    c.endEditBlock();
    

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

  } else {
  } 
}

void _sourcecodeeditor::performUpper()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  if (c.hasSelection()){

    c.beginEditBlock();

    QString s = c.selectedText();

    QString cr = QString(QChar(0x2029));

    c.insertText(s.toUpper());

    c.clearSelection();

    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

  } else {
  } 
}

void _sourcecodeeditor::performLower()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  if (c.hasSelection()){

    c.beginEditBlock();

    QString s = c.selectedText();

    QString cr = QString(QChar(0x2029));

    c.insertText(s.toLower());

    c.clearSelection();

    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

  } else {
  } 
}

void _sourcecodeeditor::performInsertFile()
{
  QString s = QFileDialog::getOpenFileName(this, tr("Open File"), QString::null, tr("Source Codes (*.kbasic *.bas *.kbasic_class *.kbasic_module *.txt)"));
  if (!s.isEmpty()){

    QFile f(s);
    if (!f.open(QIODevice::ReadOnly)){
      QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(s));
      return;
    }

	  QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s = s.replace("\r", "");
	  f.close();

    QTextCursor c = my_sourcecodeeditor_editor->textCursor();

    c.beginEditBlock();

    c.insertText(s);
    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually
  
  }
}

void _sourcecodeeditor::performInsertText(QString s)
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  c.beginEditBlock();

  c.insertText(s);
  //c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
  c.endEditBlock();

  my_sourcecodeeditor_editor->setTextCursor(c);
  my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually
}

void _sourcecodeeditor::performGotoLine()
{
  bool b;

  int min = 1;
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  int max = c.blockNumber() + 1;

  QString s = tr("Lines (%1 - %2):").arg(min).arg(max);

  s = QInputDialog::getText(this, tr("Go To Line"), s, QLineEdit::Normal, "", &b);
  if (b && !s.isEmpty()){
    int n = s.toInt();
    if (n >= min && n <= max){
      setCurrentLineAndSelectLine(n);
    }
  }
}
/*
bool _sourcecodeeditor::canUndo()
{
  return bCanUndo;
}

bool _sourcecodeeditor::canRedo()
{
  return bCanRedo;
}

bool _sourcecodeeditor::canPaste()
{
  return my_sourcecodeeditor_editor->canPaste();
}

bool _sourcecodeeditor::canCopy()
{
  return bCanCopy;
}
*/
void _sourcecodeeditor::copyAvailable(bool b)
{
  bCanCopy = b;  
  //EXTERN_my_mainwindow->EDIT_FINDDEFINITION->setEnabled(b);
  EXTERN_my_mainwindow->EDIT_CUT->setEnabled(b);
  EXTERN_my_mainwindow->EDIT_COPY->setEnabled(b);
  EXTERN_my_mainwindow->EDIT_PASTE->setEnabled(my_sourcecodeeditor_editor->canPaste());
  EXTERN_my_mainwindow->EDIT_DELETE->setEnabled(b);
  EXTERN_my_mainwindow->EDIT_COMMENT_LINES->setEnabled(b);
  EXTERN_my_mainwindow->EDIT_UNCOMMENT_LINES->setEnabled(b);
  EXTERN_my_mainwindow->EDIT_UNINDENT_LINES->setEnabled(b);
  EXTERN_my_mainwindow->EDIT_MARK_LINES->setEnabled(b);
  EXTERN_my_mainwindow->EDIT_UPPER->setEnabled(b);
  EXTERN_my_mainwindow->EDIT_LOWER->setEnabled(b);
}

void _sourcecodeeditor::redoAvailable(bool b)
{
  bCanRedo = b;
  EXTERN_my_mainwindow->EDIT_REDO->setEnabled(b);
}

void _sourcecodeeditor::undoAvailable(bool b)
{
  bCanUndo = b;
  EXTERN_my_mainwindow->EDIT_UNDO->setEnabled(b);
}

bool _sourcecodeeditor::setUnsetBookmarkSelection()
{

  QTextEdit::ExtraSelection e;

  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  c.select(QTextCursor::LineUnderCursor);
  int n = c.blockNumber();

  for (int i = 0; i < bookmarks.size(); i++){
    e = bookmarks[i];
    int k = e.cursor.blockNumber();
    if (k == n){
      bookmarks.removeAt(i);
      updateExtraSelections();  
      return false;
    }
  } 

  e.cursor = c;
  e.format = bookmarkFormat;

  bookmarks.append(e);

  updateExtraSelections();  
  return true;
}

void _sourcecodeeditor::clearBookmarkSelection()
{
  bookmarks.clear();
  updateExtraSelections();  
}

QString _sourcecodeeditor::getBreakpointsAsString()
{
  QString s = "";
  QTextEdit::ExtraSelection e;

  for (int i = 0; i < breakpoints.size(); i++){
    e = breakpoints[i];
    int k = e.cursor.blockNumber();

    if (this->getFilename().endsWith(".kbasic_form", Qt::CaseInsensitive)) k++; // add extra line
    else if (this->getFilename().endsWith(".kbasic_report", Qt::CaseInsensitive)) k++; // add extra line
    else if (this->getFilename().endsWith(".kbasic_menubar", Qt::CaseInsensitive)) k++; // add extra line
    else if (this->getFilename().endsWith(".kbasic_toolbar", Qt::CaseInsensitive)) k++; // add extra line

    s = s + QString("%1").arg(k + 1);
    s = s + ",";
  } 

  return s;
}

bool _sourcecodeeditor::setUnsetBreakpointSelection()
{

  QTextEdit::ExtraSelection e;

  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  c.select(QTextCursor::LineUnderCursor);
  int n = c.blockNumber();

  for (int i = 0; i < breakpoints.size(); i++){
    e = breakpoints[i];
    int k = e.cursor.blockNumber();
    if (k == n){
      breakpoints.removeAt(i);
      updateExtraSelections();  
      return false;
    }
  } 

  e.cursor = c;
  e.format = breakpointFormat;

  breakpoints.append(e);

  updateExtraSelections();  
  return true;
}

void _sourcecodeeditor::clearBreakpointSelection()
{
  breakpoints.clear();
  updateExtraSelections();  
}

void _sourcecodeeditor::updateExtraSelections()
{
  allExtraSelections.clear();

  allExtraSelections += bookmarks;
  allExtraSelections += breakpoints;

  /*
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  if (!c.hasSelection()){
    QTextEdit::ExtraSelection e;
    c.select(QTextCursor::LineUnderCursor);
    e.cursor = c;
    e.format = currentLineFormat;
    allExtraSelections.append(e);
  }*/

  my_sourcecodeeditor_editor->setExtraSelections(allExtraSelections);  
}

QString _sourcecodeeditor::getBeforeCurrentLineAsString()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  if (c.blockNumber() == 0) return "";
  c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);

  return c.selectedText();
}

QString _sourcecodeeditor::getCurrentLineAsString(int nLineOffset)
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  if (nLineOffset < 0) c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, nLineOffset * -1);
  else if (nLineOffset > 0) c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, nLineOffset);
  c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);

  return c.selectedText();
}

int _sourcecodeeditor::getCurrentLine()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  return c.blockNumber() + 1;
}

int _sourcecodeeditor::getCurrentColumn()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  return c.columnNumber() + 1;
}

void _sourcecodeeditor::performFind()
{
  // be sure to make only one window visible
  foreach (QWidget *widget, QApplication::allWidgets()){
    if (widget->objectName() == "Find"){
      widget->activateWindow();
      widget->setFocus();
      return;
    }
  }

  _find *o = new _find(this);
  //o->show();
}

void _sourcecodeeditor::performReplace()
{
  // be sure to make only one window visible
  foreach (QWidget *widget, QApplication::allWidgets()){
    if (widget->objectName() == "Replace"){
      widget->activateWindow();
      widget->setFocus();
      return;
    }
  }

  _replace *o = new _replace(this);
 // o->show();
}

bool _sourcecodeeditor::replace(QString replace)
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();

  if (c.hasSelection()){

    c.beginEditBlock();

    c.insertText(replace);

    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

    return true;

  } 

  return false;
}

void _sourcecodeeditor::replaceAll(QString search, QString replace, bool bMatchCase, bool bMatchWhole, bool bSearchUp, bool bSelection)
{

  if (bSelection){
  } else {
  }

/*
  int n = 0;
  while (true){
    textedit->getCursorPosition(&para, &index);

    if (!textedit->find (search, bMatchCase, bMatchWhole, !bSearchUp, &para, &index)){
re:
      
      QMessageBox::information(this, tr("Replace"), tr("'%1' replaces have been done\n").arg(n) + tr("for '") + search + "'.");

      break;
    } else {
      if (bSelection){
        textedit->getCursorPosition(&para, &index);
        if ((para == paraTo && index > indexTo) || para >= paraTo){
          goto re;
        }
      }
      n++;
      textedit->setSelection (para, index, para, index + search.length());
      textedit->insert2(replace, false, false, true);
    }
  }
*/
  if (bSelection){
  } else {
  }
  
}

void _sourcecodeeditor::setFullscreen()
{
  EXTERN_my_mainwindow->hide();
  noFullScreenParent = parentWidget();
  noFullScreenWindowFlags = windowFlags();
  noFullScreenPos = pos();
  noFullScreenSize = size();
  //showMaximized();  
  setHidden(true);
  noFullScreenIcon = windowIcon();
  setWindowIcon(kbasicIcon(kbasicPath("ide/kbasic_icon.png")));
  setParent(0);
  showFullScreen(); 
  this->my_sourcecodeeditor_editor->setFocus();
  window_nofullscreen->setIcon(kbasicIcon(kbasicPath("ide/VIEW_NOFULLSCREEN.png")));
  window_nofullscreen->setToolTip(tr("FullScreen Mode Off"));
//  window_nofullscreen->setEnabled(true);
  bFullscreen = true;
}

void _sourcecodeeditor::setNoFullscreen2()
{
  setNoFullscreen(true);
}

void _sourcecodeeditor::setNoFullscreen(bool bSwitch)
{
  if (bFullscreen){
    bFullscreen = false;
    window_nofullscreen->setIcon(kbasicIcon(kbasicPath("ide/VIEW_FULLSCREEN.png")));
    window_nofullscreen->setToolTip(tr("FullScreen Mode On"));
  //  window_nofullscreen->setEnabled(false);
    setHidden(true);

/*
    QList<QMdiSubWindow *> windows = EXTERN_my_mainwindow->workspace->subWindowList();

    for (int i = 0; i < windows.count(); i++){	    
      QMdiSubWindow *ww = windows.at(i);
      if (ww->widget() == this){        
        ww->setWidget(this);
        break;
      }
    }
*/
    EXTERN_my_mainwindow->show();
    setWindowIcon(noFullScreenIcon);

    setParent(noFullScreenParent, noFullScreenWindowFlags); 
    ((QMdiSubWindow *)noFullScreenParent)->setWidget(0);
    ((QMdiSubWindow *)noFullScreenParent)->setWidget(this);
    //setParent(EXTERN_my_mainwindow, noFullScreenWindowFlags); 
    //EXTERN_my_mainwindow->workspace->addSubWindow(this);
    //move(noFullScreenPos);
    //resize(noFullScreenSize);
    showNormal();   
  } else if (bSwitch){
    setFullscreen();
  }
}

void _sourcecodeeditor::setWindow_extend()
{
  /*
static bool b = true;
b = !b;

static bool bEXTERN_HelpWindow;
static bool bEXTERN_ParserWindow;
static bool bEXTERN_PropertyWindow;
static bool bEXTERN_ProjectWindow;
static bool bEXTERN_ToolboxForm;
static bool bEXTERN_ToolboxMenuBar;
static bool bEXTERN_ToolboxToolBar;
static bool bEXTERN_ToolboxSql;
static bool bEXTERN_ToolboxReport;
static bool bEXTERN_quickcode;
static bool bEXTERN_globallist;
static bool bEXTERN_Global;
static bool bEXTERN_stacklist;
static bool bEXTERN_Stack;
static bool bEXTERN_locallist;
static bool bEXTERN_Local;
static bool bEXTERN_FileFind;
static bool bEXTERN_FileReplace;
static bool bEXTERN_Quickcode;
static bool bEXTERN_Helpwindow_shortcut;

if (!b){
 bEXTERN_HelpWindow = EXTERN_HelpWindow->isVisible();
 bEXTERN_ParserWindow = EXTERN_ParserWindow->isVisible();
 bEXTERN_PropertyWindow = EXTERN_PropertyWindow->isVisible();
  bEXTERN_ProjectWindow = EXTERN_ProjectWindow->isVisible();
   bEXTERN_ToolboxForm = EXTERN_ToolboxForm->isVisible();
    bEXTERN_ToolboxMenuBar = EXTERN_ToolboxMenuBar->isVisible();
     bEXTERN_ToolboxToolBar = EXTERN_ToolboxToolBar->isVisible();
//     bEXTERN_ToolboxSql = EXTERN_ToolboxSql->isVisible();
      bEXTERN_ToolboxReport = EXTERN_ToolboxReport->isVisible();
       bEXTERN_quickcode = EXTERN_quickcode->isVisible();
        bEXTERN_globallist = EXTERN_globallist->isVisible();
         bEXTERN_Global = EXTERN_Global->isVisible();
          bEXTERN_stacklist = EXTERN_stacklist->isVisible();
           bEXTERN_Stack = EXTERN_Stack->isVisible();
            bEXTERN_locallist = EXTERN_locallist->isVisible();
             bEXTERN_Local = EXTERN_Local->isVisible();
 bEXTERN_FileFind = EXTERN_FileFind->isVisible();
  bEXTERN_FileReplace = EXTERN_FileReplace->isVisible();
   bEXTERN_Quickcode = EXTERN_Quickcode->isVisible();
    bEXTERN_Helpwindow_shortcut = EXTERN_Helpwindow_shortcut->isVisible();
}


EXTERN_HelpWindow->setShown(b && bEXTERN_HelpWindow);
EXTERN_ParserWindow->setShown(b && bEXTERN_ParserWindow);
EXTERN_PropertyWindow->setShown(b && bEXTERN_PropertyWindow);
EXTERN_ProjectWindow->setShown(b && bEXTERN_ProjectWindow);
EXTERN_ToolboxForm->setShown(b && bEXTERN_ToolboxForm);
EXTERN_ToolboxMenuBar->setShown(b && bEXTERN_ToolboxMenuBar);
EXTERN_ToolboxToolBar->setShown(b && bEXTERN_ToolboxToolBar);
//EXTERN_ToolboxSql->setShown(b && bEXTERN_ToolboxSql);
EXTERN_ToolboxReport->setShown(b && bEXTERN_ToolboxReport);

EXTERN_quickcode->setShown(b && bEXTERN_quickcode);

EXTERN_globallist->setShown(b && bEXTERN_globallist);
EXTERN_Global->setShown(b && bEXTERN_Global);

EXTERN_stacklist->setShown(b && bEXTERN_stacklist);
EXTERN_Stack->setShown(b && bEXTERN_Stack);

EXTERN_locallist->setShown(b && bEXTERN_locallist);
EXTERN_Local->setShown(b && bEXTERN_Local);

EXTERN_FileFind->setShown(b && bEXTERN_FileFind);
EXTERN_FileReplace->setShown(b && bEXTERN_FileReplace);

EXTERN_Quickcode->setShown(b && bEXTERN_Quickcode);
EXTERN_Helpwindow_shortcut->setShown(b && bEXTERN_Helpwindow_shortcut);

 if (!b) showMaximized(); else showNormal();
*/
}

/*
void _sourcecodeeditor::windowActivationChange(bool oldActive)
{
  if (bFullscreen){
    setNoFullscreen(true);
  }
  QWidget::windowActivationChange(oldActive);
}
*/

void _sourcecodeeditor::keyPressEvent(QKeyEvent* e)
{

  int n = e->key();
/*
  if (n == Qt::Key_C && bCTRL){
    EXTERN_my_mainwindow->event_RUN_STOP();    
    return;
  }*/

  if (bFullscreen){            
    switch(n){

    case Qt::Key_Escape: { setNoFullscreen(true); return; }
    case Qt::Key_N: if (bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_FILE_NEW_FILE(); return; }
                    if (bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_FILE_NEW_PROJECT(); return; }
                    break;
    case Qt::Key_O: if (bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_FILE_OPEN_PROJECT(); return; }
                    if (bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_FILE_OPEN_FILE(); return; }
                    break;
    case Qt::Key_S: if (bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_FILE_SAVE(); return; }
                    if (bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_FILE_SAVE_ALL(); return; }
                    break;
    case Qt::Key_F: if (bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_EDIT_FIND(); return; }
    case Qt::Key_R: if (bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_EDIT_REPLACE(); return; }
                    break;
    case Qt::Key_Tab: 
                    if (bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_EDIT_UNINDENT_LINES(); return; }
                    if (!bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_EDIT_INDENT_LINES(); return; }
                    break;
    case Qt::Key_G: if (bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_EDIT_GOTO(); return; }
                    break;
    case Qt::Key_F4: if (!bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_EDIT_SET_BOOKMARK(); return; }
                     if (!bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_EDIT_NEXT_BOOKMARK(); return; }
                     if (bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_EDIT_PREVIOUS_BOOKMARK(); return; }
                    break;
    case Qt::Key_F7: if (!bCTRL && !bSHIFT){ setNoFullscreen(!bFullscreen); return; }
                    break;
                    /*
    case Qt::Key_F10: if (!bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_VIEW_NORMAL(); return; }
                    break;
    case Qt::Key_I: if (bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_VIEW_PROJECT_OVERVIEW(); return; }
                    break;
    case Qt::Key_F2: if (!bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_VIEW_KONSOLE(); return; }
                    break;*/
    case Qt::Key_F6: if (!bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_BUILD(); return; }
                    break;

    case Qt::Key_F5: if (!bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_RUN(); return; }
                     if (bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_RUN_IN_DEBUG(); return; }
                     if (bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_RUN_IN_DEBUG2(); return; }
                    break;
                    /*
    case Qt::Key_F8: if (!bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_SINGLE_STEP(); return; }
                     if (!bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_STEP_OVER(); return; }
                     if (bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_STEP_OUT(); return; }
                     if (bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_TO_CURSOR(); return; }
                    break;
    case Qt::Key_F9: if (!bCTRL && !bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_SET_BREAKPOINT(); return; }
                     if (!bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_NEXT_BREAKPOINT(); return; }
                     if (bCTRL && bSHIFT){ setNoFullscreen(true); EXTERN_my_mainwindow->event_RUN_PREVIOUS_BREAKPOINT(); return; }
                    break;
*/

    }
  }

    /*
  case Qt::Key_Up:     
    if (bCTRL){
      QRect r = my_sourcecodeeditor_editor->cursorRect();
      my_sourcecodeeditor_editor->viewport()->scroll(0, r.height());
      my_sourcecodeeditor_editor->repaint();
      my_sourcecodeeditor_editor->zoomIn();
      my_sourcecodeeditor_editor->zoomOut();
      break;
    }
  case Qt::Key_Down:
    if (bCTRL){
      QRect r = my_sourcecodeeditor_editor->cursorRect();
      my_sourcecodeeditor_editor->viewport()->scroll(0, -r.height());
      my_sourcecodeeditor_editor->zoomIn();
      my_sourcecodeeditor_editor->zoomOut();
      break;
    }*/
  

  switch(n){
    case Qt::Key_Control:
      bCTRL = true;
      break;
    case Qt::Key_Shift:
      bSHIFT = true;
      break;
  }

}

void _sourcecodeeditor::keyReleaseEvent(QKeyEvent *e)
{   
  switch(e->key()){
    case Qt::Key_Control:
      bCTRL = false;
      break;
    case Qt::Key_Shift:
      bSHIFT = false;
      break;
  }
}

void _sourcecodeeditor::closeEvent( QCloseEvent *e )
{
  if (my_sourcecodeeditor_editor->document()->isModified()){
      
	  show();
    setFocus();

	  switch( QMessageBox::question( this, tr("Save Changes"), 
      tr("Save changes to %1?").arg( filename.isEmpty() ? tr("unnamed document") : filename),
	      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel )){
	    case QMessageBox::Yes:
	        {
		        save();
		        if (!filename.isEmpty())
		          goto a;
		        else
		          e->ignore();
	        }
	        break;
	    case QMessageBox::No:
	        goto a;
	        break;
	    default:
	        e->ignore();
          return;
	        break;
	  }

  } else {
	  goto a;
  }
  //return;

a:
  bClosing = true;
  e->accept();

  if (parentWidget()){
    QMdiSubWindow *mdis = qobject_cast<QMdiSubWindow *>(parentWidget());
    EXTERN_my_mainwindow->workspace->removeSubWindow(mdis);
  }

  QWidget::closeEvent(e);
  
  if (EXTERN_my_parserwindow) EXTERN_my_parserwindow->refreshProject(this->getFilename());

}

QString _sourcecodeeditor::getSourceCode(bool b)
{
  /*
  if (b){
     return textedit->text();
  } else {
    _sourcecodeeditor *f = new _sourcecodeeditor(0, 0, "", 0);
    f->load(filename, false);    

    QString s = f->getSourceCode(true);
    delete f;

    return s;
  }*/
  return "";

}

QString _sourcecodeeditor::getSourceCode(QString sFileName)
{
  /*
    _sourcecodeeditor *f = new _sourcecodeeditor(0, 0, "", 0);
    f->load(sFileName, false);    

    QString s = f->getSourceCode(true);
    delete f;

    return s;
    */
    return "";
  

}


bool _sourcecodeeditor::load( const QString& fn, bool _bClassForm )
{  
/*
  QString s = EXTERN_my_mainwindow->getProjectPreference("Translation");
  trl = s.split(";");

  s = "";

  {
    QString sExt = EXTERN_my_mainwindow->getFilenameExtension(fn);
    QString q = fn.left(fn.length() - sExt.length() - 1);

    if (q.count(".") > 1){

      QString sLanguage = EXTERN_my_mainwindow->getFilenameExtension(q);
      if (trl.contains(sLanguage)){        

        QString sEnglish;
        filename = q.left(q.length() - sLanguage.length() - 1) + "." + sExt;
      }
    } else {
      filename = fn;
    }
  }
  */

  QString s = "";
  filename = fn;

  
  if (!filename.isEmpty()){
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly)){
      QMessageBox::information(this, MYAPP, QString("Could not read from %1").arg(filename));
      filename = "";
      return false;
    }

    if (_bClassForm){
      
      //_form *f = new _form(0, true, _form::getObjectNameFromFilename(filename));
      //f->load(filename, true);    

      if (filename.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){
        s = _menubar::getMenuBarClassSourceCodeForSaving(filename);
      } else if (filename.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){
        s = _toolbar::getToolBarClassSourceCodeForSaving(filename);
      } else {
        s = _form::getFormClassSourceCodeForSaving(filename);
      }
      //f->close();      

    } else {
	    QTextStream t(&f);
      
      t.setCodec("UTF-8");
      t.setAutoDetectUnicode(true);
      t.setGenerateByteOrderMark(true);

      //textCodec->toUnicode

	    s = t.readAll();
      s = s.replace("\r", "");
	    f.close();

      if (!filename.endsWith(".kbasic", Qt::CaseInsensitive) && !filename.endsWith(".kbasic_class", Qt::CaseInsensitive)) setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")));
    }
  }


  if (!s.isEmpty()){
	  my_sourcecodeeditor_editor->setText(s);  
  }

  bClassForm = _bClassForm;
  bOLDFORMAT = s.contains("OPTION VERYOLDBASIC", Qt::CaseInsensitive);

  if (bClassForm){
    EXTERN_my_mainwindow->VIEW_DESIGN->setEnabled(true);
    EXTERN_my_mainwindow->VIEW_REPORTPREVIEW->setEnabled(filename.endsWith(".kbasic_report", Qt::CaseInsensitive));
/*
    if (filename.endsWith(".kbasic_form")){
      EXTERN_my_mainwindow->VIEW_DESIGN->setEnabled(true);
    } else if (filename.endsWith(".kbasic_report")){
      EXTERN_my_mainwindow->VIEW_REPORT->setEnabled(true);
      EXTERN_my_mainwindow->VIEW_REPORTPREVIEW->setEnabled(true);
    } else if (filename.endsWith(".kbasic_menubar")){
      EXTERN_my_mainwindow->VIEW_MENUBAR->setEnabled(true);
    } else if (filename.endsWith(".kbasic_toolbar")){
      EXTERN_my_mainwindow->VIEW_TOOLBAR->setEnabled(true);
    } */
    
    
  }

  my_sourcecodeeditor_editor->document()->setModified(false);
  updateCaption(getFilenameWithoutPath());
  my_sourcecodeeditor_editor->focusInEvent(0);

  QApplication::restoreOverrideCursor();
  updatingBrowser();
  createMap3();  

  return !bClosing;
}

void _sourcecodeeditor::save(bool _saveAs)
{
  
  if (filename.isEmpty()){
    saveAs();
    return;
  }
  QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

  int n = -1;
  n = filename.lastIndexOf(".", n);
/*
  if (filename.right(5) == ".html"){
    saveHTML();
    return;
  }
*/
  if (n == -1){
    filename = filename + ".kbasic";
  }
  

  QString ss = my_sourcecodeeditor_editor->toPlainText();

  if (bClassForm){
//    _form *f = new _form(0, true, _form::getObjectNameFromFilename(filename));
    //f->setFormClassSourceCode(ss);
    if (filename.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){  
      _menubar::saveMenuBarClassSourceCodeOnly(filename, ss);
    } else if (filename.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){  
      _toolbar::saveToolBarClassSourceCodeOnly(filename, ss);
    } else {  
      _form::saveFormClassSourceCodeOnly(filename, ss);
    }

    
  //  delete f;
  } else {

    QFile f(filename);
    if (!f.open(QIODevice::WriteOnly)){
        QApplication::restoreOverrideCursor();
        QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(filename));
        return;
    }

    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    QTextCodec *c = t.codec();

    t << ss;
    f.close();
  }

  my_sourcecodeeditor_editor->document()->setModified(false);

  updateCaption(getFilenameWithoutPath(), true);   
  QApplication::restoreOverrideCursor();
}
/*
void _sourcecodeeditor::saveHTML()
{
  
    if (filename.isEmpty()){
      saveAsHTML();
      return;
    }

    QString text = textedit->text();
    QFile f(filename);
    if (!f.open(IO_WriteOnly)){
        QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(filename));
        return;
    }

  text = text.replace(" ", "  ");
  text = highlightSyntax(text);
  text = text.replace("\n", " @@@ ");
  text = text.replace("@@@", "<br>\n");
  text = text.replace("  ", "&nbsp;");
  text = text.replace("&nbsp; ", "&nbsp;");

    QString m;
    m = ""
  "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">"
  "<html>"
  "<head>"
  "<title>" + filename + "</title>"
  "</head>"
  ;

    m += "<body><FONT FACE='Courier New, monospace' COLOR='#000000'>";

    m.append(text);

    m.append(""
  "</font></body>"
  "</html>"
  );

    QTextStream t(&f);
             t.setCodec("UTF-8");
         t.setAutoDetectUnicode(true);
         t.setGenerateByteOrderMark(true);
t << m;
    f.close();

    setCaption(filename);
    textedit->setModified(false);
    
}*/

void _sourcecodeeditor::saveAs()
{
	  //show();
   // setFocus();

    QString fn = QFileDialog::getSaveFileName(this, MYAPP);
    if (!fn.isEmpty()){
      QFile f(fn);

      if (f.exists()){
	      switch( QMessageBox::warning( this, tr("Save As"), 
	          tr("File %1 already exists. Do want to overwrite?").arg( fn ),
	          tr("Yes"), tr("No"), tr("Cancel") ) ) {
	        case 0:
            bool b = filename != fn;
            filename = fn;
            save(b);

            EXTERN_my_mainwindow->ci_parse(getFilename(), my_sourcecodeeditor_editor->document()->toPlainText());
	          break;
	      }
      } else {
        bool b = filename != fn;
        filename = fn;
        save(b);
      }
      //if (EXTERN_my_projectwindow) EXTERN_my_projectwindow->refresh();


    }
    
}

void _sourcecodeeditor::saveAsHTML()
{

    QString fn = getFilename();
    fn.replace(".kbasic_class", ".html");
    fn.replace(".kbasic_module", ".html");
    fn.replace(".kbasic_form", ".html");
    fn.replace(".kbasic_menubar", ".html");
    fn.replace(".kbasic_toolbar", ".html");
    fn.replace(".kbasic", ".html");

   // goto save;

    fn = QFileDialog::getSaveFileName(this, MYAPP, fn);
    if (!fn.isEmpty()){
      QFile f(fn);

      if (f.exists()){
	      switch( QMessageBox::warning( this, tr("Save As"), 
	          tr("File %1 already exists. Do want to overwrite?").arg( fn ),
	          tr("Yes"), tr("No"), tr("Cancel") ) ) {
	        case 0:
            bool b = filename != fn;
            goto save;
	          break;
	      }
      } else {
        goto save;
      }
    }

    return;
save:
    {
     QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));

      if (!fn.endsWith(".html", Qt::CaseInsensitive)) fn += ".html";

      QFile f(fn);
      if (!f.open(QIODevice::WriteOnly)){
          QApplication::restoreOverrideCursor();
          QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(filename));
          return;
      }
      QString ss = my_sourcecodeeditor_editor->toPlainText();
      
      _sourcecodeeditor_syntaxhighlighter h;

      h.highlightBlock2(fn, ss);

      QTextStream t(&f);
      
      t.setCodec("UTF-8");
      t.setAutoDetectUnicode(true);
      t.setGenerateByteOrderMark(true);

      t << ss;
      f.close();
      QApplication::restoreOverrideCursor();
    }
}

void _sourcecodeeditor::updateCaption(QString s, bool bSaving)
{
  //bool b = windowTitle() != s;

  /*
  if (EXTERN_my_mainwindow->isClassFile(filename)){
    setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_CLASS.png")));
  } else {
    setWindowIcon(kbasicIcon(kbasicPath("ide/PROJECT_NEW_MODULE.png")));
  }*/

  if (s.isEmpty()){
    s = tr("unnamed document");
    my_sourcecodeeditor_editor->document()->setModified(true);
    //bool b = true;
  }
   
  if (!bSaving && my_sourcecodeeditor_editor && my_sourcecodeeditor_editor->document()->isModified()){
    s = s + "*";
  }

  if (isFormClassSourceCode() && s.indexOf(tr("unnamed document")) < 0){
     s += tr(" (Source Code)");
  }
  
  //setWindowListname(s);
  //QString kk = getWindowListnameWithoutPath();
  setWindowTitle(s);

}

bool _sourcecodeeditor::isModified()
{
  return my_sourcecodeeditor_editor->document()->isModified();
}

void _sourcecodeeditor::insertCorrectIdentForLine(bool bAppend)
{  
//  return; // qt4 contains lots of bugs, that's really a shame for such a high price

  int x;
  QString d = getBeforeCurrentLineAsString();  
  QString e = d.trimmed();

  for (x = 0; x < d.length(); x++){
    if (d.at(x) != ' ') break;
  }

  if (
    e.startsWith("IF", Qt::CaseInsensitive) || e.startsWith("IF(", Qt::CaseInsensitive)
    || e.startsWith("SELECT CASE", Qt::CaseInsensitive) || e.startsWith("SELECT CASE(", Qt::CaseInsensitive)
    || e.startsWith("WHILE", Qt::CaseInsensitive) || e.startsWith("WHILE(", Qt::CaseInsensitive)
    || e.startsWith("DO", Qt::CaseInsensitive) || e.startsWith("DO(", Qt::CaseInsensitive)
    || e.startsWith("FOR", Qt::CaseInsensitive) || e.startsWith("FOR(", Qt::CaseInsensitive)
    || e.startsWith("ELSE", Qt::CaseInsensitive) || e.startsWith("ELSE(", Qt::CaseInsensitive)
    || e.startsWith("ELSEIF", Qt::CaseInsensitive) || e.startsWith("ELSEIF(", Qt::CaseInsensitive)

    || e.startsWith("CASE ", Qt::CaseInsensitive)
    || e.startsWith("CASE(", Qt::CaseInsensitive)
    || e.startsWith("STATIC SUB ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC SUB ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED SUB ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE SUB ", Qt::CaseInsensitive)
    || e.startsWith("STATIC PUBLIC SUB ", Qt::CaseInsensitive)
    || e.startsWith("STATIC PROTECTED SUB ", Qt::CaseInsensitive)
    || e.startsWith("STATIC PRIVATE SUB ", Qt::CaseInsensitive)
    || e.startsWith("STATIC PUBLIC SUB ", Qt::CaseInsensitive)
    || e.startsWith("STATIC PROTECTED SUB ", Qt::CaseInsensitive)
    || e.startsWith("STATIC PRIVATE SUB ", Qt::CaseInsensitive)
    || e.startsWith("SUB ", Qt::CaseInsensitive)
    || e.startsWith("STATIC FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC STATIC FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED STATIC FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE STATIC FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("STATIC PUBLIC FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("STATIC PROTECTED FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("STATIC PRIVATE FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("FUNCTION ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC SIGNAL ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED SIGNAL ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE SIGNAL ", Qt::CaseInsensitive)
    || e.startsWith("SIGNAL ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC SLOT ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED SLOT ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE SLOT ", Qt::CaseInsensitive)
    || e.startsWith("SLOT ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC TYPE ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED TYPE ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE TYPE ", Qt::CaseInsensitive)
    || e.startsWith("TYPE ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC STRUCTURE ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED STRUCTURE ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE STRUCTURE ", Qt::CaseInsensitive)
    || e.startsWith("STRUCTURE ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC ENUM ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED ENUM ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE ENUM ", Qt::CaseInsensitive)
    || e.startsWith("ENUM ", Qt::CaseInsensitive)
    || e.startsWith("TRY ", Qt::CaseInsensitive)
    || e.startsWith("CATCH ", Qt::CaseInsensitive)
    || e.startsWith("CATCH(", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC CLASS ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED CLASS ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE CLASS ", Qt::CaseInsensitive)
    || e.startsWith("CLASS ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC CONSTRUCTOR ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED CONSTRUCTOR ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE CONSTRUCTOR ", Qt::CaseInsensitive)
    || e.startsWith("CONSTRUCTOR ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC DESTRUCTOR ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED DESTRUCTOR ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE DESTRUCTOR ", Qt::CaseInsensitive)
    || e.startsWith("DESTRUCTOR ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC PROPERTY ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED PROPERTY ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE PROPERTY ", Qt::CaseInsensitive)
    || e.startsWith("PROPERTY ", Qt::CaseInsensitive)
    || e.startsWith("SET ", Qt::CaseInsensitive)
    || e.startsWith("SET(", Qt::CaseInsensitive)
    || e.startsWith("GET ", Qt::CaseInsensitive)
    || e.startsWith("DEF ", Qt::CaseInsensitive)
    || e.startsWith("WITH ", Qt::CaseInsensitive)
    || e.startsWith("WHILE ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC MODULE ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED MODULE ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE MODULE ", Qt::CaseInsensitive)
    || e.startsWith("MODULE ", Qt::CaseInsensitive)
    || e.startsWith("STATIC ", Qt::CaseInsensitive)
    || e.startsWith("PUBLIC INTERFACE ", Qt::CaseInsensitive)
    || e.startsWith("PROTECTED INTERFACE ", Qt::CaseInsensitive)
    || e.startsWith("PRIVATE INTERFACE ", Qt::CaseInsensitive)
    || e.startsWith("INTERFACE ", Qt::CaseInsensitive)

  ){
    d = d.left(x);

    if (e.startsWith("IF ", Qt::CaseInsensitive) || e.startsWith("IF(", Qt::CaseInsensitive)){
      int m = e.indexOf("THEN", 0, Qt::CaseInsensitive);
      static QString u; u = e.mid(m + 4);
      u = u.trimmed();
      if (u.length() == 0){
        d += "  ";
        if (bAppend){
          d += "\n";
          d += d.left(d.length() - 3);
          d += "End If";
        }
      }
    } else if (e.startsWith("GET ", Qt::CaseInsensitive)){
      if (!e.contains(",")){
        d += "  ";
      }
    } else if (e.startsWith("STATIC ", Qt::CaseInsensitive) && !e.contains("SUB", Qt::CaseInsensitive) && !e.contains("FUNCTION", Qt::CaseInsensitive)){
      static QString u; u = e;
      u = u.trimmed();
      if (u.length() == 6){
        d += "  ";
      }  
    } else if (e.startsWith("SELECT CASE", Qt::CaseInsensitive) || e.startsWith("SELECT CASE(", Qt::CaseInsensitive)){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Select";
      }
    } else if (e.startsWith("CASE", Qt::CaseInsensitive) || e.startsWith("CASE(", Qt::CaseInsensitive)){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
      }    
    } else if (e.startsWith("FOR", Qt::CaseInsensitive) || e.startsWith("FOR(", Qt::CaseInsensitive)){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "Next";
      }    
    } else if (
      e.startsWith("STATIC SUB ", Qt::CaseInsensitive)
      || e.startsWith("PUBLIC SUB ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED SUB ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE SUB ", Qt::CaseInsensitive)
      || e.startsWith("STATIC PUBLIC SUB ", Qt::CaseInsensitive)
      || e.startsWith("STATIC PROTECTED SUB ", Qt::CaseInsensitive)
      || e.startsWith("STATIC PRIVATE SUB ", Qt::CaseInsensitive)
      || e.startsWith("STATIC PUBLIC SUB ", Qt::CaseInsensitive)
      || e.startsWith("STATIC PROTECTED SUB ", Qt::CaseInsensitive)
      || e.startsWith("STATIC PRIVATE SUB ", Qt::CaseInsensitive)
      || e.startsWith("SUB ", Qt::CaseInsensitive)

      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Sub";
      }    
    } else if (
      e.startsWith("STATIC FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("PUBLIC FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("PUBLIC STATIC FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED STATIC FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE STATIC FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("STATIC PUBLIC FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("STATIC PROTECTED FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("STATIC PRIVATE FUNCTION ", Qt::CaseInsensitive)
      || e.startsWith("FUNCTION ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Function";
      }    
    } else if (
      e.startsWith("PUBLIC SIGNAL ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED SIGNAL ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE SIGNAL ", Qt::CaseInsensitive)
      || e.startsWith("SIGNAL ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Signal";
      }    
    } else if (
      e.startsWith("PUBLIC SLOT ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED SLOT ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE SLOT ", Qt::CaseInsensitive)
      || e.startsWith("SLOT ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Slot";
      }    
    } else if (
      e.startsWith("PUBLIC TYPE ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED TYPE ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE TYPE ", Qt::CaseInsensitive)
      || e.startsWith("TYPE ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Type";
      }    
    } else if (
      e.startsWith("PUBLIC TYPE ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED TYPE ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE TYPE ", Qt::CaseInsensitive)
      || e.startsWith("TYPE ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Type";
      }    
    } else if (
      e.startsWith("PUBLIC ENUM ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED ENUM ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE ENUM ", Qt::CaseInsensitive)
      || e.startsWith("ENUM ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Enum";
      }    
    } else if (
      e.startsWith("TRY ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Try";
      }    
    } else if (
      e.startsWith("PUBLIC CLASS ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED CLASS ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE CLASS ", Qt::CaseInsensitive)
      || e.startsWith("CLASS ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Class";
      }    
    } else if (
      e.startsWith("PUBLIC CONSTRUCTOR ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED CONSTRUCTOR ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE CONSTRUCTOR ", Qt::CaseInsensitive)
      || e.startsWith("CONSTRUCTOR ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Constructor";
      } 
    } else if (
      e.startsWith("PUBLIC DESTRUCTOR ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED DESTRUCTOR ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE DESTRUCTOR ", Qt::CaseInsensitive)
      || e.startsWith("DESTRUCTOR ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Destructor";
      } 
    } else if (
      e.startsWith("PUBLIC MODULE ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED MODULE ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE MODULE ", Qt::CaseInsensitive)
      || e.startsWith("MODULE ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Module";
      } 
    } else if (
      e.startsWith("WITH ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End With";
      } 
    } else if (
      e.startsWith("PUBLIC PROPERTY ", Qt::CaseInsensitive)
      || e.startsWith("PROTECTED PROPERTY ", Qt::CaseInsensitive)
      || e.startsWith("PRIVATE PROPERTY ", Qt::CaseInsensitive)
      || e.startsWith("PROPERTY ", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Property";
      } 
    } else if (
      e.startsWith("GET ", Qt::CaseInsensitive) && !e.contains(",")
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Get";
      } 
    } else if (
      e.startsWith("SET ", Qt::CaseInsensitive)
      || e.startsWith("SET(", Qt::CaseInsensitive)
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Set";
      } 
    } else if (
      e.startsWith("STATIC ", Qt::CaseInsensitive) && e.trimmed().length() == 6
      ){
      d += "  ";
      if (bAppend){
        d += "\n";
        d += d.left(d.length() - 3);
        d += "End Static";
      } 
    } else {
      d += "  ";
    }

  } else {
    d = d.left(x);
  }
  
  QTextCursor f = my_sourcecodeeditor_editor->textCursor();

  f.clearSelection();
  f.insertText(d);
  if (d.trimmed().length()){
    f.movePosition(QTextCursor::Up);
  }
  my_sourcecodeeditor_editor->setTextCursor(f);  
}

bool _sourcecodeeditor::beautifyCurrentLine()
{  
  return false; // waren einige fehler

  if (!bSyntaxHighlighting) return false;

  QTextCursor f = my_sourcecodeeditor_editor->textCursor();
  int n = f.columnNumber();
  f.select(QTextCursor::LineUnderCursor);
   
  QString r = f.selectedText();
  QString r2 = r;
  if (r.length() > n) return false; // break word?

  int x;
  for (x = 0; x < r.length(); x++){
    if (r.at(x) != ' ') break;
  }
  r = r.left(x);

  QString s = getCurrentLineAsString();
  if (s.trimmed().startsWith("'")) return false;

  QString t = "";
  int index = 0;
  //QString u2 = "";

  bool bComment = false;
  QString ss = s.simplified();
  if (ss.startsWith("'") || ss.startsWith("/*")) bComment = true;
  while (index < s.length()){
    int i;
    bool bString = false;
    QChar c = 0;
    QChar c2 = 0;
    QChar c3 = 0;
    QChar c4 = 0;
    for (i = index; i < s.length(); i++){
      c2 = c;
      c = s.at(i);
      c3 = i + 1 < s.length() ? s.at(i + 1) : 0;
      c4 = i + 2 < s.length() ? s.at(i + 2) : 0;

      if (!bComment && (bString == false && c == '\"')) bString = true;
      else if (!bComment && (bString  && c == '\"')){
        bString = false;
        i++;
        break;
      }

      if (!bString && (c == '\'' || (c == '/' && c3 == '*') || (c == '/' && c3 == '*' && c4 == '*'))){
        bComment = true;
        t += " ";
      }
      else if (!bString && ((c == '*' && c3 == '/'))){
        bComment = false;
        i += 2;
        break;
      }
      else if (!(c.isLetter() || c.isNumber() || c == '_')) if (!bComment && !bString) break;
    }
    
    QString u = s.mid(index, i - index);
    //QString u3 = u2;
    QString u2 = s.mid(index + 1, 1);
    if (u.length() == 0){
      u = s.mid(index, 1);  
      u = u.trimmed();
      i++;
    }
    QString z = map.value(u);
    if (bOLDFORMAT) z = z.toUpper();
//    if (z.isEmpty()) z = map2.value(u);
    if (z.isEmpty()) z = map3.value(u);
    

    if (t.endsWith("*/")) t += " ";

    if (!z.isEmpty()){
      if (!t.endsWith("'") && z != "," && !t.endsWith(".") 
        && !t.endsWith("@") 
        && !t.endsWith("$") 
        && !t.endsWith("#") 
        && !t.endsWith(" ") && !t.endsWith("<") && t.length() 
       /* && !(u.length() == 1 && isDelimitorOperator(t.at(t.length() - 1)) && isDelimitorSymbol(u3.at(0)))*/) t += " ";
      if (z == "," && t.endsWith(" ")) t = t.left(t.length() - 1);
      else if ((z == ")" || z == "]") && t.endsWith(" ")) t = t.left(t.length() - 1);
      else if ((z == "(" || z == "[") && t.endsWith(" ")) t = t.left(t.length() - 1);      
      //else if (z == "'" || z.startsWith("/*")) t += " ";
      t += z;
      if (!t.endsWith("'") && u2 != ">") t += " ";
    } else if (!u.isEmpty()){
      if (u == "." && t.endsWith(" ")) t = t.left(t.length() - 1);     
      else if (u == "@" && t.endsWith(" ")) t = t.left(t.length() - 1);     
      else if (u == "&" && t.endsWith(" ")) t = t.left(t.length() - 1);     
      else if (u == "$" && t.endsWith(" ")) t = t.left(t.length() - 1);     
      else if (u == "#" && t.endsWith(" ")) t = t.left(t.length() - 1);     
      else if ((u == "(" || u == "[") && t.endsWith(" ")) t = t.left(t.length() - 1);           
      int kk = t.length() - 1;  
      if (kk >= 0){
        QChar c = t.at(kk);
        if ((u == "(" || u == "[") && !c.isLetter() && c != '$') t += " ";
      }
      t.append(u);
    }
    index = i;    
  }

  f.insertText(r + t);

  my_sourcecodeeditor_editor->setTextCursor(f);  

  if ((r + t).trimmed() == r2.trimmed()) return false;
  return true;
}
/*
bool _sourcecodeeditor::isDelimitorOperator(QChar c)
{
	switch(c.toAscii())
	{
  case '+':
  case '-':
  case '*':
  case '/':
  case '\\':
  case '=':
  case '>':
  case '<':
  case '^':
  case '&':
  case '|':
		return true;
  default:
    return false;
    break;
  }
	return false;
}

bool _sourcecodeeditor::isDelimitorSymbol(QChar c)
{
	switch(c.toAscii())
	{
  case '.':
  case '(':
  case ')':
  case '[':
  case ']':
  case ',':
  case ':':
  case '!':
  case ';':
  case '?':
  case '#':
  case '{':
  case '}':
		return true;
  default:
    return false;
    break;
  }
	return false;
}
*/
void _sourcecodeeditor::createMap()
{
  if (map.count()) return;

  QStringList l;

  l << "$Dynamic" << "#Else" << "$End" << "#ExternalSource" << "#If" << "#Region" << "$Static" << "Absolute" << "Abstract" << "AddressOf" << "Alias" << "Ansi" << "As" << "Assembly" << "Auto" << "Base" << "ByRef" << "ByVal" << "Call" << "CallByName" << "Case" << "Catch" << "Chain" << "Choose" << "Class" << "Class_Initialize" << "Class_Terminate" << "COM" << "Common" << "Compare" << "Connect" << "Const" << "Constructor" << "Data" << "Database" << "Decimal" << "Declare" << "Def" << "Default" << "DefBool" << "DefByte" << "DefCur" << "DefDate" << "DefDbl" << "DefInt" << "DefLng" << "DefObj" << "DefSng" << "DefStr" << "DefVar" << "Delegate" << "Destructor" << "Dim" << "DirectCast" << "Disconnect" << "Do" << "Each" << "Echo" << "Else" << "ElseIf" << "Empty" << "End" << "EndIf" << "Enum" << "Erase" << "Event" << "Exit" << "Explicit" << "Finally" << "For" << "Friend" << "Function" << "Global" << "GoSub" << "GoTo" << "Handles" << "If" << "IIf" << "Implements" << "Imports" << "In" << "Inherits" << "Interface" << "Is" << "Iterate" << MYAPP << "Key" << "LBound" << "Let" << "Lib" << "Like" << "Loop" << "LSet" << "Me" << "Mid" << "Module" << "MustInherit" << "MustOverride" << "MyBase" << "MyClass" << "NameSpace" << "New" << "Next" << "Nothing" << "NotInheritable" << "NotOverridable" << "Null" << "Off" << "OldBasic" << "On" << "Option" << "Optional" << "Overloads" << "Overriddable" << "Overrides" << "ParamArray" << "Parent" << "Pen" << "Play" << "Preserve" << "Private" << "Property" << "Protected" << "Public" << "Range" << "Read" << "ReadOnly" << "ReDim" << "Rem" << "/**" << "/*" << "*/" << "'" << "Repeat" << "Restore" << "Resume" << "Return" << "RSet" << "Run" << "Select" << "Set" << "Shadows" << "Shared" << "Signal" << "SizeOf" << "Slot" << "Static" << "Step" << "Stop" << "STRIG" << "Structure" << "Sub" << "Swap" << "Switch" << "SynClock" << "System" << "Text" << "Then" << "Throw" << "Throws" << "Timer" << "To" << "TROFF" << "TRON" << "Try" << "Type" << "TypeDef" << "UBound" << "UniCode" << "Until" << "VARPTR" << "VARPTR$" << "VARSEG" << "VeryOldBasic" << "Wait" << "Wend" << "While" << "With" << "WithEvents" << "WriteOnly";
  l << "__Class__" << "__File__" << "__IsClass__" << "__IsLinux__" << "__IsMacOS__" << "__IsModule__" << "__IsSub__" << "__IsWindows__" << "__Line__" << "__Module__" << "__Scope__" << "__Sub__" << "Abs" << "Access" << "Acs" << "AddHandler" << "AppActiviate" << "Append" << "Array" << "Asc" << "Asn" << "Atn" << "Beep" << "Bin" << "Bin$" << "Binary" << "BLOAD" << "BSAVE" << "CBCD" << "CBool" << "CByte" << "CChar" << "CCur" << "CDate" << "CDbl" << "CDec" << "CEXT" << "CFIX" << "ChDir" << "ChDrive" << "Chr" << "Chr$" << "CInt" << "Circle" << "Clear" << "CLng" << "Close" << "CLS" << "CObj" << "Color" << "Command" << "Command$" << "Cos" << "CQUD" << "CreateObject" << "CShort" << "CSng" << "CsrLin" << "CType" << "CurDir" << "CurDir$" << "CVD" << "CVDMBF" << "CVERR" << "CVI" << "CVL" << "CVS" << "CVSMBF" << "Date" << "Date$" << "DateAdd" << "DateDiff" << "DatePart" << "DateSerial" << "DateValue" << "Day" << "DDB" << "Deg" << "DeleteSetting" << "Dir" << "Dir$" << "DoEvents" << "DOF" << "Draw" << "Environ" << "Environ$" << "EOF" << "ErDev" << "ErDev$" << "Erl" << "Err" << "Error" << "Error$" << "Exp" << "Fact" << "Field" << "FileAttr" << "FileCopy" << "FileDateTime" << "FileLen" << "Files" << "Filter" << "Fix" << "FN" << "Format" << "Format$" << "FormatCurrency" << "FormatDateTime" << "FormatNumber" << "FormatPercent" << "Frac" << "FRE" << "FreeFile" << "FV" << "Get" << "GetAllSettings" << "GetAttr" << "GetAutoServerSettings" << "GetObject" << "GetSetting" << "GetType" << "Hex" << "Hex$" << "Hour" << "Hypot" << "IMEStatus" << "Inkey" << "Inkey$" << "Inp" << "Input" << "Input$" << "InputBox" << "InStr" << "InStRev" << "Int" << "IOCtl" << "IOCtl$" << "IPMT" << "IRR" << "IsArray" << "IsBoolean" << "IsByte" << "IsCharacter" << "IsCollection" << "IsCString" << "IsCurrency" << "IsDate" << "IsDouble" << "IsEmpty" << "IsError" << "IsInt16" << "IsInt32" << "IsInt64" << "IsInteger" << "IsMissing" << "IsNull" << "IsNumeric" << "IsObject" << "IsShort" << "IsSingle" << "IsUInt16" << "IsUInt32" << "IsUInt64" << "IsLong" << "IsString" << "IsVariant" << "Join" << "Kill" << "LCase" << "LCase$" << "Left" << "Left$" << "Len" << "Line" << "Ln" << "Load" << "LoadPicture" << "LoadResData" << "LoadResPicture" << "LoadResString" << "Loc" << "Locate" << "Lock" << "LOF" << "Log" << "Logb" << "LPos" << "LPrint" << "LTrim" << "LTrim$" << "Max" << "Mid$" << "Min" << "Minute" << "MIRR" << "MKD$" << "MkDir" << "MKDMBF$" << "MKI$" << "MKL$" << "MKS" << "MKS$" << "MKSMBF$" << "Month" << "MonthName" << "MsgBox" << "MTIMER" << "Name" << "Now" << "NPER" << "NPV" << "Nz" << "Oct" << "Oct$" << "Open" << "Out" << "Output" << "Paint" << "Palette" << "Partition" << "PCopy" << "Peek" << "PMAP" << "PMT" << "Point" << "Poke" << "Pos" << "PPMT" << "Preset" << "Print" << "PSet" << "Put" << "PV" << "QBCOLOR" << "Rad" << "Raise" << "RaiseEvent" << "RaiseSignal" << "Random" << "Randomize" << "Rate" << "RemoveHandler" << "Replace" << "Reset" << "RGB" << "Right" << "Right$" << "RmDir" << "RND" << "Round" << "RTrim" << "RTrim$" << "SavePicture" << "SaveSetting" << "Screen" << "Sec" << "Second" << "Seek" << "Seg" << "SendKeys" << "SetAttr" << "Sgn" << "Shell" << "Sin" << "Sleep" << "Sln" << "Sound" << "Space" << "Space$" << "Spc" << "Split" << "Sqr" << "Stick" << "Str" << "Str$" << "StrComp" << "StrConv" << "String" << "String$" << "StrReverse" << "SYD" << "Tab" << "Tan" << "Time" << "Time$" << "TimeSerial" << "TimeValue" << "Trim" << "Trim$" << "TypeName" << "TypeOf" << "UCase" << "UCase$" << "UnLoad" << "UnLock" << "Using" << "Val" << "VarType" << "View" << "Weekday" << "WeekdayName" << "Width" << "Window" << "Write" << "Year";
  l << "Shl" << "Shr" << "Inc" << "Dec" << "+=" << "-=" << "/=" << "*=" << "++" << "--" << "BitAnd" << "BitOr" << "BitXor" << "BitNot" << "+" << "-" << "*" << "/" << "Mod" << "=" << "<>" << ">=" << "<=" << ">" << "<" << "And" << "AndAlso" << "Or" << "OrElse" << "Not" << "^" << "&" << "Xor" << "\\" << "Eqv" << "Imp" << "|" << "!" << "==" << "!=" << "&=" << "|=" << "^=" << "<<" << ">>";
  l << "Boolean" << "Byte" << "Character" << "Collection" << "CString" << "Currency" << "Date" << "Double" /*<< "Int16" << "Int32" << "Int64"*/ << "Integer" << "Long" << "Object" << "Short" << "Single" << "CString" << "WString" << "String" /*<< "UInt16" << "UInt32" << "UInt64"*/ << "Variant";

  l << "," << ":" << "_";
  l << "True" << "False";

  l << "Math";

  foreach(QString s, l){
    map.insert(s, s);
    map.insert(s.toLower(), s);
    map.insert(s.toUpper(), s);
  }
/*
  l.clear();

  l << "Control" << "Form" << "CommandButton" << "CustomControl" << "Label" << "CheckBox" << "RadioButton";
  l << "TextBox" << "Frame" << "ComboBox" << "ListBox" << "DateBox" << "TimeBox" << "DateTimeBox";
  l << "ScrollBox" << "Timer" << "Tab" << "Hidden" << "Image" << "ImageButton" << "TreeView";
  l << "Box" << "ChildControl" << "Editor" << "Browser" << "ProgressBar" << "VBox" << "HBox";
  l << "VHBox" << "HSplit" << "VSplit" << "Strings" << "ByteArray" << "BitArray" << "Collection";
  l << "Number" << "Dir" << "File" << "Pixmap" << "Sound" << "Font" << "DateTime";
  l << "Color" << "Math" << "Conversion" << "RegExp" << "ColorDialog" << "FontDialog" << "InputDialog";
  l << "MessageBox" << "ProgressDialog" << "StatusBar" << "SplashScreen" << "Application" << "SystemTray" << "ApplicationForm";
  l << "Pixmaps" << "Sounds" << "Process" << "ToolBar" << "Tool" << "MenuBar" << "Menu";

  foreach(QString s, l){
    map2.insert(s, s);
    map2.insert(s.toLower(), s);
    map2.insert(s.toUpper(), s);
  }*/

}

void _sourcecodeeditor::textChanged()
{
  if (!windowTitle().endsWith("*")){
    updateCaption(getFilenameWithoutPath(), false);
  }
  
  EXTERN_my_mainwindow->ci_bUpdatedAs = true;
  EXTERN_my_mainwindow->ci_bUpdatedDot = true;
  EXTERN_my_mainwindow->ci_bUpdatedDotMethod = true;


  bBrowserNeedsUpdate = true;

}

void _sourcecodeeditor::selectionChanged()
{
  if (nBrowserUpdated){  
    if (nBrowserUpdated > 1){
      nBrowserUpdated = 0;
      browser->setCurrentIndex(0);
    } else {
      nBrowserUpdated++;
    }
  }
}

void _sourcecodeeditor::updateScopes()
{
  static int nLine = 0;
  int uu = getCurrentLine();
  if (nLine == uu) return;
  nLine = uu;

  QString s = my_sourcecodeeditor_editor->document()->toPlainText();
  int i = 0;
  bool bScope = false;
  bool bScope2 = false;

  sScope = EXTERN_my_mainwindow->getFilenameWithoutPathAndExtension(getFilename());
  sScope2 = ""; 
  while (!bScope){
    if (i > nLine) break;
    QString k = getCurrentLineAsString(-(++i));

    // eat comments and whitespace
    k = k.simplified();
    int n = k.indexOf("/*");
    if (n >= 0) k = k.left(n) + "\n";
    n = k.indexOf("'");
    if (n >= 0) k = k.left(n) + "\n";

    int j = 0;
    if (bScope2) goto w;
    if ((n = k.indexOf("END SUB", 0, Qt::CaseInsensitive)) >= 0){ bScope2 = true; n = -1; }
    else if ((n = k.indexOf("END FUNCTION", 0, Qt::CaseInsensitive)) >= 0){ bScope2 = true; n = -1; }
    else if ((n = k.indexOf("END CONSTRUTOR", 0, Qt::CaseInsensitive)) >= 0){ bScope2 = true; n = -1; }
    else if ((n = k.indexOf("SUB ", 0, Qt::CaseInsensitive)) >= 0) j = 4;
    else if ((n = k.indexOf("FUNCTION ", 0, Qt::CaseInsensitive)) >= 0) j = 9;
    else if ((n = k.indexOf("CONSTRUTOR ", 0, Qt::CaseInsensitive)) >= 0) j = 11;    

    if (n >= 0){
      n += j;
      int n2 = n;
      int nn = k.length();
      while (true){
        if (k.mid(n, 1) == "(") break;
        if (k.mid(n, 1) == " ") break;
        if (k.mid(n, 1) == "\n") break;
        n++;
        if (n > nn) break;
      }
      
      sScope2 = k.mid(n2, n - n2);
      bScope2 = true;
    } else { 
  
w:
      if ((n = k.indexOf("END CLASS", 0, Qt::CaseInsensitive)) >= 0){ bScope = true; n = -1; }
      else if ((n = k.indexOf("END MODULE", 0, Qt::CaseInsensitive)) >= 0){ bScope = true; n = -1; }
      else if ((n = k.indexOf("CLASS ", 0, Qt::CaseInsensitive)) >= 0) j = 6;
      else if ((n = k.indexOf("MODULE ", 0, Qt::CaseInsensitive)) >= 0) j = 7;

      if (n >= 0){
        n += j;
        int n2 = n;
        int nn = k.length();
        while (true){
          if (k.mid(n, 1) == " ") break;
          if (k.mid(n, 1) == "\n") break;
          n++;
          if (n > nn) break;
        }
        sScope = k.mid(n2, n - n2);
        bScope = true;
      }// else if (!bScope) sScope = ""; 
    }


  }

}

QString _sourcecodeeditor::getScope() // class name or module name of current cursor line
{
  updateScopes();
  return sScope;
}

QString _sourcecodeeditor::getScope2() // method name
{
  //updateScopes();
  return sScope2;
}

QString _sourcecodeeditor::getDot() // class name or module name of current cursor line
{
  sDot = my_sourcecodeeditor_editor->getLastIdentifierBeforeDot();
  sDot = sDot.simplified();
  return sDot;
}


void _sourcecodeeditor::focusInEvent(QFocusEvent *e)
{
  my_sourcecodeeditor_editor->setFocus();
  //my_sourcecodeeditor_editor->focusInEvent(e);
}

bool _sourcecodeeditor::newEvent (QString sControlName, QString sEvent, QString sParameter, QString sCode)
{

  QString ss = "Sub " + sControlName;
  ss += "_";
  ss += sEvent;

  if (hasSub(ss)){
    my_sourcecodeeditor_editor->focusInEvent(0);
    return true;
  } else {
    gotoBeforeEndClass();

    ss += "(";
    ss += sParameter;
    ss += ")";

    QString s;

    if (sEvent.contains("OnClick", Qt::CaseInsensitive)){

    s = 
      "\n' WARNING! Use OnEvent, if you would like to react on all possible triggers\nPrivate "
      + ss + "\n"
      + (sCode.isEmpty() ? "  \n" : sCode)
      + "End Sub\n\n" 
      ;
    } else {

      s = 
        "\n\nPrivate "
        + ss + "\n"
        + (sCode.isEmpty() ? "  \n" : sCode)
        + "End Sub\n\n" 
        ;
    }
    

    QTextCursor c = my_sourcecodeeditor_editor->textCursor();

    c.beginEditBlock();

    c.insertText(s);
    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

    ss = sControlName;
    ss += "_";
    ss += sEvent;

    hasSub(ss);
  }

  my_sourcecodeeditor_editor->focusInEvent(0);
  return false;
}

bool _sourcecodeeditor::addToEvent(QString sControlName, QString sEvent, QString sParameter, QString sCode)
{
  QString ss = sControlName;
  ss += "_";
  ss += sEvent;

  if (!hasSub(ss)){
    return newEvent(sControlName, sEvent, sParameter, sCode);
  } else {
    QTextCursor c = my_sourcecodeeditor_editor->textCursor();

    c.clearSelection();
    c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, 1);
    c.beginEditBlock();

    c.insertText(sCode);
    c.endEditBlock();

    my_sourcecodeeditor_editor->setTextCursor(c);
    my_sourcecodeeditor_editor->document()->setModified(true); // looks like we need setModified manually

    hasSub(ss);
  }

  return false;
}

bool _sourcecodeeditor::hasSub(QString s, bool bSelect)
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  QTextDocument *d = my_sourcecodeeditor_editor->document();

  my_sourcecodeeditor_editor->setTextCursor(c);

  c = d->find(s, Qt::CaseInsensitive);
  if (c.hasSelection()){
    if (bSelect) setCurrentLineAndSelectLine(c.blockNumber() + 1);
    return true;
  }

  return false;
}

void _sourcecodeeditor::gotoBeforeEndClass()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  QTextDocument *d = my_sourcecodeeditor_editor->document();

  c = d->find("End Class", Qt::CaseInsensitive);
  if (c.hasSelection()){
 
    c.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor);
    c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
    my_sourcecodeeditor_editor->setTextCursor(c);
  } else {    
    c = my_sourcecodeeditor_editor->textCursor();
    c.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    c.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
    my_sourcecodeeditor_editor->setTextCursor(c);
  }
}

void _sourcecodeeditor::unselect()
{  
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  if (c.hasSelection()){
    c.clearSelection();    
    my_sourcecodeeditor_editor->setTextCursor(c);
  }
}

void _sourcecodeeditor::performFindDefinition()
{
  _finddefinition *lw = new _finddefinition();

  QString ss2 = getCurrentLineAsString();
  if (ss2.simplified().isEmpty()) return;

  QString ss = "";
  int n = 0;
  QTextCursor cc = my_sourcecodeeditor_editor->textCursor();

  if (cc.hasSelection()){
    ss = cc.selectedText();
    ss = ss.simplified();
    n = getCurrentColumn() - 1 - ss.length();
  } else {
    QString s = getCurrentLineAsString();
    QString s3 = s;
    int index = getCurrentColumn();
    if (index - 1 < 0 || s[index - 1] != QChar(' ')){
      int l = index;
      int r = index;
      while (l - 1 >= 0){
        QChar c = s[--l];
        if (!(c.isLetterOrNumber() || c == '_')) break;
      }
      n = s.length();
      while (r < n && (s[r].isLetterOrNumber() || s[r] == '_')){
        r++;
      }
      s = s.mid(l, r - l);

      s = s.trimmed();
      if (s.contains(".")){
        n = s.indexOf(".");
        ss = s.mid(n + 1);
        ss = ss.simplified();
        s3 = s3.left(index);
        n = s3.lastIndexOf(".") + 1;
        
      } else {
        ss = s;
        ss = ss.simplified();
        n = 1;
      }
    }
  }
  
  
w:
  ss2 = ss2.left(n);
  n--;
  if (n < 0) n = 0;
  if (!ss2.isEmpty()){
    QChar c = ss2.at(n);
    if (c == '.'){
      ss2 = ss2.left(n);
      n--;
    //  bool b = true;
      while(n > 0){
        c = ss2.at(n);
        if (!(c.isLetterOrNumber() || c == '_'/* && (c.isNumber() && b)*/)) break;
        //if (c.isNumber() && b) b = false;
        n--;
      }
    }
  }
  ss2 = ss2.mid(n);
  ss2 = ss2.simplified();

  QList<_inputtip_info>l = EXTERN_my_mainwindow->ci_getFindDefinition(my_sourcecodeeditor_editor->my_sourcecodeeditor->getFilename(), my_sourcecodeeditor_editor->my_sourcecodeeditor->getScope(), my_sourcecodeeditor_editor->my_sourcecodeeditor->getScope2(), ss, ss2);
  
  if (l.count() == 1){
    _inputtip_info v = l.at(0);
    QString sss = (v.scope.isEmpty() ? "" : v.scope + ".") + (v.scope2.isEmpty() ? "" : v.scope2 + ".") + v.name + " (" + EXTERN_my_mainwindow->getFilenameWithoutPath(v.file) + ")" + " in file " + v.file + " at line " + QString("%1").arg(v.line);
    lw->performFindDefinition(sss);
    delete lw;

  } else if (l.count() > 1){

    foreach (_inputtip_info v, l)
    { 
      QString ss = "";
      QString sss = (v.scope.isEmpty() ? "" : v.scope + ".") + (v.scope2.isEmpty() ? "" : v.scope2 + ".") + v.name + " (" + EXTERN_my_mainwindow->getFilenameWithoutPath(v.file) + ")" + " in file " + v.file + " at line " + QString("%1").arg(v.line);
      switch(v.type){
        case __sub: ss = "ide//Sub.png"; break;
        case __function: ss = "ide//Function.png"; break;
        case __constructor: ss = "ide//Constructor.png"; break;
        case __property2: ss = "ide//Property.png"; break;
        case __enum: ss = "ide//Enum.png"; break;
        case __type: ss = "ide//Type.png"; break;
        case __class: ss = "ide//Class.png"; break;
        case __module: ss = "ide//Module.png"; break;
        case __constant: ss = "ide//Constant.png"; break;
        case __variable: ss = "ide//Variable.png"; break;

      }
      if (ss.isEmpty()){
        lw->addItem(sss);
      } else {
        lw->addItem(new QListWidgetItem(kbasicIcon(kbasicPath(ss)), sss));
      }
      lw->show();
    }
  }
  //my_sourcecodeeditor_editor->undo();
}

_finddefinition::_finddefinition() : QListWidget((QWidget *) 0)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Tool);
  setWindowTitle(tr("Found Symbols"));
//    setModal(true);
  resize(350, 150);
  setGeometry(QApplication::desktop()->width() / 2 - width() / 2 - 50, QApplication::desktop()->height() / 2 - height() / 2 - 50, width(), height());
  
  connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClicked(QListWidgetItem*)));
}

void _finddefinition::itemDoubleClicked(QListWidgetItem *item)
{
  performFindDefinition(item->text());
  hide();
  close();
}

void _finddefinition::performFindDefinition(QString s)
{
  QString sFilename = "";
  QString sLine = "";

  int n = s.lastIndexOf("in file");
  int n2 = s.lastIndexOf("at line");

  if (n >= 0) sFilename = s.mid(n + 7, n2 - (n + 7));
  sFilename = sFilename.simplified();

  if (n2 >= 0) sLine = s.mid(n2 + 7);
  sLine = sLine.simplified();
  
  int nLine = sLine.toInt();
  EXTERN_my_mainwindow->gotoFileLine(sFilename, nLine);
}

void _sourcecodeeditor::showEvents()
{

  if (my_sourcecodeeditor_editor->my_inputtip){
    my_sourcecodeeditor_editor->hideInput();
    return;
  }

  QWidget *c;

  QStringList ln;
  QStringList lt;
  QStringList lm;

  if (EXTERN_my_form && EXTERN_my_form->firstControl(&c)){

    do {

      if (c->isHidden()) continue;

      QString sName = "";
      QString sControlType = "";

      #define SWITCH6 EXTERN_my_form->controlType(c)

      #define SWITCH GETPROPERTY_Name();
      #define SWITCH3 sName
      #include "../kbshared/_form_property_switch.h" 
      #undef SWITCH3

      #define SWITCH GETPROPERTY_ControlType();
      #define SWITCH3 sControlType
      #include "../kbshared/_form_property_switch.h" 
      #undef SWITCH3

      #undef SWITCH6

      ln.append(sName);
      lt.append(sControlType);

    } while (EXTERN_my_form->nextControl(&c)); 

  }

  if (EXTERN_my_report && EXTERN_my_report->firstControl(&c)){

    do {

      if (c->isHidden()) continue;

      QString sName = "";
      QString sControlType = "";

      #define SWITCH6 EXTERN_my_report->controlType(c)

      #define SWITCH GETPROPERTY_Name();
      #define SWITCH3 sName
      #include "../kbshared/_form_property_switch.h" 
      #undef SWITCH3

      #define SWITCH GETPROPERTY_ControlType();
      #define SWITCH3 sControlType
      #include "../kbshared/_form_property_switch.h" 
      #undef SWITCH3

      #undef SWITCH6

      ln.append(sName);
      lt.append(sControlType);

    } while (EXTERN_my_report->nextControl(&c)); 

  }

  QString s = getFilename();
  if (s.endsWith(".kbasic_form", Qt::CaseInsensitive)){
    lt.append("Form");
    ln.append("Form");
  } else if (s.endsWith(".kbasic_report", Qt::CaseInsensitive)){
    lt.append("Report");
    ln.append("Report");
  } else if (s.endsWith(".kbasic_menubar", Qt::CaseInsensitive)){
    lt.append("MenuBar");
    ln.append("MenuBar");
  } else if (s.endsWith(".kbasic_toolbar", Qt::CaseInsensitive)){
    lt.append("ToolBar");
    ln.append("ToolBar");
  }
  //ln.append(EXTERN_my_form->GETPROPERTY_Name());
/*
  if (my_sourcecodeeditor_editor->my_inputtip){
    my_sourcecodeeditor_editor->hideInput();
  }*/

  if (ln.size()){
    my_sourcecodeeditor_editor->my_inputtip = new _inputtip(this->my_sourcecodeeditor_editor, false, false, false, "", "", ln, lt, lm);  
    if (my_sourcecodeeditor_editor->my_inputtip->count()){
      my_sourcecodeeditor_editor->my_inputtip->move(events->x() + 2, 2);  
      my_sourcecodeeditor_editor->my_inputtip->show();
    }
  }

}

void _sourcecodeeditor::showEvents2(QString sControlName)
{
  QWidget *c;

  QStringList ln;
  QStringList lt;
  QStringList lm;

  if (sControlName == "Form"){
    lm.append("Form");
//    lm.append(EXTERN_my_form->GETPROPERTY_Name());
    lm.append(sControlName);
  } else if (sControlName == "Report"){
    lm.append("Report");
    lm.append(sControlName);
  } else if (sControlName == "MenuBar"){
    lm.append("MenuBar");
    lm.append(sControlName);
  } else if (sControlName == "ToolBar"){
    lm.append("ToolBar");
//    lm.append(EXTERN_my_toolbar->getFilenameWithoutPathAndExtension());
    lm.append(sControlName);

  } else if (EXTERN_my_form->firstControl(&c)){

    do {

      if (c->isHidden()) continue;

      QString sName = "";
      QString sControlType = "";

      #define SWITCH6 EXTERN_my_form->controlType(c)

      #define SWITCH GETPROPERTY_Name();
      #define SWITCH3 sName
      #include "../kbshared/_form_property_switch.h" 
      #undef SWITCH3

      #define SWITCH GETPROPERTY_ControlType();
      #define SWITCH3 sControlType
      #include "../kbshared/_form_property_switch.h" 
      #undef SWITCH3

      #undef SWITCH6

      if (sControlName == sName){
        lm.append(sName);
        lm.append(sControlType);
        break;
      }

    } while (EXTERN_my_form->nextControl(&c)); 

  } else if (EXTERN_my_report->firstControl(&c)){

    do {

      if (c->isHidden()) continue;

      QString sName = "";
      QString sControlType = "";

      #define SWITCH6 EXTERN_my_report->controlType(c)

      #define SWITCH GETPROPERTY_Name();
      #define SWITCH3 sName
      #include "../kbshared/_form_property_switch.h" 
      #undef SWITCH3

      #define SWITCH GETPROPERTY_ControlType();
      #define SWITCH3 sControlType
      #include "../kbshared/_form_property_switch.h" 
      #undef SWITCH3

      #undef SWITCH6

      if (sControlName == sName){
        lm.append(sName);
        lm.append(sControlType);
        break;
      }

    } while (EXTERN_my_report->nextControl(&c)); 

  }  

  if (my_sourcecodeeditor_editor->my_inputtip2){
    my_sourcecodeeditor_editor->hideInput2();
  }

  if (lm.size()){
    my_sourcecodeeditor_editor->my_inputtip2 = new _inputtip(this->my_sourcecodeeditor_editor, false, false, false, "", "", ln, lt, lm);  
    if (my_sourcecodeeditor_editor->my_inputtip2->count()){
      my_sourcecodeeditor_editor->my_inputtip2->move(events->x() + 2 + my_sourcecodeeditor_editor->my_inputtip->width(), 2);  
      my_sourcecodeeditor_editor->my_inputtip2->resize(my_sourcecodeeditor_editor->width() - my_sourcecodeeditor_editor->my_inputtip->width() - 5, my_sourcecodeeditor_editor->my_inputtip->height());
      my_sourcecodeeditor_editor->my_inputtip2->show();
    }
  }

}



_border::_border(_sourcecodeeditor *e ) : QWidget (e)
{
  editor = e;
  done();    
}

void _border::mouseDoubleClickEvent ( QMouseEvent * e)
{
  bDouble = true;  
/*
  int y = editor->my_sourcecodeeditor_editor->verticalScrollBar()->value();
  QTextCursor c = editor->my_sourcecodeeditor_editor->cursorForPosition(QPoint(10, e->y() + y - 6));
  int nLine = c.blockNumber();
  
  c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, nLine);

  c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);  
  editor->my_sourcecodeeditor_editor->setTextCursor(c);*/
}

void _border::mouseMoveEvent ( QMouseEvent * e)
{
  if (bButton){
    select(e);
  }
}

void _border::mousePressEvent ( QMouseEvent * e )
{
  bButton = true;
 //QTextCursor c = editor->my_sourcecodeeditor_editor->cursorForPosition(QPoint(10, e->y() + editor->my_sourcecodeeditor_editor->contentsY() - 6));
 // nStartLine = c.blockNumber();
}

void _border::mouseReleaseEvent ( QMouseEvent * e )
{
  select(e);
  done();
}

void _border::leaveEvent ( QEvent * e )
{
  done();
}

void _border::done ()
{
  nStartLine = -1;
  bButton = false;
  bDouble = false;  
}

void _border::select (QMouseEvent * e)
{
/*
  int y = editor->my_sourcecodeeditor_editor->verticalScrollBar()->value();
  QTextCursor c = editor->my_sourcecodeeditor_editor->cursorForPosition(QPoint(10, e->y() + y - 6));
  int nLine = c.blockNumber();
  
  c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, nStartLine);

  c.movePosition(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, nStartLine - nLine < 0 ? nLine - nStartLine : nStartLine - nLine);
  c.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);  
  editor->my_sourcecodeeditor_editor->setTextCursor(c);
*/
  /*
  {
    int nLine = editor->paragraphAt(QPoint(10, e->y() + editor->contentsY() - 6));
    editor->setSelection (nStartLine, 0, nLine, 9999);
    editor->setCursorPosition(nLine > nStartLine ? nLine + 1 : nStartLine + 1, 0);
    editor->ensureCursorVisible();        
  }
  editor->my_mainwindow->updateByEditor();
  */
}

QString _sourcecodeeditor::getFilename(){ return filename; }


void _sourcecodeeditor::reloadAfterFileReplacement()
{
  QTextCursor c = my_sourcecodeeditor_editor->textCursor();
  int n = c.position();

  QString s = getFilename();

  load(s, bClassForm);
  c.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor);
  c.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, n);

  my_sourcecodeeditor_editor->setTextCursor(c);


}
