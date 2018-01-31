#include "mainwindow.h"
#include "data.h"
#include "QTime"
#include <synchapi.h>

extern Data graph_data;
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    graph_data.ifpaint=true;

    QToolBar *bar = this->addToolBar("Tools");
    QActionGroup *group = new QActionGroup(bar);

    bar->setFixedSize(1000,50);

    drawPointAction = new QAction("Point", bar);
    drawPointAction->setIcon(QIcon(":/new/icon/icon/Point.png"));
    drawPointAction->setToolTip(tr("Draw a Point."));
    drawPointAction->setStatusTip(tr("Draw a Point."));
    drawPointAction->setCheckable(true);
    drawPointAction->setChecked(true);
    group->addAction(drawPointAction);
    bar->addAction(drawPointAction);

    QAction *drawEdgeAction = new QAction("Edge", bar);
    QIcon edgeicon(":/new/icon/icon/Edge.png");
    drawEdgeAction->setIcon(edgeicon);
    drawEdgeAction->setToolTip(tr("Draw a Edge."));
    drawEdgeAction->setStatusTip(tr("Draw a Edge."));
    drawEdgeAction->setCheckable(true);
    group->addAction(drawEdgeAction);
    bar->addAction(drawEdgeAction);

    QAction *drawUndirEdgeAction = new QAction("UndirEdge", bar);
    QIcon undiredgeicon(":/new/icon/icon/UndirEdge.png");
    drawUndirEdgeAction->setIcon(undiredgeicon);
    drawUndirEdgeAction->setToolTip(tr("Draw a UndirEdge."));
    drawUndirEdgeAction->setStatusTip(tr("Draw a UndirEdge."));
    drawUndirEdgeAction->setCheckable(true);
    group->addAction(drawUndirEdgeAction);
    bar->addAction(drawUndirEdgeAction);

    QAction *finishAction = new QAction("Finish",bar);
    finishAction->setIcon(QIcon(":/new/icon/icon/Finish.png"));
    finishAction->setToolTip(tr("Judge the graph."));
    finishAction->setStatusTip(tr("Judge the graph."));
    finishAction->setCheckable(true);
    group->addAction(finishAction);
    bar->addAction(finishAction);

    QAction *bianliAction = new QAction("Bianli",bar);
    bianliAction->setIcon(QIcon(":/new/icon/icon/Bianli.png"));
    bianliAction->setToolTip(tr("Bianli the graph."));
    bianliAction->setStatusTip(tr("Bianli the graph."));
    bianliAction->setCheckable(true);
    group->addAction(bianliAction);
    bar->addAction(bianliAction);

    QAction *MSTAction = new QAction("MST",bar);
    MSTAction->setIcon(QIcon(":/new/icon/icon/Tree.png"));
    MSTAction->setToolTip(tr("Cal the MST of the graph."));
    MSTAction->setStatusTip(tr("Cal the MST of the graph."));
    MSTAction->setCheckable(true);
    group->addAction(MSTAction);
    bar->addAction(MSTAction);

    QAction *SPAction = new QAction("SP",bar);
    SPAction->setIcon(QIcon(":/new/icon/icon/SP.png"));
    SPAction->setToolTip(tr("Cal the SP of the graph."));
    SPAction->setStatusTip(tr("Cal the SP of the graph."));
    SPAction->setCheckable(true);
    group->addAction(SPAction);
    bar->addAction(SPAction);

    QAction *ClearAction = new QAction("Clear",bar);
    ClearAction->setIcon(QIcon(":/new/icon/icon/Clear.png"));
    ClearAction->setToolTip(tr("Clear of the graph."));
    ClearAction->setStatusTip(tr("Clear of the graph."));
    group->addAction(ClearAction);
    bar->addAction(ClearAction);

    addToolBarBreak();
    QToolBar *ibar = this->addToolBar("Information");
    ibar->setFixedSize(1000,30);
    label = new QLabel(ibar);
    if(graph_data.ifpaint)
        label->setText("Please paint some points.");
    else
        label->setText("Sorry, you can't add new points now.");
    label->setAlignment(Qt::AlignCenter);
    QFont ft;
    ft.setPointSize(12);
    label->setFont(ft);
    ibar->addWidget(label);;

    QLabel *statusMsg = new QLabel;
    statusBar()->addWidget(statusMsg);

    PaintWidget *paintWidget = new PaintWidget(this);
    setCentralWidget(paintWidget);

    connect(drawEdgeAction, SIGNAL(triggered()),
                        this, SLOT(drawEdgeActionTriggered()));
    connect(drawPointAction, SIGNAL(triggered()),
                    this, SLOT(drawPointActionTriggered()));
    connect(drawUndirEdgeAction,SIGNAL(triggered()),
                        this, SLOT(drawUndirEdgeActionTriggered()));
    connect(finishAction,SIGNAL(triggered(bool)),
                    this,SLOT(finishActionTriggered()));
    connect(bianliAction,SIGNAL(triggered(bool)),
                    this,SLOT(bianliActionTriggered()));
    connect(MSTAction,SIGNAL(triggered(bool)),
                    this,SLOT(drawMSTActionTriggered()));
    connect(SPAction,SIGNAL(triggered(bool)),
                    this,SLOT(drawSPActionTriggered()));
    connect(ClearAction,SIGNAL(triggered(bool)),
                    this,SLOT(clearActionTriggered()));
    connect(this, SIGNAL(changeCurrentShape(Shape::Code)),
                    paintWidget, SLOT(setCurrentShape(Shape::Code)));
}

void MainWindow::drawEdgeActionTriggered()
{
    if(graph_data.ifpaint && graph_data.etype!=2)
        label->setText("Please paint some directed edges.");
    else
        label->setText("Sorry, you can't add new directed edges now.");
    emit changeCurrentShape(Shape::Edge);
}

void MainWindow::drawUndirEdgeActionTriggered()
{
    if(graph_data.ifpaint && graph_data.etype!=1)
        label->setText("Please paint some undirected edges.");
    else
        label->setText("Sorry, you can't add new undirected edges now.");
    emit changeCurrentShape(Shape::UndirEdge);
}

void MainWindow::drawPointActionTriggered()
{
    if(graph_data.ifpaint)
        label->setText("Please paint some points.");
    else
        label->setText("Sorry, you can't add new points now.");
    emit changeCurrentShape(Shape::Point);
}

void MainWindow::finishActionTriggered()
{
    if(graph_data.etype==0)
        graph_data.etype=2;
    graph_data.ifpaint=false;

    graph_data.judge();
    graph_data.initxulie();

    PaintBeautify *paintbeautify = new PaintBeautify(this);
    setCentralWidget(paintbeautify);
    if(graph_data.type==1)
        label->setText("It is a tree");
    else if(graph_data.type==2)
        label->setText("It is a forest");
    else
        label->setText("It is a general graph.");
    emit changeCurrentShape(Shape::Finish);
}

void MainWindow::bianliActionTriggered()
{
    graph_data.initxulie();
    graph_data.ifpaint=false;

    if(graph_data.type==2)
    {
        QString qs="The preorder traversal sequence is : ";
        QString id;
        id.setNum(graph_data.xulie1[1],10);
        qs.insert(qs.length(),id);
        for(int i=2;i<=graph_data.pnum;i++)
        {
            qs.insert(qs.length(),' ');
            id.setNum(graph_data.xulie1[i],10);
            qs.insert(qs.length(),id);
        }
        label->setText(qs);
    }
    else if(graph_data.type==1)
    {
        QString qs="Preorder : ";
        QString id;
        id.setNum(graph_data.xulie1[1],10);
        qs.insert(qs.length(),id);
        for(int i=2;i<=graph_data.pnum;i++)
        {
            qs.insert(qs.length(),' ');
            id.setNum(graph_data.xulie1[i],10);
            qs.insert(qs.length(),id);
        }

        qs.insert(qs.length()," , Postorder : ");
        id.setNum(graph_data.xulie2[1],10);
        qs.insert(qs.length(),id);
        for(int i=2;i<=graph_data.pnum;i++)
        {
            qs.insert(qs.length(),' ');
            id.setNum(graph_data.xulie2[i],10);
            qs.insert(qs.length(),id);
        }
        label->setText(qs);
    }
    else
    {
        QString qs="DFS : ";
        QString id;
        id.setNum(graph_data.xulie1[1],10);
        qs.insert(qs.length(),id);
        for(int i=2;i<=graph_data.pnum;i++)
        {
            qs.insert(qs.length(),' ');
            id.setNum(graph_data.xulie1[i],10);
            qs.insert(qs.length(),id);
        }

        qs.insert(qs.length()," , BFS : ");
        id.setNum(graph_data.xulie2[1],10);
        qs.insert(qs.length(),id);
        for(int i=2;i<=graph_data.pnum;i++)
        {
            qs.insert(qs.length(),' ');
            id.setNum(graph_data.xulie2[i],10);
            qs.insert(qs.length(),id);
        }
        label->setText(qs);
    }

    PaintBianli *paintbianli = new PaintBianli(this);
    setCentralWidget(paintbianli);
    emit changeCurrentShape(Shape::Bianli);
}

void MainWindow::drawMSTActionTriggered()
{
    graph_data.ifpaint=false;
    int ans = graph_data.judgeMST();
    if(ans!=-1)
    {
        PaintMST *paintmst = new PaintMST(this);
        setCentralWidget(paintmst);
        QString qs = "It is one of the MST. Weight = ";
        QString weight;
        weight.setNum(ans,10);
        qs.insert(qs.length(),weight);
        label->setText(qs);
        emit changeCurrentShape(Shape::MST);
    }
    else
    {
        label->setText("Unfortunately, the graph does not have a MST.");
    }
}

void MainWindow::drawSPActionTriggered()
{
    graph_data.ifpaint=false;
    bool isOK;
    QString text = QInputDialog::getText(NULL, "Input the start point",
                                                       "Please input the start point",
                                                       QLineEdit::Normal,
                                                       "1",
                                                       &isOK);
    if(isOK)
    {
        bool ifok;
        graph_data.start=text.toInt(&ifok,10);
        QString qs = "Point ";
        QString id;
        id.setNum(graph_data.start,10);
        qs.insert(qs.length(),id);
        qs.insert(qs.length()," as the start point, the shortest paths as follow.");
        label->setText(qs);
    }
    PaintSP *paintsp = new PaintSP(this);
    setCentralWidget(paintsp);
    emit changeCurrentShape(Shape::SP);
}

void MainWindow::clearActionTriggered()
{
    drawPointAction->setChecked(true);
    graph_data.ifpaint=true;
    graph_data.clear();
    label->setText("Now, you can paint a new graph.");

    PaintWidget *paintWidget = new PaintWidget(this);
    setCentralWidget(paintWidget);
    emit changeCurrentShape(Shape::Point);
    connect(this, SIGNAL(changeCurrentShape(Shape::Code)),
                    paintWidget, SLOT(setCurrentShape(Shape::Code)));
}
